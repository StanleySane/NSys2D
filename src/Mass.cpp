// Mass.cpp: implementation of the CMass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "Mass.h"

#include "Massdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMass::CMass(CKnot *kn1):CElem(kn1,kn1)
{
	SetMassM(_T("1"));		
	SetMassJp(_T("0"));	
	TypeElem=IDC_MASS;
}

CMass::~CMass()
{

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

double CMass::SetMassM(CString strm)
{
	CExpression e;
	double val;

	if (!e.IsNum(strm,&val))
	{
		str_M=strm;
		M=val;
		return val;
	}
	return -1;
}

double CMass::SetMassJp(CString strJp)
{
	CExpression e;
	double val;

	if (!e.IsNum(strJp,&val))
	{
		str_Jp=strJp;
		Jp=val;
		return val;
	}
	return -1;

}

double CMass::GetM() const
{
	return M;
}

double CMass::GetJp() const
{
	return Jp;
}

CString CMass::GetStrM()
{
	return str_M;
}

CString CMass::GetStrJp()
{
	return str_Jp;
}

void CMass::SetMatrMDC(CMatr & mM, CMatr & mD, CMatr & mC)
{
	CMatr loc_matr;
	GetMatrM( loc_matr );

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

void CMass::SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, int i)
{

}

void CMass::Serialize(CArchive & ar)
{
	CElem::Serialize(ar);

	if (ar.IsStoring())
	{	// storing code
		ar << GetStrM();
		ar << GetStrJp();
	}
	else
	{	// loading code
		CString M,Jp;
		ar >> M >> Jp;
		SetMassM(M);
		SetMassJp(Jp);
	}
}

bool CMass::SetCommonProperties( CElem* elem )
{
	CMass *pMass = dynamic_cast<CMass*>(elem);
	if( !pMass )	return false;

	str_M = pMass->str_M;
	str_Jp = pMass->str_Jp;
	M = pMass->M;
	Jp = pMass->Jp;

	return true;
}

void CMass::GetMatrM( CMatr &matr ) const
{
	matr.ReSize( 3, 3 );

	double m = GetM();
	double Jp = GetJp();
	
	matr[0][0] = m;
	matr[1][1] = m;
	matr[2][2] = Jp;
}

void CMass::GetMatrD( CMatr &matr ) const
{
	matr.ReSize( 3, 3 );
}

void CMass::GetMatrC( CMatr &matr ) const
{
	matr.ReSize( 3, 3 );
}