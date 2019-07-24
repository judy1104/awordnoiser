
// AwordnoiserDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Awordnoiser.h"
#include "AwordnoiserDlg.h"
#include "afxdialogex.h"

#include "RandomNoise.h"
#include "NoiseKor.h"

#define	MIN_FILE_COUNT		10000

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
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Control(pDX, IDC_BUTTON1, m_btnRun);
	DDX_Control(pDX, IDC_ST_INDEX, m_stIndex);
	DDX_Control(pDX, IDC_ST_WORDSET_PATH, m_stSentencePath);
	DDX_Control(pDX, IDC_ST_WORDSET_PATH0, m_stWordPath);
	DDX_Control(pDX, IDC_EDIT2, m_editWord2);
	DDX_Control(pDX, IDC_PROGRESS2, m_progress2);
	DDX_Control(pDX, IDC_PROGRESS3, m_progress3);
	DDX_Control(pDX, IDC_BUTTON2, m_btnRun2);
	DDX_Control(pDX, IDC_ST_INDEX2, m_stIndex2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_CHECK_LANG, m_checkLng);
	DDX_Control(pDX, IDC_STATIC_WORDS, m_stWordsPath);
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
	ON_MESSAGE(WM_MSG_WORDLIST, OnMakeBadWords)
	
	ON_BN_CLICKED(IDC_BUTTON4, &CAwordnoiserDlg::OnBnClickedButton4)
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


void CAwordnoiserDlg::CaptureEditcontrol(int nEditId, CString strPath, CString strFolder, int nWidth /*= NUM_SIZE_WIDTH*/, int nHeight /*= NUM_SIZE_HEIGHT*/)
{
	if (m_checkLng.GetCheck() == TRUE)
	{
		nHeight = 40;
	}
	
	CWnd*  myWnd = this->GetDlgItem(nEditId);
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
	CString strOcrFilename = _T("");

	if (m_nfile < m_nOldCount + 40)
	{
		strOcrFilename.Format(_T("%s\\%s_%d.bmp"), m_strOCRPath, strFolder, m_nfile);

		CFile file;
		if (file.Open(strOcrFilename, CFile::modeCreate | CFile::modeWrite) == TRUE)
		{
			file.Write(&dib_format_layout, sizeof(BITMAPFILEHEADER));
			file.Write(&dib_define, sizeof(BITMAPINFOHEADER));
			file.Write(p_image_data, dib_define.bmiHeader.biSizeImage);
			file.Close();
		}
	}

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
	
	int a = strFilename.GetAllocLength();
	int length = strFilename.GetLength();
	char szTest[MAX_PATH] = { 0, };
	strcpy(szTest, CT2A(strFilename));
	CFile file;
	if (file.Open(strFilename, CFile::modeCreate | CFile::modeWrite) == TRUE)
	{
		file.Write(&dib_format_layout, sizeof(BITMAPFILEHEADER));
		file.Write(&dib_define, sizeof(BITMAPINFOHEADER));
		file.Write(p_image_data, dib_define.bmiHeader.biSizeImage);
		file.Close();
		++m_nfile;
	}
	
	// 사용했던 비트맵과 DC 를 해제한다.
	if (NULL != h_bitmap) DeleteObject(h_bitmap);
	if (NULL != h_screen_dc) ::ReleaseDC(NULL, h_screen_dc);
}

void CAwordnoiserDlg::CaptureEditcontrol_Sentence(CString strPath, CString strName /*= _T("sentence")*/, int nWidth /*= NUM_SIZE_WIDTH*/, int nHeight /*= NUM_SIZE_HEIGHT*/)
{
	CWnd*  myWnd = this->GetDlgItem(IDC_EDIT3);
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

	// 사용했던 비트맵과 DC 를 해제한다.
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

	if (m_checkLng.GetCheck() == TRUE)
	{
		CNoiseKor KorNoiser;
		KorNoiser.GetWordList(strWord, m_strWordlist);
	}
	else
	{
		CRandomNoise Noiser;
		Noiser.GetWordList(strWord, m_strWordlist);	
	}

	if (strWordlist.IsEmpty() == FALSE)
	{
		m_strMyWord = strWord;
		bResult = TRUE;
	}

	return bResult; 
}

void CAwordnoiserDlg::ClearContorl(CEdit& editId, CButton& btnId, CProgressCtrl& progressId)
{	
	m_bDoing = FALSE;
	progressId.SetPos(m_strWordlist.GetCount());

	btnId.SetWindowTextW(_T("만들기"));
	editId.SetWindowTextW(m_strMyWord);
	progressId.SetPos(0);
}

