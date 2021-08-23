#if !defined(AFX_FREQVIEWDLG_H__AD77EAC3_938F_11D3_980F_BF05434AD432__INCLUDED_)
#define AFX_FREQVIEWDLG_H__AD77EAC3_938F_11D3_980F_BF05434AD432__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FreqViewDlg.h : header file
//
#include "matr.h"
/////////////////////////////////////////////////////////////////////////////
// CFreqViewDlg dialog

class CFreqViewDlg : public CDialog
{
// Construction
public:
	CFreqViewDlg(CMatr &f, CWnd* pParent = NULL);   // standard constructor
	CMatr F;
// Dialog Data
	//{{AFX_DATA(CFreqViewDlg)
	enum { IDD = IDD_FREQVIEW };
	CListBox	m_ListFreq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFreqViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFreqViewDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FREQVIEWDLG_H__AD77EAC3_938F_11D3_980F_BF05434AD432__INCLUDED_)
