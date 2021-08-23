// EqualDegrees.h: interface for the CEqualDegrees class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQUALDEGREES_H__89D530E3_5477_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_EQUALDEGREES_H__89D530E3_5477_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include"StdAfx.h"
#include"Matr.h"

#include<afxtempl.h>

class CEqualDegrees  
{
private:
	CList<ARRAY,ARRAY> *m_lstPairs;
	CList<Triple,Triple> *m_lstTriples;
	int m_size;//размер исходной матрицы
	ARRAY m_SolVect;
	CMatr m_Cond;
public:
	int CountDegrees( int );
	int CountKnots( int );
	void DeModifyVector( CMatr &v );
	void DeModifyMatrix( CMatr &m );
	void GetSolVect( ARRAY &sv );
	int GetModifiedSize();
	int GetRealSize();
	void ModifyMatr( CMatr &m );
	void ModifyVect( CMatr &v );
	void AddTriple( int, int, int, double );
	void Prepare();
	void AddPair( int, int );

	void ModifyMatrMDC( CMatr &M, CMatr &D, CMatr &C, bool condence );
	void ModifyMatrMC( CMatr &M, CMatr &C );

	CEqualDegrees( int n = 0 );
	virtual ~CEqualDegrees();

private:
	void ModifyMatrMass( CMatr &M, CMatr C );
	void InsertTripleInMatr( Triple tr );
	void InsertTripleInVect( Triple tr, CMatr &v );
	void TrimMatr( CMatr &M, ARRAY &vec );
	void TrimCondMatr( ARRAY& );
	void TrimAllMatr( CMatr&, CMatr&, CMatr& );
	void TrimVect( CMatr & );

	//запрещённые ф-ции
	CEqualDegrees( const CEqualDegrees& );
	CEqualDegrees& operator=( const CEqualDegrees& );
};

#endif // !defined(AFX_EQUALDEGREES_H__89D530E3_5477_11D6_B89D_FE2BA355A53D__INCLUDED_)
