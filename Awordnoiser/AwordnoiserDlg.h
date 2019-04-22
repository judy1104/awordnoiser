
// AwordnoiserDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAwordnoiserDlg ��ȭ ����
class CAwordnoiserDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CAwordnoiserDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AWORDNOISER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

private:
	int		m_nfile = 0;
	int		m_nOldCount = 0; 
	int		m_nCntSentence = 0;
	int		m_nTimerWord;
	int		m_nTimerWord2;
	int		m_nTimerSentence; 

	BOOL	m_bDoing = FALSE; 
	BOOL	m_bSuccess = FALSE; 

	CString m_strMyDirectory = _T("");
	CString m_strDirSentence = _T("");
	CString m_strMyWord = _T("");

	CString m_strTrainPath = _T("");
	CString m_strTestPath = _T("");
	CString m_strValidationPath = _T("");
	CString m_strOCRPath = _T("");

	CString m_strTextPath = _T("");

	CStringList	m_strWordlist; 
	CStringList m_strBigWordlist; 
	CStringList m_strBowlist; 
	CStringList m_strlSentence; 

	POSITION m_posWord; 
	POSITION m_posBigWord;
	POSITION m_posBowset;
	POSITION m_posSentence;

private:
	CString GetCurretDirectory();
	void CaptureEditcontrol(int nEditId, CString strPath, CString strFolder, int nWidth = NUM_SIZE_WIDTH, int nHeight = NUM_SIZE_HEIGHT);
	void CaptureEditcontrol_Sentence(CString strPath, CString strName= _T("sentence"), int nWidth = NUM_SIZE_WIDTH_SENTENCE, int nHeight = NUM_SIZE_HEIGHT_SENTENCE);
	CString GetWord(CString strMsg);
	BOOL ReadWordsetfile(CStringList& strlBOWA, CString strPath);
	BOOL RunWordnoiser(CString strWord, CStringList& strWordlist, int nFilter=10);
	void ClearContorl(CEdit& editId, CButton& btnId, CProgressCtrl& progressId);
	void SetDlgControlIndex(CProgressCtrl& progress, CStatic& stCount);
	void SetEditcontrolText(CEdit& eidtId, CString strText);
	BOOL MakeDataDirectory(CString strMyPath, CString strType, CString strWord);
	BOOL CheckDirectory(CString strPath, CString strType, CString strWord, CString& strFullPath);
	int GetFindCharCount(CString parm_string, char parm_find_char);
	BOOL CreateNoiseWord(CEdit& editId, CButton& btnId, CProgressCtrl& progressId, int nTimerId, int nTimerPtr);
	void SaveTextFile(CEdit& editId, CString strWord);
	void LoadBadwords(CStringList strBadList);

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
private:
	CEdit m_editWord;
	CEdit m_editWord2;
	CEdit m_edit3;
	CStatic m_stIndex;
	CStatic m_stIndex2;
	CStatic m_stWordPath;
	CStatic m_stSentencePath;
	CProgressCtrl m_progress;
	CProgressCtrl m_progress2;
	CProgressCtrl m_progress3;
	CButton m_btnRun;
	CButton m_btnRun2;

	afx_msg void OnBnClickedButton_Run();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg LRESULT OnMakeBadWords(WPARAM wParm, LPARAM lParm);
	afx_msg void OnTimer(UINT_PTR nIDEvent);	
	afx_msg void OnDropFiles(HDROP hDropInfo);	

};
