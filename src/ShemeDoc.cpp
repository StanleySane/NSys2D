// ShemeDoc.cpp : implementation of the CShemeDoc class
//

#include "stdafx.h"
#include "NSys2D.h"

#include "ShemeDoc.h"
#include "FormsView.h"
#include "FormsFrame.h"

#include "ElemDlg.h"
#include "PreCalcDlg.h"
#include "FreqViewDlg.h"

#include <fstream.h>

#include "ComplexSpectrDlg.h"
#include "ComplexMatr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShemeDoc

IMPLEMENT_DYNCREATE(CShemeDoc, CDocument)

BEGIN_MESSAGE_MAP(CShemeDoc, CDocument)
	//{{AFX_MSG_MAP(CShemeDoc)
	ON_COMMAND(ID_CALC, OnCalc)
	ON_COMMAND(ID_LISTELEM, OnListelem)
	ON_COMMAND(ID_FREEFORM_CALC, OnFreeformCalc)
	ON_COMMAND(ID_SCALEADD, OnScaleadd)
	ON_COMMAND(ID_SCALESUB, OnScalesub)
	ON_COMMAND(ID_REFRESH, OnRefresh)
	ON_COMMAND(ID_TEST, OnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CShemeDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CShemeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_INSys2D to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {09A14A84-BBAC-11D2-AF23-BB2B1C460D22}
static const IID IID_INSys2D =
{ 0x9a14a84, 0xbbac, 0x11d2, { 0xaf, 0x23, 0xbb, 0x2b, 0x1c, 0x46, 0xd, 0x22 } };

BEGIN_INTERFACE_MAP(CShemeDoc, CDocument)
	INTERFACE_PART(CShemeDoc, IID_INSys2D, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShemeDoc construction/destruction

CShemeDoc::CShemeDoc()
{
	m_pPropFrame = NULL;
	// TODO: add one-time construction code here
	ParamView.Scale=5;
	pProgressDlg=0;

	EnableAutomation();
	AfxOleLockApp();
}

CShemeDoc::~CShemeDoc()
{
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		CElem *el=listElem.GetNext(pos);
		if (el) delete el;
	}
	
	AfxOleUnlockApp();
}

/////////////////////////////////////////////////////////////////////////////
// CShemeDoc diagnostics

#ifdef _DEBUG
void CShemeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CShemeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShemeDoc commands

CElem* CShemeDoc::AddRod(CKnot * knot1, CKnot * knot2)
{
	CElem *prod;
	
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		prod=listElem.GetNext(pos);
		if ( ((prod->knot1==knot1)&&(prod->knot2==knot2))||
			 ((prod->knot1==knot2)&&(prod->knot2==knot1)) )
		{
			return prod;
		}
	}
	prod=new CRod(knot1,knot2);

	knot1->FriendCoord=knot2->GetCoord();
	knot2->FriendCoord=knot1->GetCoord();

	listElem.AddTail(prod);
	SetModifiedFlag();
	return prod;
}

CElem* CShemeDoc::AddDemf(CKnot * knot1, CKnot * knot2)
{
	CElem *demf;
	
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		demf=listElem.GetNext(pos);
		if ( ((demf->knot1==knot1)&&(demf->knot2==knot2))||
			 ((demf->knot1==knot2)&&(demf->knot2==knot1)) )
		{
			if (demf->TypeElem==IDC_SPRING) continue;			
			return demf;
		}
	}
	demf=new CDemf(knot1,knot2);
	listElem.AddTail(demf);
	SetModifiedFlag();
	return demf;
}

void CShemeDoc::ClearElem()
{
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		delete listElem.GetNext(pos);
	}
	listElem.RemoveAll();
}


