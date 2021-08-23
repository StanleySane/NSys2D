// AlgolMatr.cpp: implementation of the AlgolMatr class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "AlgolMatr.h"

#include<algorithm>
#include<cmath>
#include<functional>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

bool Ortho1( const AlgolMatr &a, AlgolMatr &inv, double eps = 1e-6 );

DOUBLE_ARRAY::value_type AlgolMatr::m_UnValid = 0.0;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
AlgolMatr::AlgolMatr()
{
	m_mincol = m_maxcol = 0;
	m_row = 0;
//	m_vect.resize(1);
}

void AlgolMatr::InitBy( const AlgolMatr &m )
{
	m_row = m.m_row;
	m_mincol = m.m_mincol;
	m_maxcol = m.m_maxcol;
	m_vect.resize( m_row*(m_maxcol-m_mincol+1) );
	m_vect = m.m_vect;
}

AlgolMatr& AlgolMatr::operator =( const AlgolMatr &m )
{
	if( (*this) != m )
	{
		InitBy(m);
	}
	return *this;
}

AlgolMatr::AlgolMatr( const AlgolMatr &m )
{
	InitBy(m);
}

AlgolMatr::AlgolMatr( unsigned Row, int minC, int maxC )
{
	if( minC > maxC )
	{
		ASSERT( false );
		minC = maxC = 0;
	}
	m_row = Row;
	m_mincol = minC;
	m_maxcol = maxC;
	m_vect.resize( Row*(maxC-minC+1) );
}

AlgolMatr::AlgolMatr( DOUBLE_ARRAY::value_type *ar, unsigned Row, int minC, int maxC )
{
	m_row = Row;
	if( minC > maxC )
	{
		ASSERT( false );
		m_mincol = m_maxcol = minC = maxC = 0;
		m_vect.resize( Row*(maxC-minC+1) );
		return;
	}
	m_mincol = minC;
	m_maxcol = maxC;
	m_vect.resize( Row*(maxC-minC+1) );

	for( int r = 0; r < Row; r++ )
	{
		for( int c = minC; c <= maxC; c++ )
		{
			int tmp = r*(m_maxcol-m_mincol+1)+(c-m_mincol);
			m_vect[tmp] = ar[tmp];
		}
	}
}

AlgolMatr::~AlgolMatr()
{
	m_vect.clear();
}
///////////////////////////////////////////////////////////////////////
//	realisations
///////////////////////////////////////////////////////////////////////
bool AlgolMatr::IsValidPos( int r, int c ) const
{
	if( (r<1)||(r>static_cast<int>(m_row))||(c>m_maxcol)||(c<m_mincol) )
		return false;
	return true;
}

int AlgolMatr::GetIndex( int r, int c ) const
{
	if( !IsValidPos( r, c ) )	return -1;
	return (r-1)*(m_maxcol-m_mincol+1)+(c-m_mincol);
}

DOUBLE_ARRAY::value_type& AlgolMatr::operator()( int r, int c )
{
	return GetAt( r, c );
}

const DOUBLE_ARRAY::value_type& AlgolMatr::operator()( int r, int c ) const
{
	return GetAt( r, c );
}

bool AlgolMatr::SetAt( int r, int c, DOUBLE_ARRAY::value_type v )
{
	int ind = GetIndex( r, c );
	if( ind < 0 )
		return false;
	m_vect[ind] = v;
	return true;
}

DOUBLE_ARRAY::value_type& AlgolMatr::GetAt( int r, int c )
{
	int ind = GetIndex( r, c );
	ASSERT( ind >= 0 );
	if( ind < 0 )	return m_UnValid;
	return m_vect[ind];
}

const DOUBLE_ARRAY::value_type& AlgolMatr::GetAt( int r, int c ) const
{
	int ind = GetIndex( r, c );
	ASSERT( ind >= 0 );
	if( ind < 0 )	return m_UnValid;
	return m_vect[ind];
}

