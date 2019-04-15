
// AwordnoiserDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Awordnoiser.h"
#include "AwordnoiserDlg.h"
#include "afxdialogex.h"

//#include "noise.h"
#include "RandomNoise.h"

#define	MIN_FILE_COUNT		10000

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
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_BUTTON1, m_btnRun);
	DDX_Control(pDX, IDC_ST_COUNT, m_stCount);
	DDX_Control(pDX, IDC_ST_INDEX, m_stIndex);
	DDX_Control(pDX, IDC_ST_WORDSET_PATH, m_stSentencePath);
	DDX_Control(pDX, IDC_ST_WORDSET_PATH0, m_stWordPath);
}

BEGIN_MESSAGE_MAP(CAwordnoiserDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAwordnoiserDlg::OnBnClickedButton_Run)
	ON_BN_CLICKED(IDC_BUTTON2, &CAwordnoiserDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAwordnoiserDlg::OnBnClickedButton3)
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

void CAwordnoiserDlg::CaptureEditcontrol(CString strPath, CString strFolder, int nWidth /*= NUM_SIZE_WIDTH*/, int nHeight /*= NUM_SIZE_HEIGHT*/)
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

	if (m_nfile % 5 == 3)
	{
		strFilename.Format(_T("%s\\%s_%d.jpg"), m_strTestPath, strFolder, m_nfile);
	}
	else if (m_nfile % 5 == 4)
	{
		strFilename.Format(_T("%s\\%s_%d.jpg"), m_strValidationPath, strFolder, m_nfile);
	}
	else
	{
		strFilename.Format(_T("%s\\%s_%d.jpg"), m_strTrainPath, strFolder, m_nfile);
	}
	
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
}


void CAwordnoiserDlg::CaptureEditcontrol_Sentence(CString strPath, CString strName /*= _T("sentence")*/, int nWidth /*= NUM_SIZE_WIDTH*/, int nHeight /*= NUM_SIZE_HEIGHT*/)
{
	CWnd*  myWnd = this->GetDlgItem(IDC_EDIT3);
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

	strFilename.Format(_T("%s\\sentence_%d.jpg"), strPath, m_nCntSentence);

	int length = strFilename.GetLength();
	char* st = new char[length];
	strcpy(st, (CT2A)strFilename);

	FILE *p_file = fopen(st, "wb");
	if (p_file != NULL) {
		fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
		fwrite(&dib_define, 1, sizeof(BITMAPINFOHEADER), p_file);
		fwrite(p_image_data, 1, dib_define.bmiHeader.biSizeImage, p_file);
		fclose(p_file);
		++m_nCntSentence;
	}

	// ����ߴ� ��Ʈ�ʰ� DC �� �����Ѵ�.
	if (NULL != h_bitmap) DeleteObject(h_bitmap);
	if (NULL != h_screen_dc) ::ReleaseDC(NULL, h_screen_dc);
}

CString CAwordnoiserDlg::GetWord(CString strMsg)
{
	CString strResult = _T("");
	int nPos = strMsg.Find(_T("-"), 0);
	strResult = strMsg.Mid(0, nPos);

	return strResult;
}

BOOL CAwordnoiserDlg::ReadWordsetfile(CStringList& strlWordset, CString strPath)
{
	BOOL bResult = FALSE; 

	if (_taccess(strPath, 0) == -1)
	{
		return FALSE; 
	}

	strlWordset.RemoveAll();

	CStdioFile file;
	CFileException exception;
	CString line;

	if (!file.Open(strPath, CFile::modeRead | CFile::shareDenyNone))
	{
		return FALSE;
	}
	else
	{
		try
		{
			while (true)
			{
				if (!file.ReadString(line))
				{
					break;
				}
				else
				{
					bResult = TRUE; 
					strlWordset.AddTail(GetWord(line));
				}
			}
		}
		catch (CFileException *e)
		{
			CString strMsg = _T("");
			strMsg.Format(_T("get last error code : %d"), GetLastError());
			AfxMessageBox(strMsg);
		}
	}

	file.Close();

	return bResult; 
}

