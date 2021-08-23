// KnotPropertySheet.h : header file
//
// CKnotPropertySheet is a modeless property sheet that is 
// created once and not destroyed until the application
// closes.  It is initialized and controlled from
// CKnotPropertyFrame.
 
#ifndef __KNOTPROPERTYSHEET_H__
#define __KNOTPROPERTYSHEET_H__

#include "KnotPropertyPage1.h"
#include "Knot.h"

/////////////////////////////////////////////////////////////////////////////
// CKnotPropertySheet

class CKnotPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CKnotPropertySheet)

// Construction
public:
	CKnotPropertySheet(CKnot *pKn, 
					   CWnd* pWndParent);
// Attributes
public:
	CKnot	*pKnot;
	CKnotPropertyPage1 m_Page1;
	CKnotPropertyPage2 m_Page2;
	CKnotPropertyPage3 m_Page3;
	CKnotPropertyPage4 m_Page4;

	CListKnot	*pListKnot;
	CListSpectr *pListSpectr;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKnotPropertySheet)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CKnotPropertySheet();
	 virtual void PostNcDestroy();

// Generated message map functions
protected:
	//{{AFX_MSG(CKnotPropertySheet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __KNOTPROPERTYSHEET_H__
