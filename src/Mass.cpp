// Mass.cpp: implementation of the CMass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "Mass.h"

#include "Massdlg.h"
#include "ShemeDoc.h"
#include "Sheme.h"
#include "MovieView.h"

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

CMass::CMass( CKnot *kn1, CSheme *p ):CElem(kn1,kn1,p)
{
	//SetMassM(_T("1"));
	//SetMassJp(_T("0"));
	TypeElem = IDC_MASS;

	CShemeVarsTable *pVT = (m_pSheme)?(&m_pSheme->m_VarsTable):(NULL);

	m_M.Reset( string("1"), pVT );
	m_Jp.Reset( string("0"), pVT );
}

CMass::~CMass()
{

}

CMass::CMass( const CMass &elem ):CElem(elem)
{
	InitBy(elem);
}

CMass& CMass::operator=( const CMass &elem )
{
	if( this != (&elem) )
		InitBy(elem);
	return *this;
}

void CMass::InitBy( const CMass &elem )
{
	SetCommonProperties( &elem );
}

void CMass::DrawGL( CShemeDoc *pDoc, int Time )
{
	ASSERT( pDoc->m_pMovieView );

	glLineWidth( 2 );
	glColor3f( 0.0f, 0.0f, 1.0f );

	GLdouble rad = pDoc->m_pMovieView->m_Width/45;
	double x, y, fi = 0.0;
	CCoordD c;
	if( Time < 0 )
	{
		c = knot1->GetCoord();
		x = c.x;
		y = c.y;
	}
	else
	{
		if( (knot1->nXRez < 0)||(knot1->nYRez < 0) )
			c = knot1->GetCoord();
		if( knot1->nXRez >= 0 )
			x = pDoc->m_pMovieView->m_Res( knot1->nXRez + 1, Time );
		else
		{
			x = c.x;
		}
		if( knot1->nYRez >= 0 )
			y = pDoc->m_pMovieView->m_Res( knot1->nYRez + 1, Time );
		else
		{
			y = c.y;
		}
		if( knot1->nARez[0] >= 0 )
		{
			fi = pDoc->m_pMovieView->m_Res( knot1->nARez[0] + 1, Time );
			fi *= 180.0/CNSys2DApp::M_PI;
		}
	}
	glPushMatrix();
	glTranslatef( x, y, 0.0f );
	glRotatef( fi, 0.0, 0.0, 1.0 );
	glBegin(GL_QUADS);
		glVertex2f( -rad, rad );
		glVertex2f( rad, rad );
		glVertex2f( rad, -rad );
		glVertex2f( -rad, -rad );
	glEnd();
	glPopMatrix();

	knot1->DrawGL( pDoc, Time );
}

void CMass::Draw(CDC * pDC, CParamView * pParamView)
{
	CPoint point=ShemeToScreen(knot1->GetCoord(pParamView->MultMove),pParamView);

	COLORREF col;
	col=(SelectMode?RGB(250,0,0):RGB(0,0,250));
	if (pParamView->Gray)
		col=RGB(200,200,200);

	CPen pen(PS_SOLID|PS_GEOMETRIC,1,col);
	CPen *pOld=(CPen*)pDC->SelectObject(&pen);
	CBrush brush(col),*pOldbrush;
	pOldbrush=(CBrush*)pDC->SelectObject(&brush);

	const int rad=6;
	double tmp = fabs(knot1->MoveA[0]);

	if( (fabs(pParamView->MultAngl) <= pParamView->m_ZeroRot)||
		(tmp <= pParamView->m_ZeroRot) )
	{
		CRect rect(point.x-rad, point.y-rad, point.x+rad, point.y+rad);
		pDC->FillRect(&rect, &brush);
		//pDC->Ellipse(point.x-rad,point.y-rad,point.x+rad,point.y+rad);
	}
	else
	{
		if( tmp > pParamView->m_ZeroRot )
		{
			int rad2 = rad/2, rad3 = int(double(rad)*1.4);
			CPoint polygon[4] = { CPoint(point.x-rad2,point.y+rad3), 
									CPoint(point.x+rad3,point.y+rad2),
									CPoint(point.x+rad2,point.y-rad3),
									CPoint(point.x-rad3,point.y-rad2) };
			CRgn rgn;
			rgn.CreatePolygonRgn( polygon, 4, WINDING);
			pDC->FillRgn( &rgn, &brush );
		}			
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

		pDC->TextOut( point.x+2, point.y+2, str );

		pDC->SetBkMode(oldBkMode);
		pDC->SetTextColor(oldClr);

		pDC->SelectObject(pOldFont);
	}

	knot1->Draw(pDC,pParamView);
	
	pDC->SelectObject(pOldbrush);
	pDC->SelectObject(pOld);
}

