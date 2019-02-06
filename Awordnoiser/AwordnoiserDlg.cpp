
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

#pragma warning (disable:4996)

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
	DDX_Control(pDX, IDC_CHECK6, m_ckWordset);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_BUTTON1, m_btnRun);
	DDX_Control(pDX, IDC_EDIT_FILTER, m_editFilter);
	DDX_Control(pDX, IDC_ST_COUNT, m_stCount);
	DDX_Control(pDX, IDC_ST_INDEX, m_stIndex);
	DDX_Control(pDX, IDC_ST_WORDSET_PATH, m_stWordsetPath);	
}

BEGIN_MESSAGE_MAP(CAwordnoiserDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAwordnoiserDlg::OnBnClickedButton_Run)
	ON_BN_CLICKED(IDC_BUTTON2, &CAwordnoiserDlg::OnBnClickedButton_Expectedwork)
	ON_WM_TIMER()
	ON_WM_DROPFILES()
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

	m_editFilter.SetWindowTextW(_T("10"));

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

void CAwordnoiserDlg::CaptureEditcontrol(int nWidth /*= NUM_SIZE_WIDTH*/, int nHeight /*= NUM_SIZE_HEIGHT*/)
{
	CWnd*  myWnd = this->GetDlgItem(IDC_EDIT1);
	CClientDC ScreenDC(myWnd);
	HDC h_screen_dc = ScreenDC;

	// DIB���� ����
	BITMAPINFO dib_define;
	dib_define.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	dib_define.bmiHeader.biWidth = nWidth;
	dib_define.bmiHeader.biHeight = nHeight;
	dib_define.bmiHeader.biPlanes = 1;
	dib_define.bmiHeader.biBitCount = 24;
	dib_define.bmiHeader.biCompression = BI_RGB;
	dib_define.bmiHeader.biSizeImage = (((nWidth * 24 + 31) & ~31) >> 3) * nHeight;
	dib_define.bmiHeader.biXPelsPerMeter = 0;
	dib_define.bmiHeader.biYPelsPerMeter = 0;
	dib_define.bmiHeader.biClrImportant = 0;
	dib_define.bmiHeader.biClrUsed = 0;

	// DIB�� ���� �̹��� ��Ʈ ������ ������ ������ ����
	BYTE *p_image_data = NULL;

	// dib_define�� ���ǵ� �������� DIB����
	HBITMAP h_bitmap = ::CreateDIBSection(h_screen_dc, &dib_define, DIB_RGB_COLORS, (void **)&p_image_data, 0, 0);

	// ĸ���� �̹��� ������ ���� ���� dc����
	HDC h_memory_dc = ::CreateCompatibleDC(h_screen_dc);

	// ���� DC�� �̹����� ������ ��Ʈ�� ����
	HBITMAP h_old_bitmap = (HBITMAP)::SelectObject(h_memory_dc, h_bitmap);

	// ȭ���� ĸ��
	::BitBlt(h_memory_dc, 0, 0, nWidth, nHeight, h_screen_dc, 0, 0, SRCCOPY);

	// ������ ��Ʈ������ ����
	::SelectObject(h_memory_dc, h_old_bitmap);

	// ���� DC�� ����
	DeleteDC(h_memory_dc);

	// DIB ������ ��� ���� ����
	BITMAPFILEHEADER dib_format_layout;
	ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
	dib_format_layout.bfType = *(WORD*)"BM";
	dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dib_define.bmiHeader.biSizeImage;
	dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// �̹��� ���� ����
	CString strFilename = _T("");
	strFilename.Format(_T("%s\\%s\\%s_%d.jpg"), m_strMyDirectory, m_strMyWord, m_strMyWord, m_nfile);
	int length = strFilename.GetLength();
	char* st = new char[length];
	strcpy(st, (CT2A)strFilename);

	FILE *p_file = fopen(st, "wb");
	if (p_file != NULL) {
		fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
		fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), p_file);
		fwrite(p_image_data, 1, dib_define.bmiHeader.biSizeImage, p_file);
		fclose(p_file);
		++m_nfile;
	}

	// ����ߴ� ��Ʈ�ʰ� DC �� �����Ѵ�.
	if (NULL != h_bitmap) DeleteObject(h_bitmap);
	if (NULL != h_screen_dc) ::ReleaseDC(NULL, h_screen_dc);

