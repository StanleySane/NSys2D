// ShemeView.cpp : implementation of the CShemeView class
//

#include "stdafx.h"
#include "NSys2D.h"

#include "ShemeDoc.h"
#include "ShemeView.h"

//#include "GraphView.h"
#include "TypeGraphDlg.h"

#include "GraphFrm.h"
#include "ShemeGroup.h"
#include "GraphicView.h"
#include "FreqDlg.h"
#include "SpectrDlg.h"
#include "ProgressDlg.h"
#include "ComplexMatr.h"
#include "MeshElemDlg.h"
#include "ConvertToDlg.h"
#include "Sheme.h"

#include <math.h>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShemeView

IMPLEMENT_DYNCREATE(CShemeView, CScrollView)

BEGIN_MESSAGE_MAP(CShemeView, CScrollView)
	//{{AFX_MSG_MAP(CShemeView)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_ADDGRAPH, OnAddgraph)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_ADDROD, OnAddrod)
	ON_COMMAND(ID_SCALEADD, OnScaleadd)
	ON_COMMAND(ID_SCALESUB, OnScalesub)
	ON_UPDATE_COMMAND_UI(ID_SETDEMF, OnUpdateSetdemf)
	ON_UPDATE_COMMAND_UI(ID_SETROD, OnUpdateSetrod)
	ON_UPDATE_COMMAND_UI(ID_SETSPRING, OnUpdateSetspring)
	ON_COMMAND(ID_SETDEMF, OnSetdemf)
	ON_COMMAND(ID_SETROD, OnSetrod)
	ON_COMMAND(ID_SETSPRING, OnSetspring)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_TIMER()
	ON_COMMAND(ID_ADDDEMF, OnAdddemf)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_ADDSPRING, OnAddspring)
	ON_UPDATE_COMMAND_UI(ID_ADDGRAPH, OnUpdateAddgraph)
	ON_UPDATE_COMMAND_UI(ID_SETMASS, OnUpdateSetmass)
	ON_COMMAND(ID_SETMASS, OnSetmass)
	ON_COMMAND(ID_ADDMASS, OnAddmass)
	ON_COMMAND(ID_DELELEM, OnDelelem)
	ON_UPDATE_COMMAND_UI(ID_DELELEM, OnUpdateDelelem)
	ON_UPDATE_COMMAND_UI(ID_SETNULL, OnUpdateSetnull)
	ON_COMMAND(ID_SETNULL, OnSetnull)
	ON_UPDATE_COMMAND_UI(ID_PROP, OnUpdateProp)
	ON_COMMAND(ID_PROP, OnProp)
	ON_COMMAND(ID_REFRESH, OnRefresh)
	ON_COMMAND(ID_FREQ_CALC, OnFreqCalc)
	ON_UPDATE_COMMAND_UI(ID_FREQ_CALC, OnUpdateFreqCalc)
	ON_COMMAND(ID_SPECTR_CALC, OnSpectrCalc)
	ON_WM_DESTROY()
	ON_COMMAND(ID_SETHARDROD, OnSetHardRod)
	ON_UPDATE_COMMAND_UI(ID_SETHARDROD, OnUpdateSetHardRod)
	ON_COMMAND(ID_ADDHARDROD, OnAddHardRod)
	ON_UPDATE_COMMAND_UI(ID_MESH_ELEM, OnUpdateMeshElem)
	ON_COMMAND(ID_MESH_ELEM, OnMeshElem)
	ON_COMMAND(ID_BUTTON_AUTO_SIZE, OnButtonAutoSize)
	ON_UPDATE_COMMAND_UI(ID_CONVERT_TO, OnUpdateConvertTo)
	ON_COMMAND(ID_CONVERT_TO, OnConvertTo)
	ON_UPDATE_COMMAND_UI(ID_ADDDEMF, OnUpdateAdddemf)
	ON_UPDATE_COMMAND_UI(ID_ADDHARDROD, OnUpdateAddhardrod)
	ON_UPDATE_COMMAND_UI(ID_ADDMASS, OnUpdateAddmass)
	ON_UPDATE_COMMAND_UI(ID_ADDROD, OnUpdateAddrod)
	ON_UPDATE_COMMAND_UI(ID_ADDSPRING, OnUpdateAddspring)
	ON_UPDATE_COMMAND_UI(ID_SPECTR_CALC, OnUpdateSpectrCalc)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, OnUpdateFileClose)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateFilePrintSetup)
	ON_COMMAND(ID_AUTO_SCALE, OnButtonAutoSize)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

CCoordD MousePos;

/////////////////////////////////////////////////////////////////////////////
// CShemeView construction/destruction

CShemeView::CShemeView()
{
	// TODO: add construction code here
	coordLast=coordEnd=coordStart=0;
	DrawAll=KnotOnly=DrawOnce=StateNew=0;
	pKnotBeg=pKnotEnd=SelKnot=OldSelKnot=0;
	OldSelElem=SelElem=0;
	TypeElem=IDC_NULL;
	LineNear=0;
	InitialUpdate=FALSE;
	m_bClickingGroup = false;
}

CShemeView::~CShemeView()
{
}

BOOL CShemeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CShemeView drawing

void CShemeView::OnDraw(CDC* pDC)
{
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if( m_bClickingGroup = (pDoc->ParamView.m_iClickedObjects != 0) )
		TypeElem = IDC_NULL;

	if (StateNew)
	{
		//CPen pen(PS_DOT|PS_GEOMETRIC,1,RGB(0,0,0));
		CPen pen(PS_DOT|PS_COSMETIC,1,RGB(0,0,0));
		CPen *pOld=(CPen*)pDC->SelectObject(&pen);

		int oldpop2=pDC->GetROP2();
		pDC->SetROP2(R2_XORPEN);

		POINT point1=ShemeToScreen(coordStart);
		POINT point2=ShemeToScreen(coordLast);
		POINT point3=ShemeToScreen(coordEnd);

		if (!DrawOnce)
		{
			pDC->MoveTo(point1.x,point1.y);
			pDC->LineTo(point2.x,point2.y);
		}

		pDC->MoveTo(point1.x,point1.y);
		pDC->LineTo(point3.x,point3.y);
		pDC->SetROP2(oldpop2);
		coordLast=coordEnd;

		pDC->SelectObject(pOld);
	}
	bool bDrawGroup = !pDoc->ParamView.m_vecSelNumbers.empty();
	//bDrawGroup - флаг, показывающий рисуется сейчас группа или нет
	if (((!StateNew)||(DrawOnce))&&((!KnotOnly)||(DrawAll)))
	{
		POSITION pos=pDoc->m_pSheme->listElem.GetHeadPosition();
		while (pos)
		{
			CElem *elem=pDoc->m_pSheme->listElem.GetNext(pos);
			int iOldMode;

			if( bDrawGroup )
			{
				iOldMode = elem->SelectMode;
				//изначально делаем элемент нерисуемым
				elem->SelectMode = 0;
				pDoc->ParamView.Gray = TRUE;

				if( (pDoc->ParamView.m_bSelType)||(pDoc->ParamView.m_iClickedObjects!=0) )
				{
					//если надо нарисовать выделенную группу элементов
					//(а не узлов)
					if( CShemeGroup::IsElemContainsInGroup(elem,pDoc->ParamView.m_vecSelNumbers) )
					{
						//и данный элемент содержится в ней,
						//то его надо сделать выделенным
						if( pDoc->ParamView.m_iClickedObjects == 0 )
						{
							elem->SelectMode = 1;
							pDoc->ParamView.Gray = FALSE;
						}
					}
					else
					{
						if( pDoc->ParamView.m_iClickedObjects == 1 )
						{
							pDoc->ParamView.Gray = FALSE;
						}
					}
				}
				//если же рисуются только узлы, то
				//элемент остаётся нерисуемым,
			}//bDrawGroup==true
			elem->Draw(pDC,&pDoc->ParamView);
			if( bDrawGroup )	elem->SelectMode = iOldMode;
		}
		DrawAll=DrawOnce=0;
	}
	if( bDrawGroup )
	{
		pDoc->ParamView.Gray = FALSE;
		return;
	}

	if (OldSelKnot!=SelKnot) 
	{
		if (OldSelKnot) 
		{ OldSelKnot->SelectMode=0; OldSelKnot->Draw(pDC,&pDoc->ParamView);}
		OldSelKnot=SelKnot;
		if (SelKnot) 	SelKnot->Draw(pDC,&pDoc->ParamView);
	}
	if (OldSelElem!=SelElem)
	{
		if (OldSelElem) 
		{	OldSelElem->SelectMode=0; OldSelElem->Draw(pDC,&pDoc->ParamView); }
		OldSelElem=SelElem;
		if (SelElem)	SelElem->Draw(pDC,&pDoc->ParamView);
	}
	KnotOnly=0;
}

