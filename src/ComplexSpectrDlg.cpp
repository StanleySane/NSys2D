// ComplexSpectrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "ComplexSpectrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComplexSpectrDlg dialog


CComplexSpectrDlg::CComplexSpectrDlg(CListKnot *_plistknot, 
									 CListSpectr *_plist, 
									 CKnot *_pkn,
									 int _nFree,
									 CWnd* pParent /*=NULL*/)
	: CDialog(CComplexSpectrDlg::IDD, pParent)
{
	pListKnot=_plistknot;
	pListSpectr=_plist;
	pkn=_pkn;
	nFree=_nFree;

	//{{AFX_DATA_INIT(CComplexSpectrDlg)
	//}}AFX_DATA_INIT
}


void CComplexSpectrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComplexSpectrDlg)
	DDX_Control(pDX, IDC_BUTTON2, m_But2);
	DDX_Control(pDX, IDC_BUTTON3, m_But3);
	DDX_Control(pDX, IDC_BUTTON1, m_But1);
	DDX_Control(pDX, IDC_COMBO2, m_ComboFree);
	DDX_Control(pDX, IDC_COMBO1, m_ComboKnot);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_Grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComplexSpectrDlg, CDialog)
	//{{AFX_MSG_MAP(CComplexSpectrDlg)
	ON_BN_CLICKED(IDC_BUTTON2, OnAddElem)
	ON_BN_CLICKED(IDC_BUTTON1, OnDelElem)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComplexSpectrDlg message handlers

BOOL CComplexSpectrDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetKnot();
	SetGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CComplexSpectrDlg::OnAddElem() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CComplexSpectr CS;
	CS.pKn1=pkn;
	CS.Free1=nFree;
	CS.pKn2=GetKnot(m_ComboKnot.GetCurSel());
	CS.Free2=m_ComboFree.GetCurSel();
	pListSpectr->AddSpectr(CS);
	SetGrid();
}

int CComplexSpectrDlg::SetGrid()
{
	//Подсчет количества узлов
	int count=0;
	POSITION pos=pListSpectr->GetHeadPosition();
	while (pos)
	{
		CComplexSpectr *pCS=(CComplexSpectr*)pListSpectr->GetNext(pos);
		if ( ( (pCS->pKn1==pkn)&&(pCS->Free1==nFree) )
		   ||( (pCS->pKn2==pkn)&&(pCS->Free2==nFree) ) ) count++;
	}
	m_Grid.Clear();
	m_Grid.SetCols(2);
	m_Grid.SetRows(count+1);

	CString XYA[3]={_T("X"),_T("Y"),_T("A")};

	m_Grid.SetTextMatrix(0,0,_T("Узел"));
	m_Grid.SetColWidth(0,2000);//1400
	m_Grid.SetTextMatrix(0,1,_T("XYA"));
	m_Grid.SetColWidth(1,400);
//	m_Grid.SetTextMatrix(0,2,_T("Спектр.плотность"));
//	m_Grid.SetColWidth(2,2220);

	//Заполнение сетки
	count=1;
	pos=pListSpectr->GetHeadPosition();
	while (pos)
	{
		CComplexSpectr *pCS=(CComplexSpectr*)pListSpectr->GetNext(pos);
		if ( (pCS->pKn1==pkn)&&(pCS->Free1==nFree) ) 
		{
			m_Grid.SetTextMatrix(count,0,pCS->pKn2->GetName(1));
			m_Grid.SetTextMatrix(count,1,XYA[pCS->Free2]);
			//m_Grid.SetTextMatrix(count,2,pCS->Sp.GetString());
			count++;
		}
		if ( (pCS->pKn2==pkn)&&(pCS->Free2==nFree) ) 
		{
			m_Grid.SetTextMatrix(count,0,pCS->pKn1->GetName(1));
			m_Grid.SetTextMatrix(count,1,XYA[pCS->Free1]);
			//m_Grid.SetTextMatrix(count,2,pCS->Sp.GetString());
			count++;
		}
	}
	SetEnable();
//	UpdateData(false);

	return count;
}

int CComplexSpectrDlg::SetKnot()
{
	POSITION pos=pListKnot->GetHeadPosition();
	while (pos)
	{
		CKnot *pknot=(CKnot*)pListKnot->GetNext(pos);
		m_ComboKnot.AddString(pknot->GetName(1));
	}
	return 0;
}

