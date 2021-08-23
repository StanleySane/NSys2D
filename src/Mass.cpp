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

	CRect rect(point.x-rad, point.y-rad, point.x+rad, point.y+rad);
	
	pDC->FillRect(&rect, &brush);
	//pDC->Ellipse(point.x-rad,point.y-rad,point.x+rad,point.y+rad);
	knot1->Draw(pDC,pParamView);
	
	pDC->SelectObject(pOldbrush);
	pDC->SelectObject(pOld);
}

int CMass::GoDlg(CListKnot * pListKnot)
{
	CMassDlg dlg(pListKnot, this);
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

double CMass::GetM()
{
	return M;
}

double CMass::GetJp()
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
	CMatr loc_matr(3,3);

	double m=GetM();
	double Jp=GetJp();
	
	loc_matr[0][0]=m;
	loc_matr[1][1]=m;
	loc_matr[2][2]=Jp;
		
	int N[3];
	N[0]=knot1->nXRez;
	N[1]=knot1->nYRez;
	N[2]=knot1->nARez[0];

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
