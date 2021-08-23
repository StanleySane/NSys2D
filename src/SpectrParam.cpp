// SpectrParam.cpp: implementation of the CSpectrParam class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "SpectrParam.h"
#include "KnotSpectr.h"
#include "Sheme.h"
#include "Elem.h"

#include<limits>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef max
#undef max
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpectrParam::CSpectrParam( CSheme *p ):m_pSheme(p)
{
//	for( int i = 0; i < sizeof(param)/sizeof(double); i++ )
//	{
//		param[i] = 0;
//		strEdit[i] = _T("0");
//	}
	m_1Wc = 1.0;
//	param[1] = 1.0;
//	strEdit[1]=_T("1");
//	strEdit[15]=_T("5");
//	param[15]=5;
	m_6Wmax = 5.0;
//	strEdit[16]=_T("127");
//	param[16]=127;
	m_Seed = 127.0;
//	strEdit[18]=_T("10");
//	param[18]=10;
	m_Wmax = 10.0;
	m_Sw.Reset( CString(""), (p == NULL)?(NULL):(&p->m_VarsTable) );

	TypeSpectr = 0;
	TypeInit = 0;
	pi = CNSys2DApp::M_PI;
	fi = NULL;
	A = NULL;
}

CSpectrParam::~CSpectrParam()
{
	delete [] fi;
	fi = NULL;
	delete [] A;
	A = NULL;
}

CSpectrParam::CSpectrParam( const CSpectrParam &obj ):fi(NULL), A(NULL), m_pSheme(NULL)
{
	InitBy(obj);
}

CSpectrParam& CSpectrParam::operator=( const CSpectrParam &obj )
{
	if( this != (&obj) )
		InitBy(obj);
	return *this;
}

void CSpectrParam::InitBy( const CSpectrParam &obj )
{
	int i;
	if( obj.m_pSheme )
		m_pSheme = obj.m_pSheme;
//	for( int i = 0; i < 20; i++ )
//	{
//		strEdit[i] = obj.strEdit[i];
//		param[i] = obj.param[i];
//	}
	m_1S = obj.m_1S;
	m_1Wc = obj.m_1Wc;
	m_2S = obj.m_2S;
	m_2a = obj.m_2a;
	m_3S = obj.m_3S;
	m_3Wo = obj.m_3Wo;
	m_3a = obj.m_3a;
	m_4S = obj.m_4S;
	m_4a = obj.m_4a;
	m_4b = obj.m_4b;
	m_5S = obj.m_5S;
	m_5a = obj.m_5a;
	m_5b = obj.m_5b;
	m_Sw.InitBy( obj.m_Sw );
	m_6Wmin = obj.m_6Wmin;
	m_6Wmax = obj.m_6Wmax;
	m_Seed = obj.m_Seed;
	m_Wmax = obj.m_Wmax;
	m_Late = obj.m_Late;

	TypeSpectr = obj.TypeSpectr;
	TypeInit = obj.TypeInit;

	pi = obj.pi;
	dt = obj.dt;
	T = obj.T;
	N_2 = obj.N_2;
	delete [] fi;
	delete [] A;
	if( obj.fi != NULL )
	{
		try
		{
			fi = new double[N_2];
		}
		catch( bad_alloc& )
		{
			fi = NULL;
		}
		if( fi != NULL )
		{
			for( i = 0; i < N_2; i++ )
				fi[i] = obj.fi[i];
		}
	}
	if( obj.A != NULL )
	{
		try
		{
			A = new double[N_2];
		}
		catch( bad_alloc& )
		{
			A = NULL;
		}
		if( A != NULL )
		{
			for( i = 0; i < N_2; i++ )
				A[i] = obj.A[i];
		}
	}
}
//////////////////////////////////////////////////////////////////

void CSpectrParam::GoDlg()
{
	CKnotSpectr dlg(this);
	dlg.DoModal();
}

