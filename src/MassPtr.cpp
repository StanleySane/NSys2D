// MassPtr.cpp: implementation of the MassPtr class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "MassPtr.h"

#include "Mass.h"
#include "KnotPtr.h"
#include "AlgolMatr.h"

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

bool MassPtr::Construct( KnotPtr *kn )
{
	if( m_pElem == NULL )
	{
		CKnot *pkn = kn->GetKnot();
		if( pkn == NULL )	
			return false;
		try
		{
			m_pElem = new CMass( pkn );
		}
		catch( bad_alloc& )
		{
			m_pElem = NULL;
			return false;
		}
		Pair p = m_RefMap.insert( MakeRef(m_pElem,1) );
		if( p.second == false )
			++(*p.first).second;
		KnotPtr::AddRef( pkn );
	}
	return true;
}

void MassPtr::Destruct()
{
	if( m_pElem )
	{
		Refs::iterator it = m_RefMap.find(m_pElem);
		ASSERT( it != m_RefMap.end() );
		(*it).second--;
		KnotPtr::RemoveRef( m_pElem->knot1 );
		if( (*it).second == 0 )
		{
			delete m_pElem;
			m_pElem = NULL;
			m_RefMap.erase(it);
		}
	}
}

void MassPtr::InitBy( const MassPtr &obj )
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
		}
	}
}

CMass* MassPtr::GetElem() const
{
	ASSERT(m_pElem);
	return m_pElem;
}

bool MassPtr::Create( KnotPtr *kn )
{
	if( !Construct( kn ) )	return false;
	return true;
}

bool MassPtr::SetM( double v )
{
	if( m_pElem == NULL )	return false;
	CString str;
	str.Format("%g", v );
	return (m_pElem->SetMassM( str ) < 0)?false:true;
}

bool MassPtr::SetJ( double v )
{
	if( m_pElem == NULL )	return false;
	CString str;
	str.Format("%g", v );
	return (m_pElem->SetMassJp( str ) < 0)?false:true;
}

double MassPtr::GetM() const
{
	if( m_pElem == NULL )	return -1.0;
	return m_pElem->GetM();
}

double MassPtr::GetJ() const
{
	if( m_pElem == NULL )	return -1.0;
	return m_pElem->GetJp();
}

AlgolMatr MassPtr::GetMatrM() const
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

AlgolMatr MassPtr::GetMatrD() const
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

AlgolMatr MassPtr::GetMatrC() const
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
