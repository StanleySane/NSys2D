#if !defined(AFX_GROUPPREVIEWDLG_H__D92EA882_7A00_11D5_B89C_FE2BA355A53D__INCLUDED_)
#define AFX_GROUPPREVIEWDLG_H__D92EA882_7A00_11D5_B89C_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GroupPreviewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGroupPreviewDlg dialog

class CGroupPreviewDlg : public CDialog
{
// Construction
public:
	CGroupPreviewDlg( CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGroupPreviewDlg)
	enum { IDD = IDD_DIALOG_GROUP_SHOW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupPreviewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGroupPreviewDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUPPREVIEWDLG_H__D92EA882_7A00_11D5_B89C_FE2BA355A53D__INCLUDED_)
