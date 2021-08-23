// SpringPtr.cpp: implementation of the SpringPtr class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "SpringPtr.h"

#include "Spring.h"
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

bool SpringPtr::Construct( KnotPtr *kn1, KnotPtr *kn2 )
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
			m_pElem = new CSpring( pkn1, pkn2 );
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

bool SpringPtr::Attach( CElem *pEl )
{
//ф-ция присоединяет к объекту указатель на элемент.
//после удачного выполнения этой ф-ции данный объект
//и присоединённый элемент - одно и то же.
	ASSERT( (pEl != NULL)&&(pEl->TypeElem == IDC_SPRING) );
	ASSERT( (pEl->knot1 != NULL)&&(pEl->knot2 != NULL) );
	Destruct();
	m_pElem = static_cast<CSpring*>(pEl);
	Pair p = m_RefMap.insert( MakeRef(m_pElem,1) );
	if( p.second == false )
		++(*p.first).second;
	KnotPtr::AddRef( pEl->knot1 );
	KnotPtr::AddRef( pEl->knot2 );
	return true;
}

bool SpringPtr::Detach()
{
//ф-ция отсоединяет от данного объекта указатель на элемент.
	if( m_pElem == NULL )
		return false;
	Destruct();
	return true;
}

void SpringPtr::Destruct()
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

void SpringPtr::InitBy( const SpringPtr &obj )
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

CElem* SpringPtr::GetElem() const
{
	ASSERT(m_pElem);
	return m_pElem;
}

bool SpringPtr::Create( KnotPtr *kn1, KnotPtr *kn2 )
{
	if( !Construct( kn1, kn2 ) )	return false;
	return true;
}

double SpringPtr::GetLength() const
{
	if( m_pElem == NULL )	return 0.0;
	return m_pElem->GetLength();
}

AlgolMatr SpringPtr::GetMatrM() const
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

AlgolMatr SpringPtr::GetMatrD() const
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

AlgolMatr SpringPtr::GetMatrC() const
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

int SpringPtr::GetRefCount()
{
	if( m_pElem == NULL )
		return -1;
	SpringPtr::Refs::iterator it = SpringPtr::m_RefMap.find(m_pElem);
	if( it == SpringPtr::m_RefMap.end() )
		return -1;
	return (*it).second;
}
