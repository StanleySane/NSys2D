// FreqParam.cpp: implementation of the CFreqParam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "FreqParam.h"

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

CFreqParam::CFreqParam()
{
	m_wBeg = 0.0;
	m_wEnd = 5.0;
	m_wStep = 0.005;

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

void CFreqParam::Serialize( CArchive &ar, int _sv )
{
	ShemeVersion sv = static_cast<ShemeVersion>(_sv);
	if (ar.IsStoring())
	{	// storing code
		ar << TypeCharact << Derive;
		ar << LogCoord << typeFree1 << typeFree2;
		if( sv <= VER_EQ30 )
		{
			CString str;
			str.Format("%.16g", m_wBeg);
			ar << str;
			str.Format("%.16g", m_wEnd);
			ar << str;
			str.Format("%.16g", m_wStep);
			ar << str;
		}
		else
		{
			ar << m_wBeg << m_wEnd << m_wStep;
		}
		ar << typeForce;
	}
	else
	{	// loading code
		ar >> TypeCharact >> Derive;
		ar >> LogCoord >> typeFree1 >> typeFree2;
		if( sv <= VER_EQ30 )
		{
			CString strwBeg, strwEnd, strwStep;
			ar >> strwBeg >> strwEnd >> strwStep;
			m_wBeg = atof( static_cast<LPCTSTR>(strwBeg) );
			m_wEnd = atof( static_cast<LPCTSTR>(strwEnd) );
			m_wStep = atof( static_cast<LPCTSTR>(strwStep) );
		}
		else
		{
			ar >> m_wBeg >> m_wEnd >> m_wStep;
		}
		ar >> typeForce;
		pKnot1 = NULL;
		pKnot2 = NULL;
	}
}