void CShemeView::OnInitialUpdate()
{
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	RECT rect;
	GetClientRect(&rect);
	pDoc->ParamView.pos=CPoint(0,0);
	SetScrollView();
	InitialUpdate=TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CShemeView diagnostics

#ifdef _DEBUG
void CShemeView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CShemeView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CShemeDoc* CShemeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShemeDoc)));
	return (CShemeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShemeView message handlers

void CShemeView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CScrollView::OnRButtonDown(nFlags, point);

    GetParentFrame()->ActivateFrame();

	if( m_bClickingGroup )
	{
		CShemeDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		bool update = false;
		//если такой эл-т(узел) уже есть в массиве
		// номеров, то удаляем его из массива
		if( SelKnot && (pDoc->ParamView.m_iClickedObjects==2) )
		{
			ARRAY::iterator end = pDoc->ParamView.m_vecSelNumbers.end();

			pDoc->ParamView.m_vecSelNumbers.erase( 
				std::remove( pDoc->ParamView.m_vecSelNumbers.begin(),
					end, SelKnot->Num ), end );
			update = true;
		}
		if( SelElem && (pDoc->ParamView.m_iClickedObjects==1) )
		{
			ARRAY::iterator end = pDoc->ParamView.m_vecSelNumbers.end();

			pDoc->ParamView.m_vecSelNumbers.erase( 
				std::remove( pDoc->ParamView.m_vecSelNumbers.begin(),
					end, SelElem->GetNumber() ), end );
			update = true;
		}
		if( update )
		{
			DrawAll = 1;
			Invalidate();
		}
		return;
	}

    CPoint local = point;
	ClientToScreen(&local);
    //ScreenToClient(&local);
    //ClientToDoc(local);

    CMenu menu;
    if (menu.LoadMenu(IDR_POPUPMENUSHEME))
    {
        CMenu* pPopup = menu.GetSubMenu(0);
        ASSERT(pPopup != NULL);
            
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
          local.x, local.y,
             AfxGetMainWnd()); // use main window for cmds
    }
}

void CShemeView::OnAddgraph() 
{
	// TODO: Add your command handler code here
	ASSERT(SelKnot);

	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//спрашиваем: "Что выводить?"
	CTypeGraphDlg dlg;
	if (dlg.DoModal()!=IDOK) return;

	CString str=pDoc->GetTitle();
	str+=_T(" (Узел №");
	CString str2;
	str2.Format("%d",SelKnot->Num);
	str+=str2+_T(") ");
	switch (dlg.m_SelectV)
	{
	case 0:
			str+=_T("Ux");
			break;
	case 1:
			str+=_T("Uy");
			break;
	case 2:
			str+=_T("Ua");
			break;
	case 3:
			str+=_T("Ux'");
			break;
	case 4:
			str+=_T("Uy'");
			break;
	case 5:
			str+=_T("Ua'");
			break;
	case 6:
			str+=_T("Ux''");
			break;
	case 7:
			str+=_T("Uy''");
			break;
	case 8:
			str+=_T("Ua''");
			break;
	case 9:
			str+=_T("t");
			break;
	}
	str+=_T("(");
	switch (dlg.m_SelectH)
	{
	case 0:
			str+=_T("Ux");
			break;
	case 1:
			str+=_T("Uy");
			break;
	case 2:
			str+=_T("Ua");
			break;
	case 3:
			str+=_T("Ux'");
			break;
	case 4:
			str+=_T("Uy'");
			break;
	case 5:
			str+=_T("Ua'");
			break;
	case 6:
			str+=_T("Ux''");
			break;
	case 7:
			str+=_T("Uy''");
			break;
	case 8:
			str+=_T("Ua''");
			break;
	case 9:
			str+=_T("t");
			break;
	}
	str+=_T(")");

	CNSys2DApp* pApp=(CNSys2DApp*)AfxGetApp();

	POSITION pos = pApp->GetFirstDocTemplatePosition();
	pApp->GetNextDocTemplate(pos);
	CDocTemplate *pTemplate = pApp->GetNextDocTemplate(pos);

	//CMDIChildWnd* 
	CGraphFrame *pNewFrame	= (CGraphFrame*)(pTemplate->CreateNewFrame(pDoc, NULL));
	ASSERT(pNewFrame!=NULL);
	
	
	pTemplate->InitialUpdateFrame(pNewFrame, pDoc);

	CGraphicView *pGraphView = (CGraphicView*)pNewFrame->GetActiveView();
	ASSERT (pGraphView != NULL);

	pGraphView->pKnot=SelKnot;
	//Установка переменной по горизонтали
	pGraphView->TypeX=dlg.m_SelectH;
	//Установка переменной по вертикали
	pGraphView->TypeY=dlg.m_SelectV;
	pGraphView->str_title=_T("Интегрирование ")+str;
	//Начальная установка границ изображения
	pGraphView->SetMaxMin();

	pNewFrame->SetWindowText(str);

	pDoc->UpdateAllViews(0);
}

void CShemeView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//если набираем группу,
	bool update = false;
	if( pDoc->ParamView.m_iClickedObjects != 0 )
	{
		//то заносим выбранный объект в список
		if( SelKnot && (pDoc->ParamView.m_iClickedObjects==2) )
		{
			pDoc->ParamView.m_vecSelNumbers.push_back(SelKnot->Num);
			update = true;
		}
		if( SelElem && (pDoc->ParamView.m_iClickedObjects==1) )
		{
			pDoc->ParamView.m_vecSelNumbers.push_back(SelElem->GetNumber());
			update = true;
		}
	}

	if (nFlags&MK_CONTROL)
	{
		if ( (SelKnot) && (SelKnot->GoDlg()) )  
		{
			SetScrollView();
			DrawAll=1;
			Invalidate(TRUE);
		}
		else 
			if ( (SelElem) && (SelElem->GoDlg(&pDoc->m_pSheme->listKnot)) ) 
			{
				SetScrollView();
				DrawAll=1;
				Invalidate(TRUE);
			}
	}
	else
	{
		if (TypeElem==IDC_MASS)
		{
			coordEnd=ScreenToSheme(point);
			char strex[50],strey[50];
			sprintf(strex,"%lf",coordEnd.x);
			sprintf(strey,"%lf",coordEnd.y);

			CKnot *knot=
				(SelKnot? SelKnot: pDoc->m_pSheme->listKnot.AddKnot( CKnot(strex,strey) ) );
			pDoc->m_pSheme->AddMass(knot);
			Invalidate(TRUE);
		}
/*		Новый КЭ добавлять здесь			*/
/*		else if	. . .						*/
/*		{									*/
/*											*/
/*		}									*/
		else
		{
			if (SelKnot)
			{
				coordLast=coordEnd=coordStart=SelKnot->GetCoord();
				pKnotBeg=SelKnot;
			}
			else
			{
				coordLast=coordEnd=coordStart=ScreenToSheme(point);
				pKnotEnd=pKnotBeg=0;
			}
			if (TypeElem!=IDC_NULL) StateNew=1;
		}
	}
	if( update )
	{
		DrawAll = 1;
		Invalidate(TRUE);
	}

	CScrollView::OnLButtonDown(nFlags, point);
}

CCoordD CShemeView::ScreenToSheme(CPoint &point)
{
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	return CCoordD(
	(point.x+pDoc->ParamView.pos.x )/pDoc->ParamView.Scale+pDoc->ParamView.MoveCenter.x,
	-(point.y+pDoc->ParamView.pos.y)/pDoc->ParamView.Scale+pDoc->ParamView.MoveCenter.y);
}

