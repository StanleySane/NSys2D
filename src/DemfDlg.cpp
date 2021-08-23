// DemfDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "DemfDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "knotdlg.h"
/////////////////////////////////////////////////////////////////////////////
// CDemfDlg dialog


CDemfDlg::CDemfDlg(CListKnot *plistkn,
				   CDemf *pdemf/*=NULL*/, CWnd* pParent /*=NULL*/)
	: CDialog(CDemfDlg::IDD, pParent)
{
	pListKnot=plistkn;
	pDemf=pdemf;
	//{{AFX_DATA_INIT(CDemfDlg)
	m_Radio_X1 =  0;
	m_Radio_X3 = -1;
	m_Radio_X5 = -1;
	m_Radio_XX = -1;
	m_Radio_XS = -1;
	//}}AFX_DATA_INIT
}


void CDemfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemfDlg)
	DDX_Control(pDX, IDC_EDIT5, m_Edit_XX);
	DDX_Control(pDX, IDC_EDIT4, m_Edit_XS);
	DDX_Control(pDX, IDC_EDIT3, m_Edit_X5);
	DDX_Control(pDX, IDC_EDIT2, m_Edit_X3);
	DDX_Control(pDX, IDC_EDIT1, m_Edit_X1);
	DDX_Control(pDX, IDC_COMBO3, m_ComboBoxKnot2);
	DDX_Control(pDX, IDC_COMBO2, m_ComboBoxKnot1);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio_X1);
	DDX_Radio(pDX, IDC_RADIO2, m_Radio_X3);
	DDX_Radio(pDX, IDC_RADIO3, m_Radio_X5);
	DDX_Radio(pDX, IDC_RADIO5, m_Radio_XX);
	DDX_Radio(pDX, IDC_RADIO4, m_Radio_XS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDemfDlg, CDialog)
	//{{AFX_MSG_MAP(CDemfDlg)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_BUTNEWKNOT, OnButnewknot)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemfDlg message handlers

BOOL CDemfDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InvalidateKnot(FALSE);

	m_Radio_X1=0;

	if (pDemf)
	{
		int pos1=pListKnot->FindPos(pDemf->knot1)-1;
		int pos2=pListKnot->FindPos(pDemf->knot2)-1;

		m_ComboBoxKnot1.SetCurSel(pos1);
		m_ComboBoxKnot2.SetCurSel(pos2);

		m_Edit_X1.SetWindowText(pDemf->GetStrX(1));
		m_Edit_X3.SetWindowText(pDemf->GetStrX(3));
		m_Edit_X5.SetWindowText(pDemf->GetStrX(5));
		m_Edit_XS.SetWindowText(pDemf->GetStrX(6));
		m_Edit_XX.SetWindowText(pDemf->GetStrX(0));

		m_Radio_X1=(pDemf->type==1?0:-1);
		m_Radio_X3=(pDemf->type==3?0:-1);
		m_Radio_X5=(pDemf->type==5?0:-1);
		m_Radio_XS=(pDemf->type==6?0:-1);
		m_Radio_XX=(pDemf->type==0?0:-1);
	}
	SetState();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDemfDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (!VerifyInfo()) return;

	CKnot *kn1=pListKnot->GetKnotPos(m_ComboBoxKnot1.GetCurSel());
	CKnot *kn2=pListKnot->GetKnotPos(m_ComboBoxKnot2.GetCurSel());

	if (!pDemf)
		pDemf=new CDemf(kn1, kn2);

	pDemf->knot1=kn1;
	pDemf->knot2=kn2;

	CString str;

	m_Edit_X1.GetWindowText(str);
	pDemf->SetDemfX(str,1);

	m_Edit_X3.GetWindowText(str);
	pDemf->SetDemfX(str,3);

	m_Edit_X5.GetWindowText(str);
	pDemf->SetDemfX(str,5);

	m_Edit_XS.GetWindowText(str);
	pDemf->SetDemfX(str,6);

	m_Edit_XX.GetWindowText(str);
	pDemf->SetDemfX(str,0);

	if (m_Radio_X1==0) pDemf->type=1;
	if (m_Radio_X3==0) pDemf->type=3;
	if (m_Radio_X5==0) pDemf->type=5;
	if (m_Radio_XS==0) pDemf->type=6;
	if (m_Radio_XX==0) pDemf->type=0;

	CDialog::OnOK();
}

void CDemfDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	m_Radio_X1=0;
	m_Radio_XS=m_Radio_X3=m_Radio_X5=m_Radio_XX=-1;
	SetState();
	UpdateData(FALSE);
}

void CDemfDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	m_Radio_X3=0;
	m_Radio_XS=m_Radio_X1=m_Radio_X5=m_Radio_XX=-1;
	SetState();
	UpdateData(FALSE);
}

BOOL CDemfDlg::VerifyInfo()
{
	UpdateData();
	
	CKnot *kn1=pListKnot->GetKnotPos(m_ComboBoxKnot1.GetCurSel());
	CKnot *kn2=pListKnot->GetKnotPos(m_ComboBoxKnot2.GetCurSel());

	if (kn1==kn2) 
	{
		MessageBox("Задано два одинаковых узла","Ошибка!"
			,MB_OK|MB_ICONERROR);
		return FALSE;
	}

	CExpression e;
	int ret;
	CString str1;

	if (m_Radio_X1==0)
	{
		m_Edit_X1.GetWindowText(str1);
		ret=e.IsNum(str1);
		if (ret)
		{
			CString str;
			str.LoadString(ret);
			MessageBox(str,"Коэфф. демпф. не число"
				,MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}
	if (m_Radio_X3==0)
	{
		m_Edit_X3.GetWindowText(str1);
		ret=e.IsNum(str1);
		if (ret)
		{
			CString str;
			str.LoadString(ret);
			MessageBox(str,"Коэфф. демпф. не число"
				,MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}
	if (m_Radio_X5==0)
	{
		m_Edit_X5.GetWindowText(str1);
		ret=e.IsNum(str1);
		if (ret)
		{
			CString str;
			str.LoadString(ret);
			MessageBox(str,"Коэфф. демпф. не число"
				,MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}
	if (m_Radio_XS==0)
	{
		m_Edit_XS.GetWindowText(str1);
		ret=e.IsNum(str1);
		if (ret)
		{
			CString str;
			str.LoadString(ret);
			MessageBox(str,"Коэфф. демпф. не число"
				,MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}
	if (m_Radio_XX==0)
	{
		m_Edit_XX.GetWindowText(str1);
		CIDValuesMap idv;
		idv.SetAt(_T("x"),0.1);
		idv.SetAt(_T("x1"),0.1);
		idv.SetAt(_T("t"),0.1);
		ret=e.IsNum(str1,0,&idv);
		if (ret)
		{
			CString str;
			str.LoadString(ret);
			MessageBox(str,"Ошибка в выражении"
				,MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}

	return true;
}

void CDemfDlg::InvalidateKnot(BOOL bSave)
{
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

int CDemfDlg::SetState()
{
	m_Edit_X1.EnableWindow(m_Radio_X1==0);
	m_Edit_X3.EnableWindow(m_Radio_X3==0);
	m_Edit_X5.EnableWindow(m_Radio_X5==0);
	m_Edit_XS.EnableWindow(m_Radio_XS==0);
	m_Edit_XX.EnableWindow(m_Radio_XX==0);
	return 1;
}

void CDemfDlg::OnButnewknot() 
{
	// TODO: Add your control notification handler code here
	CKnot knot;
	if (knot.GoDlg())
	{
		pListKnot->AddKnot(knot);
		InvalidateKnot(TRUE);
	}
}

void CDemfDlg::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	m_Radio_X5=0;
	m_Radio_XS=m_Radio_X3=m_Radio_X1=m_Radio_XX=-1;
	SetState();
	UpdateData(FALSE);	
}

void CDemfDlg::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	m_Radio_XX=m_Radio_X3=m_Radio_X5=m_Radio_X1=-1;
	m_Radio_XS=0;
	SetState();
	UpdateData(FALSE);
}


void CDemfDlg::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	m_Radio_XS=m_Radio_X3=m_Radio_X5=m_Radio_X1=-1;
	m_Radio_XX=0;
	SetState();
	UpdateData(FALSE);
}