int CMass::GoDlg(CListKnot * pListKnot, bool full )
{
	CMassDlg dlg( pListKnot, this, full );
	if (dlg.DoModal()==IDOK) return 1;
	return 0;
}

bool CMass::SetMassM( const CString &str )
{
	return (m_M.Reset(str) == SEE_NOERR)?(true):(false);
}

bool CMass::SetMassJp( const CString &str )
{
	return (m_Jp.Reset(str) == SEE_NOERR)?(true):(false);
}

bool CMass::SetMassM( double val )
{
	return (m_M.Reset(val) == SEE_NOERR)?(true):(false);
}

bool CMass::SetMassJp( double val )
{
	return (m_Jp.Reset(val) == SEE_NOERR)?(true):(false);
}

double CMass::GetM( bool flg )
{
	if( flg )
		SetVarState();
	return m_M.GetValue();
}

double CMass::GetJp( bool flg )
{
	if( flg )
		SetVarState();
	return m_Jp.GetValue();
}

/*
CString CMass::GetStrM()
{
	return str_M;
}

CString CMass::GetStrJp()
{
	return str_Jp;
}
*/

void CMass::SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC, std::string *pMsg )
{
	CMatr loc_matr;
	GetMatrM( loc_matr, pMsg );
	if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
		return;

	int N[3];
	N[0] = knot1->nXRez;
	N[1] = knot1->nYRez;
	N[2] = knot1->nARez[0];

	int maxn=3;
//	if (knot1->ConnectType!=0) maxn=2;

	for (int i=0;i<maxn;i++)
		for(int j=0;j<maxn;j++)
			if ((N[i]>=0)&&(N[j]>=0)) mM[N[i]][N[j]]+=loc_matr[i][j];

}

int CMass::SetMatrmP( CMatr &mP, CMatr &RezY1, CMatr &RezY2, CMatr *Y3, int i, double t, std::string *pMsg )
{
	return 0;
}

void CMass::Serialize( CArchive &ar, int sv )
{
	CElem::Serialize( ar, sv );

	if (ar.IsStoring())
	{	// storing code
		m_M.Serialize(ar);
		m_Jp.Serialize(ar);
	}
	else
	{	// loading code
		m_M.Serialize(ar);
		m_Jp.Serialize(ar);
	}
}

bool CMass::SetCommonProperties( const CElem* elem )
{
	//CMass *pMass = dynamic_cast<CMass*>(elem);
	const CMass *pMass = static_cast<const CMass*>(elem);
	if( !pMass )	return false;

	/*
	str_M = pMass->str_M;
	str_Jp = pMass->str_Jp;
	M = pMass->M;
	Jp = pMass->Jp;
	*/
	m_M.InitBy( pMass->m_M );
	m_Jp.InitBy( pMass->m_Jp );

	return true;
}

void CMass::GetMatrM( CMatr &matr, std::string *pMsg )
{
	matr.ReSize( 3, 3 );

	double m = GetM();
	double Jp = GetJp( false );
	if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
	{
		ShemeExprErr err = m_Jp.GetRunErrorCode();
		if( err != SEE_NOERR )
		{
			(*pMsg) = m_Jp.GetFullErrorMsg(err);
			return;
		}
		err = m_M.GetRunErrorCode();
		if( err != SEE_NOERR )
		{
			(*pMsg) = m_M.GetFullErrorMsg(err);
			return;
		}
	}
	
	matr[0][0] = m;
	matr[1][1] = m;
	matr[2][2] = Jp;
}

void CMass::GetMatrD( CMatr &matr, std::string *pMsg )
{
	matr.ReSize( 3, 3 );
}

void CMass::GetMatrC( CMatr &matr, std::string *pMsg )
{
	matr.ReSize( 3, 3 );
}

void CMass::SetVarState()
{
	if( m_pSheme )
	{
		m_pSheme->m_VarsTable.SetVarValue("x",0.0);
		m_pSheme->m_VarsTable.SetVarValue("w",0.0);
		m_pSheme->m_VarsTable.SetVarValue("v",0.0);
		m_pSheme->m_VarsTable.SetVarValue("t",0.0);
		m_pSheme->m_VarsTable.SetVarValue("a",0.0);
		m_pSheme->m_VarsTable.SetVarValue("cx",0.0);
		m_pSheme->m_VarsTable.SetVarValue("cy",0.0);
		CElem::SetVarState();
	}
}

CString CMass::GetName() const
{
	CString name;
	name.Format("Масса №%d (m=%s,Jp=%s)", GetNumber(), m_M.GetExpr().c_str(), m_Jp.GetExpr().c_str() );
	return name;
}
