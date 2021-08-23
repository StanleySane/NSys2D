// KnotSpectr.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "KnotSpectr.h"
#include "Expression.h"
#include "Matr.h"
#include "ProgressDlg.h"
#include "GraphFrm.h"
#include "GraphicView.h"

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
	//}}AFX_DATA_INIT
}


void CKnotSpectr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKnotSpectr)
	DDX_Control(pDX, IDC_EDIT19, m_Edit19);
	DDX_Control(pDX, IDC_EDIT18, m_Edit18);
	DDX_Control(pDX, IDC_EDIT17, m_Edit17);
	DDX_Control(pDX, IDC_EDIT16, m_Edit16);
	DDX_Control(pDX, IDC_EDIT15, m_Edit15);
	DDX_Control(pDX, IDC_EDIT14, m_Edit14);
	DDX_Control(pDX, IDC_EDIT13, m_Edit13);
	DDX_Control(pDX, IDC_EDIT12, m_Edit12);
	DDX_Control(pDX, IDC_EDIT11, m_Edit11);
	DDX_Control(pDX, IDC_EDIT10, m_Edit10);
	DDX_Control(pDX, IDC_EDIT9, m_Edit9);
	DDX_Control(pDX, IDC_EDIT8, m_Edit8);
	DDX_Control(pDX, IDC_EDIT7, m_Edit7);
	DDX_Control(pDX, IDC_EDIT6, m_Edit6);
	DDX_Control(pDX, IDC_EDIT5, m_Edit5);
	DDX_Control(pDX, IDC_EDIT4, m_Edit4);
	DDX_Control(pDX, IDC_EDIT3, m_Edit3);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Radio(pDX, IDC_RADIO1, m_TypeSpectr);
	DDX_Radio(pDX, IDC_RADIO7, m_TypeInit);
	DDX_Check(pDX, IDC_CHECK1, m_CheckView);
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
	m_TypeSpectr=pSpectrParam->TypeSpectr;
	m_TypeInit=pSpectrParam->TypeInit;
	UpdateData(false);
	SetState();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKnotSpectr::SetState()
{
	UpdateData(true);
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

	switch(m_TypeSpectr)
	{
	case 0: m_Edit1.EnableWindow();	m_Edit2.EnableWindow(); break;
	case 1: m_Edit3.EnableWindow();	m_Edit4.EnableWindow(); m_Edit19.EnableWindow(); break;
	case 2: m_Edit5.EnableWindow();	m_Edit6.EnableWindow(); m_Edit7.EnableWindow(); m_Edit19.EnableWindow();break;
	case 3: m_Edit8.EnableWindow();	m_Edit9.EnableWindow(); m_Edit10.EnableWindow(); m_Edit19.EnableWindow();break;
	case 4: m_Edit11.EnableWindow();m_Edit12.EnableWindow();m_Edit13.EnableWindow(); m_Edit19.EnableWindow();break;
	case 5: m_Edit14.EnableWindow();m_Edit15.EnableWindow();m_Edit16.EnableWindow();break;
	}
	if (m_TypeInit==1) m_Edit17.EnableWindow();
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
	pSpectrParam->TypeSpectr=m_TypeSpectr;
	pSpectrParam->TypeInit=m_TypeInit;
	for (int i=0;i<19;i++)
		pSpectrParam->param[i]=p[i];
	
	//Рисуем график если надо
	if (m_CheckView)
	{
		int s=500;
		double stepW=pSpectrParam->GetMaxW()/s;

		CMatr Dat(2,s);
		CProgressDlg *pDlg=new CProgressDlg(100,_T("Вычисление S(w)"));
		BOOL FlagExit=false;

		for (int i=0;i<s;i++)
		{
			Dat[0][i]=i*stepW;
			Dat[1][i]=pSpectrParam->GetSpectr(i*stepW);

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
		pGraphView->Dat.ReSize(2,Dat.SizeX);
		pGraphView->Dat=Dat;
	}

	CDialog::OnOK();
}

BOOL CKnotSpectr::VerifyInfo(double *p)
{
	UpdateData();
	
	CExpression e;
	int ret;
	CString str;

	switch(m_TypeSpectr)
	{
	case 0:
		{
			m_Edit1.GetWindowText(str);
			ret=e.IsNum(str,&p[0]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для s=",MB_OK|MB_ICONERROR);
				return false;
			}
			m_Edit2.GetWindowText(str);
			ret=e.IsNum(str,&p[1]);
			if ((ret)||(p[1]<=0))
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для Wc=",MB_OK|MB_ICONERROR);
				return false;
			}
			break;
		}
	case 1:
		{
			m_Edit3.GetWindowText(str);
			ret=e.IsNum(str,&p[2]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для s=",MB_OK|MB_ICONERROR);
				return false;
			}
			m_Edit4.GetWindowText(str);
			ret=e.IsNum(str,&p[3]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для a=",MB_OK|MB_ICONERROR);
				return false;
			}
			m_Edit19.GetWindowText(str);
			ret=e.IsNum(str,&p[18]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для Wmax=",MB_OK|MB_ICONERROR);
				return false;
			}
			break;
		}
	case 2:
		{
			m_Edit5.GetWindowText(str);
			ret=e.IsNum(str,&p[4]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для s=",MB_OK|MB_ICONERROR);
				return false;
			}
			m_Edit6.GetWindowText(str);
			ret=e.IsNum(str,&p[5]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для Wo=",MB_OK|MB_ICONERROR);
				return false;
			}
			m_Edit7.GetWindowText(str);
			ret=e.IsNum(str,&p[6]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для a=",MB_OK|MB_ICONERROR);
				return false;
			}
			m_Edit19.GetWindowText(str);
			ret=e.IsNum(str,&p[18]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для Wmax=",MB_OK|MB_ICONERROR);
				return false;
			}
			break;
		}
	case 3:
		{
			m_Edit8.GetWindowText(str);
			ret=e.IsNum(str,&p[7]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для s=",MB_OK|MB_ICONERROR);
				return false;
			}
			m_Edit9.GetWindowText(str);
			ret=e.IsNum(str,&p[8]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для a=",MB_OK|MB_ICONERROR);
				return false;
			}
			m_Edit10.GetWindowText(str);
			ret=e.IsNum(str,&p[9]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для b=",MB_OK|MB_ICONERROR);
				return false;
			}
			m_Edit19.GetWindowText(str);
			ret=e.IsNum(str,&p[18]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для Wmax=",MB_OK|MB_ICONERROR);
				return false;
			}
			break;
		}
	case 4:
		{
			m_Edit11.GetWindowText(str);
			ret=e.IsNum(str,&p[10]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для s=",MB_OK|MB_ICONERROR);
				return false;
			}
			m_Edit12.GetWindowText(str);
			ret=e.IsNum(str,&p[11]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для a=",MB_OK|MB_ICONERROR);
				return false;
			}
			m_Edit13.GetWindowText(str);
			ret=e.IsNum(str,&p[12]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для b=",MB_OK|MB_ICONERROR);
				return false;
			}
			m_Edit19.GetWindowText(str);
			ret=e.IsNum(str,&p[18]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для Wmax=",MB_OK|MB_ICONERROR);
				return false;
			}
			break;
		}
	case 5:
		{
			CIDValuesMap idv;
			m_Edit14.GetWindowText(str);
			idv.SetAt(_T("w"),0.1);
			ret=e.IsNum(str,&p[13],&idv);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка в выражении",MB_OK|MB_ICONERROR);
				return false;
			}
			m_Edit15.GetWindowText(str);
			ret=e.IsNum(str,&p[14]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для w от",MB_OK|MB_ICONERROR);
				return false;
			}
			m_Edit16.GetWindowText(str);
			ret=e.IsNum(str,&p[15]);
			if (ret)
			{
				CString str;
				str.LoadString(ret);
				MessageBox(str,"Ошибка для w до",MB_OK|MB_ICONERROR);
				return false;
			}
			if (p[14]>p[15])
			{
				MessageBox("Значение w от больше чем w до","Ошибка",MB_OK|MB_ICONERROR);
				return false;
			}

			break;
		}
	};
	if (m_TypeInit==1)
	{
		m_Edit17.GetWindowText(str);
		ret=e.IsNum(str,&p[16]);
		if (ret)
		{
			CString str;
			str.LoadString(ret);
			MessageBox(str,"Ошибка в инициализации",MB_OK|MB_ICONERROR);
			return false;
		}
	}
	m_Edit18.GetWindowText(str);
	ret=e.IsNum(str,&p[17]);
	if (ret)
	{
		CString str;
		str.LoadString(ret);
		MessageBox(str,"Ошибка в запаздывании",MB_OK|MB_ICONERROR);
		return false;
	}

	return true;
}

void CKnotSpectr::OnRadio7() 
{
	// TODO: Add your control notification handler code here
	SetState();
}
