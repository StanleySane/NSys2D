//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_COMPLEXSPECTRDLG_H__9B5C91A2_BC35_11D3_9812_BF05434AD432__INCLUDED_)
#define AFX_COMPLEXSPECTRDLG_H__9B5C91A2_BC35_11D3_9812_BF05434AD432__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ComplexSpectrDlg.h : header file
//
#include "knot.h"
#include "listspectr.h"
#include "listknot.h"
/////////////////////////////////////////////////////////////////////////////
// CComplexSpectrDlg dialog

class CComplexSpectrDlg : public CDialog
{
// Construction
public:
	void SetEnable();
	CKnot* GetKnot(int index);
	int SetKnot();
	int SetGrid();
	CComplexSpectrDlg(CListKnot *_plistknot, CListSpectr *_plistspectr, 
		              CKnot *_pkn, int _nFree, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CComplexSpectrDlg)
	enum { IDD = IDD_COMPLEXSPECTR };
	CButton	m_But2;
	CButton	m_But3;
	CButton	m_But1;
	CComboBox	m_ComboFree;
	CComboBox	m_ComboKnot;
	CMSFlexGrid	m_Grid;
	//}}AFX_DATA
	CListSpectr *pListSpectr;
	CListKnot   *pListKnot;
	CKnot *pkn;
	int nFree;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComplexSpectrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComplexSpectrDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddElem();
	afx_msg void OnDelElem();
	afx_msg void OnSelChangeMsflexgrid1();
	afx_msg void OnClickMsflexgrid1();
	afx_msg void OnButton3();
	afx_msg void OnSelchangeCombo1();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPLEXSPECTRDLG_H__9B5C91A2_BC35_11D3_9812_BF05434AD432__INCLUDED_)
