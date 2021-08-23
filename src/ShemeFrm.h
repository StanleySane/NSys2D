// ShemeFrm.h : interface of the CShemeFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHEMEFRM_H__09A14A8E_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_SHEMEFRM_H__09A14A8E_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CShemeFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CShemeFrame)
public:
	CShemeFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShemeFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
//	CStatusBar m_wndStatusBar;
	virtual ~CShemeFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CShemeFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEMEFRM_H__09A14A8E_BBAC_11D2_AF23_BB2B1C460D22__INCLUDED_)
