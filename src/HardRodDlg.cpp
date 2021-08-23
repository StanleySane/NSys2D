// HardRodDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "HardRodDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHardRodDlg dialog

CHardRodDlg::CHardRodDlg(CListKnot *plistkn, 
						 CHardRod *pHrod/*=NULL*/,
						 bool full/*true*/,
						 CWnd* pParent /*=NULL*/)
	: CDialog(CHardRodDlg::IDD, pParent)
{
	m_bFull = full;
	pHardRod=pHrod;
	pListKnot=plistkn;

	//{{AFX_DATA_INIT(CHardRodDlg)
	m_EditJ = _T("1");
	m_EditE = _T("1");
	m_EditM = _T("1");
	m_EditF = _T("1");
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHardRodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHardRodDlg)
	DDX_Control(pDX, IDC_COMBO4, m_ConnectType2);
	DDX_Control(pDX, IDC_COMBO1, m_ConnectType1);
	DDX_Control(pDX, IDC_COMBO3, m_ComboBoxKnot2);
	DDX_Control(pDX, IDC_COMBO2, m_ComboBoxKnot1);
	DDX_Text(pDX, IDC_EDIT1, m_EditJ);
	DDV_MaxChars(pDX, m_EditJ, 100);
	DDX_Text(pDX, IDC_EDIT2, m_EditE);
	DDV_MaxChars(pDX, m_EditE, 100);
	DDX_Text(pDX, IDC_EDIT3, m_EditM);
	DDV_MaxChars(pDX, m_EditM, 100);
	DDX_Text(pDX, IDC_EDIT4, m_EditF);
	DDV_MaxChars(pDX, m_EditF, 100);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHardRodDlg, CDialog)
	//{{AFX_MSG_MAP(CHardRodDlg)
	ON_BN_CLICKED(IDC_BUTNEWKNOT, OnButnewknot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHardRodDlg message handlers

BOOL CHardRodDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	InvalidateKnot(FALSE);

	//жесткое присоединение
	m_ConnectType1.SetCurSel(0);
	m_ConnectType2.SetCurSel(0);

	if ((pHardRod->knot1)&&(pHardRod->knot2))
	{
		m_ConnectType1.SetCurSel(pHardRod->knot1->ConnectType);
		m_ConnectType2.SetCurSel(pHardRod->knot2->ConnectType);
	}

	if (pHardRod)
	{
		int pos1=pListKnot->FindPos(pHardRod->knot1)-1;
		int pos2=pListKnot->FindPos(pHardRod->knot2)-1;

		//CString name1=GetNameKnot(pos1,pRod->knot1->GetName());
		//CString name2=GetNameKnot(pos2,pRod->knot2->GetName());

		m_ComboBoxKnot1.SetCurSel(pos1);
		m_ComboBoxKnot2.SetCurSel(pos2);
//		m_ComboBoxKnot1.SelectString(0,name1);
//		m_ComboBoxKnot2.SelectString(0,name2);

		m_EditJ=pHardRod->GetStrJ();
		m_EditE=pHardRod->GetStrE();
		m_EditM=pHardRod->GetStrM();
		m_EditF=pHardRod->GetStrF();
	}

	GetDlgItem(IDC_COMBO1)->EnableWindow(m_bFull);
	GetDlgItem(IDC_COMBO2)->EnableWindow(m_bFull);
	GetDlgItem(IDC_COMBO3)->EnableWindow(m_bFull);
	GetDlgItem(IDC_COMBO4)->EnableWindow(m_bFull);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CHardRodDlg::VerifyInfo()
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

	CExpression e;
	int ret;
	ret=e.IsNum(m_EditF);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"Выражение для F не число"
			,MB_OK|MB_ICONERROR);
		return FALSE;
	}
	ret=e.IsNum(m_EditJ);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"Выражение для J не число"
			,MB_OK|MB_ICONERROR);
		return FALSE;
	}
	ret=e.IsNum(m_EditE);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"Выражение для E не число"
			,MB_OK|MB_ICONERROR);
		return FALSE;
	}
	ret=e.IsNum(m_EditM);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"Выражение для M не число"
			,MB_OK|MB_ICONERROR);
		return FALSE;
	}
	return TRUE;
}

void CHardRodDlg::InvalidateKnot(BOOL bSave)
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

void CHardRodDlg::OnOK() 
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
		kn1 = pHardRod->knot1;
		kn2 = pHardRod->knot2;
	}

	if (!pHardRod)	pHardRod=new CHardRod(kn1, kn2);

	pHardRod->knot1=kn1;
	pHardRod->knot2=kn2;

	pHardRod->SetF(m_EditF);
	pHardRod->SetJ(m_EditJ);
	pHardRod->SetE(m_EditE);
	pHardRod->SetM(m_EditM);

	pHardRod->knot1->ConnectType=m_ConnectType1.GetCurSel();//m_Type1;
	pHardRod->knot2->ConnectType=m_ConnectType2.GetCurSel();//m_Type2;

//	pRod->knot1->AddElemKnot(pRod->knot2,pRod->type1);
//	pRod->knot2->AddElemKnot(pRod->knot1,pRod->type2);

	CDialog::OnOK();
}

void CHardRodDlg::OnButnewknot() 
{
	// TODO: Add your control notification handler code here
	CKnot knot;
	if( knot.GoDlg() )
	{
		pListKnot->AddKnot( knot );
		InvalidateKnot(TRUE);
	}
}
