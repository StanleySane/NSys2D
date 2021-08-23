// Rod.h: interface for the CRod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROD_H__6CF72FA6_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_ROD_H__6CF72FA6_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Elem.h"
#include "Expression.h"

class CRod : public CElem  
{
private:
	CString str_E, str_Jx, str_m0,str_F;
	double E,Jx,m0,F;
public:
	//Ќомера поворотной степени свободы в массиве nRezA[]
	int FreeA1,FreeA2;
	virtual void Serialize(CArchive & ar);
	int SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, int i, double Tt);
	double SetF(CString &str);
	CString GetStrF();
	double GetF();
	void SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC);
	CString GetStrM();
	double GetM();
	double SetM(CString &str);
	int GoDlg(CListKnot *pListKnot);
	CString GetStrJx();
	CString GetStrE();
	void Draw(CDC * pDC, CParamView *pParamView);
	double SetJx(CString &str);
	double SetE(CString &str);
	double GetJx();
	double GetE();
//	int type1,type2;
	
	CRod(CKnot *kn1, CKnot *kn2);
	virtual ~CRod();

};

#endif // !defined(AFX_ROD_H__6CF72FA6_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
