// ComboBox_FixedType.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "ComboBox_FixedType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboBox_FixedType

CComboBox_FixedType::CComboBox_FixedType()
{
	EnableAutomation();
}

CComboBox_FixedType::~CComboBox_FixedType()
{
}

void CComboBox_FixedType::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CComboBox::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CComboBox_FixedType, CComboBox)
	//{{AFX_MSG_MAP(CComboBox_FixedType)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CComboBox_FixedType, CComboBox)
	//{{AFX_DISPATCH_MAP(CComboBox_FixedType)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IComboBox_FixedType to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {A9AC9423-C7EA-11D2-AF23-BB2B1C460D22}
static const IID IID_IComboBox_FixedType =
{ 0xa9ac9423, 0xc7ea, 0x11d2, { 0xaf, 0x23, 0xbb, 0x2b, 0x1c, 0x46, 0xd, 0x22 } };

BEGIN_INTERFACE_MAP(CComboBox_FixedType, CComboBox)
	INTERFACE_PART(CComboBox_FixedType, IID_IComboBox_FixedType, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBox_FixedType message handlers

void CComboBox_FixedType::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	SetItemHeight( 0, 22 );	
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
	int rad=3,i;
	switch (lpDrawItemStruct->itemID)
	{
	
	case 0: 
			//разрешены все перемещения
			break;
	case 1: 
			//запрещён Y
			dc.MoveTo(center_x,center_y-6);
			dc.LineTo(center_x,center_y+6);
			
			dc.MoveTo(center_x-8,center_y+5);
			dc.LineTo(center_x+8,center_y+5);

			dc.SelectObject(&pen1);
			
			for(i=0;i<6;i++)
			{
				dc.MoveTo(center_x-7+3*i,center_y+5);
				dc.LineTo(center_x-7+3*i-3,center_y+9);
			}
			
			dc.Ellipse(center_x-rad,center_y-7,
					center_x+rad,center_y-7+2*rad);

			dc.Ellipse(center_x-rad,center_y+5-rad,
					center_x+rad,center_y+5+rad);
			
			dc.SelectObject(&pen2);

			break;
	case 2: 
			//запрещён X
			dc.MoveTo(center_x-6,center_y);
			dc.LineTo(center_x+6,center_y);
			
			dc.MoveTo(center_x+5,center_y-8);
			dc.LineTo(center_x+5,center_y+8);

			dc.SelectObject(&pen1);
			
			for(i=0;i<6;i++)
			{
				dc.MoveTo(center_x+5,center_y-7+3*i);
				dc.LineTo(center_x+9,center_y-7+3*i-3);
			}
			
			dc.Ellipse(center_x-7,center_y-rad,
					center_x-7+2*rad,center_y+rad);

			dc.Ellipse(center_x+5-rad,center_y-rad,
					center_x+5+rad,center_y+rad);
			
			dc.SelectObject(&pen2);

			break;
	case 3: 
			//запрещены X,Y разрешён только FI
			dc.MoveTo(center_x-10,center_y+5);
			dc.LineTo(center_x+10,center_y+5);

			dc.MoveTo(center_x,center_y-5);
			dc.LineTo(center_x-5,center_y+5);
			
			dc.MoveTo(center_x,center_y-5);
			dc.LineTo(center_x+5,center_y+5);

			dc.SelectObject(&pen1);
			
			for(i=0;i<7;i++)
			{
				dc.MoveTo(center_x-8+3*i,center_y+5);
				dc.LineTo(center_x-8+3*i-3,center_y+9);
			}

			dc.Ellipse(center_x-rad,center_y-5-rad,
					center_x+rad,center_y-5+rad);

			dc.SelectObject(&pen2);

			break;
	case 4:
			//заделка - все перемещения запрещены
			dc.MoveTo(center_x-10,center_y);
			dc.LineTo(center_x+10,center_y);

			dc.SelectObject(&pen1);
			
			for(i=0;i<7;i++)
			{
				dc.MoveTo(center_x-8+3*i,center_y);
				dc.LineTo(center_x-8+3*i-3,center_y+4);
			}

//			dc.Ellipse(center_x-rad,center_y-5-rad,
//					center_x+rad,center_y-5+rad);

			break;
	case 5:
		{
			//запрещён только поворот
			dc.SelectObject(&pen1);
			int tmp = 2*rad, rad2 = 2;
			CPoint pl[3] = { CPoint( center_x-rad2, center_y-rad2 ),
							CPoint( center_x-rad2, center_y-tmp ),
							CPoint( center_x-tmp, center_y-rad2 ) };
			dc.Polygon( pl, 3 );
			pl[0] = CPoint( center_x+rad2, center_y-rad2 );
			pl[1] = CPoint( center_x+rad2, center_y-tmp );
			pl[2] = CPoint( center_x+tmp, center_y-rad2 );
			dc.Polygon( pl, 3 );
			pl[0] = CPoint( center_x-rad2, center_y+rad2 );
			pl[1] = CPoint( center_x-rad2, center_y+tmp );
			pl[2] = CPoint( center_x-tmp, center_y+rad2 );
			dc.Polygon( pl, 3 );
			pl[0] = CPoint( center_x+rad2, center_y+rad2 );
			pl[1] = CPoint( center_x+rad2, center_y+tmp );
			pl[2] = CPoint( center_x+tmp, center_y+rad2 );
			dc.Polygon( pl, 3 );
			/*
			dc.MoveTo(center_x-5,center_y+3);
			dc.LineTo(center_x+3,center_y-5);
			
			dc.MoveTo(center_x-3,center_y+5);
			dc.LineTo(center_x+5,center_y-3);
			*/
		}
		break;
	case 6:
		{
			//запрещены Y,FI разрешён только X
			dc.MoveTo(center_x-8,center_y+5);
			dc.LineTo(center_x+8,center_y+5);

			CPen pen3( PS_SOLID|PS_GEOMETRIC, 3,
				(selMode?GetSysColor(COLOR_HIGHLIGHTTEXT):GetSysColor(COLOR_WINDOWTEXT)) );	
			dc.SelectObject( &pen3 );

			dc.MoveTo(center_x,center_y-1);
			dc.LineTo(center_x,center_y+6);			

			dc.SelectObject(&pen1);
			
			for(i=0;i<6;i++)
			{
				dc.MoveTo(center_x-7+3*i,center_y+5);
				dc.LineTo(center_x-7+3*i-3,center_y+9);
			}
			int tmp = 2*rad, rad2 = 2, y = center_y - 4;
			CPoint pl[3] = { CPoint( center_x-rad2, y-rad2 ),
							CPoint( center_x-rad2, y-tmp ),
							CPoint( center_x-tmp, y-rad2 ) };
			dc.Polygon( pl, 3 );
			pl[0] = CPoint( center_x+rad2, y-rad2 );
			pl[1] = CPoint( center_x+rad2, y-tmp );
			pl[2] = CPoint( center_x+tmp, y-rad2 );
			dc.Polygon( pl, 3 );
			pl[0] = CPoint( center_x-rad2, y+rad2 );
			pl[1] = CPoint( center_x-rad2, y+tmp );
			pl[2] = CPoint( center_x-tmp, y+rad2 );
			dc.Polygon( pl, 3 );
			pl[0] = CPoint( center_x+rad2, y+rad2 );
			pl[1] = CPoint( center_x+rad2, y+tmp );
			pl[2] = CPoint( center_x+tmp, y+rad2 );
			dc.Polygon( pl, 3 );

			dc.Ellipse(center_x-rad,center_y+5-rad,
					center_x+rad,center_y+5+rad);
		}
		break;
	case 7:
		{
			//запрещены X,FI разрешён только Y
			dc.MoveTo(center_x+5,center_y-8);
			dc.LineTo(center_x+5,center_y+8);

			CPen pen3( PS_SOLID|PS_GEOMETRIC, 3,
				(selMode?GetSysColor(COLOR_HIGHLIGHTTEXT):GetSysColor(COLOR_WINDOWTEXT)) );	
			dc.SelectObject( &pen3 );

			dc.MoveTo(center_x-4,center_y);
			dc.LineTo(center_x+6,center_y);			

			dc.SelectObject(&pen1);
			
			for(i=0;i<6;i++)
			{
				dc.MoveTo(center_x+5,center_y-7+3*i);
				dc.LineTo(center_x+9,center_y-7+3*i-3);
			}
			int tmp = 2*rad, rad2 = 2;
			CPoint pl[3] = { CPoint( center_x-7-rad2, center_y-rad2 ),
							CPoint( center_x-7-rad2, center_y-tmp ),
							CPoint( center_x-7-tmp, center_y-rad2 ) };
			dc.Polygon( pl, 3 );
			pl[0] = CPoint( center_x-7+rad2, center_y-rad2 );
			pl[1] = CPoint( center_x-7+rad2, center_y-tmp );
			pl[2] = CPoint( center_x-7+tmp, center_y-rad2 );
			dc.Polygon( pl, 3 );
			pl[0] = CPoint( center_x-7-rad2, center_y+rad2 );
			pl[1] = CPoint( center_x-7-rad2, center_y+tmp );
			pl[2] = CPoint( center_x-7-tmp, center_y+rad2 );
			dc.Polygon( pl, 3 );
			pl[0] = CPoint( center_x-7+rad2, center_y+rad2 );
			pl[1] = CPoint( center_x-7+rad2, center_y+tmp );
			pl[2] = CPoint( center_x-7+tmp, center_y+rad2 );
			dc.Polygon( pl, 3 );

			dc.Ellipse(center_x+5-rad,center_y-rad,
					center_x+5+rad,center_y+rad);			
		}
		break;
	default:
		ASSERT(FALSE);
	}

	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldpen);
	dc.Detach();
/*	CBitmap bitmap;
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
	bitmap.DeleteObject();*/
}
