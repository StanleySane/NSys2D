// KnotPropertyPage1.cpp : implementation file
//


#include "stdafx.h"
#include "resource.h"
#include "KnotPropertyPage1.h"
#include "ComplexSpectrDlg.h"
#include "nsys2d.h"
#include "Graphfrm.h"
#include "graphicview.h"
#include "GraphTimeDlg.h"
#include "ProgressDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CKnotPropertyPage1, CPropertyPage)
IMPLEMENT_DYNCREATE(CKnotPropertyPage2, CPropertyPage)


/////////////////////////////////////////////////////////////////////////////
// CKnotPropertyPage1 property page

CKnotPropertyPage1::CKnotPropertyPage1() : CPropertyPage(CKnotPropertyPage1::IDD)
{
	//{{AFX_DATA_INIT(CKnotPropertyPage1)
	m_EditX = _T("0");
	m_EditY = _T("0");
	//}}AFX_DATA_INIT
}

CKnotPropertyPage1::~CKnotPropertyPage1()
{
}

void CKnotPropertyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKnotPropertyPage1)
	DDX_Control(pDX, IDC_COMBO1, m_FixedType);
	DDX_Text(pDX, IDC_EDIT1, m_EditX);
	DDV_MaxChars(pDX, m_EditX, 100);
	DDX_Text(pDX, IDC_EDIT2, m_EditY);
	DDV_MaxChars(pDX, m_EditY, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKnotPropertyPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CKnotPropertyPage1)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnChangeEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CKnotPropertyPage2 property page

CKnotPropertyPage2::CKnotPropertyPage2() : CPropertyPage(CKnotPropertyPage2::IDD)
{
	//{{AFX_DATA_INIT(CKnotPropertyPage2)
	m_EditUx = _T("");
	m_EditUy = _T("");
	m_EditUa = _T("");
	m_EditUxp = _T("");
	m_EditUyp = _T("");
	m_EditUap = _T("");
	//}}AFX_DATA_INIT
}

CKnotPropertyPage2::~CKnotPropertyPage2()
{
}

void CKnotPropertyPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKnotPropertyPage2)
	DDX_Text(pDX, IDC_EDIT1, m_EditUx);
	DDV_MaxChars(pDX, m_EditUx, 100);
	DDX_Text(pDX, IDC_EDIT2, m_EditUy);
	DDV_MaxChars(pDX, m_EditUy, 100);
	DDX_Text(pDX, IDC_EDIT3, m_EditUa);
	DDV_MaxChars(pDX, m_EditUa, 100);
	DDX_Text(pDX, IDC_EDIT5, m_EditUxp);
	DDV_MaxChars(pDX, m_EditUxp, 100);
	DDX_Text(pDX, IDC_EDIT6, m_EditUyp);
	DDV_MaxChars(pDX, m_EditUyp, 100);
	DDX_Text(pDX, IDC_EDIT7, m_EditUap);
	DDV_MaxChars(pDX, m_EditUap, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKnotPropertyPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CKnotPropertyPage2)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CKnotPropertyPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_FixedType.ResetContent();
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

BOOL CKnotPropertyPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_EditUx=pKnot->GetStrUx();
	m_EditUy=pKnot->GetStrUy();
	m_EditUa=pKnot->GetStrUa();

	m_EditUxp=pKnot->GetStrUx(1);
	m_EditUyp=pKnot->GetStrUy(1);
	m_EditUap=pKnot->GetStrUa(1);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CKnotPropertyPage2::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetData();
	CPropertyPage::OnOK();
}

void CKnotPropertyPage1::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetData();
	
	CPropertyPage::OnOK();
}
/////////////////////////////////////////////////////////////////////////////
// CKnotPropertyPage3 property page

IMPLEMENT_DYNCREATE(CKnotPropertyPage3, CPropertyPage)

CKnotPropertyPage3::CKnotPropertyPage3() : CPropertyPage(CKnotPropertyPage3::IDD)
{
	//{{AFX_DATA_INIT(CKnotPropertyPage3)
	m_CheckPx = FALSE;
	m_CheckPy = FALSE;
	//}}AFX_DATA_INIT
}

CKnotPropertyPage3::~CKnotPropertyPage3()
{
}

void CKnotPropertyPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKnotPropertyPage3)
	DDX_Control(pDX, IDC_CHECK4, m_CheckViewPy);
	DDX_Control(pDX, IDC_CHECK3, m_CheckViewPx);
	DDX_Control(pDX, IDC_CSPECPY, m_ButCPy);
	DDX_Control(pDX, IDC_CSPECPX, m_ButCPx);
	DDX_Control(pDX, IDC_RADIO6, m_RadPy3);
	DDX_Control(pDX, IDC_RADIO4, m_RadPy2);
	DDX_Control(pDX, IDC_RADIO3, m_RadPy1);
	DDX_Control(pDX, IDC_RADIO5, m_RadPx3);
	DDX_Control(pDX, IDC_RADIO2, m_RadPx2);
	DDX_Control(pDX, IDC_RADIO1, m_RadPx1);
	DDX_Control(pDX, IDC_SPECTRPY, m_ButPy);
	DDX_Control(pDX, IDC_SPECTRPX, m_ButPx);
	DDX_Control(pDX, IDC_EDIT8, m_EditFiy);
	DDX_Control(pDX, IDC_EDIT7, m_EditWy);
	DDX_Control(pDX, IDC_EDIT6, m_EditAy);
	DDX_Control(pDX, IDC_EDIT10, m_EditPy);
	DDX_Control(pDX, IDC_EDIT5, m_EditPx);
	DDX_Control(pDX, IDC_EDIT3, m_EditFix);
	DDX_Control(pDX, IDC_EDIT2, m_EditWx);
	DDX_Control(pDX, IDC_EDIT1, m_EditAx);
	DDX_Check(pDX, IDC_CHECK1, m_CheckPx);
	DDX_Check(pDX, IDC_CHECK2, m_CheckPy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKnotPropertyPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CKnotPropertyPage3)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_CHECK1, OnCheckPx)
	ON_BN_CLICKED(IDC_CHECK2, OnCheckPy)
	ON_BN_CLICKED(IDC_SPECTRPX, OnSpectrpx)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_SPECTRPY, OnSpectrpy)
	ON_BN_CLICKED(IDC_CSPECPX, OnCspecpx)
	ON_BN_CLICKED(IDC_CSPECPY, OnCspecpy)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit)
	ON_BN_DOUBLECLICKED(IDC_CHECK3, OnDoubleclickedCheck3)
	ON_EN_CHANGE(IDC_EDIT10, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit)
	ON_BN_DOUBLECLICKED(IDC_CHECK4, OnDoubleclickedCheck3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKnotPropertyPage3 message handlers

BOOL CKnotPropertyPage3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_EditAx.SetWindowText(pKnot->str_Ax);
	m_EditWx.SetWindowText(pKnot->str_Wx);
	m_EditFix.SetWindowText(pKnot->str_Fix);
	m_EditPx.SetWindowText(pKnot->str_Px);

	m_EditAy.SetWindowText(pKnot->str_Ay);
	m_EditWy.SetWindowText(pKnot->str_Wy);
	m_EditFiy.SetWindowText(pKnot->str_Fiy);
	m_EditPy.SetWindowText(pKnot->str_Py);

	m_RadPx1.SetCheck(pKnot->TypePx==0);
	m_RadPx2.SetCheck(pKnot->TypePx==1);
	m_RadPx3.SetCheck(pKnot->TypePx==2);

	m_RadPy1.SetCheck(pKnot->TypePy==0);
	m_RadPy2.SetCheck(pKnot->TypePy==1);
	m_RadPy3.SetCheck(pKnot->TypePy==2);
	
	m_CheckPx=pKnot->PxEnable;
	m_CheckPy=pKnot->PyEnable;
	UpdateData(false);
	
	SetState();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CKnotPropertyPage3::SetState()
{
//	UpdateData(true);

	m_EditAx.EnableWindow(m_RadPx1.GetCheck()&&m_CheckPx);
	m_EditWx.EnableWindow(m_RadPx1.GetCheck()&&m_CheckPx);
	m_EditFix.EnableWindow(m_RadPx1.GetCheck()&&m_CheckPx);
	m_EditPx.EnableWindow(m_RadPx2.GetCheck()&&m_CheckPx);
	m_ButPx.EnableWindow(m_RadPx3.GetCheck()&&m_CheckPx);
	m_ButCPx.EnableWindow(m_RadPx3.GetCheck()&&m_CheckPx);

	m_RadPx1.EnableWindow(m_CheckPx);
	m_RadPx2.EnableWindow(m_CheckPx);
	m_RadPx3.EnableWindow(m_CheckPx);

	m_CheckViewPx.ShowWindow(m_CheckPx?SW_SHOW:0);

	m_EditAy.EnableWindow(m_RadPy1.GetCheck()&&m_CheckPy);
	m_EditWy.EnableWindow(m_RadPy1.GetCheck()&&m_CheckPy);
	m_EditFiy.EnableWindow(m_RadPy1.GetCheck()&&m_CheckPy);
	m_EditPy.EnableWindow(m_RadPy2.GetCheck()&&m_CheckPy);
	m_ButPy.EnableWindow(m_RadPy3.GetCheck()&&m_CheckPy);
	m_ButCPy.EnableWindow(m_RadPy3.GetCheck()&&m_CheckPy);

	m_RadPy1.EnableWindow(m_CheckPy);
	m_RadPy2.EnableWindow(m_CheckPy);
	m_RadPy3.EnableWindow(m_CheckPy);

	m_CheckViewPy.ShowWindow(m_CheckPy?SW_SHOW:0);
	
	UpdateData(false);
}

void CKnotPropertyPage3::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	m_RadPx2.SetCheck(0);
	m_RadPx3.SetCheck(0);
	SetState();
}

void CKnotPropertyPage3::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	m_RadPx1.SetCheck(0);
	m_RadPx3.SetCheck(0);
	SetState();
}

void CKnotPropertyPage3::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	m_RadPy2.SetCheck(0);
	m_RadPy3.SetCheck(0);
	SetState();
}