double CSpectrParam::GetSpectr( double w, std::string *pMsg )
{
	double val = 0.0;
//Стандартные спектральные плотности из 
//книги Витекберга стр.33.
	switch( TypeSpectr )
	{
	case 0:
//		if( w < param[1] )
//			val = param[0]*param[0]/(param[1]);
		if( w < m_1Wc )
			val = m_1S*m_1S/m_1Wc;
		break;
	case 1: 
//		if( w < param[18] )
//			val = param[3]*param[2]*param[2]/(pi*(w*w+param[3]*param[3]));
		if( w < m_Wmax )
			val = m_2a*m_2S*m_2S/(pi*(w*w+m_2a*m_2a));
		break;
	case 2: 
		{
//			double s = param[4], w0 = param[5], a = param[6];
//			if( w < param[18] )
//				val = s*s*a*((1/(a*a+(w-w0)*(w-w0)))+(1/(a*a+(w+w0)*(w+w0))))/2/pi;
			if( w < m_Wmax )
				val = m_2S*m_2S*m_3a*((1/(m_3a*m_3a+(w-m_3Wo)*(w-m_3Wo)))+(1/(m_3a*m_3a+(w+m_3Wo)*(w+m_3Wo))))/2/pi;
			break;
		}
	case 3:
		{
//			double s = param[7], a = param[8], b = param[9];
//			if( w < param[18] )
//				val = 2*s*s*a*(a*a+b*b)/((w*w-b*b-a*a)*(w*w-b*b-a*a)+4*a*a*w*w)/pi;
			if( w < m_Wmax )
				val = 2.0*m_4S*m_4S*m_4a*(m_4a*m_4a+m_4b*m_4b)/((w*w-m_4b*m_4b-m_4a*m_4a)*(w*w-m_4b*m_4b-m_4a*m_4a)+4*m_4a*m_4a*w*w)/pi;
			break;
		}
	case 4:
		{
//			double s = param[10], a = param[11], b = param[12];
//			if( w < param[18] ) 
//				val = s*s*(exp(-(w+b)*(w+b)/(4*a*a))+exp(-(w-b)*(w-b)/(4*a*a)))/(4*a*sqrt(pi));
			if( w < m_Wmax ) 
				val = m_5S*m_5S*(exp(-(w+m_5b)*(w+m_5b)/(4*m_5a*m_5a))+exp(-(w-m_5b)*(w-m_5b)/(4*m_5a*m_5a)))/(4*m_5a*sqrt(pi));
			break;
		}
	case 5:
		{
			if( (w >= m_6Wmin)&&(w <= m_6Wmax) )
			{
				SetVarState( w );
				val = m_Sw.GetValue();
				if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
				{
					ShemeExprErr err = m_Sw.GetRunErrorCode();
					if( err != SEE_NOERR )
					{
						(*pMsg) = m_Sw.GetFullErrorMsg(err);
						return 0.0;
					}
				}
			}
		}
		break;
	default:
		ASSERT(FALSE);
	}
	return (val<0.0)?0.0:val;
}

void CSpectrParam::Serialize( CArchive &ar, int _sv )
{
	ShemeVersion sv = static_cast<ShemeVersion>(_sv);
	if (ar.IsStoring())
	{	// storing code
		if( sv <= VER_EQ30 )
		{
			int n = 20;
			ar << n;
			double param[20] =
			{
				m_1S, m_1Wc,
				m_2S, m_2a,
				m_3S, m_3Wo, m_3a,
				m_4S, m_4a, m_4b,
				m_5S, m_5a, m_5b,
				0.0,
				m_6Wmin, m_6Wmax,
				m_Seed, m_Wmax, m_Late,
				0.0
			};
			param[13] = m_Sw.GetValue();
			CString strEdit[20];
			strEdit[13] = m_Sw.GetExpr().c_str();
			CString str;
			str.Format("%.16g", m_1S );
			strEdit[0] = str;
			str.Format("%.16g", m_1Wc );
			strEdit[1] = str;
			str.Format("%.16g", m_2S );
			strEdit[2] = str;
			str.Format("%.16g", m_2a );
			strEdit[3] = str;
			str.Format("%.16g", m_3S );
			strEdit[4] = str;
			str.Format("%.16g", m_3Wo );
			strEdit[5] = str;
			str.Format("%.16g", m_3a );
			strEdit[6] = str;
			str.Format("%.16g", m_4S );
			strEdit[7] = str;
			str.Format("%.16g", m_4a );
			strEdit[8] = str;
			str.Format("%.16g", m_4b );
			strEdit[9] = str;
			str.Format("%.16g", m_5S );
			strEdit[10] = str;
			str.Format("%.16g", m_5a );
			strEdit[11] = str;
			str.Format("%.16g", m_5b );
			strEdit[12] = str;
			str.Format("%.16g", m_6Wmin );
			strEdit[14] = str;
			str.Format("%.16g", m_6Wmax );
			strEdit[15] = str;
			str.Format("%.16g", m_Seed );
			strEdit[16] = str;
			str.Format("%.16g", m_Wmax );
			strEdit[18] = str;
			str.Format("%.16g", m_Late );
			strEdit[17] = str;
			str.Format("%.16g", 0.0 );
			strEdit[19] = str;
			for( int i = 0; i < n; i++ )
			{
				ar << param[i];
				ar << strEdit[i];
			}
		}
		else
		{
			ar << m_1S << m_1Wc << m_2S << m_2a << m_3S;
			ar << m_3Wo << m_3a << m_4S << m_4a << m_4b;
			ar << m_5S << m_5a << m_5b;
			m_Sw.Serialize(ar);
			ar << m_6Wmin << m_6Wmax;
			ar << m_Seed << m_Wmax << m_Late;
		}
		ar << TypeSpectr;
		ar << TypeInit;
	}
	else
	{	// loading code
		if( sv <= VER_EQ30 )
		{
			int n;
			ar >> n;
			if( n >= 18 )
			{
				double param[20];
				CString strEdit[20];
				for( int i = 0; i < n; i++ )
				{
					ar >> param[i];
					ar >> strEdit[i];
				}
				m_1S = param[0];
				m_1Wc = param[1];
				m_2S = param[2];
				m_2a = param[3];
				m_3S = param[4];
				m_3Wo = param[5];
				m_3a = param[6];
				m_4S = param[7];
				m_4a = param[8]; 
				m_4b = param[9];
				m_5S = param[10]; 
				m_5a = param[11]; 
				m_5b = param[12];
				m_Sw.Reset( strEdit[13] );
				m_6Wmin = param[14];
				m_6Wmax = param[15];
				m_Seed = param[16];
				m_Wmax = param[18];
				m_Late = param[17];
			}
		}
		else
		{
			ar >> m_1S >> m_1Wc >> m_2S >> m_2a >> m_3S;
			ar >> m_3Wo >> m_3a >> m_4S >> m_4a >> m_4b;
			ar >> m_5S >> m_5a >> m_5b;
			m_Sw.Serialize(ar);
			ar >> m_6Wmin >> m_6Wmax;
			ar >> m_Seed >> m_Wmax >> m_Late;
		}
		ar >> TypeSpectr;
		ar >> TypeInit;
	}
}

