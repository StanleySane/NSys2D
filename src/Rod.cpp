// Rod.cpp: implementation of the CRod class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "Rod.h"
#include "RodDlg.h"
#include "matr.h"

#include "ShemeDoc.h"
#include "Sheme.h"
#include "MovieView.h"

#include <cmath>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRod::CRod( CKnot *kn1, CKnot *kn2, CSheme *p ):CElem(kn1,kn2,p)
{
	//SetE(CString("1"));  
	//SetF(CString("1"));  
	//SetJx(CString("1"));
	//SetM(CString("1"));
	TypeElem = IDC_ROD;
	FreeA1 = FreeA2 = 0;

	CShemeVarsTable *pVT = (m_pSheme)?(&m_pSheme->m_VarsTable):(NULL);
	string Val("1");

	m_E.Reset( Val, pVT );
	m_F.Reset( Val, pVT );
	m_Jx.Reset( Val, pVT );
	m_m0.Reset( Val, pVT );
}

CRod::~CRod()
{

}

CRod::CRod( const CRod &elem ):CElem(elem)
{
	InitBy(elem);
}

CRod& CRod::operator=( const CRod &elem )
{
	if( this != (&elem) )
		InitBy(elem);
	return *this;
}

void CRod::InitBy( const CRod &elem )
{
	SetCommonProperties( &elem );
	FreeA1 = elem.FreeA1;
	FreeA2 = elem.FreeA2;
}

void CRod::SetVarState()
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

double CRod::GetM( bool flg )
{
	if( flg )
		SetVarState();
	return m_m0.GetValue();
}

double CRod::GetF( bool flg )
{
	if( flg )
		SetVarState();
	return m_F.GetValue();
}

double CRod::GetE( bool flg )
{
	if( flg )
		SetVarState();
	return m_E.GetValue();
}

double CRod::GetJx( bool flg )
{
	if( flg )
		SetVarState();
	return m_Jx.GetValue();
}

bool CRod::SetF( const CString &str )
{
	return (m_F.Reset(str) == SEE_NOERR)?(true):(false);
}

bool CRod::SetM( const CString &str )
{
	return (m_m0.Reset(str) == SEE_NOERR)?(true):(false);
}

bool CRod::SetE( const CString &str )
{
	return (m_E.Reset(str) == SEE_NOERR)?(true):(false);
}

bool CRod::SetJx( const CString &str )
{
	return (m_Jx.Reset(str) == SEE_NOERR)?(true):(false);
}

bool CRod::SetF( double val )
{
	return (m_F.SetValue(val) == SEE_NOERR)?(true):(false);
}

bool CRod::SetE( double val )
{
	return (m_E.SetValue(val) == SEE_NOERR)?(true):(false);
}

bool CRod::SetJx( double val )
{
	return (m_Jx.SetValue(val) == SEE_NOERR)?(true):(false);
}

bool CRod::SetM( double val )
{
	return (m_m0.SetValue(val) == SEE_NOERR)?(true):(false);
}

