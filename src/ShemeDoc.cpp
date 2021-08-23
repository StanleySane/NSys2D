// ShemeDoc.cpp : implementation of the CShemeDoc class
//

#include "stdafx.h"
#include "NSys2D.h"

#include "ShemeDoc.h"
#include "FormsView.h"
#include "FormsFrame.h"
#include "GraphicView.h"
#include "ScriptView.h"
#include "ScriptFrame.h"

#include "ElemDlg.h"
#include "PreCalcDlg.h"
#include "FreqViewDlg.h"
#include "EVMDialog.h"
#include "ViewStyles.h"
#include "NewGroupDlg.h"
#include "GroupListDlg.h"
#include "GroupPreviewDlg.h"
#include "GroupEditDlg.h"
#include "ConvertToDlg.h"
#include "EqualDegrees.h"
#include "Sheme.h"

#include <fstream.h>

#include "ComplexSpectrDlg.h"
#include "ComplexMatr.h"

#include<algorithm>
using namespace std;

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
	ON_COMMAND(ID_SHEME_PARAMS, OnShemeParams)
	ON_COMMAND(ID_VIEW_STYLES, OnViewStyles)
	ON_UPDATE_COMMAND_UI(ID_FREEFORM_CALC, OnUpdateFreeformCalc)
	ON_COMMAND(ID_GROUP_NEW, OnGroupNew)
	ON_COMMAND(ID_GROUP_LIST, OnGroupList)
	ON_COMMAND(ID_ELEMGROUP_DEL, OnGroupElemDel)
	ON_COMMAND(ID_ELEMGROUP_PROP, OnGroupElemProp)
	ON_COMMAND(ID_GROUP_PREVIEW, OnGroupPreview)
	ON_COMMAND(ID_ALL_DEMF, OnAllDemf)
	ON_COMMAND(ID_ALL_HARDRODS, OnAllHardRods)
	ON_COMMAND(ID_ALL_MASSES, OnAllMasses)
	ON_COMMAND(ID_ALL_RODS, OnAllRods)
	ON_COMMAND(ID_ALL_SPRINGS, OnAllSprings)
	ON_COMMAND(ID_GROUP_CONVERT_TO, OnGroupConvertTo)
	ON_COMMAND(ID_GROUP_CLICK_ELEMS, OnGroupClickElems)
	ON_COMMAND(ID_GROUP_CLICK_KNOTS, OnGroupClickKnots)
	ON_UPDATE_COMMAND_UI(ID_GROUP_CLICK_ELEMS, OnUpdateGroupClickElems)
	ON_UPDATE_COMMAND_UI(ID_GROUP_CLICK_KNOTS, OnUpdateGroupClickKnots)
	ON_COMMAND(ID_BUTTON_DEL_FREE_KNOTS, OnButtonDelFreeKnots)
	ON_UPDATE_COMMAND_UI(ID_ALL_DEMF, OnUpdateAllDemf)
	ON_UPDATE_COMMAND_UI(ID_ALL_HARDRODS, OnUpdateAllHardrods)
	ON_UPDATE_COMMAND_UI(ID_ALL_MASSES, OnUpdateAllMasses)
	ON_UPDATE_COMMAND_UI(ID_ALL_RODS, OnUpdateAllRods)
	ON_UPDATE_COMMAND_UI(ID_ALL_SPRINGS, OnUpdateAllSprings)
	ON_UPDATE_COMMAND_UI(ID_CALC, OnUpdateCalc)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DEL_FREE_KNOTS, OnUpdateButtonDelFreeKnots)
	ON_UPDATE_COMMAND_UI(ID_LISTELEM, OnUpdateListelem)
	ON_UPDATE_COMMAND_UI(ID_ELEMGROUP_DEL, OnUpdateElemgroupDel)
	ON_UPDATE_COMMAND_UI(ID_ELEMGROUP_PROP, OnUpdateElemgroupProp)
	ON_UPDATE_COMMAND_UI(ID_GROUP_CONVERT_TO, OnUpdateGroupConvertTo)
	ON_UPDATE_COMMAND_UI(ID_SHEME_PARAMS, OnUpdateShemeParams)
	ON_UPDATE_COMMAND_UI(ID_GROUP_NEW, OnUpdateGroupNew)
	ON_UPDATE_COMMAND_UI(ID_GROUP_LIST, OnUpdateGroupList)
	ON_UPDATE_COMMAND_UI(ID_GROUP_PREVIEW, OnUpdateGroupPreview)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_AUTOCORRECT, OnAutoCorrect)
	ON_UPDATE_COMMAND_UI(ID_AUTOCORRECT, OnUpdateAutoCorrect)
	ON_COMMAND(ID_BUTTON_GRCLICK_ELEMS, OnGroupClickElems)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_GRCLICK_ELEMS, OnUpdateGroupClickElems)
	ON_COMMAND(ID_BUTTON_GRCLICK_KNOTS, OnGroupClickKnots)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_GRCLICK_KNOTS, OnUpdateGroupClickKnots)
	ON_COMMAND(ID_FREE_NUMS, OnFreeNums)
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

CShemeDoc::CShemeDoc():m_pSheme(NULL)
{
	try
	{
		m_pSheme = new CSheme();
	}
	catch( bad_alloc& )
	{
		m_pSheme = NULL;
	}
	
	m_pPropFrame = NULL;
	// TODO: add one-time construction code here
	ParamView.Scale = ParamView.m_DefaultScale;
	pProgressDlg=0;

	m_bIsView = false;
	m_bMakeBar = true;

	EnableAutomation();
	AfxOleLockApp();
}

CShemeDoc::~CShemeDoc()
{
	delete m_pSheme;

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
	ASSERT( m_pSheme );
	return m_pSheme->AddRod( knot1, knot2 );
}

CElem* CShemeDoc::AddHardRod(CKnot * knot1, CKnot * knot2)
{
	ASSERT( m_pSheme );
	return m_pSheme->AddHardRod( knot1, knot2 );
}

CElem* CShemeDoc::AddDemf(CKnot * knot1, CKnot * knot2)
{
	ASSERT( m_pSheme );
	return m_pSheme->AddDemf( knot1, knot2 );
}

CElem* CShemeDoc::AddSpring(CKnot * knot1, CKnot * knot2)
{
	ASSERT( m_pSheme );
	return m_pSheme->AddSpring( knot1, knot2 );
}

CElem* CShemeDoc::AddMass(CKnot * knot1)
{
	ASSERT( m_pSheme );
	return m_pSheme->AddMass( knot1 );
}

void CShemeDoc::Serialize(CArchive& ar) 
{
	ASSERT(m_pSheme);
//	int count = 0;
//	ShemeVersion ver;
	if (ar.IsStoring())
	{	// storing code
		m_pSheme->Serialize(ar);
		//сериализация разбита на части для совместимости с предыдущими версиями
//		m_pSheme->Serialize1( ar, count, ver );
//		ParamView.Serialize(ar);
//		m_pSheme->Serialize2( ar, count, ver );
	}
	else
	{	// loading code
		m_pSheme->Serialize(ar);
		//сериализация разбита на части для совместимости с предыдущими версиями
//		m_pSheme->Serialize1( ar, count, ver );
//		ParamView.Serialize(ar);
//		m_pSheme->Serialize2( ar, count, ver );
	}// loading code
	m_pSheme->ReNumElems();

    POSITION pos = GetFirstViewPosition();
    GetNextView(pos)->Serialize(ar);
}

int CShemeDoc::PreCalculated()
{
	ASSERT(m_pSheme);
	int Count = m_pSheme->UpdateAllFree();
	int code = m_pSheme->SetMatrMDC(Count);
	if (code) return -1;
	
	//запрашиваем время, шаг и метод интегрирования 
	CPreCalcDlg dlg( &m_pSheme->ParamIntegr );
	if (dlg.DoModal()!=IDOK) return -1;
	/****************************************************/
	if( m_pSheme->m_bIsHardRod )
	{
		if( (m_pSheme->ParamIntegr.TypeMethod != 0)&&
			(m_pSheme->ParamIntegr.TypeMethod != 2)&&
			(m_pSheme->ParamIntegr.TypeMethod != 1) )
		{
			//если выбран не метод Рунге-Кутта или Ньюмарка или Парка,
			//то решать нельзя
			AfxMessageBox("Использование данного метода для жёст.стержней невозможно !!!",
				MB_OK|MB_ICONINFORMATION);
			return -1;
		}
	}
	/****************************************************/

	//Выделение памяти под массивы интегрирования
	//перемещение
	int cntstep=int(ceil(m_pSheme->ParamIntegr.Time/m_pSheme->ParamIntegr.Step)+1);
	m_pSheme->matr_RezY1.ReSize(Count,cntstep);
	//скорость
	m_pSheme->matr_RezY2.ReSize(Count,cntstep);
	if (m_pSheme->ParamIntegr.TypeMethod==2) 
		m_pSheme->matr_RezY3.ReSize(Count,cntstep);
	else m_pSheme->matr_RezY3.ReSize(1,1);
	
	//Подготовка для интегрирования со случайным возмущением
	POSITION pos=m_pSheme->listKnot.GetHeadPosition();
	while (pos)
	{
		//проходим по всем элементам
		CKnot *kn = m_pSheme->listKnot.GetNext(pos);
		kn->BeginIntegr(m_pSheme->ParamIntegr.Time);
	}

	//установка начальных условий
	BeginWaitCursor();
	m_pSheme->SetBeginPosition();
	EndWaitCursor();
	return 0;
}

