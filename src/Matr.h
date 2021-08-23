// Matr.h: interface for the CMatr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATR_H__8BB243A2_D8BD_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_MATR_H__8BB243A2_D8BD_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "StdAfxMy.h"

class AlgolMatr;

class CMatr  
{
	void InitBy( const CMatr& );
private:
	//�-�� �������� � ������� �� �������
	double *m_Data;
public:
	static double m_UnValid;//����������, ������ �� ������� 
	//���������� �������� () � �-��� GetAt ��� ������ �� ������� �������.

	int Eigen_QR( CMatr *T );
	int Eigen( CMatr *T );
	////////////////////////////////////////////////////
	int GetEigenVecs( CMatr&, EV_METHOD );
	void ConvertToAlgolMatr( AlgolMatr& );
	void ConvertToCMatr( const AlgolMatr& );
	////////////////////////////////////////////////////
	double* GetRow( int i );
	void CopyVectTo( const CMatr&, int );
	CMatr operator - (CMatr &matr);
	CMatr operator * (double num);
	CMatr operator + (CMatr &matr);
	CMatr MultOnCol(CMatr &matr, int col);
	void SetIdentity();
	int SolveSystem(CMatr &mR, CMatr &mU);
	CMatr GetInvert(int &flag, int iMethod = 1 );
	void CopyDownToUp();
	void SaveToFile(char *name);
	CMatr operator * (CMatr &matr);
	void ClearData();
	bool ReSize( int r, int c );
	void Clear();
	bool IsEmpty();
	CMatr operator ! ();

	//��������!!! ���������� [] ������������ �� ������������� ������������
	//���������� ������������ GetAt ��� �������� ().
	double* operator [](int n);

	//����� ��� ��� �������� ������ �� �������� �������������
	//�������������� � ������������ ���� �������� �-���� IsValidPos.
	bool IsValidPos( int r, int c ) const;
	int GetIndex( int r, int c ) const;

	double& operator()( int r, int c );
	const double& operator()( int r, int c ) const;
	double& GetAt( int, int );
	const double& GetAt( int, int ) const;

	int SizeX;//����� ��������
	int SizeY;//����� �����
	//�������� !!! ������������ �������� �������� SizeX � SizeY
	//������ �� �������������. ����������� Rows() � Cols().
	int Rows() const
	{	return SizeY;	}
	int Cols() const
	{	return SizeX;	}

	CMatr& operator = ( const CMatr& );
	CMatr( const CMatr& );
	CMatr( int, int );
	CMatr();
	virtual ~CMatr();

};

#endif // !defined(AFX_MATR_H__8BB243A2_D8BD_11D2_AF23_BB2B1C460D22__INCLUDED_)
