// HardRod.cpp: implementation of the CHardRod class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "HardRod.h"
#include "HardRodDlg.h"
#include "matr.h"

#include "ShemeDoc.h"
#include "Sheme.h"
#include "MovieView.h"

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHardRod::CHardRod( CKnot *kn1, CKnot *kn2, CSheme *p ):CElem(kn1,kn2,p)
{
//	SetE(CString("1"));  
//	SetF(CString("1"));  
//	SetJ(CString("1"));
//	SetM(CString("1"));
	TypeElem = IDC_HARDROD;
	FreeA1 = FreeA2 = 0;

	m_HardMethod = 0;
	m_NofKnots = 2;
	m_NofHardRodsInOneKnot[0] = m_NofHardRodsInOneKnot[1] = 1;

	CShemeVarsTable *pVT = (m_pSheme)?(&m_pSheme->m_VarsTable):(NULL);
	string Val("1");

	m_E.Reset( Val, pVT );
	m_F.Reset( Val, pVT );
	m_J.Reset( Val, pVT );
	m_M.Reset( Val, pVT );
}

CHardRod::~CHardRod()
{

}

CHardRod::CHardRod( const CHardRod &elem ):CElem(elem)
{
	InitBy(elem);
}

CHardRod& CHardRod::operator=( const CHardRod &elem )
{
	if( this != (&elem) )
		InitBy(elem);
	return *this;
}

void CHardRod::InitBy( const CHardRod &elem )
{
	SetCommonProperties( &elem );
	FreeA1 = elem.FreeA1;
	FreeA2 = elem.FreeA2;
	m_HardMethod = elem.m_HardMethod;
	m_NofKnots = elem.m_NofKnots;
	m_NofHardRodsInOneKnot[0] = elem.m_NofHardRodsInOneKnot[0];
	m_NofHardRodsInOneKnot[1] = elem.m_NofHardRodsInOneKnot[1];
}

///////////////////////////////////////////////////////////////
//	realisations
///////////////////////////////////////////////////////////////
void CHardRod::DrawGL( CShemeDoc *pDoc, int Time )
{
	ASSERT( pDoc->m_pMovieView );

	glLineWidth( 4 );
	glColor3f( 0.0f, 0.0f, GLfloat(150.0/255.0) );

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
	glBegin(GL_LINES);
		glVertex2f( x1, y1 );
		glVertex2f( x2, y2 );
	glEnd();

	knot1->DrawGL( pDoc, Time );
	knot2->DrawGL( pDoc, Time );
}

