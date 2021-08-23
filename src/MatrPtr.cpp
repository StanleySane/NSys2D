// MatrPtr.cpp: implementation of the MatrPtr class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "MatrPtr.h"

#include "StdAfxMy.h"

#include "AlgolMatr.h"
#include "Matr.h"
#include "ValueHeader.h"

#include<new>
#include<cmath>
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
		if( (c == 0)||(r == 0) )
		{
			m_pMatr = new AlgolMatr();
		}
		else
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
		//ASSERT( it != m_MatrRefMap.end() );
		if( it == m_MatrRefMap.end() )
		{
			m_pMatr = NULL;
			return;
		}
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
//	ASSERT(m_pMatr);
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

bool MatrPtr::GetEigen( AlgolMatr &Freqs, AlgolMatr &Forms, int iMethod )
{
	if( m_pMatr == NULL )
		return false;
	if( (iMethod < 0)||(iMethod > 3) )
		return false;

	if( iMethod == 0 )
	{
		CMatr m;
		m.ConvertToCMatr( *m_pMatr );
		CMatr forms( m.SizeY, m.SizeY );
		//¬ычисление собственных частот и форм методом якоби
		if( m.Eigen( &forms ) < 0 )
			return false;
		//Ќормирование форм
		for( int i = 0; i < forms.SizeX; i++ )
		{
			double val = 0.0;
			for( int j = 0; j < forms.SizeY; j++ )
			{
				double tmp = forms.GetAt( j, i );
				val += tmp*tmp;
			}
			val = sqrt(val);
			for( j = 0; j < forms.SizeY; j++ )
			{
				forms.GetAt( j, i ) /= val;
			}
		}
		//—ортируем формы по возрастанию частот
		int s = m.SizeX - 1;
		for( i = 0; i < s; i++ )
		{
			for( int j = i+1; j < m.SizeX; j++ )
			{
				if( m.GetAt(i,i) > m.GetAt(j,j) )
				{
					double tmp = m.GetAt(i,i);
					m.GetAt(i,i) = m.GetAt(j,j);
					m.GetAt(j,j) = tmp;
					for( int k = 0; k < forms.SizeY; k++ )
					{
						tmp = forms.GetAt(k,i);
						forms.GetAt(k,i) = forms.GetAt(k,j);
						forms.GetAt(k,j) = tmp;
					}
				}
			}
		}
		if( Freqs.Resize( m.SizeX, 1 ) == false )
			return false;
		for( i = 0; i < m.SizeX; i++ )
		{
			Freqs( i+1, 0 ) = m.GetAt( 0, i );
		}
		forms.ConvertToAlgolMatr( Forms );
	}
	else
	{
		//вычисление собств.значений и форм QR-методом
		EV_METHOD EVMethod;
		switch( iMethod )
		{
		case 1:
			EVMethod = EVM_QR_ELM;
			break;
		case 2:
			EVMethod = EVM_QR_DIR;
			break;
		case 3:
			EVMethod = EVM_QR_ORT;
			break;
		}
		if( m_pMatr->GetEigen( Freqs, Forms, EVMethod ) == false )
			return false;
		Freqs.SetMinCol(0);
		Forms.SetMinCol(0);
		//Ќормирование форм
		int r, c, cols = Forms.GetMaxCol(), rows = Forms.GetRow();
		for( c = 0; c < cols; c++ )
		{
			double val = 0.0;
			for( r = 0; r < rows; r++ )
			{
				double tmp = Forms( r, c );
				val += tmp*tmp;
			}
			val = sqrt(val);
			for( r = 0; r < rows; r++ )
			{
				Forms( r, c ) /= val;
			}
		}
		//—ортируем формы по возрастанию частот
		cols = Freqs.GetRow();
		rows = Forms.GetMaxCol();
		int s = cols - 1;
		for( r = 0; r < s; r++ )
		{
			for( c = r+1; c < cols; c++ )
			{
				if( Freqs(r,0) > Freqs(c,0) )
				{
					double tmp = Freqs(r,0);
					Freqs(r,0) = Freqs(c,0);
					Freqs(c,0) = tmp;
					for( int k = 0; k < rows; k++ )
					{
						tmp = Forms(k,r);
						Forms(k,r) = Forms(k,c);
						Forms(k,c) = tmp;
					}
				}
			}
		}
	}//if(EVm==EVM_JACOBY)
	return true;
}