
// treecheckDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CtreecheckDlg dialog
class CtreecheckDlg : public CDialogEx
{
// Construction
public:
	CtreecheckDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TREECHECK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnCheckTree();
	afx_msg void OnExit();
	afx_msg void OnEnChangeEdit1();
	CEdit m_Result;
};
