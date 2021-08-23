#if !defined(AFX_KNOTDLG_H__704BE923_BC59_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_KNOTDLG_H__704BE923_BC59_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// KnotDlg.h : header file
//
#include "knot.h"
#include "listknot.h"
#include "ComboBox_FixedType.h"

/////////////////////////////////////////////////////////////////////////////
// CKnotDlg dialog

class CKnotDlg : public CDialog
{
// Construction
public:
	CKnot* pKnot;
	CKnotDlg(CKnot *pKnot = NULL, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKnotDlg)
	enum { IDD = IDD_DIALOGCOORD };
	CComboBox_FixedType	m_FixedType;
	double	m_EditX;
	double	m_EditY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKnotDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CKnotDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KNOTDLG_H__704BE923_BC59_11D2_AF23_BB2B1C460D22__INCLUDED_)
