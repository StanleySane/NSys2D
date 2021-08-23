// Spring.cpp: implementation of the CSpring class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "Spring.h"

#include "SpringDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpring::CSpring(CKnot *kn1, CKnot *kn2):CElem(kn1,kn2)
{
	SetSprnX1("1");	
	SetSprnX3("0");	
	SetSprnX5("0");	
	SetSprnXX("0");	
	type=1;
	TypeElem=IDC_SPRING;
}

CSpring::~CSpring()
{

}

int CSpring::GoDlg(CListKnot * pListKnot, bool full )
{
	CSpringDlg dlg( pListKnot, this, full );
	if (dlg.DoModal()==IDOK) return 1;
	return 0;
}

void CSpring::Draw(CDC * pDC, CParamView * pParamView)
{
	CPoint point1=ShemeToScreen(knot1->GetCoord(pParamView->MultMove),pParamView);
	CPoint point2=ShemeToScreen(knot2->GetCoord(pParamView->MultMove),pParamView);

	COLORREF col;
	col=(SelectMode?RGB(250,0,0):RGB(0,0,250));
	if (pParamView->Gray)
		col=RGB(200,200,200);

	CPen pen(PS_SOLID|PS_GEOMETRIC,1,col);
	CPen *pOld=(CPen*)pDC->SelectObject(&pen);

	CCoordD vect=point2-point1;
	double norm=sqrt(vect.x*vect.x+vect.y*vect.y);
	vect.x=(vect.x/norm);
	vect.y=(vect.y/norm);

	if (norm<14) 
	{
		pDC->MoveTo(point1.x,point1.y);
		pDC->LineTo(point2.x,point2.y);
	}
	else
	{
		const int len1=10;
		const int h=5;
		const double ang=70.0*3.141592/180.0;
		
		CPoint point3=CPoint(point1.x+int(vect.x*len1), point1.y+int(vect.y*len1));
		pDC->MoveTo(point1);
		pDC->LineTo(point3);

		CCoordD vect2=CCoordD(vect.x*h,vect.y*h);

		CPoint point5=CPoint(int(
						point3.x+vect2.x*cos(ang)-vect2.y*sin(ang)),
						int(point3.y+vect2.x*sin(ang)+vect2.y*cos(ang) ) );

		CPoint point6=CPoint(
						int(point3.x+vect2.x*cos(ang)+vect2.y*sin(ang)+vect2.x*2*cos(ang)),
						int(point3.y-vect2.x*sin(ang)+vect2.y*cos(ang)+vect2.y*2*cos(ang)) );

		int N=int((norm-2*len1)/(h*4*cos(ang))-0.5);
		double step=(norm-2*len1)/(N+0.5);
		
		CCoordD dpoint=CCoordD(
						vect.x*step,
						vect.y*step );
		
		pDC->MoveTo(point3);
		pDC->LineTo(point5);

		
		for (int i=0;i<N;i++)
		{
			pDC->LineTo(point6.x+int(dpoint.x*i),point6.y+int(dpoint.y*i));
			pDC->LineTo(point5.x+int(dpoint.x*(i+1)),point5.y+int(dpoint.y*(i+1)) );
		}
		pDC->LineTo(point1.x+int(vect.x*(norm-len1)),point1.y+int(vect.y*(norm-len1) ) );
		pDC->LineTo(point2);
	}

	//Номер элемента
	if( (m_Number)&&(!pParamView->Gray)&&(pParamView->m_bNumElems) )
	{
		pDC->SetBkColor(pDC->IsPrinting()?RGB(255,255,255):GetSysColor(COLOR_WINDOW));
		pDC->SetTextAlign( TA_LEFT|TA_TOP );	
		CFont *pOldFont = (CFont*)pDC->SelectObject(&(pParamView->m_fntElems));

		CString str; 
		str.Format("[%d]", m_Number );

		COLORREF oldClr = pDC->SetTextColor(pParamView->m_clrNumElems);
		int oldBkMode = pDC->SetBkMode(TRANSPARENT);

		CCoordD k1 = knot1->GetCoord(pParamView->MultMove);
		CCoordD k2 = knot2->GetCoord(pParamView->MultMove);
		CPoint point = ShemeToScreen( (k1+k2)/2, pParamView );//середина между двумя узлами
		pDC->TextOut( point.x, point.y, str );

		pDC->SetBkMode(oldBkMode);
		pDC->SetTextColor(oldClr);

		pDC->SelectObject(pOldFont);
	}

	knot1->Draw(pDC,pParamView);
	knot2->Draw(pDC,pParamView);

	pDC->SelectObject(pOld);
}

double CSpring::SetSprnX1(CString str)
{
	CExpression e;
	double val;

	if (!e.IsNum(str,&val))
	{
		str_X1=str;
		a_X1=val;
		type=1;
		return val;
	}
	return -1;
}

double CSpring::SetSprnX3(CString str)
{
	CExpression e;
	double val;

	if (!e.IsNum(str,&val))
	{
		str_X3=str;
		a_X3=val;
		type=3;
		return val;
	}
	return -1;
}

double CSpring::SetSprnX5(CString str)
{
	CExpression e;
	double val;

	if (!e.IsNum(str,&val))
	{
		str_X5=str;
		a_X5=val;
		type=5;
		return val;
	}
	return -1;
}

