// KnotSpectr.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "KnotSpectr.h"
#include "Matr.h"
#include "ProgressDlg.h"
#include "GraphFrm.h"
#include "GraphicView.h"

#include "Sheme.h"
#include "Elem.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKnotSpectr dialog


CKnotSpectr::CKnotSpectr(CSpectrParam *pSpParam, CWnd* pParent /*=NULL*/)
	: CDialog(CKnotSpectr::IDD, pParent)
{
	pSpectrParam=pSpParam;
	FlagView=0;
	
	//{{AFX_DATA_INIT(CKnotSpectr)
	m_TypeSpectr = 0;
	m_TypeInit = 0;
	m_CheckView = FALSE;
	m_Edit14 = _T("");
	m_Edit1 = 0.0;
	m_Edit10 = 0.0;
	m_Edit11 = 0.0;
	m_Edit12 = 0.0;
	m_Edit13 = 0.0;
	m_Edit15 = 0.0;
	m_Edit16 = 0.0;
	m_Edit17 = 0.0;
	m_Edit18 = 0.0;
	m_Edit19 = 0.0;
	m_Edit2 = 0.0;
	m_Edit3 = 0.0;
	m_Edit4 = 0.0;
	m_Edit5 = 0.0;
	m_Edit6 = 0.0;
	m_Edit7 = 0.0;
	m_Edit8 = 0.0;
	m_Edit9 = 0.0;
	//}}AFX_DATA_INIT
}


void CKnotSpectr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKnotSpectr)
	DDX_Radio(pDX, IDC_RADIO1, m_TypeSpectr);
	DDX_Radio(pDX, IDC_RADIO7, m_TypeInit);
	DDX_Check(pDX, IDC_CHECK1, m_CheckView);
	DDX_Text(pDX, IDC_EDIT14, m_Edit14);
	DDV_MaxChars(pDX, m_Edit14, 100);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	DDX_Text(pDX, IDC_EDIT10, m_Edit10);
	DDX_Text(pDX, IDC_EDIT11, m_Edit11);
	DDX_Text(pDX, IDC_EDIT12, m_Edit12);
	DDX_Text(pDX, IDC_EDIT13, m_Edit13);
	DDX_Text(pDX, IDC_EDIT15, m_Edit15);
	DDX_Text(pDX, IDC_EDIT16, m_Edit16);
	DDX_Text(pDX, IDC_EDIT17, m_Edit17);
	DDX_Text(pDX, IDC_EDIT18, m_Edit18);
	DDX_Text(pDX, IDC_EDIT19, m_Edit19);
	DDX_Text(pDX, IDC_EDIT2, m_Edit2);
	DDX_Text(pDX, IDC_EDIT3, m_Edit3);
	DDX_Text(pDX, IDC_EDIT4, m_Edit4);
	DDX_Text(pDX, IDC_EDIT5, m_Edit5);
	DDX_Text(pDX, IDC_EDIT6, m_Edit6);
	DDX_Text(pDX, IDC_EDIT7, m_Edit7);
	DDX_Text(pDX, IDC_EDIT8, m_Edit8);
	DDX_Text(pDX, IDC_EDIT9, m_Edit9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKnotSpectr, CDialog)
	//{{AFX_MSG_MAP(CKnotSpectr)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio7)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKnotSpectr message handlers

