// Mass.h: interface for the CMass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MASS_H__DDB382C2_D6CB_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_MASS_H__DDB382C2_D6CB_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Elem.h"

class CMass : public CElem  
{
public:
	virtual void Serialize(CArchive & ar);
	void SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, int i);
	void SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC);
	CString GetStrJp();
	CString GetStrM();
	double GetJp();
	double GetM();
	double SetMassJp(CString strJp);
	double SetMassM(CString strm);
	CString str_M;
	CString str_Jp;
	double M,Jp;
	int GoDlg(CListKnot * pListKnot);
	void Draw(CDC * pDC, CParamView * pParamView);
	CMass(CKnot *kn1);
	virtual ~CMass();

};

#endif // !defined(AFX_MASS_H__DDB382C2_D6CB_11D2_AF23_BB2B1C460D22__INCLUDED_)