void CShemeDoc::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code
		ar << listElem.GetCount();

		ParamView.Serialize(ar);
		ParamIntegr.Serialize(ar);
		ParamFreq.Serialize(ar);
		ParamSpectrOut.Serialize(ar);
		//CElem
		POSITION pos=listElem.GetHeadPosition();
		while (pos)
		{
			CElem *pElem=listElem.GetNext(pos);

			ar << pElem->TypeElem;
			pElem->Serialize(ar);
		}

		//Совместная спектральная плотность
		ar << listspectrP.GetCount();
		pos=listspectrP.GetHeadPosition();
		while (pos)
		{
			CComplexSpectr *pCS=(CComplexSpectr*)listspectrP.GetNext(pos);
			pCS->Serialize(ar);
		}
		//Совместная спектральная плотность
		ar << listspectrU.GetCount();
		pos=listspectrU.GetHeadPosition();
		while (pos)
		{
			CComplexSpectr *pCS=(CComplexSpectr*)listspectrU.GetNext(pos);
			pCS->Serialize(ar);
		}
	}
	else
	{	// loading code
		//ParamView
		int count;
		ar >> count;
		ParamView.Serialize(ar);
		ParamIntegr.Serialize(ar);
		ParamFreq.Serialize(ar);
		ParamSpectrOut.Serialize(ar);
		//CElem
		listKnot.Clear();
		ClearElem();

		for (int i=0;i<count;i++)
		{
			int TypeElem;
			ar >> TypeElem;
			

			switch (TypeElem)
			{
				case IDC_SPRING: 
					{
						
						CSpring *pSpring=new CSpring(0,0);
						pSpring->Serialize(ar);

						listElem.AddTail(pSpring);
						break;
					}
				case IDC_ROD:
					{
						CRod *pRod=new CRod(0,0);
						pRod->Serialize(ar);
						listElem.AddTail(pRod);
						break;
					}
				case IDC_DEMF:
					{
						CDemf *pDemf=new CDemf(0,0);
						pDemf->Serialize(ar);
						listElem.AddTail(pDemf);
						break;
					}
				case IDC_MASS:
					{
						CMass *pMass=new CMass(0);
						pMass->Serialize(ar);
						listElem.AddTail(pMass);
						break;
					}
			}
		}
		//Составление списка узлов с отсеиванием повторяющихся
		POSITION pos=listElem.GetHeadPosition();
		while (pos)
		{
			CElem *pElem=listElem.GetNext(pos);
			
			CKnot *pKn=listKnot.AddKnot(*(pElem->knot1));
			if (pKn!=pElem->knot1) 
				delete pElem->knot1;
			pElem->knot1=pKn;

			pKn=listKnot.AddKnot(*(pElem->knot2));
			if (pKn!=pElem->knot2) 
				delete pElem->knot2;
			pElem->knot2=pKn;
		}
		listKnot.ReNum();
		
		//Заполнение списка связей для стержней
		//Сначала проходим по всем элементам, а потом только через стержни
		SetConnectElements();

		//Совместная спектральная плотность
		ar >> count;
		listspectrP.Clear();
		for (i=0;i<count;i++)
		{
			CComplexSpectr *pCS=new CComplexSpectr;
			pCS->Serialize(ar);

			CKnot *pKn=listKnot.AddKnot(*(pCS->pKn1));
			if (pKn!=pCS->pKn1) 
				delete pCS->pKn1;
			pCS->pKn1=pKn;

			pKn=listKnot.AddKnot(*(pCS->pKn2));
			if (pKn!=pCS->pKn2) 
				delete pCS->pKn2;
			pCS->pKn2=pKn;
			
			listspectrP.AddTail(pCS);
		}
		//Совместная спектральная плотность
		ar >> count;
		listspectrU.Clear();
		for (i=0;i<count;i++)
		{
			CComplexSpectr *pCS=new CComplexSpectr;
			pCS->Serialize(ar);

			CKnot *pKn=listKnot.AddKnot(*(pCS->pKn1));
			if (pKn!=pCS->pKn1) 
				delete pCS->pKn1;
			pCS->pKn1=pKn;

			pKn=listKnot.AddKnot(*(pCS->pKn2));
			if (pKn!=pCS->pKn2) 
				delete pCS->pKn2;
			pCS->pKn2=pKn;
			
			listspectrU.AddTail(pCS);
		}
		listKnot.ReNum();
	}
    POSITION pos = GetFirstViewPosition();
    GetNextView(pos)->Serialize(ar);
}

CElem* CShemeDoc::AddSpring(CKnot * knot1, CKnot * knot2)
{
	CElem *sprn;
	
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		sprn=listElem.GetNext(pos);
		if ( ((sprn->knot1==knot1)&&(sprn->knot2==knot2))||
			 ((sprn->knot1==knot2)&&(sprn->knot2==knot1)) )
		{
			if (sprn->TypeElem==IDC_DEMF) continue;
			return sprn;
		}
	}
	sprn=new CSpring(knot1,knot2);
	listElem.AddTail(sprn);
	SetModifiedFlag();
	return sprn;
}

CElem* CShemeDoc::AddMass(CKnot * knot1)
{
	CElem *mass;
	
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		mass=listElem.GetNext(pos);
		if ( (mass->knot1==knot1)&&(mass->TypeElem==IDC_MASS) )
		{
			return mass;
		}
	}
	mass=new CMass(knot1);
	listElem.AddTail(mass);
	SetModifiedFlag();
	return mass;
}

int CShemeDoc::PreCalculated()
{
	int Count=UpdateAllFree();
	int code=SetMatrMDC(Count);
	if (code) return -1;
	
	//запрашиваем время, шаг и метод интегрирования 
	CPreCalcDlg dlg(&ParamIntegr);
	if (dlg.DoModal()!=IDOK) return -1;

	//Выделение памяти под массивы интегрирования
	//перемещение
	int cntstep=int(ceil(ParamIntegr.Time/ParamIntegr.Step)+1);
	matr_RezY1.ReSize(Count,cntstep);
	//скорость
	matr_RezY2.ReSize(Count,cntstep);
	if (ParamIntegr.TypeMethod==2) matr_RezY3.ReSize(Count,cntstep);
	else matr_RezY3.ReSize(1,1);
	
	//Подготовка для интегрирования со случайным возмущением
	POSITION pos=listKnot.GetHeadPosition();
	while (pos)
	{
		//проходим по всем элементам
		CKnot *kn=listKnot.GetNext(pos);
		kn->BeginIntegr(ParamIntegr.Time);
	}

	//установка начальных условий
	BeginWaitCursor();
	SetBeginPosition();
	EndWaitCursor();
	return 0;
}

