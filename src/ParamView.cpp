// ParamView.cpp: implementation of the CParamView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "ParamView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParamView::CParamView(double scale/*=2*/, 
					   CCoordD &coord/*=CCoordD(0,0)*/) 
{
	Scale=scale;
	MoveCenter=coord;
	pos=CPoint(0,0);
	
	MultMove=0;
	MultAngl=0;
	Gray=false;
}

CParamView::~CParamView()
{

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
