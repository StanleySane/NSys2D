// HardRod.cpp: implementation of the CHardRod class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "HardRod.h"
#include "HardRodDlg.h"
#include "matr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHardRod::CHardRod(CKnot *kn1, CKnot *kn2):CElem(kn1,kn2)
{
	SetE(CString("1"));  
	SetF(CString("1"));  
	SetJ(CString("1"));
	SetM(CString("1"));
	TypeElem = IDC_HARDROD;
	FreeA1 = FreeA2 = 0;

	m_HardMethod = 0;
	m_NofKnots = 2;
	m_NofHardRodsInOneKnot[0] = m_NofHardRodsInOneKnot[1] = 1;
}

CHardRod::~CHardRod()
{

}

///////////////////////////////////////////////////////////////
//	realisations
///////////////////////////////////////////////////////////////

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
		//ќпределение локальных перемещений
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

		double tmp1 = point2.x-point1.x, tmp2 = point2.y-point1.y;
		double tmp3 = tmp1*tmp1, tmp4 = tmp2*tmp2;
		double tStep=1.0/(sqrt(tmp3+tmp4)+1);
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

	//Ќомер элемента
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
		CPoint point = ShemeToScreen( (k1+k2)/2, pParamView );//середина между двум€ узлами
		pDC->TextOut( point.x, point.y, str );

		pDC->SetBkMode(oldBkMode);
		pDC->SetTextColor(oldClr);

		pDC->SelectObject(pOldFont);
	}

	knot1->Draw(pDC,pParamView);
	knot2->Draw(pDC,pParamView);

	pDC->SelectObject(pOld);
}

void CHardRod::SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC)
{
	//Ќомера степеней свободы
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
		GetMatrC( locC );
		for( int i = 0; i < 6; i++ )
			for( int j = 0; j < 6; j++ )
				if( (N[i] >= 0)&&(N[j] >= 0) )
				{
					mC[N[i]][N[j]] += locC[i][j];
				}
	}

	CMatr locM;
	GetMatrM( locM );
	for( int i = 0; i < 6; i++ )
		for( int j = 0; j < 6; j++ )
			if( (N[i] >= 0)&&(N[j] >= 0) )
			{
				mM[N[i]][N[j]] += locM[i][j];
			}
}

int CHardRod::SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, int i, double Tt)
{
	return 0;
}

void CHardRod::Serialize(CArchive & ar)
{
	CElem::Serialize(ar);

	if (ar.IsStoring())
	{	// storing code
		ar << GetStrF();
		ar << GetStrJ();
		ar << GetStrE();
		ar << GetStrM();
	}
	else
	{	// loading code
		CString F, E, J, M;
		ar >> F >> J >> E >> M;
		SetF(F);
		SetJ(J);
		SetE(E);
		SetM(M);
	}
}

int CHardRod::GoDlg( CListKnot *pListKnot, bool full )
{
	CHardRodDlg dlg( pListKnot, this, full );
	if( dlg.DoModal() == IDOK )	return 1;
	return 0;
}

bool CHardRod::SetCommonProperties( CElem* elem )
{
	CHardRod *pHR = dynamic_cast<CHardRod*>(elem);
	if( !pHR )	return false;

	str_E = pHR->str_E;
	str_J = pHR->str_J;
	str_m = pHR->str_m;
	str_F = pHR->str_F;
	E = pHR->E;
	J = pHR->J;
	m = pHR->m;
	F = pHR->F;

	return true;
}

void CHardRod::GetMatrM( CMatr &matr ) const
{
	matr.ReSize( 6, 6 );

	double J = GetJ();
	double m = GetM();//масса стержн€

	if( m_HardMethod != 2 )
	{
		if( m_HardMethod == 0 )
		{
			//использование жЄст. .Ё. без разноса масс
			//матрица масс
			matr[0][0]= matr[1][1] = matr[3][3] = matr[4][4] = m/2.0;
			matr[2][2] = matr[5][5] = J/2.0;
		}
		else
		{
			//m_HardMethod == 1
			//m_NofKnots - кол-во узлов, св€занных подр€д жЄсткими эл-ми
			//m_NofHardRodsInOneKnot[0] - кол-во стержней, сход€щихс€ в первом узле
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
		//использование обычного  .Ё., но с удалением степеней свободы
		CMatr T(6,6);
		GetMatrT( T, 6 );

		double L = GetLength();
		double F = GetF();
		double E = GetE();

		m /= L;//погонна€ масса
		double mL = m*L, mL2 = mL*L, mL3 = mL2*L, EF = E*F;
		//матрица масс
		matr[0][0]= mL/3.0;
		matr[3][3]= mL/3.0;
		matr[3][0]= mL/6.0;
		//матрица жЄсткости
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
	TRACE0("\n\n!T*locM*T:\n");
	for( int r = 0; r < matr.SizeY; r++ )
	{
		for( int c = 0; c < matr.SizeX; c++ )
		{
			TRACE1("%.6e ", matr[r][c] );
		}
		TRACE0("\n");
	}
////////////////////////////////////////////
}

void CHardRod::GetMatrD( CMatr &m ) const
{
	m.ReSize( 6, 6 );
}

void CHardRod::GetMatrC( CMatr &matr ) const
{
	matr.ReSize( 6, 6 );
	if( m_HardMethod == 2 )
	{
		//использование обычного  .Ё., но с удалением степеней свободы
		CMatr T( 6, 6 );
		GetMatrT( T, 6 );

		double F = GetF();
		double E = GetE();
		double J = GetJ();
		double L = GetLength();
		double m = GetM();//масса стержн€

		m /= L;//погонна€ масса
		//матрица жЄсткости
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
