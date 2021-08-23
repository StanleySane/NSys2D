// ParamIntegr.cpp: implementation of the CParamIntegr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "ParamIntegr.h"

#include "Sheme.h"
#include "Elem.h"

using namespace std;

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
	Time = 10.0;
	Step = 0.1;
	TypeMethod=1;

//	strTime=_T("10");
//	strStep=_T("0.1");
}

CParamIntegr::~CParamIntegr()
{

}

void CParamIntegr::Serialize( CArchive &ar, int _sv )
{
	ShemeVersion sv = static_cast<ShemeVersion>(_sv);
	if (ar.IsStoring())
	{	// storing code
		if( sv <= VER_EQ30 )
		{
			CString strTime, strStep;
			strTime.Format("%.16g", Time );
			strStep.Format("%.16g", Step );
			ar << strTime << strStep;
		}
		ar << Time << Step;
		ar << TypeMethod;
	}
	else
	{	// loading code
		if( sv <= VER_EQ30 )
		{
			CString strTime, strStep;
			ar >> strTime >> strStep;
		}
		ar >> Time >> Step;
		ar >> TypeMethod;
	}
}