CKnot* CComplexSpectrDlg::GetKnot(int index)
{
	int cnt=0;
	POSITION pos=pListKnot->GetHeadPosition();
	while (pos)
	{
		CKnot *pknot=(CKnot*)pListKnot->GetNext(pos);
		if (cnt==index) return pknot;
		cnt++;
	}
	return 0;
}

void CComplexSpectrDlg::OnDelElem() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	int rows=m_Grid.GetRowSel();
	
	int count=0;
	POSITION pos=pListSpectr->GetHeadPosition();
	while (pos)
	{
		CComplexSpectr *pCS=(CComplexSpectr*)pListSpectr->GetNext(pos);
		if ( ( (pCS->pKn1==pkn)&&(pCS->Free1==nFree) )
		   ||( (pCS->pKn2==pkn)&&(pCS->Free2==nFree) ) ) count++;
		if (count==rows) 
		{
			pListSpectr->DelSpectr(*pCS);
			SetGrid();
			SetEnable();
			return;
		}
	}
}

BEGIN_EVENTSINK_MAP(CComplexSpectrDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CComplexSpectrDlg)
	ON_EVENT(CComplexSpectrDlg, IDC_MSFLEXGRID1, 69 /* SelChange */, OnSelChangeMsflexgrid1, VTS_NONE)
	ON_EVENT(CComplexSpectrDlg, IDC_MSFLEXGRID1, -600 /* Click */, OnClickMsflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CComplexSpectrDlg::OnSelChangeMsflexgrid1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	int rows=m_Grid.GetRowSel();
	CKnot *pknottmp;
	int count=0;
	CString strtmp;
	int Freetmp;
	BOOL bChange=false;

	POSITION pos=pListSpectr->GetHeadPosition();
	while (pos)
	{
		CComplexSpectr *pCS=(CComplexSpectr*)pListSpectr->GetNext(pos);
		if ( ( (pCS->pKn1==pkn)&&(pCS->Free1==nFree) )
		   ||( (pCS->pKn2==pkn)&&(pCS->Free2==nFree) ) ) count++;
		if (count==rows) 
		{
			if ( (pCS->pKn1==pkn)&&(pCS->Free1==nFree) ) 
			{ 
				pknottmp=pCS->pKn2; 
				Freetmp=pCS->Free2; 
			}
			if ( (pCS->pKn2==pkn)&&(pCS->Free2==nFree) ) 
			{ 
				pknottmp=pCS->pKn1; 
				Freetmp=pCS->Free1; 
			}
			bChange=true;
			break;
		}
	}
	if (!bChange) return;
	count=0;
	pos=pListKnot->GetHeadPosition();
	while (pos)
	{
		CKnot *pknot=(CKnot*)pListKnot->GetNext(pos);
		if (pknot==pknottmp) break;
		count++;
	}
	m_ComboKnot.SetCurSel(count);

	m_ComboFree.SetCurSel(Freetmp);
	UpdateData(false);
}

void CComplexSpectrDlg::OnClickMsflexgrid1() 
{
	// TODO: Add your control notification handler code here
	OnSelChangeMsflexgrid1();
}

void CComplexSpectrDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	int rows=m_Grid.GetRowSel();
	int count=0;

	POSITION pos=pListSpectr->GetHeadPosition();
	while (pos)
	{
		CComplexSpectr *pCS=(CComplexSpectr*)pListSpectr->GetNext(pos);
		if ( ( (pCS->pKn1==pkn)&&(pCS->Free1==nFree) )
		   ||( (pCS->pKn2==pkn)&&(pCS->Free2==nFree) ) ) count++;
		if (count==rows) 
		{
			pCS->Sp.GoDlg();
			break;
		}
	}
}

void CComplexSpectrDlg::SetEnable()
{
	BOOL Enable=false;

	POSITION pos=pListSpectr->GetHeadPosition();
	while (pos)
	{
		CComplexSpectr *pCS=(CComplexSpectr*)pListSpectr->GetNext(pos);
		if ( ( (pCS->pKn1==pkn)&&(pCS->Free1==nFree) )
		   ||( (pCS->pKn2==pkn)&&(pCS->Free2==nFree) ) ) 
			Enable=true;
	}
	m_But1.EnableWindow(Enable);
	m_But3.EnableWindow(Enable);

	m_But2.EnableWindow(((m_ComboKnot.GetCurSel()>=0)&&(m_ComboFree.GetCurSel()>=0)));

	UpdateData(false);
}

void CComplexSpectrDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	SetEnable();
}
