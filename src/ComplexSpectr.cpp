// ComplexSpectr.cpp: implementation of the CComplexSpectr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "ComplexSpectr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComplexSpectr::CComplexSpectr( CSheme *p ):Sp(p)
{

}

CComplexSpectr::~CComplexSpectr()
{

}

BOOL CComplexSpectr::operator ==(CComplexSpectr & cs)
{
	if ( ((cs.pKn1==pKn1)&&(cs.pKn2==pKn2)&&(cs.Free1==Free1)&&(cs.Free2==Free2))||
		 ((cs.pKn2==pKn1)&&(cs.pKn1==pKn2)&&(cs.Free2==Free1)&&(cs.Free1==Free2)) )
			return true;		
	else	return false;
}

void CComplexSpectr::Serialize( CArchive &ar, int sv )
{
	if (ar.IsStoring())
	{	// storing code
		ar << Free1 << Free2;
		Sp.Serialize( ar, sv );
		pKn1->Serialize( ar, sv );
		pKn2->Serialize( ar, sv );
	}
	else
	{	// loading code
		ar >> Free1 >> Free2;
		Sp.Serialize( ar, sv );
		pKn1=new CKnot;
		pKn2=new CKnot;
		pKn1->Serialize( ar, sv );
		pKn2->Serialize( ar, sv );
	}
}
