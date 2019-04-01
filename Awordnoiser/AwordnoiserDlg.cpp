
// AwordnoiserDlg.cpp : 구현 파일
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

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CAwordnoiserDlg 대화 상자



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


// CAwordnoiserDlg 메시지 처리기

BOOL CAwordnoiserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_ckop1.SetCheck(TRUE);
	m_ckop3.SetCheck(TRUE);
	m_ckop4.SetCheck(TRUE);
	m_ckop5.SetCheck(TRUE);

	m_editFilter.SetWindowTextW(_T("20"));

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
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAwordnoiserDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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

	// DIB형식 정의
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

	// DIB의 내부 이미지 비트 패턴을 참조할 포인터 변수
	BYTE *p_image_data = NULL;

	// dib_define에 정의된 내용으로 DIB생성
	HBITMAP h_bitmap = ::CreateDIBSection(h_screen_dc, &dib_define, DIB_RGB_COLORS, (void **)&p_image_data, 0, 0);

	// 캡쳐한 이미지 추출을 위한 가상 dc생성
	HDC h_memory_dc = ::CreateCompatibleDC(h_screen_dc);

	// 가상 DC에 이미지를 추출할 비트맵 연결
	HBITMAP h_old_bitmap = (HBITMAP)::SelectObject(h_memory_dc, h_bitmap);

	// 화면을 캡쳐
	::BitBlt(h_memory_dc, 0, 0, nWidth, nHeight, h_screen_dc, 0, 0, SRCCOPY);

	// 본래의 비트맵으로 복구
	::SelectObject(h_memory_dc, h_old_bitmap);

	// 가상 DC를 제거
	DeleteDC(h_memory_dc);

	// DIB 파일의 헤더 내용 구성
	BITMAPFILEHEADER dib_format_layout;
	ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
	dib_format_layout.bfType = *(WORD*)"BM";
	dib_format_layout.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dib_define.bmiHeader.biSizeImage;
	dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	// 이미지 파일 생성
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

	// 사용했던 비트맵과 DC 를 해제한다.
	if (NULL != h_bitmap) DeleteObject(h_bitmap);
	if (NULL != h_screen_dc) ::ReleaseDC(NULL, h_screen_dc);

// 	CWnd*  myWnd = this->GetDlgItem(IDC_EDIT1);
// 	CDC memDC;
// 	CBitmap bitmap;
// 
// 	CClientDC dc(this);      // dc선언해주고 (this)에 화면을 출력하기 위해선언
// 	CClientDC ScreenDC(myWnd);   // 스크린DC 선언
// 
// 	memDC.CreateCompatibleDC(&ScreenDC);   // 스크린DC와 호환되는 DC생성
// 	bitmap.CreateCompatibleBitmap(&ScreenDC, NUM_SIZE_WIDTH, NUM_SIZE_HEIGHT);   // 스크린DC와 호환되는 비트맵 생성
// 	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);   // Bitmap 포인터를 넘겨줌
// 	memDC.StretchBlt(0, 0, NUM_SIZE_WIDTH, NUM_SIZE_HEIGHT, &ScreenDC, 0, 0, NUM_SIZE_WIDTH, NUM_SIZE_HEIGHT, SRCCOPY);   // 스크린DC에 저장된화면을 memDC에 copy, bitmap에도 기록됨
// 																														  // 출력
// 	dc.BitBlt(0, 0, NUM_SIZE_WIDTH, NUM_SIZE_HEIGHT, &memDC, 0, 0, SRCCOPY);   // 0,0 부터 해상도크기까지 memDC가 가리키는 참조값 0, 0부터 복사해서 출력함
// 
// 	memDC.SelectObject(pOldBitmap);
// 	DeleteDC(memDC);
// 
// 
// 	// DIB의 형식을 정의한다.
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
// 	// DIB 파일의 헤더 내용을 구성한다.
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

	AfxMessageBox(_T("끝"));
	m_btnRun.SetWindowTextW(_T("만들기"));
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

void CAwordnoiserDlg::SetEditcontrolText(CString strText)
{
	m_editWord.SetWindowText(_T(""));
	m_editWord.SetWindowText(strText);
}

