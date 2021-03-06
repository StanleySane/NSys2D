// SpringDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "SpringDlg.h"

#include "knot.h"
#include "Sheme.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpringDlg dialog


CSpringDlg::CSpringDlg(CListKnot *plistkn,
				   CSpring *psprn/*=NULL*/,
				   bool full/*true*/,
				   CWnd* pParent /*=NULL*/)
	: CDialog(CSpringDlg::IDD, pParent)
{
	m_bFull = full;
	pListKnot=plistkn;
	pSprn=psprn;
	//{{AFX_DATA_INIT(CSpringDlg)
	m_Radio_X1 = -1;
	m_Radio_X3 = -1;
	m_Radio_X5 = -1;
	m_Radio_XX = -1;
	m_Edit_XX = _T("");
	m_Edit_X1 = 0.0;
	m_Edit_X3 = 0.0;
	m_Edit_X5 = 0.0;
	//}}AFX_DATA_INIT
}


void CSpringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpringDlg)
	DDX_Control(pDX, IDC_COMBO3, m_ComboBoxKnot2);
	DDX_Control(pDX, IDC_COMBO2, m_ComboBoxKnot1);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio_X1);
	DDX_Radio(pDX, IDC_RADIO2, m_Radio_X3);
	DDX_Radio(pDX, IDC_RADIO3, m_Radio_X5);
	DDX_Radio(pDX, IDC_RADIO4, m_Radio_XX);
	DDX_Text(pDX, IDC_EDIT4, m_Edit_XX);
	DDV_MaxChars(pDX, m_Edit_XX, 100);
	DDX_Text(pDX, IDC_EDIT1, m_Edit_X1);
	DDX_Text(pDX, IDC_EDIT2, m_Edit_X3);
	DDX_Text(pDX, IDC_EDIT3, m_Edit_X5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpringDlg, CDialog)
	//{{AFX_MSG_MAP(CSpringDlg)
	ON_BN_CLICKED(IDC_BUTNEWKNOT, OnButnewknot)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpringDlg message handlers

void CSpringDlg::OnButnewknot() 
{
	// TODO: Add your control notification handler code here
	CKnot knot;
	if (knot.GoDlg())
	{
		pListKnot->AddKnot(knot);
		InvalidateKnot(TRUE);
	}
}

void CSpringDlg::InvalidateKnot(BOOL bSave/*=NULL*/)
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