void AlgolMatr::Negate()
{
	if( m_vect.empty() )
		return;
	for_each( m_vect.begin(), m_vect.end(), negate<DOUBLE_ARRAY::value_type>() );
}

void AlgolMatr::Power( int p )
{
	if( p == 0 )
	{
		LoadIdentity();
		return;
	}
	if( p < 0 )
	{
		if( !Invert() )
			return;
		p = -p;
	}
	if( p == 1 )
		return;
	// p > 1
	AlgolMatr tmp(*this);
	for( int i = 1; i < p; i++ )
		(*this) *= tmp;
}

AlgolMatr AlgolMatr::operator / ( int v )
{
	DOUBLE_ARRAY::value_type d = static_cast<DOUBLE_ARRAY::value_type>(v);
	int s = m_vect.size();
	AlgolMatr tmp(*this);
	if( v == 0 )	return tmp;
	for( int i = 0; i < s; i++ )
		tmp.m_vect[i] = m_vect[i]/d;
	return tmp;
}

AlgolMatr AlgolMatr::operator / ( double v )
{
	int s = m_vect.size();
	AlgolMatr tmp(*this);
	if( fabs(v) < ZERO )	return tmp;
	for( int i = 0; i < s; i++ )
		tmp.m_vect[i] = m_vect[i]/v;
	return tmp;
}

AlgolMatr AlgolMatr::operator * ( const AlgolMatr &v )
{
	(*this) *= v;
	return *this;
}

AlgolMatr& AlgolMatr::operator *= ( const AlgolMatr &v )
{
	if( m_mincol != v.m_row );
		return *this;
	AlgolMatr temp( m_row, v.m_mincol, v.m_maxcol );

	for( int r = 1; r <= m_row; r++ )
		for( int c = v.m_mincol; c <= v.m_maxcol; c++ )
			for( int i = m_mincol; i <= m_maxcol; i++ )
				temp( r, c ) += GetAt( r, i ) * v.GetAt( i, c );
	(*this) = temp;
	return (*this);
}

AlgolMatr AlgolMatr::operator * ( int v )
{
	DOUBLE_ARRAY::value_type d = static_cast<DOUBLE_ARRAY::value_type>(v);
	int s = m_vect.size();
	AlgolMatr tmp(*this);
	for( int i = 0; i < s; i++ )
		tmp.m_vect[i] = m_vect[i]*d;
	return tmp;
}

AlgolMatr AlgolMatr::operator * ( double v )
{
	int s = m_vect.size();
	AlgolMatr tmp(*this);
	for( int i = 0; i < s; i++ )
		tmp.m_vect[i] = m_vect[i]*v;
	return tmp;
}

AlgolMatr AlgolMatr::operator - ( const AlgolMatr &v )
{
	if( (m_row != v.m_row)||(GetWidth() != v.GetWidth()) );
		return AlgolMatr();
	AlgolMatr temp( m_row, v.m_mincol, v.m_maxcol );

	for( int r = 1; r <= m_row; r++ )
		for( int c = v.m_mincol; c <= v.m_maxcol; c++ )
			for( int i = m_mincol; i <= m_maxcol; i++ )
				temp( r, c ) = GetAt( r, i ) - v.GetAt( i, c );
	return temp;
}

AlgolMatr AlgolMatr::operator - ( int v )
{
	DOUBLE_ARRAY::value_type d = static_cast<DOUBLE_ARRAY::value_type>(v);
	int s = m_vect.size();
	AlgolMatr tmp(*this);
	for( int i = 0; i < s; i++ )
		tmp.m_vect[i] = m_vect[i] - d;
	return tmp;
}

AlgolMatr AlgolMatr::operator - ( double v )
{
	int s = m_vect.size();
	AlgolMatr tmp(*this);
	for( int i = 0; i < s; i++ )
		tmp.m_vect[i] = m_vect[i] - v;
	return tmp;
}