void CKnotPropertyPage3::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	m_RadPy1.SetCheck(0);
	m_RadPy3.SetCheck(0);
	SetState();
}

void CKnotPropertyPage3::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
//	if (!VerifyInfo()) return;
	SetData();

	//Вывод графиков если требуется
	if (m_CheckViewPx.GetCheck())
	{
		int s=int((pKnot->ParamTime.T1-pKnot->ParamTime.T0)/pKnot->ParamTime.dT);
		if (s<2) s=3;

		CMatr Dat(2,s);
		int ret=pKnot->BeginIntegr(pKnot->ParamTime.T1);
		CProgressDlg *pDlg=new CProgressDlg(100,_T("Вычисление Px(t)"));
		BOOL FlagExit=false;

		for (int i=0;i<s;i++)
		{
			Dat[0][i]=i*pKnot->ParamTime.dT;
			Dat[1][i]=pKnot->GetPx(0,0,i*pKnot->ParamTime.dT);

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
		if (ret) pKnot->EndIntegr();
		
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
		CString str;
		str.Format("Силовое возмущение Px(t). Узел №%d",pKnot->Num);
		pGraphView->str_title=str;
		//Начальная установка границ изображения
		pGraphView->SetMaxMin();
		pNewFrame->SetWindowText(str);
		pGraphView->Dat.ReSize(2,Dat.SizeX);
		pGraphView->Dat=Dat;
	}
	if (m_CheckViewPy.GetCheck())
	{
		int s=int((pKnot->ParamTime.T1-pKnot->ParamTime.T0)/pKnot->ParamTime.dT);
		if (s<2) s=3;

		CMatr Dat(2,s);
		int ret=pKnot->BeginIntegr(pKnot->ParamTime.T1);
		CProgressDlg *pDlg=new CProgressDlg(100,_T("Вычисление Py(t)"));
		BOOL FlagExit=false;

		for (int i=0;i<s;i++)
		{
			Dat[0][i]=i*pKnot->ParamTime.dT;
			Dat[1][i]=pKnot->GetPy(0,0,i*pKnot->ParamTime.dT);

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
		if (ret) pKnot->EndIntegr();
		
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
		CString str;
		str.Format("Силовое возмущение Py(t). Узел №%d",pKnot->Num);
		pGraphView->str_title=str;
		//Начальная установка границ изображения
		pGraphView->SetMaxMin();
		pNewFrame->SetWindowText(str);
		pGraphView->Dat.ReSize(2,Dat.SizeX);
		pGraphView->Dat=Dat;
	}
	//Конец вывода графиков********************

	CPropertyPage::OnOK();
}

BOOL CKnotPropertyPage3::VerifyInfo()
{
	UpdateData();

	CString str1;
	CExpression e;
	int ret;

	if (m_RadPx1.GetCheck())
	{
		double Ax,Wx,Fix;
		
		m_EditAx.GetWindowText(str1);
		if (ret=e.IsNum(str1,&Ax))
		{
			CString mes;
			mes.LoadString(ret);
			
			MessageBox(mes,"Амплитуда Ax не число",
				 MB_OK|MB_ICONERROR );
			
			return false;
		}

		m_EditWx.GetWindowText(str1);
		if (ret=e.IsNum(str1,&Wx))
		{
			CString mes;
			mes.LoadString(ret);
			
			MessageBox(mes,"Частота Wx не число",
				 MB_OK|MB_ICONERROR );
			
			return false;
		}

		m_EditFix.GetWindowText(str1);
		if (ret=e.IsNum(str1,&Fix))
		{
			CString mes;
			mes.LoadString(ret);
			
			MessageBox(mes,"Фаза Fix не число",
				 MB_OK|MB_ICONERROR );
			
			return false;
		}
	}
	if (m_RadPx2.GetCheck())
	{
		m_EditPx.GetWindowText(str1);
		CIDValuesMap idv;
		idv.SetAt(_T("x"),0.1);
		idv.SetAt(_T("x1"),0.1);
		idv.SetAt(_T("t"),0.1);
		ret=e.IsNum(str1,0,&idv);
		if (ret)
		{
			CString str;
			str.LoadString(ret);
			MessageBox(str,"Ошибка в выражении Px"
				,MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}

	if (m_RadPy1.GetCheck())
	{
		CExpression e;
		int ret;
		double Ay,Wy,Fiy;

		m_EditAy.GetWindowText(str1);
		if (ret=e.IsNum(str1,&Ay))
		{
			CString mes;
			mes.LoadString(ret);
			
			MessageBox(mes,"Амплитуда Ay не число",
				 MB_OK|MB_ICONERROR );
			
			return false;
		}

		m_EditWy.GetWindowText(str1);
		if (ret=e.IsNum(str1,&Wy))
		{
			CString mes;
			mes.LoadString(ret);
			
			MessageBox(mes,"Частота Wy не число",
				 MB_OK|MB_ICONERROR );
			
			return false;
		}

		m_EditFiy.GetWindowText(str1);
		if (ret=e.IsNum(str1,&Fiy))
		{
			CString mes;
			mes.LoadString(ret);
			
			MessageBox(mes,"Фаза Fiy не число",
				 MB_OK|MB_ICONERROR );
			
			return false;
		}
	}
	if (m_RadPy2.GetCheck())
	{
		m_EditPy.GetWindowText(str1);
		CIDValuesMap idv;
		idv.SetAt(_T("x"),0.1);
		idv.SetAt(_T("x1"),0.1);
		idv.SetAt(_T("t"),0.1);
		ret=e.IsNum(str1,0,&idv);
		if (ret)
		{
			CString str;
			str.LoadString(ret);
			MessageBox(str,"Ошибка в выражении Py"
				,MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}
	return true;
}

void CKnotPropertyPage3::OnCheckPx() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	UpdateData(true);
	SetState();
}

void CKnotPropertyPage3::OnCheckPy() 
{
	// TODO: Add your control notification handler code here
	//m_CheckPy.SetCheck(m_CheckPy.GetCheck()==1?0:1);
	SetModified();
	UpdateData(true);
	SetState();
}
/////////////////////////////////////////////////////////////////////////////
// CKnotPropertyPage4 property page

IMPLEMENT_DYNCREATE(CKnotPropertyPage4, CPropertyPage)

CKnotPropertyPage4::CKnotPropertyPage4() : CPropertyPage(CKnotPropertyPage4::IDD)
{
	//{{AFX_DATA_INIT(CKnotPropertyPage4)
	m_CheckUx = FALSE;
	m_CheckUy = FALSE;
	//}}AFX_DATA_INIT
}

CKnotPropertyPage4::~CKnotPropertyPage4()
{
}

void CKnotPropertyPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKnotPropertyPage4)
	DDX_Control(pDX, IDC_CSPECUY, m_ButCUy);
	DDX_Control(pDX, IDC_CSPECUX, m_ButCUx);
	DDX_Control(pDX, IDC_CHECK4, m_CheckViewUy);
	DDX_Control(pDX, IDC_CHECK3, m_CheckViewUx);
	DDX_Control(pDX, IDC_RADIO6, m_RadUy3);
	DDX_Control(pDX, IDC_RADIO5, m_RadUx3);
	DDX_Control(pDX, IDC_BUTTON2, m_ButUy);
	DDX_Control(pDX, IDC_BUTTON1, m_ButUx);
	DDX_Control(pDX, IDC_EDIT10, m_EditUy);
	DDX_Control(pDX, IDC_EDIT8, m_EditFiy);
	DDX_Control(pDX, IDC_EDIT7, m_EditWy);
	DDX_Control(pDX, IDC_EDIT6, m_EditAy);
	DDX_Control(pDX, IDC_EDIT5, m_EditUx);
	DDX_Control(pDX, IDC_EDIT3, m_EditFix);
	DDX_Control(pDX, IDC_EDIT2, m_EditWx);
	DDX_Control(pDX, IDC_EDIT1, m_EditAx);
	DDX_Control(pDX, IDC_RADIO4, m_RadUy2);
	DDX_Control(pDX, IDC_RADIO3, m_RadUy1);
	DDX_Control(pDX, IDC_RADIO2, m_RadUx2);
	DDX_Control(pDX, IDC_RADIO1, m_RadUx1);
	DDX_Check(pDX, IDC_CHECK1, m_CheckUx);
	DDX_Check(pDX, IDC_CHECK2, m_CheckUy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKnotPropertyPage4, CPropertyPage)
	//{{AFX_MSG_MAP(CKnotPropertyPage4)
	ON_BN_CLICKED(IDC_CHECK1, OnCheckUx)
	ON_BN_CLICKED(IDC_CHECK2, OnCheckUy)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit)
	ON_BN_CLICKED(IDC_CSPECUX, OnCspecux)
	ON_BN_CLICKED(IDC_CSPECUY, OnCspecuy)
	ON_EN_CHANGE(IDC_EDIT10, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit)
	ON_BN_DOUBLECLICKED(IDC_CHECK3, OnDoubleclickedCheck3)
	ON_BN_DOUBLECLICKED(IDC_CHECK4, OnDoubleclickedCheck3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKnotPropertyPage4 message handlers

void CKnotPropertyPage4::OnCheckUx() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	UpdateData(true);
	SetState();
}

void CKnotPropertyPage4::OnCheckUy() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	UpdateData(true);
	SetState();
}

void CKnotPropertyPage4::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	m_RadUx2.SetCheck(0);
	m_RadUx3.SetCheck(0);
	SetState();
}