double CSpring::SetSprnXX(CString str)
{
//	CExpression e;
//	double val;

//	if (!e.IsNum(str,&val))
//	{
		str_XX=str;
		a_XX=0;//val
		type=0;
		return 0;
//	}
//	return -1;
}

double CSpring::GetSprnX1() const
{
	return a_X1;
}

double CSpring::GetSprnX3() const
{
	return a_X3;
}

double CSpring::GetSprnX5() const
{
	return a_X5;
}

double CSpring::GetSprnXX() const
{
	return a_XX;
}

CString CSpring::GetStrX1()
{
	return str_X1;
}

CString CSpring::GetStrX3()
{
	return str_X3;
}

CString CSpring::GetStrX5()
{
	return str_X5;
}

CString CSpring::GetStrXX()
{
	return str_XX;
}


void CSpring::SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC)
{
	if( type == 1 )
	{
		CMatr loc_matr;
		GetMatrC( loc_matr );

		int N[4];
		N[0]=knot1->nXRez;
		N[1]=knot1->nYRez;
		N[2]=knot2->nXRez;
		N[3]=knot2->nYRez;

		for (int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				if ((N[i]>=0)&&(N[j]>=0)) 
					mC[N[i]][N[j]]+=loc_matr[i][j];
	}
}

int CSpring::SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, int i, double Tt)
{
	if (type==1) return 0;

	CMatr Ugl(4,1), Uloc(4,1), T(4,4), Ploc(4,1), Pgl(4,1);

	if (knot1->nXRez>=0) Ugl[0][0]=RezY1[knot1->nXRez][i];
	if (knot1->nYRez>=0) Ugl[1][0]=RezY1[knot1->nYRez][i];

	if (knot2->nXRez>=0) Ugl[2][0]=RezY1[knot2->nXRez][i];
	if (knot2->nYRez>=0) Ugl[3][0]=RezY1[knot2->nYRez][i];

	GetMatrT(T,4);

	Uloc=T*Ugl;
	
	switch (type)
	{
	case 3:
			Ploc[0][0]= a_X3*pow(Uloc[2][0]-Uloc[0][0],3);
			Ploc[2][0]=-a_X3*pow(Uloc[2][0]-Uloc[0][0],3);
			break;
	case 5:
			Ploc[0][0]= a_X5*pow(Uloc[2][0]-Uloc[0][0],5);
			Ploc[2][0]=-a_X5*pow(Uloc[2][0]-Uloc[0][0],5);
			break;
	case 0:
			CExpression e;
			CIDValuesMap idv;
			idv.SetAt(_T("t"),Tt);

			CMatr Uvgl(4,1), Uvloc(4,1);

			if (knot1->nXRez>=0) Uvgl[0][0]=RezY2[knot1->nXRez][i];
			if (knot1->nYRez>=0) Uvgl[1][0]=RezY2[knot1->nYRez][i];
			if (knot2->nXRez>=0) Uvgl[2][0]=RezY2[knot2->nXRez][i];
			if (knot2->nYRez>=0) Uvgl[3][0]=RezY2[knot2->nYRez][i];

			Uvloc=T*Uvgl;

			idv.SetAt(_T("x"),  Uloc[2][0]-Uloc[0][0]);
			idv.SetAt(_T("x1"), Uvloc[2][0]-Uvloc[0][0]);
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

void CSpring::Serialize(CArchive & ar)
{
	CElem::Serialize(ar);

	if (ar.IsStoring())
	{	// storing code
		ar << GetStrX1();
		ar << GetStrX3();
		ar << GetStrX5();
		ar << GetStrXX();
		ar << type;
	}
	else
	{	// loading code
		CString X3,X5,X1,XX;
		ar >> X1 >> X3 >> X5 >> XX;
		SetSprnX1(X1);
		SetSprnX3(X3);
		SetSprnX5(X5);
		SetSprnXX(XX);
		ar >> type;
	}
}

bool CSpring::SetCommonProperties( CElem* elem )
{
	CSpring *pSpr = dynamic_cast<CSpring*>(elem);
	if( !pSpr )	return false;

	a_X1 = pSpr->a_X1;
	a_X3 = pSpr->a_X3;
	a_X5 = pSpr->a_X5;
	a_XX = pSpr->a_XX;
	str_X1 = pSpr->str_X1;
	str_X3 = pSpr->str_X3;
	str_X5 = pSpr->str_X5;
	str_XX = pSpr->str_XX;
	type = pSpr->type;

	return true;
}

void CSpring::GetMatrM( CMatr &matr ) const
{
	matr.ReSize( 4, 4 );
}

void CSpring::GetMatrD( CMatr &matr ) const
{
	matr.ReSize( 4, 4 );
}

void CSpring::GetMatrC( CMatr &matr ) const
{
	matr.ReSize( 4, 4 );
	if( type == 1)
	{
		CMatr T( 4, 4 );
		double c = GetSprnX1();
		GetMatrT( T, 4 );

		matr[0][0] = c;
		matr[2][2] = c;
		matr[2][0] = -c;
		matr[0][2] = -c;
		
		matr = !T*matr*T;
	}
}
