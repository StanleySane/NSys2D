// Demf.h: interface for the CDemf class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMF_H__F5362BC2_CB61_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_DEMF_H__F5362BC2_CB61_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Elem.h"

class CDemf : public CElem  
{
private:
	double a_X1;
	double a_X3;
	double a_X5;
	double a_XS;
	double a_XX;
	CString str_X1;
	CString str_X3;
	CString str_X5;
	CString str_XS;
	CString str_XX;
public:
//	CString GetStrXS();
	virtual void Serialize(CArchive & ar);
	int SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, int i, double Tt);
	void SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC);

	void GetMatrM( CMatr& ) const;
	void GetMatrD( CMatr& ) const;
	void GetMatrC( CMatr& ) const;
//	double GetDemfXX();
	double GetDemfX(int i) const;
//	CString GetStrXX();
	//получить строку для диалога в нужную строку (i)
	CString GetStrX(int i);
//	double SetDemfXX(CString str);
//	double SetDemfX1(CString str);
//	double GetDemfX5();
//	double GetDemfX3();
//	CString GetStrX5();
//	CString GetStrX3();
	double SetDemfX(CString str, int i);
//	double SetDemfX3(CString str);
	int type;
	int GoDlg(CListKnot *pListKnot, bool full = true );
	bool SetCommonProperties( CElem* elem );
	void Draw(CDC *pDC, CParamView *pParamView);
	CDemf(CKnot *kn1, CKnot *kn2);
	virtual ~CDemf();

};

#endif // !defined(AFX_DEMF_H__F5362BC2_CB61_11D2_AF23_BB2B1C460D22__INCLUDED_)