void CKnotPropertyPage4::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	m_RadUx1.SetCheck(0);
	m_RadUx3.SetCheck(0);
	SetState();
}

void CKnotPropertyPage4::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	m_RadUy2.SetCheck(0);
	m_RadUy3.SetCheck(0);
	SetState();
}

void CKnotPropertyPage4::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	m_RadUy1.SetCheck(0);
	m_RadUy3.SetCheck(0);
	SetState();
}

void CKnotPropertyPage4::SetState()
{
//	UpdateData(true);

	m_EditAx.EnableWindow(m_RadUx1.GetCheck()&&m_CheckUx);
	m_EditWx.EnableWindow(m_RadUx1.GetCheck()&&m_CheckUx);
	m_EditFix.EnableWindow(m_RadUx1.GetCheck()&&m_CheckUx);
	m_EditUx.EnableWindow(m_RadUx2.GetCheck()&&m_CheckUx);
	m_ButUx.EnableWindow(m_RadUx3.GetCheck()&&m_CheckUx);
	m_ButCUx.EnableWindow(m_RadUx3.GetCheck()&&m_CheckUx);

	m_RadUx1.EnableWindow(m_CheckUx);
	m_RadUx2.EnableWindow(m_CheckUx);
	m_RadUx3.EnableWindow(m_CheckUx);
	
	m_CheckViewUx.ShowWindow(m_CheckUx?SW_SHOW:0);

	m_EditAy.EnableWindow(m_RadUy1.GetCheck()&&m_CheckUy);
	m_EditWy.EnableWindow(m_RadUy1.GetCheck()&&m_CheckUy);
	m_EditFiy.EnableWindow(m_RadUy1.GetCheck()&&m_CheckUy);
	m_EditUy.EnableWindow(m_RadUy2.GetCheck()&&m_CheckUy);
	m_ButUy.EnableWindow(m_RadUy3.GetCheck()&&m_CheckUy);
	m_ButCUy.EnableWindow(m_RadUy3.GetCheck()&&m_CheckUy);

	m_RadUy1.EnableWindow(m_CheckUy);
	m_RadUy2.EnableWindow(m_CheckUy);
	m_RadUy3.EnableWindow(m_CheckUy);

	m_CheckViewUy.ShowWindow(m_CheckUy?SW_SHOW:0);
	
	UpdateData(false);
}

