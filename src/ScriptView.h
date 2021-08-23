// ScriptView.h : header file
//
#if !defined(AFX_SCRIPTVIEW_H__7E388EA2_4EF8_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_SCRIPTVIEW_H__7E388EA2_4EF8_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CScriptDoc;
/////////////////////////////////////////////////////////////////////////////
// CScriptView view

class CScriptView : public CEditView
{
protected: // create from serialization only
	CScriptView();
	DECLARE_DYNCREATE(CScriptView)

// Attributes
public:
	CScriptDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScriptView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Generated message map functions
	//{{AFX_MSG(CScriptView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRunScript();
//	afx_msg void OnScriptFileSaveAs();
	afx_msg void OnScriptFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ShemeView.cpp
inline CScriptDoc* CScriptView::GetDocument()
   { return (CScriptDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIPTVIEW_H__7E388EA2_4EF8_11D6_B89D_FE2BA355A53D__INCLUDED_)
