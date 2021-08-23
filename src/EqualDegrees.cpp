// EqualDegrees.cpp: implementation of the CEqualDegrees class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "EqualDegrees.h"

#include<new>
#include<algorithm>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CEqualDegrees::CEqualDegrees( int n ):m_lstPairs(NULL), m_lstTriples(NULL), m_size(0)
{
	try
	{
		m_lstPairs = new CList<ARRAY,ARRAY>(1);
	}
	catch( bad_alloc& )
	{
		m_lstPairs = NULL;
		return;
	}
	try
	{
		m_lstTriples = new CList<Triple,Triple>(1);
	}
	catch( bad_alloc& )
	{
		m_lstTriples = NULL;
		return;
	}
	m_size = n;
}

CEqualDegrees::~CEqualDegrees()
{
	if( m_lstPairs )
		m_lstPairs->RemoveAll();
	if( m_lstTriples )
		m_lstTriples->RemoveAll();
	delete m_lstPairs;
	delete m_lstTriples;
}
////////////////////////////////////////////////////////////
//	realisations
////////////////////////////////////////////////////////////
void CEqualDegrees::AddPair( int x1, int x2 )
{
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}
	POSITION pos = m_lstPairs->GetHeadPosition();
	while( pos )
	{
		ARRAY::iterator it;
		ARRAY tmp = m_lstPairs->GetAt(pos);
		//ищем, есть ли уже такая степень свободы в списке?
		it = find( tmp.begin(), tmp.end(), x1 );
		if( it != tmp.end() )
		{
			//есть, тогда добавляем сюда x2
			m_lstPairs->GetAt(pos).push_back(x2);
			return;
		}
		else
		{
			//нету. значит ищем x2
			it = find( tmp.begin(), tmp.end(), x2 );
			if( it != tmp.end() )
			{
				//есть x2, тогда добавляем сюда x1
				m_lstPairs->GetAt(pos).push_back(x1);
				return;
			}
			else
			{
				//нету ни той ни другой.
				//продолжаем искать в следующем элементе
				//списка
			}
		}
		m_lstPairs->GetNext(pos);
	}
	//если не нашли нигде, то добаляем эту пару в новый элемент
	//списка:
	ARRAY new_array;
	new_array.push_back(x1);
	new_array.push_back(x2);
	m_lstPairs->AddTail( new_array );
}

