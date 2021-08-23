#if !defined(AFX_FREQVIEW_H__AD77EAC2_938F_11D3_980F_BF05434AD432__INCLUDED_)
#define AFX_FREQVIEW_H__AD77EAC2_938F_11D3_980F_BF05434AD432__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FreqView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFreqView dialog

class CFreqView : public CDialog
{
// Construction
public:
	CFreqView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFreqView)
	enum { IDD = IDD_DIALOG4 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFreqView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFreqView)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FREQVIEW_H__AD77EAC2_938F_11D3_980F_BF05434AD432__INCLUDED_)
