#if !defined(AFX_GRAPHDLG_H__2DF2E5A4_9BFE_11D6_B89E_FE2BA355A53D__INCLUDED_)
#define AFX_GRAPHDLG_H__2DF2E5A4_9BFE_11D6_B89E_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GraphDlg.h : header file
//
#include "GraphicView.h"
#include "ColorButton.h"
/////////////////////////////////////////////////////////////////////////////
// CGraphDlg dialog

class CGraphDlg : public CDialog
{
// Construction
public:
	CGraphDlg( CGraphData *pGr, CWnd* pParent = NULL);   // standard constructor

	CGraphData *m_pGraphData;
	CGraphData m_GraphData;
// Dialog Data
	//{{AFX_DATA(CGraphDlg)
	enum { IDD = IDD_GRAPH_EDIT };
	CString	m_strCaption;
	CString	m_strFileName;
	double	m_Scale;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CColorButton m_Color;
	// Generated message map functions
	//{{AFX_MSG(CGraphDlg)
	afx_msg void OnEditGraphColor();
	afx_msg void OnGraphLoad();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHDLG_H__2DF2E5A4_9BFE_11D6_B89E_FE2BA355A53D__INCLUDED_)