BOOL CKnotSpectr::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	/*
	m_Edit1.SetWindowText(pSpectrParam->strEdit[0]);
	m_Edit2.SetWindowText(pSpectrParam->strEdit[1]);
	m_Edit3.SetWindowText(pSpectrParam->strEdit[2]);
	m_Edit4.SetWindowText(pSpectrParam->strEdit[3]);
	m_Edit5.SetWindowText(pSpectrParam->strEdit[4]);
	m_Edit6.SetWindowText(pSpectrParam->strEdit[5]);
	m_Edit7.SetWindowText(pSpectrParam->strEdit[6]);
	m_Edit8.SetWindowText(pSpectrParam->strEdit[7]);
	m_Edit9.SetWindowText(pSpectrParam->strEdit[8]);
	m_Edit10.SetWindowText(pSpectrParam->strEdit[9]);
	m_Edit11.SetWindowText(pSpectrParam->strEdit[10]);
	m_Edit12.SetWindowText(pSpectrParam->strEdit[11]);
	m_Edit13.SetWindowText(pSpectrParam->strEdit[12]);
	m_Edit14.SetWindowText(pSpectrParam->strEdit[13]);
	m_Edit15.SetWindowText(pSpectrParam->strEdit[14]);
	m_Edit16.SetWindowText(pSpectrParam->strEdit[15]);
	m_Edit17.SetWindowText(pSpectrParam->strEdit[16]);
	m_Edit18.SetWindowText(pSpectrParam->strEdit[17]);
	m_Edit19.SetWindowText(pSpectrParam->strEdit[18]);
	*/
	m_Edit1 = pSpectrParam->m_1S;
	m_Edit2 = pSpectrParam->m_1Wc;
	m_Edit3 = pSpectrParam->m_2S;
	m_Edit4 = pSpectrParam->m_2a;
	m_Edit5 = pSpectrParam->m_3S;
	m_Edit6 = pSpectrParam->m_3Wo;
	m_Edit7 = pSpectrParam->m_3a;
	m_Edit8 = pSpectrParam->m_4S;
	m_Edit9 = pSpectrParam->m_4a;
	m_Edit10 = pSpectrParam->m_4b;
	m_Edit11 = pSpectrParam->m_5S;
	m_Edit12 = pSpectrParam->m_5a;
	m_Edit13 = pSpectrParam->m_5b;
	m_Edit14 = pSpectrParam->m_Sw.GetExpr().c_str();
	m_Edit15 = pSpectrParam->m_6Wmin;
	m_Edit16 = pSpectrParam->m_6Wmax;
	m_Edit17 = pSpectrParam->m_Seed;
	m_Edit18 = pSpectrParam->m_Late;
	m_Edit19 = pSpectrParam->m_Wmax;

	m_TypeSpectr = pSpectrParam->TypeSpectr;
	m_TypeInit = pSpectrParam->TypeInit;
	UpdateData(false);
	SetState();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKnotSpectr::SetState()
{
	UpdateData(true);
	/*
	m_Edit1.EnableWindow(false);
	m_Edit2.EnableWindow(false);
	m_Edit3.EnableWindow(false);
	m_Edit4.EnableWindow(false);
	m_Edit5.EnableWindow(false);
	m_Edit6.EnableWindow(false);
	m_Edit7.EnableWindow(false);
	m_Edit8.EnableWindow(false);
	m_Edit9.EnableWindow(false);
	m_Edit10.EnableWindow(false);
	m_Edit11.EnableWindow(false);
	m_Edit12.EnableWindow(false);
	m_Edit13.EnableWindow(false);
	m_Edit14.EnableWindow(false);
	m_Edit15.EnableWindow(false);
	m_Edit16.EnableWindow(false);
	m_Edit17.EnableWindow(false);
	m_Edit19.EnableWindow(false);
	*/
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT10)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT11)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT12)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT13)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT14)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT15)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT16)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT17)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT18)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT19)->EnableWindow(FALSE);

	switch(m_TypeSpectr)
	{
	case 0:
//		m_Edit1.EnableWindow();
//		m_Edit2.EnableWindow(); 
		GetDlgItem(IDC_EDIT1)->EnableWindow();
		GetDlgItem(IDC_EDIT2)->EnableWindow();
		break;
	case 1:
//		m_Edit3.EnableWindow();	
//		m_Edit4.EnableWindow();
//		m_Edit19.EnableWindow();
		GetDlgItem(IDC_EDIT3)->EnableWindow();
		GetDlgItem(IDC_EDIT4)->EnableWindow();
		GetDlgItem(IDC_EDIT19)->EnableWindow();
		break;
	case 2: 
//		m_Edit5.EnableWindow();
//		m_Edit6.EnableWindow(); 
//		m_Edit7.EnableWindow();
//		m_Edit19.EnableWindow();
		GetDlgItem(IDC_EDIT5)->EnableWindow();
		GetDlgItem(IDC_EDIT6)->EnableWindow();
		GetDlgItem(IDC_EDIT7)->EnableWindow();
		GetDlgItem(IDC_EDIT19)->EnableWindow();
		break;
	case 3: 
//		m_Edit8.EnableWindow();
//		m_Edit9.EnableWindow();
//		m_Edit10.EnableWindow(); 
//		m_Edit19.EnableWindow();
		GetDlgItem(IDC_EDIT8)->EnableWindow();
		GetDlgItem(IDC_EDIT9)->EnableWindow();
		GetDlgItem(IDC_EDIT10)->EnableWindow();
		GetDlgItem(IDC_EDIT19)->EnableWindow();
		break;
	case 4:
//		m_Edit11.EnableWindow();
//		m_Edit12.EnableWindow();
//		m_Edit13.EnableWindow();
//		m_Edit19.EnableWindow();
		GetDlgItem(IDC_EDIT11)->EnableWindow();
		GetDlgItem(IDC_EDIT12)->EnableWindow();
		GetDlgItem(IDC_EDIT13)->EnableWindow();
		GetDlgItem(IDC_EDIT19)->EnableWindow();
		break;
	case 5: 
//		m_Edit14.EnableWindow();
//		m_Edit15.EnableWindow();
//		m_Edit16.EnableWindow();
		GetDlgItem(IDC_EDIT14)->EnableWindow();
		GetDlgItem(IDC_EDIT15)->EnableWindow();
		GetDlgItem(IDC_EDIT16)->EnableWindow();
		break;
	}
	if( m_TypeInit == 1 )
		GetDlgItem(IDC_EDIT17)->EnableWindow();
