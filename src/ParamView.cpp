// ParamView.cpp: implementation of the CParamView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "ParamView.h"

#include<algorithm>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

double CParamView::m_DefaultScale = 5;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParamView::CParamView(double scale/*=2*/, 
					   CCoordD &coord/*=CCoordD(0,0)*/) 
{
	Scale = scale;
	MoveCenter=coord;
	pos=CPoint(0,0);
	
	MultMove=0;
	MultAngl=0;
	Gray=false;

	m_bTextOut = false;
	m_bNumKnots = true;
	m_bNumElems = true;

	m_fntKnot.CreatePointFont(100,_T("Arial"), 0);//MS Sans Serif//75
	m_fntElems.CreatePointFont(80,_T("Arial"), 0);
	m_fntFree.CreatePointFont(100,_T("Times New Roman"), 0);//MS Sans Serif
	m_strFreeFontName = CString("Times New Roman , 10");
	m_strNumElemsFontName = CString("Arial , 8");
	m_strNumKnotsFontName = CString("Arial , 10");

	m_clrNumKnots = m_clrFree = RGB(0,0,0);
	m_clrNumElems = RGB(192,192,192);

	m_bSelType = true;
	m_vecSelNumbers.clear();

	m_iClickedObjects = 0;

	m_ZeroRot = 1e-5;

	m_bFreeNums = false;
}

CParamView::~CParamView()
{
	m_fntKnot.DeleteObject();
	m_fntElems.DeleteObject();
	m_fntFree.DeleteObject();
}

void CParamView::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << Scale << pos.x << pos.y;
		ar << MoveCenter.x << MoveCenter.y;
	}
	else
	{	// loading code
		ar >> Scale >> pos.x >> pos.y;
		ar >> MoveCenter.x >> MoveCenter.y;
	}
}

void CParamView::DelZeroInSelNumbers()
{
	ARRAY::iterator it;
	it = std::find( m_vecSelNumbers.begin(), 
				m_vecSelNumbers.end(), 0 );
	if( it != m_vecSelNumbers.end() )// по идее всегда должно выполняться, но мало ли...
		m_vecSelNumbers.erase( it );
}
