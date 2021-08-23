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

class CShemeDoc;
class CSheme;

class CElem : public CObjectSheme  
{
	void InitBy( const CElem& );
public:
	CElem( const CElem& );
	CElem& operator=( const CElem& );

	void SetVarState();
	void SetNumber( int num )
	{	m_Number = num;	}
	int GetNumber() const
	{	return m_Number;	}
	virtual void Serialize( CArchive &ar, int sv );
	virtual int SetMatrmP( CMatr &, CMatr &, CMatr &, CMatr*, int, double, std::string *pMsg = NULL ) = 0;
	void GetMatrT(CMatr &V, int size=6) const;
	double GetAng() const;
	double GetAngle() const;
	double GetLength() const;
	virtual void SetMatrMDC( CMatr &mM, CMatr &mD, CMatr &mC, std::string *pMsg = NULL )=0;
	virtual int GoDlg(CListKnot *pListKnot, bool full = true )=0;
	virtual bool SetCommonProperties( const CElem* elem ) = 0;

	int SelectMode, OldMode;
	int TypeElem;
	CKnot* knot1;
	CKnot* knot2;

	virtual void Draw(CDC *dc, CParamView* pParamView)=0;
	virtual void DrawGL( CShemeDoc*, int ) = 0;
	virtual CString GetName() const = 0;

	CElem( CKnot *kn1, CKnot *kn2, CSheme *p = NULL );
	virtual ~CElem();
protected:
	int m_Number;

};

#endif // !defined(AFX_ELEM_H__6CF72FA5_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
