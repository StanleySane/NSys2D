// ComboBox_ConnectType.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "ComboBox_ConnectType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboBox_ConnectType

CComboBox_ConnectType::CComboBox_ConnectType()
{
	EnableAutomation();
}

CComboBox_ConnectType::~CComboBox_ConnectType()
{
}

void CComboBox_ConnectType::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CComboBox::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CComboBox_ConnectType, CComboBox)
	//{{AFX_MSG_MAP(CComboBox_ConnectType)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CComboBox_ConnectType, CComboBox)
	//{{AFX_DISPATCH_MAP(CComboBox_ConnectType)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IComboBox_ConnectType to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {56B2DD22-C98D-11D2-AF23-BB2B1C460D22}
static const IID IID_IComboBox_ConnectType =
{ 0x56b2dd22, 0xc98d, 0x11d2, { 0xaf, 0x23, 0xbb, 0x2b, 0x1c, 0x46, 0xd, 0x22 } };

BEGIN_INTERFACE_MAP(CComboBox_ConnectType, CComboBox)
	INTERFACE_PART(CComboBox_ConnectType, IID_IComboBox_ConnectType, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBox_ConnectType message handlers
void CComboBox_ConnectType::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	SetItemHeight( 0, 18 );	
	CRect rect=lpDrawItemStruct->rcItem;

	BOOL selMode=lpDrawItemStruct->itemState & ODS_SELECTED;
	GetSysColor(COLOR_HIGHLIGHTTEXT);

	CPen pen1(PS_SOLID|PS_GEOMETRIC,1,
		(selMode?GetSysColor(COLOR_HIGHLIGHTTEXT):GetSysColor(COLOR_WINDOWTEXT)) );	
	CPen pen2(PS_SOLID|PS_GEOMETRIC,2,
		(selMode?GetSysColor(COLOR_HIGHLIGHTTEXT):GetSysColor(COLOR_WINDOWTEXT)) );	
	CBrush brush(selMode?GetSysColor(COLOR_HIGHLIGHT):GetSysColor(COLOR_WINDOW));


	CPen *pOldpen=(CPen*)dc.SelectObject(&pen2);
	CBrush *pOldBrush=(CBrush*)dc.SelectObject(&brush);

	LONG center_x=(rect.left+rect.right)/2;
	LONG center_y=(rect.top+rect.bottom)/2;

	dc.FillRect(&rect,&brush);

	switch (lpDrawItemStruct->itemID)
	{
	case 0: 
			dc.MoveTo(rect.left+10,center_y);
			dc.LineTo(center_x-2,center_y);

			dc.MoveTo(center_x+2,center_y);
			dc.LineTo(rect.right-10,center_y);

			dc.MoveTo(center_x-5,center_y-3);
			dc.LineTo(center_x+5,center_y-3);

			dc.MoveTo(center_x-5,center_y+3);
			dc.LineTo(center_x+5,center_y+3);
			break;
	case 1:
			int rad=3;
			dc.MoveTo(rect.left+10,center_y);
			dc.LineTo(center_x-rad,center_y);

			dc.MoveTo(center_x+rad,center_y);
			dc.LineTo(rect.right-10,center_y);

			dc.SelectObject(&pen1);
			dc.Ellipse(center_x-rad,center_y-rad,
					center_x+rad,center_y+rad);
			dc.SelectObject(&pen2);
			break;
	}
	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldpen);
	dc.Detach();
}
