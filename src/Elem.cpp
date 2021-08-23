// Elem.cpp: implementation of the CElem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "Elem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CElem::CElem(CKnot *kn1, CKnot *kn2)
{
	knot1=kn1; knot2=kn2;
	SelectMode=OldMode=0;
	m_Number = 0;
}

CElem::~CElem()
{

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
	double ang=GetAng();
	double dd=1;
	double M_PI=acos(-1);
	if (cos(ang)==-1) 
	{	ang-=M_PI;  dd=-1;	}

	V.ClearData();
	if (size==6)
	{
		V[0][0]=cos(ang);		
		V[0][1]=sin(ang);
		V[1][1]=cos(ang);
		V[1][0]=-sin(ang);
		V[2][2]=dd;
		V[3][3]=cos(ang);
		V[3][4]=sin(ang);	
		V[4][4]=cos(ang);
		V[4][3]=-sin(ang);	
		V[5][5]=dd;
	}
	if (size==4)
	{
		V[0][0]=cos(ang);		
		V[0][1]=sin(ang);
		V[1][1]=cos(ang);
		V[1][0]=-sin(ang);

		V[2][2]=cos(ang);
		V[2][3]=sin(ang);	
		V[3][3]=cos(ang);
		V[3][2]=-sin(ang);	
	}
	if (size==3)
	{
		V[0][0]=cos(ang);		
		V[0][1]=sin(ang);
		V[1][1]=cos(ang);
		V[1][0]=-sin(ang);
		V[2][2]=dd;
	}
	if (size==2)
	{
		V[0][0]=cos(ang);		
		V[0][1]=sin(ang);
		V[1][1]=cos(ang);
		V[1][0]=-sin(ang);
	}
}

int CElem::SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, int i, double Tt)
{
	return 0;
}

void CElem::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{	// storing code
//		ar << TypeElem;
		knot1->Serialize(ar);
		knot2->Serialize(ar);
	}
	else
	{	// loading code
//		int TypeElem;
//		ar >> TypeElem;
		knot1=new CKnot;
		knot2=new CKnot;
		knot1->Serialize(ar);
		knot2->Serialize(ar);
	}
}
