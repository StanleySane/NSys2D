// Rod.h: interface for the CRod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROD_H__6CF72FA6_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_ROD_H__6CF72FA6_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Elem.h"

class CShemeDoc;

class CRod : public CElem  
{
	void InitBy( const CRod& );
private:
	//CString str_E, str_Jx, str_m0,str_F;
	//double E,Jx,m0,F;
public:
	CShemeExpr m_E, m_Jx, m_m0, m_F;
	//Ќомера поворотной степени свободы в массиве nRezA[]
	int FreeA1, FreeA2;
	virtual void Serialize( CArchive &ar, int _sv );
	virtual int SetMatrmP( CMatr &, CMatr &, CMatr &, CMatr*, int, double, std::string *pMsg = NULL );
	void SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC, std::string *pMsg = NULL );

	void SetVarState();

	bool SetF( const CString& );
	bool SetM( const CString& );
	bool SetJx( const CString&);
	bool SetE( const CString& );
	bool SetF( double );
	bool SetM( double );
	bool SetJx( double );
	bool SetE( double );
	/*
	CString GetStrF();
	CString GetStrM();
	CString GetStrJx();
	CString GetStrE();
	*/
	double GetF( bool flg = true );
	double GetM( bool flg = true );
	double GetJx( bool flg = true );
	double GetE( bool flg = true );

	void GetMatrM( CMatr&, std::string *pMsg = NULL );
	void GetMatrD( CMatr&, std::string *pMsg = NULL );
	void GetMatrC( CMatr&, std::string *pMsg = NULL );

	int GoDlg(CListKnot *pListKnot, bool full = true );
	bool SetCommonProperties( const CElem* elem );
	void Draw(CDC * pDC, CParamView *pParamView);
	void DrawGL( CShemeDoc*, int );
	CString GetName() const;

	CRod( CKnot *kn1, CKnot *kn2, CSheme *p = NULL );
	virtual ~CRod();
	CRod( const CRod& );
	CRod& operator=( const CRod& );

};

#endif // !defined(AFX_ROD_H__6CF72FA6_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
