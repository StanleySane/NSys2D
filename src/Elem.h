// Elem.h: interface for the CElem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELEM_H__6CF72FA5_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_ELEM_H__6CF72FA5_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ObjectSheme.h"
#include "Knot.h"
#include "ListKnot.h"
#include "Matr.h"

class CElem : public CObjectSheme  
{
public:
	virtual void Serialize(CArchive& ar);
	virtual int SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, int i, double Tt);
	void GetMatrT(CMatr &V, int size=6);
	double GetAng();
	double GetLength();
	virtual void SetMatrMDC(CMatr &mM, CMatr &mD, CMatr &mC)=0;
	virtual int GoDlg(CListKnot *pListKnot)=0;
	int SelectMode, OldMode;
	int TypeElem;
	CKnot* knot1;
	CKnot* knot2;
	virtual void Draw(CDC *dc, CParamView* pParamView)=0;
	CElem(CKnot *kn1, CKnot *kn2);
	virtual ~CElem();

};

#endif // !defined(AFX_ELEM_H__6CF72FA5_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
