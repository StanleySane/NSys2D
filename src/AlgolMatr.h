// AlgolMatr.h: interface for the AlgolMatr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALGOLMATR_H__ABD44842_50BF_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_ALGOLMATR_H__ABD44842_50BF_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include"StdAfx.h"

class AlgolMatr  
{
//	нумерация строк от единицы.
//	столбцов от m_mincol до m_maxcol.

	void InitBy( const AlgolMatr& );
public:
	static DOUBLE_ARRAY::value_type m_UnValid;

	inline bool IsUnValid( DOUBLE_ARRAY::value_type *p ) const
	{	return (p == &m_UnValid);	}
	int GetIndex( int, int ) const;
	bool IsValidPos( int, int ) const;
	unsigned GetRow() const
	{	return m_row;	}
	int GetMinCol() const
	{	return m_mincol;	}
	int GetMaxCol() const
	{	return m_maxcol;	}
	int GetWidth() const
	{	return (m_maxcol-m_mincol+1);	}
	DOUBLE_ARRAY::value_type& operator()( int, int );
	const DOUBLE_ARRAY::value_type& operator()( int, int ) const;
	DOUBLE_ARRAY::value_type& GetAt( int, int );
	const DOUBLE_ARRAY::value_type& GetAt( int, int ) const;
	bool SetAt( int, int, DOUBLE_ARRAY::value_type );

	int SetMinCol( int NewMinCol )
	{
		//ф-ция меняет порядок нумерации столбцов
		//делая индекс первого равным NewMinCol,
		//и возвращает старое значение
		if( (m_row == 0)||(m_mincol == NewMinCol) )
			return m_mincol;
		int old = m_mincol;
		m_mincol = NewMinCol;
		m_maxcol += (NewMinCol - old);
		return old;
	}

	AlgolMatr& operator =( const AlgolMatr& );
	AlgolMatr();
	AlgolMatr( unsigned Row, int minC = 0, int maxC = 0 );
	AlgolMatr( DOUBLE_ARRAY::value_type *ar, unsigned Row, int minC, int maxC );
	AlgolMatr( const AlgolMatr& );
	~AlgolMatr();

	bool Transpose();
	bool Resize( int, int );
	bool Invert();
	bool LoadIdentity();
	void Negate();
	void Power(int);
	AlgolMatr operator / ( int );
	AlgolMatr operator / ( double );
	AlgolMatr operator * ( const AlgolMatr& );
	AlgolMatr operator * ( int );
	AlgolMatr operator * ( double );
	AlgolMatr operator - ( const AlgolMatr& );
	AlgolMatr operator - ( int );
	AlgolMatr operator - ( double );
	AlgolMatr operator + ( const AlgolMatr& );
	AlgolMatr operator + ( int );
	AlgolMatr operator + ( double );

	AlgolMatr& operator *= ( const AlgolMatr& );

	bool operator == ( const AlgolMatr& );
	bool operator != ( const AlgolMatr& );
private:
	unsigned m_row;
	int m_mincol, m_maxcol;
	DOUBLE_ARRAY m_vect;
};


#endif // !defined(AFX_ALGOLMATR_H__ABD44842_50BF_11D6_B89D_FE2BA355A53D__INCLUDED_)
