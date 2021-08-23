#if !defined(AFX_EVMDIALOG_H__92495FC2_3129_11D5_B89B_FE2BA355A53D__INCLUDED_)
#define AFX_EVMDIALOG_H__92495FC2_3129_11D5_B89B_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EVMDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEVMDialog dialog

class CEVMDialog : public CDialog
{
// Construction
public:
	CEVMDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEVMDialog)
	enum { IDD = IDD_EV_METHODS };
	int		m_Method;
	int		m_HardMethod;
	BOOL	m_bCondenceMass;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEVMDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEVMDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVMDIALOG_H__92495FC2_3129_11D5_B89B_FE2BA355A53D__INCLUDED_)
