// KnotPtr.cpp: implementation of the KnotPtr class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "KnotPtr.h"

#include "Knot.h"

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

bool KnotPtr::Construct()
{
	if( m_pKnot == NULL )
	{
		try
		{
			m_pKnot = new CKnot();
		}
		catch( bad_alloc& )
		{
			m_pKnot = NULL;
			return false;
		}
		AddRef( m_pKnot );
	}
	return true;
}

bool KnotPtr::Attach( CKnot *p )
{
	ASSERT(p);
	Destruct();
	m_pKnot = p;
	AddRef( m_pKnot );
	return true;
}

bool KnotPtr::Detach()
{
	if( m_pKnot == NULL )
		return false;
	Destruct();
	return true;
}

bool KnotPtr::RemoveRef( CKnot *pKn )
{
//ф-ция возвращает ИСТИНУ, если указатель уже можно удалять, 
//т.е. если на него никто не ссылается.
	if( pKn != NULL )
	{
		Refs::iterator it = m_RefMap.find(pKn);
		ASSERT( it != m_RefMap.end() );
		(*it).second--;
		if( (*it).second != 0 )	return false;
		m_RefMap.erase(it);
	}
	return true;
}

bool KnotPtr::AddRef( CKnot *pKn )
{
//ф-ция возвращает ИСТИНУ, только если такого указателя ещё не было
//и ссылка на него успешно установлена в 1.
//если же указатель нулевой (тогда вообще ничего не происходит)
//или такой указатель уже есть в карте (тогда инкрементируется счётчик ссылок на него),
//то вернётся ЛОЖЬ.
	if( pKn != NULL )
	{
		Pair p = m_RefMap.insert( MakeRef(pKn,1) );
		if( p.second )	return true;
		//значит такой указатель уже есть
		++(*p.first).second;
	}
	return false;
}

void KnotPtr::Destruct()
{
	if( m_pKnot )
	{
		if( RemoveRef(m_pKnot) )
		{
			delete m_pKnot;
			m_pKnot = NULL;
		}
	}
}

void KnotPtr::InitBy( const KnotPtr &obj )
{
	if( m_pKnot != obj.m_pKnot )
	{
		if( m_pKnot )
			Destruct();
		m_pKnot = obj.m_pKnot;
		if( m_pKnot )
		{
			bool res = AddRef( m_pKnot );
			ASSERT( res == false );
			//Refs::iterator it = m_RefMap.find(m_pKnot);
			//ASSERT( it != m_RefMap.end() );
			//(*it).second++;
		}
	}
}

CKnot* KnotPtr::GetKnot() const
{
	ASSERT(m_pKnot);
	return m_pKnot;
}

bool KnotPtr::Create( double x, double y )
{
	if( !Construct() )
		return false;
	return (m_pKnot->SetCoord(x,y) == 1)?true:false;
}