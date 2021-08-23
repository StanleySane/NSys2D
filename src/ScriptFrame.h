// ScriptFrame.h : header file
//
#if !defined(AFX_SCRIPTFRAME_H__7E388EA3_4EF8_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_SCRIPTFRAME_H__7E388EA3_4EF8_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CScriptFrame frame

class CScriptFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CScriptFrame)
protected:
	CScriptFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CToolBar    m_wndToolBar;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CScriptFrame();

	// Generated message map functions
	//{{AFX_MSG(CScriptFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIPTFRAME_H__7E388EA3_4EF8_11D6_B89D_FE2BA355A53D__INCLUDED_)
