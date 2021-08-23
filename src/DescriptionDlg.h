#if !defined(AFX_DESCRIPTIONDLG_H__24C5BFC2_98CF_11D6_B89E_FE2BA355A53D__INCLUDED_)
#define AFX_DESCRIPTIONDLG_H__24C5BFC2_98CF_11D6_B89E_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DescriptionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDescriptionDlg dialog

class CDescriptionDlg : public CDialog
{
// Construction
public:
	CDescriptionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDescriptionDlg)
	enum { IDD = IDD_DESCRIPTION };
	CString	m_strDescr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDescriptionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDescriptionDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DESCRIPTIONDLG_H__24C5BFC2_98CF_11D6_B89E_FE2BA355A53D__INCLUDED_)
