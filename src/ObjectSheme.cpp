// ObjectSheme.cpp: implementation of the CObjectSheme class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "ObjectSheme.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CObjectSheme::CObjectSheme( CSheme *p ):m_pSheme(p)
{
}

CObjectSheme::~CObjectSheme()
{

}

CObjectSheme::CObjectSheme( const CObjectSheme &obj )
{
	m_pSheme = obj.m_pSheme;
}

CObjectSheme& CObjectSheme::operator=( const CObjectSheme &obj )
{
	if( this != (&obj) )
		m_pSheme = obj.m_pSheme;
	return *this;
}

POINT CObjectSheme::ShemeToScreen(CCoordD & coord, CParamView * pPV)
{
	POINT point;
	point.x=long( pPV->Scale*(coord.x-pPV->MoveCenter.x)+0.55555);//-pPV->pos.x;
	point.y=long(-pPV->Scale*(coord.y-pPV->MoveCenter.y)+0.55555);//+pPV->pos.y;
	return point;
}

void CObjectSheme::Serialize( CArchive &ar, int sv )
{

}
