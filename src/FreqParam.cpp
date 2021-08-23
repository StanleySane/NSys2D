// FreqParam.cpp: implementation of the CFreqParam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "FreqParam.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFreqParam::CFreqParam()
{
	strwBeg=_T("0");
	strwEnd=_T("5");
	strwStep=_T("0.005");
	LogCoord=false;
	Derive=0;
	TypeCharact=0;
	nFree1=0; 
	nFree2=0;
	typeFree1=0;
	typeFree2=0;
	pKnot1=0;
	pKnot2=0;
	typeForce=0;
}

CFreqParam::~CFreqParam()
{

}

void CFreqParam::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << TypeCharact << Derive;
		ar << LogCoord << typeFree1 << typeFree2;
		ar << strwBeg << strwEnd << strwStep;
		ar << typeForce;
	}
	else
	{	// loading code
		ar >> TypeCharact >> Derive;
		ar >> LogCoord >> typeFree1 >> typeFree2;
		ar >> strwBeg >> strwEnd >> strwStep;
		ar >> typeForce;
		pKnot1=0;
		pKnot2=0;
	}
}