void CEqualDegrees::Prepare()
{
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}
	TRACE0("\nTriples before prepare:\n");
	POSITION pos1 = m_lstTriples->GetHeadPosition();
	while( pos1 )
	{
		TRACE("%d=%d+%d*%.3lf\n", m_lstTriples->GetAt(pos1).right_move,
			m_lstTriples->GetAt(pos1).left_move,
			m_lstTriples->GetAt(pos1).rotate,
			m_lstTriples->GetAt(pos1).L);
		m_lstTriples->GetNext(pos1);
	}

	//ВНИМАНИЕ: эта ф-ция должна быть обязательно
	//вызвана в конце заполнения объекта типа CEqualDegrees
	POSITION pos = m_lstPairs->GetHeadPosition();
	while( pos )
	{
		sort( m_lstPairs->GetAt(pos).begin(),
				m_lstPairs->GetAt(pos).end() );
		for( int i = 0; i < m_lstPairs->GetAt(pos).size()-1; i++ )
		{
			//поиск в векторе равных значений и удаление лишних из них
			while( m_lstPairs->GetAt(pos).at(i) == m_lstPairs->GetAt(pos).at(i+1) )
			{
				ARRAY::iterator it = m_lstPairs->GetAt(pos).begin();
				it += i;//it указывает на (i+1)-й элемент
				m_lstPairs->GetAt(pos).erase(it);
			}
		}
		m_lstPairs->GetNext(pos);
	}
	ARRAY vecNotSol;// дополнительный вектор номеров степеней свободы,
					// которые не учавствуют в решении, но которые
					// надо учесть в м-це m_Cond
	//готовим вектор решения
	m_SolVect.clear();
	for( int i = 0; i < m_size; i++ )
	{
		pos = m_lstPairs->GetHeadPosition();
		bool IsInPairs = false;
		while( pos )
		{
			if( m_lstPairs->GetAt(pos).at(0) == i )
			{
				//если эта степень находится в начале одного из векторов,
				//значит на неё мы "меняем" все остальные степени
				//и её заносим в вектор решения
				m_SolVect.push_back( i );
				IsInPairs = true;
				break;
			}
			int n = m_lstPairs->GetAt(pos).size();
			//проверяем остальные степени
			for( int j = 1; j < n; j++ )
			{
				if( m_lstPairs->GetAt(pos).at(j) == i )
				{
					//если такая степень есть не в начале вектора,
					//то мы её не должны использовать
					IsInPairs = true;
					break;
				}
			}
			m_lstPairs->GetNext(pos);
		}
		if( IsInPairs )	continue;

		pos = m_lstTriples->GetHeadPosition();
		bool IsInTriples = false;
		while( pos )
		{
			int tmp = m_lstTriples->GetAt(pos).right_move;// DEBUG
			if( m_lstTriples->GetAt(pos).right_move < 0 )
			{
				int tmp2 = m_lstTriples->GetAt(pos).left_move;// DEBUG
				if( m_lstTriples->GetAt(pos).left_move == i )
				{
					//если эта степень является левым прогибом
					//стержня, чей правый прогиб заделан, то
					//эта степень не участвует в решении,
					// т.к. стержень жёсткий
					//IsInTriples = true;
					vecNotSol.push_back( i );
					//break;
				}
			}
			if( m_lstTriples->GetAt(pos).right_move == i )
			{
				//если эта степень является правым прогибом
				//стержня, то она точно не участвует в решении
				IsInTriples = true;
				break;
			}
			m_lstTriples->GetNext(pos);
		}
		if( IsInTriples )	continue;

		//если этой степени нет нигде, то она точно участвует в решении
		//и её заносим в вектор решения
		m_SolVect.push_back( i );
	}

	sort( m_SolVect.begin(), m_SolVect.end() );
///////////////////////////////////////////////////////
	TRACE0("\nTriples after prepare:\n");
	POSITION pos2 = m_lstTriples->GetHeadPosition();
	while( pos2 )
	{
		TRACE("%d=%d+%d*%.3lf\n", m_lstTriples->GetAt(pos2).right_move,
			m_lstTriples->GetAt(pos2).left_move,
			m_lstTriples->GetAt(pos2).rotate,
			m_lstTriples->GetAt(pos2).L);
		m_lstTriples->GetNext(pos2);
	}
///////////////////////////////////////////////////////
	//создание конденсирующих матриц 
	int n = m_SolVect.size();
	m_Cond.ReSize( m_size, n );
	ARRAY vecNotSolCol;
	for( int r = 0; r < n; r++ )
	{
		int i = m_SolVect[r];
		ARRAY::iterator it = find( vecNotSol.begin(), vecNotSol.end(), i );
		if( it != vecNotSol.end() )	vecNotSolCol.push_back( r );
		m_Cond[i][r] += 1.0;
	}
	