void CAwordnoiserDlg::CheckDirectory(CString strPath, CString strFolder)
{
	CString		strwordDir = _T("");

	strwordDir.Format(_T("%s\\%s"), strPath, strFolder);
	if (_taccess(strwordDir, 0) == ISNOTNORMAL)
	{
		CString strMsg = _T("");

		if (CreateDirectory(strwordDir, NULL) == FALSE)
		{
			strMsg.Format(_T("CreateDirectory fail, wordDir:%s"), strwordDir);
			AfxMessageBox(strMsg);
			return;
		}
	}

	CString strTrain = _T("");
	CString strTest = _T("");
	CString strValidation = _T("");

	strTrain.Format(_T("%s\\train"), strwordDir);
	strTest.Format(_T("%s\\test"), strwordDir);
	strValidation.Format(_T("%s\\validation"), strwordDir);

	if (_taccess(strTrain, 0) == -1)
	{
		if (CreateDirectory(strTrain, NULL) == FALSE)
		{
			CString strMsg = _T("");
			strMsg.Format(_T("CreateDirectory(strTrain) fail, wordDir:%s"), strTrain);
			AfxMessageBox(strMsg);
		}
		else
		{
			m_strTrainPath = strTrain;
		}
	}
	else
	{
		m_strTrainPath = strTrain;
	}

	if (_taccess(strTest, 0) == -1)
	{
		if (CreateDirectory(strTest, NULL) == FALSE)
		{
			CString strMsg = _T("");
			strMsg.Format(_T("CreateDirectory(strTest) fail, wordDir:%s"), strTest);
			AfxMessageBox(strMsg);
		}
		else
		{
			m_strTestPath = strTest;
		}
	}
	else
	{
		m_strTestPath = strTest;
	}

	if (_taccess(strValidation, 0) == -1)
	{
		if (CreateDirectory(strValidation, NULL) == FALSE)
		{
			CString strMsg = _T("");
			strMsg.Format(_T("CreateDirectory(strValidation) fail, wordDir:%s"), strValidation);
			AfxMessageBox(strMsg);
		}
		else
		{
			m_strValidationPath = strValidation;
		}
	}
	else
	{
		m_strValidationPath = strValidation;
	}
}

void CAwordnoiserDlg::OnBnClickedButton_Run()
{
	if (m_ckWordset.GetCheck() == TRUE)
	{
		CString strPath = _T("");
		m_stWordsetPath.GetWindowTextW(strPath);
		
		if (ReadWordsetfile(m_strBowlist, strPath) == TRUE)
		{
			if (m_strBowlist.IsEmpty() == FALSE)
			{
				m_posBowset = m_strBowlist.GetHeadPosition();
				if (m_nTimerBow == NULL)
				{
					CheckDirectory(m_strMyDirectory, STR_WORDSET_FOLDER);
					m_nTimerBow = SetTimer(2, 200, NULL);
				}
			}						
		}
		else
		{
			AfxMessageBox(_T("ReadWordsetfile failed"));
		}
	}
	else
	{
		if (m_bDoing == FALSE)
		{
			CString		strWord = _T("");
			//CString		strwordDir = _T("");

			m_editWord.GetWindowTextW(strWord);
			if (strWord.IsEmpty() == TRUE)
			{
				AfxMessageBox(_T("...?"));
				return;
			}

			CheckDirectory(m_strMyDirectory, strWord);
// 			strwordDir.Format(_T("%s\\%s"), m_strMyDirectory, strWord);
// 			if (_taccess(strwordDir, 0) == ISNOTNORMAL)
// 			{
// 				if (CreateDirectory(strwordDir, NULL) == FALSE)
// 				{
// 					CString strMsg = _T("");
// 					strMsg.Format(_T("CreateDirectory fail, wordDir:%s"), strwordDir);
// 					AfxMessageBox(strMsg);
// 				}
// 			}

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

					m_posWord = m_strWordlist.GetHeadPosition();
					m_nTimerWord = SetTimer(1, 100, 0);

					CString strMsg = _T("");
					strMsg.Format(_T("%d"), m_strWordlist.GetCount() - 1);
					m_stCount.SetWindowTextW(strMsg);

					m_bDoing = TRUE;
					m_btnRun.SetWindowTextW(_T("중지"));
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
			m_btnRun.SetWindowTextW(_T("만들기"));
			m_editWord.SetWindowTextW(m_strMyWord);
			if (m_nTimerWord)
			{
				KillTimer(m_nTimerWord);
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
		strMsg.Format(_T("예상 단어 수:%d"), m_strWordlist.GetCount());
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
		SetEditcontrolText(m_strWordlist.GetNext(m_posWord));
		SaveTextFile();
		CaptureEditcontrol(m_strMyDirectory, m_strMyWord);	
		SetDlgControlIndex();

		if ((m_strWordlist.IsEmpty() == TRUE)||(m_posWord == m_strWordlist.GetTailPosition()))
		{
			KillTimer(m_nTimerWord);
			m_nTimerWord = NULL;
			ClearContorl();
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
		AfxMessageBox(_T("파일 개수 초과"));
	}
	else
	{
		::DragQueryFile(hDropInfo, 0, szPathname, MAX_PATH);
		TCHAR* szFilename = _tcsrchr(szPathname, _T('\\')) + 1;
		strFilename = szFilename;
		if (strFilename.CompareNoCase(STR_WORDSET_FILENAME) == 0)
		{
			m_stWordsetPath.SetWindowTextW(szPathname);
			m_ckWordset.ShowWindow(TRUE);
		}
		else
		{
			AfxMessageBox(_T("형식 오류"));
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