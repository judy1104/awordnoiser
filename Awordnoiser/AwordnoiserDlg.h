
// AwordnoiserDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


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

	CString m_strMyDirectory = _T("");
	CString m_strMyWord = _T("");

	CStringList	m_strWordlist; 

private:
	CString GetCurretDirectory();
	void CaptureEditcontrol();
	BOOL RunWordnoiser(CString strWord, CStringList& strWordlist);

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
	CButton m_ckop1;
	CButton m_ckop2;
	CButton m_ckop3;
	CButton m_ckop4;
	CButton m_ckop5;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

};