void CShemeDoc::OnCalc() 
{
	// TODO: Add your command handler code here
	if (PreCalculated()) return;

 	pProgressDlg=new CProgressDlg(100, _T("Интегрирование"));

	int code;
	switch (ParamIntegr.TypeMethod)
	{
	case 0: code=RungeKutt(matr_RezY1.SizeX); break;
	case 1: code=Park(matr_RezY1.SizeX); break;
	case 2: code=Numark(matr_RezY1.SizeX); break;
	};

	//if (code) //Интегрирование было прервано
	pProgressDlg->DestroyWindow();
	pProgressDlg=0;

	AfterCalc();
	UpdateAllViews(0);
}

void CShemeDoc::OnListelem() 
{
	// TODO: Add your command handler code here
	CElemDlg dlg(&listElem,&listKnot);
	dlg.DoModal();
	UpdateAllViews(0);
}

void CShemeDoc::OnProperties()
{
	// TODO: The property sheet attached to your project
	// via this function is not hooked up to any message
	// handler.  In order to actually use the property sheet,
	// you will need to associate this function with a control
	// in your project such as a menu item or tool bar button.
	//
	// If mini frame does not already exist, create a new one.
	// Otherwise, unhide it

	if (m_pPropFrame == NULL)
	{
		m_pPropFrame = new CKnotPropertyFrame;
		CRect rect(0, 0, 0, 0);
		CString strTitle;
		VERIFY(strTitle.LoadString(IDS_PROPSHT_CAPTION1));

		// TODO: Warning: Your base class isn't a CWnd type
		// so the menu will be created with a parent HWND of NULL.
		if (!m_pPropFrame->Create(NULL, strTitle,
			MFS_THICKFRAME|WS_POPUP | WS_CAPTION | WS_SYSMENU, rect))
		{
			delete m_pPropFrame;
			m_pPropFrame = NULL;
			return;
		}
		m_pPropFrame->CenterWindow();
	}

	// Before unhiding the modeless property sheet, update its
	// settings appropriately.  For example, if you are reflecting
	// the state of the currently selected item, pick up that
	// information from the active view and change the property
	// sheet settings now.

	if (m_pPropFrame != NULL && !m_pPropFrame->IsWindowVisible())
		m_pPropFrame->ShowWindow(SW_SHOW);
}

//Интегрирование методом Рунге-Кутта (nStep - число шагов плюс один)
int CShemeDoc::RungeKutt(int nStep)
{
	CMatr mMD(matr_M.SizeY,matr_M.SizeX);
	CMatr mMC(matr_M.SizeY,matr_M.SizeX);
	CMatr mP(matr_M.SizeY,1);

	mMD=matr_M_1*matr_D;
	mMC=matr_M_1*matr_C;

	double h=ParamIntegr.Step;
	double mult=(h + h*h/2.0 + h*h*h/6.0 + h*h*h*h/24.0)*(-1.0);

	BOOL FlagExit;
	for (int i=1; i<nStep;i++)
	{
		//Обработка сообщений
		MSG msg;
		FlagExit=false;
		while (PeekMessage(&msg, pProgressDlg->m_Button.m_hWnd, WM_KEYDOWN, WM_LBUTTONUP, PM_REMOVE))   // Until WM_QUIT message
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
		pProgressDlg->SetPos(int(100.0*i/nStep));

		//Очистка вектора правых частей
		mP.ClearData();

		POSITION pos=listElem.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CElem *elem=listElem.GetNext(pos);
	//		if ( (elem->TypeElem==IDC_DEMF)||(elem->TypeElem==IDC_SPRING) )
				if (elem->SetMatrmP(mP, matr_RezY1, matr_RezY2, i-1, ParamIntegr.Step*i)) 
				{
					AfxMessageBox("Ошибка в вычислении выражения");
					return -1;
				}
		}
		pos=listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CKnot *knot=listKnot.GetNext(pos);
			if (knot->SetMatrmP(mP, matr_RezY1, matr_RezY2, i-1, ParamIntegr.Step*i, matr_UM, matr_UD, matr_UC)) 
			{
				AfxMessageBox("Ошибка в вычислении выражения");
				return -1;
			}
		}
		pos=listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CKnot *knot=listKnot.GetNext(pos);
			if (knot->SetMatrmP(mP, ParamIntegr.Step*i)) 
			{
				AfxMessageBox("Ошибка в вычислении выражения");
				return -1;
			}
		}
		
		
		matr_RezY2.CopyVectTo(
			(mMD.MultOnCol(matr_RezY2,i-1)-matr_M_1*mP+
			       mMC.MultOnCol(matr_RezY1,i-1))*mult,i);
		
		for (int j=0; j<matr_RezY1.SizeY;j++)
		{
			matr_RezY1[j][i]=matr_RezY1[j][i-1]+matr_RezY2[j][i-1]*(-mult);
			matr_RezY2[j][i]+=matr_RezY2[j][i-1];
		}

		if (UEnable)
		{
			//Установка кинематических перемещений и скоростей
			pos=listKnot.GetHeadPosition();
			while (pos)
			{
				//проходим по всем узлам
				CKnot *knot=listKnot.GetNext(pos);
				if (knot->SetKinematicPos(matr_RezY1,matr_RezY2, i, ParamIntegr.Step*i)) 
				{
					AfxMessageBox("Ошибка при вычислении выражения");
					return -1;
				}
			}
		}
	}
	return (FlagExit?-1:0);
}