void CShemeDoc::OnCalc() 
{
	// TODO: Add your command handler code here
	if (PreCalculated()) return;

	CString title( _T("Интегрирование схемы ") );
	title += GetTitle();
 	pProgressDlg=new CProgressDlg(100, title );

	int code;
	switch (m_pSheme->ParamIntegr.TypeMethod)
	{
	case 0: code=RungeKutt(m_pSheme->matr_RezY1.SizeX); break;
	case 1: code=Park(m_pSheme->matr_RezY1.SizeX); break;
	case 2: code=Numark(m_pSheme->matr_RezY1.SizeX); break;
	};

	//if (code) //Интегрирование было прервано
	pProgressDlg->DestroyWindow();
	delete pProgressDlg;
	pProgressDlg = NULL;

	m_pSheme->AfterCalc();
	UpdateAllViews(0);
}

void CShemeDoc::OnListelem() 
{
	// TODO: Add your command handler code here
	CElemDlg dlg( &m_pSheme->listElem, &m_pSheme->listKnot );
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
	CMatr mMD(m_pSheme->matr_M.SizeY,m_pSheme->matr_M.SizeX);
	CMatr mMC(m_pSheme->matr_M.SizeY,m_pSheme->matr_M.SizeX);
	int Psize = m_pSheme->matr_M.SizeY;
	if( m_pSheme->m_bIsHardRod )	Psize = m_pSheme->m_pEqDeg->GetRealSize();
	CMatr mP(Psize,1);

	mMD=m_pSheme->matr_M_1*m_pSheme->matr_D;
	mMC=m_pSheme->matr_M_1*m_pSheme->matr_C;

	double h = m_pSheme->ParamIntegr.Step;
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

		POSITION pos = m_pSheme->listElem.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CElem *elem = m_pSheme->listElem.GetNext(pos);
	//		if ( (elem->TypeElem==IDC_DEMF)||(elem->TypeElem==IDC_SPRING) )
				if (elem->SetMatrmP(mP, m_pSheme->matr_RezY1, m_pSheme->matr_RezY2, i-1, m_pSheme->ParamIntegr.Step*i)) 
				{
					AfxMessageBox("Ошибка в вычислении выражения");
					return -1;
				}
		}
		pos = m_pSheme->listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CKnot *knot = m_pSheme->listKnot.GetNext(pos);
			if( knot->SetMatrmP( mP, m_pSheme->matr_RezY1, 
				m_pSheme->matr_RezY2, i-1, 
				m_pSheme->ParamIntegr.Step*i, 
				m_pSheme->matr_UM, m_pSheme->matr_UD, m_pSheme->matr_UC) )
			{
				AfxMessageBox("Ошибка в вычислении выражения");
				return -1;
			}
		}
		pos = m_pSheme->listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CKnot *knot = m_pSheme->listKnot.GetNext(pos);
			if (knot->SetMatrmP(mP, m_pSheme->ParamIntegr.Step*i)) 
			{
				AfxMessageBox("Ошибка в вычислении выражения");
				return -1;
			}
		}

		Psize = m_pSheme->matr_RezY1.SizeY;
		int short_size = m_pSheme->m_pEqDeg->GetModifiedSize();
		if( m_pSheme->m_bIsHardRod )	Psize = short_size;
		CMatr tmpVect( Psize, 1);
		
		/*******************************************************/
		//учёт жёст.стержней если надо
		if( m_pSheme->m_bIsHardRod )
		{
			CMatr tmpRezY1( short_size, m_pSheme->matr_RezY1.SizeX ),
					tmpRezY2( short_size, m_pSheme->matr_RezY2.SizeX );

			for( int c = 0; c < m_pSheme->matr_RezY1.SizeX; c++ )
			{
				CMatr tmp(m_pSheme->matr_RezY1.SizeY, 1);
				for( int r = 0; r < m_pSheme->matr_RezY1.SizeY; r++ )
				{
					//вырезаем из matr_RezY? столбец
					tmp[r][0] = m_pSheme->matr_RezY1[r][c];
				}
				m_pSheme->m_pEqDeg->ModifyVect(tmp);
				tmpRezY1.CopyVectTo( tmp, c );
				
			}
			for( c = 0; c < m_pSheme->matr_RezY2.SizeX; c++ )
			{
				CMatr tmp(m_pSheme->matr_RezY2.SizeY, 1);
				for( int r = 0; r < m_pSheme->matr_RezY2.SizeY; r++ )
				{
					//вырезаем из matr_RezY? столбец
					tmp[r][0] = m_pSheme->matr_RezY2[r][c];
				}
				m_pSheme->m_pEqDeg->ModifyVect(tmp);
				tmpRezY2.CopyVectTo( tmp, c );
				
			}
			CMatr tmpP( mP.SizeY, mP.SizeX );
			tmpP = mP;
			m_pSheme->m_pEqDeg->ModifyVect(tmpP);

			tmpVect = (mMD.MultOnCol(tmpRezY2,i-1)-m_pSheme->matr_M_1*tmpP+
					   mMC.MultOnCol(tmpRezY1,i-1))*mult;
			m_pSheme->m_pEqDeg->DeModifyVector(tmpVect);

		}
		else	tmpVect = (mMD.MultOnCol(m_pSheme->matr_RezY2,i-1)-m_pSheme->matr_M_1*mP+
						   mMC.MultOnCol(m_pSheme->matr_RezY1,i-1))*mult;

		m_pSheme->matr_RezY2.CopyVectTo( tmpVect, i );
		
		for (int j=0; j<m_pSheme->matr_RezY1.SizeY;j++)
		{
			m_pSheme->matr_RezY1[j][i]=m_pSheme->matr_RezY1[j][i-1]+m_pSheme->matr_RezY2[j][i-1]*(-mult);
			m_pSheme->matr_RezY2[j][i]+=m_pSheme->matr_RezY2[j][i-1];
		}

		if (m_pSheme->UEnable)
		{
			//Установка кинематических перемещений и скоростей
			pos = m_pSheme->listKnot.GetHeadPosition();
			while (pos)
			{
				//проходим по всем узлам
				CKnot *knot = m_pSheme->listKnot.GetNext(pos);
				if( knot->SetKinematicPos( m_pSheme->matr_RezY1, m_pSheme->matr_RezY2, i, m_pSheme->ParamIntegr.Step*i)) 
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
	double h = m_pSheme->ParamIntegr.Step;
	m_pSheme->ParamIntegr.Step=h/ReduceStep;
//	RungeKutt(3*ReduceStep);
	m_pSheme->matr_RezY3.ReSize(m_pSheme->matr_RezY1.SizeY,3*ReduceStep+1);
	int exitcode = Numark(3*ReduceStep);
	m_pSheme->matr_RezY3.ReSize(1,1);

	for (int k=0;k<3;k++)
		for (int i=0;i<m_pSheme->matr_RezY1.SizeY;i++)
		{
			m_pSheme->matr_RezY1[i][k]=m_pSheme->matr_RezY1[i][k*ReduceStep];
			m_pSheme->matr_RezY2[i][k]=m_pSheme->matr_RezY2[i][k*ReduceStep];
		}
	m_pSheme->ParamIntegr.Step=h;
	if (exitcode) return -1;
	//RungeKutt(5);
	//Numark(5);

	//находим обратную матрицу левой части системы уравнений
	CMatr mM_1(m_pSheme->matr_M.SizeY,m_pSheme->matr_M.SizeX);
	int code;
	mM_1=(m_pSheme->matr_M*(100.0/36.0/m_pSheme->ParamIntegr.Step/m_pSheme->ParamIntegr.Step)+m_pSheme->matr_D*(10.0/6.0/m_pSheme->ParamIntegr.Step)+m_pSheme->matr_C).GetInvert(code);
	if (!code)
	{
		AfxMessageBox( _T("Ошибка в схеме."),
						MB_OK|MB_ICONSTOP);
		return -1;
	}

	int Psize = m_pSheme->matr_M.SizeY;
	if( m_pSheme->m_bIsHardRod )
		Psize = m_pSheme->m_pEqDeg->GetRealSize();
	CMatr mP(Psize,1);
//	CMatr mP(matr_M.SizeY,1);
	CMatr mF(m_pSheme->matr_M.SizeY,1);
	
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
		POSITION pos = m_pSheme->listElem.GetHeadPosition();
		while (pos)
		{
			CElem *elem = m_pSheme->listElem.GetNext(pos);
			//if ( (elem->TypeElem==IDC_DEMF)||(elem->TypeElem==IDC_SPRING) )
				if (elem->SetMatrmP(mP, m_pSheme->matr_RezY1, m_pSheme->matr_RezY2, i, m_pSheme->ParamIntegr.Step*(i+1))) 
				{
					AfxMessageBox("Ошибка при вычислении выражения");
					return -1;
				}
		}
		pos = m_pSheme->listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CKnot *knot = m_pSheme->listKnot.GetNext(pos);
			if (knot->SetMatrmP(mP, m_pSheme->matr_RezY1,
				m_pSheme->matr_RezY2, i-1, m_pSheme->ParamIntegr.Step*i,
				m_pSheme->matr_UM, m_pSheme->matr_UD, m_pSheme->matr_UC)) 
			{
				AfxMessageBox("Ошибка при вычислении выражения");
				return -1;
			}
		}
		pos = m_pSheme->listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CKnot *knot = m_pSheme->listKnot.GetNext(pos);
			if (knot->SetMatrmP(mP, m_pSheme->ParamIntegr.Step*i)) 
			{
				AfxMessageBox("Ошибка при вычислении выражения");
				return -1;
			}
		}

		Psize = m_pSheme->matr_RezY1.SizeY;
		int short_size = m_pSheme->m_pEqDeg->GetModifiedSize();
		if( m_pSheme->m_bIsHardRod )	Psize = short_size;
		CMatr tmpVect( Psize, 1);
		/*******************************************************/
		//учёт жёст.стержней если надо
		if( m_pSheme->m_bIsHardRod )
		{
			CMatr tmpRezY1( short_size, m_pSheme->matr_RezY1.SizeX ),
				tmpRezY2( short_size, m_pSheme->matr_RezY2.SizeX );

			for( int c = 0; c < m_pSheme->matr_RezY1.SizeX; c++ )
			{
				CMatr tmp(m_pSheme->matr_RezY1.SizeY, 1);
				for( int r = 0; r < m_pSheme->matr_RezY1.SizeY; r++ )
				{
					//вырезаем из matr_RezY? столбец
					tmp[r][0] = m_pSheme->matr_RezY1[r][c];
				}
				m_pSheme->m_pEqDeg->ModifyVect(tmp);
				tmpRezY1.CopyVectTo( tmp, c );
				
			}
			for( c = 0; c < m_pSheme->matr_RezY2.SizeX; c++ )
			{
				CMatr tmp(m_pSheme->matr_RezY2.SizeY, 1);
				for( int r = 0; r < m_pSheme->matr_RezY2.SizeY; r++ )
				{
					//вырезаем из matr_RezY? столбец
					tmp[r][0] = m_pSheme->matr_RezY2[r][c];
				}
				m_pSheme->m_pEqDeg->ModifyVect(tmp);
				tmpRezY2.CopyVectTo( tmp, c );
				
			}
			CMatr tmpP( mP.SizeY, mP.SizeX );
			tmpP = mP;
			m_pSheme->m_pEqDeg->ModifyVect(tmpP);

			mF = m_pSheme->matr_M.MultOnCol(tmpRezY2,i)*(15.0/6.0/m_pSheme->ParamIntegr.Step)-
				m_pSheme->matr_M.MultOnCol(tmpRezY2,i-1)*(1.0/m_pSheme->ParamIntegr.Step)+
				m_pSheme->matr_M.MultOnCol(tmpRezY2,i-2)*(1.0/6.0/m_pSheme->ParamIntegr.Step)+
			
				(m_pSheme->matr_M*(150.0/36.0/m_pSheme->ParamIntegr.Step/m_pSheme->ParamIntegr.Step)+
				m_pSheme->matr_D*(15.0/6.0/m_pSheme->ParamIntegr.Step)).MultOnCol(tmpRezY1,i)-

				(m_pSheme->matr_M*(10.0/6.0/m_pSheme->ParamIntegr.Step/m_pSheme->ParamIntegr.Step)+
				m_pSheme->matr_D*(1.0/m_pSheme->ParamIntegr.Step)).MultOnCol(tmpRezY1,i-1)+

				(m_pSheme->matr_M*(10.0/36.0/m_pSheme->ParamIntegr.Step/m_pSheme->ParamIntegr.Step)+
				m_pSheme->matr_D*(1.0/6.0/m_pSheme->ParamIntegr.Step)).MultOnCol(tmpRezY1,i-2)+
				tmpP;
			tmpVect = mM_1*mF;
			m_pSheme->m_pEqDeg->DeModifyVector(tmpVect);
		}
		else	
		{
			mF = m_pSheme->matr_M.MultOnCol(m_pSheme->matr_RezY2,i)*(15.0/6.0/m_pSheme->ParamIntegr.Step)-
				m_pSheme->matr_M.MultOnCol(m_pSheme->matr_RezY2,i-1)*(1.0/m_pSheme->ParamIntegr.Step)+
				m_pSheme->matr_M.MultOnCol(m_pSheme->matr_RezY2,i-2)*(1.0/6.0/m_pSheme->ParamIntegr.Step)+
			
				(m_pSheme->matr_M*(150.0/36.0/m_pSheme->ParamIntegr.Step/m_pSheme->ParamIntegr.Step)+
				m_pSheme->matr_D*(15.0/6.0/m_pSheme->ParamIntegr.Step)).MultOnCol(m_pSheme->matr_RezY1,i)-

				(m_pSheme->matr_M*(10.0/6.0/m_pSheme->ParamIntegr.Step/m_pSheme->ParamIntegr.Step)+
				m_pSheme->matr_D*(1.0/m_pSheme->ParamIntegr.Step)).MultOnCol(m_pSheme->matr_RezY1,i-1)+

				(m_pSheme->matr_M*(10.0/36.0/m_pSheme->ParamIntegr.Step/m_pSheme->ParamIntegr.Step)+
				m_pSheme->matr_D*(1.0/6.0/m_pSheme->ParamIntegr.Step)).MultOnCol(m_pSheme->matr_RezY1,i-2)+
				mP;
			tmpVect = mM_1*mF;
		}
		m_pSheme->matr_RezY1.CopyVectTo( tmpVect,i+1);

		for (int j=0;j<m_pSheme->matr_RezY2.SizeY;j++)
			m_pSheme->matr_RezY2[j][i+1]=(10*m_pSheme->matr_RezY1[j][i+1]-15*m_pSheme->matr_RezY1[j][i]+6*m_pSheme->matr_RezY1[j][i-1]-m_pSheme->matr_RezY1[j][i-2])/6.0/m_pSheme->ParamIntegr.Step;

		if (m_pSheme->UEnable)
		{
			//Установка кинематических перемещений и скоростей
			pos = m_pSheme->listKnot.GetHeadPosition();
			while (pos)
			{
				//проходим по всем узлам
				CKnot *knot = m_pSheme->listKnot.GetNext(pos);
				if (knot->SetKinematicPos(m_pSheme->matr_RezY1, m_pSheme->matr_RezY2, i+1, m_pSheme->ParamIntegr.Step*(i+1))) 
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
	double m_Step = m_pSheme->ParamIntegr.Step;
		
	CMatr mMpr(m_pSheme->matr_M.SizeY, m_pSheme->matr_M.SizeX);
	int Psize = m_pSheme->matr_M.SizeY;
	if( m_pSheme->m_bIsHardRod )
		Psize = m_pSheme->m_pEqDeg->GetRealSize();
	CMatr mP(Psize,1);
//	CMatr mP(matr_M.SizeY,1);

	mMpr = m_pSheme->matr_M*(1.0/(betta*m_Step*m_pSheme->ParamIntegr.Step)) + 
		m_pSheme->matr_D*(alpha/(betta*m_Step)) + m_pSheme->matr_C;
	int code;
	mMpr=mMpr.GetInvert(code);
	if (!code)
	{
		AfxMessageBox("Ошибка при решении системы уравнений");
		return -1;
	}
	//CMatr matr_RezY3(matr_RezY1.SizeY, 1);
	m_pSheme->matr_RezY3.ClearData();
	BOOL FlagExit;
	for (int i=1; i<nStep;i++)
	{
		FlagExit = false;
		///////////////////////////////////////////////////////////////////////
		//Обработка сообщений
		MSG msg;
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
		///////////////////////////////////////////////////////////////////////
		//Очистка вектора правых частей
		mP.ClearData();

		POSITION pos = m_pSheme->listElem.GetHeadPosition();
		while (pos)
		{
			//проходим по всем элементам
			CElem *elem = m_pSheme->listElem.GetNext(pos);
			//if ( (elem->TypeElem==IDC_DEMF)||(elem->TypeElem==IDC_SPRING) )
				if (elem->SetMatrmP(mP, m_pSheme->matr_RezY1, m_pSheme->matr_RezY2, i-1, m_Step*i)) 
				{
					AfxMessageBox("Ошибка в вычислении выражения");
					return -1;
				}
		}
		pos = m_pSheme->listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем узлам
			CKnot *knot = m_pSheme->listKnot.GetNext(pos);
			if (knot->SetMatrmP(mP, m_pSheme->matr_RezY1, m_pSheme->matr_RezY2,
				i-1, m_Step*i, m_pSheme->matr_UM, m_pSheme->matr_UD, m_pSheme->matr_UC)) 
			{
				AfxMessageBox("Ошибка при вычислении выражения");
				return -1;
			}
		}
		pos = m_pSheme->listKnot.GetHeadPosition();
		while (pos)
		{
			//проходим по всем узлам
			CKnot *knot = m_pSheme->listKnot.GetNext(pos);
			if (knot->SetMatrmP(mP, m_Step*i)) 
			{
				AfxMessageBox("Ошибка при вычислении выражения");
				return -1;
			}
		}

		Psize = m_pSheme->matr_RezY1.SizeY;
		int short_size = m_pSheme->m_pEqDeg->GetModifiedSize();
		if( m_pSheme->m_bIsHardRod )	Psize = short_size;
		CMatr tmpVect( Psize, 1);
		/*******************************************************/
		//учёт жёст.стержней если надо
		if( m_pSheme->m_bIsHardRod )
		{
			CMatr tmpRezY1( short_size, m_pSheme->matr_RezY1.SizeX ),
				tmpRezY2( short_size, m_pSheme->matr_RezY2.SizeX ),
				tmpRezY3( short_size, m_pSheme->matr_RezY3.SizeX );

			for( int c = 0; c < m_pSheme->matr_RezY1.SizeX; c++ )
			{
				CMatr tmp(m_pSheme->matr_RezY1.SizeY, 1);
				for( int r = 0; r < m_pSheme->matr_RezY1.SizeY; r++ )
				{
					//вырезаем из matr_RezY? столбец
					tmp[r][0] = m_pSheme->matr_RezY1[r][c];
				}
				m_pSheme->m_pEqDeg->ModifyVect(tmp);
				tmpRezY1.CopyVectTo( tmp, c );
				
			}
			for( c = 0; c < m_pSheme->matr_RezY2.SizeX; c++ )
			{
				CMatr tmp(m_pSheme->matr_RezY2.SizeY, 1);
				for( int r = 0; r < m_pSheme->matr_RezY2.SizeY; r++ )
				{
					//вырезаем из matr_RezY? столбец
					tmp[r][0] = m_pSheme->matr_RezY2[r][c];
				}
				m_pSheme->m_pEqDeg->ModifyVect(tmp);
				tmpRezY2.CopyVectTo( tmp, c );
				
			}
			for( c = 0; c < m_pSheme->matr_RezY3.SizeX; c++ )
			{
				CMatr tmp(m_pSheme->matr_RezY3.SizeY, 1);
				for( int r = 0; r < m_pSheme->matr_RezY3.SizeY; r++ )
				{
					//вырезаем из matr_RezY? столбец
					tmp[r][0] = m_pSheme->matr_RezY3[r][c];
				}
				m_pSheme->m_pEqDeg->ModifyVect(tmp);
				tmpRezY3.CopyVectTo( tmp, c );
				
			}
			CMatr tmpP( mP.SizeY, mP.SizeX );
			tmpP = mP;
			m_pSheme->m_pEqDeg->ModifyVect(tmpP);

			tmpVect = mMpr*((m_pSheme->matr_M*(1.0/(2.0*betta)-1) + m_pSheme->matr_D*m_Step*(alpha/(2.0*betta)-1)).MultOnCol(tmpRezY3,i-1)+
					(m_pSheme->matr_M*(1.0/(betta*m_Step)) + m_pSheme->matr_D*(alpha/betta-1)).MultOnCol(tmpRezY2,i-1)+
					(m_pSheme->matr_M*(1.0/(betta*m_Step*m_Step)) + m_pSheme->matr_D*(alpha/(betta*m_Step))).MultOnCol(tmpRezY1,i-1)
					+tmpP);
			m_pSheme->m_pEqDeg->DeModifyVector(tmpVect);
		}
		else	
		{
			tmpVect = mMpr*((m_pSheme->matr_M*(1.0/(2.0*betta)-1) + m_pSheme->matr_D*m_Step*(alpha/(2.0*betta)-1)).MultOnCol(m_pSheme->matr_RezY3,i-1)+
					(m_pSheme->matr_M*(1.0/(betta*m_Step)) + m_pSheme->matr_D*(alpha/betta-1)).MultOnCol(m_pSheme->matr_RezY2,i-1)+
					(m_pSheme->matr_M*(1.0/(betta*m_Step*m_Step)) + m_pSheme->matr_D*(alpha/(betta*m_Step))).MultOnCol(m_pSheme->matr_RezY1,i-1)
					+mP);
		}

		m_pSheme->matr_RezY1.CopyVectTo( tmpVect, i );

		for (int j=0;j<m_pSheme->matr_RezY2.SizeY;j++)
		{
			m_pSheme->matr_RezY2[j][i]=(m_pSheme->matr_RezY1[j][i]-m_pSheme->matr_RezY1[j][i-1])*(alpha/(betta*m_Step))-
							  m_pSheme->matr_RezY2[j][i-1]*(alpha/betta-1)-
							  m_pSheme->matr_RezY3[j][i-1]*m_Step*(alpha/(2.0*betta)-1);

			m_pSheme->matr_RezY3[j][i]=(m_pSheme->matr_RezY1[j][i]-m_pSheme->matr_RezY1[j][i-1])*(1.0/(betta*m_Step*m_Step))-
							  m_pSheme->matr_RezY2[j][i-1]*(1.0/(betta*m_Step))-
							  m_pSheme->matr_RezY3[j][i-1]*(1.0/(2.0*betta)-1.0);
		}
		if (m_pSheme->UEnable)
		{
			//Установка кинематических перемещений и скоростей
			POSITION pos = m_pSheme->listKnot.GetHeadPosition();
			while (pos)
			{
				//проходим по всем узлам
				CKnot *knot = m_pSheme->listKnot.GetNext(pos);
				if (knot->SetKinematicPos( m_pSheme->matr_RezY1,
					m_pSheme->matr_RezY2, i, m_Step*i)) 
				{
					AfxMessageBox("Ошибка при вычислении выражения");
					return -1;
				}
			}
		}
	}
	return (FlagExit?-1:0);
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
	//если только оно ещё не создано
	if( m_bIsView )	return;
	m_bIsView = true;

	CString str;
	str=GetTitle();

	str+=_T("  Собственные формы колебаний");
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
	rect.OffsetRect(rect.Width()/2,0);
	if (rect.Width()<325) rect.right=rect.left+325;
	rect.bottom += 100;
	pNewFrame->MoveWindow(&rect);

	
	pTemplate->InitialUpdateFrame(pNewFrame, this);

	CFormsView *pFormsView = (CFormsView*)pNewFrame->GetActiveView();
	ASSERT (pFormsView != NULL);
	pFormsView->m_bCalculated = true;

	pNewFrame->SetWindowText(str);

	//Копируем данные
/*	pFormsView->matr_Forms.ReSize(Matr_Forms.SizeY,Matr_Forms.SizeX);
	pFormsView->matr_Forms=Matr_Forms;

	pFormsView->matr_Freq.ReSize(1, F.SizeY);
	for (i=0;i<F.SizeY;i++)
		pFormsView->matr_Freq[0][i]=F[0][i];

	pFormsView->SetForm(0);*/

	UpdateAllViews(0);

	pFormsView->m_bCalculated = false;
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

void CShemeDoc::OnTest() 
{
	// TODO: Add your command handler code here
	ASSERT(m_pSheme);
	int Count = m_pSheme->UpdateAllFree();
	int code = m_pSheme->SetMatrMDC(Count);
//	if (code) return;

	m_pSheme->matr_C.SaveToFile("mC");
	m_pSheme->matr_D.SaveToFile("mD");
	m_pSheme->matr_M.SaveToFile("mM");

/*	int s=matr_C.SizeY;
	double w=10;
	CComplexMatr C(s,s);
	C.UnitMatr(matr_C - matr_M*(w*w),matr_D*w);
	int flag;
	C=C.GetInvert(flag);
	C.SaveToFileRe("mC_Re");
	C.SaveToFileIm("mC_Im");*/
}

void CShemeDoc::OnShemeParams() 
{
	// TODO: Add your command handler code here
	CEVMDialog dlg;

	dlg.m_HardMethod = m_pSheme->m_HardMethod;
	dlg.m_bCondenceMass = m_pSheme->m_bCondenceMass;
	switch(m_pSheme->m_EVMethod)
	{
	case EVM_JACOBY:
		dlg.m_Method = 0;
		break;
	case EVM_QR_ELM:
		dlg.m_Method = 1;
		break;
	case EVM_QR_DIR:
		dlg.m_Method = 2;
		break;
	case EVM_QR_ORT:
		dlg.m_Method = 3;
		break;
	default:
		dlg.m_Method = 0;
		break;
	}
	if( dlg.DoModal() == IDOK )
	{
		m_pSheme->m_bCondenceMass = (dlg.m_bCondenceMass)?(true):(false);
		m_pSheme->m_HardMethod = dlg.m_HardMethod;
		switch(dlg.m_Method)
		{
		case 0:
			m_pSheme->m_EVMethod = EVM_JACOBY;
			break;
		case 1:
			m_pSheme->m_EVMethod = EVM_QR_ELM;
			break;
		case 2:
			m_pSheme->m_EVMethod = EVM_QR_DIR;
			break;
		case 3:
			m_pSheme->m_EVMethod = EVM_QR_ORT;
			break;
		default:
			m_pSheme->m_EVMethod = EVM_JACOBY;
			break;
		}
	}
}

void CShemeDoc::OnViewStyles() 
{
	// TODO: Add your command handler code here
	
	//вызов диалога для настройки параметров изображения
	//схем: цветов, шрифтов и т.д.
	CViewStyles dlg;

	dlg.m_bNumElems = ParamView.m_bNumElems;
	dlg.m_bNumKnots = ParamView.m_bNumKnots;
	dlg.m_bTextOut = ParamView.m_bTextOut;

	dlg.m_clrFree = ParamView.m_clrFree;
	dlg.m_clrNumElems = ParamView.m_clrNumElems;
	dlg.m_clrNumKnots = ParamView.m_clrNumKnots;

	dlg.m_strFreeFont = ParamView.m_strFreeFontName;
	dlg.m_strNumElems = ParamView.m_strNumElemsFontName;
	dlg.m_strNumKnots = ParamView.m_strNumKnotsFontName;

	dlg.m_ZeroRot = ParamView.m_ZeroRot;

	int flag = ParamView.m_fntFree.GetLogFont( &dlg.m_lfFree );
	ASSERT( flag );
	flag = ParamView.m_fntElems.GetLogFont( &dlg.m_lfNumElems );
	ASSERT( flag );
	flag = ParamView.m_fntKnot.GetLogFont( &dlg.m_lfNumKnots );
	ASSERT( flag );

	if( dlg.DoModal() == IDOK )
	{
		ParamView.m_bNumElems = dlg.m_bNumElems?true:false;
		ParamView.m_bNumKnots = dlg.m_bNumKnots?true:false;
		ParamView.m_bTextOut = dlg.m_bTextOut?true:false;

		ParamView.m_ZeroRot = dlg.m_ZeroRot;

		if(	dlg.m_bFreeFontModified )
		{
			ParamView.m_strFreeFontName = dlg.m_strFreeFont;
			ParamView.m_clrFree = dlg.m_clrFree;
			ParamView.m_fntFree.DeleteObject();
			flag = ParamView.m_fntFree.CreateFontIndirect( &dlg.m_lfFree );
			ASSERT( flag );
		}
		if( dlg.m_bNumElemsFontModified )
		{
			ParamView.m_strNumElemsFontName = dlg.m_strNumElems;
			ParamView.m_clrNumElems = dlg.m_clrNumElems;
			ParamView.m_fntElems.DeleteObject();
			flag = ParamView.m_fntElems.CreateFontIndirect( &dlg.m_lfNumElems );
			ASSERT( flag );
		}
		if( dlg.m_bNumKnotsFontModified )
		{
			ParamView.m_strNumKnotsFontName = dlg.m_strNumKnots;
			ParamView.m_clrNumKnots = dlg.m_clrNumKnots;
			ParamView.m_fntKnot.DeleteObject();
			flag = ParamView.m_fntKnot.CreateFontIndirect( &dlg.m_lfNumKnots );
			ASSERT( flag );
		}
	}
	UpdateAllViews(NULL);
}

void CShemeDoc::OnUpdateFreeformCalc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//проверяем: есть ли что считать?
	bool bThereIs = false;
	if( m_pSheme->listElem.GetHeadPosition() )
		bThereIs = true;//если есть хоть один элемент,
						//то можно разрешить счёт.
	pCmdUI->Enable( bThereIs && (ParamView.m_iClickedObjects == 0) );
}