BOOL CSpringDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InvalidateKnot(FALSE);

	m_Radio_X1=0;

	if (pSprn)
	{
		int pos1=pListKnot->FindPos(pSprn->knot1)-1;
		int pos2=pListKnot->FindPos(pSprn->knot2)-1;

		m_ComboBoxKnot1.SetCurSel(pos1);
		m_ComboBoxKnot2.SetCurSel(pos2);

//		m_Edit_X1.SetWindowText(pSprn->GetStrX1());
//		m_Edit_X3.SetWindowText(pSprn->GetStrX3());
//		m_Edit_X5.SetWindowText(pSprn->GetStrX5());
//		m_Edit_XX.SetWindowText(pSprn->GetStrXX());
		m_Edit_X1 = pSprn->GetSprnX1();
		m_Edit_X3 = pSprn->GetSprnX3();
		m_Edit_X5 = pSprn->GetSprnX5();
		m_Edit_XX = pSprn->m_XX.GetExpr().c_str();

		m_Radio_X1=(pSprn->type==1?0:-1);
		m_Radio_X3=(pSprn->type==3?0:-1);
		m_Radio_X5=(pSprn->type==5?0:-1);
		m_Radio_XX=(pSprn->type==0?0:-1);
	}

	GetDlgItem(IDC_COMBO2)->EnableWindow(m_bFull);
	GetDlgItem(IDC_COMBO3)->EnableWindow(m_bFull);
	GetDlgItem(IDC_BUTNEWKNOT)->EnableWindow(m_bFull);

	SetState();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSpringDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (!VerifyInfo()) return;

	CKnot *kn1, *kn2;
	if( m_bFull )
	{
		kn1=pListKnot->GetKnotPos(m_ComboBoxKnot1.GetCurSel());
		kn2=pListKnot->GetKnotPos(m_ComboBoxKnot2.GetCurSel());
	}
	else
	{
		kn1 = pSprn->knot1;
		kn2 = pSprn->knot2;
	}

	if (!pSprn)
		pSprn=new CSpring(kn1, kn2);

	pSprn->knot1=kn1;
	pSprn->knot2=kn2;

	bool res = pSprn->SetSprnX1( m_Edit_X1 );
	ASSERT( res == true );
	res = pSprn->SetSprnX3( m_Edit_X3 );
	ASSERT( res == true );
	res = pSprn->SetSprnX5( m_Edit_X5 );
	ASSERT( res == true );
	res = pSprn->SetSprnXX( m_Edit_XX );
	ASSERT( res == true );
	/*
	CString str;

	m_Edit_X1.GetWindowText(str);
	pSprn->SetSprnX1(str);

	m_Edit_X3.GetWindowText(str);
	pSprn->SetSprnX3(str);

	m_Edit_X5.GetWindowText(str);
	pSprn->SetSprnX5(str);

	m_Edit_XX.GetWindowText(str);
	pSprn->SetSprnXX(str);
	*/

	if (m_Radio_X1==0) pSprn->type=1;
	if (m_Radio_X3==0) pSprn->type=3;
	if (m_Radio_X5==0) pSprn->type=5;
	if (m_Radio_XX==0) pSprn->type=0;

	CDialog::OnOK();
}

void CSpringDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	m_Radio_X1=0;
	m_Radio_X3=m_Radio_X5=m_Radio_XX=-1;
	SetState();
	UpdateData(FALSE);
}

void CSpringDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	m_Radio_X3=0;
	m_Radio_X1=m_Radio_X5=m_Radio_XX=-1;
	SetState();
	UpdateData(FALSE);
}

void CSpringDlg::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	m_Radio_X5=0;
	m_Radio_X3=m_Radio_X1=m_Radio_XX=-1;
	SetState();
	UpdateData(FALSE);	
}

void CSpringDlg::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	m_Radio_XX=0;
	m_Radio_X1=m_Radio_X3=m_Radio_X5=m_Radio_X1=-1;
	SetState();
	UpdateData(FALSE);
}

int CSpringDlg::SetState()
{
//	m_Edit_X1.EnableWindow(m_Radio_X1==0);
//	m_Edit_X3.EnableWindow(m_Radio_X3==0);
//	m_Edit_X5.EnableWindow(m_Radio_X5==0);
//	m_Edit_XX.EnableWindow(m_Radio_XX==0);
	GetDlgItem(IDC_EDIT1)->EnableWindow(m_Radio_X1==0);
	GetDlgItem(IDC_EDIT2)->EnableWindow(m_Radio_X3==0);
	GetDlgItem(IDC_EDIT3)->EnableWindow(m_Radio_X5==0);
	GetDlgItem(IDC_EDIT4)->EnableWindow(m_Radio_XX==0);
	return 1;
}

BOOL CSpringDlg::VerifyInfo()
{
	UpdateData();

	if( m_bFull )
	{
		CKnot *kn1=pListKnot->GetKnotPos(m_ComboBoxKnot1.GetCurSel());
		CKnot *kn2=pListKnot->GetKnotPos(m_ComboBoxKnot2.GetCurSel());

		if (kn1==kn2) 
		{
			MessageBox("?????? ??? ?????????? ????","??????!"
				,MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}

	CString mes;
	ASSERT(pSprn->m_pSheme);
	if( !pSprn->m_pSheme->m_VarsTable.IsValidExpr( m_Edit_XX, mes ) )
	{
		mes = _T("?????? ? ????????? ") + m_Edit_XX + _T(":\n") + mes;
		AfxMessageBox( mes );
		return FALSE;
	}
	return TRUE;
}
