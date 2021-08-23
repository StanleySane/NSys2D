// ComplexMatr.h: interface for the CComplexMatr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPLEXMATR_H__1DB6F6C2_CF11_11D3_9813_BF05434AD432__INCLUDED_)
#define AFX_COMPLEXMATR_H__1DB6F6C2_CF11_11D3_9813_BF05434AD432__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "complex.h"
#include "matr.h"

class CComplexMatr  
{
private:
	Complex **Data;
public:
public:
	CComplexMatr& UnitMatr(CMatr & matrRe, CMatr & matrJm);
/*	int Eigen_QR(CMatr *T);
	int Eigen(CMatr *T);
//	CMatr QRSolvingEigenProblem();
//	CMatr& TreeDiagForm();
	double* GetRow(int i);
	void CopyVectTo(CMatr &matr, int num);
	CMatr operator - (CMatr &matr);
	CMatr operator * (double num);
	CMatr operator + (CMatr &matr);
	CMatr MultOnCol(CMatr &matr, int col);*/
	void SetIdentity();
	int SolveSystem(CComplexMatr &mR, CComplexMatr &mU);
	CComplexMatr GetInvert(int &flag);
/*	void CopyDownToUp();*/
	void SaveToFileRe(char *name);
	void SaveToFileIm(char *name);
	CComplexMatr &operator = (CComplexMatr &matr);
	CComplexMatr operator * (CComplexMatr &matr);
	CComplexMatr(CComplexMatr &matr);
	void ClearData();
	void ReSize(int nx, int ny);
	void Clear();
	int IsEmpty();
/*	CMatr operator ! ();*/
	Complex* operator [] (int n);
	int SizeX,SizeY;
	CComplexMatr(int ny, int nx);
	CComplexMatr();
	virtual ~CComplexMatr();

};

#endif // !defined(AFX_COMPLEXMATR_H__1DB6F6C2_CF11_11D3_9813_BF05434AD432__INCLUDED_)