BOOL CKnotPropertyPage4::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_EditAx.SetWindowText(pKnot->str_uAx);
	m_EditWx.SetWindowText(pKnot->str_uWx);
	m_EditFix.SetWindowText(pKnot->str_uFix);
	m_EditUx.SetWindowText(pKnot->str_uUx);

	m_EditAy.SetWindowText(pKnot->str_uAy);
	m_EditWy.SetWindowText(pKnot->str_uWy);
	m_EditFiy.SetWindowText(pKnot->str_uFiy);
	m_EditUy.SetWindowText(pKnot->str_uUy);

	m_RadUx1.SetCheck(pKnot->TypeUx==0);
	m_RadUx2.SetCheck(pKnot->TypeUx==1);
	m_RadUx3.SetCheck(pKnot->TypeUx==2);

	m_RadUy1.SetCheck(pKnot->TypeUy==0);
	m_RadUy2.SetCheck(pKnot->TypeUy==1);
	m_RadUy3.SetCheck(pKnot->TypeUy==2);
	
	m_CheckUx=pKnot->UxEnable;
	m_CheckUy=pKnot->UyEnable;
	UpdateData(false);
	
	SetState();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKnotPropertyPage4::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetData();

	//Вывод графиков если требуется
	if (m_CheckViewUx.GetCheck())
	{
		int s=int((pKnot->ParamTime.T1-pKnot->ParamTime.T0)/pKnot->ParamTime.dT);
		if (s<2) s=3;

		CMatr Dat(2,s);
		int ret=pKnot->BeginIntegr(pKnot->ParamTime.T1);
		CProgressDlg *pDlg=new CProgressDlg(100,_T("Вычисление Ux(t)"));
		BOOL FlagExit=false;

		for (int i=0;i<s;i++)
		{
			Dat[0][i]=i*pKnot->ParamTime.dT;
			Dat[1][i]=pKnot->GetUx(i*pKnot->ParamTime.dT);

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
			while (PeekMessage(&msg, 0, 0, 0x0ffff, PM_REMOVE))   // Until WM_QUIT message
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
		if (ret) pKnot->EndIntegr();
		
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
		CString str;
		str.Format("Кинематическое возмущение Ux(t). Узел №%d",pKnot->Num);
		pGraphView->str_title=str;
		//Начальная установка границ изображения
		pGraphView->SetMaxMin();
		pNewFrame->SetWindowText(str);
		pGraphView->Dat.ReSize(2,Dat.SizeX);
		pGraphView->Dat=Dat;
	}
	if (m_CheckViewUy.GetCheck())
	{
		int s=int((pKnot->ParamTime.T1-pKnot->ParamTime.T0)/pKnot->ParamTime.dT);
		if (s<2) s=3;

		CMatr Dat(2,s);
		int ret=pKnot->BeginIntegr(pKnot->ParamTime.T1);
		CProgressDlg *pDlg=new CProgressDlg(100,_T("Вычисление Uy(t)"));
		BOOL FlagExit=false;

		for (int i=0;i<s;i++)
		{
			Dat[0][i]=i*pKnot->ParamTime.dT;
			Dat[1][i]=pKnot->GetUy(i*pKnot->ParamTime.dT);

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
			while (PeekMessage(&msg, 0, 0, 0x0ffff, PM_REMOVE))   // Until WM_QUIT message
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
		if (ret) pKnot->EndIntegr();
		
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
		CString str;
		str.Format("Кинематическое возмущение Uy(t). Узел №%d",pKnot->Num);
		pGraphView->str_title=str;
		//Начальная установка границ изображения
		pGraphView->SetMaxMin();
		pNewFrame->SetWindowText(str);
		pGraphView->Dat.ReSize(2,Dat.SizeX);
		pGraphView->Dat=Dat;
	}
	
	CPropertyPage::OnOK();
}

BOOL CKnotPropertyPage4::VerifyInfo()
{
	UpdateData();

	CString str1;
	CExpression e;
	int ret;

	if (m_RadUx1.GetCheck())
	{
		double Ax,Wx,Fix;
		
		m_EditAx.GetWindowText(str1);
		if (ret=e.IsNum(str1,&Ax))
		{
			CString mes;
			mes.LoadString(ret);
			
			MessageBox(mes,"Амплитуда Ax не число",
				 MB_OK|MB_ICONERROR );
			
			return false;
		}

		m_EditWx.GetWindowText(str1);
		if (ret=e.IsNum(str1,&Wx))
		{
			CString mes;
			mes.LoadString(ret);
			
			MessageBox(mes,"Частота Wx не число",
				 MB_OK|MB_ICONERROR );
			
			return false;
		}

		m_EditFix.GetWindowText(str1);
		if (ret=e.IsNum(str1,&Fix))
		{
			CString mes;
			mes.LoadString(ret);
			
			MessageBox(mes,"Фаза Fix не число",
				 MB_OK|MB_ICONERROR );
			
			return false;
		}
	}
	if (m_RadUx2.GetCheck())
	{
		m_EditUx.GetWindowText(str1);
		CIDValuesMap idv;
		idv.SetAt(_T("t"),0.1);
		ret=e.IsNum(str1,0,&idv);
		if (ret)
		{
			CString str;
			str.LoadString(ret);
			MessageBox(str,"Ошибка в выражении Ux"
				,MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}

	if (m_RadUy1.GetCheck())
	{
		CExpression e;
		int ret;
		double Ay,Wy,Fiy;

		m_EditAy.GetWindowText(str1);
		if (ret=e.IsNum(str1,&Ay))
		{
			CString mes;
			mes.LoadString(ret);
			
			MessageBox(mes,"Амплитуда Ay не число",
				 MB_OK|MB_ICONERROR );
			
			return false;
		}

		m_EditWy.GetWindowText(str1);
		if (ret=e.IsNum(str1,&Wy))
		{
			CString mes;
			mes.LoadString(ret);
			
			MessageBox(mes,"Частота Wy не число",
				 MB_OK|MB_ICONERROR );
			
			return false;
		}

		m_EditFiy.GetWindowText(str1);
		if (ret=e.IsNum(str1,&Fiy))
		{
			CString mes;
			mes.LoadString(ret);
			
			MessageBox(mes,"Фаза Fiy не число",
				 MB_OK|MB_ICONERROR );
			
			return false;
		}
	}
	if (m_RadUy2.GetCheck())
	{
		m_EditUy.GetWindowText(str1);
		CIDValuesMap idv;
		idv.SetAt(_T("t"),0.1);
		ret=e.IsNum(str1,0,&idv);
		if (ret)
		{
			CString str;
			str.LoadString(ret);
			MessageBox(str,"Ошибка в выражении Uy"
				,MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}
	return true;
}

void CKnotPropertyPage3::OnSpectrpx() 
{
	// TODO: Add your control notification handler code here
	pKnot->SpPx.GoDlg();
}

void CKnotPropertyPage3::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	m_RadPx1.SetCheck(0);
	m_RadPx2.SetCheck(0);
	SetState();
}

void CKnotPropertyPage3::OnRadio6() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	m_RadPy1.SetCheck(0);
	m_RadPy2.SetCheck(0);
	SetState();
}

void CKnotPropertyPage3::OnSpectrpy() 
{
	// TODO: Add your control notification handler code here
	pKnot->SpPy.GoDlg();
}

void CKnotPropertyPage4::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	m_RadUx1.SetCheck(0);
	m_RadUx2.SetCheck(0);
	SetState();
}

void CKnotPropertyPage4::OnRadio6() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	m_RadUy1.SetCheck(0);
	m_RadUy2.SetCheck(0);
	SetState();
}

void CKnotPropertyPage4::OnButton1() 
{
	// TODO: Add your control notification handler code here
	pKnot->SpUx.GoDlg();
}

void CKnotPropertyPage4::OnButton2() 
{
	// TODO: Add your control notification handler code here
	pKnot->SpUy.GoDlg();
}

void CKnotPropertyPage3::OnCspecpx() 
{
	// TODO: Add your control notification handler code here
	CComplexSpectrDlg dlg(pListKnot, pListSpectr, pKnot, 0);
	dlg.DoModal();
}

void CKnotPropertyPage3::OnCspecpy() 
{
	// TODO: Add your control notification handler code here
	CComplexSpectrDlg dlg(pListKnot, pListSpectr, pKnot, 1);
	dlg.DoModal();
}

BOOL CKnotPropertyPage3::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return (CPropertyPage::OnKillActive()&&VerifyInfo());
}

