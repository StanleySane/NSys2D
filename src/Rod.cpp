// Rod.cpp: implementation of the CRod class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "Rod.h"
#include "RodDlg.h"
#include "matr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRod::CRod(CKnot *kn1, CKnot *kn2):CElem(kn1,kn2)
{
	SetE(CString("1"));  
	SetF(CString("1"));  
	SetJx(CString("1"));
	SetM(CString("1"));
	TypeElem=IDC_ROD;
	FreeA1=FreeA2=0;
}

CRod::~CRod()
{

}

double CRod::GetE()
{
	return E;
}

double CRod::GetJx()
{
	return Jx;
}

double CRod::SetE(CString & str)
{
	CExpression e;
	double val;

	if (!e.IsNum(str,&val))
	{
		str_E=str;
		E=val;
		return val;
	}
	return -1;
}

double CRod::SetJx(CString & str)
{
	CExpression e;
	double val;

	if (!e.IsNum(str,&val))
	{
		str_Jx=str;
		Jx=val;
		return val;
	}
	return -1;
}

void CRod::Draw(CDC * pDC, CParamView *pParamView)
{
	POINT point1=ShemeToScreen(knot1->GetCoord(pParamView->MultMove),pParamView);
	POINT point2=ShemeToScreen(knot2->GetCoord(pParamView->MultMove),pParamView);

	COLORREF col;
	col=(SelectMode?RGB(250,0,0):RGB(0,0,250));
	if (pParamView->Gray)
		col=RGB(200,200,200);

	CPen pen(PS_SOLID|PS_INSIDEFRAME/*|PS_GEOMETRIC*/,2,col);
	CPen *pOld=(CPen*)pDC->SelectObject(&pen);

	if (pParamView->MultMove==0)
	{
		pDC->MoveTo(point1.x, point1.y);
		pDC->LineTo(point2.x, point2.y);
	}
	else
	{	
		//Определение локальных перемещений
		CMatr Ugl(6,1), Uloc(6,1), T(6,6);
		CMatr mM(6,6), A(6,1);

		double L=GetLength();

		Ugl[0][0]=knot1->MoveX*pParamView->MultMove;
		Ugl[1][0]=knot1->MoveY*pParamView->MultMove;
		Ugl[2][0]=knot1->MoveA[FreeA1]*pParamView->MultAngl;
		Ugl[3][0]=knot2->MoveX*pParamView->MultMove;
		Ugl[4][0]=knot2->MoveY*pParamView->MultMove;
		Ugl[5][0]=knot2->MoveA[FreeA2]*pParamView->MultAngl;

		GetMatrT(T, 6);

		Uloc=T*Ugl;//T*Ugl;
		mM[0][0]=0;
		mM[3][0]=L;

		mM[1][1]=0;
		mM[2][1]=0;
		mM[4][1]=L*L*L;
		mM[5][1]=3*L*L;
	
		mM[1][2]=0;
		mM[2][2]=0;
		mM[4][2]=L*L;
		mM[5][2]=2*L;

		mM[0][3]=1;
		mM[3][3]=1;

		mM[1][4]=0;
		mM[2][4]=1;
		mM[4][4]=L;
		mM[5][4]=1;

		mM[1][5]=1;
		mM[2][5]=0;
		mM[4][5]=1;
		mM[5][5]=0;

		if (!mM.SolveSystem(Uloc, A)) 
			A.ClearData();
		
		CMatr T1(2,2), T_1(2,2);
		GetMatrT(T1,2);
		T_1=!T1;//!T1;

		double tStep=1.0/(sqrt((point2.x-point1.x)*(point2.x-point1.x)
								+(point2.y-point1.y)*(point2.y-point1.y))+1);
		CCoordD c1=knot1->GetCoord();
		CCoordD c2=knot2->GetCoord();

		CMatr Uu(2,1), U(2,1);
		for (double t=0;t<=1;t+=tStep)
		{
			CCoordD c=knot1->GetCoord();
			Uu[0][0]=A[0][0]*t*L+A[3][0];
			Uu[1][0]=A[1][0]*pow(t*L,3)+A[2][0]*pow(t*L,2)+A[4][0]*t*L+A[5][0];
			U=T_1*Uu;
			CCoordD cc(
				U[0][0]+(c2.x-c1.x)*t+c1.x,
				U[1][0]+(c2.y-c1.y)*t+c1.y
				);
			POINT p=ShemeToScreen(cc, pParamView);

			if (t==0)	pDC->MoveTo(p);
			else		pDC->LineTo(p);
		}
	}
	knot1->Draw(pDC,pParamView);
	knot2->Draw(pDC,pParamView);

	pDC->SelectObject(pOld);
}