void CShemeDoc::PreviewGroup( bool bElem )
{
	if( ParamView.m_vecSelNumbers.empty() )	return;

	ParamView.m_bSelType = bElem;
	UpdateAllViews(NULL);

	CGroupPreviewDlg dlgGP;
	dlgGP.DoModal();

	ParamView.m_vecSelNumbers.clear();
}

void CShemeDoc::OnGroupNew() 
{
	// TODO: Add your command handler code here
	CNewGroupDlg dlg;
	int ret;

	do
	{
		CShemeGroup gr;
	
		dlg.m_strGroup.Empty();
		gr.GetName( dlg.m_strGroupName );

		bool er = true;
		while( (er == true)&&( (ret=dlg.DoModal()) == IDOK) )
		{
			gr.SetName( dlg.m_strGroupName );
			gr.SetGroup( dlg.m_strGroup );
			gr.SetType( dlg.m_iGroupType );

			er = false;
			if( !gr.Analize() )
			{
				//ошибка
				er = true;
				CString strEM;
				gr.GetErrorMessage( strEM );
				strEM += _T(" Хотите исправить ошибку?");
				int ret = AfxMessageBox( strEM, MB_OKCANCEL|MB_TASKMODAL|MB_ICONEXCLAMATION );
				if( ret == IDCANCEL )	break;
			}
			else	
			{
				if( gr.GetType() == 0 )
					m_pSheme->m_vecElemGroups.push_back( gr );
				else
					m_pSheme->m_vecKnotGroups.push_back( gr );
			}
			SetModifiedFlag();
		}//while( (er...
	}	while( ret != IDCANCEL );
}