AlgolMatr AlgolMatr::operator + ( const AlgolMatr &v )
{
	if( (m_row != v.m_row)||(GetWidth() != v.GetWidth()) );
		return AlgolMatr();
	AlgolMatr temp( m_row, v.m_mincol, v.m_maxcol );

	for( int r = 1; r <= m_row; r++ )
		for( int c = v.m_mincol; c <= v.m_maxcol; c++ )
			for( int i = m_mincol; i <= m_maxcol; i++ )
				temp( r, c ) = GetAt( r, i ) + v.GetAt( i, c );
	return temp;
}

AlgolMatr AlgolMatr::operator + ( int v )
{
	DOUBLE_ARRAY::value_type d = static_cast<DOUBLE_ARRAY::value_type>(v);
	int s = m_vect.size();
	AlgolMatr tmp(*this);
	for( int i = 0; i < s; i++ )
		tmp.m_vect[i] = m_vect[i] + d;
	return tmp;
}

AlgolMatr AlgolMatr::operator + ( double v )
{
	int s = m_vect.size();
	AlgolMatr tmp(*this);
	for( int i = 0; i < s; i++ )
		tmp.m_vect[i] = m_vect[i] + v;
	return tmp;
}

bool AlgolMatr::operator == ( const AlgolMatr &v )
{
	if( (m_row != v.m_row)||(m_maxcol != v.m_maxcol)||(m_mincol != v.m_mincol) )
		return false;
	return ( m_vect == v.m_vect );
}

bool AlgolMatr::operator != ( const AlgolMatr &v )
{
	return !( (*this) == v);
}

bool AlgolMatr::Invert()
{
//	Обращение м-цы.
//	eps - максимальная относительная ошибка округления.
	int width = GetWidth();
	if( m_row != width )	return false;
	AlgolMatr inv( m_row, 1, width );
	int old = SetMinCol( 1 );//это надо для правильной работы Ortho1.
	//если задать eps < 1e-150,то при взятии eps2 = eps^2 будет потеря точности
	if( !Ortho1( *this, inv, 1e-100 ) )
	{
		SetMinCol(old);
		return false;
	}
	inv.SetMinCol(old);
	(*this) = inv;
	return true;
}

bool AlgolMatr::LoadIdentity()
{
	if( m_row != GetWidth() )
		return false;
	for( int r = 1; r <= m_row; r++ )
		for( int c = m_mincol; c <= m_maxcol; c++ )
			GetAt( r, c ) = (r == (c - m_mincol + 1))?1.0:0.0;
	return true;
}

bool AlgolMatr::Transpose()
{
	int w = GetWidth();
	if( (m_row == 0)||(w == 0) )
		return false;
	AlgolMatr tmp( *this );
	if( !Resize( w, m_row ) )
		return false;
	for( int r = 1; r <= tmp.m_row; r++ )
		for( int c = tmp.m_mincol; c <= tmp.m_maxcol; c++ )
			GetAt( c, r ) = tmp( r, c );
	return true;
}

bool AlgolMatr::Resize( int r, int c )
{
//ф-ция меняет размеры м-цы на новые (r;c).
//при этом нумерация столбцов устанавливается с нуля.
	if( (r < 0)||(c < 0) )
		return false;
	if( (m_row == r)&&(c == GetWidth()) )
	{
		SetMinCol(0);
		return true;
	}
	m_row = r;
	m_mincol = 0;
	m_maxcol = c - 1;
	m_vect.resize( r*c );
	return true;
}

