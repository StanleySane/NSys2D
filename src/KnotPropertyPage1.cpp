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
#include "Sheme.h"
#include "Elem.h"

using namespace std;

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
	m_EditX = 0.0;
	m_EditY = 0.0;
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
	DDX_Text(pDX, IDC_EDIT2, m_EditY);
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
	m_FixedType.AddString("");
	m_FixedType.AddString("");
	m_FixedType.AddString("");
	m_FixedType.SetCurSel(pKnot->FixedType);

	if( m_bFull )
	{
		//m_EditX = pKnot->GetStrX();
		//m_EditY = pKnot->GetStrY();
		m_EditX = pKnot->GetCoordX();
		m_EditY = pKnot->GetCoordY();
	}
	else
	{
		//m_EditX = _T("");
		//m_EditY = _T("");
		GetDlgItem(IDC_EDIT1)->SetWindowText("");
		GetDlgItem(IDC_EDIT2)->SetWindowText("");
	}

	GetDlgItem(IDC_EDIT1)->EnableWindow(m_bFull);
	GetDlgItem(IDC_EDIT2)->EnableWindow(m_bFull);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CKnotPropertyPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_EditUx = pKnot->m_Ux.GetExpr().c_str();
	m_EditUy = pKnot->m_Uy.GetExpr().c_str();
	m_EditUa = pKnot->m_Ua.GetExpr().c_str();

	m_EditUxp = pKnot->m_Uxp.GetExpr().c_str();
	m_EditUyp = pKnot->m_Uyp.GetExpr().c_str();
	m_EditUap = pKnot->m_Uap.GetExpr().c_str();

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
	m_EditPx = _T("");
	m_EditPy = _T("");
	m_EditAx = 0.0;
	m_EditWx = 0.0;
	m_EditFix = 0.0;
	m_EditAy = 0.0;
	m_EditWy = 0.0;
	m_EditFiy = 0.0;
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
	DDX_Check(pDX, IDC_CHECK1, m_CheckPx);
	DDX_Check(pDX, IDC_CHECK2, m_CheckPy);
	DDX_Text(pDX, IDC_EDIT5, m_EditPx);
	DDV_MaxChars(pDX, m_EditPx, 100);
	DDX_Text(pDX, IDC_EDIT10, m_EditPy);
	DDV_MaxChars(pDX, m_EditPy, 100);
	DDX_Text(pDX, IDC_EDIT1, m_EditAx);
	DDX_Text(pDX, IDC_EDIT2, m_EditWx);
	DDX_Text(pDX, IDC_EDIT3, m_EditFix);
	DDX_Text(pDX, IDC_EDIT6, m_EditAy);
	DDX_Text(pDX, IDC_EDIT7, m_EditWy);
	DDX_Text(pDX, IDC_EDIT8, m_EditFiy);
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
	m_EditAx = pKnot->Ax;
	m_EditWx = pKnot->Wx;
	m_EditFix = pKnot->Fix;
	m_EditPx = pKnot->m_Px.GetExpr().c_str();

	m_EditAy = pKnot->Ay;
	m_EditWy = pKnot->Wy;
	m_EditFiy = pKnot->Fiy;
	m_EditPy = pKnot->m_Py.GetExpr().c_str();

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

	BOOL state = m_RadPx1.GetCheck()&&m_CheckPx;
	GetDlgItem(IDC_EDIT1)->EnableWindow(state);
	GetDlgItem(IDC_EDIT2)->EnableWindow(state);
	GetDlgItem(IDC_EDIT3)->EnableWindow(state);

	GetDlgItem(IDC_EDIT5)->EnableWindow(m_RadPx2.GetCheck()&&m_CheckPx);

	m_ButPx.EnableWindow(m_RadPx3.GetCheck()&&m_CheckPx);
	m_ButCPx.EnableWindow(m_RadPx3.GetCheck()&&m_CheckPx);

	m_RadPx1.EnableWindow(m_CheckPx);
	m_RadPx2.EnableWindow(m_CheckPx);
	m_RadPx3.EnableWindow(m_CheckPx);

	m_CheckViewPx.ShowWindow(m_CheckPx?SW_SHOW:0);

	state = m_RadPy1.GetCheck()&&m_CheckPy;
	GetDlgItem(IDC_EDIT6)->EnableWindow(state);
	GetDlgItem(IDC_EDIT7)->EnableWindow(state);
	GetDlgItem(IDC_EDIT8)->EnableWindow(state);

	GetDlgItem(IDC_EDIT10)->EnableWindow(m_RadPy2.GetCheck()&&m_CheckPy);

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
	if (!VerifyInfo()) return;
	SetData();

	//????? ???????? ???? ?????????
	if (m_CheckViewPx.GetCheck())
	{
		int s=int((pKnot->ParamTime.T1-pKnot->ParamTime.T0)/pKnot->ParamTime.dT);
		if (s<2) s=3;

		CMatr Dat(2,s);
		int ret=pKnot->BeginIntegr(pKnot->ParamTime.T1);
		CProgressDlg *pDlg=new CProgressDlg(100,_T("?????????? Px(t)"));
		BOOL FlagExit=false;
		CString tmpstr;

		string strMsg;
		for (int i=0;i<s;i++)
		{
			double tmpx = i*pKnot->ParamTime.dT;
			if( pKnot->m_pSheme && pKnot->m_pSheme->m_bRichCalc )
			{
				tmpstr.Format("?????????? ????? %.16g", tmpx );
				pDlg->SetDetails(tmpstr);
			}
			Dat[0][i] = tmpx;
			Dat[1][i] = pKnot->GetPx(0,0,0,tmpx, &strMsg );
			if( pKnot->m_pSheme && pKnot->m_pSheme->m_bValidateExpr && !strMsg.empty() )
			{
				AfxMessageBox( CString("?????? ??? ?????????? ?????????: ") + strMsg.c_str() );
				break;
			}

			//????????? ?????????
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
		//????????? ?????????? ?? ???????????
		CString str;
		str.Format("??????? ?????????? Px(t). ???? ?%d",pKnot->Num);
		pGraphView->str_title=str;
		//????????? ????????? ?????? ???????????
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
		CProgressDlg *pDlg=new CProgressDlg(100,_T("?????????? Py(t)"));
		BOOL FlagExit=false;
		CString tmpstr;

		string strMsg;
		for (int i=0;i<s;i++)
		{
			double tmpx = i*pKnot->ParamTime.dT;
			if( pKnot->m_pSheme && pKnot->m_pSheme->m_bRichCalc )
			{
				tmpstr.Format("?????????? ????? %.16g", tmpx );
				pDlg->SetDetails(tmpstr);
			}
			Dat[0][i] = tmpx;
			Dat[1][i] = pKnot->GetPy(0,0,0,tmpx);
			if( pKnot->m_pSheme && pKnot->m_pSheme->m_bValidateExpr && !strMsg.empty() )
			{
				AfxMessageBox( CString("?????? ?? ?????????? ?????????: ") + strMsg.c_str() );
				break;
			}

			//????????? ?????????
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
		//????????? ?????????? ?? ???????????
		CString str;
		str.Format("??????? ?????????? Py(t). ???? ?%d",pKnot->Num);
		pGraphView->str_title=str;
		//????????? ????????? ?????? ???????????
		pGraphView->SetMaxMin();
		pNewFrame->SetWindowText(str);
		pGraphView->Dat.ReSize(2,Dat.SizeX);
		pGraphView->Dat=Dat;
	}
	//????? ?????? ????????********************

	CPropertyPage::OnOK();
}

BOOL CKnotPropertyPage3::VerifyInfo()
{
	UpdateData();

	if( m_RadPx2.GetCheck() )
	{
		CString mes;
		ASSERT(pKnot->m_pSheme);
		if( !pKnot->m_pSheme->m_VarsTable.IsValidExpr( m_EditPx, mes ) )
		{
			mes = _T("?????? ? ????????? Px:\n") + mes;
			AfxMessageBox( mes );
			return FALSE;
		}
	}

	if( m_RadPy2.GetCheck() )
	{
		CString mes;
		ASSERT(pKnot->m_pSheme);
		if( !pKnot->m_pSheme->m_VarsTable.IsValidExpr( m_EditPy, mes ) )
		{
			mes = _T("?????? ? ????????? Py:\n") + mes;
			AfxMessageBox( mes );
			return FALSE;
		}
	}
	return TRUE;
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
	m_EditUy = _T("");
	m_EditUx = _T("");
	m_EditAx = 0.0;
	m_EditWx = 0.0;
	m_EditFix = 0.0;
	m_EditAy = 0.0;
	m_EditWy = 0.0;
	m_EditFiy = 0.0;
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
	DDX_Control(pDX, IDC_RADIO4, m_RadUy2);
	DDX_Control(pDX, IDC_RADIO3, m_RadUy1);
	DDX_Control(pDX, IDC_RADIO2, m_RadUx2);
	DDX_Control(pDX, IDC_RADIO1, m_RadUx1);
	DDX_Check(pDX, IDC_CHECK1, m_CheckUx);
	DDX_Check(pDX, IDC_CHECK2, m_CheckUy);
	DDX_Text(pDX, IDC_EDIT10, m_EditUy);
	DDV_MaxChars(pDX, m_EditUy, 100);
	DDX_Text(pDX, IDC_EDIT5, m_EditUx);
	DDV_MaxChars(pDX, m_EditUx, 100);
	DDX_Text(pDX, IDC_EDIT1, m_EditAx);
	DDX_Text(pDX, IDC_EDIT2, m_EditWx);
	DDX_Text(pDX, IDC_EDIT3, m_EditFix);
	DDX_Text(pDX, IDC_EDIT6, m_EditAy);
	DDX_Text(pDX, IDC_EDIT7, m_EditWy);
	DDX_Text(pDX, IDC_EDIT8, m_EditFiy);
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

	BOOL state = m_RadUx1.GetCheck()&&m_CheckUx;
	GetDlgItem(IDC_EDIT1)->EnableWindow(state);
	GetDlgItem(IDC_EDIT2)->EnableWindow(state);
	GetDlgItem(IDC_EDIT3)->EnableWindow(state);
	GetDlgItem(IDC_EDIT5)->EnableWindow(m_RadUx2.GetCheck()&&m_CheckUx);

	m_ButUx.EnableWindow(m_RadUx3.GetCheck()&&m_CheckUx);
	m_ButCUx.EnableWindow(m_RadUx3.GetCheck()&&m_CheckUx);

	m_RadUx1.EnableWindow(m_CheckUx);
	m_RadUx2.EnableWindow(m_CheckUx);
	m_RadUx3.EnableWindow(m_CheckUx);
	
	m_CheckViewUx.ShowWindow(m_CheckUx?SW_SHOW:0);

	state = m_RadUy1.GetCheck()&&m_CheckUy;
	GetDlgItem(IDC_EDIT6)->EnableWindow(state);
	GetDlgItem(IDC_EDIT7)->EnableWindow(state);
	GetDlgItem(IDC_EDIT8)->EnableWindow(state);
	GetDlgItem(IDC_EDIT10)->EnableWindow(m_RadUy2.GetCheck()&&m_CheckUy);

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
	m_EditAx = pKnot->uAx;
	m_EditWx = pKnot->uWx;
	m_EditFix = pKnot->uFix;
	m_EditUx = pKnot->m_uUx.GetExpr().c_str();

	m_EditAy = pKnot->uAy;
	m_EditWy = pKnot->uWy;
	m_EditFiy = pKnot->uFiy;
	m_EditUy = pKnot->m_uUy.GetExpr().c_str();

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

	//????? ???????? ???? ?????????
	if (m_CheckViewUx.GetCheck())
	{
		int s=int((pKnot->ParamTime.T1-pKnot->ParamTime.T0)/pKnot->ParamTime.dT);
		if (s<2) s=3;

		CMatr Dat(2,s);
		int ret=pKnot->BeginIntegr(pKnot->ParamTime.T1);
		CProgressDlg *pDlg=new CProgressDlg(100,_T("?????????? Ux(t)"));
		BOOL FlagExit=false;
		CString tmpstr;

		string strMsg;
		for (int i=0;i<s;i++)
		{
			double tmpx = i*pKnot->ParamTime.dT;
			if( pKnot->m_pSheme && pKnot->m_pSheme->m_bRichCalc )
			{
				tmpstr.Format("?????????? ????? %.16g", tmpx );
				pDlg->SetDetails(tmpstr);
			}
			Dat[0][i] = tmpx;
			Dat[1][i] = pKnot->GetUx( 0.0, 0.0, 0.0, tmpx, &strMsg );
			if( pKnot->m_pSheme && pKnot->m_pSheme->m_bValidateExpr && !strMsg.empty() )
			{
				AfxMessageBox( CString("?????? ??? ?????????? ?????????: ") + strMsg.c_str() );
				break;
			}

			//????????? ?????????
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
		//????????? ?????????? ?? ???????????
		CString str;
		str.Format("?????????????? ?????????? Ux(t). ???? ?%d",pKnot->Num);
		pGraphView->str_title=str;
		//????????? ????????? ?????? ???????????
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
		CProgressDlg *pDlg=new CProgressDlg(100,_T("?????????? Uy(t)"));
		BOOL FlagExit=false;
		CString tmpstr;

		string strMsg;
		for (int i=0;i<s;i++)
		{
			double tmpx = i*pKnot->ParamTime.dT;
			if( pKnot->m_pSheme && pKnot->m_pSheme->m_bRichCalc )
			{
				tmpstr.Format("?????????? ????? %.16g", tmpx );
				pDlg->SetDetails(tmpstr);
			}
			Dat[0][i] = tmpx;
			Dat[1][i] = pKnot->GetUy( 0.0, 0.0, 0.0, tmpx, &strMsg );
			if( pKnot->m_pSheme && pKnot->m_pSheme->m_bValidateExpr && !strMsg.empty() )
			{
				AfxMessageBox( CString("?????? ??? ?????????? ?????????: ") + strMsg.c_str() );
				break;
			}

			//????????? ?????????
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
		//????????? ?????????? ?? ???????????
		CString str;
		str.Format("?????????????? ?????????? Uy(t). ???? ?%d",pKnot->Num);
		pGraphView->str_title=str;
		//????????? ????????? ?????? ???????????
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

	if (m_RadUx2.GetCheck())
	{
		CString mes;
		ASSERT(pKnot->m_pSheme);
		if( !pKnot->m_pSheme->m_VarsTable.IsValidExpr( m_EditUx, mes ) )
		{
			mes = _T("?????? ? ????????? Ux:\n") + mes;
			AfxMessageBox( mes );
			return FALSE;
		}
	}

	if (m_RadUy2.GetCheck())
	{
		CString mes;
		ASSERT(pKnot->m_pSheme);
		if( !pKnot->m_pSheme->m_VarsTable.IsValidExpr( m_EditUy, mes ) )
		{
			mes = _T("?????? ? ????????? Uy:\n") + mes;
			AfxMessageBox( mes );
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

	if( !m_bFull )	return true;
	return true;
}

BOOL CKnotPropertyPage2::VerifyInfo()
{
	UpdateData();

	CString mes;
	ASSERT(pKnot->m_pSheme);

	if( !pKnot->m_pSheme->m_VarsTable.IsValidExpr( m_EditUx, mes ) )
	{
		mes = _T("?????? ? ????????? Ux:\n") + mes;
		AfxMessageBox( mes );
		return FALSE;
	}
	if( !pKnot->m_pSheme->m_VarsTable.IsValidExpr( m_EditUy, mes ) )
	{
		mes = _T("?????? ? ????????? Uy:\n") + mes;
		AfxMessageBox( mes );
		return FALSE;
	}
	if( !pKnot->m_pSheme->m_VarsTable.IsValidExpr( m_EditUa, mes ) )
	{
		mes = _T("?????? ? ????????? Ua:\n") + mes;
		AfxMessageBox( mes );
		return FALSE;
	}
	if( !pKnot->m_pSheme->m_VarsTable.IsValidExpr( m_EditUxp, mes ) )
	{
		mes = _T("?????? ? ????????? Uxp:\n") + mes;
		AfxMessageBox( mes );
		return FALSE;
	}
	if( !pKnot->m_pSheme->m_VarsTable.IsValidExpr( m_EditUyp, mes ) )
	{
		mes = _T("?????? ? ????????? Uyp:\n") + mes;
		AfxMessageBox( mes );
		return FALSE;
	}
	if( !pKnot->m_pSheme->m_VarsTable.IsValidExpr( m_EditUap, mes ) )
	{
		mes = _T("?????? ? ????????? Uap:\n") + mes;
		AfxMessageBox( mes );
		return FALSE;
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
	
	pKnot->Ax = m_EditAx;
	pKnot->Wx = m_EditWx;
	pKnot->Fix = m_EditFix;
	ShemeExprErr er = pKnot->m_Px.Reset( m_EditPx );
	ASSERT( er == SEE_NOERR );

	pKnot->Ay = m_EditAy;
	pKnot->Wy = m_EditWy;
	pKnot->Fiy = m_EditFiy;
	er = pKnot->m_Py.Reset( m_EditPy );
	ASSERT( er == SEE_NOERR );


	if (m_RadPx1.GetCheck()) pKnot->TypePx=0;
	if (m_RadPx2.GetCheck()) pKnot->TypePx=1;
	if (m_RadPx3.GetCheck()) pKnot->TypePx=2;

	if (m_RadPy1.GetCheck()) pKnot->TypePy=0;
	if (m_RadPy2.GetCheck()) pKnot->TypePy=1;
	if (m_RadPy3.GetCheck()) pKnot->TypePy=2;

	pKnot->PxEnable = m_CheckPx;
	pKnot->PyEnable = m_CheckPy;

}

void CKnotPropertyPage4::SetData()
{
	UpdateData();
	
	pKnot->uAx = m_EditAx;
	pKnot->uWx = m_EditWx;
	pKnot->uFix = m_EditFix;
	ShemeExprErr er = pKnot->m_uUx.Reset( m_EditUx );
	ASSERT( er == SEE_NOERR );

	pKnot->uAy = m_EditAy;
	pKnot->uWy = m_EditWy;
	pKnot->uFiy = m_EditFiy;
	er = pKnot->m_uUy.Reset( m_EditUy );
	ASSERT( er == SEE_NOERR );


	if (m_RadUx1.GetCheck()) pKnot->TypeUx=0;
	if (m_RadUx2.GetCheck()) pKnot->TypeUx=1;
	if (m_RadUx3.GetCheck()) pKnot->TypeUx=2;

	if (m_RadUy1.GetCheck()) pKnot->TypeUy=0;
	if (m_RadUy2.GetCheck()) pKnot->TypeUy=1;
	if (m_RadUy3.GetCheck()) pKnot->TypeUy=2;

	pKnot->UxEnable=m_CheckUx;
	pKnot->UyEnable=m_CheckUy;

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

	ShemeExprErr er = pKnot->m_Ux.Reset( m_EditUx );
	ASSERT( er == SEE_NOERR );
	er = pKnot->m_Uy.Reset( m_EditUy );
	ASSERT( er == SEE_NOERR );
	er = pKnot->m_Ua.Reset( m_EditUa );
	ASSERT( er == SEE_NOERR );
	er = pKnot->m_Uxp.Reset( m_EditUxp );
	ASSERT( er == SEE_NOERR );
	er = pKnot->m_Uyp.Reset( m_EditUyp );
	ASSERT( er == SEE_NOERR );
	er = pKnot->m_Uap.Reset( m_EditUap );
	ASSERT( er == SEE_NOERR );

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
	
	if( !m_bFull )
	{
		pKnot->FixedType = m_FixedType.GetCurSel();
		return;
	}

	
	pKnot->SetCoord( m_EditX, m_EditY );
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
	CProgressDlg *pDlg=new CProgressDlg(100,_T("??????????"));
	BOOL FlagExit=false;

	for (int i=0;i<s;i++)
	{
		Dat[0][i]=i*dlg.Step;
		Dat[1][i]=pKnot->GetPy(0,0,i*dlg.Step);

		//????????? ?????????
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
	//????????? ?????????? ?? ???????????
	CString str;
	str.Format("?????? ???????? ?????????? Px. ???? ?%d",pKnot->Num);
	pGraphView->str_title=str;
	//????????? ????????? ?????? ???????????
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

