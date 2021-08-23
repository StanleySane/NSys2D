#if !defined(AFX_PRECALCDLG_H__CA872FE2_DEE5_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_PRECALCDLG_H__CA872FE2_DEE5_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PreCalcDlg.h : header file
//
#include "ParamIntegr.h"
/////////////////////////////////////////////////////////////////////////////
// CPreCalcDlg dialog

class CPreCalcDlg : public CDialog
{
// Construction
public:
	CPreCalcDlg(CParamIntegr *pParamIntegr, CWnd* pParent = NULL);   // standard constructor
	CParamIntegr *pParam;
// Dialog Data
	//{{AFX_DATA(CPreCalcDlg)
	enum { IDD = IDD_DIALOGPRECALC };
	int		m_Method;
	double	m_EditTime;
	double	m_EditStep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreCalcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPreCalcDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRECALCDLG_H__CA872FE2_DEE5_11D2_AF23_BB2B1C460D22__INCLUDED_)
