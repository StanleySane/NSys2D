#if !defined(AFX_COMBOBOX_FIXEDTYPE_H__A9AC9424_C7EA_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_COMBOBOX_FIXEDTYPE_H__A9AC9424_C7EA_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ComboBox_FixedType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComboBox_FixedType window

class CComboBox_FixedType : public CComboBox
{
// Construction
public:
	CComboBox_FixedType();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBox_FixedType)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual ~CComboBox_FixedType();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboBox_FixedType)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CComboBox_FixedType)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOX_FIXEDTYPE_H__A9AC9424_C7EA_11D2_AF23_BB2B1C460D22__INCLUDED_)
