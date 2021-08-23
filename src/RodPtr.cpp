// RodPtr.cpp: implementation of the RodPtr class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "RodPtr.h"

#include "Rod.h"
#include "AlgolMatr.h"
//#include "CoordD.h"
#include "KnotPtr.h"

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
bool RodPtr::Construct( KnotPtr *kn1, KnotPtr *kn2 )
{
	if( m_pElem == NULL )
	{
		CKnot *pkn1 = kn1->GetKnot(), *pkn2 = kn2->GetKnot();
		if( (pkn1 == NULL)||(pkn2 == NULL) )	
			return false;
		if( pkn1->GetCoord() == pkn2->GetCoord() )
			return false;
		try
		{
			m_pElem = new CRod( pkn1, pkn2 );
		}
		catch( bad_alloc& )
		{
			m_pElem = NULL;
			return false;
		}
		Pair p = m_RefMap.insert( MakeRef(m_pElem,1) );
		if( p.second == false )
			++(*p.first).second;
		KnotPtr::AddRef( pkn1 );
		KnotPtr::AddRef( pkn2 );
	}
	return true;
}

void RodPtr::Destruct()
{
	if( m_pElem )
	{
		Refs::iterator it = m_RefMap.find(m_pElem);
		ASSERT( it != m_RefMap.end() );
		(*it).second--;
		KnotPtr::RemoveRef( m_pElem->knot1 );
		KnotPtr::RemoveRef( m_pElem->knot2 );
		if( (*it).second == 0 )
		{
			delete m_pElem;
			m_pElem = NULL;
			m_RefMap.erase(it);
		}
	}
}

void RodPtr::InitBy( const RodPtr &obj )
{
	if( m_pElem != obj.m_pElem )
	{
		if( m_pElem )
			Destruct();
		m_pElem = obj.m_pElem;
		if( m_pElem )
		{
			Refs::iterator it = m_RefMap.find(m_pElem);
			ASSERT( it != m_RefMap.end() );
			(*it).second++;
			KnotPtr::AddRef( m_pElem->knot1 );
			KnotPtr::AddRef( m_pElem->knot2 );
		}
	}
}

CRod* RodPtr::GetElem() const
{
	ASSERT(m_pElem);
	return m_pElem;
}

bool RodPtr::Create( KnotPtr *kn1, KnotPtr *kn2 )
{
	if( !Construct( kn1, kn2 ) )	return false;
	return true;
}

bool RodPtr::SetM( double v )
{
	if( m_pElem == NULL )	return false;
	CString str;
	str.Format("%g", v );
	return (m_pElem->SetM( str ) < 0)?false:true;
}

bool RodPtr::SetJ( double v )
{
	if( m_pElem == NULL )	return false;
	CString str;
	str.Format("%g", v );
	return (m_pElem->SetJx( str ) < 0)?false:true;
}

bool RodPtr::SetF( double v )
{
	if( m_pElem == NULL )	return false;
	CString str;
	str.Format("%g", v );
	return (m_pElem->SetF( str ) < 0)?false:true;
}

bool RodPtr::SetE( double v )
{
	if( m_pElem == NULL )	return false;
	CString str;
	str.Format("%g", v );
	return (m_pElem->SetE( str ) < 0)?false:true;
}

double RodPtr::GetM() const
{
	if( m_pElem == NULL )	return -1.0;
	return m_pElem->GetM();
}

double RodPtr::GetF() const
{
	if( m_pElem == NULL )	return -1.0;
	return m_pElem->GetF();
}

double RodPtr::GetE() const
{
	if( m_pElem == NULL )	return -1.0;
	return m_pElem->GetE();
}

double RodPtr::GetJ() const
{
	if( m_pElem == NULL )	return -1.0;
	return m_pElem->GetJx();
}

double RodPtr::GetLength() const
{
	if( m_pElem == NULL )	return 0.0;
	return m_pElem->GetLength();
}

AlgolMatr RodPtr::GetMatrM() const
{
	AlgolMatr am;
	if( m_pElem == NULL )
		return am;
	CMatr matr;
	m_pElem->GetMatrM( matr );
	matr.ConvertToAlgolMatr( am );
	am.SetMinCol(0);
	return am;
}

AlgolMatr RodPtr::GetMatrD() const
{
	AlgolMatr am;
	if( m_pElem == NULL )
		return am;
	CMatr matr;
	m_pElem->GetMatrD( matr );
	matr.ConvertToAlgolMatr( am );
	am.SetMinCol(0);
	return am;
}

AlgolMatr RodPtr::GetMatrC() const
{
	AlgolMatr am;
	if( m_pElem == NULL )
		return am;
	CMatr matr;
	m_pElem->GetMatrC( matr );
	matr.ConvertToAlgolMatr( am );
	am.SetMinCol(0);
	return am;
}