void CAwordnoiserDlg::SetDlgControlIndex(CProgressCtrl& progress, CStatic& stCount)
{
	progress.SetPos(m_nfile);

	CString strMsg = _T("");
	strMsg.Format(_T("%d/"), m_nfile);
	stCount.SetWindowTextW(strMsg);

}

void CAwordnoiserDlg::SetEditcontrolText(CEdit& eidtId, CString strText)
{
	eidtId.SetWindowText(_T(""));
	eidtId.SetWindowText(strText);
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

BOOL CAwordnoiserDlg::CheckDirectory(CString strPath, CString strType, CString strWord, CString& strFullPath)
{
	BOOL bResult = TRUE; 

	if (MakeDataDirectory(strPath, strType, strWord) == TRUE)
	{
		CString strFolderPath = _T("");
		strFolderPath.Format(_T("%s\\%s\\%s"), strPath, strType, strWord);
		strFullPath = strFolderPath;
	}
	else
	{
		bResult = FALSE; 
	}

	return bResult; 
}

int CAwordnoiserDlg::GetFindCharCount(CString parm_string, char parm_find_char)
{
	// 함수 출처 : https://m.blog.naver.com/PostView.nhn?blogId=yagyu82&logNo=95519861&proxyReferer=https%3A%2F%2Fwww.google.com%2F
	int length = parm_string.GetLength(), find_count = 0;

	for (int i = 0; i < length; i++)
	{
		if (parm_string[i] == parm_find_char)
		{
			find_count++;
		}
	}

	return find_count;
}

BOOL CAwordnoiserDlg::CreateNoiseWord(CEdit& editId, CButton& btnId, CProgressCtrl& progressId, int nTimerId, int nTimerPtr)
{
	BOOL		bResult = TRUE;
	CString		strWord = _T("");
	editId.GetWindowTextW(strWord);

	if (strWord.IsEmpty() == TRUE)
	{
		AfxMessageBox(_T("IsEmpty error"));
		return FALSE;
	}

	if (CheckDirectory(m_strMyDirectory, _T("train"), strWord, m_strTrainPath) == FALSE)
	{
		AfxMessageBox(_T("CheckDirectory train error"));
		return FALSE;
	}

	if (CheckDirectory(m_strMyDirectory, _T("test"), strWord, m_strTestPath) == FALSE)
	{
		AfxMessageBox(_T("CheckDirectory test error"));
		return FALSE;
	}

	if (CheckDirectory(m_strMyDirectory, _T("validation"), strWord, m_strValidationPath) == FALSE)
	{
		AfxMessageBox(_T("CheckDirectory validation error"));
		return FALSE;
	}

	if (CheckDirectory(m_strMyDirectory, _T("ocr"), strWord, m_strOCRPath) == FALSE)
	{
		AfxMessageBox(_T("CheckDirectory ocr error"));
		return FALSE;
	}

	if (RunWordnoiser(strWord, m_strWordlist) == TRUE)
	{
		if (m_strWordlist.IsEmpty() == TRUE)
		{
			AfxMessageBox(_T("wordlist is empty"));
			return FALSE;
		}
		else
		{
			progressId.SetRange(0, MIN_FILE_COUNT);
			progressId.SetPos(0);

			m_posWord = m_strWordlist.GetHeadPosition();
			nTimerPtr = SetTimer(nTimerId, 100, 0);

			m_bDoing = TRUE;
			btnId.SetWindowTextW(_T("중지"));
		}
	}
	else
	{
		AfxMessageBox(_T("RunWordnoiser failed"));
		return FALSE;
	}
}

void CAwordnoiserDlg::OnBnClickedButton_Run()
{
	if (m_bDoing == FALSE)
	{
		CreateNoiseWord(m_editWord, m_btnRun, m_progress, 1, m_nTimerWord);
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
		if (_taccess(strFile, 0) == -1)
		{
			AfxMessageBox(_T("NO ACCESS"));
		}
		else
		{
			CFile cfile;
			if (cfile.Open(strFile, CFile::modeRead | CFile::shareDenyNone) == TRUE)
			{
				char pbufRead[1024] = {0, };
				cfile.Read(pbufRead, sizeof(pbufRead));

				CString strReadMsg = _T("");
				strReadMsg = pbufRead;

				int nCntWord = GetFindCharCount(strReadMsg, '|');
				
				for (int i = 0; i <= nCntWord; ++i)
				{
					CString strText = _T("");
					AfxExtractSubString(strText, strReadMsg, i, '|');
					m_strBigWordlist.AddTail(strText);
				}
			}			
		}
	}

	if (m_strBigWordlist.IsEmpty() == FALSE)
	{
		m_posBigWord = m_strBigWordlist.GetHeadPosition();
		PostMessage(WM_MSG_WORDLIST, NULL, NULL);
	}
}

LRESULT CAwordnoiserDlg::OnMakeBadWords(WPARAM wParm, LPARAM lParm)
{
	CString	strWord = _T("");
	
	strWord = m_strBigWordlist.GetNext(m_posBigWord);

	m_editWord2.SetWindowTextW(strWord);
	CreateNoiseWord(m_editWord2, m_btnRun2, m_progress2, 2, m_nTimerWord2);

	return 0; 
}

void CAwordnoiserDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{		
		KillTimer(m_nTimerWord);
		SetEditcontrolText(m_editWord, m_strWordlist.GetNext(m_posWord));
		SaveTextFile(m_editWord, m_strMyWord);
		CaptureEditcontrol(IDC_EDIT1, m_strMyDirectory, m_strMyWord);
		SetDlgControlIndex(m_progress, m_stIndex);
				
		if ((m_strWordlist.IsEmpty() == TRUE)||(m_posWord == m_strWordlist.GetTailPosition()))
		{
			m_nTimerWord = NULL;
			m_nOldCount = 0;
			ClearContorl(m_editWord, m_btnRun, m_progress);

			if (m_nfile < MIN_FILE_COUNT)
			{
				m_nOldCount = m_nfile;
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
		KillTimer(m_nTimerWord2);
		SetEditcontrolText(m_editWord2, m_strWordlist.GetNext(m_posWord));
		SaveTextFile(m_editWord2, m_strMyWord);
		CaptureEditcontrol(IDC_EDIT2, m_strMyDirectory, m_strMyWord);
		SetDlgControlIndex(m_progress2, m_stIndex2);

		if ((m_strWordlist.IsEmpty() == TRUE) || (m_posWord == m_strWordlist.GetTailPosition()))
		{
			m_nTimerWord2 = NULL;
			m_nOldCount = 0;
			ClearContorl(m_editWord2, m_btnRun2, m_progress2);

			if (m_checkLng.GetCheck() == TRUE)
			{
				if (m_nfile < MIN_FILE_COUNT)
				{
					m_nOldCount = m_nfile;
					m_strWordlist.RemoveAll();
					RunWordnoiser(m_strMyWord, m_strWordlist);
					m_posWord = m_strWordlist.GetHeadPosition();
					m_nTimerWord2 = SetTimer(2, 100, 0);
				}
				else
				{
					if (m_posBigWord != NULL)
					{
						m_nfile = 0;
						PostMessage(WM_MSG_WORDLIST, NULL, NULL);
					}
				}
			}
			else
			{
				if (m_nfile < MIN_FILE_COUNT)
				{
					m_nOldCount = m_nfile;
					m_strWordlist.RemoveAll();
					RunWordnoiser(m_strMyWord, m_strWordlist);
					m_posWord = m_strWordlist.GetHeadPosition();
					m_nTimerWord2 = SetTimer(2, 100, 0);
				}
				else
				{
					if (m_posBigWord != NULL)
					{
						m_nfile = 0;
						PostMessage(WM_MSG_WORDLIST, NULL, NULL);
					}
				}
			}			
		}
		else
		{
			m_nTimerWord2 = SetTimer(2, 100, 0);
		}
	}
	else if (nIDEvent == 3)
	{
		KillTimer(m_nTimerSentence);		
		CaptureEditcontrol_Sentence(m_strDirSentence);
		
		if (m_posSentence != m_strlSentence.GetTailPosition())
		{
			CString strText = m_strlSentence.GetNext(m_posSentence);
			SetEditcontrolText(m_edit3, strText);
			m_nTimerSentence = SetTimer(3, 100, 0);
		}
	}
	else if (nIDEvent == 4)
	{
		KillTimer(m_nTimerWord4);
		SetEditcontrolText(m_editWord2, m_strlnormal.GetNext(m_posWord4));
		CaptureEditcontrol(IDC_EDIT2, m_strMyDirectory, m_strMyWord);

		if (m_posWord4 == m_strlnormal.GetTailPosition())
		{
			// 종료
		}
		else
		{
			SetTimer(4, 100, 0);
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
		if (strFilename.CompareNoCase(STR_SENTENCE_FILE) == 0)
		{
			m_stSentencePath.SetWindowTextW(szPathname);
		}
		else if (
			(strFilename.CompareNoCase(STR_WORD_FILE) == 0) || 
			(strFilename.CompareNoCase(STR_WORD_FILE_KOR) == 0) || 
			(strFilename.CompareNoCase(_T("test.txt")) == 0))
		{
			m_stWordPath.SetWindowTextW(szPathname);

			if (strFilename.CompareNoCase(STR_WORD_FILE_KOR) == 0)
			{
				m_checkLng.SetCheck(TRUE);
			}
		}
		else if (
			(strFilename.CompareNoCase(STR_WORD_KOR) == 0) || 
			(strFilename.CompareNoCase(STR_WORD_ENG) == 0))
		{
			m_stWordsPath.SetWindowTextW(szPathname);
		}
		else
		{
			AfxMessageBox(_T("형식 오류"));
		}
	}

	::DragFinish(hDropInfo);

	CDialogEx::OnDropFiles(hDropInfo);
}

void CAwordnoiserDlg::SaveTextFile(CEdit& editId, CString strWord)
{
	CString strText = _T("");
	CString strText2 = _T("");
	editId.GetWindowTextW(strText);

	strText2.Format(_T("%s\r\n"), strText);
	m_strTextPath.Format(_T("%s//%s.txt"), m_strMyDirectory, strWord);

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
		CFile cfile;
		if (cfile.Open(strFile, CFile::modeRead | CFile::shareDenyNone) == TRUE)
		{
			char pbufRead[1024] = { 0, };
			cfile.Read(pbufRead, sizeof(pbufRead));

			CString strReadMsg = _T("");
			strReadMsg = pbufRead;

			int nCntWord = GetFindCharCount(strReadMsg, '.');


			for (int i = 0; i <= nCntWord; ++i)
			{
				CString strText = _T("");
				AfxExtractSubString(strText, strReadMsg, i, '.');
				strText.Replace(_T("\r\n"), _T(""));
				strText.TrimLeft(_T(" "));
				m_strlSentence.AddTail(strText);
			}
			cfile.Close();
		}
	}

	if (m_strlSentence.IsEmpty() == FALSE)
	{

		if (CheckDirectory(m_strMyDirectory, _T("sentence"), _T("none"), m_strDirSentence) == FALSE)
		{
			AfxMessageBox(_T("CheckDirectory ocr error"));
		}

		m_posSentence = m_strlSentence.GetHeadPosition();
		SetEditcontrolText(m_edit3, m_strlSentence.GetNext(m_posSentence));
		m_nTimerSentence = SetTimer(3, 100, 0);
	}

	// 메모장에서 읽은 문장을 리스트에 넣기. 
	// 원본 캡처 후 저장, 그리고
	// 형용사를 변형된 욕설로 교체
	// 변형 문장 캡처 후 저장. 
}

void CAwordnoiserDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strFile = _T("");
	m_stWordsPath.GetWindowTextW(strFile);

	if (_taccess(strFile, 0) != -1)
	{
		if (strFile.Find(_T("kor")) != -1)
		{
			m_strMyWord = _T("korean12");
		}
		else if (strFile.Find(_T("eng")) != -1)
		{
			m_strMyWord = _T("english17");
		}

		if (CheckDirectory(m_strMyDirectory, _T("ocr"), m_strMyWord, m_strOCRPath) == FALSE)
		{
			AfxMessageBox(_T("CheckDirectory ocr error"));
		}

		if (CheckDirectory(m_strMyDirectory, _T("train"), m_strMyWord, m_strTrainPath) == FALSE)

		{
			AfxMessageBox(_T("CheckDirectory train error"));	
		}

		if (CheckDirectory(m_strMyDirectory, _T("test"), m_strMyWord, m_strTestPath) == FALSE)
		{
			AfxMessageBox(_T("CheckDirectory test error"));
		}

		if (CheckDirectory(m_strMyDirectory, _T("validation"), m_strMyWord, m_strValidationPath) == FALSE)
		{
			AfxMessageBox(_T("CheckDirectory validation error"));
		}

		CFile cfile;
		if (cfile.Open(strFile, CFile::modeRead | CFile::shareDenyNone) == TRUE)
		{
			TCHAR pbufRead[102400] = { 0, };
			cfile.Read(pbufRead, sizeof(pbufRead));

			CString strReadMsg = _T("");
			strReadMsg = pbufRead;
			strReadMsg.Replace(_T("\r\n"), _T(""));

			int nCntWord = GetFindCharCount(strReadMsg, '|');
			
			for (int i = 0; i <= nCntWord; ++i)
			{
				CString strText = _T("");
				AfxExtractSubString(strText, strReadMsg, i, '|');
				//m_setWords.insert(strText);
				m_strlnormal.AddTail(strText);
			}
			cfile.Close();
		}

		m_posWord4 = m_strlnormal.GetHeadPosition();
		SetTimer(4, 100, 0);
	}
	else
	{
		AfxMessageBox(_T("no file"));
	}
}
