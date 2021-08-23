// HardRodPtr.cpp: implementation of the HardRodPtr class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "HardRodPtr.h"

#include "HardRod.h"
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

bool HardRodPtr::Construct( KnotPtr *kn1, KnotPtr *kn2 )
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
			m_pElem = new CHardRod( pkn1, pkn2 );
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

bool HardRodPtr::Attach( CElem *pEl )
{
//ф-ция присоединяет к объекту указатель на элемент.
//после удачного выполнения этой ф-ции данный объект
//и присоединённый элемент - одно и то же.
	ASSERT( (pEl != NULL)&&(pEl->TypeElem == IDC_HARDROD) );
	ASSERT( (pEl->knot1 != NULL)&&(pEl->knot2 != NULL) );
	Destruct();
	m_pElem = static_cast<CHardRod*>(pEl);
	Pair p = m_RefMap.insert( MakeRef(m_pElem,1) );
	if( p.second == false )
		++(*p.first).second;
	KnotPtr::AddRef( pEl->knot1 );
	KnotPtr::AddRef( pEl->knot2 );
	return true;
}

bool HardRodPtr::Detach()
{
//ф-ция отсоединяет от данного объекта указатель на элемент.
	if( m_pElem == NULL )
		return false;
	Destruct();
	return true;
}

void HardRodPtr::Destruct()
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

void HardRodPtr::InitBy( const HardRodPtr &obj )
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

CElem* HardRodPtr::GetElem() const
{
	ASSERT(m_pElem);
	return m_pElem;
}

bool HardRodPtr::Create( KnotPtr *kn1, KnotPtr *kn2 )
{
	if( !Construct( kn1, kn2 ) )	return false;
	return true;
}

bool HardRodPtr::SetM( double v )
{
	if( m_pElem == NULL )	return false;
	return m_pElem->SetM( v );
}

bool HardRodPtr::SetJ( double v )
{
	if( m_pElem == NULL )	return false;
	return m_pElem->SetJ( v );
}

bool HardRodPtr::SetF( double v )
{
	if( m_pElem == NULL )	return false;
	return m_pElem->SetF( v );
}

bool HardRodPtr::SetE( double v )
{
	if( m_pElem == NULL )	return false;
	return m_pElem->SetE( v );
}

double HardRodPtr::GetM() const
{
	if( m_pElem == NULL )	return -1.0;
	return m_pElem->GetM();
}

double HardRodPtr::GetJ() const
{
	if( m_pElem == NULL )	return -1.0;
	return m_pElem->GetJ();
}

double HardRodPtr::GetF() const
{
	if( m_pElem == NULL )	return -1.0;
	return m_pElem->GetF();
}

double HardRodPtr::GetE() const
{
	if( m_pElem == NULL )	return -1.0;
	return m_pElem->GetE();
}

double HardRodPtr::GetLength() const
{
	if( m_pElem == NULL )	return -1.0;
	return m_pElem->GetLength();
}

AlgolMatr HardRodPtr::GetMatrM() const
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

AlgolMatr HardRodPtr::GetMatrD() const
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

AlgolMatr HardRodPtr::GetMatrC() const
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

int HardRodPtr::GetRefCount()
{
	if( m_pElem == NULL )
		return -1;
	HardRodPtr::Refs::iterator it = HardRodPtr::m_RefMap.find(m_pElem);
	if( it == HardRodPtr::m_RefMap.end() )
		return -1;
	return (*it).second;
}