int CShemeDoc::Park(int nStep)
{
	//Стартуем методом Рунге-Кутта
	//Измельчение шага для увеличения точности
	int ReduceStep=nStep/3;
	if (ReduceStep>5) ReduceStep=5;
	double h=ParamIntegr.Step;
	ParamIntegr.Step=h/ReduceStep;
//	RungeKutt(3*ReduceStep);
	matr_RezY3.ReSize(matr_RezY1.SizeY,3*ReduceStep+1);
	int exitcode=Numark(3*ReduceStep);
	matr_RezY3.ReSize(1,1);

	for (int k=0;k<3;k++)
		for (int i=0;i<matr_RezY1.SizeY;i++)
		{
			matr_RezY1[i][k]=matr_RezY1[i][k*ReduceStep];
			matr_RezY2[i][k]=matr_RezY2[i][k*ReduceStep];
		}
	ParamIntegr.Step=h;
	if (exitcode) return -1;
	//RungeKutt(5);
	//Numark(5);

	//находим обратную матрицу левой части системы уравнений
	CMatr mM_1(matr_M.SizeY,matr_M.SizeX);
	int code;
	mM_1=(matr_M*(100.0/36.0/ParamIntegr.Step/ParamIntegr.Step)+matr_D*(10.0/6.0/ParamIntegr.Step)+matr_C).GetInvert(code);
	if (!code)
	{
		AfxMessageBox( _T("Ошибка в схеме."),
						MB_OK|MB_ICONSTOP);
		return -1;
	}

	CMatr mP(matr_M.SizeY,1);
	CMatr mF(matr_M.SizeY,1);
	
	BOOL FlagExit;
	for (int i=2;i<(nStep-1);i++)
	{
		//Обработка сообщений
		MSG msg;
		FlagExit=false;
		while (PeekMessage(&msg, pProgressDlg->m_Button.m_hWnd, WM_KEYDOWN, WM_LBUTTONUP, PM_REMOVE))   // Until WM_QUIT message
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
		pProgressDlg->SetPos(int(100.0*i/nStep));

		//Заполняем вектор нелинейной части
		mP.ClearData();

		//проходим по всем элементам
		POSITION pos=listElem.GetHeadPosition();
		while (pos)
		{
			CElem *elem=listElem.GetNext(pos);
			//if ( (elem->TypeElem==IDC_DEMF)||(elem->TypeElem==IDC_SPRING) )
				if (elem->SetMatrmP(mP, matr_RezY1, matr_RezY2, i, ParamIntegr.Step*(i+1))) 
				{
					AfxMessageBox("Ошибка при вычислении выражения");
					return -1;
				}
		}
		pos=listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CKnot *knot=listKnot.GetNext(pos);
			if (knot->SetMatrmP(mP, matr_RezY1, matr_RezY2, i-1, ParamIntegr.Step*i, matr_UM, matr_UD, matr_UC)) 
			{
				AfxMessageBox("Ошибка при вычислении выражения");
				return -1;
			}
		}
		pos=listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CKnot *knot=listKnot.GetNext(pos);
			if (knot->SetMatrmP(mP, ParamIntegr.Step*i)) 
			{
				AfxMessageBox("Ошибка при вычислении выражения");
				return -1;
			}
		}

		mF=matr_M.MultOnCol(matr_RezY2,i)*(15.0/6.0/ParamIntegr.Step)-
			matr_M.MultOnCol(matr_RezY2,i-1)*(1.0/ParamIntegr.Step)+
			matr_M.MultOnCol(matr_RezY2,i-2)*(1.0/6.0/ParamIntegr.Step)+
			
			(matr_M*(150.0/36.0/ParamIntegr.Step/ParamIntegr.Step)+
			matr_D*(15.0/6.0/ParamIntegr.Step)).MultOnCol(matr_RezY1,i)-

			(matr_M*(10.0/6.0/ParamIntegr.Step/ParamIntegr.Step)+
			matr_D*(1.0/ParamIntegr.Step)).MultOnCol(matr_RezY1,i-1)+

			(matr_M*(10.0/36.0/ParamIntegr.Step/ParamIntegr.Step)+
			matr_D*(1.0/6.0/ParamIntegr.Step)).MultOnCol(matr_RezY1,i-2)+
			mP;

		matr_RezY1.CopyVectTo(mM_1*mF,i+1);

		for (int j=0;j<matr_RezY2.SizeY;j++)
			matr_RezY2[j][i+1]=(10*matr_RezY1[j][i+1]-15*matr_RezY1[j][i]+6*matr_RezY1[j][i-1]-matr_RezY1[j][i-2])/6.0/ParamIntegr.Step;

		if (UEnable)
		{
			//Установка кинематических перемещений и скоростей
			pos=listKnot.GetHeadPosition();
			while (pos)
			{
				//проходим по всем узлам
				CKnot *knot=listKnot.GetNext(pos);
				if (knot->SetKinematicPos(matr_RezY1,matr_RezY2, i+1, ParamIntegr.Step*(i+1))) 
				{
					AfxMessageBox("Ошибка при вычислении выражения");
					return -1;
				}
			}
		}
	}
	return (FlagExit?-1:0);
}

