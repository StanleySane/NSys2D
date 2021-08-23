#if !defined(AFX_SPRINGDLG_H__A4DE2CC3_D31A_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_SPRINGDLG_H__A4DE2CC3_D31A_11D2_AF23_BB2B1C460D22__INCLUDED_

#include "ListKnot.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SpringDlg.h : header file
//
#include "spring.h"
/////////////////////////////////////////////////////////////////////////////
// CSpringDlg dialog

class CSpringDlg : public CDialog
{
	bool m_bFull;
// Construction
public:
	BOOL VerifyInfo();
	int SetState();
	void InvalidateKnot(BOOL bSave=FALSE);
	CListKnot *pListKnot;
	CSpring* pSprn;
	CSpringDlg(CListKnot *plistkn,
				   CSpring *psprn=NULL, bool full = true,
				   CWnd* pParent=NULL);

// Dialog Data
	//{{AFX_DATA(CSpringDlg)
	enum { IDD = IDD_DIALOGSPRING };
	CComboBox	m_ComboBoxKnot2;
	CComboBox	m_ComboBoxKnot1;
	int		m_Radio_X1;
	int		m_Radio_X3;
	int		m_Radio_X5;
	int		m_Radio_XX;
	CString	m_Edit_XX;
	double	m_Edit_X1;
	double	m_Edit_X3;
	double	m_Edit_X5;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpringDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpringDlg)
	afx_msg void OnButnewknot();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPRINGDLG_H__A4DE2CC3_D31A_11D2_AF23_BB2B1C460D22__INCLUDED_)