//	n = vecNotSol.size();
//	for( r = 0; r < n; r++ )
//	{
//		int i = vecNotSol[r];
//		m_Cond[i][r] += 1.0;
//	}

	pos = m_lstTriples->GetHeadPosition();
	while( pos )
	{
		InsertTripleInMatr( m_lstTriples->GetAt(pos) );
		m_lstTriples->GetNext(pos);
	}

	pos = m_lstPairs->GetHeadPosition();
	while( pos )
	{
		int s = m_lstPairs->GetAt(pos).size();
		if( m_lstPairs->GetAt(pos).at(0) < 0 )
		{
			//если все эти степени заделаны, то
			//забиваем их нулями.
			for( int i = 0; i < n; i++ )
			{
				for( int j = 1; j < s; j++ )
					m_Cond[m_lstPairs->GetAt(pos).at(j)][i] = 0.0;
			}
		}
		else
		{
			//складываем строки
			for( int i = 0; i < n; i++ )
			{
				//вычисляем величину элемента суммированных строк
				double val = 0.0;
				for( int j = 0; j < s; j++ )
					val += m_Cond[m_lstPairs->GetAt(pos).at(j)][i];
				//заносим эту величину в строки
				for( j = 0; j < s; j++ )
					m_Cond[m_lstPairs->GetAt(pos).at(j)][i] = val;
			}
		}
		m_lstPairs->GetNext(pos);
	}

	int n2 = vecNotSol.size();
	for( r = 0; r < n2; r++ )
	{
		m_SolVect.erase( std::remove( m_SolVect.begin(), m_SolVect.end(), vecNotSol[r] ), m_SolVect.end() );
	}

	if( vecNotSol.size() > 0 )
	{
		CMatr NewCond( m_size-vecNotSol.size(), n-vecNotSolCol.size() );
		r = 0;
		for( i = 0; i < m_Cond.SizeY; i++ )
		{
			ARRAY::iterator it = find( vecNotSol.begin(), vecNotSol.end(), i );
			if( it != vecNotSol.end() )	continue;
			int c = 0;
			for( int j = 0; j < m_Cond.SizeX; j++ )
			{
				it = find( vecNotSolCol.begin(), vecNotSolCol.end(), j );
				if( it != vecNotSolCol.end() )	continue;
				NewCond[r][c] = m_Cond[i][j];
				c++;
			}
			r++;
		}
		m_Cond = NewCond;
	}

	////////////////////////////////////////////
	TRACE0("\n\nCondMatr:\n");
	for( r = 0; r < m_Cond.SizeY; r++ )
	{
		TRACE1("\n%d>>> ", r);
		for( int c = 0; c < m_Cond.SizeX; c++ )
		{
			TRACE1("%.5lf ", m_Cond[r][c] );
		}
	}
	////////////////////////////////////////////
}

int CEqualDegrees::CountDegrees( int deg )
{
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return 0;
	}
	int c = 0;
	POSITION pos = m_lstTriples->GetHeadPosition();
	while( pos )
	{
		if( m_lstTriples->GetNext(pos).rotate == deg )	c++;
	}
	return (int)(c/2);
}

int CEqualDegrees::CountKnots( int deg )
{
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return 0;
	}
	POSITION pos = m_lstPairs->GetHeadPosition();
	while( pos )
	{
		ARRAY::iterator it;
		it = find( m_lstPairs->GetAt(pos).begin(),
				   m_lstPairs->GetAt(pos).end(), deg );
		if( it != m_lstPairs->GetAt(pos).end() )
		{
			return m_lstPairs->GetAt(pos).size();
		}
		m_lstPairs->GetNext(pos);
	}
	return 0;
}

void CEqualDegrees::AddTriple( int right, int left, int rot, double length )
{
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}
//	right = left + rot*length
	if( (right < 0)&&(left < 0) )	return;
	else
	{
		if( left >= 0 )
		{
			if( rot >= 0 )
				ASSERT( left< rot );
			if( (right >= 0)&&(left > right) )
			{
				int tmp = left;
				left = right;
				right = tmp;
				length *= -1;
			}
		}
		Triple tmp;
		tmp.left_move = left;
		tmp.right_move = right;
		tmp.rotate = rot;
		tmp.L = length;
		m_lstTriples->AddTail( tmp );
	}
}