CString CRod::GetStrE()
{
	return str_E;
}

CString CRod::GetStrJx()
{
	return str_Jx;
}

int CRod::GoDlg(CListKnot *pListKnot)
{
	CRodDlg dlg(pListKnot, this);
	if (dlg.DoModal()==IDOK) 
		return 1;
	return 0;
}

double CRod::SetM(CString & str)
{
	CExpression e;
	double val;

	if (!e.IsNum(str,&val))
	{
		str_m0=str;
		m0=val;
		return val;
	}
	return -1;
}

double CRod::GetM()
{
	return m0;
}

CString CRod::GetStrM()
{
	return str_m0;
}

void CRod::SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC)
{
	CMatr locM(6,6),locC(6,6),T(6,6);
	GetMatrT(T,6);

	double m=GetM();
	double F=GetF();
	double E=GetE();
	double J=GetJx();
	double L=GetLength();

	//Номера степеней свободы
	int N[6];
	N[0]=knot1->nXRez;
	N[1]=knot1->nYRez;
	N[2]=knot1->nARez[FreeA1];
	N[3]=knot2->nXRez;
	N[4]=knot2->nYRez;
	N[5]=knot2->nARez[FreeA2];
	
//матрица масс
	locM[0][0]= m*L/3.0;
	locM[3][3]= m*L/3.0;
	locM[3][0]= m*L/6.0;
//матрица жёсткости
	locC[0][0]= E*F/L;
	locC[3][3]= E*F/L;
	locC[3][0]=-E*F/L;

	//жестко закрепленный стержень по обоим краям
//	if ((knot1->ConnectType==0)&&(knot2->ConnectType==0))
	{
		//матрица масс
		locM[1][1]= m*L*13.0/35.0;
		locM[2][1]= m*L*L*11.0/210.0;
		locM[4][1]= m*L*9.0/70.0;
		locM[5][1]=-m*L*L*13.0/420.0;

		locM[2][2]= m*L*L*L/105.0;
		locM[4][2]= m*L*L*13.0/420.0;
		locM[5][2]=-m*L*L*L*1/140.0;

		locM[4][4]= m*L*13.0/35.0;
		locM[5][4]=-m*L*L*11.0/210.0;

		locM[5][5]= m*L*L*L/105.0;
	
		//матрица жёсткости
		locC[1][1]= 12*E*J/(L*L*L);
		locC[2][1]= 6*E*J/(L*L);
		locC[4][1]=-12*E*J/(L*L*L);
		locC[5][1]= 6*E*J/(L*L);

		locC[2][2]= 4*E*J/L;
		locC[4][2]=-6*E*J/(L*L);
		locC[5][2]= 2*E*J/L;
		
		locC[4][4]= 12*E*J/(L*L*L);
		locC[5][4]=-6*E*J/(L*L);

		locC[5][5]= 4*E*J/L;

	}
	//с одной стороны шарнирное опирание
/*	if ( ((knot1->ConnectType==0)&&(knot2->ConnectType!=0))||
		 ((knot1->ConnectType!=0)&&(knot2->ConnectType==0)) )
	{
		//матрица масс
		locM[1][1]= m*L*17.0/35.0;
		locM[2][1]= m*L*L*3.0/35.0;
		locM[4][1]= m*L*39.0/280.0;
		locM[5][1]=-m*L*L*19.0/420.0;

		locM[2][2]= m*L*L*L*2/105.0;
		locM[4][2]= m*L*L*11.0/280.0;
		locM[5][2]=-m*L*L*L/84.0;

		locM[4][4]= m*L*33.0/140.0;
		locM[5][4]=-m*L*L*4.0/105.0;

		locM[5][5]= m*L*L*L/105.0;

		//матрица жёсткости
		locC[1][1]= 3*E*J/(L*L*L);
		locC[2][1]= 3*E*J/(L*L);
		locC[4][1]=-3*E*J/(L*L*L);
		locC[5][1]= 0;

		locC[2][2]= 3*E*J/L;
		locC[4][2]=-3*E*J/(L*L);
		locC[5][2]= 0;
		
		locC[4][4]= 3*E*J/(L*L*L);
		locC[5][4]= 0;

		locC[5][5]= 4*E*J/L;

		//Если первый узел шарнирно, то меняем степени свободы местами
		if ((knot1->ConnectType!=0)&&(knot2->ConnectType==0))
		{
			N[0]=knot2->nXRez;
			N[1]=knot2->nYRez;
			N[2]=knot2->nARez[FreeA2];
			N[3]=knot1->nXRez;
			N[4]=knot1->nYRez;
			N[5]=knot1->nARez[FreeA1];
		}
	}
	//с обоих сторон шарнирное опирание
	if ((knot1->ConnectType!=0)&&(knot2->ConnectType!=0))
	{
		//матрица масс
		locM[1][1]= m*L/3.0;
		locM[2][1]= m*L*L*1.0/15.0;
		locM[4][1]= m*L/6.0;
		locM[5][1]=-m*L*L*7.0/120.0;

		locM[2][2]= m*L*L*L*2/105.0;
		locM[4][2]= m*L*L*7.0/120.0;
		locM[5][2]=-m*L*L*L*31.0/1680.0;

		locM[4][4]= m*L/3.0;
		locM[5][4]=-m*L*L/15.0;

		locM[5][5]= m*L*L*L*2/105.0;

		//матрица жёсткости
//		locC[1][1]= 12*E*J/(L*L*L);
//		locC[2][1]= 6*E*J/(L*L);
//		locC[4][1]=-12*E*J/(L*L*L);
//		locC[5][1]= 6*E*J/(L*L);

		locC[2][2]= 3*E*J/L;
//		locC[4][2]=-6*E*J/(L*L);
		locC[5][2]=-3*E*J/L/2.0;
		
//		locC[4][4]= 12*E*J/(L*L*L);
//		locC[5][4]=-6*E*J/(L*L);

		locC[5][5]= 3*E*J/L;
	}*/

	locM.CopyDownToUp();
	locM=!T*locM*T;
	locC.CopyDownToUp();
	locC=!T*locC*T;
	
	for (int i=0;i<6;i++)
		for(int j=0;j<6;j++)
			if ((N[i]>=0)&&(N[j]>=0))
			{
				mM[N[i]][N[j]]+=locM[i][j];
				mC[N[i]][N[j]]+=locC[i][j];
			}
}