/*
	Применение метода наименьших квадратов для решения систем ур-ий.
	Из книги
		Уилкинсон, Райнш
		"Справочник алгоритмов на языке АЛГОЛ. Линейная алгебра.", 1976.
*/
bool Ortho1( const AlgolMatr &a, AlgolMatr &inv, double eps )
{
/*
	Обращение м-цы a (n,n).
	eps - максимальная относительная ошибка округления.
	Обратная м-ца помещена в inv (n,n).
	Если итерационное уточнение неэффективно, то возвращается false
	иначе - true.
*/
//copyright©2001 Буравилин.С.С. 96ДПМП БГТУ
	int n = static_cast<int>(a.GetRow());

	ASSERT( n == a.GetWidth() );
	ASSERT( a.GetMinCol() == 1 );
	ASSERT( inv.GetMinCol() == 1 );
	ASSERT( n == inv.GetWidth() );
	ASSERT( n == static_cast<int>(inv.GetRow()) );

	ASSERT( eps >= 1e-150 );//если задать eps < 1e-150,то при взятии eps2 = eps^2 будет потеря точности !!!

	int g, h, i, j, l = 0, ll, nn;
	double s, t;
	AlgolMatr u(n,1,n), p(n,1,1), q( static_cast<int>(n*(n+1)/2), 1, 1 );

	for( i = 1; i <= n; i++ )
		for( j = 1; j <= n; j++ )
			u(i,j) = a(i,j);

	//формирование м-ц R и U
	for( i = 1; i <= n; i++ )
	{
		s = 0.0;
		for( j = 1; j <= n; j++ )
		{
			p(j,1) = t = u(j,i);
			s += t*t;
		}
		l++;
		q(l,1) = s;
		for( g = i+1; g <= n; g++ )
		{
			t = 0.0;
			for(j = 1; j <= n; j++ )
				t += p(j,1)*u(j,g);
			//размещение эл-ов i-й строки м-цы R в массиве q.
			l++;
			q(l,1) = t;
			t /= s;
			//формирование столбца i-й оставшейся м-цы.
			for( j = 1; j <= n; j++ )
				u(j,g) -= p(j,1)*t;
		}//for(g)
	}
	//обратная подстановка
	ll = l;
	nn = n + 2;
	for( i = n; i >= 1; i-- )
	{
		h = l - i;
		t = q(l,1);
		for( j = 1; j <= n; j++ )
		{
			s = u(j,i);
			for( g = i+1; g <= n; g++ )
				s -= q(g+h,1)*inv(g,j);
			inv(i,j) = s/t;
		}
		l += i - nn;
	}
	//итерационное уточнение
	double eps2 = eps*eps, s0 = 0.0, s1, s2;
	AlgolMatr pp(n,1,1), px(n,1,1);

	bool iteration;
	do
	{
		iteration = false;
		s1 = s2 = 0.0;
		for( i = 1; i <= n; i++ )
		{
			l = ll;
			//размещение i-го столбца м-цы невязок в массиве p.
			for( j = 1; j <= n; j++ )
				px(j,1) = inv(j,i);
			for( j = 1; j <= n; j++ )
			{
				//innerprod:
				long double s1s2 = static_cast<long double>((j==i)?(-1.0):(0.0));
				for( int jj = 1; jj <= n; jj++ )
					s1s2 += static_cast<long double>(a(j,jj))*static_cast<long double>(px(jj,1));
				//------------------------------------------
				p(j,1) = static_cast<double>(-s1s2);
			}
			//размещение i-го столбца правых частей в массиве pp.
			for( j = 1; j <= n; j++ )
			{
				s = 0.0;
				for( g = 1; g <= n; g++ )
					s += u(g,j)*p(g,1);
				pp(j,1) = s;
			}
			//обратная подстановка.
			for( j = n; j >= 1; j-- )
			{
				s = pp(j,1);
				h = l - j;
				for( g = j+1; g <= n; g++ )
					s -= q(g+h,1)*pp(g,1);
				pp(j,1) = s = s/q(l,1);
				s1 += s*s;
				t = px(j,1);
				s2 += t*t;
				inv(j,i) = s + t;
				l += j - nn;
			}
		}//for(i)
		if( s1 >= (s2*0.25) )	return false;
		if( (s1 >= (s2*eps2))&&((fabs(s0)<ZERO)||(s1<=(s0*0.01))) )
		{
			s0 = s1;
			iteration = true;
		}
	}	while( iteration );
///////////////////////////////////////////////////////////////////
	return true;
}