//		m_Edit17.EnableWindow();
	UpdateData(false);
}

void CKnotSpectr::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	SetState();
}

void CKnotSpectr::OnOK() 
{
	// TODO: Add extra validation here
	double p[20];

	if (!VerifyInfo(p)) return;

	/*
	m_Edit1.GetWindowText(pSpectrParam->strEdit[0]);
	m_Edit2.GetWindowText(pSpectrParam->strEdit[1]);
	m_Edit3.GetWindowText(pSpectrParam->strEdit[2]);
	m_Edit4.GetWindowText(pSpectrParam->strEdit[3]);
	m_Edit5.GetWindowText(pSpectrParam->strEdit[4]);
	m_Edit6.GetWindowText(pSpectrParam->strEdit[5]);
	m_Edit7.GetWindowText(pSpectrParam->strEdit[6]);
	m_Edit8.GetWindowText(pSpectrParam->strEdit[7]);
	m_Edit9.GetWindowText(pSpectrParam->strEdit[8]);
	m_Edit10.GetWindowText(pSpectrParam->strEdit[9]);
	m_Edit11.GetWindowText(pSpectrParam->strEdit[10]);
	m_Edit12.GetWindowText(pSpectrParam->strEdit[11]);
	m_Edit13.GetWindowText(pSpectrParam->strEdit[12]);
	m_Edit14.GetWindowText(pSpectrParam->strEdit[13]);
	m_Edit15.GetWindowText(pSpectrParam->strEdit[14]);
	m_Edit16.GetWindowText(pSpectrParam->strEdit[15]);
	m_Edit17.GetWindowText(pSpectrParam->strEdit[16]);
	m_Edit18.GetWindowText(pSpectrParam->strEdit[17]);
	m_Edit19.GetWindowText(pSpectrParam->strEdit[18]);
	*/
	pSpectrParam->m_1S = m_Edit1;
	pSpectrParam->m_1Wc = m_Edit2;
	pSpectrParam->m_2S = m_Edit3;
	pSpectrParam->m_2a = m_Edit4;
	pSpectrParam->m_3S = m_Edit5;
	pSpectrParam->m_3Wo = m_Edit6;
	pSpectrParam->m_3a = m_Edit7;
	pSpectrParam->m_4S = m_Edit8;
	pSpectrParam->m_4a = m_Edit9;
	pSpectrParam->m_4b = m_Edit10;
	pSpectrParam->m_5S = m_Edit11;
	pSpectrParam->m_5a = m_Edit12;
	pSpectrParam->m_5b = m_Edit13;
	ShemeExprErr res = pSpectrParam->m_Sw.Reset( m_Edit14 );
	ASSERT( res == SEE_NOERR );
	pSpectrParam->m_6Wmin = m_Edit15;
	pSpectrParam->m_6Wmax = m_Edit16;
	pSpectrParam->m_Seed = m_Edit17;
	pSpectrParam->m_Late = m_Edit18;
	pSpectrParam->m_Wmax = m_Edit19;

	pSpectrParam->TypeSpectr = m_TypeSpectr;
	pSpectrParam->TypeInit = m_TypeInit;
//	for (int i=0;i<19;i++)	pSpectrParam->param[i]=p[i];
	
	//Рисуем график если надо
	if (m_CheckView)
	{
		int s=500;
		double stepW = pSpectrParam->GetMaxW()/s;

		CMatr Dat(2,s);
		CProgressDlg *pDlg=new CProgressDlg(100,_T("Вычисление S(w)"));
		BOOL FlagExit=false;
		CString tmpstr;

		string msg;
		for (int i=0;i<s;i++)
		{
			double tmpx = i*stepW;
			if( pSpectrParam->m_pSheme && pSpectrParam->m_pSheme->m_bRichCalc )
			{
				tmpstr.Format("Вычисление точки %.16g", tmpx );
				pDlg->SetDetails(tmpstr);
			}
			Dat(0,i) = tmpx;
			Dat(1,i) = pSpectrParam->GetSpectr( tmpx, &msg );
			if( pSpectrParam->m_pSheme && pSpectrParam->m_pSheme->m_bValidateExpr && !msg.empty() )
			{
				AfxMessageBox( CString("Ошибка вычисления выражения: ") + msg.c_str() );
				break;
			}

			//Обработка сообщений
			MSG msg;
			FlagExit=false;
			while (PeekMessage(&msg, pDlg->m_Button.m_hWnd, WM_KEYDOWN, WM_LBUTTONUP, PM_REMOVE))   // Until WM_QUIT message
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
   				if ((msg.message==WM_KEYDOWN)||(msg.message==WM_LBUTTONUP))
				{
					switch (msg.wParam)
					{
					case 0:
					case 13:
					case 27:
					case 32:	FlagExit=true; break;
					}
				}
			}
			while (PeekMessage(&msg, pDlg->m_hWnd, 0, 0x0ffff, PM_REMOVE))   // Until WM_QUIT message
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			if (FlagExit)
			{
				break;
			}
			pDlg->SetPos(int(100.0*i/s));
		}
		delete pDlg;
		
		CNSys2DApp* pApp=(CNSys2DApp*)AfxGetApp();
		POSITION pos = pApp->GetFirstDocTemplatePosition();
		pApp->GetNextDocTemplate(pos);
		CDocTemplate *pTemplate = pApp->GetNextDocTemplate(pos);
		CDocument *pDoc=((CMDIFrameWnd*)AfxGetMainWnd())->MDIGetActive()->GetActiveDocument();
		CGraphFrame *pNewFrame	= (CGraphFrame*)(pTemplate->CreateNewFrame(pDoc, NULL));
		ASSERT(pNewFrame!=NULL);
		pTemplate->InitialUpdateFrame(pNewFrame, pDoc);
		CGraphicView *pGraphView = (CGraphicView*)pNewFrame->GetActiveView();
		ASSERT (pGraphView != NULL);
		pGraphView->pKnot=0;
		//Установка переменной по горизонтали
		CString str=_T("Функция спектральной плотности");
		pGraphView->str_title=str;
		//Начальная установка границ изображения
		pGraphView->SetMaxMin();
		pNewFrame->SetWindowText(str);
		pGraphView->Dat.ReSize( 2, Dat.SizeX );
		pGraphView->Dat = Dat;
	}

	CDialog::OnOK();
}

BOOL CKnotSpectr::VerifyInfo(double *p)
{
	UpdateData();
	
	if( m_TypeSpectr == 5 )
	{
		CString mes;
		ASSERT(pSpectrParam->m_pSheme);
		if( !pSpectrParam->m_pSheme->m_VarsTable.IsValidExpr( m_Edit14, mes ) )
		{
			mes = _T("Ошибка в выражении S(w):\n") + mes;
			AfxMessageBox( mes );
			return FALSE;
		}
	}

	return TRUE;
}

void CKnotSpectr::OnRadio7() 
{
	// TODO: Add your control notification handler code here
	SetState();
}
