// Demf.cpp: implementation of the CDemf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "Demf.h"

#include "ShemeDoc.h"
#include "Sheme.h"
#include "MovieView.h"
#include "demfdlg.h"

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

CDemf::CDemf( CKnot *kn1, CKnot *kn2, CSheme *p ):CElem(kn1,kn2,p)
{
	SetDemfX1(1);	
	SetDemfX3(0);	
	SetDemfX5(0);	
	SetDemfXS(0);	
//	SetDemfXX("0");	
	m_XX.Reset( string("0"), (p)?(&p->m_VarsTable):(NULL) );
	type = 1;
	TypeElem = IDC_DEMF;
}

CDemf::~CDemf()
{
}

CDemf::CDemf( const CDemf &elem ):CElem(elem)
{
	InitBy(elem);
}

CDemf& CDemf::operator=( const CDemf &elem )
{
	if( this != (&elem) )
		InitBy(elem);
	return *this;
}

void CDemf::InitBy( const CDemf &elem )
{
	SetCommonProperties( &elem );
}
///////////////////////////////////////////////////////////////////////
void CDemf::DrawGL( CShemeDoc *pDoc, int Time )
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
	double L = GetLength();//реальная длина элемента
	double L2 = c.GetNorm();//длина после деформирования
	double ang = c.GetAng();//угол поворота
	double h = L/10.0;

	glPushMatrix();
	glTranslated( x1, y1, 0.0 );
	glRotated( ang*180.0/CNSys2DApp::M_PI, 0.0, 0.0, 1.0 );

	if( 2*h >= L2 )
	{
		glBegin(GL_LINES);
			glVertex2d( 0.0, 0.0 );
			glVertex2d( L2, 0.0 );
		glEnd();
	}
	else
	{
		double w = h;
		double tmp = L2/2;
		double tmp2 = tmp - h, tmp3 = tmp + h;
		//"захваты":
		glBegin(GL_LINES);
			glVertex2d( 0.0, 0.0 );
			glVertex2d( tmp2, 0.0 );
			glVertex2d( L2, 0.0 );
			glVertex2d( tmp, 0.0 );
		glEnd();
		tmp = w/2.0;
		glBegin(GL_LINE_STRIP);
			glVertex2d( tmp3, -tmp );
			glVertex2d( tmp2, -tmp );
			glVertex2d( tmp2, tmp );
			glVertex2d( tmp3, tmp );
		glEnd();
	}
	glPopMatrix();

	knot1->DrawGL( pDoc, Time );
	knot2->DrawGL( pDoc, Time );
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
		
		double tmp = sqrt(len2)/10.0;
		int tmpX = vect.x/tmp, tmpY = vect.y/tmp;
		CPoint point6=CPoint(point4.x+tmpX,
							 point4.y+tmpY );
		CPoint point7=CPoint(point5.x+tmpX,
							 point5.y+tmpY );

		pDC->MoveTo(point4.x,point4.y);
		pDC->LineTo(point6.x,point6.y);

		pDC->MoveTo(point5.x,point5.y);
		pDC->LineTo(point7.x,point7.y);
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

int CDemf::GoDlg(CListKnot * pListKnot, bool full )
{
	CDemfDlg dlg( pListKnot, this, full );
	if (dlg.DoModal()==IDOK) return 1;
	return 0;
}

bool CDemf::SetDemfX1( double val )
{
	a_X1 = val;
	return true;
}

bool CDemf::SetDemfX3( double val )
{
	a_X3 = val;
	return true;
}

bool CDemf::SetDemfX5( double val )
{
	a_X5 = val;
	return true;
}

bool CDemf::SetDemfXS( double val )
{
	a_XS = val;
	return true;
}

bool CDemf::SetDemfXX( const CString &str )
{
	return (m_XX.Reset(str) == SEE_NOERR);
}

/*
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
*/

double CDemf::GetDemfXX( double x, double v, double a, double t, std::string &ec )
{
//в ec заносится сообщение об ошибке
	SetVarState( x, v, a, t );
	ec = "";
	double val = m_XX.GetValue();
	if( m_pSheme && m_pSheme->m_bValidateExpr )
	{
		ShemeExprErr er = m_XX.GetRunErrorCode();
		if( er != SEE_NOERR )
			ec = m_XX.GetFullErrorMsg(er);
	}
	return val;
}

double CDemf::GetDemfX( int i )
{
	switch (i)
	{
	case 1: return a_X1;
	case 3: return a_X3;
	case 5: return a_X5;
	case 6: return a_XS;
	default:
		ASSERT(FALSE);
		break;
	};
	return -1.0;
}

