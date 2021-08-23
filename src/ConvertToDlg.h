#if !defined(AFX_CONVERTTODLG_H__52281FC2_7BC6_11D5_B89C_FE2BA355A53D__INCLUDED_)
#define AFX_CONVERTTODLG_H__52281FC2_7BC6_11D5_B89C_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConvertToDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConvertToDlg dialog

class CConvertToDlg : public CDialog
{
// Construction
public:
	CConvertToDlg( int oldType, CWnd* pParent = NULL);   // standard constructor

	int m_iType;

// Dialog Data
	//{{AFX_DATA(CConvertToDlg)
	enum { IDD = IDD_CONVERT_TO };
	CString	m_strNewElemType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConvertToDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConvertToDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVERTTODLG_H__52281FC2_7BC6_11D5_B89C_FE2BA355A53D__INCLUDED_)
