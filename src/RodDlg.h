#if !defined(AFX_RODDLG_H__704BE922_BC59_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_RODDLG_H__704BE922_BC59_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RodDlg.h : header file
//
#include "combobox_ConnectType.h"
#include "knot.h"
#include "listknot.h"
#include "rod.h"
#include <afxtempl.h>
/////////////////////////////////////////////////////////////////////////////
// CRodDlg dialog

class CRodDlg : public CDialog
{
	bool m_bFull;
// Construction
public:
	void InvalidateKnot(BOOL bSave=FALSE);
	CListKnot *pListKnot;
	CRod* pRod;
	BOOL VerifyInfo();
	CRodDlg(CListKnot *plistkn,CRod *prod=NULL,bool full = true,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRodDlg)
	enum { IDD = IDD_DIALOGROD };
	CComboBox_ConnectType	m_ConnectType2;
	CComboBox_ConnectType	m_ConnectType1;
	CComboBox	m_ComboBoxKnot2;
	CComboBox	m_ComboBoxKnot1;
	CString	m_EditJx;
	CString	m_EditE;
	CString	m_EditM;
	CString	m_EditF;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRodDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRodDlg)
	afx_msg void OnButnewknot();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RODDLG_H__704BE922_BC59_11D2_AF23_BB2B1C460D22__INCLUDED_)
