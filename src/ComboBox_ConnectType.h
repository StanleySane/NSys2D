#if !defined(AFX_COMBOBOX_CONNECTTYPE_H__56B2DD23_C98D_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_COMBOBOX_CONNECTTYPE_H__56B2DD23_C98D_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ComboBox_ConnectType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComboBox_ConnectType window

class CComboBox_ConnectType : public CComboBox
{
// Construction
public:
	CComboBox_ConnectType();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBox_ConnectType)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual ~CComboBox_ConnectType();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboBox_ConnectType)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CComboBox_ConnectType)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOX_CONNECTTYPE_H__56B2DD23_C98D_11D2_AF23_BB2B1C460D22__INCLUDED_)
