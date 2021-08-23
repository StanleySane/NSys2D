// Demf.cpp: implementation of the CDemf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "Demf.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "demfdlg.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDemf::CDemf(CKnot *kn1, CKnot *kn2):CElem(kn1,kn2)
{
	SetDemfX("1",1);	
	SetDemfX("0",3);	
	SetDemfX("0",5);	
	SetDemfX("0",6);	
	SetDemfX("0",0);	
	type=1;
	TypeElem=IDC_DEMF;
}

CDemf::~CDemf()
{

}

void CDemf::Draw(CDC * pDC, CParamView * pParamView)
{
	CPoint point1=ShemeToScreen(knot1->GetCoord(pParamView->MultMove),pParamView);
	CPoint point2=ShemeToScreen(knot2->GetCoord(pParamView->MultMove),pParamView);

	COLORREF col;
	col=(SelectMode?RGB(250,0,0):RGB(0,0,250));
	if (pParamView->Gray)
		col=RGB(200,200,200);

	CPen pen(PS_SOLID|PS_GEOMETRIC,1,col);
	CPen *pOld=(CPen*)pDC->SelectObject(&pen);

	CPoint vect=point2-point1;
	double len2=vect.x*vect.x+vect.y*vect.y;

	if (len2<144) 
	{
		pDC->MoveTo(point1.x,point1.y);
		pDC->LineTo(point2.x,point2.y);
	}
	else
	{
		double rad1=(sqrt(len2)/2-5)/sqrt(len2);
		double rad2=(sqrt(len2)/2-2)/sqrt(len2);
		
		CPoint point3=CPoint(point1.x+int(vect.x*rad1), point1.y+int(vect.y*rad1));

		pDC->MoveTo(point1.x,point1.y);
		pDC->LineTo(point3.x,point3.y);

		pDC->MoveTo(point2.x,point2.y);
		pDC->LineTo(point1.x+int(vect.x*rad2),point1.y+int(vect.y*rad2) );

		CPoint vectort=CPoint(-vect.y,vect.x);

		double normvectort=sqrt(vectort.x*vectort.x+vectort.y*vectort.y);
		CPoint point4=CPoint(point3.x+int(vectort.x*3/normvectort),
							 point3.y+int(vectort.y*3/normvectort) );
		CPoint point5=CPoint(point3.x-int(vectort.x*3/normvectort),
							 point3.y-int(vectort.y*3/normvectort) );

		pDC->MoveTo(point4.x,point4.y);
		pDC->LineTo(point5.x,point5.y);
		
		CPoint point6=CPoint(point4.x+int(vect.x/sqrt(len2)*10),
							 point4.y+int(vect.y/sqrt(len2)*10) );
		CPoint point7=CPoint(point5.x+int(vect.x/sqrt(len2)*10),
							 point5.y+int(vect.y/sqrt(len2)*10) );

		pDC->MoveTo(point4.x,point4.y);
		pDC->LineTo(point6.x,point6.y);

		pDC->MoveTo(point5.x,point5.y);
		pDC->LineTo(point7.x,point7.y);
	}

	knot1->Draw(pDC,pParamView);
	knot2->Draw(pDC,pParamView);

	pDC->SelectObject(pOld);
}

int CDemf::GoDlg(CListKnot * pListKnot)
{
	CDemfDlg dlg(pListKnot, this);
	if (dlg.DoModal()==IDOK) return 1;
	return 0;
}


double CDemf::SetDemfX(CString str, int i)
{
	CExpression e;
	double val;

	switch(i)
	{
	case 1:
		if (!e.IsNum(str,&val))
		{
			str_X1=str;
			a_X1=val;		//type=1;
			return val;
		}
		break;
	case 3:
		if (!e.IsNum(str,&val))
		{
			str_X3=str;
			a_X3=val;		//type=3;
			return val;
		}
		break;
	case 5:
		if (!e.IsNum(str,&val))
		{
			str_X5=str;
			a_X5=val;		//type=5;
			return val;
		}
		break;
	case 6:
		if (!e.IsNum(str,&val))
		{
			str_XS=str;
			a_XS=val;		//type=6;
			return val;
		}
		break;
	case 0:
		CIDValuesMap idv;
		idv.SetAt(_T("x"),0.1);
		idv.SetAt(_T("x1"),0.1);
		idv.SetAt(_T("t"),0.1);
		if (!e.IsNum(str,&val,&idv))
		{
			str_XX=str;
			a_XX=val;		//type=0;
			return val;
		}
		break;
	}
	return -1;
}






