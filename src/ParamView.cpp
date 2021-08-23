// ParamView.cpp: implementation of the CParamView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "ParamView.h"

#include "StdAfxMy.h"

#include "Sheme.h"
#include "Elem.h"

#include<algorithm>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

double CParamView::m_DefaultScale = 5;

//CArchive& operator <<( CArchive &, LOGFONT & );
//CArchive& operator >>( CArchive &, LOGFONT & );
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

void CParamView::Serialize( CArchive &ar, int _sv )
{
	ShemeVersion sv = static_cast<ShemeVersion>(_sv);
	if (ar.IsStoring())
	{	// storing code
		ar << Scale << pos.x << pos.y;
		ar << MoveCenter.x << MoveCenter.y;
		if( sv >= VER_EQ31 )
		{
			ar << m_bNumKnots << m_bNumElems << m_bTextOut;
			/*
			LOGFONT lf;
			m_fntKnot.GetLogFont( &lf );
			ar << lf;
			m_fntElems.GetLogFont( &lf );
			ar << lf;
			m_fntFree.GetLogFont( &lf );
			ar << lf;
			*/
			ar << m_clrNumKnots;
			ar << m_clrNumElems;
			ar << m_clrFree;
			ar << m_ZeroRot;
		}
	}
	else
	{	// loading code
		ar >> Scale >> pos.x >> pos.y;
		ar >> MoveCenter.x >> MoveCenter.y;
		if( sv >= VER_EQ31 )
		{
			int nk, ne, to;
			ar >> nk >> ne >> to;
			m_bNumKnots = (nk != 0);
			m_bNumElems = (ne != 0);
			m_bTextOut = (to != 0);
			/*
			LOGFONT lf;
			m_fntKnot.GetLogFont( &lf );
			ar >> lf;
			m_fntKnot.CreateFontIndirect( lf );
			ar >> lf;
			m_fntElems.CreateFontIndirect( &lf );
			ar >> lf;
			m_fntFree.CreateFontIndirect( &lf );
			*/
			ar >> m_clrNumKnots;
			ar >> m_clrNumElems;
			ar >> m_clrFree;
			ar >> m_ZeroRot;
		}
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

/*
CArchive& operator <<( CArchive &ar, LOGFONT &lf )
{
	ar << lf.lfHeight << lf.lfWidth << lf.lfEscapement << lf.lfOrientation;
	ar << lf.lfWeight << lf.lfItalic << lf.lfUnderline << lf.lfStrikeOut;
	ar << lf.lfCharSet << lf.lfOutPrecision << lf.lfClipPrecision << lf.lfQuality;
	ar << lf.lfPitchAndFamily;
	CString str(lf.lfFaceName);
	ar << str;
	return ar;
}

CArchive& operator >>( CArchive &ar, LOGFONT &lf )
{
	ar >> lf.lfHeight >> lf.lfWidth >> lf.lfEscapement >> lf.lfOrientation;
	ar >> lf.lfWeight >> lf.lfItalic >> lf.lfUnderline >> lf.lfStrikeOut;
	ar >> lf.lfCharSet >> lf.lfOutPrecision >> lf.lfClipPrecision >> lf.lfQuality;
	ar >> lf.lfPitchAndFamily;
	CString str;
	ar >> str;
	strncpy( lf.lfFaceName, str.LockBuffer(), LF_FACESIZE );
	str.UnlockBuffer();
	return ar;
}
*/