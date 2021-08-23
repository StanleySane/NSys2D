// Elem.cpp: implementation of the CElem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "Elem.h"

#include "Sheme.h"

#include <cmath>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CElem::CElem( CKnot *kn1, CKnot *kn2, CSheme *p ):CObjectSheme(p)
{
	knot1=kn1; knot2=kn2;
	SelectMode=OldMode=0;
	m_Number = 0;
}

CElem::~CElem()
{

}

CElem::CElem( const CElem &elem ):CObjectSheme(elem)
{
	SelectMode = OldMode = 0;
	InitBy( elem );
}

CElem& CElem::operator=( const CElem &elem )
{
	if( this != (&elem) )
		InitBy( elem );
	return *this;
}

void CElem::InitBy( const CElem &elem )
{
	knot1 = elem.knot1;
	knot2 = elem.knot2;
	m_Number = elem.m_Number;
	TypeElem = elem.TypeElem;
}

void CElem::SetVarState()
{
	if( m_pSheme )
	{
		m_pSheme->m_VarsTable.SetVarValue("cx1",knot1->GetCoordX());
		m_pSheme->m_VarsTable.SetVarValue("cy1",knot1->GetCoordY());
		m_pSheme->m_VarsTable.SetVarValue("cx2",knot2->GetCoordX());
		m_pSheme->m_VarsTable.SetVarValue("cy2",knot2->GetCoordY());
	}
}

double CElem::GetLength() const
{
	return (knot1->GetCoord()-knot2->GetCoord()).GetNorm();
}

double CElem::GetAng() const
{
//	return (knot1->GetCoord()-knot2->GetCoord()).GetAng();
	return (knot2->GetCoord()-knot1->GetCoord()).GetAng();
}

double CElem::GetAngle() const
{
	return (knot2->GetCoord()-knot1->GetCoord()).GetAng();
}

void CElem::GetMatrT(CMatr & V, int size/*=6*/) const
{
	if( (size != 2)&&(size != 3)&&(size != 4)&&(size != 6) )
		return;
	double ang = GetAng();
	double dd = 1;
//	double M_PI=acos(-1);
	double ca = cos(ang), sa = sin(ang);
	if( ca == -1 ) 
	{	
		ang -= CNSys2DApp::M_PI;
		dd = -1.0;
	}

	V.ClearData();
	if (size==6)
	{
		V[0][0] = ca;		
		V[0][1] = sa;
		V[1][1] = ca;
		V[1][0] = -sa;
		V[2][2] = dd;
		V[3][3] = ca;
		V[3][4] = sa;	
		V[4][4] = ca;
		V[4][3] = -sa;	
		V[5][5] = dd;
	}
	if (size==4)
	{
		V[0][0] = ca;		
		V[0][1] = sa;
		V[1][1] = ca;
		V[1][0] = -sa;

		V[2][2] = ca;
		V[2][3] = sa;	
		V[3][3] = ca;
		V[3][2] = -sa;	
	}
	if (size==3)
	{
		V[0][0] = ca;		
		V[0][1] = sa;
		V[1][1] = ca;
		V[1][0] = -sa;
		V[2][2] = dd;
	}
	if (size==2)
	{
		V[0][0] = ca;		
		V[0][1] = sa;
		V[1][1] = ca;
		V[1][0] = -sa;
	}
}

void CElem::Serialize( CArchive &ar, int sv )
{
	if (ar.IsStoring())
	{	// storing code
//		ar << TypeElem;
		knot1->Serialize( ar, sv );
		knot2->Serialize( ar, sv );
	}
	else
	{	// loading code
//		int TypeElem;
//		ar >> TypeElem;
		knot1 = new CKnot(m_pSheme);
		knot2 = new CKnot(m_pSheme);
		knot1->Serialize( ar, sv );
		knot2->Serialize( ar, sv );
	}
}
