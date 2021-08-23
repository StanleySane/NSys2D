// SpectrParam.h: interface for the CSpectrParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPECTRPARAM_H__D6CE3224_AB05_11D3_AF28_B4D2D506A1A2__INCLUDED_)
#define AFX_SPECTRPARAM_H__D6CE3224_AB05_11D3_AF28_B4D2D506A1A2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSpectrParam  
{
public:
	double GetMaxW();
	double GetValue(double Tt);
	void EndIntegr();
	int BeginIntegr(double _T);
	void Serialize(CArchive & ar);
	double GetSpectr(double w);
	void GoDlg();
	CSpectrParam();
	virtual ~CSpectrParam();
	CString strEdit[20];
	double param[20];
	int TypeSpectr;
	int TypeInit;

	//Инициализация для интегрирования
	double pi;
	double dt;
	double T;
	int N_2;
	double *fi;
	double *A;
};

#endif // !defined(AFX_SPECTRPARAM_H__D6CE3224_AB05_11D3_AF28_B4D2D506A1A2__INCLUDED_)