void CHardRod::Draw(CDC * pDC, CParamView *pParamView)
{
	POINT point1=ShemeToScreen(knot1->GetCoord(pParamView->MultMove),pParamView);
	POINT point2=ShemeToScreen(knot2->GetCoord(pParamView->MultMove),pParamView);

	COLORREF col;
	col = (SelectMode?RGB(250,0,0):RGB(0,0,150));
	if( pParamView->Gray )	col = RGB(200,200,200);

	CPen pen(PS_SOLID|PS_INSIDEFRAME/*|PS_GEOMETRIC*/,4,col);
	CPen *pOld = (CPen*)pDC->SelectObject(&pen);

	if( pParamView->MultMove == 0 )
	{
		pDC->MoveTo( point1.x, point1.y );
		pDC->LineTo( point2.x, point2.y );
	}
	else
	{	
		//Определение локальных перемещений
		CMatr Ugl(6,1), Uloc(6,1), T(6,6);
		CMatr mM(6,6), A(6,1);

		double L = GetLength();

		Ugl[0][0]=knot1->MoveX*pParamView->MultMove;
		Ugl[1][0]=knot1->MoveY*pParamView->MultMove;
		Ugl[2][0]=knot1->MoveA[FreeA1]*pParamView->MultAngl;
		Ugl[3][0]=knot2->MoveX*pParamView->MultMove;
		Ugl[4][0]=knot2->MoveY*pParamView->MultMove;
		Ugl[5][0]=knot2->MoveA[FreeA2]*pParamView->MultAngl;

		GetMatrT(T, 6);

		Uloc = T * Ugl;//T*Ugl;
		CMatr T1(2,2), T_1(2,2);
		GetMatrT(T1,2);
		T_1 = !T1;//!T1;

//		double tmp1 = point2.x-point1.x, tmp2 = point2.y-point1.y;
//		double tmp3 = tmp1*tmp1, tmp4 = tmp2*tmp2;
//		double tStep=1.0/(sqrt(tmp3+tmp4)+1);
		CCoordD c1=knot1->GetCoord();
		CCoordD c2=knot2->GetCoord();

		CMatr Uu(2,1), U(2,1);

		Uu[0][0] = Uloc[0][0];
		Uu[1][0] = Uloc[1][0];
		U = T_1*Uu;
		CCoordD cc1( U[0][0] + c1.x, U[1][0] + c1.y );
		POINT p = ShemeToScreen(cc1, pParamView);
		pDC->MoveTo( p );

		Uu[0][0] = Uloc[3][0];
		Uu[1][0] = Uloc[4][0];
		U = T_1*Uu;
		CCoordD cc2( U[0][0] + c2.x, U[1][0] + c2.y );
		p = ShemeToScreen(cc2, pParamView);
		pDC->LineTo( p );
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

void CHardRod::SetMatrMDC( CMatr & mM, CMatr & mD, CMatr & mC, std::string *pMsg )
{
	//Номера степеней свободы
	int N[6];
	N[0] = knot1->nXRez;
	N[1] = knot1->nYRez;
	N[2] = knot1->nARez[FreeA1];
	N[3] = knot2->nXRez;
	N[4] = knot2->nYRez;
	N[5] = knot2->nARez[FreeA2];

	if( m_HardMethod == 2 )
	{
		CMatr locC;
		GetMatrC( locC, pMsg );
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
			return;
		for( int i = 0; i < 6; i++ )
			for( int j = 0; j < 6; j++ )
				if( (N[i] >= 0)&&(N[j] >= 0) )
				{
					mC[N[i]][N[j]] += locC[i][j];
				}
	}

	CMatr locM;
	GetMatrM( locM, pMsg );
	if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
		return;
	for( int i = 0; i < 6; i++ )
		for( int j = 0; j < 6; j++ )
			if( (N[i] >= 0)&&(N[j] >= 0) )
			{
				mM[N[i]][N[j]] += locM[i][j];
			}
}

int CHardRod::SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, CMatr *Y3, int i, double Tt, std::string *pMsg )
{
	return 0;
}

void CHardRod::Serialize( CArchive &ar, int sv )
{
	CElem::Serialize( ar, sv );

	if (ar.IsStoring())
	{	// storing code
		m_F.Serialize(ar);
		m_J.Serialize(ar);
		m_E.Serialize(ar);
		m_M.Serialize(ar);
	}
	else
	{	// loading code
		m_F.Serialize(ar);
		m_J.Serialize(ar);
		m_E.Serialize(ar);
		m_M.Serialize(ar);
	}
}

int CHardRod::GoDlg( CListKnot *pListKnot, bool full )
{
	CHardRodDlg dlg( pListKnot, this, full );
	if( dlg.DoModal() == IDOK )	return 1;
	return 0;
}

bool CHardRod::SetCommonProperties( const CElem* elem )
{
	//CHardRod *pHR = dynamic_cast<CHardRod*>(elem);
	const CHardRod *pHR = static_cast<const CHardRod*>(elem);
	if( !pHR )	return false;

	/*
	str_E = pHR->str_E;
	str_J = pHR->str_J;
	str_m = pHR->str_m;
	str_F = pHR->str_F;
	E = pHR->E;
	J = pHR->J;
	m = pHR->m;
	F = pHR->F;
	*/
	m_E.InitBy( pHR->m_E );
	m_J.InitBy( pHR->m_J );
	m_F.InitBy( pHR->m_F );
	m_M.InitBy( pHR->m_M );

	return true;
}

void CHardRod::GetMatrM( CMatr &matr, std::string *pMsg )
{
	matr.ReSize( 6, 6 );

	double J = GetJ();
	double m = GetM( false );//масса стержня
	if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
	{
		ShemeExprErr err = m_J.GetRunErrorCode();
		if( err != SEE_NOERR )
		{
			(*pMsg) = m_J.GetFullErrorMsg(err);
			return;
		}
		err = m_M.GetRunErrorCode();
		if( err != SEE_NOERR )
		{
			(*pMsg) = m_M.GetFullErrorMsg(err);
			return;
		}
	}

	if( m_HardMethod != 2 )
	{
		if( m_HardMethod == 0 )
		{
			//использование жёст.К.Э. без разноса масс
			//матрица масс
			matr[0][0]= matr[1][1] = matr[3][3] = matr[4][4] = m/2.0;
			matr[2][2] = matr[5][5] = J/2.0;
		}
		else
		{
			//m_HardMethod == 1
			//m_NofKnots - кол-во узлов, связанных подряд жёсткими эл-ми
			//m_NofHardRodsInOneKnot[0] - кол-во стержней, сходящихся в первом узле
			//m_NofHardRodsInOneKnot[1] - во втором узле
			double val1 = (double)(m_NofKnots*m_NofHardRodsInOneKnot[0]);
			double val2 = (double)(m_NofKnots*m_NofHardRodsInOneKnot[1]);
			matr[0][0]= matr[1][1] = m/val1;
			matr[3][3] = matr[4][4] = m/val2;
			matr[2][2] = J/val1;
			matr[5][5] = J/val2;
		}

	}
	else
	{
		//m_HardMethod == 2
		//использование обычного К.Э., но с удалением степеней свободы
		CMatr T(6,6);
		GetMatrT( T, 6 );

		double L = GetLength();
		double F = GetF( false );
		double E = GetE( false );
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
		{
			ShemeExprErr err = m_E.GetRunErrorCode();
			if( err != SEE_NOERR )
			{
				(*pMsg) = m_E.GetFullErrorMsg(err);
				return;
			}
			err = m_F.GetRunErrorCode();
			if( err != SEE_NOERR )
			{
				(*pMsg) = m_F.GetFullErrorMsg(err);
				return;
			}
		}

		m /= L;//погонная масса
		double mL = m*L, mL2 = mL*L, mL3 = mL2*L, EF = E*F;
		//матрица масс
		matr[0][0]= mL/3.0;
		matr[3][3]= mL/3.0;
		matr[3][0]= mL/6.0;
		//матрица жёсткости
		matr[0][0]= EF/L;
		matr[3][3]= EF/L;
		matr[3][0]=-EF/L;

		matr[1][1]= mL*13.0/35.0;
		matr[2][1]= mL2*11.0/210.0;
		matr[4][1]= mL*9.0/70.0;
		matr[5][1]=-mL2*13.0/420.0;

		matr[2][2]= mL3/105.0;
		matr[4][2]= mL2*13.0/420.0;
		matr[5][2]=-mL3/140.0;

		matr[4][4]= mL*13.0/35.0;
		matr[5][4]=-mL2*11.0/210.0;
		matr[5][5]= mL3/105.0;
	
		matr.CopyDownToUp();
		matr = !T*matr*T;
	}
////////////////////////////////////////////
#ifdef _DEBUG
	TRACE0("\n\n!T*locM*T:\n");
	for( int r = 0; r < matr.SizeY; r++ )
	{
		for( int c = 0; c < matr.SizeX; c++ )
		{
			TRACE1("%.6e ", matr[r][c] );
		}
		TRACE0("\n");
	}
#endif
////////////////////////////////////////////
}

void CHardRod::GetMatrD( CMatr &m, std::string *pMsg )
{
	m.ReSize( 6, 6 );
}

void CHardRod::GetMatrC( CMatr &matr, std::string *pMsg )
{
	matr.ReSize( 6, 6 );
	if( m_HardMethod == 2 )
	{
		//использование обычного К.Э., но с удалением степеней свободы
		CMatr T( 6, 6 );
		GetMatrT( T, 6 );

		double F = GetF();
		double E = GetE( false );
		double J = GetJ( false );
		double m = GetM( false );//масса стержня
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
		{
			ShemeExprErr err = m_E.GetRunErrorCode();
			if( err != SEE_NOERR )
			{
				(*pMsg) = m_E.GetFullErrorMsg(err);
				return;
			}
			err = m_F.GetRunErrorCode();
			if( err != SEE_NOERR )
			{
				(*pMsg) = m_F.GetFullErrorMsg(err);
				return;
			}
			err = m_J.GetRunErrorCode();
			if( err != SEE_NOERR )
			{
				(*pMsg) = m_J.GetFullErrorMsg(err);
				return;
			}
			err = m_M.GetRunErrorCode();
			if( err != SEE_NOERR )
			{
				(*pMsg) = m_M.GetFullErrorMsg(err);
				return;
			}
		}
		double L = GetLength();

		m /= L;//погонная масса
		//матрица жёсткости
		matr[0][0]= E*F/L;
		matr[3][3]= E*F/L;
		matr[3][0]=-E*F/L;

		matr[1][1]= 12*E*J/(L*L*L);
		matr[2][1]= 6*E*J/(L*L);
		matr[4][1]=-12*E*J/(L*L*L);
		matr[5][1]= 6*E*J/(L*L);

		matr[2][2]= 4*E*J/L;
		matr[4][2]=-6*E*J/(L*L);
		matr[5][2]= 2*E*J/L;
		
		matr[4][4]= 12*E*J/(L*L*L);
		matr[5][4]=-6*E*J/(L*L);
		matr[5][5]= 4*E*J/L;

		matr.CopyDownToUp();
		matr = !T*matr*T;
	}
}

void CHardRod::SetVarState()
{
	if( m_pSheme )
	{
		m_pSheme->m_VarsTable.SetVarValue("x",0.0);
		m_pSheme->m_VarsTable.SetVarValue("v",0.0);
		m_pSheme->m_VarsTable.SetVarValue("t",0.0);
		m_pSheme->m_VarsTable.SetVarValue("a",0.0);
		m_pSheme->m_VarsTable.SetVarValue("cx",0.0);
		m_pSheme->m_VarsTable.SetVarValue("cy",0.0);
		m_pSheme->m_VarsTable.SetVarValue("w",0.0);
		CElem::SetVarState();
	}
}

double CHardRod::GetM( bool flg )
{
	if( flg )
		SetVarState();
	return m_M.GetValue();
}

double CHardRod::GetF( bool flg )
{
	if( flg )
		SetVarState();
	return m_F.GetValue();
}

double CHardRod::GetE( bool flg )
{
	if( flg )
		SetVarState();
	return m_E.GetValue();
}

double CHardRod::GetJ( bool flg )
{
	if( flg )
		SetVarState();
	return m_J.GetValue();
}

bool CHardRod::SetF( const CString &str )
{
	return (m_F.Reset(str) == SEE_NOERR)?(true):(false);
}

bool CHardRod::SetM( const CString &str )
{
	return (m_M.Reset(str) == SEE_NOERR)?(true):(false);
}

bool CHardRod::SetE( const CString &str )
{
	return (m_E.Reset(str) == SEE_NOERR)?(true):(false);
}

bool CHardRod::SetJ( const CString &str )
{
	return (m_J.Reset(str) == SEE_NOERR)?(true):(false);
}

bool CHardRod::SetF( double val )
{
	return (m_F.SetValue(val) == SEE_NOERR)?(true):(false);
}

bool CHardRod::SetE( double val )
{
	return (m_E.SetValue(val) == SEE_NOERR)?(true):(false);
}

bool CHardRod::SetJ( double val )
{
	return (m_J.SetValue(val) == SEE_NOERR)?(true):(false);
}

bool CHardRod::SetM( double val )
{
	return (m_M.SetValue(val) == SEE_NOERR)?(true):(false);
}

CString CHardRod::GetName() const
{
	CString name;
	name.Format("Жесткий стержень №%d (E=%s,F=%s,J=%s,m=%s)", GetNumber(), m_E.GetExpr().c_str(), m_F.GetExpr().c_str(), m_J.GetExpr().c_str(), m_M.GetExpr().c_str() );
	return name;
}