int CShemeDoc::Numark(int nStep)
{
	double alpha=0.5;
	double betta=0.25;
	double m_Step=ParamIntegr.Step;
		
	CMatr mMpr(matr_M.SizeY,matr_M.SizeX);
	CMatr mP(matr_M.SizeY,1);

	mMpr=matr_M*(1.0/(betta*m_Step*ParamIntegr.Step)) + matr_D*(alpha/(betta*m_Step)) + matr_C;
	int code;
	mMpr=mMpr.GetInvert(code);
	if (!code)
	{
		AfxMessageBox("Ошибка при решении системы уравнений");
		return -1;
	}
	//CMatr matr_RezY3(matr_RezY1.SizeY, 1);
	matr_RezY3.ClearData();
	BOOL FlagExit;
	for (int i=1; i<nStep;i++)
	{
		//Обработка сообщений
		MSG msg;
		FlagExit=false;
		while (PeekMessage(&msg, pProgressDlg->m_Button.m_hWnd, WM_KEYDOWN, WM_LBUTTONUP, PM_REMOVE))   // Until WM_QUIT message
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
		pProgressDlg->SetPos(int(100.0*i/nStep));


		//Очистка вектора правых частей
		mP.ClearData();

		POSITION pos=listElem.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CElem *elem=listElem.GetNext(pos);
			//if ( (elem->TypeElem==IDC_DEMF)||(elem->TypeElem==IDC_SPRING) )
				if (elem->SetMatrmP(mP, matr_RezY1, matr_RezY2, i-1, m_Step*i)) 
				{
					AfxMessageBox("Ошибка в вычислении выражения");
					return -1;
				}
		}
		pos=listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем узлам
			CKnot *knot=listKnot.GetNext(pos);
			if (knot->SetMatrmP(mP, matr_RezY1, matr_RezY2, i-1, m_Step*i, matr_UM, matr_UD, matr_UC)) 
			{
				AfxMessageBox("Ошибка при вычислении выражения");
				return -1;
			}
		}
		pos=listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем узлам
			CKnot *knot=listKnot.GetNext(pos);
			if (knot->SetMatrmP(mP, m_Step*i)) 
			{
				AfxMessageBox("Ошибка при вычислении выражения");
				return -1;
			}
		}

		
		matr_RezY1.CopyVectTo(
			mMpr*(
			(matr_M*(1.0/(2.0*betta)-1) + matr_D*m_Step*(alpha/(2.0*betta)-1)).MultOnCol(matr_RezY3,i-1)+
			(matr_M*(1.0/(betta*m_Step)) + matr_D*(alpha/betta-1)).MultOnCol(matr_RezY2,i-1)+
			(matr_M*(1.0/(betta*m_Step*m_Step)) + matr_D*(alpha/(betta*m_Step))).MultOnCol(matr_RezY1,i-1)
			+mP),
			i);

		for (int j=0;j<matr_RezY2.SizeY;j++)
		{
			matr_RezY2[j][i]=(matr_RezY1[j][i]-matr_RezY1[j][i-1])*(alpha/(betta*m_Step))-
							  matr_RezY2[j][i-1]*(alpha/betta-1)-
							  matr_RezY3[j][i-1]*m_Step*(alpha/(2.0*betta)-1);

			matr_RezY3[j][i]=(matr_RezY1[j][i]-matr_RezY1[j][i-1])*(1.0/(betta*m_Step*m_Step))-
							  matr_RezY2[j][i-1]*(1.0/(betta*m_Step))-
							  matr_RezY3[j][i-1]*(1.0/(2.0*betta)-1.0);
		}
		if (UEnable)
		{
			//Установка кинематических перемещений и скоростей
			POSITION pos=listKnot.GetHeadPosition();
			while (pos)
			{
				//проходим по всем узлам
				CKnot *knot=listKnot.GetNext(pos);
				if (knot->SetKinematicPos(matr_RezY1,matr_RezY2, i, m_Step*i)) 
				{
					AfxMessageBox("Ошибка при вычислении выражения");
					return -1;
				}
			}
		}
	}
	return (FlagExit?-1:0);
}

//Вроде уже не используется
void CShemeDoc::SetConnectElements()
{
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		CElem *pElem=listElem.GetNext(pos);
		pElem->knot1->FriendCoord=pElem->knot2->GetCoord();
		pElem->knot2->FriendCoord=pElem->knot1->GetCoord();
	}
	pos=listElem.GetHeadPosition();
	while (pos)
	{
		CElem *pElem=listElem.GetNext(pos);
		if (pElem->TypeElem==IDC_ROD)
		{
			pElem->knot1->FriendCoord=pElem->knot2->GetCoord();
			pElem->knot2->FriendCoord=pElem->knot1->GetCoord();
		}
	}
}

void CShemeDoc::AfterCalc()
{
	matr_UM.Clear();
	matr_UD.Clear();
	matr_UC.Clear();

	POSITION pos=listKnot.GetHeadPosition();
	while (pos)
	{
		//проходим по всем узлам
		CKnot *kn=listKnot.GetNext(pos);
		kn->EndIntegr();
	}
}


