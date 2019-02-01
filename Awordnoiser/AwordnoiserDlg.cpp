
// AwordnoiserDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Awordnoiser.h"
#include "AwordnoiserDlg.h"
#include "afxdialogex.h"

#include "noise.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAwordnoiserDlg ��ȭ ����



CAwordnoiserDlg::CAwordnoiserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AWORDNOISER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAwordnoiserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editWord);
	DDX_Control(pDX, IDC_CHECK1, m_ckop1);
	DDX_Control(pDX, IDC_CHECK2, m_ckop2);
	DDX_Control(pDX, IDC_CHECK3, m_ckop3);
	DDX_Control(pDX, IDC_CHECK4, m_ckop4);
	DDX_Control(pDX, IDC_CHECK5, m_ckop5);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_BUTTON1, m_btnRun);
}

BEGIN_MESSAGE_MAP(CAwordnoiserDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAwordnoiserDlg::OnBnClickedButton_Run)
	ON_BN_CLICKED(IDC_BUTTON2, &CAwordnoiserDlg::OnBnClickedButton_Expectedwork)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAwordnoiserDlg �޽��� ó����

BOOL CAwordnoiserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_ckop1.SetCheck(TRUE);
	m_ckop3.SetCheck(TRUE);
	m_ckop4.SetCheck(TRUE);
	m_ckop5.SetCheck(TRUE);

	CString strPath = _T("");
	strPath = GetCurretDirectory();

	m_strMyDirectory.Format(_T("%s\\Awordnoiser"), strPath);
	if (_taccess(m_strMyDirectory, 0) == ISNOTNORMAL)
	{
		if (CreateDirectory(m_strMyDirectory, NULL) == FALSE)
		{
			return FALSE;
		}
	}	

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CAwordnoiserDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CAwordnoiserDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CAwordnoiserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CAwordnoiserDlg::GetCurretDirectory()
{
	CString strPath = _T("");

	TCHAR szCurPath[SIZE_DEFAUTL] = { 0, };
	GetModuleFileName(AfxGetInstanceHandle(), szCurPath, SIZE_DEFAUTL);
	(*_tcsrchr(szCurPath, _T('\\'))) = _T('\0');

	strPath = szCurPath; 

	return strPath;
}

void CAwordnoiserDlg::CaptureEditcontrol()
{
	// ĸó�ؼ� ���Ϸ� �����Ұž�

	CWnd*  myWnd = this->GetDlgItem(IDC_EDIT1);
	CDC memDC;
	CBitmap bitmap;

	CClientDC dc(this);      // dc�������ְ� (this)�� ȭ���� ����ϱ� ���ؼ���
	CClientDC ScreenDC(myWnd);   // ��ũ��DC ����

	memDC.CreateCompatibleDC(&ScreenDC);   // ��ũ��DC�� ȣȯ�Ǵ� DC����
	bitmap.CreateCompatibleBitmap(&ScreenDC, NUM_SIZE_WIDTH, NUM_SIZE_HEIGHT);   // ��ũ��DC�� ȣȯ�Ǵ� ��Ʈ�� ����
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);   // Bitmap �����͸� �Ѱ���
	memDC.StretchBlt(0, 0, NUM_SIZE_WIDTH, NUM_SIZE_HEIGHT, &ScreenDC, 0, 0, NUM_SIZE_WIDTH, NUM_SIZE_HEIGHT, SRCCOPY);   // ��ũ��DC�� �����ȭ���� memDC�� copy, bitmap���� ��ϵ�
																														  // ���
	dc.BitBlt(0, 0, NUM_SIZE_WIDTH, NUM_SIZE_HEIGHT, &memDC, 0, 0, SRCCOPY);   // 0,0 ���� �ػ�ũ����� memDC�� ����Ű�� ������ 0, 0���� �����ؼ� �����

	memDC.SelectObject(pOldBitmap);

}

BOOL CAwordnoiserDlg::RunWordnoiser(CString strWord, CStringList& strWordlist)
{
	BOOL bResult = FALSE; 

	if (strWord.IsEmpty() == TRUE)
	{
		return FALSE;
	}

	strWordlist.RemoveAll();

	CNoise Noiser(m_strMyWord, 1, m_ckop1.GetCheck(), m_ckop2.GetCheck(), m_ckop3.GetCheck(), m_ckop4.GetCheck(), m_ckop5.GetCheck());
	Noiser.GetWordList(strWordlist);

	if (strWordlist.IsEmpty() == FALSE)
	{
		bResult = TRUE;
	}

	return bResult; 
}

void CAwordnoiserDlg::OnBnClickedButton_Run()
{
	if (m_bDoing == FALSE)
	{
		CString		strWord = _T("");
		CString		strwordDir = _T("");

		m_editWord.GetWindowTextW(strWord);
		if (strWord.IsEmpty() == TRUE)
		{
			AfxMessageBox(_T("...?"));
			return;
		}

		strwordDir.Format(_T("%s\\%s"), m_strMyDirectory, strWord);
		if (_taccess(strwordDir, 0) == ISNOTNORMAL)
		{
			if (CreateDirectory(strwordDir, NULL) == FALSE)
			{
				CString strMsg = _T("");
				strMsg.Format(_T("CreateDirectory fail, wordDir:%s"), strwordDir);
				AfxMessageBox(strMsg);
			}
		}
			
		if (RunWordnoiser(strWord, m_strWordlist) == TRUE)
		{
			if (m_strWordlist.IsEmpty() == TRUE)
			{
				AfxMessageBox(_T("wordlist is empty"));
			}
			else
			{
				m_progress.SetRange(0, m_strWordlist.GetCount());
				m_progress.SetPos(0);
				m_nTimer = SetTimer(1, 100, 0);
				
				m_bDoing = TRUE;
				m_btnRun.SetWindowTextW(_T("����"));
			}
		}
		else
		{
			AfxMessageBox(_T("RunWordnoiser failed"));
		}
	}
	else
	{
		m_bDoing = FALSE;
		m_btnRun.SetWindowTextW(_T("�����"));
		if (m_nTimer)
		{
			KillTimer(m_nTimer);
		}
	}		
}

void CAwordnoiserDlg::OnBnClickedButton_Expectedwork()
{
	CString		strWord = _T("");
	m_editWord.GetWindowTextW(strWord);
	if (strWord.IsEmpty() == TRUE)
	{
		AfxMessageBox(_T("...?"));
		return;
	}

	if (RunWordnoiser(strWord, m_strWordlist) == TRUE)
	{
		CString strMsg = _T("");
		strMsg.Format(_T("���� �ܾ� ��:%d"), m_strWordlist.GetCount());
		AfxMessageBox(strMsg);
	}
	else
	{
		AfxMessageBox(_T("RunWordnoiser failed"));
	}
}

void CAwordnoiserDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		CString strEdit = _T("");
		m_editWord.GetWindowTextW(strEdit);
		if (strEdit.IsEmpty() == TRUE)
		{
			KillTimer(m_nTimer);
			m_nfile = 0;			
			m_progress.SetPos(m_strWordlist.GetCount());
			AfxMessageBox(_T("��"));
		}
		else
		{
			CaptureEditcontrol();		
			m_progress.SetPos(m_nfile);
		}		
	}

	CDialogEx::OnTimer(nIDEvent);
}