double CRod::GetF()
{
	return F;
}

CString CRod::GetStrF()
{
	return str_F;
}

double CRod::SetF(CString & str)
{
	CExpression e;
	double val;

	if (!e.IsNum(str,&val))
	{
		str_F=str;
		F=val;
		return val;
	}
	return -1;
}

int CRod::SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, int i, double Tt)
{
//	return 0;
/*	CCoordD m1,m2;
	if (knot1->nXRez>=0) m1.x=RezY1[knot1->nXRez][i];
	if (knot1->nYRez>=0) m1.y=RezY1[knot1->nYRez][i];
	
	if (knot2->nXRez>=0) m2.x=RezY1[knot2->nXRez][i];
	if (knot2->nYRez>=0) m2.y=RezY1[knot2->nYRez][i];
//	CCoordD m1((RezY1[knot1->nXRez][i],RezY1[knot1->nYRez][i]));
//	CCoordD m2((RezY1[knot2->nXRez][i],RezY1[knot2->nYRez][i]));

	CCoordD c1=knot1->GetCoord()+m1;
	CCoordD c2=knot2->GetCoord()+m2;

	double mom=0;
	if (knot2->nYRez>=0)
		mom+=(c2.x-c1.x)*knot2->GetPy(RezY1[knot2->nYRez][i],RezY2[knot2->nYRez][i],Tt);
	if (knot2->nXRez>=0)
		mom-=(c2.y-c1.y)*knot2->GetPx(RezY1[knot2->nXRez][i],RezY2[knot2->nXRez][i],Tt);

	if (knot1->nARez[FreeA1]>=0)
		mP[knot1->nARez[FreeA1]][0]-=mom;

	mom=0;
	if (knot1->nYRez>=0)
		mom+=(c1.x-c2.x)*knot1->GetPy(RezY1[knot1->nYRez][i],RezY1[knot1->nYRez][i],Tt);
	if (knot1->nXRez>=0)
		mom-=(c1.y-c2.y)*knot1->GetPx(RezY1[knot1->nXRez][i],RezY1[knot1->nXRez][i],Tt);

	if (knot2->nARez[FreeA2]>=0)
		mP[knot2->nARez[FreeA2]][0]-=mom;*/
	
	return 0;
}

void CRod::Serialize(CArchive & ar)
{
	CElem::Serialize(ar);

	if (ar.IsStoring())
	{	// storing code
		ar << GetStrF();
		ar << GetStrJx();
		ar << GetStrE();
		ar << GetStrM();
	}
	else
	{	// loading code
		CString F,E,Jx,M;
		ar >> F >> Jx >> E >> M;
		SetF(F);
		SetJx(Jx);
		SetE(E);
		SetM(M);
	}
}
