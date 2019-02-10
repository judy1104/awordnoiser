
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
	int		m_nTimerWord;
	int		m_nTimerBow;

	BOOL	m_bDoing = FALSE; 

	CString m_strMyDirectory = _T("");
	CString m_strMyWord = _T("");

	CString m_strTrainPath = _T("");
	CString m_strTestPath = _T("");
	CString m_strValidationPath = _T("");

	CStringList	m_strWordlist; 
	CStringList m_strBowlist; 

	POSITION m_posWord; 
	POSITION m_posBowset;

private:
	CString GetCurretDirectory();
	void CaptureEditcontrol(CString strPath, CString strFolder, int nWidth = NUM_SIZE_WIDTH, int nHeight = NUM_SIZE_HEIGHT);
	CString GetWord(CString strMsg);
	BOOL ReadWordsetfile(CStringList& strlBOWA, CString strPath);
	BOOL RunWordnoiser(CString strWord, CStringList& strWordlist, int nFilter=10);
	void ClearContorl();
	void SetDlgControlIndex();
	void SetEditcontrolText(CString strText);
	void CheckDirectory(CString strPath, CString strFolder);

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
	CEdit m_editFilter;
	CStatic m_stCount;
	CStatic m_stIndex;
	CStatic m_stWordsetPath;
	CProgressCtrl m_progress;
	CButton m_ckop1;
	CButton m_ckop2;
	CButton m_ckop3;
	CButton m_ckop4;
	CButton m_ckop5;
	CButton m_btnRun;
	CButton m_ckWordset;

	afx_msg void OnBnClickedButton_Run();
	afx_msg void OnBnClickedButton_Expectedwork();
	afx_msg void OnTimer(UINT_PTR nIDEvent);	
	afx_msg void OnDropFiles(HDROP hDropInfo);	
};
