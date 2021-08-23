// KnotPropertyFrame.h : header file
//
// This file contains the mini-frame that controls modeless 
// property sheet CKnotPropertySheet.

#ifndef __KNOTPROPERTYFRAME_H__
#define __KNOTPROPERTYFRAME_H__

#include "KnotPropertySheet.h"

/////////////////////////////////////////////////////////////////////////////
// CKnotPropertyFrame frame

class CKnotPropertyFrame : public CMiniFrameWnd
{
	DECLARE_DYNCREATE(CKnotPropertyFrame)
//Construction
public:
	CKnotPropertyFrame();

// Attributes
public:
	CKnotPropertySheet* m_pModelessPropSheet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKnotPropertyFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CKnotPropertyFrame();

	// Generated message map functions
	//{{AFX_MSG(CKnotPropertyFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif	// __KNOTPROPERTYFRAME_H__
