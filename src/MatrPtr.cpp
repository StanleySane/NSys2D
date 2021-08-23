// MatrPtr.cpp: implementation of the MatrPtr class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "MatrPtr.h"

#include "AlgolMatr.h"
#include "ValueHeader.h"

#include<new>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MatrPtr::MatrPtr( const AlgolMatr &m )
{
	m_pMatr = NULL;
	try
	{
		m_pMatr = new AlgolMatr( m );
	}
	catch( bad_alloc& )
	{
		m_pMatr = NULL;
		return;
	}
	Pair p = m_MatrRefMap.insert( MakeMatrRef(m_pMatr,1) );
	if( p.second == false )
	{
		++(*p.first).second;
	}
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
errorsT MatrPtr::Construct( int r, int c )
{
	ASSERT( !m_pMatr );
	ASSERT( (r>=0)&&(c>=0) );
	try
	{
		m_pMatr = new AlgolMatr( r, 0, c-1 );
	}
	catch( bad_alloc& )
	{
		m_pMatr = NULL;
		return NOMEM;
	}
	Pair p = m_MatrRefMap.insert( MakeMatrRef(m_pMatr,1) );
	if( p.second == false )
	{
		++(*p.first).second;
	}
	return NOERR;
}

void MatrPtr::Destruct()
{
	if( m_pMatr )
	{
		Refs::iterator it = m_MatrRefMap.find(m_pMatr);
		ASSERT( it != m_MatrRefMap.end() );
		(*it).second--;
		if( (*it).second == 0 )
		{
			delete m_pMatr;
			m_pMatr = NULL;
			m_MatrRefMap.erase(it);
		}
	}
}

void MatrPtr::InitBy( const MatrPtr &obj )
{
	if( m_pMatr != obj.m_pMatr )
	{
		if( m_pMatr )
			Destruct();
		m_pMatr = obj.m_pMatr;
		if( m_pMatr )
		{
			Refs::iterator it = m_MatrRefMap.find(m_pMatr);
			ASSERT( it != m_MatrRefMap.end() );
			(*it).second++;
		}
	}
}

AlgolMatr* MatrPtr::GetMatr() const
{
	ASSERT(m_pMatr);
	return m_pMatr;
}

bool MatrPtr::Resize( int r, int c )
{
	if( !m_pMatr )
	{
		if( Construct( r, c ) != NOERR )
			return false;
		return true;
	}
	return m_pMatr->Resize( r, c );
}

bool MatrPtr::SetAt( int r, int c, const Value &v )
{
//ф-ци€ заносит в элемент м-цы (r,c) значение v.
//≈сли (r,c) находитс€ за пределами массива или v несовместим с типом м-цы,
//то возвращаетс€ false.
	if( !m_pMatr )
		return false;
	Value tmp = v;
	if( tmp.ConvertTo( TYPE_DOUBLE ) == false )
		return false;
	return m_pMatr->SetAt( r + 1, c, v.GetDouble() );
}

bool MatrPtr::GetAt( int r, int c, Value &v )
{
//ф-ци€ заносит в v значение элемента м-цы (r,c).
//≈сли (r,c) находитс€ за пределами массива,
//то возвращаетс€ false.
	if( !m_pMatr )
		return false;
	r++;
	if( !m_pMatr->IsValidPos( r, c ) )
		return false;
	v.SetDouble( m_pMatr->GetAt( r, c ) );
	return true;
}
