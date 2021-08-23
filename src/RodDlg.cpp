// RodDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "RodDlg.h"

#include "KnotDlg.h"
#include "Sheme.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRodDlg dialog


CRodDlg::CRodDlg(CListKnot *plistkn,CRod *prod/*=NULL*/,
				 bool full/*true*/,
				 CWnd* pParent /*=NULL*/)
	: CDialog(CRodDlg::IDD, pParent)
{
	m_bFull = full;
	pRod=prod;
	pListKnot=plistkn;

	//{{AFX_DATA_INIT(CRodDlg)
	m_EditJx = _T("1");
	m_EditE = _T("1");
	m_EditM = _T("1");
	m_EditF = _T("1");
	//}}AFX_DATA_INIT
}


void CRodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRodDlg)
	DDX_Control(pDX, IDC_COMBO4, m_ConnectType2);
	DDX_Control(pDX, IDC_COMBO1, m_ConnectType1);
	DDX_Control(pDX, IDC_COMBO3, m_ComboBoxKnot2);
	DDX_Control(pDX, IDC_COMBO2, m_ComboBoxKnot1);
	DDX_Text(pDX, IDC_EDIT1, m_EditJx);
	DDV_MaxChars(pDX, m_EditJx, 100);
	DDX_Text(pDX, IDC_EDIT2, m_EditE);
	DDV_MaxChars(pDX, m_EditE, 100);
	DDX_Text(pDX, IDC_EDIT3, m_EditM);
	DDV_MaxChars(pDX, m_EditM, 100);
	DDX_Text(pDX, IDC_EDIT4, m_EditF);
	DDV_MaxChars(pDX, m_EditF, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRodDlg, CDialog)
	//{{AFX_MSG_MAP(CRodDlg)
	ON_BN_CLICKED(IDC_BUTNEWKNOT, OnButnewknot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRodDlg message handlers

void CRodDlg::OnButnewknot() 
{
	// TODO: Add your control notification handler code here
	CKnot knot;
	if (knot.GoDlg())
	{
		pListKnot->AddKnot(knot);
		InvalidateKnot(TRUE);
	}
}

BOOL CRodDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	InvalidateKnot(FALSE);

	//жесткое присоединение
	m_ConnectType1.SetCurSel(0);
	m_ConnectType2.SetCurSel(0);

	if ((pRod->knot1)&&(pRod->knot2))
	{
		m_ConnectType1.SetCurSel(pRod->knot1->ConnectType);
		m_ConnectType2.SetCurSel(pRod->knot2->ConnectType);
	}

	if (pRod)
	{
		int pos1=pListKnot->FindPos(pRod->knot1)-1;
		int pos2=pListKnot->FindPos(pRod->knot2)-1;

		m_ComboBoxKnot1.SetCurSel(pos1);
		m_ComboBoxKnot2.SetCurSel(pos2);

		m_EditJx = pRod->m_Jx.GetExpr().c_str();
		m_EditE = pRod->m_E.GetExpr().c_str();
		m_EditM = pRod->m_m0.GetExpr().c_str();
		m_EditF = pRod->m_F.GetExpr().c_str();
	}

	GetDlgItem(IDC_COMBO1)->EnableWindow(m_bFull);
	GetDlgItem(IDC_COMBO2)->EnableWindow(m_bFull);
	GetDlgItem(IDC_COMBO3)->EnableWindow(m_bFull);
	GetDlgItem(IDC_COMBO4)->EnableWindow(m_bFull);
	GetDlgItem(IDC_BUTNEWKNOT)->EnableWindow(m_bFull);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CRodDlg::VerifyInfo()
{
	UpdateData();

	if( m_bFull )
	{
		CKnot *kn1=pListKnot->GetKnotPos(m_ComboBoxKnot1.GetCurSel());
		CKnot *kn2=pListKnot->GetKnotPos(m_ComboBoxKnot2.GetCurSel());

		if (kn1==kn2) 
		{
			MessageBox("Задано два одинаковых узла","Ошибка!"
				,MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}

	CString mes;
	ASSERT(pRod->m_pSheme);
	if( !pRod->m_pSheme->m_VarsTable.IsValidExpr( m_EditF, mes ) )
	{
		mes = _T("Ошибка в выражении F:\n") + mes;
		AfxMessageBox( mes );
		return FALSE;
	}
	if( !pRod->m_pSheme->m_VarsTable.IsValidExpr( m_EditJx, mes ) )
	{
		mes = _T("Ошибка в выражении Jx:\n") + mes;
		AfxMessageBox( mes );
		return FALSE;
	}
	if( !pRod->m_pSheme->m_VarsTable.IsValidExpr( m_EditE, mes ) )
	{
		mes = _T("Ошибка в выражении E:\n") + mes;
		AfxMessageBox( mes );
		return FALSE;
	}
	if( !pRod->m_pSheme->m_VarsTable.IsValidExpr( m_EditM, mes ) )
	{
		mes = _T("Ошибка в выражении m:\n") + mes;
		AfxMessageBox( mes );
		return FALSE;
	}

	return TRUE;
}

void CRodDlg::InvalidateKnot(BOOL bSave)
{
	if( !m_bFull )	return;
	int pos1=0,pos2=0;
	
	if (bSave)
	{
		pos1=m_ComboBoxKnot1.GetCurSel();
		pos2=m_ComboBoxKnot2.GetCurSel();
	}

	m_ComboBoxKnot1.ResetContent();
	m_ComboBoxKnot2.ResetContent();

	int count=0;
	POSITION pos=pListKnot->GetHeadPosition();
	while (pos)
	{
		CKnot *kn=pListKnot->GetNext(pos);
		count++;
//		count=pListKnot->FindPos(kn);
		CString name=kn->GetName(count);
		m_ComboBoxKnot1.AddString(name);
		m_ComboBoxKnot2.AddString(name);
	}

	if (m_ComboBoxKnot1.GetCount())
	{
		m_ComboBoxKnot1.SetCurSel(0);
		m_ComboBoxKnot2.SetCurSel(0);
	}
	if (bSave)
	{
		m_ComboBoxKnot1.SetCurSel(pos1);
		m_ComboBoxKnot2.SetCurSel(pos2);
	}
}

void CRodDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (!VerifyInfo()) return;

//	if (pRod->knot1) pRod->knot1->DelElemKnot(pRod->knot2);
//	if (pRod->knot2) pRod->knot2->DelElemKnot(pRod->knot1);

	CKnot *kn1, *kn2;
	if( m_bFull )
	{
		kn1=pListKnot->GetKnotPos(m_ComboBoxKnot1.GetCurSel());
		kn2=pListKnot->GetKnotPos(m_ComboBoxKnot2.GetCurSel());
	}
	else
	{
		kn1 = pRod->knot1;
		kn2 = pRod->knot2;
	}

	if (!pRod)
		pRod=new CRod(kn1, kn2);

	pRod->knot1=kn1;
	pRod->knot2=kn2;

	bool res = pRod->SetF(m_EditF);
	ASSERT( res == true );
	res = pRod->SetJx(m_EditJx);
	ASSERT( res == true );
	res = pRod->SetE(m_EditE);
	ASSERT( res == true );
	res = pRod->SetM(m_EditM);
	ASSERT( res == true );

	pRod->knot1->ConnectType=m_ConnectType1.GetCurSel();//m_Type1;
	pRod->knot2->ConnectType=m_ConnectType2.GetCurSel();//m_Type2;

//	pRod->knot1->AddElemKnot(pRod->knot2,pRod->type1);
//	pRod->knot2->AddElemKnot(pRod->knot1,pRod->type2);

	CDialog::OnOK();
}
