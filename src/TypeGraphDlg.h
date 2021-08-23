#if !defined(AFX_TYPEGRAPHDLG_H__3FBBE143_E3BC_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_TYPEGRAPHDLG_H__3FBBE143_E3BC_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TypeGraphDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTypeGraphDlg dialog

class CTypeGraphDlg : public CDialog
{
// Construction
public:
	CTypeGraphDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTypeGraphDlg)
	enum { IDD = IDD_DIALOGTYPEGRAPH };
	int		m_SelectH;
	int		m_SelectV;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTypeGraphDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTypeGraphDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TYPEGRAPHDLG_H__3FBBE143_E3BC_11D2_AF23_BB2B1C460D22__INCLUDED_)
