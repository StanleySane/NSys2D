// ComboBoxElem.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "ComboBoxElem.h"

//temp
//#include "resource.h"


#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboBoxElem

CComboBoxElem::CComboBoxElem()
{
	EnableAutomation();
}

CComboBoxElem::~CComboBoxElem()
{
}

void CComboBoxElem::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CComboBox::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CComboBoxElem, CComboBox)
	//{{AFX_MSG_MAP(CComboBoxElem)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CComboBoxElem, CComboBox)
	//{{AFX_DISPATCH_MAP(CComboBoxElem)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IComboBoxElem to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {704BE924-BC59-11D2-AF23-BB2B1C460D22}
static const IID IID_IComboBoxElem =
{ 0x704be924, 0xbc59, 0x11d2, { 0xaf, 0x23, 0xbb, 0x2b, 0x1c, 0x46, 0xd, 0x22 } };

BEGIN_INTERFACE_MAP(CComboBoxElem, CComboBox)
	INTERFACE_PART(CComboBoxElem, IID_IComboBoxElem, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBoxElem message handlers

void CComboBoxElem::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	CRect rect=lpDrawItemStruct->rcItem;
	SetItemHeight( 0, 18 );	

	CBitmap bitmap;
	char st[100];
	GetLBText(lpDrawItemStruct->itemID, st);

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		if (!strcmp(st,"IDB_BITMAP_1"))
			bitmap.LoadBitmap(IDB_BITMAP_1i);
		if (!strcmp(st,"IDB_BITMAP_2"))
			bitmap.LoadBitmap(IDB_BITMAP_2i);
		if (!strcmp(st,"IDB_BITMAP_3"))
			bitmap.LoadBitmap(IDB_BITMAP_3i);

		BITMAP bmp;
		bitmap.GetBitmap(&bmp);
		CSize sz(bmp.bmWidth,bmp.bmHeight);

		dc.DrawState(CPoint(rect.left,rect.top),sz,bitmap,DST_BITMAP);
	}
	else
	{
		BITMAP bmp;
		if (!strcmp(st,"IDB_BITMAP_1"))
			bitmap.LoadBitmap(IDB_BITMAP_1);
		if (!strcmp(st,"IDB_BITMAP_2"))
			bitmap.LoadBitmap(IDB_BITMAP_2);
		if (!strcmp(st,"IDB_BITMAP_3"))
			bitmap.LoadBitmap(IDB_BITMAP_3);
		
		bitmap.GetBitmap(&bmp);
		CSize sz(bmp.bmWidth,bmp.bmHeight);
		dc.DrawState(CPoint(rect.left,rect.top),sz,bitmap,DST_BITMAP);
	}//(rect.right-rect.left-100)/2,rect.top
	bitmap.DeleteObject();
	dc.Detach();
}