BOOL CKnotPropertyPage1::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return (CPropertyPage::OnKillActive()&&VerifyInfo());
}

BOOL CKnotPropertyPage2::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return (CPropertyPage::OnKillActive()&&VerifyInfo());
}

BOOL CKnotPropertyPage4::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return (CPropertyPage::OnKillActive()&&VerifyInfo());
}

BOOL CKnotPropertyPage1::VerifyInfo()
{
	UpdateData();
	
	CExpression e;
	int ret;
	if (ret=e.IsNum(m_EditX))
	{
		CString mes;
		mes.LoadString(ret);
		
		MessageBox(mes,"Координата X",
			 MB_OK|MB_ICONERROR );
		
		return false;
	}

	if (ret=e.IsNum(m_EditY))
	{
		CString mes;
		mes.LoadString(ret);
		
		MessageBox(mes,"Координата Y",
			  MB_OK|MB_ICONERROR );
		
		return false;
	}
	return true;
}

BOOL CKnotPropertyPage2::VerifyInfo()
{
	UpdateData();
	
	CExpression e;
	int ret;
	if (ret=e.IsNum(m_EditUx))
	{
		CString mes;
		mes.LoadString(ret);
		
		MessageBox(mes,"Перемещение Ux",
			 MB_OK|MB_ICONERROR );
		
		return false;
	}

	if (ret=e.IsNum(m_EditUy))
	{
		CString mes;
		mes.LoadString(ret);
		
		MessageBox(mes,"Перемещение Uy",
			 MB_OK|MB_ICONERROR );
		
		return false;
	}

	if (ret=e.IsNum(m_EditUa))
	{
		CString mes;
		mes.LoadString(ret);
		
		MessageBox(mes,"Перемещение Ua",
			 MB_OK|MB_ICONERROR );
		
		return false;
	}
	
	if (ret=e.IsNum(m_EditUxp))
	{
		CString mes;
		mes.LoadString(ret);
		
		MessageBox(mes,"Перемещение Uxp",
			 MB_OK|MB_ICONERROR );
		
		return false;
	}

	if (ret=e.IsNum(m_EditUyp))
	{
		CString mes;
		mes.LoadString(ret);
		
		MessageBox(mes,"Перемещение Uyp",
			 MB_OK|MB_ICONERROR );
		
		return false;
	}

	if (ret=e.IsNum(m_EditUap))
	{
		CString mes;
		mes.LoadString(ret);
		
		MessageBox(mes,"Перемещение Uap",
			 MB_OK|MB_ICONERROR );
		
		return false;
	}
	return true;
}