void CEqualDegrees::ModifyMatrMass( CMatr &M, CMatr C )
{
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}
	int n = m_SolVect.size();
	int newsize = m_size - n;

	CMatr M11(n,n), M12(n,newsize), M22(newsize,newsize);
	CMatr K22(newsize,newsize), K21(newsize,n);

	int rm11 = 0, cm11, rm12 = 0, cm12, rm22 = 0, cm22;
	int rk21 = 0, ck21, rk22 = 0, ck22;
	//выделение подматриц M11,M12,M22,K22,K21
	for( int row = 0; row < m_size; row++ )
	{
		cm11 = cm12 = cm22 = ck21 = ck22 = 0;

		bool UsefullRow = false;
		//выясняем - используемая это строка или нет ?
		ARRAY::iterator it;
		it = find( m_SolVect.begin(), m_SolVect.end(), row );
		if( it != m_SolVect.end() )
		{
			//используемая
			UsefullRow = true;
		}

		for( int col = 0; col < m_size; col++ )
		{
			bool UsefullCol = false;
			//выясняем - используемый это столбец или нет ?
			ARRAY::iterator it;
			it = find( m_SolVect.begin(), m_SolVect.end(), col );
			if( it != m_SolVect.end() )
			{
				//используемый
				UsefullCol = true;
			}

			//заполнение:
			if( UsefullRow )
			{
				//M11,M12
				if( UsefullCol )
				{
					//M11
					M11[rm11][cm11] = M[row][col];
					cm11++;
				}
				else
				{
					//M12
					M12[rm12][cm12] = M[row][col];
					cm12++;
				}
			}
			else
			{
				//M22,K21,K22
				if( UsefullCol )
				{
					//K21
					K21[rk21][ck21] = C[row][col];
					ck21++;
				}
				else
				{
					//M22,K22
					M22[rm22][cm22] = M[row][col];
					cm22++;
					K22[rk22][ck22] = C[row][col];
					ck22++;
				}
			}
		}//for(col)

		if( UsefullRow )
		{	
			rm11++;
			rm12++;
		}	
		else
		{
			rm22++;
			rk21++;
			rk22++;
		}

	}//for(row)

	//считаем конденсированную матрицу масс
	CMatr D2, M_;
	int flag;
	D2 = K22.GetInvert(flag)*K21;
	M_ = M12*D2;
	M = M11 - M_ - !M_ + (!D2*M22*D2);
}

void CEqualDegrees::ModifyMatr(CMatr & m)
{
	ASSERT( m.SizeX == m_size );
	ASSERT( m.SizeY == m_size );
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}

	m = !m_Cond*m*m_Cond;
	return;

///////////////////////////////////////////////////////////
	TRACE0("\nPairs before modify:\n");
	POSITION pos2 = m_lstPairs->GetHeadPosition();
	while( pos2 )
	{
		TRACE0("\n>>> ");
		for( int i = 0; i < m_lstPairs->GetAt(pos2).size(); i++ )
		{
			TRACE("%d=", m_lstPairs->GetAt(pos2).at(i) );
		}
		m_lstPairs->GetNext(pos2);
	}

	//учёт "поворотно-прогибных" степеней свободы
	POSITION pos = m_lstTriples->GetHeadPosition();
	while( pos )
	{
		ASSERT( false );
//		InsertTripleInMatr( m_lstTriples->GetAt(pos), m );
		m_lstTriples->GetNext(pos);
	}//учёт поворотно-изгибных

////////////////////////////////////////////
	TRACE0("\n\nBefore modify pairs:\n");
	for( int r = 0; r < m.SizeY; r++ )
	{
		TRACE1("\n%d>>> ", r);
		for( int c = 0; c < m.SizeX; c++ )
		{
			TRACE1("%.5lf ", m[r][c] );
		}
	}
