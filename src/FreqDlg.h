#if !defined(AFX_FREQDLG_H__C0BC9242_7D6C_11D3_980F_BF05434AD432__INCLUDED_)
#define AFX_FREQDLG_H__C0BC9242_7D6C_11D3_980F_BF05434AD432__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FreqDlg.h : header file
//
#include "listknot.h"
#include "FreqParam.h"
/////////////////////////////////////////////////////////////////////////////
// CFreqDlg dialog

class CFreqDlg : public CDialog
{
// Construction
public:
	BOOL VerifyInfo();
	void InvalidateKnot(BOOL bSave);
	CListKnot *pListKnot;
	CFreqDlg(CListKnot *plistkn, CFreqParam *param, CWnd* pParent = NULL);   // standard constructor

	//Указатель на класс, содержащий начальные параметры для вычисления 
	//частотных характеристик
	CFreqParam *pParam;
	//Номера выбранных степеней свободы
	int Free1, Free2;
	//указатели на два узла для которых строятся характеристики
	CKnot *pkn1,*pkn2;

// Dialog Data
	//{{AFX_DATA(CFreqDlg)
	enum { IDD = IDD_FREQDLG };
	CComboBox	m_ComboBoxKnot2;
	CComboBox	m_ComboBoxKnot1;
	CString	m_w0;
	CString	m_w1;
	CString	m_dw;
	BOOL	m_LogCoord;
	int		m_TypeCharact;
	int		m_Free1;
	int		m_Free2;
	int		m_Derive;
	int		m_Force;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFreqDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFreqDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FREQDLG_H__C0BC9242_7D6C_11D3_980F_BF05434AD432__INCLUDED_)