BOOL CKnotPropertyPage3::OnApply() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!VerifyInfo()) return false;

	SetData();
	
//	return true;
	
	return CPropertyPage::OnApply();
}

void CKnotPropertyPage3::OnChangeEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	SetModified();
}

void CKnotPropertyPage3::SetData()
{
	UpdateData();
	
	m_EditAx.GetWindowText(pKnot->str_Ax);
	m_EditWx.GetWindowText(pKnot->str_Wx);
	m_EditFix.GetWindowText(pKnot->str_Fix);
	m_EditPx.GetWindowText(pKnot->str_Px);

	m_EditAy.GetWindowText(pKnot->str_Ay);
	m_EditWy.GetWindowText(pKnot->str_Wy);
	m_EditFiy.GetWindowText(pKnot->str_Fiy);
	m_EditPy.GetWindowText(pKnot->str_Py);


	if (m_RadPx1.GetCheck()) pKnot->TypePx=0;
	if (m_RadPx2.GetCheck()) pKnot->TypePx=1;
	if (m_RadPx3.GetCheck()) pKnot->TypePx=2;

	if (m_RadPy1.GetCheck()) pKnot->TypePy=0;
	if (m_RadPy2.GetCheck()) pKnot->TypePy=1;
	if (m_RadPy3.GetCheck()) pKnot->TypePy=2;

	pKnot->PxEnable=m_CheckPx;
	pKnot->PyEnable=m_CheckPy;

	CString str1;
	CExpression e;

	if (m_RadPx1.GetCheck())
	{
		m_EditAx.GetWindowText(str1);
		e.IsNum(str1,&pKnot->Ax);

		m_EditWx.GetWindowText(str1);
		e.IsNum(str1,&pKnot->Wx);

		m_EditFix.GetWindowText(str1);
		e.IsNum(str1,&pKnot->Fix);
	}

	if (m_RadPy1.GetCheck())
	{
		m_EditAy.GetWindowText(str1);
		e.IsNum(str1,&pKnot->Ay);

		m_EditWy.GetWindowText(str1);
		e.IsNum(str1,&pKnot->Wy);

		m_EditFiy.GetWindowText(str1);
		e.IsNum(str1,&pKnot->Fiy);
	}
}