int CShemeDoc::UpdateAllFree()
{
	//чистим узлы
	POSITION pos=listKnot.GetHeadPosition();
	while (pos)
	{
		CKnot *knot=listKnot.GetNext(pos);
		knot->nXRez=-1;
		knot->nYRez=-1;
		for (int i=0;i<knot->CntAngle;i++)
			knot->nARez[i]=-1;
	}

	//Проставляем -2 на используемых степенях свободы
	pos=listElem.GetHeadPosition();
	while (pos)
	{
		CElem *elem=listElem.GetNext(pos);
		elem->knot1->nXRez=-2;
		elem->knot1->nYRez=-2;
		elem->knot2->nXRez=-2;
		elem->knot2->nYRez=-2;
		if (elem->TypeElem==IDC_ROD)
		{
			CRod *rod=(CRod*)elem;
			//Если шарнирно, то 
			rod->FreeA1=0;
			rod->FreeA2=0;

			if (rod->knot1->ConnectType!=0) 
			{
				for (int i=0;i<rod->knot1->CntAngle;i++)
					if (rod->knot1->nARez[i]==-1) 
					{
						rod->knot1->nARez[i]=-2;
						rod->FreeA1=i;
						break;
					}
			}
			else 
			{
				rod->knot1->nARez[0]=-2;
			}

			if (rod->knot2->ConnectType!=0) 
			{
				for (int i=0;i<rod->knot2->CntAngle;i++)
					if (rod->knot2->nARez[i]==-1) 
					{
						rod->knot2->nARez[i]=-2;
						rod->FreeA2=i;
						break;
					}
			}
			else 
			{
				rod->knot2->nARez[0]=-2;
			}
		}
		if (elem->TypeElem==IDC_MASS)
		{
			CMass *mas=(CMass*)elem;
			if (mas->GetJp()>0) 
				mas->knot1->nARez[0]=-2;
		}
	}
	
	//устанавливаем связи для закрепленных степеней свободы
	pos=listKnot.GetHeadPosition();
	while (pos)
	{
		//проходим по всем элементам
		CKnot *kn=listKnot.GetNext(pos);
		kn->SetFixedKnot();
	}
	
	//считаем степени свободы и
	//заполняем номера степеней свободы
	int Count=0;
	pos=listKnot.GetHeadPosition();
	while (pos)
	{
		CKnot *knot=listKnot.GetNext(pos);
		if (knot->nXRez==-2) knot->nXRez=Count++;
		if (knot->nYRez==-2) knot->nYRez=Count++;
		for (int i=0;i<knot->CntAngle;i++)
			if (knot->nARez[i]==-2) knot->nARez[i]=Count++;
	}
	return Count;
}

