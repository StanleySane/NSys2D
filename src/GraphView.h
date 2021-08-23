#if !defined(AFX_GRAPHVIEW_H__09A14A9E_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_GRAPHVIEW_H__09A14A9E_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GraphView.h : header file
//
#include "knot.h"
/////////////////////////////////////////////////////////////////////////////
// CGraphView view

class CGraphView : public CScrollView
{
protected:
	CGraphView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGraphView)

// Attributes
public:

// Operations
public:
	double ScaleX;
	double ScaleY;
	int TypeX, TypeY;
	BOOL AutoSizing;
	CKnot *pKnot;
	double *Tt;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphView)
	public:
	virtual void OnFinalRelease();
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CGraphView)
	afx_msg void OnHoradd();
	afx_msg void OnHorsub();
	afx_msg void OnVertadd();
	afx_msg void OnVertsub();
	afx_msg void OnUpdateAutosize(CCmdUI* pCmdUI);
	afx_msg void OnAutosize();
	afx_msg void OnUpdateSaverez(CCmdUI* pCmdUI);
	afx_msg void OnSaverez();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CGraphView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHVIEW_H__09A14A9E_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
