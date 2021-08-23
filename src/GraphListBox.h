#if !defined(AFX_GRAPHLISTBOX_H__2DF2E5A3_9BFE_11D6_B89E_FE2BA355A53D__INCLUDED_)
#define AFX_GRAPHLISTBOX_H__2DF2E5A3_9BFE_11D6_B89E_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GraphListBox.h : header file
//
class CGraphData;
class CGraphicView;
/////////////////////////////////////////////////////////////////////////////
// CGraphListBox window

class CGraphListBox : public CCheckListBox
{
// Construction
public:
	CGraphListBox();

// Attributes
public:

// Operations
public:
	void DrawItem( CGraphData*, CDC*, const CRect& );
	void Fill( CGraphicView* );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGraphListBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHLISTBOX_H__2DF2E5A3_9BFE_11D6_B89E_FE2BA355A53D__INCLUDED_)