void CShemeView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!StateNew) return;
	if (SelKnot) pKnotEnd=SelKnot;

	if (LineNear)
	{
		CPoint p=ShemeToScreen(coordStart,TRUE);
		CCoordD c=ScreenToSheme(point);
		if (fabs(c.x-coordStart.x)<fabs(c.y-coordStart.y))		
			point.x=p.x;
		else											
			point.y=p.y;
	}
	
	coordEnd=ScreenToSheme(point);
	// создавать двухузловой эл-т только если задано два узла
	if( !(coordEnd == coordStart) )
	{
		char strbx[50],strby[50],strex[50],strey[50];

		sprintf(strbx,"%lf",coordStart.x);
		sprintf(strby,"%lf",coordStart.y);
		sprintf(strex,"%lf",coordEnd.x);
		sprintf(strey,"%lf",coordEnd.y);

		CKnot *knotstart=
			(pKnotBeg? pKnotBeg: pDoc->m_pSheme->listKnot.AddKnot( CKnot(strbx,strby) ) );
		CKnot *knotend=
			(pKnotEnd? pKnotEnd: pDoc->m_pSheme->listKnot.AddKnot( CKnot(strex,strey) ) );

		if (knotstart!=knotend)
		{
			switch(TypeElem)
			{
			case IDC_ROD:
				{
					pDoc->AddRod(knotstart,knotend);
					break;
				}
			case IDC_HARDROD:
				{
					pDoc->AddHardRod(knotstart,knotend);
					break;
				}
			case IDC_DEMF:
				{
					pDoc->AddDemf(knotstart,knotend);
					break;
				}
			case IDC_SPRING:
				{
					pDoc->AddSpring(knotstart,knotend);
					break;
				}
			case IDC_MASS:
				{
					pDoc->AddMass(knotend);
					break;
				}
			}//switch
		}//if(knotstart!=knotend)
	}
	pKnotEnd=pKnotBeg=0;
	StateNew=0;
	if (SelKnot)	SelKnot->SelectMode=0;

	CScrollView::OnLButtonUp(nFlags, point);

	SetScrollView();////////////////
	SelKnot=FindKnot(point);
	if (SelKnot)	
		SelKnot->SelectMode=1;
		
	DrawAll=1;
	Invalidate(TRUE);
}

void CShemeView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (LineNear)
	{
		CPoint p=ShemeToScreen(coordStart,TRUE);
		CCoordD c=ScreenToSheme(point);
		if (fabs(c.x-coordStart.x)<fabs(c.y-coordStart.y))		
			point.x=p.x;
		else											
			point.y=p.y;
	}

	MousePos = ScreenToSheme(point);

	SelKnot=FindKnot(point);
	if ( (SelKnot!=OldSelKnot)  )
	{
		if (SelKnot)	
		{
			SelKnot->SelectMode=1;
			if (SelElem) 
			{
				SelElem->SelectMode=0;
				SelElem=0;
			}
		}
		KnotOnly=1;
		Invalidate(FALSE);
	}
	else if (!SelKnot)
	{
		if ( ((nFlags&MK_CONTROL)&&(TypeElem!=IDC_NULL))||
			 (TypeElem==IDC_NULL) )
		{
			SelElem=FindElem(point);	
			if (SelElem!=OldSelElem) 
			{
				//if (OldSelElem) OldSelElem->SelectMode=0;
				if (SelElem)
					SelElem->SelectMode=1;
				KnotOnly=1;
				Invalidate(FALSE);
			}
		}
		else
		{
			if (SelElem)
			{
				SelElem->SelectMode=0;
				KnotOnly=1;
				Invalidate(FALSE);
				SelElem=0;
			}
		}
	}
	if (StateNew) IsScroll(point);
	else KillAllTimer(4);
	if (StateNew)
	{
		if (nFlags&MK_LBUTTON)
		{
			coordEnd=ScreenToSheme(point);
			Invalidate(FALSE);
		}
		else
		{
			StateNew=0;
			Invalidate(TRUE);
		}
	}

	CScrollView::OnMouseMove(nFlags, point);
}

POINT CShemeView::ShemeToScreen(CCoordD &coord, BOOL scroll/*=FALSE*/)
{
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POINT point;

	point.x=long(+pDoc->ParamView.Scale*(coord.x-pDoc->ParamView.MoveCenter.x)+0.55555);//+pDoc->ParamView.pos.x;
	point.y=long(-pDoc->ParamView.Scale*(coord.y-pDoc->ParamView.MoveCenter.y)+0.55555);//+pDoc->ParamView.pos.y;
	if (scroll)
	{
		point.x-=pDoc->ParamView.pos.x;
		point.y-=pDoc->ParamView.pos.y;
	}

	return point;
}

CKnot* CShemeView::FindKnot(CPoint & point)
{
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CKnot *kn;
	CPoint pt;
	
	POSITION pos=pDoc->m_pSheme->listKnot.GetHeadPosition();
	while (pos)
	{
		kn=pDoc->m_pSheme->listKnot.GetNext(pos);
		pt=kn->GetScreenCoord(&pDoc->ParamView)-pDoc->ParamView.pos;

		const int rad=3;

		if ( (abs(pt.x-point.x)<=rad)&&
			 (abs(pt.y-point.y)<=rad) )
		{
			return kn;
		}
	}
	return 0;	
}

CElem* CShemeView::FindElem(CPoint & point)
{
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	const double rad=2;

	CElem *elem,*elemMin=0;
	double hMin=10E10;
	
	POSITION pos=pDoc->m_pSheme->listElem.GetHeadPosition();
	while (pos)
	{
		elem=pDoc->m_pSheme->listElem.GetNext(pos);

		CCoordD c1=elem->knot1->GetCoord();
		CCoordD c2=elem->knot2->GetCoord();
		CCoordD c3=ScreenToSheme(point);

		double h;
		if (elem->TypeElem==IDC_MASS)
		{
			h=sqrt((c3.x-c1.x)*(c3.x-c1.x)+(c3.y-c1.y)*(c3.y-c1.y));
			if ((h*pDoc->ParamView.Scale)>6) continue;
		}
		else
		{

			double F=(c1.x*c2.y-c2.x*c1.y)+(c2.x*c3.y-c3.x*c2.y)+(c3.x*c1.y-c1.x*c3.y);
			double L2=(c1.x-c2.x)*(c1.x-c2.x)+(c1.y-c2.y)*(c1.y-c2.y);
			h=fabs(F)/sqrt(L2);
			
			if ( (h*pDoc->ParamView.Scale)>rad ) continue;
			if ( (c1.x-c3.x)*(c1.x-c3.x)+(c1.y-c3.y)*(c1.y-c3.y)>L2) continue;
			if ( (c2.x-c3.x)*(c2.x-c3.x)+(c2.y-c3.y)*(c2.y-c3.y)>L2) continue;
		}
		if (hMin>=h)
		{
			if ( (elem->TypeElem==IDC_ROD) || (rand()>(RAND_MAX/2.0)) )
			{
				hMin=h;
				elemMin=elem;
			}
		}
	}
	return elemMin;	
}

void CShemeView::OnAddrod() 
{
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: Add your command handler code here
	CRod rod(0,0);
	int ret=rod.GoDlg(&pDoc->m_pSheme->listKnot);

	if (ret) 
	{
		CElem *elem=pDoc->AddRod(rod.knot1,rod.knot2);
		int num = elem->GetNumber();
		if (elem) *elem=rod;
		elem->SetNumber( num );
		//pDoc->SetModifiedFlag();
		SetScrollView();////////////////
		
		Invalidate(TRUE);
	}
}


void CShemeView::OnScaleadd() 
{
	// TODO: Add your command handler code here
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->ParamView.Scale*=sqrt(2);
	SetScrollView();
	pDoc->UpdateAllViews(this);
	Invalidate(TRUE);
}

void CShemeView::OnScalesub() 
{
	// TODO: Add your command handler code here
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->ParamView.Scale/=sqrt(2);
	SetScrollView();
	pDoc->UpdateAllViews(this);
	Invalidate(TRUE);
}

