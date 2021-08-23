// KnotDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "KnotDlg.h"
#include "Expression.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKnotDlg dialog


CKnotDlg::CKnotDlg(CKnot *pKn/*=NULL*/, CWnd* pParent /*=NULL*/)
	: CDialog(CKnotDlg::IDD, pParent)
{
	pKnot=pKn;
	//{{AFX_DATA_INIT(CKnotDlg)
	m_EditX = _T("");
	m_EditY = _T("");
	//}}AFX_DATA_INIT
}


void CKnotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKnotDlg)
	DDX_Control(pDX, IDC_COMBO1, m_FixedType);
	DDX_Text(pDX, IDC_EDIT1, m_EditX);
	DDV_MaxChars(pDX, m_EditX, 100);
	DDX_Text(pDX, IDC_EDIT2, m_EditY);
	DDV_MaxChars(pDX, m_EditY, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKnotDlg, CDialog)
	//{{AFX_MSG_MAP(CKnotDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKnotDlg message handlers

BOOL CKnotDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
//*************************************
/*	TC_ITEM struc;
	struc.mask=TCIF_TEXT;
	struc.pszText="Нач. условия";
	struc.cchTextMax=13;
	struc.iImage=-1;
	struc.lParam=0;
	m_TabCtrl.InsertItem(0,&struc);
	struc.pszText="Координаты";
	m_TabCtrl.InsertItem(0,&struc);
	m_TabCtrl.SetCurSel(0);*/
//**************************************
	m_FixedType.ResetContent();
	m_FixedType.AddString("");
	m_FixedType.AddString("");
	m_FixedType.AddString("");
	m_FixedType.AddString("");
	m_FixedType.AddString("");
	m_FixedType.AddString("");
	m_FixedType.SetCurSel(pKnot->FixedType);

	m_EditX=pKnot->GetStrX();
	m_EditY=pKnot->GetStrY();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKnotDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	
	CExpression e;
	int ret;
	if (ret=e.IsNum(m_EditX))
	{
		CString mes;
		mes.LoadString(ret);
		
		MessageBox(mes,"Координата X",
			 MB_OK|MB_ICONERROR );
		
		return;
	}

	if (ret=e.IsNum(m_EditY))
	{
		CString mes;
		mes.LoadString(ret);
		
		MessageBox(mes,"Координата Y",
			  MB_OK|MB_ICONERROR );
		
		return;
	}
	
	pKnot->SetCoord(m_EditX,m_EditY);
	pKnot->FixedType=m_FixedType.GetCurSel();

	CDialog::OnOK();
}

