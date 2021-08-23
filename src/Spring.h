// Spring.h: interface for the CSpring class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRING_H__A4DE2CC4_D31A_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_SPRING_H__A4DE2CC4_D31A_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Elem.h"

class CSpring : public CElem  
{
private:
	double a_X1;
	double a_X3;
	double a_X5;
	double a_XX;
	CString str_X1;
	CString str_X3;
	CString str_X5;
	CString str_XX;
public:
	virtual void Serialize(CArchive & ar);
	int SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, int i, double Tt);
	void SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC);

	void GetMatrM( CMatr& ) const;
	void GetMatrD( CMatr& ) const;
	void GetMatrC( CMatr& ) const;

	CString GetStrX1();
	CString GetStrX3();
	CString GetStrX5();
	CString GetStrXX();
	double GetSprnX1() const;
	double GetSprnX3() const;
	double GetSprnX5() const;
	double GetSprnXX() const;
	double SetSprnX1(CString str);
	double SetSprnX3(CString str);
	double SetSprnX5(CString str);
	double SetSprnXX(CString str);
	int type;
	void Draw(CDC * pDC, CParamView * pParamView);
	int GoDlg(CListKnot * pListKnot, bool full = true );
	bool SetCommonProperties( CElem* elem );
	CSpring(CKnot *kn1, CKnot *kn2);
	virtual ~CSpring();
};

#endif // !defined(AFX_SPRING_H__A4DE2CC4_D31A_11D2_AF23_BB2B1C460D22__INCLUDED_)
