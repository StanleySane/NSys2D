// SpectrParam.cpp: implementation of the CSpectrParam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "SpectrParam.h"
#include "KnotSpectr.h"
#include "Expression.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpectrParam::CSpectrParam()
{
	for (int i=0;i<sizeof(param)/sizeof(double);i++)
	{
		param[i]=0;
		strEdit[i]=_T("0");
	}
	param[1]=1;
	strEdit[1]=_T("1");
	strEdit[15]=_T("5");
	param[15]=5;
	strEdit[16]=_T("127");
	param[16]=127;
	strEdit[18]=_T("10");
	param[18]=10;

	TypeSpectr=0;
	TypeInit=0;
	pi=acos(-1);
	fi=0;
	A=0;
}

CSpectrParam::~CSpectrParam()
{

}

void CSpectrParam::GoDlg()
{
	CKnotSpectr dlg(this);
	dlg.DoModal();
}

double CSpectrParam::GetSpectr(double w)
{
	double val=0;
//Стандартные спектральные плотности из 
//книги Витекберга стр.33.
	switch (TypeSpectr)
	{
	case 0:
			if (w<param[1]) val=param[0]*param[0]/(param[1]);
			break;
	case 1: if (w<param[18]) val=param[3]*param[2]*param[2]/(pi*(w*w+param[3]*param[3]));
			break;
	case 2: 
		{
			double s=param[4], w0=param[5], a=param[6];
			if (w<param[18]) val=s*s*a*((1/(a*a+(w-w0)*(w-w0)))+(1/(a*a+(w+w0)*(w+w0))))/2/pi;
			break;
		}
	case 3:
		{
			double s=param[7], a=param[8], b=param[9];
			if (w<param[18]) val=2*s*s*a*(a*a+b*b)/((w*w-b*b-a*a)*(w*w-b*b-a*a)+4*a*a*w*w)/pi;
			break;
		}
	case 4:
		{
			double s=param[10], a=param[11], b=param[12];
			if (w<param[18]) val=s*s*(exp(-(w+b)*(w+b)/(4*a*a))+exp(-(w-b)*(w-b)/(4*a*a)))/(4*a*sqrt(pi));
			break;
		}
	case 5:
			if ((w>=param[14])&&(w<=param[15]))
			{
				CExpression e;
				CIDValuesMap idv;
				idv.SetAt(_T("w"),w);
				//if (!
				e.IsNum(strEdit[13],&val,&idv);
			}
			break;
	}
	return (val<0)?0:val;
}

void CSpectrParam::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{	// storing code
		int n=sizeof(param)/sizeof(double);
		ar << n;
		for (int i=0;i<n;i++)
		{
			ar << param[i];
			ar << strEdit[i];
		}
		ar << TypeSpectr;
		ar << TypeInit;
	}
	else
	{	// loading code
		int n;
		ar >> n;
		for (int i=0;i<n;i++)
		{
			ar >> param[i];
			ar >> strEdit[i];
		}
		ar >> TypeSpectr;
		ar >> TypeInit;
	}
}

int CSpectrParam::BeginIntegr(double _T)
{
	if (A!=0) return 0;
	double Wmax=GetMaxW();
	dt=pi/Wmax;
	T=_T;
	N_2=int(T/(2*dt));
	fi=new double[N_2];
	A=new double[N_2];

	//Инициализация генератора случайных чисел
	if (TypeInit==1) srand((unsigned int)param[16]);
	else srand((unsigned int)time(0));

	//Вычисление амплитуд и фаз случайных колебений
	for (int k=0;k<N_2;k++)
	{
		fi[k]=rand()*2*pi/RAND_MAX;
		A[k]=sqrt(2*2*pi*GetSpectr(2*pi*k/T)/T);
	}
	return 1;
}

void CSpectrParam::EndIntegr()
{
	delete [] fi;
	fi=0;
	delete [] A;
	A=0;
}

double CSpectrParam::GetValue(double Tt)
{
	if (Tt<param[17]) return 0;
	double rez=0;

	for(int k=0;k<N_2;k++)
		rez+=A[k]*sin(2*pi*k*(Tt-param[17])/T+fi[k]);
	return rez;
}

double CSpectrParam::GetMaxW()
{
	double Wmax=1;
	switch (TypeSpectr)
	{
	case 0:
			Wmax=param[1];
			break;
	case 1:
	case 2: 
	case 3:
	case 4:	Wmax=param[18];
			break;
	case 5:
			Wmax=param[15];
			break;
	}
	if (Wmax<=0) Wmax=1;

	return Wmax;
}