void CShemeView::OnUpdateSetdemf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bClickingGroup );
	pCmdUI->SetCheck( TypeElem==IDC_DEMF );
}

void CShemeView::OnUpdateSetrod(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bClickingGroup );
	pCmdUI->SetCheck( TypeElem==IDC_ROD );
}

void CShemeView::OnUpdateSetspring(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bClickingGroup );
	pCmdUI->SetCheck( TypeElem==IDC_SPRING );
}

void CShemeView::OnSetdemf() 
{
	// TODO: Add your command handler code here
	TypeElem=IDC_DEMF;
}

void CShemeView::OnSetrod() 
{
	// TODO: Add your command handler code here
	TypeElem=IDC_ROD;
}

void CShemeView::OnSetspring() 
{
	// TODO: Add your command handler code here
	TypeElem=IDC_SPRING;
}

int CShemeView::SetScrollView()
{
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	double maxx = 0, maxy = 0, minx = 0, miny = 0;
	int First=1;
	POSITION pos=pDoc->m_pSheme->listKnot.GetHeadPosition();
	while (pos)
	{
		CKnot *kn=pDoc->m_pSheme->listKnot.GetNext(pos);
		CCoordD c=kn->GetCoord();
		if (First)	
		{
			minx=maxx=c.x;	miny=maxy=c.y;
			First=0;
		}
		else
		{
			if (c.x<minx) minx=c.x;
			if (c.x>maxx) maxx=c.x;
			if (c.y<miny) miny=c.y;
			if (c.y>maxy) maxy=c.y;
		}
	}
	
	double sc=pDoc->ParamView.Scale;
	
	CSize scroll;
	scroll.cx=int((maxx-minx)*sc+100);
	scroll.cy=int((maxy-miny)*sc+100);

	pDoc->ParamView.MoveCenter=CCoordD(minx-75/sc,maxy+75/sc);
	
	//CRect rect;
	//GetClientRect(&rect);

	//CPoint p=rect.TopLeft();
	//rect.SetRect(p.x,p.y,scroll.cx+p.x,scroll.cy+p.y);

	//MoveWindow(p.x, p.y, scroll.cx+p.x+10, scroll.cy+p.y+10);



/*	if (rect.Width()>scroll.cx) rectWindow.cx=

	scroll.cx=max( rect.Width(),int((maxx-minx)*sc+50) );
	scroll.cy=max( rect.Height(),int((maxy-miny)*sc+50) );*/
	
	SetScrollSizes(MM_TEXT, scroll);
	pDoc->ParamView.pos=GetScrollPosition();
	return 1;
}

void CShemeView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	
	if (InitialUpdate)//nType==SIZE_MAXIMIZED)
	{
		CShemeDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->ParamView.pos=GetScrollPosition();
		Invalidate(FALSE);
	}
}


void CShemeView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
	pDoc->ParamView.pos=GetScrollPosition();
	Invalidate(FALSE);
}

void CShemeView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
	pDoc->ParamView.pos=GetScrollPosition();
	Invalidate(FALSE);
}

BOOL CShemeView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	// TODO: Add your specialized code here and/or call the base class
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->ParamView.pos=GetScrollPosition();

	return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}


void CShemeView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	switch (nIDEvent)
	{
	case 1://bottom
		{
			CSize sz=GetTotalSize();
			CPoint point=GetScrollPosition();
			CRect rect;
			GetClientRect(rect);

			if ((sz.cy-rect.Height())<=point.y)
				SetScrollSizes(MM_TEXT, CSize(sz.cx, sz.cy+3));	
			ScrollToPosition(CPoint(point.x, point.y+3) );
			
			pDoc->ParamView.pos=GetScrollPosition();
			if (StateNew) DrawOnce=1;
			Invalidate(TRUE);
			break;
		}
	case 2://top
		{
			CSize sz=GetTotalSize();
			CPoint point=GetScrollPosition();
			//CRect rect;
			//GettClientRect(rect);

			if (point.y==0)
			{
				SetScrollSizes(MM_TEXT, CSize(sz.cx, sz.cy+3) );
				pDoc->ParamView.MoveCenter.y+=3/pDoc->ParamView.Scale;
			}
			else
				ScrollToPosition(CPoint(point.x, point.y-3) );
			
			pDoc->ParamView.pos=GetScrollPosition();
			if (StateNew) DrawOnce=1;
			Invalidate(TRUE);
			break;
		}
	case 3://left
		{
			CSize sz=GetTotalSize();
			CPoint point=GetScrollPosition();
			CRect rect;
			GetClientRect(rect);

			if (point.x==0)
			{
				SetScrollSizes(MM_TEXT, CSize(sz.cx+3, sz.cy) );
				pDoc->ParamView.MoveCenter.x-=3/pDoc->ParamView.Scale;
			}
			else
				ScrollToPosition(CPoint(point.x-3, point.y) );
			
			pDoc->ParamView.pos=GetScrollPosition();
			if (StateNew) DrawOnce=1;
			Invalidate(TRUE);
			break;
		}
	case 4://right
		{
			CSize sz=GetTotalSize();
			CPoint point=GetScrollPosition();
			CRect rect;
			GetClientRect(rect);

			if ((sz.cx-rect.Width())<=point.x)
				SetScrollSizes(MM_TEXT, CSize(sz.cx+3, sz.cy));	
			ScrollToPosition(CPoint(point.x+3, point.y) );
			
			pDoc->ParamView.pos=GetScrollPosition();
			if (StateNew) DrawOnce=1;
			Invalidate(TRUE);
			break;
		}
	}

	CScrollView::OnTimer(nIDEvent);
}

int CShemeView::IsScroll(CPoint &pos)
{
	CRect rect;
	GetClientRect(rect);
	KillAllTimer(4);
	if ((rect.Height()-1)==pos.y) 
		SetTimer(1,20,0);//bottom
	if (pos.y==0) 
		SetTimer(2,20,0);//top
	if (pos.x==0) 
		SetTimer(3,20,0);//left
	if (pos.x==(rect.Width()-1)) 
		SetTimer(4,20,0);//right
	return 0;
}

void CShemeView::KillAllTimer(int count)
{
	for (int i=1;i<=count;i++)
		KillTimer(i);
}

void CShemeView::OnAdddemf() 
{
	// TODO: Add your command handler code here
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDemf demf(0,0);
	int ret=demf.GoDlg(&pDoc->m_pSheme->listKnot);

	if (ret) 
	{
		CElem *elem=pDoc->AddDemf(demf.knot1,demf.knot2);
		int num = elem->GetNumber();
		if (elem) *elem=demf;
		elem->SetNumber( num );
		SetScrollView();
		
		Invalidate(TRUE);
	}
}


void CShemeView::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code
		CRect rect;
		((CMDIChildWnd*)GetOwner())->GetWindowRect(&rect);
		ar << rect;		
	}
	else
	{	// loading code
		CRect rect;
		ar >> rect;
		((CMDIChildWnd*)GetOwner())->MoveWindow(&rect);

		SetScrollView();
	}
}

void CShemeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (StateNew && ((nFlags&0x0ff)==42) )
	{
		LineNear=1;
		//SendMessage
		//fwKeys = wParam;        // key flags 
		//xPos = LOWORD(lParam);  // horizontal position of cursor 
		//yPos = HIWORD(lParam);  // vertical position of cursor 
 
		CPoint p=ShemeToScreen(coordLast,TRUE);
		int x=HIWORD((p.y<<16)+p.x);
		int y=LOWORD((p.y<<16)+p.x);
		SendMessage(WM_MOUSEMOVE,MK_LBUTTON|MK_SHIFT, (p.y<<16)+p.x);
		Invalidate(FALSE);
	}
	else LineNear=0;
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CShemeView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (StateNew && ((nFlags&0x0ff)==42) )
	{
		LineNear=0;
//		CPoint p=ShemeToScreen(coordLast);
//		SendMessage(WM_MOUSEMOVE,MK_LBUTTON, (p.y<<16+p.x));
		Invalidate(FALSE);
	}	
	else LineNear=0;
		
	CScrollView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CShemeView::OnAddspring() 
{
	// TODO: Add your command handler code here
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CSpring sprn(0,0);
	int ret=sprn.GoDlg(&pDoc->m_pSheme->listKnot);

	if (ret) 
	{
		CElem *elem=pDoc->AddSpring(sprn.knot1,sprn.knot2);
		int num = elem->GetNumber();
		if (elem) *elem=sprn;
		elem->SetNumber( num );
		//pDoc->SetModifiedFlag();
		SetScrollView();////////////////
		
		Invalidate(TRUE);
	}
}

