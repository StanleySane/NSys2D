// ParamIntegr.cpp: implementation of the CParamIntegr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "ParamIntegr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParamIntegr::CParamIntegr()
{
	Time=10;
	Step=0.1;
	TypeMethod=1;

	strTime=_T("10");
	strStep=_T("0.1");
}

CParamIntegr::~CParamIntegr()
{

}

void CParamIntegr::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << strTime << strStep;
		ar << Time << Step;
		ar << TypeMethod;
	}
	else
	{	// loading code
		ar >> strTime >> strStep;
		ar >> Time >> Step;
		ar >> TypeMethod;
	}
}