int CShemeDoc::SetMatrMDC(int Count, int Freq/*=0*/)
{
	if (Count==0) return -1;

	//выделяем память
	matr_M.ReSize(Count,Count);
	matr_M_1.ReSize(Count,Count);
	matr_C.ReSize(Count,Count);
	matr_D.ReSize(Count,Count);

	//заполняем матрицы
	POSITION pos=listElem.GetHeadPosition();
	while (pos)
	{
		//проходим по всем элементам
		CElem *elem=listElem.GetNext(pos);
		elem->SetMatrMDC(matr_M, matr_D, matr_C);
	}
	//проверка диагонали матрицы matr_C (можно убрать)
	for (int i=0;i<Count;i++)
	{
		if (matr_C[i][i]==0) 
		{
			CString str;
			str.Format("Нулевая жесткость в узле № %d",listKnot.FindNum(i));
			AfxMessageBox( str, MB_OK|MB_ICONINFORMATION);

			//return -1;
			break;
		}
	}
	//среднее диагональных элементов
	double avC=0, avD=0, avM=0;
	for (int t=0;t<matr_C.SizeY;t++)
	{
		avC+=matr_C[t][t];
		avD+=matr_D[t][t];
		avM+=matr_M[t][t];
	}
	avC/=matr_C.SizeY;	avD/=matr_D.SizeY;	avM/=matr_M.SizeY;
	if (avC==0) avC=1;
	if (avM==0) avM=1;
	
	if (!Freq)
	{
		//Поиск и подсчет кинематических возмущений
		int CntU=0;
		pos=listKnot.GetHeadPosition();
		while (pos)
		{
			CKnot *knot=listKnot.GetNext(pos);
			if ((knot->nXRez>=0)&&(knot->UxEnable)) knot->nXU=CntU++;
			else knot->nXU=-1;
			if ((knot->nYRez>=0)&&(knot->UyEnable)) knot->nYU=CntU++;
			else knot->nYU=-1;
		}
		UEnable=false;
		if (CntU>0)
		{
			//Устанавливаем флаг использования кинематического возмущения
			UEnable=true;
			
			//matr_UM.ReSize(Count, CntU);
			matr_UD.ReSize(Count, CntU);
			matr_UC.ReSize(Count, CntU);

			//Делаем копии нужных столбцов матрицы
			pos=listKnot.GetHeadPosition();
			while (pos)
			{
				CKnot *knot=listKnot.GetNext(pos);
				if (knot->nXU>=0) 
				{
					for (int i=0;i<matr_C.SizeY;i++)
					{
						matr_UD[i][knot->nXU]=matr_D[i][knot->nXRez];
						matr_UC[i][knot->nXU]=matr_C[i][knot->nXRez];
					}
				}
				if (knot->nYU>=0) 
				{
					for (int i=0;i<matr_C.SizeY;i++)
					{
						matr_UD[i][knot->nYU]=matr_D[i][knot->nYRez];
						matr_UC[i][knot->nYU]=matr_C[i][knot->nYRez];
					}
				}
			}

			//Чистим основные матицы
			pos=listKnot.GetHeadPosition();
			while (pos)
			{
				CKnot *knot=listKnot.GetNext(pos);
				if (knot->nXU>=0) 
				{
					for (int i=0;i<matr_C.SizeY;i++)
					{
						matr_C[i][knot->nXRez]=0;
						matr_C[knot->nXRez][i]=0;

						matr_D[i][knot->nXRez]=0;
						matr_D[knot->nXRez][i]=0;

						matr_M[i][knot->nXRez]=0;
						matr_M[knot->nXRez][i]=0;
					}
					matr_C[knot->nXRez][knot->nXRez]=avC;
					matr_D[knot->nXRez][knot->nXRez]=avD;
					matr_M[knot->nXRez][knot->nXRez]=avM;
				}
				if (knot->nYU>=0) 
				{
					for (int i=0;i<matr_C.SizeY;i++)
					{
						matr_C[i][knot->nYRez]=0;
						matr_C[knot->nYRez][i]=0;

						matr_D[i][knot->nYRez]=0;
						matr_D[knot->nYRez][i]=0;

						matr_M[i][knot->nYRez]=0;
						matr_M[knot->nYRez][i]=0;
					}
					matr_C[knot->nYRez][knot->nYRez]=avC;
					matr_D[knot->nYRez][knot->nYRez]=avD;
					matr_M[knot->nYRez][knot->nYRez]=avM;
				}
			}
		}
	}
	//Проверяем степени свободы с кинематическим возмущением
	pos=listKnot.GetHeadPosition();
	while (pos)
	{
		CKnot *knot=listKnot.GetNext(pos);
		if ((knot->nXRez>=0)&&(knot->UxEnable>=0)) 
		{
			if (matr_C[knot->nXRez][knot->nXRez]==0) 
				matr_C[knot->nXRez][knot->nXRez]=avC;
			if (matr_D[knot->nXRez][knot->nXRez]==0) 
				matr_D[knot->nXRez][knot->nXRez]=avD;
			if (matr_M[knot->nXRez][knot->nXRez]==0) 
				matr_M[knot->nXRez][knot->nXRez]=avM;
		}
		if ((knot->nYRez>=0)&&(knot->UyEnable>=0)) 
		{
			if (matr_C[knot->nYRez][knot->nYRez]==0) 
				matr_C[knot->nYRez][knot->nYRez]=avC;
			if (matr_D[knot->nYRez][knot->nYRez]==0) 
				matr_D[knot->nYRez][knot->nYRez]=avD;
			if (matr_M[knot->nYRez][knot->nYRez]==0) 
				matr_M[knot->nYRez][knot->nYRez]=avM;
		}
	}

	//Ищем обратную матрицу
	int code;
	
	CMatr TempM(matr_M.SizeY,matr_M.SizeX);
	TempM=matr_M;
	matr_M_1=TempM.GetInvert(code);
	if (!code)
	{
		AfxMessageBox( _T("Ошибка в схеме."),MB_OK|MB_ICONSTOP);
		return -1;
	}
	return 0;
}

int CShemeDoc::SetBeginPosition()
{
	POSITION pos=listKnot.GetHeadPosition();
	while (pos)
	{
		//проходим по всем элементам
		CKnot *kn=listKnot.GetNext(pos);
		if (kn->nXRez>=0) 
		{
			matr_RezY1[kn->nXRez][0]=kn->GetUx(0);
			matr_RezY2[kn->nXRez][0]=kn->GetUx(0,1);
		}
		if (kn->nYRez>=0) 
		{
			matr_RezY1[kn->nYRez][0]=kn->GetUy(0);
			matr_RezY2[kn->nYRez][0]=kn->GetUy(0,1);
		}
		for (int i=0;i<kn->CntAngle;i++)
			if (kn->nARez[i]>=0)
			{
				matr_RezY1[kn->nARez[i]][0]=kn->GetUa();
				matr_RezY2[kn->nARez[i]][0]=kn->GetUa(1);
			}
	}
	return 0;
}

