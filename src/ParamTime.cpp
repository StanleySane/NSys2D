// ParamTime.cpp: implementation of the CParamTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "ParamTime.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParamTime::CParamTime()
{
	strT0=_T("0");		T0=0;
	strT1=_T("10");		T1=10;
	strdT=_T("0.1");	dT=0.1;
}

CParamTime::~CParamTime()
{

}

void CParamTime::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << strT0 << strT1 << strdT;
		ar << T0 << T1 << dT;
	}
	else
	{	// loading code
		ar >> strT0 >> strT1 >> strdT;
		ar >> T0 >> T1 >> dT;
	}
}
