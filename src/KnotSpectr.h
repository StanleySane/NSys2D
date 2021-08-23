#if !defined(AFX_KNOTSPECTR_H__D6CE3223_AB05_11D3_AF28_B4D2D506A1A2__INCLUDED_)
#define AFX_KNOTSPECTR_H__D6CE3223_AB05_11D3_AF28_B4D2D506A1A2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// KnotSpectr.h : header file
//
#include "spectrparam.h"

/////////////////////////////////////////////////////////////////////////////
// CKnotSpectr dialog

class CKnotSpectr : public CDialog
{
// Construction
public:
	BOOL VerifyInfo(double *p);
	void SetState();
	CKnotSpectr(CSpectrParam *pSpParam, CWnd* pParent = NULL);   // standard constructor

	CSpectrParam *pSpectrParam;
	int FlagView;
// Dialog Data
	//{{AFX_DATA(CKnotSpectr)
	enum { IDD = IDD_KNOTSPECTR };
	CEdit	m_Edit19;
	CEdit	m_Edit18;
	CEdit	m_Edit17;
	CEdit	m_Edit16;
	CEdit	m_Edit15;
	CEdit	m_Edit14;
	CEdit	m_Edit13;
	CEdit	m_Edit12;
	CEdit	m_Edit11;
	CEdit	m_Edit10;
	CEdit	m_Edit9;
	CEdit	m_Edit8;
	CEdit	m_Edit7;
	CEdit	m_Edit6;
	CEdit	m_Edit5;
	CEdit	m_Edit4;
	CEdit	m_Edit3;
	CEdit	m_Edit2;
	CEdit	m_Edit1;
	int		m_TypeSpectr;
	int		m_TypeInit;
	BOOL	m_CheckView;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKnotSpectr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKnotSpectr)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	virtual void OnOK();
	afx_msg void OnRadio7();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KNOTSPECTR_H__D6CE3223_AB05_11D3_AF28_B4D2D506A1A2__INCLUDED_)
