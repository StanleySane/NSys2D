// Spring.h: interface for the CSpring class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRING_H__A4DE2CC4_D31A_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_SPRING_H__A4DE2CC4_D31A_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Elem.h"

class CShemeDoc;

class CSpring : public CElem  
{
	void InitBy( const CSpring& );
private:
	double a_X1;
	double a_X3;
	double a_X5;
//	CString str_X1;
//	CString str_X3;
//	CString str_X5;
//	CString str_XX;
public:
	int type;
	CShemeExpr m_XX;

	virtual void Serialize( CArchive &ar, int _sv );
	virtual int SetMatrmP( CMatr &mP, CMatr &RezY1, CMatr &RezY2, CMatr *Y3, int i, double Tt, std::string *pMsg = NULL );
	void SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC, std::string *pMsg = NULL );

	void SetVarState( double x, double v, double a, double t );

	void GetMatrM( CMatr&, std::string *pMsg = NULL );
	void GetMatrD( CMatr&, std::string *pMsg = NULL );
	void GetMatrC( CMatr&, std::string *pMsg = NULL );

//	CString GetStrX1();
//	CString GetStrX3();
//	CString GetStrX5();
//	CString GetStrXX();
	double GetSprnX1() const;
	double GetSprnX3() const;
	double GetSprnX5() const;
	double GetSprnXX( double x, double v, double a, double t, std::string &ec );
	bool SetSprnX1( double );
	bool SetSprnX3( double );
	bool SetSprnX5( double );
	bool SetSprnXX( const CString& );

	void Draw(CDC * pDC, CParamView * pParamView);
	void DrawGL( CShemeDoc*, int );
	CString GetName() const;

	int GoDlg(CListKnot * pListKnot, bool full = true );
	bool SetCommonProperties( const CElem* elem );

	CSpring( CKnot *kn1, CKnot *kn2, CSheme *p = NULL );
	virtual ~CSpring();
	CSpring( const CSpring& );
	CSpring& operator=( const CSpring& );
};

#endif // !defined(AFX_SPRING_H__A4DE2CC4_D31A_11D2_AF23_BB2B1C460D22__INCLUDED_)