BOOL CAwordnoiserDlg::RunWordnoiser(CString strWord, CStringList& strWordlist, int nFilter /*= 10*/)
{
	BOOL bResult = FALSE; 

	if (strWord.IsEmpty() == TRUE)
	{
		return FALSE;
	}

	strWordlist.RemoveAll();

	//CNoise Noiser(strWord, nFilter, m_ckop1.GetCheck(), m_ckop2.GetCheck(), m_ckop3.GetCheck(), m_ckop4.GetCheck(), m_ckop5.GetCheck());
	//Noiser.GetWordList(strWordlist);

	CRandomNoise Noiser;
	Noiser.GetWordList(strWord, m_strWordlist);

	if (strWordlist.IsEmpty() == FALSE)
	{
		m_strMyWord = strWord; 
		bResult = TRUE;
	}

	return bResult; 
}

void CAwordnoiserDlg::ClearContorl()
{	
	m_progress.SetPos(m_strWordlist.GetCount());

	m_btnRun.SetWindowTextW(_T("�����"));
	m_editWord.SetWindowTextW(m_strMyWord);
	m_progress.SetPos(0);
	//m_stIndex.SetWindowTextW(_T(""));
	//m_stCount.SetWindowTextW(_T(""));
}

void CAwordnoiserDlg::SetDlgControlIndex()
{
	m_progress.SetPos(m_nfile);

	CString strMsg = _T("");
	strMsg.Format(_T("%d/"), m_nfile);
	m_stIndex.SetWindowTextW(strMsg);

}

void CAwordnoiserDlg::SetEditcontrolText(CString strText)
{
	m_editWord.SetWindowText(_T(""));
	m_editWord.SetWindowText(strText);
}