void CShemeView::OnUpdateAddgraph(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( (SelKnot!=NULL)&&(!m_bClickingGroup) );
}

void CShemeView::OnUpdateSetmass(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bClickingGroup );
	pCmdUI->SetCheck( TypeElem==IDC_MASS );
}

void CShemeView::OnSetmass() 
{
	// TODO: Add your command handler code here
	TypeElem=IDC_MASS;
}

void CShemeView::OnAddmass() 
{
	// TODO: Add your command handler code here
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CMass mass(0);
	int ret=mass.GoDlg(&pDoc->m_pSheme->listKnot);

	if (ret) 
	{
		CElem *elem=pDoc->AddMass(mass.knot1);
		int num = elem->GetNumber();
		if (elem) *elem=mass;
		elem->SetNumber( num );
		//pDoc->SetModifiedFlag();
		SetScrollView();////////////////
		
		Invalidate(TRUE);
	}
}

void CShemeView::OnDelelem() 
{
	// TODO: Add your command handler code here
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	ASSERT(SelElem);

	//Просматриваем все элементы
	POSITION pos2,pos=pDoc->m_pSheme->listElem.GetHeadPosition();
	while (pos)
	{
		pos2=pos;
		//Получаем указатель на очередной элемент
		CElem *elem=pDoc->m_pSheme->listElem.GetNext(pos);
		//Если нашли позицию выбранного элемента, то ...
		if (elem==SelElem)
		{	
			int busy1=0,busy2=0;

			//Ищем элементы, присоединенные к выбранному
			POSITION pos3=pDoc->m_pSheme->listElem.GetHeadPosition();
			while(pos3)
			{
				//получаем указатель на очередной элемент для поиска
				CElem *findelem=pDoc->m_pSheme->listElem.GetNext(pos3);
				if (findelem!=elem)
				{
					if ( (findelem->knot1==elem->knot1)||
						 (findelem->knot2==elem->knot1) )
						busy1=1;
					if ( (findelem->knot1==elem->knot2)||
						 (findelem->knot2==elem->knot2) )
						busy2=1;
				}
			}

			//Поиск графиков с несуществующими узлами
			POSITION posgraph=pDoc->GetFirstViewPosition();
			while (posgraph)
			{
				CGraphicView *pview=(CGraphicView*)pDoc->GetNextView(posgraph);
				if ( ((!busy1)&&(pview->pKnot==elem->knot1)) ||
					 ((!busy2)&&(pview->pKnot==elem->knot2))  )
				{
					pDoc->RemoveView(pview);
					pview->GetOwner()->DestroyWindow();
				}
			}

			//Удаление пустых узлов
			POSITION ppp;
			if (!busy1)	
			{
				pDoc->m_pSheme->listKnot.FindPos(elem->knot1,&ppp);
				delete elem->knot1;
				pDoc->m_pSheme->listKnot.RemoveAt(ppp);
			}
			if ((!busy2)&&(elem->knot1!=elem->knot2))
			{
				pDoc->m_pSheme->listKnot.FindPos(elem->knot2,&ppp);
				delete elem->knot2;
				pDoc->m_pSheme->listKnot.RemoveAt(ppp);
			}

			//Удаление из списка
			delete elem;
			pDoc->m_pSheme->listElem.RemoveAt(pos2);
			OldSelElem=SelElem=0;
			pDoc->m_pSheme->SetConnectElements();
			pDoc->SetModifiedFlag();
			Invalidate(TRUE);
			return;
		}
	}
}

void CShemeView::OnUpdateDelelem(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( (SelElem!=0)&&(!m_bClickingGroup) );
}


void CShemeView::OnUpdateSetnull(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(TypeElem==IDC_NULL);
}

void CShemeView::OnSetnull() 
{
	// TODO: Add your command handler code here
	TypeElem=IDC_NULL;		
}

void CShemeView::OnUpdateProp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( (SelElem||SelKnot)&&(!m_bClickingGroup) );
}

void CShemeView::OnProp() 
{
	// TODO: Add your command handler code here
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (SelKnot) 
	{
		if (SelKnot->GoDlg()) 
		{
			DrawAll=1;
			pDoc->m_pSheme->SetConnectElements();
			pDoc->SetModifiedFlag();
			SetScrollView();
		}
		Invalidate(TRUE);
		return;
	}
	if (SelElem) 
	{
		if (SelElem->GoDlg(&(pDoc->m_pSheme->listKnot)))
		{
			DrawAll=1;
			pDoc->SetModifiedFlag();
		}
	}
	Invalidate(TRUE);
}

void CShemeView::OnRefresh() 
{
	// TODO: Add your command handler code here
	DrawAll=1;
	Invalidate(TRUE);
}

void CShemeView::OnFreqCalc() 
{
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your command handler code here

//	if( pDoc->m_pSheme->IsShemeContainsHardRod() )
//	{
//		AfxMessageBox("Заглушка.\nОперация запрещена для схем с жёсткими стержнями !!!");
//		return;
//	}

	//Обновление степеней свободы
	int Count=pDoc->m_pSheme->UpdateAllFree();
	//Формирование матрицы масс, демпфирования и жесткости
	int code=pDoc->m_pSheme->SetMatrMDC(Count,1);
	if (code) return;

	//Вывод диалога
	CFreqDlg dlg(&pDoc->m_pSheme->listKnot, &(pDoc->m_pSheme->ParamFreq) );
	
	if (SelKnot) dlg.pkn1=dlg.pkn2=SelKnot;
	
	if (dlg.DoModal()==IDOK)
	{
		//Вычисление нужной частотной характеристики
		double w0, w1, dw;
		BOOL FlagExit;
		CExpression e;
		e.IsNum(pDoc->m_pSheme->ParamFreq.strwBeg, &w0);
		e.IsNum(pDoc->m_pSheme->ParamFreq.strwEnd, &w1);
		e.IsNum(pDoc->m_pSheme->ParamFreq.strwStep, &dw);
		int Free1=pDoc->m_pSheme->ParamFreq.nFree1;
		int Free2=pDoc->m_pSheme->ParamFreq.nFree2;
		int s=pDoc->m_pSheme->matr_C.SizeY;

		CComplexMatr C(s,s);//, D(1,s);
		int SizeX=int((w1-w0)/dw+0.555);
		CMatr Dat(2,SizeX);

		//Создание прогрессбара
		CProgressDlg progrdlg(SizeX,_T("Вычисление частотных характеристик"));

		//Вычисление нужной характеристики
		for (int i=0;i<SizeX;i++)
		{
			double w=w0+i*dw;

			C.UnitMatr(pDoc->m_pSheme->matr_C - pDoc->m_pSheme->matr_M*(w*w),pDoc->m_pSheme->matr_D*w);
			int flag;
			C=C.GetInvert(flag);
			if (!flag) 
			{
				//MessageBox("Ошибка вычисления характеристики");
				if (i>0)
				{
					Dat[0][i]=Dat[0][i-1];
					Dat[1][i]=Dat[1][i-1];
				}
				continue;
			}

			double Re, Im;
			if (pDoc->m_pSheme->ParamFreq.typeForce==0) 
			{
				Re=C[Free2][Free1].Re();
				Im=C[Free2][Free1].Im();
				//for (int t=0;t<s;t++)
				//	D[0][i]=C[i][Free1];
			}
			else// (pDoc->ParamFreq.typeForce==1) 
			{
				Complex c;//=C[Free2][Free1]*Complex(pDoc->matr_C[Free2][Free1],pDoc->matr_D[Free2][Free1]*w);
				if (Free1==Free2) c=1;
				else
					for (int t=0;t<s;t++)
						c=c+C[Free2][t]*Complex(pDoc->m_pSheme->matr_C[t][Free1],pDoc->m_pSheme->matr_D[t][Free1]*w);
				Re=c.Re();
				Im=c.Im();
			}

			//double Re=D[0][Free2].Re();
			//double Im=D[0][Free2].Im();
			double A=sqrt(pow(Re,2)+pow(Im,2));
			double Fi;
			double pi=acos(-1);

			//CCoordD c(Re,Im);
			//Fi=-c.GetAng();
			Fi=atan2(Im,Re);
			if (Fi>0) Fi-=2*pi;

			switch (pDoc->m_pSheme->ParamFreq.TypeCharact)
			{
			case 0:
				Dat[1][i]=A*pow(w,pDoc->m_pSheme->ParamFreq.Derive*2);
				Dat[0][i]=w;
				break;
			case 1:
				Dat[1][i]=Im;
				Dat[0][i]=Re;
				break;
			case 2:
				Dat[1][i]=Fi;
				Dat[0][i]=w;
				break;
			};
			//Обработка сообщений
			MSG msg;
			FlagExit=false;
			while (PeekMessage(&msg, progrdlg.m_Button.m_hWnd, WM_KEYDOWN, WM_LBUTTONUP, PM_REMOVE))   // Until WM_QUIT message
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
			if (FlagExit){	return; break;	}
			//Конец обработки сообщений

			//Вывод прогрессбара
			progrdlg.m_Progress.SetPos(i);
			progrdlg.UpdateData(FALSE);
		}
		//Удаление прогрессбара

		//Заполнение внутреннего массива графика
		//Создание окна с графиком и присоединение его к документу
		CString str1, str2, str3;
		str1=pDoc->GetTitle();
//		str2.Format(" (Узел №%d) ",SelKnot->Num);
		switch (pDoc->m_pSheme->ParamFreq.TypeCharact)
		{
		case 0:
				str3+=_T("  АЧХ ");
				break;
		case 1:
				str3+=_T("  АФХ ");
				break;
		case 2:
				str3+=_T("  ФЧХ ");
				break;
		}
		CNSys2DApp* pApp=(CNSys2DApp*)AfxGetApp();

		POSITION pos = pApp->GetFirstDocTemplatePosition();
		pApp->GetNextDocTemplate(pos);
		CDocTemplate *pTemplate = pApp->GetNextDocTemplate(pos);

		//CMDIChildWnd* 
		CGraphFrame *pNewFrame	= (CGraphFrame*)(pTemplate->CreateNewFrame(pDoc, NULL));
		ASSERT(pNewFrame!=NULL);
		
		
		pTemplate->InitialUpdateFrame(pNewFrame, pDoc);

		CGraphicView *pGraphView = (CGraphicView*)pNewFrame->GetActiveView();
		ASSERT (pGraphView != NULL);

		pGraphView->pKnot=0;
		//Установка переменной по горизонтали
		pGraphView->str_title=str3+str2;
		//Начальная установка границ изображения
		pGraphView->SetMaxMin();

		pNewFrame->SetWindowText(str1+str2+str3);

		pGraphView->Dat.ReSize(2,SizeX);

		pGraphView->Dat=Dat;

		pDoc->UpdateAllViews(0);
	}
}

