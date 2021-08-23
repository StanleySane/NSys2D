#if !defined(AFX_MASSDLG_H__DDB382C3_D6CB_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_MASSDLG_H__DDB382C3_D6CB_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MassDlg.h : header file
//
#include "mass.h"
/////////////////////////////////////////////////////////////////////////////
// CMassDlg dialog

class CMassDlg : public CDialog
{
// Construction
public:
	BOOL VerifyInfo();
	void InvalidateKnot(BOOL bSave);
	CMass* pMass;
	CListKnot* pListKnot;

	CMassDlg(CListKnot *plistkn,
				   CMass *pmass=NULL, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMassDlg)
	enum { IDD = IDD_DIALOGMASS };
	CComboBox	m_ComboBoxKnot;
	CString	m_EditM;
	CString	m_EditJp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMassDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMassDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButnewknot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MASSDLG_H__DDB382C3_D6CB_11D2_AF23_BB2B1C460D22__INCLUDED_)