void CShemeDoc::OnFreeformCalc() 
{
	// TODO: Add your command handler code here
/*	int Count=UpdateAllFree();
	int code=SetMatrMDC(Count);
	if (code) return;

	CMatr F(matr_C.SizeY, matr_C.SizeX), Matr_Forms(matr_C.SizeX, matr_C.SizeX);
	F=matr_M_1*matr_C;
	//Вычисление собственных частот и форм колебений методом Якоби
	code=F.Eigen(&Matr_Forms);
	if (code<0) 
	{
		AfxMessageBox( _T("Процесс нахождения собственных частот не сходится."),MB_OK|MB_ICONSTOP);
		return;
	}

	//Нормирование форм
	for (int i=0;i<Matr_Forms.SizeY;i++)
	{
		double maxU=0;
		POSITION pos=listKnot.GetHeadPosition();
		while (pos)
		{
			CKnot *kn=listKnot.GetNext(pos);
			if (kn->nXRez>=0) 
			{
				double uu=Matr_Forms[kn->nXRez][i];
				if (fabs(uu)>fabs(maxU)) maxU=uu;
			}
			if (kn->nYRez>=0)
			{
				double uu=Matr_Forms[kn->nYRez][i];
				if (fabs(uu)>fabs(maxU)) maxU=uu;
			}
		}
		if (maxU!=0)
			for (int j=0;j<Matr_Forms.SizeY;j++)
				Matr_Forms[j][i]/=maxU/20.0;
	}
	//Извлекаем корень из квадратов частот и записываем в первую строку
	for (i=0;i<F.SizeY;i++)
		F[0][i]=sqrt(F[i][i]);
	//Сортируем формы по возрастанию частот
	for (i=0;i<F.SizeX-1;i++)
		for (int j=i+1;j<F.SizeX;j++)
			if ( sqrt(F[0][i])>sqrt(F[0][j]) )
			{
				double tmp=F[0][i];
				F[0][i]=F[0][j];
				F[0][j]=tmp;
				for (int k=0;k<Matr_Forms.SizeY;k++)
				{
					tmp=Matr_Forms[k][i];
					Matr_Forms[k][i]=Matr_Forms[k][j];
					Matr_Forms[k][j]=tmp;
				}
			}*/

	//Открытие окна с формами
	
	//Заполнение внутреннего окна
	//Заполнение внутреннего массива графика
	//Создание окна с графиком и присоединение его к документу
	CString str;
	str=GetTitle();

	str+=_T("  Собственные формы колебений");
//		str2.Format(" (Узел №%d) ",SelKnot->Num);

	CNSys2DApp* pApp=(CNSys2DApp*)AfxGetApp();

	POSITION pos = pApp->GetFirstDocTemplatePosition();
	pApp->GetNextDocTemplate(pos);
	pApp->GetNextDocTemplate(pos);

	CDocTemplate *pTemplate = pApp->GetNextDocTemplate(pos);

	//CMDIChildWnd* 
	CFormsFrame *pNewFrame	= (CFormsFrame*)(pTemplate->CreateNewFrame(this, NULL));
	ASSERT(pNewFrame!=NULL);
	
	//Устанавливаем размер фрейма как у схемы (у первого представления)
	CRect rect;

	pos = GetFirstViewPosition();
	CView* pView = GetNextView(pos);
	pView-> GetOwner()->GetWindowRect(&rect);//((CMDIChildWnd*)
	rect.OffsetRect(rect.Width(),0);
	if (rect.Width()<325) rect.right=rect.left+325;
	pNewFrame->MoveWindow(&rect);

	
	pTemplate->InitialUpdateFrame(pNewFrame, this);

	CFormsView *pFormsView = (CFormsView*)pNewFrame->GetActiveView();
	ASSERT (pFormsView != NULL);

	pNewFrame->SetWindowText(str);

	//Копируем данные
/*	pFormsView->matr_Forms.ReSize(Matr_Forms.SizeY,Matr_Forms.SizeX);
	pFormsView->matr_Forms=Matr_Forms;

	pFormsView->matr_Freq.ReSize(1, F.SizeY);
	for (i=0;i<F.SizeY;i++)
		pFormsView->matr_Freq[0][i]=F[0][i];

	pFormsView->SetForm(0);*/

	UpdateAllViews(0);
}

void CShemeDoc::OnScaleadd() 
{
	// TODO: Add your command handler code here
	ParamView.Scale*=sqrt(2);
	UpdateAllViews(0);
}

void CShemeDoc::OnScalesub() 
{
	// TODO: Add your command handler code here
	ParamView.Scale/=sqrt(2);
	UpdateAllViews(0);
}

void CShemeDoc::OnRefresh() 
{
	// TODO: Add your command handler code here
	UpdateAllViews(0);
}

int CShemeDoc::DelFreeKnot()
{
	POSITION pos_old, pos=listKnot.GetHeadPosition();
	while (pos)
	{
		pos_old=pos;
		CKnot *kn=listKnot.GetNext(pos);
		BOOL busy=false;
		POSITION pos2=listElem.GetHeadPosition();
		while (pos2)
		{
			CElem *elem=listElem.GetNext(pos2);
			if ((elem->knot1==kn)||(elem->knot2==kn))
				busy=true;
		}
		if (!busy)
			listKnot.RemoveAt(pos_old);
	}
	return 0;
}


void CShemeDoc::OnTest() 
{
	// TODO: Add your command handler code here
	int Count=UpdateAllFree();
	int code=SetMatrMDC(Count);
//	if (code) return;

	matr_C.SaveToFile("mC");
	matr_D.SaveToFile("mD");
	matr_M.SaveToFile("mM");

/*	int s=matr_C.SizeY;
	double w=10;
	CComplexMatr C(s,s);
	C.UnitMatr(matr_C - matr_M*(w*w),matr_D*w);
	int flag;
	C=C.GetInvert(flag);
	C.SaveToFileRe("mC_Re");
	C.SaveToFileIm("mC_Im");*/
}