void CShemeView::OnUpdateFreqCalc(CCmdUI* pCmdUI) 
{
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your command update UI handler code here

	pCmdUI->Enable( (pDoc->m_pSheme->listKnot.GetCount()>0)&&(!m_bClickingGroup) );	
}

void CShemeView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect clrect;
	GetClientRect(&clrect);
	pDC->SetMapMode(MM_ISOTROPIC);

	pDC->SetWindowExt(clrect.Width(), clrect.Height());
	pDC->SetWindowOrg(GetDeviceScrollPosition());
	
	CSize sizePaper=CSize(pDC->GetDeviceCaps(HORZRES),
						  pDC->GetDeviceCaps(VERTRES));

	CRect rect(0,0,sizePaper.cx,sizePaper.cy);
	pDC->SetViewportExt(rect.Width(), rect.Height());

//	pDC->LPtoDP(&rect);
	pInfo->m_rectDraw=rect;
	OnDraw( pDC );
}

BOOL CShemeView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// TODO: call DoPreparePrinting to invoke the Print dialog box
	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(1);
	return DoPreparePrinting(pInfo);
}

void CShemeView::OnSpectrCalc() 
{
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your command handler code here
//	if( pDoc->m_pSheme->IsShemeContainsHardRod() )
//	{
//		AfxMessageBox("Заглушка.\nОперация запрещена для схем с жёсткими стержнями !!!");
//		return;
//	}
	//Обновление степеней свободы
	int Count=pDoc->m_pSheme->UpdateAllFree();
	//Формирование матрицы масс, демпфирования и жесткости
	int code=pDoc->m_pSheme->SetMatrMDC(Count,1);
	if (code) return;

	//Вывод диалога
	CSpectrDlg dlg(&pDoc->m_pSheme->ParamSpectrOut, &pDoc->m_pSheme->listKnot, SelKnot);
	if (dlg.DoModal()==IDOK)
	{
		//Вычисление нужной частотной характеристики
		double w0, w1, dw;
		BOOL FlagExit;
		CExpression e;
		e.IsNum(pDoc->m_pSheme->ParamSpectrOut.strwBeg, &w0);
		e.IsNum(pDoc->m_pSheme->ParamSpectrOut.strwEnd, &w1);
		e.IsNum(pDoc->m_pSheme->ParamSpectrOut.strwStep, &dw);
		int Free1=pDoc->m_pSheme->ParamSpectrOut.nFree1;
		int s = pDoc->m_pSheme->matr_C.SizeY;
		CComplexMatr C(s,s);
		int SizeX = int((w1-w0)/dw+0.555);
		CMatr Dat(2,SizeX);

		//Создание прогрессбара
		CProgressDlg progrdlg(100,_T("Вычисление спектральной плотности"));

		//Вычисление спектральной плотности
		for (int i=0;i<SizeX;i++)
		{
			double w=w0+i*dw;
			
			C.UnitMatr(pDoc->m_pSheme->matr_C - pDoc->m_pSheme->matr_M*(w*w),pDoc->m_pSheme->matr_D*w);
			int flag;
			C=C.GetInvert(flag);
			if (!flag) 
			{
				//MessageBox("Ошибка вычисления характеристики");
				if (i>0)
				{
					Dat[0][i]=w;
					Dat[1][i]=Dat[1][i-1];
				}

				continue;
			}

			double Rez=0;
			POSITION pos=pDoc->m_pSheme->listKnot.GetHeadPosition();
			while(pos)
			{
				CKnot *pkn = pDoc->m_pSheme->listKnot.GetNext(pos);
				int nFx,nFy;
				//Силовое возмущение
				nFx=pkn->nXRez;
				if ((nFx>=0)&&(pkn->PxEnable)&&(!pkn->UxEnable)&&(pkn->TypePx==2)) 
					Rez+=Sqr(C[Free1][nFx])*pkn->SpPx.GetSpectr(w);
				nFy=pkn->nYRez;
				if ((nFy>=0)&&(pkn->PyEnable)&&(!pkn->UyEnable)&&(pkn->TypePy==2)) 
					Rez+=Sqr(C[Free1][nFy])*pkn->SpPy.GetSpectr(w);

				//Кинематическое возмущение
				Complex c;
				if ((nFx>=0)&&(pkn->UxEnable)&&(pkn->TypeUx==2))
				{
					Complex c;
					if (nFx==Free1) c=1;
					else
						for (int t=0;t<s;t++)
							c+=(C[Free1][t]*Complex(pDoc->m_pSheme->matr_C[t][nFx],pDoc->m_pSheme->matr_D[t][nFx]*w));
					Rez+=Sqr(c)*pkn->SpUx.GetSpectr(w);
				}
				if ((nFy>=0)&&(pkn->UyEnable)&&(pkn->TypeUy==2))
				{
					Complex c;
					if (nFy==Free1) c=1;
					else
						for (int t=0;t<s;t++)
							c+=(C[Free1][t]*Complex(pDoc->m_pSheme->matr_C[t][nFy],pDoc->m_pSheme->matr_D[t][nFy]*w));
					Rez+=Sqr(c)*pkn->SpUy.GetSpectr(w);
				}
			}

			//Силовое возмущение (взаимная плотность)
			pos=pDoc->m_pSheme->listspectrP.GetHeadPosition();
			while(pos)
			{
				CComplexSpectr *pCS=pDoc->m_pSheme->listspectrP.GetNext(pos);
				int nF1, nF2;
				switch (pCS->Free1)
				{
				case 0: nF1=pCS->pKn1->nXRez;
				case 1: nF1=pCS->pKn1->nYRez;
				case 2: nF1=pCS->pKn1->nARez[0];
				}
				switch (pCS->Free2)
				{
				case 0: nF2=pCS->pKn2->nXRez;
				case 1: nF2=pCS->pKn2->nYRez;
				case 2: nF2=pCS->pKn2->nARez[0];
				}
				if ((nF1>=0)&&(nF2>=0)) 
					Rez+=2*pCS->Sp.GetSpectr(w)*(
					C[Free1][nF1].Re()*C[Free1][nF2].Re()+
					C[Free1][nF1].Im()*C[Free1][nF2].Im() );
			}
			//Кинематическое возмущение (взаимная плотность)
			pos = pDoc->m_pSheme->listspectrU.GetHeadPosition();
			while(pos)
			{
				CComplexSpectr *pCS = pDoc->m_pSheme->listspectrU.GetNext(pos);
				int nF1, nF2;
				switch (pCS->Free1)
				{
				case 0: nF1=pCS->pKn1->nXRez;
				case 1: nF1=pCS->pKn1->nYRez;
				case 2: nF1=pCS->pKn1->nARez[0];
				}
				switch (pCS->Free2)
				{
				case 0: nF2=pCS->pKn2->nXRez;
				case 1: nF2=pCS->pKn2->nYRez;
				case 2: nF2=pCS->pKn2->nARez[0];
				}
				if ((nF1>=0)&&(nF2>=0)) 
				{
					Complex c1, c2;
					for (int t=0;t<s;t++)
					{
						c1+=(C[Free1][t]*Complex(pDoc->m_pSheme->matr_C[t][nF1],pDoc->m_pSheme->matr_D[t][nF1]*w));
						c2+=(C[Free1][t]*Complex(pDoc->m_pSheme->matr_C[t][nF2],pDoc->m_pSheme->matr_D[t][nF2]*w));
					}
					Rez+=pCS->Sp.GetSpectr(w)*(c1.Re()*c2.Re()+c1.Im()*c2.Im());
				}
			}

			Dat[0][i]=w;
			Dat[1][i]=Rez;

			//Обработка сообщений
			MSG msg;
			FlagExit=false;
			while (PeekMessage(&msg, progrdlg.m_Button.m_hWnd, WM_KEYDOWN, WM_LBUTTONUP, PM_REMOVE))   // Until WM_QUIT message
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
			if (FlagExit){	return; break;	}
			//Конец обработки сообщений

			//Вывод прогрессбара
			progrdlg.SetPos(int(100.0*i/SizeX));
		}
		//Удаление прогрессбара

		//Заполнение внутреннего массива графика
		//Создание окна с графиком и присоединение его к документу
		CString str1, str2, str3;
		str1=pDoc->GetTitle();
		str2.Format(" (Узел №%d) ",pDoc->m_pSheme->ParamSpectrOut.pKnot1->Num);
		switch (pDoc->m_pSheme->ParamSpectrOut.typeFree1)
		{
		case 0:
				str3+=_T("(Х)");
				break;
		case 1:
				str3+=_T("(Y)");
				break;
		case 2:
				str3+=_T("(A)");
				break;
		}
		CNSys2DApp* pApp=(CNSys2DApp*)AfxGetApp();

		POSITION pos = pApp->GetFirstDocTemplatePosition();
		pApp->GetNextDocTemplate(pos);
		CDocTemplate *pTemplate = pApp->GetNextDocTemplate(pos);

		//CMDIChildWnd* 
		CGraphFrame *pNewFrame	= (CGraphFrame*)(pTemplate->CreateNewFrame(pDoc, NULL));
		ASSERT(pNewFrame!=NULL);
		
		
		pTemplate->InitialUpdateFrame(pNewFrame, pDoc);

		CGraphicView *pGraphView = (CGraphicView*)pNewFrame->GetActiveView();
		ASSERT (pGraphView != NULL);

		pGraphView->pKnot=0;
		//Установка переменной по горизонтали
		pGraphView->str_title=str1+str2+str3;
		//Начальная установка границ изображения
		pGraphView->SetMaxMin();

		pNewFrame->SetWindowText(str1+str2+str3);

		pGraphView->Dat.ReSize(2,SizeX);

		pGraphView->Dat=Dat;

		pDoc->UpdateAllViews(0);
	}
}

