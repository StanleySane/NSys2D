// Demf.h: interface for the CDemf class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMF_H__F5362BC2_CB61_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_DEMF_H__F5362BC2_CB61_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Elem.h"

class CShemeDoc;
class CSheme;

class CDemf : public CElem  
{
	void InitBy( const CDemf& );
private:
	double a_X1;
	double a_X3;
	double a_X5;
	double a_XS;
//	CString str_X1;
//	CString str_X3;
//	CString str_X5;
//	CString str_XS;
//	CString str_XX;
public:
	CShemeExpr m_XX;
	int type;
//	CString GetStrXS();
	virtual void Serialize( CArchive &ar, int _sv );
	int SetMatrmP( CMatr &, CMatr &, CMatr &, CMatr *, int, double, std::string *pMsg = NULL );
	void SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC, std::string *pMsg = NULL );

	void SetVarState( double x, double v, double a, double t );

	void GetMatrM( CMatr&, std::string *pMsg = NULL );
	void GetMatrD( CMatr&, std::string *pMsg = NULL );
	void GetMatrC( CMatr&, std::string *pMsg = NULL );

	bool SetDemfX1( double );
	bool SetDemfX3( double );
	bool SetDemfX5( double );
	bool SetDemfXS( double );
	bool SetDemfXX( const CString& );

	double GetDemfX(int i);
	double GetDemfXX( double x, double v, double a, double t, std::string &ec );
	//получить строку для диалога в нужную строку (i)
//	CString GetStrX(int i);

	int GoDlg(CListKnot *pListKnot, bool full = true );
	bool SetCommonProperties( const CElem* elem );
	void Draw(CDC *pDC, CParamView *pParamView);
	void DrawGL( CShemeDoc*, int );
	CString GetName() const;

	CDemf( CKnot *kn1, CKnot *kn2, CSheme *p = NULL );
	virtual ~CDemf();
	CDemf( const CDemf& );
	CDemf& operator=( const CDemf& );

};

#endif // !defined(AFX_DEMF_H__F5362BC2_CB61_11D2_AF23_BB2B1C460D22__INCLUDED_)
