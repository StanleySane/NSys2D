// SpectrParam.h: interface for the CSpectrParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPECTRPARAM_H__D6CE3224_AB05_11D3_AF28_B4D2D506A1A2__INCLUDED_)
#define AFX_SPECTRPARAM_H__D6CE3224_AB05_11D3_AF28_B4D2D506A1A2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ShemeExpr.h"

class CSheme;

class CSpectrParam  
{
	void InitBy( const CSpectrParam& );
public:
	CSheme *m_pSheme;

	CSpectrParam( CSheme *p = NULL );
	virtual ~CSpectrParam();
	CSpectrParam( const CSpectrParam& );
	CSpectrParam& operator=( const CSpectrParam& );

	void SetVarState( double );
	double GetMaxW();
	double GetValue(double Tt);
	void EndIntegr();
	int BeginIntegr(double _T);
	void Serialize( CArchive&, int );
	double GetSpectr( double w, std::string *pMsg = NULL );
	void GoDlg();

	double m_1S, m_1Wc;
	double m_2S, m_2a;
	double m_3S, m_3Wo, m_3a;
	double m_4S, m_4a, m_4b;
	double m_5S, m_5a, m_5b;
	CShemeExpr m_Sw;
	double m_6Wmin, m_6Wmax;
	double m_Seed, m_Wmax, m_Late;
//	CString strEdit[20];
//	double param[20];
	int TypeSpectr;
	int TypeInit;

	//Инициализация для интегрирования
	double pi;
	double dt;
	double T;
	int N_2;
private:
	double *fi;
	double *A;
};

#endif // !defined(AFX_SPECTRPARAM_H__D6CE3224_AB05_11D3_AF28_B4D2D506A1A2__INCLUDED_)
