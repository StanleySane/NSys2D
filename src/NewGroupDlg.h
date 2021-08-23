#if !defined(AFX_NEWGROUPDLG_H__2B3FD902_7655_11D5_B89C_FE2BA355A53D__INCLUDED_)
#define AFX_NEWGROUPDLG_H__2B3FD902_7655_11D5_B89C_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NewGroupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewGroupDlg dialog

class CNewGroupDlg : public CDialog
{
// Construction
public:
	CNewGroupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewGroupDlg)
	enum { IDD = IDD_GROUP_NEW };
	CString	m_strGroup;
	CString	m_strGroupName;
	int		m_iGroupType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewGroupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewGroupDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWGROUPDLG_H__2B3FD902_7655_11D5_B89C_FE2BA355A53D__INCLUDED_)