void CRod::DrawGL( CShemeDoc *pDoc, int Time )
{
	ASSERT( pDoc->m_pMovieView );

	CMovieView::RodMoves::iterator it = pDoc->m_pMovieView->m_RodMoves.find(this);
	if( it == pDoc->m_pMovieView->m_RodMoves.end() )
	{
		ASSERT(FALSE);
		return;
	}

	glLineWidth( 2 );
	glColor3f( 0.0f, 0.0f, 1.0f );

	if( Time < 0 )
	{
		double x1, y1, x2, y2;
		CCoordD c;
		c = knot1->GetCoord();
		x1 = c.x;
		y1 = c.y;
		c = knot2->GetCoord();
		x2 = c.x;
		y2 = c.y;
		glBegin(GL_LINES);
			glVertex2d( x1, y1 );
			glVertex2d( x2, y2 );
		glEnd();
	}
	else
	{
		CMovieView::RodMoves::referent_type::value_type *vec = &((*it).second.at(Time));
		int s = vec->size();
		glBegin(GL_LINE_STRIP);
			for( int i = 0; i < s; i++ )
			{
				glVertex2d( (vec->at(i)).first, (vec->at(i)).second );
			}
		glEnd();
	}
	knot1->DrawGL( pDoc, Time );
	knot2->DrawGL( pDoc, Time );
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

		Ugl(0,0) = knot1->MoveX*pParamView->MultMove;
		Ugl(1,0) = knot1->MoveY*pParamView->MultMove;
		Ugl(2,0) = knot1->MoveA[FreeA1]*pParamView->MultAngl;
		Ugl(3,0) = knot2->MoveX*pParamView->MultMove;
		Ugl(4,0) = knot2->MoveY*pParamView->MultMove;
		Ugl(5,0) = knot2->MoveA[FreeA2]*pParamView->MultAngl;

		GetMatrT(T, 6);

		Uloc = T*Ugl;//T*Ugl;
		mM(0,0) = mM(5,5) = mM(2,5) = mM(1,4) = mM(1,1) = mM(2,1) = mM(1,2) = mM(2,2) = 0.0;
		mM(3,0) = mM(4,4) = L;
		mM(4,1) = L*L*L;
		mM(5,1) = 3*L*L;
		mM(4,2) = L*L;
		mM(5,2) = 2*L;
		mM(0,3) = mM(4,5) = mM(3,3) = mM(2,4) = mM(5,4) = mM(1,5) = 1.0;

		if (!mM.SolveSystem(Uloc, A)) 
			A.ClearData();
		
		CMatr T1(2,2), T_1(2,2);
		GetMatrT(T1,2);
		T_1 = !T1;//!T1;

		double tmp1 = point2.x-point1.x, tmp2 = point2.y-point1.y;
		double tmp3 = tmp1*tmp1, tmp4 = tmp2*tmp2;
		double tStep = 1.0/(sqrt(tmp3+tmp4)+1.0);
		CCoordD c1 = knot1->GetCoord();
		CCoordD c2 = knot2->GetCoord();

		CMatr Uu(2,1), U(2,1);
		for( double t = 0.0; t <= 1.0; t += tStep )
		{
			CCoordD c = knot1->GetCoord();
			double tl = t*L, tl2 = tl*tl, tl3 = tl2*tl;
			Uu(0,0) = A(0,0)*tl + A(3,0);
			Uu(1,0) = A(1,0)*tl3 + A(2,0)*tl2 + A(4,0)*tl + A(5,0);
			U=T_1*Uu;
			CCoordD cc(	U(0,0)+(c2.x-c1.x)*t+c1.x, U(1,0)+(c2.y-c1.y)*t+c1.y );
			POINT p = ShemeToScreen(cc, pParamView);

			if( t == 0 )
				pDC->MoveTo(p);
			else
				pDC->LineTo(p);
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

int CRod::GoDlg(CListKnot *pListKnot, bool full )
{
	CRodDlg dlg( pListKnot, this, full );
	if (dlg.DoModal()==IDOK) 
		return 1;
	return 0;
}

/*
CString CRod::GetStrE()
{
	return str_E;
}

CString CRod::GetStrJx()
{
	return str_Jx;
}

CString CRod::GetStrM()
{
	return str_m0;
}

CString CRod::GetStrF()
{
	return str_F;
}
*/

void CRod::SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC, std::string *pMsg )
{
	CMatr locM, locC;
	GetMatrM( locM, pMsg );
	GetMatrC( locC, pMsg );

	//Номера степеней свободы
	int N[6];
	N[0]=knot1->nXRez;
	N[1]=knot1->nYRez;
	N[2]=knot1->nARez[FreeA1];
	N[3]=knot2->nXRez;
	N[4]=knot2->nYRez;
	N[5]=knot2->nARez[FreeA2];
	
	//с одной стороны шарнирное опирание
/*	if ( ((knot1->ConnectType==0)&&(knot2->ConnectType!=0))||
		 ((knot1->ConnectType!=0)&&(knot2->ConnectType==0)) )
	{
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
	*/

	for (int i=0;i<6;i++)
		for(int j=0;j<6;j++)
			if ((N[i]>=0)&&(N[j]>=0))
			{
				mM[N[i]][N[j]]+=locM[i][j];
				mC[N[i]][N[j]]+=locC[i][j];
			}
}

int CRod::SetMatrmP( CMatr &mP, CMatr &RezY1, CMatr &RezY2, CMatr *Y3, int i, double Tt, std::string *pMsg )
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

void CRod::Serialize( CArchive &ar, int _sv )
{
	CElem::Serialize( ar, _sv );

	if (ar.IsStoring())
	{	// storing code
		//ar << GetStrF();
		//ar << GetStrJx();
		//ar << GetStrE();
		//ar << GetStrM();
		m_F.Serialize( ar );
		m_Jx.Serialize( ar );
		m_E.Serialize( ar );
		m_m0.Serialize( ar );
	}
	else
	{	// loading code
		/*
		CString F,E,Jx,M;
		ar >> F >> Jx >> E >> M;
		SetF(F);
		SetJx(Jx);
		SetE(E);
		SetM(M);
		*/
		m_F.Serialize( ar );
		m_Jx.Serialize( ar );
		m_E.Serialize( ar );
		m_m0.Serialize( ar );
	}
}

bool CRod::SetCommonProperties( const CElem* elem )
{
	//CRod *pRod = dynamic_cast<CRod*>(elem);
	const CRod *pRod = static_cast<const CRod*>(elem);
	if( !pRod )	return false;

	//str_E = pRod->str_E;
	//str_Jx = pRod->str_Jx;
	//str_m0 = pRod->str_m0;
	//str_F = pRod->str_F;
	//E = pRod->E;
	//Jx = pRod->Jx;
	//m0 = pRod->m0;
	//F = pRod->F;
	m_F.InitBy( pRod->m_F );
	m_E.InitBy( pRod->m_E );
	m_m0.InitBy( pRod->m_m0 );
	m_Jx.InitBy( pRod->m_Jx );

	return true;
}

void CRod::GetMatrM( CMatr &matr, std::string *pMsg )
{
	matr.ReSize( 6, 6 );
	CMatr T( 6, 6 );
	GetMatrT( T, 6 );

	double m = GetM();
	double F = GetF( false );
	double E = GetE( false );
	double J = GetJx( false );
	if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
	{
		ShemeExprErr err = m_Jx.GetRunErrorCode();
		if( err != SEE_NOERR )
		{
			(*pMsg) = m_Jx.GetFullErrorMsg(err);
			return;
		}
		err = m_m0.GetRunErrorCode();
		if( err != SEE_NOERR )
		{
			(*pMsg) = m_m0.GetFullErrorMsg(err);
			return;
		}
		err = m_E.GetRunErrorCode();
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
	double L = GetLength();

//матрица масс
	matr[0][0]= m*L/3.0;
	matr[3][3]= m*L/3.0;
	matr[3][0]= m*L/6.0;

	//жестко закрепленный стержень по обоим краям
//	if ((knot1->ConnectType==0)&&(knot2->ConnectType==0))
	{
		//матрица масс
		matr[1][1]= m*L*13.0/35.0;
		matr[2][1]= m*L*L*11.0/210.0;
		matr[4][1]= m*L*9.0/70.0;
		matr[5][1]=-m*L*L*13.0/420.0;

		matr[2][2]= m*L*L*L/105.0;
		matr[4][2]= m*L*L*13.0/420.0;
		matr[5][2]=-m*L*L*L*1/140.0;

		matr[4][4]= m*L*13.0/35.0;
		matr[5][4]=-m*L*L*11.0/210.0;

		matr[5][5]= m*L*L*L/105.0;
	
	}
	//с одной стороны шарнирное опирание
/*	if ( ((knot1->ConnectType==0)&&(knot2->ConnectType!=0))||
		 ((knot1->ConnectType!=0)&&(knot2->ConnectType==0)) )
	{
		//матрица масс
		matr[1][1]= m*L*17.0/35.0;
		matr[2][1]= m*L*L*3.0/35.0;
		matr[4][1]= m*L*39.0/280.0;
		matr[5][1]=-m*L*L*19.0/420.0;

		matr[2][2]= m*L*L*L*2/105.0;
		matr[4][2]= m*L*L*11.0/280.0;
		matr[5][2]=-m*L*L*L/84.0;

		matr[4][4]= m*L*33.0/140.0;
		matr[5][4]=-m*L*L*4.0/105.0;

		matr[5][5]= m*L*L*L/105.0;

	}
	//с обоих сторон шарнирное опирание
	if ((knot1->ConnectType!=0)&&(knot2->ConnectType!=0))
	{
		//матрица масс
		matr[1][1]= m*L/3.0;
		matr[2][1]= m*L*L*1.0/15.0;
		matr[4][1]= m*L/6.0;
		matr[5][1]=-m*L*L*7.0/120.0;

		matr[2][2]= m*L*L*L*2/105.0;
		matr[4][2]= m*L*L*7.0/120.0;
		matr[5][2]=-m*L*L*L*31.0/1680.0;

		matr[4][4]= m*L/3.0;
		matr[5][4]=-m*L*L/15.0;

		matr[5][5]= m*L*L*L*2/105.0;
	}*/

	matr.CopyDownToUp();
	matr = !T*matr*T;
}

void CRod::GetMatrD( CMatr &matr, std::string *pMsg )
{
	matr.ReSize( 6, 6 );
}

void CRod::GetMatrC( CMatr &matr, std::string *pMsg )
{
	matr.ReSize( 6, 6 );
	CMatr T( 6, 6 );
	GetMatrT( T, 6 );

	double m = GetM();
	double F = GetF( false );
	double E = GetE( false );
	double J = GetJx( false );
	if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
	{
		ShemeExprErr err = m_Jx.GetRunErrorCode();
		if( err != SEE_NOERR )
		{
			(*pMsg) = m_Jx.GetFullErrorMsg(err);
			return;
		}
		err = m_m0.GetRunErrorCode();
		if( err != SEE_NOERR )
		{
			(*pMsg) = m_m0.GetFullErrorMsg(err);
			return;
		}
		err = m_F.GetRunErrorCode();
		if( err != SEE_NOERR )
		{
			(*pMsg) = m_F.GetFullErrorMsg(err);
			return;
		}
		err = m_E.GetRunErrorCode();
		if( err != SEE_NOERR )
		{
			(*pMsg) = m_E.GetFullErrorMsg(err);
			return;
		}
	}
	double L = GetLength();

//матрица жёсткости
	matr[0][0]= E*F/L;
	matr[3][3]= E*F/L;
	matr[3][0]=-E*F/L;

	//жестко закрепленный стержень по обоим краям
//	if ((knot1->ConnectType==0)&&(knot2->ConnectType==0))
	{
		//матрица жёсткости
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

	}
	//с одной стороны шарнирное опирание
/*	if ( ((knot1->ConnectType==0)&&(knot2->ConnectType!=0))||
		 ((knot1->ConnectType!=0)&&(knot2->ConnectType==0)) )
	{
		//матрица жёсткости
		matr[1][1]= 3*E*J/(L*L*L);
		matr[2][1]= 3*E*J/(L*L);
		matr[4][1]=-3*E*J/(L*L*L);
		matr[5][1]= 0;

		matr[2][2]= 3*E*J/L;
		matr[4][2]=-3*E*J/(L*L);
		matr[5][2]= 0;
		
		matr[4][4]= 3*E*J/(L*L*L);
		matr[5][4]= 0;

		matr[5][5]= 4*E*J/L;
	}
	//с обоих сторон шарнирное опирание
	if ((knot1->ConnectType!=0)&&(knot2->ConnectType!=0))
	{
		//матрица жёсткости
//		matr[1][1]= 12*E*J/(L*L*L);
//		matr[2][1]= 6*E*J/(L*L);
//		matr[4][1]=-12*E*J/(L*L*L);
//		matr[5][1]= 6*E*J/(L*L);

		matr[2][2]= 3*E*J/L;
//		matr[4][2]=-6*E*J/(L*L);
		matr[5][2]=-3*E*J/L/2.0;
		
//		matr[4][4]= 12*E*J/(L*L*L);
//		matr[5][4]=-6*E*J/(L*L);

		matr[5][5]= 3*E*J/L;
	}*/

	matr.CopyDownToUp();
	matr = !T*matr*T;
}

CString CRod::GetName() const
{
	CString name;
	name.Format("Стержень №%d (E=%s,F=%s,Jx=%s,m0=%s)", GetNumber(), m_E.GetExpr().c_str(), m_F.GetExpr().c_str(), m_Jx.GetExpr().c_str(), m_m0.GetExpr().c_str() );
	return name;
}
