#if !defined(AFX_SHEMEVARS_H__D5F3E3E2_9347_11D6_B89E_FE2BA355A53D__INCLUDED_)
#define AFX_SHEMEVARS_H__D5F3E3E2_9347_11D6_B89E_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ShemeVars.h : header file
//
#include "ShemeVarsTable.h"
/////////////////////////////////////////////////////////////////////////////
// CShemeVars dialog

class CShemeVars : public CDialog
{
// Construction
public:
	CShemeVars( CShemeVarsTable *p, CWnd* pParent = NULL);   // standard constructor
	bool SetItem( ShemeVarsTable::iterator&, int, bool insert = false );
	bool Recalc();
	int GetSelectedIndex();
	void EditVar();

	CShemeVarsTable *m_pVarsTable;
	bool m_bValidTable;
	bool m_bWasActions;
// Dialog Data
	//{{AFX_DATA(CShemeVars)
	enum { IDD = IDD_SHEME_VARS };
	CListCtrl	m_VarList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShemeVars)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShemeVars)
	virtual BOOL OnInitDialog();
	afx_msg void OnRecalc();
	virtual void OnOK();
	afx_msg void OnAddVar();
	afx_msg void OnDelVar();
	afx_msg void OnEditVar();
	afx_msg void OnDblclkVarsList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEMEVARS_H__D5F3E3E2_9347_11D6_B89E_FE2BA355A53D__INCLUDED_)