int CSpectrParam::BeginIntegr(double _T)
{
	if( (A != NULL)||(fi != NULL) )
		return 0;
	double Wmax = GetMaxW();
	dt = pi/Wmax;
	T = _T;
	N_2 = int(T/(2*dt));
	try
	{
		fi = new double[N_2];
	}
	catch( bad_alloc& )
	{
		fi = NULL;
		return 0;
	}
	try
	{
		A = new double[N_2];
	}
	catch( bad_alloc& )
	{
		A = NULL;
		return 0;
	}

	//Инициализация генератора случайных чисел
	if( TypeInit == 1 )
		//srand((unsigned int)param[16]);
		srand( (unsigned int)m_Seed );
	else
		srand((unsigned int)time(0));

	//Вычисление амплитуд и фаз случайных колебений
	string msg;
	for( int k = 0; k < N_2; k++ )
	{
		fi[k] = rand()*2*pi/RAND_MAX;
		A[k] = sqrt(4.0*pi*GetSpectr( 2*pi*k/T, &msg )/T);
		if( m_pSheme && m_pSheme->m_bValidateExpr && !msg.empty() )
		{
			AfxMessageBox( CString("Ошибка при вычислении выражения: ") + msg.c_str() );
			return 0;
		}
	}
	return 1;
}

void CSpectrParam::EndIntegr()
{
	delete [] fi;
	fi = NULL;
	delete [] A;
	A = NULL;
}

double CSpectrParam::GetValue(double Tt)
{
//	if( (Tt < param[17])||(fi == NULL)||(A == NULL) )
	if( (Tt < m_Late)||(fi == NULL)||(A == NULL) )
		return 0.0;
	double rez = 0;
	double tmp;
	if( fabs(T) < 1e-300 )
		tmp = numeric_limits<double>::max();
	else
		tmp = 2.0*pi*(Tt-m_Late)/T;
//		tmp = 2.0*pi*(Tt-param[17])/T;

	for( int k = 0; k < N_2; k++ )
		rez += A[k]*sin(k*tmp + fi[k]);
	return rez;
}

double CSpectrParam::GetMaxW()
{
	double Wmax = 1.0;
	switch (TypeSpectr)
	{
	case 0:
		//Wmax = param[1];
		Wmax = m_1Wc;
		break;
	case 1:
	case 2: 
	case 3:
	case 4:	
		//Wmax = param[18];
		Wmax = m_Wmax;
		break;
	case 5:
		//Wmax = param[15];
		Wmax = m_6Wmax;
		break;
	}
	if( Wmax <= 0.0 )
		Wmax = 1.0;
	return Wmax;
}

void CSpectrParam::SetVarState( double w )
{
	if( m_pSheme )
	{
		m_pSheme->m_VarsTable.SetVarValue("x",0.0);
		m_pSheme->m_VarsTable.SetVarValue("v",0.0);
		m_pSheme->m_VarsTable.SetVarValue("t",0.0);
		m_pSheme->m_VarsTable.SetVarValue("a",0.0);
		m_pSheme->m_VarsTable.SetVarValue("w",w);
		m_pSheme->m_VarsTable.SetVarValue("cx",0.0);
		m_pSheme->m_VarsTable.SetVarValue("cy",0.0);
		m_pSheme->m_VarsTable.SetVarValue("cx1",0.0);
		m_pSheme->m_VarsTable.SetVarValue("cy1",0.0);
		m_pSheme->m_VarsTable.SetVarValue("cx2",0.0);
		m_pSheme->m_VarsTable.SetVarValue("cy2",0.0);
	}
}