// HardRod.h: interface for the CHardRod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HARDROD_H__ECCFA7C2_310F_11D5_B89B_FE2BA355A53D__INCLUDED_)
#define AFX_HARDROD_H__ECCFA7C2_310F_11D5_B89B_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Elem.h"
#include "Expression.h"

class CHardRod : public CElem  
{

private:
	CString str_E, str_J, str_m, str_F;
	double E,J,m,F;

public:
	int m_HardMethod;
	int m_NofKnots;
	int m_NofHardRodsInOneKnot[2];
	//Ќомера поворотной степени свободы в массиве nRezA[]
	int FreeA1,FreeA2;
	virtual void Serialize(CArchive & ar);
	int SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, int i, double Tt);
	void SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC);
	
	void GetMatrM( CMatr& ) const;
	void GetMatrD( CMatr& ) const;
	void GetMatrC( CMatr& ) const;

	void Draw(CDC * pDC, CParamView *pParamView);

	int GoDlg(CListKnot *pListKnot, bool full = true );
	bool SetCommonProperties( CElem* elem );
//	Get-ы
	CString GetStrM()
	{	return str_m;	}
	CString GetStrF()
	{	return str_F;	}
	CString GetStrJ()
	{	return str_J;	}
	CString GetStrE()
	{	return str_E;	}
	double GetM() const
	{	return m;	}
	double GetJ() const
	{	return J;	}
	double GetF() const
	{	return F;	}
	double GetE() const
	{	return E;	}
//	int type1,type2;

//	Set-ы
	double SetF(CString &str)
	{
		CExpression e;
		double val;
		if( !e.IsNum(str,&val) )
		{
			str_F = str;
			F = val;
			return val;
		}
		return -1;
	}
	double SetM(CString &str)
	{
		CExpression e;
		double val;
		if( !e.IsNum(str,&val) )
		{
			str_m = str;
			m = val;
			return val;
		}
		return -1;
	}
	double SetJ(CString &str)
	{
		CExpression e;
		double val;
		if( !e.IsNum(str,&val) )
		{
			str_J = str;
			J = val;
			return val;
		}
		return -1;
	}
	double SetE(CString &str)
	{
		CExpression e;
		double val;
		if( !e.IsNum(str,&val) )
		{
			str_E = str;
			E = val;
			return val;
		}
		return -1;
	}

//	constructor/destructor
	CHardRod( CKnot *kn1, CKnot *kn2 );
	virtual ~CHardRod();

};

#endif // !defined(AFX_HARDROD_H__ECCFA7C2_310F_11D5_B89B_FE2BA355A53D__INCLUDED_)
