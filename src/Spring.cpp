// Spring.cpp: implementation of the CSpring class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "Spring.h"

#include "SpringDlg.h"
#include "MovieView.h"
#include "ShemeDoc.h"
#include "Sheme.h"

#include<cmath>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpring::CSpring( CKnot *kn1, CKnot *kn2, CSheme *p ):CElem(kn1,kn2,p)
{
	SetSprnX1(1);	
	SetSprnX3(0);	
	SetSprnX5(0);	
//	SetSprnXX("0");	
	m_XX.Reset( string("0"), (p)?(&p->m_VarsTable):(NULL) );
	type = 1;
	TypeElem = IDC_SPRING;
}

CSpring::~CSpring()
{

}

CSpring::CSpring( const CSpring &elem ):CElem(elem)
{
	InitBy(elem);
}

CSpring& CSpring::operator=( const CSpring &elem )
{
	if( this != (&elem) )
		InitBy(elem);
	return *this;
}

void CSpring::InitBy( const CSpring &elem )
{
	SetCommonProperties( &elem );
}

int CSpring::GoDlg(CListKnot * pListKnot, bool full )
{
	CSpringDlg dlg( pListKnot, this, full );
	if (dlg.DoModal()==IDOK) return 1;
	return 0;
}

void CSpring::DrawGL( CShemeDoc *pDoc, int Time )
{
	ASSERT( pDoc->m_pMovieView );

	glLineWidth( 1 );
	glColor3f( 0.0f, 0.0f, 1.0f );

	double x1, y1, x2, y2;
	CCoordD c;
	if( Time < 0 )
	{
		c = knot1->GetCoord();
		x1 = c.x;
		y1 = c.y;
		c = knot2->GetCoord();
		x2 = c.x;
		y2 = c.y;
	}
	else
	{
		if( (knot1->nXRez < 0)||(knot1->nYRez < 0) )
			c = knot1->GetCoord();
		if( knot1->nXRez >= 0 )
			x1 = pDoc->m_pMovieView->m_Res( knot1->nXRez + 1, Time );
		else
		{
			x1 = c.x;
		}
		if( knot1->nYRez >= 0 )
			y1 = pDoc->m_pMovieView->m_Res( knot1->nYRez + 1, Time );
		else
		{
			y1 = c.y;
		}

		if( (knot2->nXRez < 0)||(knot2->nYRez < 0) )
			c = knot2->GetCoord();
		if( knot2->nXRez >= 0 )
			x2 = pDoc->m_pMovieView->m_Res( knot2->nXRez + 1, Time );
		else
		{
			x2 = c.x;
		}
		if( knot2->nYRez >= 0 )
			y2 = pDoc->m_pMovieView->m_Res( knot2->nYRez + 1, Time );
		else
		{
			y2 = c.y;
		}
	}
	c = CCoordD( CCoordD( x2, y2 ) - CCoordD( x1, y1 ) );
	double L = GetLength();//реальная длина
	double L2 = c.GetNorm();//после деформирования
	double ang = c.GetAng();//угол поворота
	double l = L/10.0;//длина "захвата"

	glPushMatrix();
	glTranslatef( x1, y1, 0.0 );
	glRotatef( ang*180.0/CNSys2DApp::M_PI, 0.0, 0.0, 1.0 );
	if( 2*l >= L2 )
	{
		glBegin(GL_LINES);
			glVertex2f( 0.0, 0.0 );
			glVertex2f( L2, 0.0 );
		glEnd();
	}
	else
	{
		int m = 10;//удвоенное число витков (т.е. число витков = m/2)
		double w = l*1.5;//ширина пружины
		double H = L2 - 2*l;
		double h = H/m;//половина длины витка
		double w2 = w/2;
		glBegin(GL_LINE_STRIP);
			glVertex2f( 0.0, 0.0 );
			glVertex2f( l, 0.0 );
			for( int i = 0; i <= m; i++ )
			{
				glVertex2f( l + i*h,  w2 - w*(i%2) );
			}
			glVertex2f( L2 - l, 0.0 );
			glVertex2f( L2, 0.0 );
		glEnd();
	}
	glPopMatrix();

	knot1->DrawGL( pDoc, Time );
	knot2->DrawGL( pDoc, Time );
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
	double norm = sqrt(vect.x*vect.x+vect.y*vect.y);
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
		const double ang = 70.0*CNSys2DApp::M_PI/180.0, sa = sin(ang), ca = cos(ang);
		
		CPoint point3=CPoint(point1.x+int(vect.x*len1), point1.y+int(vect.y*len1));
		pDC->MoveTo(point1);
		pDC->LineTo(point3);

		CCoordD vect2=CCoordD(vect.x*h,vect.y*h);

		CPoint point5 = CPoint( int(point3.x+vect2.x*ca-vect2.y*sa),
								int(point3.y+vect2.x*sa+vect2.y*ca ) );

		CPoint point6 = CPoint( int(point3.x+vect2.x*ca+vect2.y*sa+vect2.x*2*ca),
								int(point3.y-vect2.x*sa+vect2.y*ca+vect2.y*2*ca) );

		int N=int((norm-2*len1)/(h*4*ca)-0.5);
		double step=(norm-2*len1)/(N+0.5);
		
		CCoordD dpoint=CCoordD(	vect.x*step, vect.y*step );
		
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

bool CSpring::SetSprnX1( double v )
{
	a_X1 = v;
	return true;
}

bool CSpring::SetSprnX3( double v )
{
	a_X3 = v;
	return true;
}

bool CSpring::SetSprnX5( double v )
{
	a_X5 = v;
	return true;
}

bool CSpring::SetSprnXX( const CString &str )
{
	return (m_XX.Reset(str) == SEE_NOERR);
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

double CSpring::GetSprnXX( double x, double v, double a, double t, std::string &ec )
{
	ec = "";
	SetVarState( x, v, a, t );
	double val = m_XX.GetValue();
	if( m_pSheme && m_pSheme->m_bValidateExpr )
	{
		ShemeExprErr err = m_XX.GetRunErrorCode();
		if( err != SEE_NOERR )
		{
			ec = m_XX.GetFullErrorMsg(err);
		}
	}
	return val;
}

/*
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
*/

void CSpring::SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC, std::string *pMsg )
{
	if( type == 1 )
	{
		CMatr loc_matr;
		GetMatrC( loc_matr, pMsg );
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
			return;
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

int CSpring::SetMatrmP( CMatr &mP, CMatr &RezY1, CMatr &RezY2, CMatr *Y3, int i, double Tt, std::string *pMsg )
{
	if( type == 1 )
		return 0;

	CMatr Ugl(4,1), Uloc(4,1), T(4,4), Ploc(4,1), Pgl(4,1);

	if (knot1->nXRez>=0) Ugl[0][0]=RezY1[knot1->nXRez][i];
	if (knot1->nYRez>=0) Ugl[1][0]=RezY1[knot1->nYRez][i];

	if (knot2->nXRez>=0) Ugl[2][0]=RezY1[knot2->nXRez][i];
	if (knot2->nYRez>=0) Ugl[3][0]=RezY1[knot2->nYRez][i];

	GetMatrT(T,4);

	Uloc = T*Ugl;
	
	switch (type)
	{
	case 3:
		{
			double x = Uloc[2][0]-Uloc[0][0];
			x = x*x*x*a_X3;
			Ploc[0][0] = x;
			Ploc[2][0] = -x;
		}
		break;
	case 5:
		{
			double x = Uloc[2][0]-Uloc[0][0], x2 = x*x;
			x = x2*x2*x*a_X5;
			Ploc[0][0] = x;
			Ploc[2][0] = -x;
		}
		break;
	case 0:
		{
			CMatr Uvgl(4,1), Uvloc(4,1);

			if (knot1->nXRez>=0) Uvgl[0][0]=RezY2[knot1->nXRez][i];
			if (knot1->nYRez>=0) Uvgl[1][0]=RezY2[knot1->nYRez][i];
			if (knot2->nXRez>=0) Uvgl[2][0]=RezY2[knot2->nXRez][i];
			if (knot2->nYRez>=0) Uvgl[3][0]=RezY2[knot2->nYRez][i];
			Uvloc = T*Uvgl;

			double a = 0.0;
			if( Y3 != NULL )
			{
				CMatr Agl(4,1), Aloc(4,1);
				if( knot1->nXRez >= 0 )	Agl[0][0] = Y3->GetAt(knot1->nXRez,i);
				if( knot1->nYRez >= 0 ) Agl[1][0] = Y3->GetAt(knot1->nYRez,i);
				if( knot2->nXRez >= 0 ) Agl[2][0] = Y3->GetAt(knot2->nXRez,i);
				if( knot2->nYRez >= 0 ) Agl[3][0] = Y3->GetAt(knot2->nYRez,i);
				Aloc = T*Agl;
				a = Aloc[2][0] - Aloc[0][0];
			}

			SetVarState( Uloc[2][0]-Uloc[0][0], Uvloc[2][0]-Uvloc[0][0], a, Tt );
			double res = m_XX.GetValue();
			if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
			{
				ShemeExprErr err = m_XX.GetRunErrorCode();
				if( err != SEE_NOERR )
				{
					(*pMsg) = m_XX.GetFullErrorMsg(err);
					return -1;
				}
			}

			Ploc[0][0] = res;
			Ploc[2][0] = -res;
		}
		break;
	}
	Pgl = !T*Ploc;

	if (knot1->nXRez>=0) mP[knot1->nXRez][0]+=Pgl[0][0];
	if (knot1->nYRez>=0) mP[knot1->nYRez][0]+=Pgl[1][0];
	if (knot2->nXRez>=0) mP[knot2->nXRez][0]+=Pgl[2][0];
	if (knot2->nYRez>=0) mP[knot2->nYRez][0]+=Pgl[3][0];

	return 0;
}

void CSpring::Serialize( CArchive &ar, int _sv )
{
	CElem::Serialize( ar, _sv );

	ShemeVersion sv = static_cast<ShemeVersion>(_sv);
	if (ar.IsStoring())
	{	// storing code
		if( sv <= VER_EQ30 )
		{
			CString str;
			str.Format("%.16g", a_X1 );
			ar << str;
			str.Format("%.16g", a_X3 );
			ar << str;
			str.Format("%.16g", a_X5 );
			ar << str;
		}
		else
		{
			ar << a_X1 << a_X3 << a_X5;
		}
		m_XX.Serialize(ar);
		ar << type;
	}
	else
	{	// loading code
		if( sv <= VER_EQ30 )
		{
			CString X3, X5, X1;
			ar >> X1 >> X3 >> X5;
			a_X1 = atof( static_cast<LPCTSTR>(X1) );
			a_X3 = atof( static_cast<LPCTSTR>(X3) );
			a_X5 = atof( static_cast<LPCTSTR>(X5) );
		}
		else
		{
			ar >> a_X1 >> a_X3 >> a_X5;
		}
		m_XX.Serialize(ar);
		ar >> type;
	}
}

bool CSpring::SetCommonProperties( const CElem* elem )
{
	//CSpring *pSpr = dynamic_cast<CSpring*>(elem);
	const CSpring *pSpr = static_cast<const CSpring*>(elem);
	if( !pSpr )	return false;

	a_X1 = pSpr->a_X1;
	a_X3 = pSpr->a_X3;
	a_X5 = pSpr->a_X5;
//	a_XX = pSpr->a_XX;
	m_XX.InitBy( pSpr->m_XX );
//	str_X1 = pSpr->str_X1;
//	str_X3 = pSpr->str_X3;
//	str_X5 = pSpr->str_X5;
//	str_XX = pSpr->str_XX;
	type = pSpr->type;

	return true;
}

void CSpring::GetMatrM( CMatr &matr, std::string *pMsg )
{
	matr.ReSize( 4, 4 );
}

void CSpring::GetMatrD( CMatr &matr, std::string *pMsg )
{
	matr.ReSize( 4, 4 );
}

void CSpring::GetMatrC( CMatr &matr, std::string *pMsg )
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

void CSpring::SetVarState( double x, double v, double a, double t )
{
	if( m_pSheme )
	{
		m_pSheme->m_VarsTable.SetVarValue("x",x);
		m_pSheme->m_VarsTable.SetVarValue("w",x);
		m_pSheme->m_VarsTable.SetVarValue("v",v);
		m_pSheme->m_VarsTable.SetVarValue("t",t);
		m_pSheme->m_VarsTable.SetVarValue("a",a);
		m_pSheme->m_VarsTable.SetVarValue("cx",0.0);
		m_pSheme->m_VarsTable.SetVarValue("cy",0.0);
		CElem::SetVarState();
	}
}

CString CSpring::GetName() const
{
	CString name, pars;
	name.Format("Пружина №%d Коэф.жесткости = ", GetNumber() );
	switch(type)
	{
	case 1:
		pars.Format("%.16g*x", a_X1 );
		break;
	case 3: 
		pars.Format("%.16g*x^3", a_X3 );
		break;
	case 5: 
		pars.Format("%.16g*x^5", a_X5 );
		break;
	case 0:
		pars.Format("%s", m_XX.GetExpr().c_str() );
		break;
	default:
		ASSERT(FALSE);
	}
	return name + pars;
}