BOOL CAwordnoiserDlg::MakeDataDirectory(CString strMyPath, CString strType, CString strWord)
{
	if ((strMyPath.IsEmpty() == TRUE) || (strType.IsEmpty() == TRUE) || (strWord.IsEmpty() ==TRUE))
	{
		return FALSE;
	}

	BOOL bResult = TRUE;
	CString strMsg = _T("");

	if (_taccess(strMyPath, 0) == -1)
	{
		if (CreateDirectory(strMyPath, NULL) == FALSE)
		{
			strMsg.Format(_T("CreateDirectory fail, dir:%s"), strMyPath);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}

	CString strPath = _T("");
	strPath.Format(_T("%s\\%s"), strMyPath, strType);

	if (_taccess(strPath, 0) == -1)
	{
		if (CreateDirectory(strPath, NULL) == FALSE)
		{
			strMsg.Format(_T("CreateDirectory fail, dir:%s"), strPath);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}

	strPath.Format(_T("%s\\%s\\%s"), strMyPath, strType, strWord);
	if (_taccess(strPath, 0) == -1)
	{
		if (CreateDirectory(strPath, NULL) == FALSE)
		{
			strMsg.Format(_T("CreateDirectory fail, dir:%s"), strPath);
			AfxMessageBox(strMsg);
			return FALSE;
		}
	}

	return bResult; 	
}

BOOL CAwordnoiserDlg::CheckDirectory(CString strPath, CString strWord)
{
	BOOL bResult = TRUE; 

	if (MakeDataDirectory(strPath, _T("train"), strWord) == TRUE)
	{
		CString strFolderPath = _T("");
		strFolderPath.Format(_T("%s\\train\\%s"), strPath, strWord);
		m_strTrainPath = strFolderPath;
	}
	else
	{
		bResult = FALSE; 
	}

	if (MakeDataDirectory(strPath, _T("test"), strWord) == TRUE)
	{
		CString strFolderPath = _T("");
		strFolderPath.Format(_T("%s\\test\\%s"), strPath, strWord);
		m_strTestPath = strFolderPath;
	}
	else
	{
		bResult = FALSE;
	}

	if (MakeDataDirectory(strPath, _T("validation"), strWord) == TRUE)
	{
		CString strFolderPath = _T("");
		strFolderPath.Format(_T("%s\\validation\\%s"), strPath, strWord);
		m_strValidationPath = strFolderPath;
	}	
	else
	{
		bResult = FALSE;
	}
	
	return bResult; 
}

void CAwordnoiserDlg::OnBnClickedButton_Run()
{
	if (m_bDoing == FALSE)
	{
		CString		strWord = _T("");
		//CString		strwordDir = _T("");

		m_editWord.GetWindowTextW(strWord);
		if (strWord.IsEmpty() == TRUE)
		{
			AfxMessageBox(_T("IsEmpty error"));
			return;
		}
		
		if (CheckDirectory(m_strMyDirectory, strWord) == FALSE)
		{
			AfxMessageBox(_T("CheckDirectory error"));
			return;
		}

		if (RunWordnoiser(strWord, m_strWordlist) == TRUE)
		{
			if (m_strWordlist.IsEmpty() == TRUE)
			{
				AfxMessageBox(_T("wordlist is empty"));
			}
			else
			{
				m_progress.SetRange(0, MIN_FILE_COUNT);
				m_progress.SetPos(0);

				m_posWord = m_strWordlist.GetHeadPosition();
				m_nTimerWord = SetTimer(1, 100, 0);

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
		if (m_nTimerWord)
		{
			KillTimer(m_nTimerWord);
		}
	}
}

void CAwordnoiserDlg::OnBnClickedButton2()
{
	CString strFile = _T("");
	m_stWordPath.GetWindowTextW(strFile);

	if (strFile.IsEmpty() == TRUE)
	{
		AfxMessageBox(_T("NO FILE"));
	}
	else
	{
		// �����б�,
		// �ܾ� ����Ʈ �����.
	}
}

void CAwordnoiserDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{		
		KillTimer(m_nTimerWord);
		SetEditcontrolText(m_strWordlist.GetNext(m_posWord));
		SaveTextFile();
		CaptureEditcontrol(m_strMyDirectory, m_strMyWord);	
		SetDlgControlIndex();
				
		if ((m_strWordlist.IsEmpty() == TRUE)||(m_posWord == m_strWordlist.GetTailPosition()))
		{
			m_nTimerWord = NULL;
			ClearContorl();

			if (m_nfile < MIN_FILE_COUNT)
			{
				m_strWordlist.RemoveAll();
				RunWordnoiser(m_strMyWord, m_strWordlist);
				m_posWord = m_strWordlist.GetHeadPosition();
				m_nTimerWord = SetTimer(1, 100, 0);
			}
		}
		else
		{
			m_nTimerWord = SetTimer(1, 100, 0);
		}
	}
	else if (nIDEvent == 2)
	{
		SetEditcontrolText(m_strBowlist.GetNext(m_posBowset));
		CaptureEditcontrol(m_strMyDirectory, STR_WORDSET_FOLDER);

		if ((m_strBowlist.IsEmpty() == TRUE) || (m_posBowset == m_strBowlist.GetTailPosition()))
		{
			KillTimer(m_nTimerBow);
			m_nTimerBow = NULL;
			m_strTextPath = _T("");
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
		if (strFilename.CompareNoCase(STR_WORDSET_FILENAME) == 0)
		{
			m_stSentencePath.SetWindowTextW(szPathname);
		}
		else
		{
			AfxMessageBox(_T("���� ����"));
		}
	}

	::DragFinish(hDropInfo);

	CDialogEx::OnDropFiles(hDropInfo);
}

void CAwordnoiserDlg::SaveTextFile()
{
	CString strText = _T("");
	CString strText2 = _T("");
	m_editWord.GetWindowTextW(strText);

	strText2.Format(_T("%s\r\n"), strText);
	
	if (m_strTextPath.IsEmpty() == TRUE)
	{
		m_strTextPath.Format(_T("%s//%s.txt"), m_strMyDirectory, m_strMyWord);
	}

	CFile  pf;
	
	if (pf.Open(m_strTextPath, CFile::modeReadWrite | CFile::shareDenyNone) == FALSE)
	{
		if (pf.Open(m_strTextPath, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyNone) == FALSE)
		{
			return;
		}
		else
		{
			USHORT nShort = 0xfeff;
			pf.Write(&nShort, sizeof(USHORT));
		}
	}
	pf.SeekToEnd();

	int nSize = _tcslen(strText2) * sizeof(TCHAR);
	pf.Write(strText2, nSize);
	
	pf.Close();
}

void CAwordnoiserDlg::LoadBadwords(CStringList strBadList)
{
	CString strPath = _T("");
	strPath.Format(_T("%s//bad-words.csv"), m_strMyDirectory);

	CFile  pf;
	if (pf.Open(m_strTextPath, CFile::modeReadWrite | CFile::shareDenyNone) == FALSE)
	{

	}
}

void CAwordnoiserDlg::OnBnClickedButton3()
{
	CString strFile = _T("");
	m_stSentencePath.GetWindowTextW(strFile);

	if (strFile.IsEmpty() == TRUE)
	{
		CaptureEditcontrol_Sentence(m_strMyDirectory, _T("sentence"));
	}
	else
	{
		
	}

	// �޸��忡�� ���� ������ ����Ʈ�� �ֱ�. 
	// ���� ĸó �� ����, �׸���
	// ����縦 ������ �弳�� ��ü
	// ���� ���� ĸó �� ����. 
}
