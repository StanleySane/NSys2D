#if !defined(AFX_MOVIEFRAME_H__68049FA2_5EEA_11D6_B89E_FE2BA355A53D__INCLUDED_)
#define AFX_MOVIEFRAME_H__68049FA2_5EEA_11D6_B89E_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MovieFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMovieFrame frame

class CMovieFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CMovieFrame)
protected:
	CMovieFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CToolBar    m_wndToolBar;
	CButton m_CurrentTime;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMovieFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMovieFrame();

	// Generated message map functions
	//{{AFX_MSG(CMovieFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVIEFRAME_H__68049FA2_5EEA_11D6_B89E_FE2BA355A53D__INCLUDED_)
