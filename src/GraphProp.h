#if !defined(AFX_GRAPHPROP_H__2DF2E5A2_9BFE_11D6_B89E_FE2BA355A53D__INCLUDED_)
#define AFX_GRAPHPROP_H__2DF2E5A2_9BFE_11D6_B89E_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GraphProp.h : header file
//
#include "GraphicView.h"
#include "GraphListBox.h"
/////////////////////////////////////////////////////////////////////////////
// CGraphProp dialog

class CGraphProp : public CDialog
{
// Construction
public:
	CGraphProp( CGraphicView *pView, CWnd* pParent = NULL);   // standard constructor

	CGraphicView *m_pView;
	void EditItem();
// Dialog Data
	//{{AFX_DATA(CGraphProp)
	enum { IDD = IDD_GRAPHS_PROPERTIES };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CGraphListBox m_GraphList;
	// Generated message map functions
	//{{AFX_MSG(CGraphProp)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkGraphList();
	afx_msg void OnGraphEdit();
	afx_msg void OnGraphNew();
	virtual void OnOK();
	afx_msg void OnGraphDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHPROP_H__2DF2E5A2_9BFE_11D6_B89E_FE2BA355A53D__INCLUDED_)
