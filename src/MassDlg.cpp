// MassDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "MassDlg.h"

#include "Sheme.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMassDlg dialog


CMassDlg::CMassDlg(CListKnot *plistkn,
				   CMass *pmass/*=NULL*/,
				   bool full/*true*/,
				   CWnd* pParent /*=NULL*/)
	: CDialog(CMassDlg::IDD, pParent)
{
	m_bFull = full;
	pListKnot=plistkn;
	pMass=pmass;
	//{{AFX_DATA_INIT(CMassDlg)
	m_EditM = _T("");
	m_EditJp = _T("");
	//}}AFX_DATA_INIT
}


void CMassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMassDlg)
	DDX_Control(pDX, IDC_COMBO1, m_ComboBoxKnot);
	DDX_Text(pDX, IDC_EDIT1, m_EditM);
	DDV_MaxChars(pDX, m_EditM, 100);
	DDX_Text(pDX, IDC_EDIT2, m_EditJp);
	DDV_MaxChars(pDX, m_EditJp, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMassDlg, CDialog)
	//{{AFX_MSG_MAP(CMassDlg)
	ON_BN_CLICKED(IDC_BUTNEWKNOT, OnButnewknot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMassDlg message handlers

BOOL CMassDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InvalidateKnot(FALSE);

	if (pMass)
	{
		int pos=pListKnot->FindPos(pMass->knot1)-1;

		m_ComboBoxKnot.SetCurSel(pos);

		m_EditM = pMass->m_M.GetExpr().c_str();
		m_EditJp = pMass->m_Jp.GetExpr().c_str();
	}

	GetDlgItem(IDC_COMBO1)->EnableWindow(m_bFull);
	GetDlgItem(IDC_BUTNEWKNOT)->EnableWindow(m_bFull);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMassDlg::InvalidateKnot(BOOL bSave)
{
	if( !m_bFull )	return;
	int pos1=0;
	
	if (bSave)
		pos1=m_ComboBoxKnot.GetCurSel();

	m_ComboBoxKnot.ResetContent();

	int count=0;
	POSITION pos=pListKnot->GetHeadPosition();
	while (pos)
	{
		CKnot *kn=pListKnot->GetNext(pos);
		count++;
//		count=pListKnot->FindPos(kn);
		CString name=kn->GetName(count);
		m_ComboBoxKnot.AddString(name);
	}

	if (m_ComboBoxKnot.GetCount())
		m_ComboBoxKnot.SetCurSel(0);
	if (bSave)
		m_ComboBoxKnot.SetCurSel(pos1);
}

void CMassDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (!VerifyInfo()) return;

	CKnot *kn;
	if( m_bFull )
	{
		kn = pListKnot->GetKnotPos(m_ComboBoxKnot.GetCurSel());
	}
	else
	{
		kn = pMass->knot1;
	}

	if (!pMass)
		pMass = new CMass(kn);

	pMass->knot1 = kn;
	pMass->knot2 = kn;

	bool res = pMass->SetMassM(m_EditM);
	ASSERT( res == true );
	res = pMass->SetMassJp(m_EditJp);
	ASSERT( res == true );

	CDialog::OnOK();
}

BOOL CMassDlg::VerifyInfo()
{
	UpdateData();
	
	if( m_bFull )
	{
		if (m_ComboBoxKnot.GetCurSel()==CB_ERR) 
		{
			MessageBox("Не выбран узел","Ошибка!"
				,MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}

	CString mes;
	ASSERT(pMass->m_pSheme);
	if( !pMass->m_pSheme->m_VarsTable.IsValidExpr( m_EditM, mes ) )
	{
		mes = _T("Ошибка в выражении m:\n") + mes;
		AfxMessageBox( mes );
		return FALSE;
	}
	if( !pMass->m_pSheme->m_VarsTable.IsValidExpr( m_EditJp, mes ) )
	{
		mes = _T("Ошибка в выражении Jp:\n") + mes;
		AfxMessageBox( mes );
		return FALSE;
	}
	return TRUE;
}

void CMassDlg::OnButnewknot() 
{
	// TODO: Add your control notification handler code here
	CKnot knot;
	if (knot.GoDlg())
	{
		pListKnot->AddKnot(knot);
		InvalidateKnot(TRUE);
	}
}