////////////////////////////////////////////

	//учёт равных степеней свободы
	pos = m_lstPairs->GetHeadPosition();
	while( pos )
	{
		int n = m_lstPairs->GetAt(pos).size();
		if( m_lstPairs->GetAt(pos).at(0) < 0 )
		{
			//если все эти степени заделаны, то
			//забиваем их нулями.
			//строки:
			for( int i = 0; i < m_size; i++ )
			{
				for( int j = 1; j < n; j++ )
					m[m_lstPairs->GetAt(pos).at(j)][i] = 0.0;
			}
			//столбцы:
			for( i = 0; i < m_size; i++ )
			{
				for( int j = 1; j < n; j++ )
					m[i][m_lstPairs->GetAt(pos).at(j)] = 0.0;
			}
		}
		else
		{
			//складываем строки
			for( int i = 0; i < m_size; i++ )
			{
				//вычисляем величину элемента суммированных строк
				double val = 0.0;
				for( int j = 0; j < n; j++ )
					val += m[m_lstPairs->GetAt(pos).at(j)][i];
				//заносим эту величину в строки
				for( j = 0; j < n; j++ )
					m[m_lstPairs->GetAt(pos).at(j)][i] = val;
			}
////////////////////////////////////////////
	TRACE0("\n\nBefore rows adding:\n");
	for( int r = 0; r < m.SizeY; r++ )
	{
		TRACE1("\n%d>>> ", r);
		for( int c = 0; c < m.SizeX; c++ )
		{
			TRACE1("%.5lf ", m[r][c] );
		}
	}
////////////////////////////////////////////

			//складываем столбцы
			for( i = 0; i < m_size; i++ )
			{
				//вычисляем величину элемента суммированных столбцов
				double val = 0.0;
				for( int j = 0; j < n; j++ )
					val += m[i][m_lstPairs->GetAt(pos).at(j)];
				//заносим эту величину в столбцы
				for( j = 0; j < n; j++ )
					m[i][m_lstPairs->GetAt(pos).at(j)] = val;
			}
		}
		m_lstPairs->GetNext(pos);
	}

	//создаём новую матрицу
	int ns = m_SolVect.size();
	CMatr new_matr( ns, ns );

	int row = 0, col;
	for( int i = 0; i < m_size; i++ )
	{
		col = 0;
		ARRAY::iterator it;
		//ищем, использумая ли это степень свободы?
		it = find( m_SolVect.begin(),
				   m_SolVect.end(), i );
		if( it != m_SolVect.end() )
		{
			//используемая
			for( int j = 0; j < m_size; j++ )
			{
				//ищем, использумая ли это степень свободы?
				it = find( m_SolVect.begin(),
				    	   m_SolVect.end(), j );
				if( it != m_SolVect.end() )
				{
					//используемая
					new_matr[row][col] = m[i][j];
					col++;
				}
			}
			row++;
		}
	}

	m = new_matr;

	TRACE0("\nPairs after modify:\n");
	pos2 = m_lstPairs->GetHeadPosition();
	while( pos2 )
	{
		TRACE0("\n>>> ");
		for( int i = 0; i < m_lstPairs->GetAt(pos2).size(); i++ )
		{
			TRACE("%d=", m_lstPairs->GetAt(pos2).at(i) );
		}
		m_lstPairs->GetNext(pos2);
	}

}

void CEqualDegrees::GetSolVect(ARRAY & sv)
{
	sv = m_SolVect;
}

void CEqualDegrees::DeModifyVector(CMatr & v)
{
	ASSERT( v.SizeX == 1 );
	ASSERT( v.SizeY == m_SolVect.size() );
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}
//расширение вектора v до первоначальных размеров
//(до модификации матрицы) с учётом ранее введенных
//"жёстких" степеней свободы.
//вектор должен хранится в столбце !!!
	CMatr NewVect(m_size,1);

	int n = m_SolVect.size();
	for( int i = 0; i < n; i++ )
	{
		NewVect[m_SolVect[i]][0] = v[i][0];
	}

	POSITION pos = m_lstPairs->GetHeadPosition();
	while( pos )
	{
		int p = m_lstPairs->GetAt(pos).at(0);
		double val = (p>=0)?(NewVect[p][0]):(0.0);
		int m = m_lstPairs->GetAt(pos).size();
		for( int j = 1; j < m; j++ )
		{
			NewVect[m_lstPairs->GetAt(pos).at(j)][0] = val;
		}
		m_lstPairs->GetNext(pos);
	}

	pos = m_lstTriples->GetHeadPosition();
	while( pos )
	{
		int p2 = m_lstTriples->GetAt(pos).right_move;
		if( p2 < 0 )
		{
			m_lstTriples->GetNext(pos);
			continue;
		}
		int p = m_lstTriples->GetAt(pos).left_move;
		double val = (p>=0)?(NewVect[p][0]):(0.0);
		int rot = m_lstTriples->GetAt(pos).rotate;
		if( rot >= 0 )
			val += NewVect[rot][0]*m_lstTriples->GetAt(pos).L;
		NewVect[p2][0] = val;
		m_lstTriples->GetNext(pos);
	}

	v = NewVect;
}



