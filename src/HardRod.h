// HardRod.h: interface for the CHardRod class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HARDROD_H__ECCFA7C2_310F_11D5_B89B_FE2BA355A53D__INCLUDED_)
#define AFX_HARDROD_H__ECCFA7C2_310F_11D5_B89B_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Elem.h"

class CShemeDoc;

class CHardRod : public CElem  
{
	void InitBy( const CHardRod& );
private:
	//CString str_E, str_J, str_m, str_F;
	//double E,J,m,F;

public:
	CShemeExpr m_E, m_J, m_M, m_F;

	int m_HardMethod;
	int m_NofKnots;
	int m_NofHardRodsInOneKnot[2];
	//Ќомера поворотной степени свободы в массиве nRezA[]
	int FreeA1,FreeA2;
	virtual void Serialize( CArchive &ar, int sv );
	virtual int SetMatrmP( CMatr &, CMatr &, CMatr &, CMatr*, int, double, std::string *pMsg = NULL );
	void SetMatrMDC( CMatr & mM, CMatr & mD, CMatr & mC, std::string *pMsg = NULL );
	
	void GetMatrM( CMatr&, std::string *pMsg = NULL );
	void GetMatrD( CMatr&, std::string *pMsg = NULL );
	void GetMatrC( CMatr&, std::string *pMsg = NULL );

	void Draw(CDC * pDC, CParamView *pParamView);
	void DrawGL( CShemeDoc*, int );

	int GoDlg(CListKnot *pListKnot, bool full = true );
	bool SetCommonProperties( const CElem* elem );

	void SetVarState();

//	Set-ы
	bool SetF( const CString& );
	bool SetM( const CString& );
	bool SetJ( const CString&);
	bool SetE( const CString& );
	bool SetF( double );
	bool SetM( double );
	bool SetJ( double );
	bool SetE( double );
//	Get-ы
	double GetF( bool flg = true );
	double GetM( bool flg = true );
	double GetJ( bool flg = true );
	double GetE( bool flg = true );

	CString GetName() const;

//	constructor/destructor
	CHardRod( CKnot *kn1, CKnot *kn2, CSheme *p = NULL );
	virtual ~CHardRod();
	CHardRod( const CHardRod& );
	CHardRod& operator=( const CHardRod& );

};

#endif // !defined(AFX_HARDROD_H__ECCFA7C2_310F_11D5_B89B_FE2BA355A53D__INCLUDED_)
