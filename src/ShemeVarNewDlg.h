#if !defined(AFX_SHEMEVARNEWDLG_H__0C943223_936F_11D6_B89E_FE2BA355A53D__INCLUDED_)
#define AFX_SHEMEVARNEWDLG_H__0C943223_936F_11D6_B89E_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ShemeVarNewDlg.h : header file
//
class CShemeVarsTable;
/////////////////////////////////////////////////////////////////////////////
// ShemeVarNewDlg dialog

class ShemeVarNewDlg : public CDialog
{
// Construction
public:
	ShemeVarNewDlg( CShemeVarsTable *p, bool flg = true, CWnd* pParent = NULL);   // standard constructor

	CShemeVarsTable *m_pVarsTable;
	bool m_bNewVar;
// Dialog Data
	//{{AFX_DATA(ShemeVarNewDlg)
	enum { IDD = IDD_SHEME_VAR_NEW };
	CString	m_strExpr;
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ShemeVarNewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ShemeVarNewDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEMEVARNEWDLG_H__0C943223_936F_11D6_B89E_FE2BA355A53D__INCLUDED_)
