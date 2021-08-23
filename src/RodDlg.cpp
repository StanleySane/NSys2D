// RodDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "RodDlg.h"

#include "KnotDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRodDlg dialog


CRodDlg::CRodDlg(CListKnot *plistkn,CRod *prod/*=NULL*/,
				 CWnd* pParent /*=NULL*/)
	: CDialog(CRodDlg::IDD, pParent)
{
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

	//������� �������������
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

		//CString name1=GetNameKnot(pos1,pRod->knot1->GetName());
		//CString name2=GetNameKnot(pos2,pRod->knot2->GetName());

		m_ComboBoxKnot1.SetCurSel(pos1);
		m_ComboBoxKnot2.SetCurSel(pos2);
//		m_ComboBoxKnot1.SelectString(0,name1);
//		m_ComboBoxKnot2.SelectString(0,name2);

		m_EditJx=pRod->GetStrJx();
		m_EditE=pRod->GetStrE();
		m_EditM=pRod->GetStrM();
		m_EditF=pRod->GetStrF();
	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CRodDlg::VerifyInfo()
{
	UpdateData();
	
	CKnot *kn1=pListKnot->GetKnotPos(m_ComboBoxKnot1.GetCurSel());
	CKnot *kn2=pListKnot->GetKnotPos(m_ComboBoxKnot2.GetCurSel());

	if (kn1==kn2) 
	{
		MessageBox("������ ��� ���������� ����","������!"
			,MB_OK|MB_ICONERROR);
		return FALSE;
	}

	CExpression e;
	int ret;
	ret=e.IsNum(m_EditF);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"��������� ��� F �� �����"
			,MB_OK|MB_ICONERROR);
		return FALSE;
	}
	ret=e.IsNum(m_EditJx);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"��������� ��� Jx �� �����"
			,MB_OK|MB_ICONERROR);
		return FALSE;
	}
	ret=e.IsNum(m_EditE);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"��������� ��� E �� �����"
			,MB_OK|MB_ICONERROR);
		return FALSE;
	}
	ret=e.IsNum(m_EditM);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"��������� ��� M �� �����"
			,MB_OK|MB_ICONERROR);
		return FALSE;
	}
	return TRUE;
}

void CRodDlg::InvalidateKnot(BOOL bSave)
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

void CRodDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (!VerifyInfo()) return;

//	if (pRod->knot1) pRod->knot1->DelElemKnot(pRod->knot2);
//	if (pRod->knot2) pRod->knot2->DelElemKnot(pRod->knot1);

	CKnot *kn1=pListKnot->GetKnotPos(m_ComboBoxKnot1.GetCurSel());
	CKnot *kn2=pListKnot->GetKnotPos(m_ComboBoxKnot2.GetCurSel());

	if (!pRod)
		pRod=new CRod(kn1, kn2);

	pRod->knot1=kn1;
	pRod->knot2=kn2;

	pRod->SetF(m_EditF);
	pRod->SetJx(m_EditJx);
	pRod->SetE(m_EditE);
	pRod->SetM(m_EditM);

	pRod->knot1->ConnectType=m_ConnectType1.GetCurSel();//m_Type1;
	pRod->knot2->ConnectType=m_ConnectType2.GetCurSel();//m_Type2;

//	pRod->knot1->AddElemKnot(pRod->knot2,pRod->type1);
//	pRod->knot2->AddElemKnot(pRod->knot1,pRod->type2);

	CDialog::OnOK();
}