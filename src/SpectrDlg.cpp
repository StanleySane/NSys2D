// SpectrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "SpectrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpectrDlg dialog


CSpectrDlg::CSpectrDlg(CFreqParam *pparam, CListKnot *plistknot, CKnot *pknot, CWnd* pParent /*=NULL*/)
	: CDialog(CSpectrDlg::IDD, pParent)
{
	pListKnot=plistknot;
	pKnot=pknot;
	pParamOut=pparam;
	
	//{{AFX_DATA_INIT(CSpectrDlg)
	m_Free = 0;
	m_W0 = _T("");
	m_W1 = _T("");
	m_dW = _T("");
	//}}AFX_DATA_INIT
}


void CSpectrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpectrDlg)
	DDX_Control(pDX, IDC_COMBO1, m_ComboKnot);
	DDX_CBIndex(pDX, IDC_COMBO2, m_Free);
	DDX_Text(pDX, IDC_EDIT1, m_W0);
	DDX_Text(pDX, IDC_EDIT2, m_W1);
	DDX_Text(pDX, IDC_EDIT3, m_dW);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpectrDlg, CDialog)
	//{{AFX_MSG_MAP(CSpectrDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpectrDlg message handlers

BOOL CSpectrDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InvalidateKnot();
	m_W0=pParamOut->strwBeg;
	m_W1=pParamOut->strwEnd;
	m_dW=pParamOut->strwStep;

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSpectrDlg::InvalidateKnot()
{
	m_ComboKnot.ResetContent();

	int count=0, NumSel=0;
	POSITION pos=pListKnot->GetHeadPosition();
	while (pos)
	{
		CKnot *pkn=pListKnot->GetNext(pos);
		if (pKnot==pkn) NumSel=count;
		count++;
//		count=pListKnot->FindPos(kn);
		CString name=pkn->GetName(count);
		m_ComboKnot.AddString(name);
	}
	if (m_ComboKnot.GetCount())
		m_ComboKnot.SetCurSel(NumSel);
}

void CSpectrDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (!VerifyInfo()) return;

	int count=0;
	int NumSel=m_ComboKnot.GetCurSel();

	POSITION pos=pListKnot->GetHeadPosition();
	while (pos)
	{
		CKnot *pkn=pListKnot->GetNext(pos);
		if (count==NumSel) 
		{
			pParamOut->pKnot1=pkn;
			pParamOut->typeFree1=m_Free;
			break;
		}
		count++;
	}
	if (m_Free==0) pParamOut->nFree1=pParamOut->pKnot1->nXRez;
	if (m_Free==1) pParamOut->nFree1=pParamOut->pKnot1->nYRez;
	if (m_Free==2) pParamOut->nFree1=pParamOut->pKnot1->nARez[0];

	pParamOut->strwBeg=m_W0;
	pParamOut->strwEnd=m_W1;
	pParamOut->strwStep=m_dW;
	
	CDialog::OnOK();
}

BOOL CSpectrDlg::VerifyInfo()
{
	UpdateData();

	CExpression e;
	int ret;
	CString str1;

	ret=e.IsNum(m_W0);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"Начальная частота не число"
			,MB_OK|MB_ICONERROR);
		return false;
	}
	ret=e.IsNum(m_W1);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"Конечная частота не число"
			,MB_OK|MB_ICONERROR);
		return false;
	}
	ret=e.IsNum(m_dW);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"Шаг частоты не число"
			,MB_OK|MB_ICONERROR);
		return false;
	}
	return true;
}