// 	CWnd*  myWnd = this->GetDlgItem(IDC_EDIT1);
// 	CDC memDC;
// 	CBitmap bitmap;
// 
// 	CClientDC dc(this);      // dc�������ְ� (this)�� ȭ���� ����ϱ� ���ؼ���
// 	CClientDC ScreenDC(myWnd);   // ��ũ��DC ����
// 
// 	memDC.CreateCompatibleDC(&ScreenDC);   // ��ũ��DC�� ȣȯ�Ǵ� DC����
// 	bitmap.CreateCompatibleBitmap(&ScreenDC, NUM_SIZE_WIDTH, NUM_SIZE_HEIGHT);   // ��ũ��DC�� ȣȯ�Ǵ� ��Ʈ�� ����
// 	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);   // Bitmap �����͸� �Ѱ���
// 	memDC.StretchBlt(0, 0, NUM_SIZE_WIDTH, NUM_SIZE_HEIGHT, &ScreenDC, 0, 0, NUM_SIZE_WIDTH, NUM_SIZE_HEIGHT, SRCCOPY);   // ��ũ��DC�� �����ȭ���� memDC�� copy, bitmap���� ��ϵ�
// 																														  // ���
// 	dc.BitBlt(0, 0, NUM_SIZE_WIDTH, NUM_SIZE_HEIGHT, &memDC, 0, 0, SRCCOPY);   // 0,0 ���� �ػ�ũ����� memDC�� ����Ű�� ������ 0, 0���� �����ؼ� �����
// 
// 	memDC.SelectObject(pOldBitmap);
// 	DeleteDC(memDC);
// 
// 
// 	// DIB�� ������ �����Ѵ�.
// 	BITMAPINFO dib_define;
// 	dib_define.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
// 	dib_define.bmiHeader.biWidth = NUM_SIZE_WIDTH;
// 	dib_define.bmiHeader.biHeight = NUM_SIZE_HEIGHT;
// 	dib_define.bmiHeader.biPlanes = 1;
// 	dib_define.bmiHeader.biBitCount = 24;
// 	dib_define.bmiHeader.biCompression = BI_RGB;
// 	dib_define.bmiHeader.biSizeImage = (((NUM_SIZE_WIDTH * 24 + 31) & ~31) >> 3) * NUM_SIZE_HEIGHT;
// 	dib_define.bmiHeader.biXPelsPerMeter = 0;
// 	dib_define.bmiHeader.biYPelsPerMeter = 0;
// 	dib_define.bmiHeader.biClrImportant = 0;
// 	dib_define.bmiHeader.biClrUsed = 0;
// 	
// 	// DIB ������ ��� ������ �����Ѵ�.
// 	BITMAPFILEHEADER dib_format_layout;
// 	ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
// 	dib_format_layout.bfType = *(WORD*)"BM";
// 	dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dib_define.bmiHeader.biSizeImage;
// 	dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
// 
// 	CString strFilename = _T("");
// 	strFilename.Format(_T("%s\\%s\\%s_%d.jpg"), m_strMyDirectory, m_strMyWord, m_strMyWord, m_nfile);
// 	int length = strFilename.GetLength();
// 	char* st = new char[length];
// 	//strcpy_s(st, length, (CT2A)strFilename);
// 	strcpy(st, (CT2A)strFilename);
// 
// 	errno_t err = 0;
// 	FILE *p_file =fopen(st, "wb");
// 	//err = fopen_s(&p_file, st, "wb");
// 	if ((err == 0)&&(p_file != NULL))
// 	{			
// 		fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);		
// 		fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), p_file);		
// 		fwrite(NULL, 1, dib_define.bmiHeader.biSizeImage, p_file);	
// 		++m_nfile;
// 	}
}

