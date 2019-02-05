
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
	int		m_nTimer;

	BOOL	m_bDoing = FALSE; 

	CString m_strMyDirectory = _T("");
	CString m_strMyWord = _T("");

	CStringList	m_strWordlist; 

	POSITION m_position; 

private:
	CString GetCurretDirectory();
	void CaptureEditcontrol(int nWidth = NUM_SIZE_WIDTH, int nHeight = NUM_SIZE_HEIGHT);
	BOOL RunWordnoiser(CString strWord, CStringList& strWordlist, int nFilter=10);
	void ClearContorl();
	void SetDlgControlIndex();
	void SetEditcontrolText();

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editWord;
	CEdit m_editFilter;
	CStatic m_stCount;
	CStatic m_stIndex;
	CProgressCtrl m_progress;
	CButton m_ckop1;
	CButton m_ckop2;
	CButton m_ckop3;
	CButton m_ckop4;
	CButton m_ckop5;
	CButton m_btnRun;

	afx_msg void OnBnClickedButton_Run();
	afx_msg void OnBnClickedButton_Expectedwork();
	afx_msg void OnTimer(UINT_PTR nIDEvent);	
};
