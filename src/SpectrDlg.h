#if !defined(AFX_SPECTRDLG_H__1BB58762_C35E_11D3_AF28_BB2B1C460D22__INCLUDED_)
#define AFX_SPECTRDLG_H__1BB58762_C35E_11D3_AF28_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SpectrDlg.h : header file
//
#include "listknot.h"
#include "knot.h"
#include "FreqParam.h"

/////////////////////////////////////////////////////////////////////////////
// CSpectrDlg dialog

class CSpectrDlg : public CDialog
{
// Construction
public:
	BOOL VerifyInfo();
	void InvalidateKnot();
	CSpectrDlg(CFreqParam *pparam, CListKnot *plistknot, CKnot *pknot, CWnd* pParent = NULL);   // standard constructor
	CListKnot *pListKnot;
	CKnot *pKnot;
	CFreqParam *pParamOut;

// Dialog Data
	//{{AFX_DATA(CSpectrDlg)
	enum { IDD = IDD_SPECTRDLG };
	CComboBox	m_ComboKnot;
	int		m_Free;
	double	m_W0;
	double	m_W1;
	double	m_dW;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpectrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpectrDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECTRDLG_H__1BB58762_C35E_11D3_AF28_BB2B1C460D22__INCLUDED_)