void CShemeDoc::OnGroupList() 
{
	ASSERT(m_pSheme);
	// TODO: Add your command handler code here
	CGroupListDlg dlg( m_pSheme->m_vecElemGroups, m_pSheme->m_vecKnotGroups, true );
	//true означает, что диалог создаётся для просмотра
	//и редактирования групп и все возможности диалога задействованы
	
	int ret;
	for(;;)
	{
		ret = dlg.DoModal();
		if( ret != IDC_BUTTON_GROUP_SHOW )	break;
		//значит нажата кнопка просмотра группы
		if( dlg.m_SelDlgItem == -1 )	return;

		int p = CShemeGroup::GetRealPosInGroup( dlg.m_arDel, dlg.m_SelDlgItem );
		int m = m_pSheme->m_vecElemGroups.size();
		bool bElem = (p<m)?true:false;//показывает: выбран элемент или нет

		CString str;
		int err;
		if( bElem )
			err = m_pSheme->IsGroupContainsNotexistingObject( bElem, dlg.m_vecElGr[p], str, ParamView.m_vecSelNumbers );
		else
			err = m_pSheme->IsGroupContainsNotexistingObject( bElem, dlg.m_vecKnGr[p-m], str, ParamView.m_vecSelNumbers );
		
		if( err == 2 )
		{
			AfxMessageBox( str, MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
			return;
		}
		bool show = true;
		if( err == 1 )
		{
			str += _T("\nПросмотреть что есть?");
			if( AfxMessageBox( str, MB_YESNO|MB_TASKMODAL|MB_ICONQUESTION ) == IDNO )
			{
				ParamView.m_vecSelNumbers.clear();
				show = false;
			}
		}

		if( show )
		{
			PreviewGroup( bElem );
		}
		UpdateAllViews(NULL);
	}

	if( ret == IDOK )
	{
		int n = dlg.m_arDel.size();
		Groups vecNewElems, vecNewKnots;
		int m = m_pSheme->m_vecElemGroups.size();
		for( int i = 0; i < n; i++)
		{
			if( dlg.m_arDel[i] == 0 )
			{
				//не была удалена
				//проверяем была ли модифицирована
				if( dlg.m_arMod[i] == 1 )
				{
					if( i < m )
					{
						//это элемент
						CString name, gr;
						(dlg.m_vecElGr[i]).GetName( name );
						(dlg.m_vecElGr[i]).GetGroup( gr );
						CShemeGroup newGr( gr, name, dlg.m_vecElGr[i].GetType() );
						vecNewElems.push_back( newGr );
					}
					else
					{
						//это узел
						CString name, gr;
						(dlg.m_vecKnGr[i-m]).GetName( name );
						(dlg.m_vecKnGr[i-m]).GetGroup( gr );
						CShemeGroup newGr( gr, name, dlg.m_vecKnGr[i-m].GetType() );
						vecNewKnots.push_back( newGr );
					}
				}
				else
				{
					if( i < m )
					{
						//это элемент
						vecNewElems.push_back( m_pSheme->m_vecElemGroups[i] );
					}
					else
					{
						//это узел
						vecNewKnots.push_back( m_pSheme->m_vecKnotGroups[i-m] );
					}
				}
			}
		}
		m_pSheme->m_vecElemGroups = vecNewElems;
		m_pSheme->m_vecKnotGroups = vecNewKnots;
		SetModifiedFlag();
	}
	else
	{
		if( ret == IDCANCEL )
		{
			ARRAY::iterator it_del = find( dlg.m_arDel.begin(),
										dlg.m_arDel.end(), 1 );
			ARRAY::iterator it_mod = find( dlg.m_arMod.begin(),
										dlg.m_arMod.end(), 1 );
			if( (it_del != dlg.m_arDel.end())||(it_mod != dlg.m_arMod.end()) )
			{
				AfxMessageBox("Внесённые вами изменения не будут учтены.", 
					MB_OK|MB_TASKMODAL|MB_ICONINFORMATION );
			}
		}//ret==IDCANCEL
	}
	UpdateAllViews(NULL);
}

void CShemeDoc::OnGroupElemDel() 
{
	// TODO: Add your command handler code here
	ASSERT(m_pSheme);
	//удалять можно только элементы, т.к. большинство узлов
	//наверняка связано элементами
	Groups vecKnots;
	vecKnots.clear();//на всякий случай
	CGroupListDlg dlg( m_pSheme->m_vecElemGroups, vecKnots, false );
	//false означает, что диалог создаётся только для
	//выбора одной группы из списка без возможности её редактирования
	//или удаления для дальнейшего удаления или редактирования
	//группы элементов(узлов) на основе выбранной группы.

	if( dlg.DoModal() == IDOK )
	{
		if( dlg.m_SelDlgItem == -1 )
		{
			return;
		}
		//выбирается только группа элементов!!!
		CString str;
		ARRAY vec;
		int err = m_pSheme->IsGroupContainsNotexistingObject( true, m_pSheme->m_vecElemGroups[dlg.m_SelDlgItem], str, vec );

		if( err == 2 )
		{
			AfxMessageBox( str, MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
			return;
		}
		//выбранную группу элементов надо удалить из схемы:
		//теперь vec содержит массив номеров выбранных элементов
		if( err == 1 )
		{
			AfxMessageBox( str, MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
			return;
		}

		POSITION pos2, pos = m_pSheme->listElem.GetHeadPosition();
		while( pos )
		{
			pos2 = pos;
			//проходим по всем элементам
			CElem *elem = m_pSheme->listElem.GetNext(pos);

			if( CShemeGroup::IsElemContainsInGroup( elem, vec ) )
			{
				int busy1 = 0, busy2 = 0;

				//Ищем элементы, присоединенные к выбранному
				POSITION pos3 = m_pSheme->listElem.GetHeadPosition();
				while( pos3 )
				{
					//получаем указатель на очередной элемент для поиска
					CElem *findelem = m_pSheme->listElem.GetNext(pos3);
					if( findelem != elem )
					{
						if( (findelem->knot1==elem->knot1)||
							 (findelem->knot2==elem->knot1) )
							busy1=1;
						if( (findelem->knot1==elem->knot2)||
							 (findelem->knot2==elem->knot2) )
							busy2=1;
					}
				}

				//Поиск графиков с несуществующими узлами
				POSITION posgraph = GetFirstViewPosition();
				while( posgraph )
				{
					CGraphicView *pview = (CGraphicView*)GetNextView(posgraph);
					if( ((!busy1)&&(pview->pKnot==elem->knot1)) ||
						 ((!busy2)&&(pview->pKnot==elem->knot2))  )
					{
						RemoveView(pview);
						pview->GetOwner()->DestroyWindow();
					}
				}

				//Удаление из списка
				delete elem;
				m_pSheme->listElem.RemoveAt(pos2);
				m_pSheme->SetConnectElements();

			}//it != m_vecElemGroups.end()
		}//while(pos)
		SetModifiedFlag();

	}//dlg.DoModal() == IDOK
	UpdateAllViews(NULL);
}

void CShemeDoc::OnGroupElemProp() 
{
	ASSERT(m_pSheme);
	// TODO: Add your command handler code here
	CGroupListDlg dlg( m_pSheme->m_vecElemGroups, m_pSheme->m_vecKnotGroups, false );
	//false означает, что диалог создаётся только для
	//выбора одной группы из списка без возможности её редактирования
	//или удаления для дальнейшего удаления или редактирования
	//группы элементов(узлов) на основе выбранной группы.
	
	if( dlg.DoModal() == IDOK )
	{
		if( dlg.m_SelDlgItem == -1 )
		{
			return;
		}

		int p = CShemeGroup::GetRealPosInGroup( dlg.m_arDel, dlg.m_SelDlgItem );
		ARRAY vec;
		int m = m_pSheme->m_vecElemGroups.size();
		bool bElem = (p<m)?true:false;//показывает выбран ли элемент

		CString str;
		int err;
		if( bElem )
			err = m_pSheme->IsGroupContainsNotexistingObject( bElem, m_pSheme->m_vecElemGroups[p], str, vec );
		else
			err = m_pSheme->IsGroupContainsNotexistingObject( bElem, m_pSheme->m_vecKnotGroups[p-m], str, vec );
		
		if( err == 2 )
		{
			AfxMessageBox( str, MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
			return;
		}
		if( err == 1 )
		{
			AfxMessageBox( str, MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
			return;
		}
		if( vec.empty() )	return;
		//теперь vec содержит массив номеров выбранных элементов или узлов
		if( (bElem)&&(!m_pSheme->IsElemGroupOfOneType(vec)) )
		{
			AfxMessageBox( CString("Группа содержит элементы разных типов.\nНевозможно вызвать окно свойств элемента!"), 
				MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
			return;
		}
		//если в конце концов всё в порядке, то можно вызвать
		//диалог св-в.
		if( bElem )
		{
			POSITION pos = m_pSheme->listElem.GetHeadPosition();
			CElem *elem;
			while( pos )
			{
				//получаем указатель на первый элемент из этой группы
				if( CShemeGroup::IsElemContainsInGroup( m_pSheme->listElem.GetAt(pos), vec ) )
				{
					elem = m_pSheme->listElem.GetAt(pos);
					break;
				}
				m_pSheme->listElem.GetNext(pos);
			}

			if( elem->GoDlg( &m_pSheme->listKnot, false) )
			{
				//изменились св-ва элемента.
				//надо заполнить ими св-ва всех
				//элементов группы.
				pos = m_pSheme->listElem.GetHeadPosition();
				while( pos )
				{
					CElem *next_elem = m_pSheme->listElem.GetAt(pos);

					if( elem == next_elem )
					{
						m_pSheme->listElem.GetNext(pos);
						continue;
					}
					if( CShemeGroup::IsElemContainsInGroup( m_pSheme->listElem.GetAt(pos), vec ) )
					{
						if( !next_elem->SetCommonProperties(elem) )
						{
							//не возможно приведение типов, проводимое
							//в данной ф-ции.
							//это возможно, если группа содержит элементы
							//разных типов.
							//хотя до этого мы проверили такую возможность
							//но всё равно, на всякий случай, проверка повторяется.
							AfxMessageBox( CString("Внутренняя ошибка программы!!!\nОбратитесь к разработчику."), 
								MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
							return;
						}
					}
					m_pSheme->listElem.GetNext(pos);
				}//while(pos)
				SetModifiedFlag();
			}//elem->GoDlg( &listKnot, false)==1
		}//bElem==true
		else
		{
			POSITION pos = m_pSheme->listKnot.GetHeadPosition();
			CKnot *knot;
			while( pos )
			{
				//получаем указатель на первый узел из этой группы
				if( CShemeGroup::IsKnotContainsInGroup( m_pSheme->listKnot.GetAt(pos), vec ) )
				{
					knot = m_pSheme->listKnot.GetAt(pos);
					break;
				}
				m_pSheme->listKnot.GetNext(pos);
			}

			if( knot->GoDlg( false ) )
			{
				//изменились св-ва узла.
				//надо заполнить ими св-ва всех
				//узлов группы.
				pos = m_pSheme->listKnot.GetHeadPosition();
				while( pos )
				{
					CKnot *next_knot = m_pSheme->listKnot.GetAt(pos);

					if( knot == next_knot )
					{
						m_pSheme->listKnot.GetNext(pos);
						continue;
					}
					if( CShemeGroup::IsKnotContainsInGroup( m_pSheme->listKnot.GetAt(pos), vec ) )
					{
						next_knot->SetCommonProperties(knot);
					}
					m_pSheme->listKnot.GetNext(pos);
				}//while(pos)
				SetModifiedFlag();
			}//knot->GoDlg( false ) == 1
		}//bElem==false
	}//IDOK
	UpdateAllViews(NULL);
}

void CShemeDoc::OnGroupPreview() 
{
	ASSERT(m_pSheme);
	// TODO: Add your command handler code here
	CGroupListDlg dlg( m_pSheme->m_vecElemGroups, m_pSheme->m_vecKnotGroups, false );
	//false означает, что диалог создаётся только для
	//выбора одной группы из списка без возможности её редактирования
	//или удаления для дальнейшего удаления или редактирования
	//группы элементов(узлов) на основе выбранной группы.
	
	if( dlg.DoModal() == IDOK )
	{
		if( dlg.m_SelDlgItem == -1 )	return;

		int p = CShemeGroup::GetRealPosInGroup( dlg.m_arDel, dlg.m_SelDlgItem );
		int m = m_pSheme->m_vecElemGroups.size();
		bool bElem = (p<m)?true:false;
		CString str;
		int err;
		if( bElem )
			err = m_pSheme->IsGroupContainsNotexistingObject( bElem, m_pSheme->m_vecElemGroups[p], str, ParamView.m_vecSelNumbers );
		else
			err = m_pSheme->IsGroupContainsNotexistingObject( bElem, m_pSheme->m_vecKnotGroups[p-m], str, ParamView.m_vecSelNumbers );

		if( err == 2 )
		{
			AfxMessageBox( str, MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
			return;
		}

		if( err == 1 )
		{
			str += _T("\nПросмотреть что есть?");
			if( AfxMessageBox( str, MB_YESNO|MB_TASKMODAL|MB_ICONQUESTION ) == IDNO )
			{
				ParamView.m_vecSelNumbers.clear();
				return;
			}
		}

		PreviewGroup( bElem );
	}
	UpdateAllViews(NULL);
}

void CShemeDoc::OnAllDemf() 
{
	// TODO: Add your command handler code here
	m_pSheme->CreateGroupForAllObjects( IDC_DEMF );
}

void CShemeDoc::OnAllHardRods() 
{
	// TODO: Add your command handler code here
	m_pSheme->CreateGroupForAllObjects( IDC_HARDROD );
}

void CShemeDoc::OnAllMasses() 
{
	// TODO: Add your command handler code here
	m_pSheme->CreateGroupForAllObjects( IDC_MASS );
}

void CShemeDoc::OnAllRods() 
{
	// TODO: Add your command handler code here
	m_pSheme->CreateGroupForAllObjects( IDC_ROD );
}

void CShemeDoc::OnAllSprings() 
{
	// TODO: Add your command handler code here
	m_pSheme->CreateGroupForAllObjects( IDC_SPRING );
}

void CShemeDoc::OnGroupConvertTo() 
{
	// TODO: Add your command handler code here
	ASSERT(m_pSheme);
	//конвертировать можно только стержни
	Groups vecKnots;
	vecKnots.clear();//на всякий случай
	CGroupListDlg dlg( m_pSheme->m_vecElemGroups, vecKnots, false );
	//false означает, что диалог создаётся только для
	//выбора одной группы из списка без возможности её редактирования
	//или удаления для дальнейшего удаления или редактирования
	//группы элементов(узлов) на основе выбранной группы.

	if( dlg.DoModal() == IDOK )
	{
		if( dlg.m_SelDlgItem == -1 )
		{
			return;
		}
		//выбирается только группа элементов!!!
		CString str;
		ARRAY vec;
		int err = m_pSheme->IsGroupContainsNotexistingObject( true, m_pSheme->m_vecElemGroups[dlg.m_SelDlgItem], str, vec );

		if( err == 2 )
		{
			AfxMessageBox( str, MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
			return;
		}
		//выбранную группу элементов надо удалить из схемы:
		//теперь vec содержит массив номеров выбранных элементов
		if( err == 1 )
		{
			AfxMessageBox( str, MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
			return;
		}

		if( !m_pSheme->IsElemGroupOfOneType(vec) )
		{
			AfxMessageBox( CString("Группа содержит элементы разных типов."), 
				MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
			return;
		}
		//теперь ясно, что группа содержит элементы одного типа
		int elemType;
		POSITION pos2, pos = m_pSheme->listElem.GetHeadPosition();
		bool first = true;
		while( pos )
		{
			pos2 = pos;
			//проходим по всем элементам
			CElem *elem = m_pSheme->listElem.GetNext(pos);

			if( CShemeGroup::IsElemContainsInGroup( elem, vec ) )
			{
				if( first )
				{
					elemType = elem->TypeElem;
					if( !((elemType==IDC_ROD)||(elemType==IDC_HARDROD)) )
					{
						AfxMessageBox("Конвертация возможна только для стержней!", 
							MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
						return;
					}
					CConvertToDlg dlgCT( elemType );
					if( dlgCT.DoModal() == IDCANCEL )
					{
						return;
					}
					first = false;
				}
				if( elem->TypeElem != elemType )	continue;//такое может быть, если этот элемент уже был конвертирован
				//теперь читаем св-ва старого элемента
				CKnot *kn1 = elem->knot1, *kn2 = elem->knot2;
				CString E, F, J;
				double m;
				int num = elem->GetNumber();
				if( elemType == IDC_ROD )
				{
					E = ((CRod*)elem)->GetStrE();
					F = ((CRod*)elem)->GetStrF();
					J = ((CRod*)elem)->GetStrJx();
					//делаем из погонной массы массу стержня
					m = ((CRod*)elem)->GetM()*((CRod*)elem)->GetLength();
				}
				else
				{
					E = ((CHardRod*)elem)->GetStrE();
					F = ((CHardRod*)elem)->GetStrF();
					J = ((CHardRod*)elem)->GetStrJ();
					//делаем из массы стержня погонную массу
					m = ((CHardRod*)elem)->GetM()/((CHardRod*)elem)->GetLength();
				}
				CString M;
				M.Format("%.11e", m );
				//Удаление старого элемента из списка
				delete elem;
				m_pSheme->listElem.RemoveAt(pos2);
				//создаём новый 
				if( elemType == IDC_ROD )
				{
					CHardRod *rodNew = (CHardRod*)AddHardRod( kn1, kn2 );
					rodNew->SetE( E );
					rodNew->SetF( F );
					rodNew->SetJ( J );
					rodNew->SetM( M );
					rodNew->SetNumber( num );
				}
				else
				{
					CRod *rodNew = (CRod*)AddRod( kn1, kn2 );
					rodNew->SetE( E );
					rodNew->SetF( F );
					rodNew->SetJx( J );
					rodNew->SetM( M );
					rodNew->SetNumber( num );
				}
				pos = m_pSheme->listElem.GetHeadPosition();
			}//IsElemContainsInGroup==true
		}//while(pos)
		m_pSheme->SetConnectElements();
		SetModifiedFlag();
	}//dlg.DoModal() == IDOK
	UpdateAllViews(NULL);
}

void CShemeDoc::GroupClicking( int type )
{
	ASSERT(m_pSheme);
	if( ParamView.m_iClickedObjects == 0 )
	{
		ParamView.m_iClickedObjects = type;
		ParamView.m_vecSelNumbers.clear();
		ParamView.m_vecSelNumbers.push_back(0);
		m_pSheme->ClearAllSelectings();
	}
	else
	{
		ParamView.m_iClickedObjects = 0;
		std::sort( ParamView.m_vecSelNumbers.begin(),
					ParamView.m_vecSelNumbers.end() );
		ParamView.m_vecSelNumbers.assign( ParamView.m_vecSelNumbers.begin(),
			std::unique_copy( ParamView.m_vecSelNumbers.begin(), ParamView.m_vecSelNumbers.end(), ParamView.m_vecSelNumbers.begin() ) );
		ParamView.DelZeroInSelNumbers();
		if( ParamView.m_vecSelNumbers.empty() )
		{
			m_pSheme->ClearAllSelectings();
			return;
		}

		CString strGroup = CShemeGroup::GetPackedGroup( ParamView.m_vecSelNumbers );
		CShemeGroup gr( strGroup, (type==1)?(0):(1) );
		CGroupEditDlg dlg( &gr );
		if( dlg.DoModal() == IDOK )
		{
			gr.SetName( dlg.m_strGroupName );
			gr.SetGroup( dlg.m_strGroup );
			//здесь полагаем, что группа уже была проверена на
			//корректность в самом диалоге.
			if( type == 1 )
				m_pSheme->m_vecElemGroups.push_back( gr );
			else
				m_pSheme->m_vecKnotGroups.push_back( gr );
		}
		ParamView.m_vecSelNumbers.clear();
		m_pSheme->ClearAllSelectings();
	}
}

void CShemeDoc::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(FALSE);

	dlg.m_ofn.lpstrTitle = _T("Сохранить схему как...");

	CString strName = GetTitle();
	CString str;
	str += "Sheme Files v2.5 (*.shm)"; str += (TCHAR)NULL;
	str += "*.shm"; str += (TCHAR)NULL;
	str += "Sheme Files v3.0 (*.shm)"; str += (TCHAR)NULL;
	str += "*.shm"; str += (TCHAR)NULL;
	str += "All Files (*.*)"; str += (TCHAR)NULL;
	str += "*.*"; str += (TCHAR)NULL;

/*	char Filter[256];
	int size = str.GetLength(), pos = 0;
	for( int i = 0; i < size; ++i )
	{
		if( i >= 256 )
		{
			pos = 256-2;
			break;
		}
		Filter[i] = str[i];
		pos = i;
	}
	Filter[pos+1] = '\0';
	dlg.m_ofn.lpstrFilter = Filter;*/
	dlg.m_ofn.lpstrFilter = static_cast<LPCTSTR>(str);

	dlg.m_ofn.nFilterIndex = 2;
	dlg.m_ofn.lpstrDefExt = _T("shm");
	dlg.m_ofn.Flags |= OFN_OVERWRITEPROMPT;

	const int N = 80;
	char FileName[N];
/*	size = strName.GetLength();
	pos = 0;
	for( i = 0; i < size; ++i )
	{
		if( i >= N )
		{
			pos = N-2;
			break;
		}
		FileName[i] = strName[i];
		pos = i;
	}
	FileName[pos+1] = '\0';*/
	strncpy( FileName, strName.LockBuffer(), N );
	strName.UnlockBuffer();
	dlg.m_ofn.lpstrFile = FileName;
	dlg.m_ofn.nMaxFile = N;

	while( dlg.DoModal() == IDOK )
	{
		if( dlg.m_ofn.Flags & OFN_EXTENSIONDIFFERENT )
		{
			int ret = AfxMessageBox("Набрано некорректное расширение.\nСохранить с таким расширением?",
								MB_YESNOCANCEL|MB_TASKMODAL|MB_ICONQUESTION);
			if( ret == IDNO )
			{
				m_pSheme->m_verShemeVersion = VER_EQ30;
				continue;
			}
			else	if( ret = IDCANCEL )	return;
		}
		if( dlg.m_ofn.nFilterIndex == 1 )
		{
			if( AfxMessageBox("Выбран устаревший формат файла.\nНе все возможности будут сохранены.\nСохранить?",
								MB_YESNO|MB_TASKMODAL|MB_ICONQUESTION) == IDNO )
			{
				m_pSheme->m_verShemeVersion = VER_EQ30;
				return;
			}
			if( m_pSheme->IsShemeContainsHardRod() )
			{
				CString mes("Схема содержит абс.жёсткие стержни, которые не могут быть сохранены в данном формате.");
				mes += _T("\nКонвертируйте все жёсткие стержни в обычные и снова попытайтесь сохраниться.");
				AfxMessageBox( mes, MB_OK|MB_TASKMODAL|MB_ICONEXCLAMATION );
				return;
			}
			m_pSheme->m_verShemeVersion = VER_LE25;
		}
		else
			m_pSheme->m_verShemeVersion = VER_EQ30;

		CString strPathName( dlg.GetPathName() );
		CFile F( strPathName, CFile::modeCreate|CFile::modeWrite );
		CArchive ar( &F, CArchive::store );
		
		Serialize( ar );
		SetTitle( dlg.GetFileName() );
		ar.Flush();
		F.Flush();
		F.Close();
		m_pSheme->m_verShemeVersion = VER_EQ30;

		SetModifiedFlag(FALSE);
		SetPathName( strPathName );
		break;
	}
}

void CShemeDoc::OnGroupClickElems() 
{
	// TODO: Add your command handler code here
	GroupClicking( 1 );//набрать группу элементов
	UpdateAllViews(NULL);
}

void CShemeDoc::OnGroupClickKnots() 
{
	// TODO: Add your command handler code here
	GroupClicking( 2 );//набрать группу узлов
	UpdateAllViews(NULL);	
}

void CShemeDoc::OnUpdateGroupClickElems(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( ParamView.m_iClickedObjects == 1 );
	pCmdUI->Enable( ParamView.m_iClickedObjects != 2 );
}

void CShemeDoc::OnUpdateGroupClickKnots(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( ParamView.m_iClickedObjects == 2 );
	pCmdUI->Enable( ParamView.m_iClickedObjects != 1 );	
}

void CShemeDoc::OnButtonDelFreeKnots() 
{
	// TODO: Add your command handler code here
	//Удаление пустых узлов
	m_pSheme->DelFreeKnot();
	UpdateAllViews(NULL);
}

void CShemeDoc::OnAutoCorrect() 
{
	// TODO: Add your command handler code here
	m_pSheme->m_bAutoCorrect = !m_pSheme->m_bAutoCorrect;
}

void CShemeDoc::OnUpdateAutoCorrect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( (m_pSheme->m_bAutoCorrect)?(1):(0) );
}

void CShemeDoc::OnUpdateAllDemf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}

void CShemeDoc::OnUpdateAllHardrods(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}

void CShemeDoc::OnUpdateAllMasses(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}

void CShemeDoc::OnUpdateAllRods(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}

void CShemeDoc::OnUpdateAllSprings(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}

void CShemeDoc::OnUpdateCalc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}

void CShemeDoc::OnUpdateButtonDelFreeKnots(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}

void CShemeDoc::OnUpdateListelem(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}
void CShemeDoc::OnUpdateElemgroupDel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}

void CShemeDoc::OnUpdateElemgroupProp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}

void CShemeDoc::OnUpdateGroupConvertTo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}

void CShemeDoc::OnUpdateShemeParams(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}

void CShemeDoc::OnUpdateGroupNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}

void CShemeDoc::OnUpdateGroupList(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}

void CShemeDoc::OnUpdateGroupPreview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ParamView.m_iClickedObjects == 0 );
}


void CShemeDoc::OnFreeNums() 
{
	// TODO: Add your command handler code here
	m_pSheme->ResetAllFree();
	ParamView.m_bFreeNums = true;
	ParamView.Gray = TRUE;
	UpdateAllViews(NULL);

	CGroupPreviewDlg dlgGP;
	dlgGP.DoModal();

	UpdateAllViews(NULL);
	ParamView.Gray = FALSE;
	ParamView.m_bFreeNums = false;
}
