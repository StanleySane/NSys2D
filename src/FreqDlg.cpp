// FreqDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "FreqDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFreqDlg dialog


CFreqDlg::CFreqDlg(CListKnot *plistkn, CFreqParam *param, CWnd* pParent /*=NULL*/)
	: CDialog(CFreqDlg::IDD, pParent)
{
	pkn1=pkn2=0;
	pParam=param;
	pListKnot=plistkn;
	if (!pParam->pKnot1) pParam->pKnot1=pListKnot->GetKnotPos(0);
	if (!pParam->pKnot2) pParam->pKnot2=pListKnot->GetKnotPos(0);

	//{{AFX_DATA_INIT(CFreqDlg)
	m_w0 = _T("");
	m_w1 = _T("");
	m_dw = _T("");
	m_LogCoord = FALSE;
	m_TypeCharact = -1;
	m_Free1 = -1;
	m_Free2 = -1;
	m_Derive = -1;
	m_Force = -1;
	//}}AFX_DATA_INIT
}


void CFreqDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFreqDlg)
	DDX_Control(pDX, IDC_COMBO2, m_ComboBoxKnot2);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBoxKnot1);
	DDX_Text(pDX, IDC_EDIT1, m_w0);
	DDX_Text(pDX, IDC_EDIT2, m_w1);
	DDX_Text(pDX, IDC_EDIT3, m_dw);
	DDX_Check(pDX, IDC_CHECK1, m_LogCoord);
	DDX_Radio(pDX, IDC_RADIO1, m_TypeCharact);
	DDX_Radio(pDX, IDC_RADIO4, m_Free1);
	DDX_Radio(pDX, IDC_RADIO7, m_Free2);
	DDX_Radio(pDX, IDC_RADIO10, m_Derive);
	DDX_Radio(pDX, IDC_RADIO13, m_Force);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFreqDlg, CDialog)
	//{{AFX_MSG_MAP(CFreqDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFreqDlg message handlers

BOOL CFreqDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InvalidateKnot(false);

	if (!pkn1) pkn1=pParam->pKnot1;
	if (!pkn2) pkn2=pParam->pKnot2;

	if (pkn1)
	{
		int pos1=pListKnot->FindPos(pkn1)-1;
		m_ComboBoxKnot1.SetCurSel(pos1);
	}
	if (pkn2)
	{
		int pos2=pListKnot->FindPos(pkn2)-1;
		m_ComboBoxKnot2.SetCurSel(pos2);
	}

	m_TypeCharact=pParam->TypeCharact;
	m_Free1=pParam->typeFree1;
	m_Free2=pParam->typeFree2;
	m_Derive=pParam->Derive;
	m_w0=pParam->strwBeg;
	m_w1=pParam->strwEnd;
	m_dw=pParam->strwStep;
	m_LogCoord=pParam->LogCoord;
	m_Force=pParam->typeForce;

	UpdateData(false);
	
	return true;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFreqDlg::InvalidateKnot(BOOL bSave)
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

void CFreqDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (!VerifyInfo()) return;

	pParam->strwBeg=m_w0;
	pParam->strwEnd=m_w1;
	pParam->strwStep=m_dw;
	pParam->Derive=m_Derive;
	pParam->TypeCharact=m_TypeCharact;
	pParam->LogCoord=m_LogCoord;
	pParam->nFree1=Free1;
	pParam->nFree2=Free2;
	pParam->typeFree1=m_Free1;
	pParam->typeFree2=m_Free2;
	pParam->typeForce=m_Force;
	pParam->pKnot1=pListKnot->GetKnotPos(m_ComboBoxKnot1.GetCurSel());
	pParam->pKnot2=pListKnot->GetKnotPos(m_ComboBoxKnot2.GetCurSel());
	
	CDialog::OnOK();
}

BOOL CFreqDlg::VerifyInfo()
{
	UpdateData();
	
	CKnot *kn1=pListKnot->GetKnotPos(m_ComboBoxKnot1.GetCurSel());
	CKnot *kn2=pListKnot->GetKnotPos(m_ComboBoxKnot2.GetCurSel());

	switch (m_Free1)
	{
	case 0:	Free1=kn1->nXRez;		break;
	case 1:	Free1=kn1->nYRez;		break;
	case 2:	Free1=kn1->nARez[0];	break;
	}
	switch (m_Free2)
	{
	case 0:	Free2=kn2->nXRez;		break;
	case 1:	Free2=kn2->nYRez;		break;
	case 2:	Free2=kn2->nARez[0];	break;
	}

	if (Free1<0)
	{
		MessageBox("1-я степень свободы неподвижна","Ошибка!",MB_OK|MB_ICONERROR);
		return false;
	}
	if (Free2<0)
	{
		MessageBox("2-я степень свободы неподвижна","Ошибка!",MB_OK|MB_ICONERROR);
		return false;
	}

	CExpression e;
	int ret;
	CString str1;

	ret=e.IsNum(m_w0);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"Начальная частота не число"
			,MB_OK|MB_ICONERROR);
		return false;
	}
	ret=e.IsNum(m_w1);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"Конечная частота не число"
			,MB_OK|MB_ICONERROR);
		return false;
	}
	ret=e.IsNum(m_dw);
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