void CKnotPropertyPage4::SetData()
{
	UpdateData();
	
	m_EditAx.GetWindowText(pKnot->str_uAx);
	m_EditWx.GetWindowText(pKnot->str_uWx);
	m_EditFix.GetWindowText(pKnot->str_uFix);
	m_EditUx.GetWindowText(pKnot->str_uUx);

	m_EditAy.GetWindowText(pKnot->str_uAy);
	m_EditWy.GetWindowText(pKnot->str_uWy);
	m_EditFiy.GetWindowText(pKnot->str_uFiy);
	m_EditUy.GetWindowText(pKnot->str_uUy);


	if (m_RadUx1.GetCheck()) pKnot->TypeUx=0;
	if (m_RadUx2.GetCheck()) pKnot->TypeUx=1;
	if (m_RadUx3.GetCheck()) pKnot->TypeUx=2;

	if (m_RadUy1.GetCheck()) pKnot->TypeUy=0;
	if (m_RadUy2.GetCheck()) pKnot->TypeUy=1;
	if (m_RadUy3.GetCheck()) pKnot->TypeUy=2;

	pKnot->UxEnable=m_CheckUx;
	pKnot->UyEnable=m_CheckUy;

	CString str1;
	CExpression e;

	if (m_RadUx1.GetCheck())
	{
		m_EditAx.GetWindowText(str1);
		e.IsNum(str1,&pKnot->uAx);

		m_EditWx.GetWindowText(str1);
		e.IsNum(str1,&pKnot->uWx);

		m_EditFix.GetWindowText(str1);
		e.IsNum(str1,&pKnot->uFix);
	}

	if (m_RadUy1.GetCheck())
	{
		m_EditAy.GetWindowText(str1);
		e.IsNum(str1,&pKnot->uAy);

		m_EditWy.GetWindowText(str1);
		e.IsNum(str1,&pKnot->uWy);

		m_EditFiy.GetWindowText(str1);
		e.IsNum(str1,&pKnot->uFiy);
	}
}

BOOL CKnotPropertyPage4::OnApply() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!VerifyInfo()) return false;

	SetData();
	
//	return true;
	return CPropertyPage::OnApply();
}

void CKnotPropertyPage4::OnChangeEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	SetModified();	
}

void CKnotPropertyPage2::OnChangeEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	SetModified();
}

BOOL CKnotPropertyPage2::OnApply() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!VerifyInfo()) return false;
	SetData();
	return CPropertyPage::OnApply();
}

void CKnotPropertyPage2::SetData()
{
	UpdateData();
	
	pKnot->SetStrUx(m_EditUx);
	pKnot->SetStrUy(m_EditUy);
	pKnot->SetStrUa(m_EditUa);

	pKnot->SetStrUx(m_EditUxp,1);
	pKnot->SetStrUy(m_EditUyp,1);
	pKnot->SetStrUa(m_EditUap,1);
}

BOOL CKnotPropertyPage1::OnApply() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!VerifyInfo()) return false;
	SetData();
		
	return CPropertyPage::OnApply();
}

void CKnotPropertyPage1::SetData()
{
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
}

void CKnotPropertyPage1::OnChangeEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	SetModified();	
}

/*void CKnotPropertyPage3::OnGraphpy() 
{
	// TODO: Add your control notification handler code here
	CGraphTimeDlg dlg;
	if (dlg.DoModal()!=IDOK) return;
	int s=int((dlg.End-dlg.Beg)/dlg.Step);
	if (s<2) return;
	CMatr Dat(2,s);
	pKnot->BeginIntegr(dlg.End);
	CProgressDlg *pDlg=new CProgressDlg(100,_T("Вычисления"));
	BOOL FlagExit=false;

	for (int i=0;i<s;i++)
	{
		Dat[0][i]=i*dlg.Step;
		Dat[1][i]=pKnot->GetPy(0,0,i*dlg.Step);

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
		while (PeekMessage(&msg, 0, 0, 0x0ffff, PM_REMOVE))   // Until WM_QUIT message
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
	pKnot->EndIntegr();
	
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
	CString str;
	str.Format("График силового возмущения Px. Узел №%d",pKnot->Num);
	pGraphView->str_title=str;
	//Начальная установка границ изображения
	pGraphView->SetMaxMin();

	pNewFrame->SetWindowText(str);

	pGraphView->Dat.ReSize(2,Dat.SizeX);

	pGraphView->Dat=Dat;

//	pDoc->UpdateAllViews(0);
	
}*/

void CKnotPropertyPage4::OnCspecux() 
{
	// TODO: Add your control notification handler code here
	CComplexSpectrDlg dlg(pListKnot, pListSpectr, pKnot, 0);
	dlg.DoModal();
}

void CKnotPropertyPage4::OnCspecuy() 
{
	// TODO: Add your control notification handler code here
	CComplexSpectrDlg dlg(pListKnot, pListSpectr, pKnot, 1);
	dlg.DoModal();
}

void CKnotPropertyPage3::OnDoubleclickedCheck3() 
{
	// TODO: Add your control notification handler code here
	CGraphTimeDlg dlg(&pKnot->ParamTime);
	dlg.DoModal();
}

void CKnotPropertyPage4::OnDoubleclickedCheck3() 
{
	// TODO: Add your control notification handler code here
	CGraphTimeDlg dlg(&pKnot->ParamTime);
	dlg.DoModal();
}

