// Matr.h: interface for the CMatr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATR_H__8BB243A2_D8BD_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_MATR_H__8BB243A2_D8BD_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class AlgolMatr;

class CMatr  
{
private:
	double **Data;
public:
	int Eigen_QR(CMatr *T);
	int Eigen(CMatr *T);
	////////////////////////////////////////////////////
	int GetEigenVecs( CMatr &M, EV_METHOD EVm );
	void ConvertToAlgolMatr( AlgolMatr &AM );
	void ConvertToCMatr( AlgolMatr AM );
	////////////////////////////////////////////////////
//	CMatr QRSolvingEigenProblem();
//	CMatr& TreeDiagForm();
	double* GetRow(int i);
	void CopyVectTo(CMatr &matr, int num);
	CMatr operator - (CMatr &matr);
	CMatr operator * (double num);
	CMatr operator + (CMatr &matr);
	CMatr MultOnCol(CMatr &matr, int col);
	void SetIdentity();
	int SolveSystem(CMatr &mR, CMatr &mU);
	CMatr GetInvert(int &flag, int iMethod = 1 );
	void CopyDownToUp();
	void SaveToFile(char *name);
	CMatr &operator = (CMatr &matr);
	CMatr operator * (CMatr &matr);
	CMatr(CMatr &matr);
	void ClearData();
	void ReSize(int ny, int nx);
	void Clear();
	int IsEmpty();
	CMatr operator ! ();
	double* operator [] (int n);
	int SizeX,SizeY;
	 CMatr(int ny, int nx);
	CMatr();
	virtual ~CMatr();

};

#endif // !defined(AFX_MATR_H__8BB243A2_D8BD_11D2_AF23_BB2B1C460D22__INCLUDED_)
