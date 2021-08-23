#if !defined(AFX_HARDRODDLG_H__ECCFA7C3_310F_11D5_B89B_FE2BA355A53D__INCLUDED_)
#define AFX_HARDRODDLG_H__ECCFA7C3_310F_11D5_B89B_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HardRodDlg.h : header file
//
#include "combobox_ConnectType.h"
#include "knot.h"
#include "listknot.h"
#include "HardRod.h"
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CHardRodDlg dialog

class CHardRodDlg : public CDialog
{
	bool m_bFull;
// Construction
public:
	void InvalidateKnot(BOOL bSave=FALSE);
	CListKnot *pListKnot;
	CHardRod *pHardRod;
	BOOL VerifyInfo();
	CHardRodDlg(CListKnot *plistkn, CHardRod *pHrod=NULL,
		bool full = true, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHardRodDlg)
	enum { IDD = IDD_DIALOGHARDROD };
	CComboBox_ConnectType	m_ConnectType2;
	CComboBox_ConnectType	m_ConnectType1;
	CComboBox	m_ComboBoxKnot2;
	CComboBox	m_ComboBoxKnot1;
	CString	m_EditJ;
	CString	m_EditE;
	CString	m_EditM;
	CString	m_EditF;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHardRodDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHardRodDlg)
		virtual BOOL OnInitDialog();
		virtual void OnOK();
	afx_msg void OnButnewknot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HARDRODDLG_H__ECCFA7C3_310F_11D5_B89B_FE2BA355A53D__INCLUDED_)
