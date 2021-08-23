#if !defined(AFX_MOVIEVIEW_H__68049FA3_5EEA_11D6_B89E_FE2BA355A53D__INCLUDED_)
#define AFX_MOVIEVIEW_H__68049FA3_5EEA_11D6_B89E_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MovieView.h : header file
//
#include "AlgolMatr.h"

#include<map>
#include<vector>

class CShemeDoc;
class CRod;
/////////////////////////////////////////////////////////////////////////////
// CMovieView view

class CMovieView : public CScrollView
{
protected:
	CMovieView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMovieView)

private:
	void SetCurrentTime();
	void Draw();
	void Reset();
	BOOL CreateGLContext( HDC );
	BOOL SetPixelFormat( HDC );

	int m_width, m_height;
	CClientDC *m_pDC;
	HGLRC m_hrc;
	//шаг интегрирования (нужен для вывода текущего времени):
	double m_IntegrStep;
	//текущий момент времени (вернее, момент интегрирования):
	int m_Time;
	//конечный момент времени:
	int m_TimeMax;
	//начальный момент времени:
	int m_StartTime;
	//приращение таймера (в милисекундах):
	UINT m_TimeStep;
	//флаг о том, что идёт выполнение:
	bool m_bIsMoving;
	//флаг о том, что окно ещё ни разу не прорисовывалось:
	bool m_bIsFirstCreating;
	//строка с текущим временем:
	CString m_strCurrentTime;

// Attributes
public:
	typedef std::map<CRod*,std::vector<std::vector<std::pair<double,double> > > > RodMoves;
	RodMoves m_RodMoves;

	//флаг: рисовать или нет связи
	bool m_bShowKnots;
	GLUquadricObj *m_pQuad;
	//ширина схемы:
	double m_Width;
	//м-ца результата интегрирования (matr_ResY1),
	//приведённая к формату анимации, т.е. в ней хранятся не
	//смещения координат узлов, а уже экранные коор-ты узлов в
	//каждый момент времени:
	AlgolMatr m_Res;
	//вектор истинных (т.е. заданных в схеме) координат соответствующих
	//степеней свободы:
	AlgolMatr m_KnotCoords;


// Operations
public:
	CShemeDoc* GetDocument();

	void InitMatr( CShemeDoc* );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMovieView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMovieView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMovieView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMovieRun();
	afx_msg void OnMovieStop();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateMovieRun(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMovieStop(CCmdUI* pCmdUI);
	afx_msg void OnMovieParams();
	afx_msg void OnUpdateMovieParams(CCmdUI* pCmdUI);
	afx_msg void OnMovieMoveLeft();
	afx_msg void OnMovieMoveRight();
	afx_msg void OnMovieScaleDec();
	afx_msg void OnMovieScaleInc();
	afx_msg void OnMovieAutoScale();
	afx_msg void OnMovieMoveDown();
	afx_msg void OnMovieMoveUp();
	afx_msg void OnMoviePrevStep();
	afx_msg void OnMovieNextStep();
	afx_msg void OnUpdateMoviePrevStep(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMovieNextStep(CCmdUI* pCmdUI);
	afx_msg void OnMoviePause();
	afx_msg void OnUpdateMoviePause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCurrentTime(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CMovieView.cpp
inline CShemeDoc* CMovieView::GetDocument()
   { return (CShemeDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVIEVIEW_H__68049FA3_5EEA_11D6_B89E_FE2BA355A53D__INCLUDED_)