BOOL CAwordnoiserDlg::RunWordnoiser(CString strWord, CStringList& strWordlist, int nFilter /*= 10*/)
{
	BOOL bResult = FALSE; 

	if (strWord.IsEmpty() == TRUE)
	{
		return FALSE;
	}

	strWordlist.RemoveAll();

	CNoise Noiser(strWord, nFilter, m_ckop1.GetCheck(), m_ckop2.GetCheck(), m_ckop3.GetCheck(), m_ckop4.GetCheck(), m_ckop5.GetCheck());
	Noiser.GetWordList(strWordlist);

	if (strWordlist.IsEmpty() == FALSE)
	{
		m_strMyWord = strWord; 
		bResult = TRUE;
	}

	return bResult; 
}

void CAwordnoiserDlg::ClearContorl()
{
	m_nfile = 0;
	m_progress.SetPos(m_strWordlist.GetCount());

	AfxMessageBox(_T("��"));
	m_btnRun.SetWindowTextW(_T("�����"));
	m_editWord.SetWindowTextW(m_strMyWord);
	m_progress.SetPos(0);
	m_stIndex.SetWindowTextW(_T(""));
	m_stCount.SetWindowTextW(_T(""));
}

void CAwordnoiserDlg::SetDlgControlIndex()
{
	m_progress.SetPos(m_nfile);

	CString strMsg = _T("");
	strMsg.Format(_T("%d/"), m_nfile);
	m_stIndex.SetWindowTextW(strMsg);

}

void CAwordnoiserDlg::SetEditcontrolText()
{
	m_editWord.SetWindowText(_T(""));
	m_editWord.SetWindowText(m_strWordlist.GetNext(m_position));

// 	if (m_position == m_strWordlist.GetTailPosition())
// 	{
// 		KillTimer(m_nTimer);
// 		m_nfile = 0;
// 		m_progress.SetPos(m_strWordlist.GetCount());
// 		m_btnRun.SetWindowTextW(_T("�����"));
// 		m_editWord.SetWindowTextW(m_strMyWord);
// 		AfxMessageBox(_T("��"));
// 		m_progress.SetPos(0);
// 	}
}

void CAwordnoiserDlg::OnBnClickedButton_Run()
{
	if (m_ckWordset.GetCheck() == TRUE)
	{

	}
	else
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

			CString strFilter = _T("");
			m_editFilter.GetWindowTextW(strFilter);

			if (RunWordnoiser(strWord, m_strWordlist, _ttoi(strFilter)) == TRUE)
			{
				if (m_strWordlist.IsEmpty() == TRUE)
				{
					AfxMessageBox(_T("wordlist is empty"));
				}
				else
				{
					m_progress.SetRange(0, m_strWordlist.GetCount());
					m_progress.SetPos(0);

					m_position = m_strWordlist.GetHeadPosition();
					m_nTimer = SetTimer(1, 100, 0);

					CString strMsg = _T("");
					strMsg.Format(_T("%d"), m_strWordlist.GetCount() - 1);
					m_stCount.SetWindowTextW(strMsg);

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
			m_editWord.SetWindowTextW(m_strMyWord);
			if (m_nTimer)
			{
				KillTimer(m_nTimer);
			}
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
		SetEditcontrolText();
		CaptureEditcontrol();	
		SetDlgControlIndex();

		if (m_position == m_strWordlist.GetTailPosition())
		{
			KillTimer(m_nTimer);
			ClearContorl();
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CAwordnoiserDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default
	int nFile = 0; 
	TCHAR szPathname[MAX_PATH] = { 0, };
	CString strFilename = _T("");

	nFile = ::DragQueryFile(hDropInfo, 0xFFFFFFFF, szPathname, MAX_PATH);

	if (nFile > 1)
	{
		AfxMessageBox(_T("���� ���� �ʰ�"));
	}
	else
	{
		::DragQueryFile(hDropInfo, 0, szPathname, MAX_PATH);
		TCHAR* szFilename = _tcsrchr(szPathname, _T('\\')) + 1;
		strFilename = szFilename;
		if (strFilename.CompareNoCase(_T("wordset.csv")) == 0)
		{
			m_stWordsetPath.SetWindowTextW(szPathname);
		}
		else
		{
			AfxMessageBox(_T("���� ����"));
		}
	}

	::DragFinish(hDropInfo);

	CDialogEx::OnDropFiles(hDropInfo);
}