void CShemeView::OnDestroy() 
{
	CScrollView::OnDestroy();
	
	// TODO: Add your message handler code here
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//pDoc->OnCloseDocument();
}


void CShemeView::OnSetHardRod() 
{
	// TODO: Add your command handler code here
	TypeElem = IDC_HARDROD;
}

void CShemeView::OnUpdateSetHardRod(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bClickingGroup );
	pCmdUI->SetCheck( TypeElem==IDC_HARDROD );
}

void CShemeView::OnAddHardRod() 
{
	// TODO: Add your command handler code here
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: Add your command handler code here
	CHardRod Hrod(0,0);
	int ret = Hrod.GoDlg( &pDoc->m_pSheme->listKnot );

	if( ret ) 
	{
		CElem *elem = pDoc->AddHardRod( Hrod.knot1, Hrod.knot2 );
		int num = elem->GetNumber();
		if( elem )	*elem = Hrod;
		elem->SetNumber( num );
		pDoc->SetModifiedFlag();
		SetScrollView();
		Invalidate(TRUE);
	}	
}

void CShemeView::OnUpdateMeshElem(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( (!m_bClickingGroup)&&(SelElem)&&((SelElem->TypeElem==IDC_ROD)||(SelElem->TypeElem==IDC_HARDROD)) );
}

