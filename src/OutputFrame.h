#if !defined(AFX_OUTPUTFRAME_H__981535C2_4FDA_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_OUTPUTFRAME_H__981535C2_4FDA_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OutputFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COutputFrame frame

class COutputFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(COutputFrame)
protected:
	COutputFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CToolBar    m_wndToolBar;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COutputFrame();

	// Generated message map functions
	//{{AFX_MSG(COutputFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTFRAME_H__981535C2_4FDA_11D6_B89D_FE2BA355A53D__INCLUDED_)