void CDemf::SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC, std::string *pMsg )
{
	if (type==1)
	{
		CMatr loc_matr;
		GetMatrD( loc_matr, pMsg );
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
			return;
		/*
		double a=GetDemfX(1);
		CMatr T( 4, 4 );
		GetMatrT(T,4);

		loc_matr[0][0]=a;
		loc_matr[2][2]=a;
		loc_matr[2][0]=-a;
		loc_matr[0][2]=-a;
		
		loc_matr=!T*loc_matr*T;
		*/
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

int CDemf::SetMatrmP( CMatr &mP, CMatr &RezY1, CMatr &RezY2, CMatr *Y3, int i, double Tt, std::string *pMsg )
{
	if( type == 1 )
		return 0;

	CMatr Vgl(4,1), Vloc(4,1), T(4,4), Ploc(4,1), Pgl(4,1);

	if (knot1->nXRez>=0) Vgl[0][0]=RezY2[knot1->nXRez][i];
	if (knot1->nYRez>=0) Vgl[1][0]=RezY2[knot1->nYRez][i];

	if (knot2->nXRez>=0) Vgl[2][0]=RezY2[knot2->nXRez][i];
	if (knot2->nYRez>=0) Vgl[3][0]=RezY2[knot2->nYRez][i];

	GetMatrT(T,4);

	Vloc=T*Vgl;
	
	double VV = Vloc[2][0] - Vloc[0][0];
	switch (type)
	{
	case 3:
		{
			double VV2 = VV*VV;
			VV = VV2*VV*a_X3;
			Ploc[0][0] = VV;
			Ploc[2][0] = -VV;
		}
		break;
	case 5:
		{
			double VV2 = VV*VV;
			VV2 = VV2*VV2;//VV^4
			VV = VV*VV2*a_X5;
			Ploc[0][0] = VV;
			Ploc[2][0] = -VV;
		}
		break;
	case 6:
		{
			if( VV > 0.0 )
			{
				Ploc[0][0] = a_XS;
				Ploc[2][0] = -a_XS;
				break;
			}
			if( VV < 0.0 )
			{
				Ploc[0][0] = -a_XS;
				Ploc[2][0] = +a_XS;
			}
		}
		break;
	case 0:
		{
			CMatr Ugl(4,1), Uloc(4,1);

			if (knot1->nXRez>=0) Ugl[0][0]=RezY1[knot1->nXRez][i];
			if (knot1->nYRez>=0) Ugl[1][0]=RezY1[knot1->nYRez][i];
			if (knot2->nXRez>=0) Ugl[2][0]=RezY1[knot2->nXRez][i];
			if (knot2->nYRez>=0) Ugl[3][0]=RezY1[knot2->nYRez][i];
			Uloc = T*Ugl;

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

			SetVarState( Uloc[2][0]-Uloc[0][0], VV, a, Tt );
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

void CDemf::Serialize( CArchive &ar, int _sv )
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
			str.Format("%.16g", a_XS );
			ar << str;
		}
		else
		{
			ar << a_X1 << a_X3 << a_X5 << a_XS;
		}
		m_XX.Serialize(ar);
		ar << type;
	}
	else
	{	// loading code
		if( sv <= VER_EQ30 )
		{
			CString X3, X5, X1, XS;
			ar >> X1 >> X3 >> X5 >> XS;
			a_X1 = atof( static_cast<LPCTSTR>(X1) );
			a_X3 = atof( static_cast<LPCTSTR>(X3) );
			a_X5 = atof( static_cast<LPCTSTR>(X5) );
			a_XS = atof( static_cast<LPCTSTR>(XS) );
		}
		else
		{
			ar >> a_X1 >> a_X3 >> a_X5 >> a_XS;
		}
		m_XX.Serialize(ar);
		ar >> type;
	}
}

bool CDemf::SetCommonProperties( const CElem* elem )
{
	//CDemf *pDemf = dynamic_cast<CDemf*>(elem);
	const CDemf *pDemf = static_cast<const CDemf*>(elem);
	if( !pDemf )	return false;

	a_X1 = pDemf->a_X1;
	a_X3 = pDemf->a_X3;
	a_X5 = pDemf->a_X5;
	a_XS = pDemf->a_XS;
	m_XX.InitBy( pDemf->m_XX );
	/*
	str_X1 = pDemf->str_X1;
	str_X3 = pDemf->str_X3;
	str_X5 = pDemf->str_X5;
	str_XS = pDemf->str_XX;
	str_XX = pDemf->str_XX;
	*/
	type = pDemf->type;

	return true;
}

void CDemf::GetMatrM( CMatr &m, std::string *pMsg )
{
	m.ReSize( 4, 4 );
}

void CDemf::GetMatrD( CMatr &m, std::string *pMsg )
{
	if( type == 1 )
	{
		m.ReSize( 4, 4 );
		CMatr T( 4, 4 );
		double a = GetDemfX(1);
		GetMatrT( T, 4 );

		m[0][0] = a;
		m[2][2] = a;
		m[2][0] = -a;
		m[0][2] = -a;
		
		m = !T*m*T;
	}
	else
		m.ReSize( 4, 4 );
}

void CDemf::GetMatrC( CMatr &m, std::string *pMsg )
{
	m.ReSize( 4, 4 );
}

void CDemf::SetVarState( double x, double v, double a, double t )
{
	if( m_pSheme )
	{
		m_pSheme->m_VarsTable.SetVarValue("x",x);
		m_pSheme->m_VarsTable.SetVarValue("v",v);
		m_pSheme->m_VarsTable.SetVarValue("t",t);
		m_pSheme->m_VarsTable.SetVarValue("a",a);
		m_pSheme->m_VarsTable.SetVarValue("w",a);
		m_pSheme->m_VarsTable.SetVarValue("cx",0.0);
		m_pSheme->m_VarsTable.SetVarValue("cy",0.0);
		CElem::SetVarState();
	}
}

CString CDemf::GetName() const
{
	CString name, pars;
	name.Format("Демпфер №%d Коэф.демпфирования = ", GetNumber() );
	switch(type)
	{
	case 1:
		pars.Format("%.16g*x'", a_X1 );
		break;
	case 3: 
		pars.Format("%.16g*(x')^3", a_X3 );
		break;
	case 5: 
		pars.Format("%.16g*(x')^5", a_X5 );
		break;
	case 6:
		pars.Format("%.16g*sign(x')", a_XS );
		break;
	case 0:
		pars.Format("%s", m_XX.GetExpr().c_str() );
		break;
	default:
		ASSERT(FALSE);
	}
	return name + pars;
}