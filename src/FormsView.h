#if !defined(AFX_FORMSVIEW_H__0B7E1602_967C_11D3_980F_BF05434AD432__INCLUDED_)
#define AFX_FORMSVIEW_H__0B7E1602_967C_11D3_980F_BF05434AD432__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FormsView.h : header file
//
#include "matr.h"
/////////////////////////////////////////////////////////////////////////////
// CFormsView view

class CFormsView : public CScrollView
{
protected:
	CFormsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFormsView)

// Attributes
public:
	CMatr matr_Forms, matr_Freq;
	double MultMove;
	double MultAngl;
	int NumForm;
	BOOL ViewEnable;
// Operations
public:
	void SetForm(int n);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormsView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFormsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFormsView)
	afx_msg void OnMoveadd();
	afx_msg void OnMovesub();
	afx_msg void OnFreqnext();
	afx_msg void OnFreqprew();
	afx_msg void OnUpdateforms();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMSVIEW_H__0B7E1602_967C_11D3_980F_BF05434AD432__INCLUDED_)
