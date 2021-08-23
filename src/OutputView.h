#if !defined(AFX_OUTPUTVIEW_H__981535C3_4FDA_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_OUTPUTVIEW_H__981535C3_4FDA_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OutputView.h : header file
//

class CScriptDoc;
class COutputFrame;
/////////////////////////////////////////////////////////////////////////////
// COutputView view

class COutputView : public CEditView
{
protected:
	COutputView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COutputView)

// Attributes
public:
	CString m_Text;//текст скрипта
	CString m_Output;//текст вывода
// Operations
public:
	void Show( const CString& );
	void Run( const CString&, COutputFrame* );
	CScriptDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COutputView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(COutputView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnOutputFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in COutputView.cpp
inline CScriptDoc* COutputView::GetDocument()
   { return (CScriptDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTVIEW_H__981535C3_4FDA_11D6_B89D_FE2BA355A53D__INCLUDED_)
