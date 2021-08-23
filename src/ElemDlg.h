#if !defined(AFX_ELEMDLG_H__482731A2_DA51_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_ELEMDLG_H__482731A2_DA51_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ElemDlg.h : header file
//
#include "Elem.h"
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CElemDlg dialog

class CElemDlg : public CDialog
{
// Construction
public:
	int SetItem(CElem *elem, int index, BOOL insert=FALSE);
	int GetSelectIndex();
	POSITION GetElemPosition(int num);
	CElemDlg(CList<CElem*,CElem*> *plistelem,
					CListKnot *plistknot,
					CWnd* pParent = NULL);   // standard constructor
	CList<CElem*,CElem*> *pListElem;
	CListKnot *pListKnot;
// Dialog Data
	//{{AFX_DATA(CElemDlg)
	enum { IDD = IDD_DIALOGELEM };
	CListCtrl	m_ListControl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CElemDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonprop();
	afx_msg void OnButtondel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELEMDLG_H__482731A2_DA51_11D2_AF23_BB2B1C460D22__INCLUDED_)
