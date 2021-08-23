#if !defined(AFX_DEMFDLG_H__F5362BC3_CB61_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_DEMFDLG_H__F5362BC3_CB61_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DemfDlg.h : header file
//
#include "demf.h"
/////////////////////////////////////////////////////////////////////////////
// CDemfDlg dialog

class CDemfDlg : public CDialog
{
	bool m_bFull;
// Construction
public:
	int SetState();
	void InvalidateKnot(BOOL bSave=FALSE);
	BOOL VerifyInfo();
	CDemfDlg(CListKnot *plistkn, CDemf *pdemf=NULL, bool full = true, CWnd* pParent = NULL);   // standard constructor
	CDemf* pDemf;
	CListKnot *pListKnot;

// Dialog Data
	//{{AFX_DATA(CDemfDlg)
	enum { IDD = IDD_DIALOGDEMF };
	CEdit	m_Edit_XX;
	CEdit	m_Edit_XS;
	CEdit	m_Edit_X5;
	CEdit	m_Edit_X3;
	CEdit	m_Edit_X1;
	CComboBox	m_ComboBoxKnot2;
	CComboBox	m_ComboBoxKnot1;
	int		m_Radio_X1;
	int		m_Radio_X3;
	int		m_Radio_X5;
	int		m_Radio_XX;
	int		m_Radio_XS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemfDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDemfDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnButnewknot();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMFDLG_H__F5362BC3_CB61_11D2_AF23_BB2B1C460D22__INCLUDED_)