CString CDemf::GetStrX(int i)
{
	switch (i)
	{
	case 1: return str_X1;
	case 3: return str_X3;
	case 5: return str_X5;
	case 6: return str_XS;
	case 0: return str_XX;
	};
	return _T("-1");
}

double CDemf::GetDemfX(int i)
{
	switch (i)
	{
	case 1: return a_X1;
	case 3: return a_X3;
	case 5: return a_X5;
	case 6: return a_XS;
	case 0: return a_XX;
	};
	return -1;
}

void CDemf::SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC)
{
	if (type==1)
	{
		CMatr loc_matr(4,4),T(4,4);
		double a=GetDemfX(1);
		GetMatrT(T,4);

		loc_matr[0][0]=a;
		loc_matr[2][2]=a;
		loc_matr[2][0]=-a;
		loc_matr[0][2]=-a;
		
		loc_matr=!T*loc_matr*T;

		int N[4];
		N[0]=knot1->nXRez;
		N[1]=knot1->nYRez;
		N[2]=knot2->nXRez;
		N[3]=knot2->nYRez;

		for (int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				if ((N[i]>=0)&&(N[j]>=0)) mD[N[i]][N[j]]+=loc_matr[i][j];
	}
}

int CDemf::SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, int i, double Tt)
{
	if (type==1) return 0;

	CMatr Vgl(4,1), Vloc(4,1), T(4,4), Ploc(4,1), Pgl(4,1);

	if (knot1->nXRez>=0) Vgl[0][0]=RezY2[knot1->nXRez][i];
	if (knot1->nYRez>=0) Vgl[1][0]=RezY2[knot1->nYRez][i];

	if (knot2->nXRez>=0) Vgl[2][0]=RezY2[knot2->nXRez][i];
	if (knot2->nYRez>=0) Vgl[3][0]=RezY2[knot2->nYRez][i];

	GetMatrT(T,4);

	Vloc=T*Vgl;

	double VV=Vloc[2][0]-Vloc[0][0];
	
	switch (type)
	{
	case 3:
			Ploc[0][0]= a_X3*pow(VV,3);
			Ploc[2][0]=-a_X3*pow(VV,3);
			break;
	case 5:
			Ploc[0][0]= a_X5*pow(VV,5);
			Ploc[2][0]=-a_X5*pow(VV,5);
			break;
	case 6:
			if (VV>0)
			{
				Ploc[0][0]= a_XS;
				Ploc[2][0]=-a_XS;
			}
			if (VV<0)
			{
				Ploc[0][0]=-a_XS;
				Ploc[2][0]=+a_XS;
			}
			break;
	case 0:
			CExpression e;
			CIDValuesMap idv;
			idv.SetAt(_T("t"),Tt);

			CMatr Ugl(4,1), Uloc(4,1);

			if (knot1->nXRez>=0) Ugl[0][0]=RezY1[knot1->nXRez][i];
			if (knot1->nYRez>=0) Ugl[1][0]=RezY1[knot1->nYRez][i];
			if (knot2->nXRez>=0) Ugl[2][0]=RezY1[knot2->nXRez][i];
			if (knot2->nYRez>=0) Ugl[3][0]=RezY1[knot2->nYRez][i];

			Vloc=T*Vgl;

			idv.SetAt(_T("x"),  Uloc[2][0]-Uloc[0][0]);
			idv.SetAt(_T("x1"), VV);
			if (e.IsNum(str_XX,&a_XX,&idv))
				return -1;
			Ploc[0][0]= a_XX;
			Ploc[2][0]=-a_XX;
			break;
	}
	Pgl=!T*Ploc;

	if (knot1->nXRez>=0) mP[knot1->nXRez][0]+=Pgl[0][0];
	if (knot1->nYRez>=0) mP[knot1->nYRez][0]+=Pgl[1][0];
	if (knot2->nXRez>=0) mP[knot2->nXRez][0]+=Pgl[2][0];
	if (knot2->nYRez>=0) mP[knot2->nYRez][0]+=Pgl[3][0];

	return 0;

}

void CDemf::Serialize(CArchive & ar)
{
	CElem::Serialize(ar);

	if (ar.IsStoring())
	{	// storing code
		ar << GetStrX(1);
		ar << GetStrX(3);
		ar << GetStrX(5);
		ar << GetStrX(6);
		ar << GetStrX(0);
		ar << type;
	}
	else
	{	// loading code
		CString X3,X5,X1,XS,XX;
		ar >> X1 >> X3 >> X5 >> XS >> XX;
		SetDemfX(X1,1);
		SetDemfX(X3,3);
		SetDemfX(X5,5);
		SetDemfX(XS,6);
		SetDemfX(XX,0);
		ar >> type;
	}
}
