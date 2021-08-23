#if !defined(AFX_GROUPLISTDLG_H__2B3FD903_7655_11D5_B89C_FE2BA355A53D__INCLUDED_)
#define AFX_GROUPLISTDLG_H__2B3FD903_7655_11D5_B89C_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GroupListDlg.h : header file
//
#include "ShemeGroup.h"
/////////////////////////////////////////////////////////////////////////////
// CGroupListDlg dialog

class CGroupListDlg : public CDialog
{
	bool m_DlgType;//true - для удаления и редактирования и т.д.
					//false - для простого выбора группы
// Construction
public:
	Groups m_vecElGr;
	Groups m_vecKnGr;
	ARRAY m_arMod;//список модифицированных групп
	ARRAY m_arDel;//список удалённых групп
	int m_SelDlgItem;//при m_DlgType==false это поле содержит
	//номер выбранноё группы

	CGroupListDlg( const Groups &vecElGr, 
		const Groups &vecKnGr,
		bool flag, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGroupListDlg)
	enum { IDD = IDD_GROUP_LIST };
	CListBox	m_ListBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGroupListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditGroup();
	afx_msg void OnButtonDelGroup();
	virtual void OnOK();
	afx_msg void OnButtonGroupShow();
	afx_msg void OnButtonGroupSave();
	afx_msg void OnButtonGroupOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUPLISTDLG_H__2B3FD903_7655_11D5_B89C_FE2BA355A53D__INCLUDED_)