void CEqualDegrees::InsertTripleInMatr( Triple tr )
{
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}
	if( tr.right_move < 0 )	return;
	if( tr.left_move >= 0 )
	{
		//ищем: есть ли данный Triple.left_move где нибудь
		//как Triple.right_move ?
		bool is = false;
		POSITION pos = m_lstTriples->GetHeadPosition();
		while( pos )
		{
			if( tr.left_move == m_lstTriples->GetAt(pos).right_move )
			{
				is = true;
				Triple temp;
				temp.right_move = tr.right_move;
				temp.left_move = m_lstTriples->GetAt(pos).left_move;
				temp.rotate = m_lstTriples->GetAt(pos).rotate;
				temp.L = m_lstTriples->GetAt(pos).L;

				InsertTripleInMatr( temp );
			}
			m_lstTriples->GetNext(pos);
		}
		if( !is )
		{
			//если нигде не нашли, то добавляем tr.right_move
			//в tr.left_move.
			m_Cond[tr.right_move][tr.left_move] += 1.0;
		}//!is
	}

	//добавляем tr.right_move в "поворотную" строку
	if( tr.rotate >= 0 )
	{
		int column;
		ARRAY::iterator it;
		it = find( m_SolVect.begin(), m_SolVect.end(), tr.rotate );
		if( it != m_SolVect.end() )
		{
			//если есть, то это используемая степень свободы
			column = tr.rotate;
		}
		else
		{
			//иначе ищем замещающую её степень свободы
			POSITION pos = m_lstPairs->GetHeadPosition();
			while( pos )
			{
				ARRAY::iterator it;
				it = find( m_lstPairs->GetAt(pos).begin(),
						m_lstPairs->GetAt(pos).end(),
						tr.rotate );
				if( it != m_lstPairs->GetAt(pos).end() )
				{
					column = m_lstPairs->GetAt(pos).at(0);
				}
				m_lstPairs->GetNext(pos);
			}
		}

		m_Cond[tr.right_move][column] += tr.L;
	}
}

void CEqualDegrees::InsertTripleInVect( Triple tr, CMatr &v )
{
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}
	if( tr.right_move < 0 )	return;
	if( tr.left_move >= 0 )
	{
		//ищем: есть ли данный Triple.left_move где нибудь
		//как Triple.right_move ?
		bool is = false;
		POSITION pos = m_lstTriples->GetHeadPosition();
		while( pos )
		{
			if( tr.left_move == m_lstTriples->GetAt(pos).right_move )
			{
				is = true;
				Triple temp;
				temp.right_move = tr.right_move;
				temp.left_move = m_lstTriples->GetAt(pos).left_move;
				temp.rotate = m_lstTriples->GetAt(pos).rotate;
				temp.L = m_lstTriples->GetAt(pos).L;

				//m_lstTriples->GetAt(pos).right_move = tr.right_move;
				//InsertTripleInVect( m_lstTriples->GetAt(pos), v );
				InsertTripleInVect( temp, v );
			}
			m_lstTriples->GetNext(pos);
		}
		if( !is )
		{
			//если нигде не нашли, то добавляем tr.right_move
			//в tr.left_move.
			//добавляем в строку
			v[tr.left_move][0] += v[tr.right_move][0];
		}//!is
	}

	//добавляем tr.right_move в "поворотную" строку
	if( tr.rotate >= 0 )
	{
		//добавляем в строку
		v[tr.rotate][0] += v[tr.right_move][0]*tr.L;
	}
}

void CEqualDegrees::ModifyVect(CMatr & v)
{
	ASSERT( v.SizeX == 1 );
	ASSERT( v.SizeY == m_size );
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}

	TrimVect(v);
	v = !m_Cond*v;
	return;

	//учёт "поворотно-прогибных" степеней свободы
	POSITION pos = m_lstTriples->GetHeadPosition();
	while( pos )
	{
		InsertTripleInVect( m_lstTriples->GetAt(pos), v );
		m_lstTriples->GetNext(pos);
	}//учёт поворотно-изгибных

	//учёт равных степеней свободы
	pos = m_lstPairs->GetHeadPosition();
	while( pos )
	{
		int n = m_lstPairs->GetAt(pos).size();
		if( m_lstPairs->GetAt(pos).at(0) < 0 )
		{
			//если все эти степени заделаны, то
			//забиваем их нулями.
			//строки:
			for( int j = 1; j < n; j++ )
				v[m_lstPairs->GetAt(pos).at(j)][0] = 0.0;
		}
		else
		{
			//складываем строки.
			//вычисляем величину элемента суммированных строк
			double val = 0.0;
			for( int j = 1; j < n; j++ )
				val += v[m_lstPairs->GetAt(pos).at(j)][0];
			//заносим эту величину в строки
			for( j = 0; j < n; j++ )
				v[m_lstPairs->GetAt(pos).at(j)][0] = val;
		}

		m_lstPairs->GetNext(pos);
	}

	//создаём новый вектор
	int ns = m_SolVect.size();
	CMatr new_vect( ns, 1 );

	int row = 0;
	for( int i = 0; i < m_size; i++ )
	{
		ARRAY::iterator it;
		//ищем, использумая ли это степень свободы?
		it = find( m_SolVect.begin(),
				   m_SolVect.end(), i );
		if( it != m_SolVect.end() )
		{
			//используемая
			new_vect[row][0] = v[i][0];
			row++;
		}
	}

	v = new_vect;
}

