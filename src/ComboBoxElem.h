#if !defined(AFX_COMBOBOXELEM_H__704BE925_BC59_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_COMBOBOXELEM_H__704BE925_BC59_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ComboBoxElem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComboBoxElem window

class CComboBoxElem : public CComboBox
{
// Construction
public:
	CComboBoxElem();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxElem)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );
	virtual ~CComboBoxElem();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboBoxElem)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CComboBoxElem)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOXELEM_H__704BE925_BC59_11D2_AF23_BB2B1C460D22__INCLUDED_)
