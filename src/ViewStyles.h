#if !defined(AFX_VIEWSTYLES_H__92495FC3_3129_11D5_B89B_FE2BA355A53D__INCLUDED_)
#define AFX_VIEWSTYLES_H__92495FC3_3129_11D5_B89B_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ViewStyles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewStyles dialog

class CViewStyles : public CDialog
{
// Construction
public:
	CViewStyles(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewStyles)
	enum { IDD = IDD_VIEW_STYLES };
	BOOL	m_bNumElems;
	BOOL	m_bNumKnots;
	BOOL	m_bTextOut;
	CString	m_strFreeFont;
	CString	m_strNumElems;
	CString	m_strNumKnots;
	double	m_ZeroRot;
	//}}AFX_DATA

	COLORREF m_clrFree, m_clrNumElems, m_clrNumKnots;
	LOGFONT m_lfFree, m_lfNumElems, m_lfNumKnots;
	bool m_bFreeFontModified, m_bNumElemsFontModified,m_bNumKnotsFontModified;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewStyles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewStyles)
	afx_msg void OnButtonFreeFont();
	afx_msg void OnButtonNumElemsFont();
	afx_msg void OnButtonNumKnotsFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWSTYLES_H__92495FC3_3129_11D5_B89B_FE2BA355A53D__INCLUDED_)
