// Mass.h: interface for the CMass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MASS_H__DDB382C2_D6CB_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_MASS_H__DDB382C2_D6CB_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Elem.h"

class CShemeDoc;

class CMass : public CElem  
{
	void InitBy( const CMass& );
public:
	//double M,Jp;
	CShemeExpr m_M, m_Jp;
	//CString str_M;
	//CString str_Jp;

	virtual void Serialize( CArchive &ar, int sv );
	virtual int SetMatrmP( CMatr &, CMatr &, CMatr &, CMatr*, int, double, std::string *pMsg = NULL );
	void SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC, std::string *pMsg = NULL );

	void SetVarState();

	void GetMatrM( CMatr&, std::string *pMsg = NULL );
	void GetMatrD( CMatr&, std::string *pMsg = NULL );
	void GetMatrC( CMatr&, std::string *pMsg = NULL );

	//CString GetStrJp();
	//CString GetStrM();
	double GetJp( bool flg = true );
	double GetM( bool flg = true );
	bool SetMassJp( const CString& );
	bool SetMassM( const CString& );
	bool SetMassJp( double );
	bool SetMassM( double );

	int GoDlg(CListKnot * pListKnot, bool full = true );
	bool SetCommonProperties( const CElem* elem );
	void Draw(CDC * pDC, CParamView * pParamView);
	void DrawGL( CShemeDoc*, int );

	CString GetName() const;

	CMass( CKnot *kn1, CSheme *p = NULL );
	virtual ~CMass();
	CMass( const CMass& );
	CMass& operator=( const CMass& );

};

#endif // !defined(AFX_MASS_H__DDB382C2_D6CB_11D2_AF23_BB2B1C460D22__INCLUDED_)
