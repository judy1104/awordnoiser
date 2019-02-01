
// AwordnoiserDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CAwordnoiserDlg 대화 상자
class CAwordnoiserDlg : public CDialogEx
{
// 생성입니다.
public:
	CAwordnoiserDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AWORDNOISER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

private:
	int		m_nfile = 0;
	int		m_nTimer;

	CString m_strMyDirectory = _T("");
	CString m_strMyWord = _T("");

	CStringList	m_strWordlist; 

private:
	CString GetCurretDirectory();
	void CaptureEditcontrol();

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CEdit m_editWord;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_ckop1;
};
