// GraphListBox.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "GraphListBox.h"

#include "GraphicView.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphListBox

CGraphListBox::CGraphListBox()
{
}

CGraphListBox::~CGraphListBox()
{
}


BEGIN_MESSAGE_MAP(CGraphListBox, CCheckListBox)
	//{{AFX_MSG_MAP(CGraphListBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphListBox message handlers

void CGraphListBox::DrawItem( CGraphData *pGr, CDC *pDC, const CRect &rect )
{
	CBrush br( pGr->m_Clr );
	CRect rectBitMap( rect ), rectText( rect );
	rectBitMap.right = rectBitMap.Height() + rectBitMap.left;
	rectBitMap.left += 1;
	rectBitMap.top += 1;
	rectBitMap.bottom -= 1;
	rectText.left += rectText.Height();
	pDC->FillRect( &rectBitMap, &br );
	CString str;
	str.Format("%.16g", pGr->m_Scale );
	str = pGr->m_strCaption + CString(_T(" (*")) + str + CString(_T(")"));
	str += _T("{") + pGr->m_strFileName + _T("}");
	pDC->DrawText( str, rectText, DT_LEFT );
}

void CGraphListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC *pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
	CGraphData *pGr = reinterpret_cast<CGraphData*>(lpDrawItemStruct->itemData);
	if( lpDrawItemStruct->itemAction & ODA_DRAWENTIRE )
	{
		CRect rect( lpDrawItemStruct->rcItem );
		DrawItem( pGr, pDC, rect );
	}
	if( (lpDrawItemStruct->itemState & ODS_SELECTED)&&
		(lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)) )
	{
		// Выделение рамки если запись выделена
	    CBrush br(RGB(0,0,0));
		pDC->FrameRect( &lpDrawItemStruct->rcItem, &br );
	}
	if( !(lpDrawItemStruct->itemState & ODS_SELECTED) &&
		(lpDrawItemStruct->itemAction & ODA_SELECT) )
	{
		// Удаление рамки если выделение с записи списка снято
		CRect rect( lpDrawItemStruct->rcItem );
		DrawItem( pGr, pDC, rect );
	    CBrush br(RGB(255,255,255));
		pDC->FrameRect( &lpDrawItemStruct->rcItem, &br );
	}	
}

void CGraphListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your code to determine the size of specified item
	lpMeasureItemStruct->itemHeight = 40;
}

void CGraphListBox::Fill( CGraphicView *pView )
{
	ASSERT(pView);
	ResetContent();
	GraphList::iterator beg = pView->m_Graphs.begin(), fin = pView->m_Graphs.end();
	for( GraphList::iterator it = beg; it != fin; ++it )
	{
		AddString( reinterpret_cast<LPCTSTR>(&(*it)) );
		SetCheck( distance(beg,it), (*it).m_bEnable );
	}
}

int CGraphListBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct) 
{
	// TODO: Add your code to determine the sorting order of the specified items
	// return -1 = item 1 sorts before item 2
	// return 0 = item 1 and item 2 sort the same
	// return 1 = item 1 sorts after item 2
	
	return 0;
}
