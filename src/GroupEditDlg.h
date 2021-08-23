#if !defined(AFX_GROUPEDITDLG_H__545E71A2_76ED_11D5_B89C_FE2BA355A53D__INCLUDED_)
#define AFX_GROUPEDITDLG_H__545E71A2_76ED_11D5_B89C_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GroupEditDlg.h : header file
//
#include "ShemeGroup.h"
/////////////////////////////////////////////////////////////////////////////
// CGroupEditDlg dialog

class CGroupEditDlg : public CDialog
{
	int m_iGrType;
// Construction
public:
	CGroupEditDlg( const CShemeGroup *gr, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGroupEditDlg)
	enum { IDD = IDD_GROUP_EDIT };
	CString	m_strGroup;
	CString	m_strGroupName;
	CString	m_strGroupSet;
	CString	m_strGroupType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGroupEditDlg)
	afx_msg void OnButtonRefresh();
	virtual void OnOK();
	afx_msg void OnButtonPack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUPEDITDLG_H__545E71A2_76ED_11D5_B89C_FE2BA355A53D__INCLUDED_)
