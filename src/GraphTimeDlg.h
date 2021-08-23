#if !defined(AFX_GRAPHTIMEDLG_H__5532A5C2_DD6E_11D3_9814_BF05434AD432__INCLUDED_)
#define AFX_GRAPHTIMEDLG_H__5532A5C2_DD6E_11D3_9814_BF05434AD432__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GraphTimeDlg.h : header file
//
#include "paramtime.h"
/////////////////////////////////////////////////////////////////////////////
// CGraphTimeDlg dialog

class CGraphTimeDlg : public CDialog
{
// Construction
public:
	BOOL VerifyInfo();
	CGraphTimeDlg(CParamTime *pparam, CWnd* pParent = NULL);   // standard constructor
	CParamTime *pParam;
// Dialog Data
	//{{AFX_DATA(CGraphTimeDlg)
	enum { IDD = IDD_DIALOG4 };
	CString	m_TimeBeg;
	CString	m_TimeEnd;
	CString	m_TimeStep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphTimeDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHTIMEDLG_H__5532A5C2_DD6E_11D3_9814_BF05434AD432__INCLUDED_)
