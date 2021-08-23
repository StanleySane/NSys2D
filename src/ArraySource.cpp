// ArraySource.cpp: implementation of the Array class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"

#include"ValueHeader.h"
#include"ArrayHeader.h"

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////
//	members of Array class
////////////////////////////////////////////////////////////////
void Array::Destruct()
{
	if( m_vec != NULL )
	{
		int s = m_vec->size();
		for( int i = 0; i < s; i++ )
			delete m_vec->at(i);
		delete m_vec;
		m_vec = NULL;
	}
}

void Array::InitBy( const Array &v )
{
	Destruct();
	m_tType = v.m_tType;
	if( v.m_vec != NULL )
	{
		int s = v.m_vec->size();
		try
		{
			m_vec = new vector<Value*>( s, NULL );
		}
		catch( bad_alloc& )
		{
			// !!!
			m_vec = NULL;
			Destruct();
			return;
		}
		for( int i = 0; i < s; i++ )
		{
			try
			{
				m_vec->at(i) = new Value( *v.m_vec->at(i) );
			}
			catch( bad_alloc& )
			{
				//!!!
				m_vec->at(i) = NULL;
				Destruct();
				return;
			}
		}
	}
}

bool Array::SetAt( int pos, const Value &val )
{
//ф-ци€ заносит в элемент массива с номером pos значение val.
//≈сли pos находитс€ за пределами массива или val несовместим с типом массива,
//то возвращаетс€ false.
	ASSERT( m_vec != NULL );
	if( (pos < 0)||(pos >= m_vec->size()) )
		return false;
	Value tmp = val;
	if( tmp.ConvertTo( Array::GetValType(m_tType) ) == false )
		return false;
	ASSERT( m_vec->at(pos) != NULL );
	*m_vec->at(pos) = tmp;
	return true;
}

bool Array::GetAt( int pos, Value &val ) const
{
//ф-ци€ заносит в val значение элемента массива с номером pos.
//≈сли pos находитс€ за пределами массива,
//то возвращаетс€ false.
	ASSERT( m_vec != NULL );
	if( (pos < 0)||(pos >= m_vec->size()) )
		return false;
	ASSERT( m_vec->at(pos) != NULL );
	val = *m_vec->at(pos);
	return true;
}

bool Array::SetType( TypeID tp )
{
//ф-ци€ задаЄт тип хранимого значени€.
//ф-ци€ вызываетс€ только раз: после создани€ объекта !
	if( m_tType != TYPE_UNKNOWN )
		return false;
	m_tType = tp;
	return true;
}

bool Array::Resize( int s )
{
	ASSERT( m_tType != TYPE_UNKNOWN );
	if( s < 0 )
		return false;
	Destruct();
	try
	{
		m_vec = new vector<Value*>( s, NULL );
	}
	catch( bad_alloc& )
	{
		m_vec = NULL;
		return false;
	}
	for( int i = 0; i < s; i++ )
	{
		try
		{
			m_vec->at(i) = new Value();
		}
		catch( bad_alloc& )
		{
			m_vec->at(i) = NULL;
			Destruct();
			return false;
		}
		(m_vec->at(i))->SetType( Array::GetValType(m_tType) );
	}
	return true;
}

bool Array::IsArray( TypeID tp )
{
	if( (tp == TYPE_ARRAY_INT)||
		(tp == TYPE_ARRAY_DOUBLE)||
		(tp == TYPE_ARRAY_BOOL)||
		(tp == TYPE_ARRAY_STRING) )
		return true;
	return false;
}

TypeID Array::GetValType( TypeID tp )
{
//ф-ци€ возвращает тип хранимого в массиве значени€,
//если тип самого массива = tp.
	switch(tp)
	{
	case TYPE_ARRAY_INT:
		return TYPE_INT;
		break;
	case TYPE_ARRAY_BOOL:
		return TYPE_BOOL;
		break;
	case TYPE_ARRAY_DOUBLE:
		return TYPE_DOUBLE;
		break;
	case TYPE_ARRAY_STRING:
		return TYPE_STRING;
		break;
	}
	return TYPE_UNKNOWN;
}
