#if !defined(AFX_GRAPHICVIEW_H__106B4362_7B0E_11D3_980F_BF05434AD432__INCLUDED_)
#define AFX_GRAPHICVIEW_H__106B4362_7B0E_11D3_980F_BF05434AD432__INCLUDED_

#include "CoordD.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GraphicView.h : header file
//
#include "matr.h"
#include "knot.h"
/////////////////////////////////////////////////////////////////////////////
// CGraphicView view

typedef struct _Field
{
	int left, right, top, down;
}FieldGraph;

class CGraphData
{
	void InitBy( const CGraphData& );
public:
//структура, хранящая данные о загруженных графиках
	CGraphData();
	~CGraphData();
	CGraphData( const CGraphData& );
	CGraphData& operator=( const CGraphData& );

	CString m_strCaption, m_strFileName;
	bool m_bEnable;//флаг видимости
	COLORREF m_Clr;//цвет
	double m_Scale;//масштабирующий множитель
	CMatr m_Data;//вектор из 2-х столбцов (X;Y)

	bool operator==( const CGraphData& ) const;
	bool operator<( const CGraphData& ) const;
	bool operator!=( const CGraphData& ) const;
	bool operator>( const CGraphData& ) const;
};

typedef std::list<CGraphData> GraphList;

class CGraphicView : public CView
{
protected:
	CGraphicView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGraphicView)

// Attributes
public:
	GraphList m_Graphs;

	int TypeX, TypeY;
	CKnot *pKnot;

	int Mode_GetCoord;//Включен режим вывода координат курсора на графике
	double RegionMaxY[2];
	double RegionMinY[2];
	CPoint RegionPoint[2];

	int SizeX;
	BOOL AutoSizing;
	CMatr Dat;
	bool m_bMainGraphEnable;//показывать или нет главный график
	double ScaleX, ScaleY;
	double minX, maxX, minY, maxY;
	CPoint PointBeg, PointEnd, PointNew;
	BOOL RectOnly, CoordOnly;
	FieldGraph field;
	CString str_title;
	double *pRowX, *pRowY, *pT;
// Operations
public:
	inline void DrawRect(CDC* pDC, int x1, int y1, int x2, int y2);
	void SetMaxMin();
	double GetStandartStep(double _step);
	inline void DrawTitle( CDC*, CRect&, CFont&, COLORREF& );
	inline void DrawOutLine(CDC *pDC, CRect &clrect);
	inline BOOL NormalizePoint(CPoint *p);
	inline CCoordD ScreenToSheme(POINT &p);
	inline CPoint ShemeToScreen(CCoordD &c);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGraphicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAutosize();
	afx_msg void OnUpdateAutosize(CCmdUI* pCmdUI);
	afx_msg void OnGetcoord();
	afx_msg void OnUpdateGetcoord(CCmdUI* pCmdUI);
	afx_msg void OnSaverez();
	afx_msg void OnUpdateSaverez(CCmdUI* pCmdUI);
	afx_msg void OnCalcmat();
	afx_msg void OnGraphProp();
	afx_msg void OnMainGraph();
	afx_msg void OnUpdateMainGraph(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICVIEW_H__106B4362_7B0E_11D3_980F_BF05434AD432__INCLUDED_)