void CEqualDegrees::DeModifyMatrix( CMatr &matr )
{
	ASSERT( matr.SizeY == m_SolVect.size() );
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}
	//расширение матрицы m до первоначальных размеров
	//(до модификации матрицы) с учётом ранее введенных
	//"жёстких" степеней свободы.
	CMatr NewMatr( m_size, matr.SizeX );

	int n = m_SolVect.size();
	for( int i = 0; i < n; i++ )
	{
		for( int j = 0; j < matr.SizeX; j++ )
			NewMatr[m_SolVect[i]][j] = matr[i][j];
	}

	POSITION pos = m_lstPairs->GetHeadPosition();
	while( pos )
	{
		int p = m_lstPairs->GetAt(pos).at(0);
		int m = m_lstPairs->GetAt(pos).size();
		for( int i = 0; i < matr.SizeX; i++ )
		{
			double val = (p>=0)?(NewMatr[p][i]):(0.0);
			for( int j = 1; j < m; j++ )
			{
				NewMatr[m_lstPairs->GetAt(pos).at(j)][i] = val;
			}
		}
		m_lstPairs->GetNext(pos);
	}

	TRACE0("\nTriples:\n");
	pos = m_lstTriples->GetHeadPosition();
	while( pos )
	{
		TRACE("%d=%d+%d*%.3lf\n", m_lstTriples->GetAt(pos).right_move,
			m_lstTriples->GetAt(pos).left_move,
			m_lstTriples->GetAt(pos).rotate,
			m_lstTriples->GetAt(pos).L);
		m_lstTriples->GetNext(pos);
	}

	pos = m_lstTriples->GetHeadPosition();
	while( pos )
	{
		int p = m_lstTriples->GetAt(pos).left_move;
		for( int i = 0; i < matr.SizeX; i++ )
		{
			int p2 = m_lstTriples->GetAt(pos).right_move;
			if( p2 < 0 )	continue;
			double val = (p>=0)?(NewMatr[p][i]):(0.0);
			int rot = m_lstTriples->GetAt(pos).rotate;
			if( rot >= 0 )
				val += NewMatr[rot][i]*m_lstTriples->GetAt(pos).L;
			NewMatr[p2][i] = val;

		}
		m_lstTriples->GetNext(pos);
	}

	TRACE0("\nNewMatr:\n");
	for( int r = 0; r < m_size; r++ )
	{
		for( int c = 0; c < NewMatr.SizeX; c++ )
		{
			TRACE1("%.5lf ", NewMatr[r][c] );
		}
		TRACE0("\n");
	}
	matr = NewMatr;

}

int CEqualDegrees::GetModifiedSize()
{
	return m_SolVect.size();
}

int CEqualDegrees::GetRealSize()
{
	return m_size;
}

void CEqualDegrees::TrimVect( CMatr &v )
{
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}
	POSITION pos = m_lstTriples->GetHeadPosition();
	ARRAY vecNotSol;
	while( pos )
	{
		if( m_lstTriples->GetAt(pos).right_move < 0 )
		{
			vecNotSol.push_back( m_lstTriples->GetAt(pos).left_move );
		}
		m_lstTriples->GetNext(pos);
	}
	if( vecNotSol.size() == 0 )	return;
	vecNotSol.assign( vecNotSol.begin(), std::unique_copy( vecNotSol.begin(), vecNotSol.end(), vecNotSol.begin() ) );
