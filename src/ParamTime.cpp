// ParamTime.cpp: implementation of the CParamTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "ParamTime.h"

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

CParamTime::CParamTime()
{
//	strT0=_T("0");	
//	strT1=_T("10");	
//	strdT=_T("0.1");
	T0 = 0.0;
	T1 = 10.0;
	dT = 0.1;
}

CParamTime::~CParamTime()
{

}

void CParamTime::Serialize( CArchive &ar, int _sv )
{
	ShemeVersion sv = static_cast<ShemeVersion>(_sv);
	if (ar.IsStoring())
	{	// storing code
		if( sv <= VER_EQ30 )
		{
			CString str;
			str.Format("%.16g", T0 );
			ar << str;
			str.Format("%.16g", T1 );
			ar << str;
			str.Format("%.16g", dT );
			ar << str;
		}
		ar << T0 << T1 << dT;
	}
	else
	{	// loading code
		if( sv <= VER_EQ30 )
		{
			CString strT0, strT1, strdT;
			ar >> strT0 >> strT1 >> strdT;
		}
		ar >> T0 >> T1 >> dT;
	}
}
