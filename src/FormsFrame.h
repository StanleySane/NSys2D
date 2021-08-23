#if !defined(AFX_FORMSFRAME_H__0B7E1603_967C_11D3_980F_BF05434AD432__INCLUDED_)
#define AFX_FORMSFRAME_H__0B7E1603_967C_11D3_980F_BF05434AD432__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FormsFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormsFrame frame

class CFormsFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CFormsFrame)
protected:
	CFormsFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CToolBar    m_wndToolBar;
	CRect rect;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormsFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFormsFrame();

	// Generated message map functions
	//{{AFX_MSG(CFormsFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMSFRAME_H__0B7E1603_967C_11D3_980F_BF05434AD432__INCLUDED_)