//	TrimMatr( M, vecNotSol );
	int n = v.SizeY - vecNotSol.size();
	CMatr NewVec( n, 1 );
	int r = 0;
	for( int i = 0; i < v.SizeY; i++ )
	{
		ARRAY::iterator it = find( vecNotSol.begin(), vecNotSol.end(), i );
		if( it != vecNotSol.end() )	continue;
		NewVec[r][0] = v[i][0];
		r++;
	}
	v = NewVec;
}

void CEqualDegrees::TrimMatr( CMatr &M, ARRAY &vec )
{
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}
	int n = M.SizeX - vec.size();
	CMatr NewM( n, n );
	int r = 0, c = 0;
	for( int i = 0; i < M.SizeY; i++ )
	{
		ARRAY::iterator it = find( vec.begin(), vec.end(), i );
		if( it != vec.end() )	continue;
		c = 0;
		for( int j = 0; j < M.SizeY; j++ )
		{
			it = find( vec.begin(), vec.end(), j );
			if( it != vec.end() )	continue;
			NewM[r][c] = M[i][j];
			c++;
		}
		r++;
	}
	M = NewM;
}

void CEqualDegrees::TrimCondMatr( ARRAY &vec )
{
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}
	int n = m_Cond.SizeY - vec.size();
	CMatr NewM( n, m_Cond.SizeX );
	int r = 0, c = 0;
	for( int i = 0; i < m_Cond.SizeY; i++ )
	{
		ARRAY::iterator it = find( vec.begin(), vec.end(), i );
		if( it != vec.end() )	continue;
		c = 0;
		for( int j = 0; j < m_Cond.SizeX; j++ )
		{
			NewM[r][c] = m_Cond[i][j];
			c++;
		}
		r++;
	}
	m_Cond = NewM;
}

void CEqualDegrees::TrimAllMatr( CMatr &M, CMatr &D, CMatr &C )
{
//	ф-ция укорачивает м-цы масс и т.д.
//	с учётом наличия связей у жёст.стержней
//	Т.е. если у стержня x2=0 (шарнир), то x1=0 тоже,
//	несмотря на то, что x1 участвует во всех решениях
//	и на схеме не заделано.

	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}
	POSITION pos = m_lstTriples->GetHeadPosition();
	ARRAY vecNotSol;
	while( pos )
	{
		if( m_lstTriples->GetAt(pos).right_move < 0 )
		{
			vecNotSol.push_back( m_lstTriples->GetAt(pos).left_move );
		}
		m_lstTriples->GetNext(pos);
	}
	int n = vecNotSol.size();
	if( n == 0 )	return;
	vecNotSol.assign( vecNotSol.begin(), std::unique_copy( vecNotSol.begin(), vecNotSol.end(), vecNotSol.begin() ) );
	if( m_Cond.SizeY != (M.SizeY - n) )
		TrimCondMatr( vecNotSol );
	TrimMatr( M, vecNotSol );
	TrimMatr( D, vecNotSol );
	TrimMatr( C, vecNotSol );
}

void CEqualDegrees::ModifyMatrMDC( CMatr &M, CMatr &D, CMatr &C, bool condence )
{
	ASSERT( (M.SizeX == m_size)&&(M.SizeY == m_size) );
	ASSERT( (D.SizeX == m_size)&&(D.SizeY == m_size) );
	ASSERT( (C.SizeX == m_size)&&(C.SizeY == m_size) );
	if( !m_lstPairs || !m_lstTriples )
	{
		AfxMessageBox("Ошибка выделения пямяти. Закройте, пожалуйста, приложение.");
		return;
	}

	TrimAllMatr( M, D, C );// подготовить м-цы
	if( condence )
	{
		ModifyMatrMass( M, C );
//		ModifyMatrMass( C, C );
	}
	else
	{
		M = !m_Cond*M*m_Cond;
//		C = !m_Cond*C*m_Cond;
	}
	D = !m_Cond*D*m_Cond;
	C = !m_Cond*C*m_Cond;	
}

void CEqualDegrees::ModifyMatrMC( CMatr &M, CMatr &C )
{
	ASSERT( (M.SizeX == m_size)&&(M.SizeY == m_size) );
	ASSERT( (C.SizeX == m_size)&&(C.SizeY == m_size) );
 
	M = !m_Cond*M*m_Cond;
	//ModifyMatrMass( M, C );
	C = !m_Cond*C*m_Cond;
}