void CShemeView::OnMeshElem() 
{
	// TODO: Add your command handler code here
	ASSERT(SelElem);
	int elemType = SelElem->TypeElem;
	ASSERT( (elemType==IDC_ROD)||(elemType==IDC_HARDROD) );
	
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//получаем число элементов, на которое надо разбить данный
	CMeshElemDlg dlg( elemType );

	dlg.m_strLeftKnot = SelElem->knot1->GetName();
	dlg.m_strRightKnot = SelElem->knot2->GetName();
	dlg.m_dLength = SelElem->GetLength();

	int way, ret;
	while( (ret = dlg.DoModal()) == IDOK )
	{
		way = dlg.m_iWay;
		if( way == 1 )
		{
			//если выбрана врезка одного узла
			//и данные некорректны, тоо предлагаем исправиться
			if( (dlg.m_dLeftLength>dlg.m_dLength)||
				(dlg.m_dRightLength>dlg.m_dLength) )
			{
				if( AfxMessageBox("Задана некорректная длина одной из частей.\nХотите исправить?",
					MB_YESNO|MB_TASKMODAL|MB_ICONEXCLAMATION ) == IDNO )
					return;
				else	continue;
			}
			if( (dlg.m_iLeftProc==100)||(dlg.m_iLeftProc==0)||
				(dlg.m_iRightProc==100)||(dlg.m_iRightProc==0) )
			{
				if( AfxMessageBox("При таком расположении нового узла разбивка не имеет смысла.\nХотите исправить?",
					MB_YESNO|MB_TASKMODAL|MB_ICONEXCLAMATION ) == IDNO )
					return;
				else	continue;
			}
		}
		break;
	}
	if( ret == IDCANCEL )	return;

	CCoordD left = SelElem->knot1->GetCoord(), right = SelElem->knot2->GetCoord();
	ARRAY vec;//массив номеров новых элементов
	if( way == 0 )
	{
		ASSERT( elemType == IDC_ROD );
		//разбить на несколько элементов
		int iElemsCount = dlg.m_iElemsCount;
	
		double XStep = (right.x-left.x)/iElemsCount, YStep = (right.y-left.y)/iElemsCount;

		CKnot *prev = SelElem->knot1;
		for( int i = 0; i < (iElemsCount-1); i++ )
		{
			double posX2, posY2;//коор-ты нового узла нового элемента
			posX2 = left.x + XStep*(i+1);
			posY2 = left.y + YStep*(i+1);
			CString strPosX2, strPosY2;
			strPosX2.Format("%.5lf", posX2 );
			strPosY2.Format("%.5lf", posY2 );

			CKnot knotNew( strPosX2, strPosY2 ), *kn;
			kn = pDoc->m_pSheme->listKnot.AddKnot( knotNew );

			CRod *rodNew = (CRod*)pDoc->AddRod( prev, kn );
			if( !rodNew->SetCommonProperties( SelElem ) )
			{
				AfxMessageBox("Фатальная ошибка!!!\nОбратитесь к разработчику.");
				return;
			}
			vec.push_back( rodNew->GetNumber() );
			prev = kn;
		}
		CRod *rodNew = (CRod*)pDoc->AddRod( prev, SelElem->knot2 );
		if( !rodNew->SetCommonProperties( SelElem ) )
		{
			AfxMessageBox("Фатальная ошибка!!!\nОбратитесь к разработчику.");
			return;
		}
		vec.push_back( rodNew->GetNumber() );
	}
	else//way==1
	{
		//rel - размер левой части элемента в долях
		double rel = dlg.m_dLeftLength/dlg.m_dLength;
		//коор-ты нового узла нового элемента
		double posX = left.x + (right.x - left.x)*rel;
		double posY = left.y + (right.y - left.y)*rel;
		CString strPosX, strPosY;
		strPosX.Format("%.5lf", posX );
		strPosY.Format("%.5lf", posY );

		CKnot knotNew( strPosX, strPosY ), *kn;
		kn = pDoc->m_pSheme->listKnot.AddKnot( knotNew );

		CElem *elem;
		if( elemType == IDC_ROD )
		{
			elem = pDoc->AddRod( SelElem->knot1, kn );
		}
		else
		{
			elem = pDoc->AddHardRod( SelElem->knot1, kn );
		}
		if( !elem->SetCommonProperties( SelElem ) )
		{
			AfxMessageBox("Фатальная ошибка!!!\nОбратитесь к разработчику.");
			return;
		}
		vec.push_back( elem->GetNumber() );
		if( elemType == IDC_ROD )
		{
			elem = pDoc->AddRod( kn, SelElem->knot2 );
		}
		else
		{
			elem = pDoc->AddHardRod( kn, SelElem->knot2 );
		}
		if( !elem->SetCommonProperties( SelElem ) )
		{
			AfxMessageBox("Фатальная ошибка!!!\nОбратитесь к разработчику.");
			return;
		}
		vec.push_back( elem->GetNumber() );
	}//врезка узла

	//теперь удаляем старый элемент
	//Просматриваем все элементы
	POSITION pos2, pos = pDoc->m_pSheme->listElem.GetHeadPosition();
	while( pos )
	{
		pos2 = pos;
		//Получаем указатель на очередной элемент
		CElem *elem = pDoc->m_pSheme->listElem.GetNext(pos);
		//Если нашли позицию выбранного элемента, то ...
		if( elem == SelElem )
		{	
			//Удаление из списка
			delete elem;
			pDoc->m_pSheme->listElem.RemoveAt(pos2);
			OldSelElem = SelElem = 0;
			break;
		}
	}	

	pDoc->m_pSheme->SetConnectElements();//зачем - не знаю
	pDoc->SetModifiedFlag();
	Invalidate(TRUE);

	//предлагаем создать новую группу
	if( AfxMessageBox( "Создать группу для новых элементов?", 
		MB_YESNO|MB_TASKMODAL|MB_ICONQUESTION )== IDYES )
	{
		CShemeGroup gr( CShemeGroup::GetPackedGroup( vec ), 0 );
		pDoc->m_pSheme->m_vecElemGroups.push_back( gr );
		CString str;
		gr.GetName( str );
		AfxMessageBox( _T("Создана новая группа с именем \"")+str+_T("\""),
			MB_OK|MB_TASKMODAL|MB_ICONINFORMATION );
	}
}

void CShemeView::OnButtonAutoSize() 
{
	// TODO: Add your command handler code here
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->ParamView.Scale = pDoc->ParamView.m_DefaultScale;
	SetScrollView();
	pDoc->UpdateAllViews(this);
	Invalidate(TRUE);
}

void CShemeView::OnUpdateConvertTo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( (!m_bClickingGroup)&&(SelElem)&&( (SelElem->TypeElem==IDC_ROD)||(SelElem->TypeElem==IDC_HARDROD) ) );
}

void CShemeView::OnConvertTo() 
{
	// TODO: Add your command handler code here
	ASSERT(SelElem);
	int elemType = SelElem->TypeElem;
	ASSERT( (elemType==IDC_ROD)||(elemType==IDC_HARDROD) );
	
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CConvertToDlg dlg( elemType );
	if( dlg.DoModal() == IDCANCEL )
	{
		return;
	}
	
	CKnot *kn1 = SelElem->knot1, *kn2 = SelElem->knot2;

	CString E, F, J;
	double m;
	int num = SelElem->GetNumber();
	if( elemType == IDC_ROD )
	{
		E = ((CRod*)SelElem)->GetStrE();
		F = ((CRod*)SelElem)->GetStrF();
		J = ((CRod*)SelElem)->GetStrJx();
		//делаем из погонной массы массу стержня
		m = ((CRod*)SelElem)->GetM()*((CRod*)SelElem)->GetLength();
	}
	else
	{
		E = ((CHardRod*)SelElem)->GetStrE();
		F = ((CHardRod*)SelElem)->GetStrF();
		J = ((CHardRod*)SelElem)->GetStrJ();
		//делаем из массы стержня погонную массу
		m = ((CHardRod*)SelElem)->GetM()/((CHardRod*)SelElem)->GetLength();
	}
	CString M;
	M.Format("%.5lf", m );
	//удаляем старый элемент
	//Просматриваем все элементы
	POSITION pos2, pos = pDoc->m_pSheme->listElem.GetHeadPosition();
	while( pos )
	{
		pos2 = pos;
		//Получаем указатель на очередной элемент
		CElem *elem = pDoc->m_pSheme->listElem.GetNext(pos);
		//Если нашли позицию выбранного элемента, то ...
		if( elem == SelElem )
		{	
			//Удаление из списка
			delete elem;
			pDoc->m_pSheme->listElem.RemoveAt(pos2);
			OldSelElem = SelElem = 0;
			break;
		}
	}
	//создаём новый 
	if( elemType == IDC_ROD )
	{
		CHardRod *rodNew = (CHardRod*)pDoc->AddHardRod( kn1, kn2 );
		rodNew->SetE( E );
		rodNew->SetF( F );
		rodNew->SetJ( J );
		rodNew->SetM( M );
		rodNew->SetNumber( num );
	}
	else
	{
		CRod *rodNew = (CRod*)pDoc->AddRod( kn1, kn2 );
		rodNew->SetE( E );
		rodNew->SetF( F );
		rodNew->SetJx( J );
		rodNew->SetM( M );
		rodNew->SetNumber( num );
	}

	pDoc->m_pSheme->SetConnectElements();//зачем - не знаю
	pDoc->SetModifiedFlag();
	Invalidate(TRUE);
}

void CShemeView::OnUpdateAdddemf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bClickingGroup );
}

void CShemeView::OnUpdateAddhardrod(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bClickingGroup );
}

void CShemeView::OnUpdateAddmass(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bClickingGroup );
}

void CShemeView::OnUpdateAddrod(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bClickingGroup );
}

void CShemeView::OnUpdateAddspring(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bClickingGroup );
}

void CShemeView::OnUpdateSpectrCalc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bClickingGroup );
}

void CShemeView::OnUpdateFileClose(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bClickingGroup );
}

void CShemeView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bClickingGroup );
}

void CShemeView::OnUpdateFilePrintSetup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !m_bClickingGroup );
}

int CShemeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CShemeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if( pDoc->m_pSheme == NULL )
		return -1;
	pDoc->m_pSheme->m_pDoc = pDoc;

	return 0;
}
