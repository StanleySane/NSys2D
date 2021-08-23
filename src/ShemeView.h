// ShemeView.h : interface of the CShemeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHEMEVIEW_H__09A14A92_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_SHEMEVIEW_H__09A14A92_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_

#include "CoordD.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CShemeView : public CScrollView
{
protected: // create from serialization only
	CShemeView();
	DECLARE_DYNCREATE(CShemeView)

// Attributes
public:
	CShemeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShemeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	virtual void Serialize(CArchive& ar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void KillAllTimer(int count);
	int IsScroll(CPoint &pos);
	int SetScrollView();
	int TypeElem;
	CElem* OldSelElem;
	CElem* SelElem;
//	inline void DrawSelRod(CDC *pDC, COLORREF col);
	CElem* FindElem(CPoint & point);
	CKnot* pKnotEnd;
	CKnot* pKnotBeg;
	CKnot* SelKnot;
	CKnot* OldSelKnot;
//	inline void CShemeView::DrawSelKnot(CDC *pDC,COLORREF col);
	CKnot* FindKnot(CPoint &point);
	POINT ShemeToScreen(CCoordD &coord, BOOL scroll=FALSE);
	int StateNew,DrawOnce,KnotOnly,DrawAll,LineNear;
	BOOL InitialUpdate;
	CToolTipCtrl m_ToolTip;
	bool m_bEnableToolTips;
	CCoordD coordLast;
	CCoordD coordEnd;
	CCoordD coordStart;
	CCoordD ScreenToSheme(CPoint &point);
	virtual ~CShemeView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// m_bClickingGroup - флаг, показывающий набирается ли
	// сейчас мышкой группа. Соответственно - надо ли делать
	// Disable кнопки и меню.
	bool m_bClickingGroup;

// Generated message map functions
protected:
	//{{AFX_MSG(CShemeView)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAddgraph();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnAddrod();
	afx_msg void OnScaleadd();
	afx_msg void OnScalesub();
	afx_msg void OnUpdateSetdemf(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetrod(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetspring(CCmdUI* pCmdUI);
	afx_msg void OnSetdemf();
	afx_msg void OnSetrod();
	afx_msg void OnSetspring();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAdddemf();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnAddspring();
	afx_msg void OnUpdateAddgraph(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetmass(CCmdUI* pCmdUI);
	afx_msg void OnSetmass();
	afx_msg void OnAddmass();
	afx_msg void OnDelelem();
	afx_msg void OnUpdateDelelem(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetnull(CCmdUI* pCmdUI);
	afx_msg void OnSetnull();
	afx_msg void OnUpdateProp(CCmdUI* pCmdUI);
	afx_msg void OnProp();
	afx_msg void OnRefresh();
	afx_msg void OnFreqCalc();
	afx_msg void OnUpdateFreqCalc(CCmdUI* pCmdUI);
	afx_msg void OnSpectrCalc();
	afx_msg void OnDestroy();
	afx_msg void OnSetHardRod();
	afx_msg void OnUpdateSetHardRod(CCmdUI* pCmdUI);
	afx_msg void OnAddHardRod();
	afx_msg void OnUpdateMeshElem(CCmdUI* pCmdUI);
	afx_msg void OnMeshElem();
	afx_msg void OnButtonAutoSize();
	afx_msg void OnUpdateConvertTo(CCmdUI* pCmdUI);
	afx_msg void OnConvertTo();
	afx_msg void OnUpdateAdddemf(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddhardrod(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddmass(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddrod(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddspring(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSpectrCalc(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileClose(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintSetup(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnToolTip( UINT id, NMHDR *pTTTStruct, LRESULT *pResult );
	afx_msg void OnToolTips();
	afx_msg void OnUpdateToolTips(CCmdUI* pCmdUI);
	afx_msg void OnGroupClickKnots();
	afx_msg void OnGroupClickElems();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ShemeView.cpp
inline CShemeDoc* CShemeView::GetDocument()
   { return (CShemeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEMEVIEW_H__09A14A92_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
