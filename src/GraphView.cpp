// GraphView.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "GraphView.h"
#include "ShemeDoc.h"

#include "GraphFrm.h"

#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphView

IMPLEMENT_DYNCREATE(CGraphView, CScrollView)

CGraphView::CGraphView()
{
	ScaleX=1;
	ScaleY=0.01;
	AutoSizing=TRUE;
	pKnot=0;
	TypeX=6;
	TypeY=6;
	Tt=0;
	
	EnableAutomation();
}

CGraphView::~CGraphView()
{
	if (Tt) delete [] Tt;
}

void CGraphView::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CScrollView::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CGraphView, CScrollView)
	//{{AFX_MSG_MAP(CGraphView)
	ON_COMMAND(ID_HORADD, OnHoradd)
	ON_COMMAND(ID_HORSUB, OnHorsub)
	ON_COMMAND(ID_VERTADD, OnVertadd)
	ON_COMMAND(ID_VERTSUB, OnVertsub)
	ON_UPDATE_COMMAND_UI(ID_AUTOSIZE, OnUpdateAutosize)
	ON_COMMAND(ID_AUTOSIZE, OnAutosize)
	ON_UPDATE_COMMAND_UI(ID_SAVEREZ, OnUpdateSaverez)
	ON_COMMAND(ID_SAVEREZ, OnSaverez)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CGraphView, CScrollView)
	//{{AFX_DISPATCH_MAP(CGraphView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IGraphView to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {09A14A9D-BBAC-11D2-AF23-BB2B1C460D22}
static const IID IID_IGraphView =
{ 0x9a14a9d, 0xbbac, 0x11d2, { 0xaf, 0x23, 0xbb, 0x2b, 0x1c, 0x46, 0xd, 0x22 } };

BEGIN_INTERFACE_MAP(CGraphView, CScrollView)
	INTERFACE_PART(CGraphView, IID_IGraphView, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphView drawing

void CGraphView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = 275;
	sizeTotal.cy = 230;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CGraphView::OnDraw(CDC* pDC)
{
	CShemeDoc* pDoc = (CShemeDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code here
	//ЦВЕТА
	//Сетка
	CPen pen(PS_DOT|PS_GEOMETRIC,1,RGB(0,150,0));
	//График
//	CPen pen2(PS_SOLID|PS_GEOMETRIC,2,RGB(0,0,0));//220
	CPen pen2(PS_SOLID|PS_GEOMETRIC,1,RGB(240,0,0));//220
	//Оси
	CPen pen3(PS_SOLID|PS_GEOMETRIC,2,RGB(0,0,0));
	//Рамка
	CPen pen4(PS_SOLID|PS_GEOMETRIC,1,RGB(0,0,0));

	CPen *pOld=(CPen*)pDC->SelectObject(&pen);

//	CBrush brush(GetSysColor(COLOR_WINDOW));
//	CBrush *pOldbrush=(CBrush*)pDC->SelectObject(&brush);

	int SizeX=pDoc->matr_RezY1.SizeX;
	if (Tt) delete Tt;
	Tt=new double[SizeX];
	for (int r=0;r<SizeX;r++) 
		Tt[r]=r*pDoc->ParamIntegr.Step;
	
	double *pRowX, *pRowY;
	//выбор нужных массивов из результатов расчета
	switch (TypeX)
	{
	case 0: pRowX=(pKnot->nXRez>=0?pDoc->matr_RezY1.GetRow(pKnot->nXRez):0);	break;
	case 1: pRowX=(pKnot->nYRez>=0?pDoc->matr_RezY1.GetRow(pKnot->nYRez):0);	break;
	case 2: pRowX=(pKnot->nARez[0]>=0?pDoc->matr_RezY1.GetRow(pKnot->nARez[0]):0); break;
	case 3: pRowX=(pKnot->nXRez>=0?pDoc->matr_RezY2.GetRow(pKnot->nXRez):0);	break;
	case 4: pRowX=(pKnot->nYRez>=0?pDoc->matr_RezY2.GetRow(pKnot->nYRez):0);	break;
	case 5: pRowX=(pKnot->nARez[0]>=0?pDoc->matr_RezY2.GetRow(pKnot->nARez[0]):0); break;
	case 6: pRowX=Tt; break;
	}
	
	switch (TypeY)
	{
	case 0: pRowY=(pKnot->nXRez>=0?pDoc->matr_RezY1.GetRow(pKnot->nXRez):0);	break;
	case 1: pRowY=(pKnot->nYRez>=0?pDoc->matr_RezY1.GetRow(pKnot->nYRez):0);	break;
	case 2: pRowY=(pKnot->nARez[0]>=0?pDoc->matr_RezY1.GetRow(pKnot->nARez[0]):0); break;
	case 3: pRowY=(pKnot->nXRez>=0?pDoc->matr_RezY2.GetRow(pKnot->nXRez):0);	break;
	case 4: pRowY=(pKnot->nYRez>=0?pDoc->matr_RezY2.GetRow(pKnot->nYRez):0);	break;
	case 5: pRowY=(pKnot->nARez[0]>=0?pDoc->matr_RezY2.GetRow(pKnot->nARez[0]):0); break;
	case 6: pRowY=Tt; break;
	}

	if ( (!pRowX) || (!pRowY) )
	{
		pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
		pDC->SetTextAlign(TA_LEFT|TA_BASELINE);	
		pDC->TextOut(20,50,"Нет результатов расчета или эта степень свободы неподвижна.");
		return;
	}

	//поиск максимумов и минимумов по осям
	double minX, maxX, minY, maxY;

	maxX=minX=pRowX[0];
	maxY=minY=pRowY[0];
	for (int k=1;k<SizeX;k++)
	{
		double Val=pRowX[k];
		if (Val>maxX) maxX=Val;
		if (Val<minX) minX=Val;
		Val=pRowY[k];
		if (Val>maxY) maxY=Val;
		if (Val<minY) minY=Val;
	}
	
	if ( (maxX==minX) || (maxY==minY) )
	{
		pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
		pDC->SetTextAlign(TA_LEFT|TA_BASELINE);	
		pDC->TextOut(20,50,"(maxX==minX) || (maxY==minY)");
		return;
	}

	
	//поля на графике
	const int LeftGraph=25;		//левый отступ
	const int TopGraph=15;		//верхний отступ
	const int RightGraph=15;	//правый отступ
	const int DownGraph=15;		//нижний отступ

	maxX+=(maxX-minX)*0.05;
	minX-=(maxX-minX)*0.05;
	maxY+=(maxY-minY)*0.05;
	minY-=(maxY-minY)*0.05;

	//Задание размера скролинга
	CSize sizeTotal;
	if (AutoSizing)
	{
		//sizeTotal=GetTotalSize();
		//sizeTotal=
		CRect rect;
		GetClientRect(&rect);
		sizeTotal=rect.Size();
		SetScrollSizes(MM_TEXT, sizeTotal);
		ScaleX=(maxX-minX)/(sizeTotal.cx-LeftGraph-RightGraph);
		ScaleY=(maxY-minY)/(sizeTotal.cy-TopGraph-DownGraph);
	}
	else
	{
		sizeTotal.cx = int((maxX-minX)/ScaleX)+LeftGraph+RightGraph;
		sizeTotal.cy = int((maxY-minY)/ScaleY)+TopGraph+DownGraph;
		SetScrollSizes(MM_TEXT, sizeTotal);
	}

	
	//Координаты для текста на графике
	int text_x=LeftGraph, text_y=sizeTotal.cy;

	//Оси
	int y=sizeTotal.cy-DownGraph+int(minY/ScaleY);
	if ( (y>TopGraph) && (y<(sizeTotal.cy-DownGraph)) )
		text_y=y;
	int x=LeftGraph-int(minX/ScaleX);
	if ((x>LeftGraph)&&(x<(sizeTotal.cx-RightGraph)) )
		text_x=x;

	//сетка

	//Установка шрифтов
	pDC->SelectObject(&pen);
	CFont font1;
	font1.CreatePointFont(75,_T("Arial"), 0);//MS Sans Serif
	pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
	pDC->SetTextAlign(TA_CENTER|TA_BOTTOM);	
	CFont *pOldFont=pDC->SelectObject(&font1);

	
	//Ориентировочный шаг сетки
	double ScrStepX=50;//шаг сетки
	double ScrStepY=50;//шаг сетки

	const int StandartStep[]={0, 10, 20, 25, 40, 50, 75, 130};

	//ось X	
	//Примерный шаг
	double stpX_=(maxX-minX)/(sizeTotal.cx-LeftGraph-RightGraph)*ScrStepX;
	//временно убираемая степень
	double powX=pow(10,ceil(log10(stpX_))-2);
	int stpX=int(stpX_/powX);

	for (int i=0;i<sizeof(StandartStep)/sizeof(int);i++)
		if ( (stpX>StandartStep[i])&&(stpX<StandartStep[i+1]) )
		{
			if ((stpX-StandartStep[i])>(StandartStep[i+1]-stpX))
				 stpX=StandartStep[i+1];
			else stpX=StandartStep[i];
			break;
		}
	double StepX=stpX*powX;

	int addexpX=( ((stpX==25)||(stpX==75)) ?1:0);

	//положительная часть
	double x0_hor=(minX<=0?0:ceil(minX/StepX)*StepX);
	while (x0_hor<maxX)
	{
		int X=int((x0_hor-minX)/ScaleX)+LeftGraph;
		pDC->MoveTo(X,TopGraph);
		pDC->LineTo(X,sizeTotal.cy-DownGraph);

		CString str;
		int exp=int(-log10(powX));
		str.Format("%.*lf",(exp<0?0:exp+addexpX), x0_hor);
		pDC->TextOut(X,text_y-1,str);

		x0_hor+=StepX;
	}
	

	//отрицательная часть
	x0_hor=(maxX>=0?0:floor(maxX/StepX)*StepX);
	while (x0_hor>minX)
	{
		int X=int((x0_hor-minX)/ScaleX)+LeftGraph;
		pDC->MoveTo(X,TopGraph);
		pDC->LineTo(X,sizeTotal.cy-DownGraph);
		
		CString str;
		int exp=int(-log10(powX));
		str.Format("%.*lf",(exp<0?0:exp+addexpX), x0_hor);
		pDC->TextOut(X,text_y-1,str);

		x0_hor-=StepX;
	}
	

	//ось Y
	//Примерный шаг
	double stpY_=(maxY-minY)/(sizeTotal.cy-DownGraph-TopGraph)*ScrStepY;
	//временно убираемая степень
	double powY=pow(10,ceil(log10(stpY_))-2);
	int stpY=int(stpY_/powY);

	for (i=0;i<sizeof(StandartStep)/sizeof(int);i++)
		if ( (stpY>StandartStep[i])&&(stpY<StandartStep[i+1]) )
		{
			if ((stpY-StandartStep[i])>(StandartStep[i+1]-stpY))
				 stpY=StandartStep[i+1];
			else stpY=StandartStep[i];
			break;
		}
	double StepY=stpY*powY;

	int addexpY=( ((stpY==25)||(stpY==75))?1:0);
	pDC->SetTextAlign(TA_RIGHT|TA_BASELINE);	
	//положительная часть
	double y0_hor=(minY<=0?0:ceil(minY/StepY)*StepY);
	while (y0_hor<maxY)
	{
		int Y=sizeTotal.cy-int((y0_hor-minY)/ScaleY)-DownGraph;
		pDC->MoveTo(LeftGraph,Y);
		pDC->LineTo(sizeTotal.cx-RightGraph,Y);

		if (y0_hor!=0.0)
		{
			CString str;
			int exp=int(-log10(powY));
			str.Format("%.*lf",(exp<0?0:exp+addexpY ),y0_hor);
			pDC->TextOut(text_x-1,Y,str);
		}
		y0_hor+=StepY;
	}
	

	//отрицательная часть
	y0_hor=(maxY>=0?0:floor(maxY/StepY)*StepY);
	while (y0_hor>minY)
	{
		int Y=sizeTotal.cy-int((y0_hor-minY)/ScaleY)-DownGraph;
		pDC->MoveTo(LeftGraph,Y);
		pDC->LineTo(sizeTotal.cx-RightGraph,Y);
		
		if (y0_hor!=0.0)
		{
			CString str;
			int exp=int(-log10(powY));
			str.Format("%.*lf",(exp<0?0:exp+addexpY ),y0_hor);
			pDC->TextOut(text_x-1,Y,str);
		}

		y0_hor-=StepY;
	}
	
	
	//Оси
	pDC->SelectObject(&pen3);
	if ( (y>TopGraph) && (y<(sizeTotal.cy-DownGraph)) )
	{
		pDC->MoveTo(LeftGraph,y);
		pDC->LineTo(sizeTotal.cx-RightGraph,y);
	}	
	if ((x>LeftGraph)&&(x<(sizeTotal.cx-RightGraph)) )
	{
		pDC->MoveTo(x,TopGraph);
		pDC->LineTo(x,sizeTotal.cy-DownGraph);
	}
	
	
	//floor(minX/StepX)*StepX;

	


	
/*	//экспоненциальная часть
	int powV=(int)maxD(log10(fabs(maxY)),log10(fabs(minY)) );
	int powH=(int)maxD(log10(fabs(maxX)),log10(fabs(minX)) );

	//(StepX*ScaleX)


	//количество строк над нулём
	int nExpH=0;//Число десятичных знаков после запятой

	do
	{
		StepH=50;
		StepH=double(int(StepH*ScaleX*pow(10,nExpH+powH)))/(pow(10,nExpH+powH)*ScaleX);
//		if (StepH==0) 
//		{
//			CString str;
//			str.Format("StepH=%.16lf",StepH);
//			pDC->TextOut(50,50,str);
//			return;
//		}
		nExpH++;	
	}
	while ( (StepH*ScaleX*pow(10,nExpH+powH-2))<1);
	nExpH--;

	//положительная часть
	int nTab=int(int(minX/ScaleX)/StepH);//Количество шагов отступов
	if (nTab<1) nTab=1;
	double gridH=StepH*nTab;

	int X=int(-minX/ScaleX)+LeftGraph+int(gridH);
	while (X<(sizeTotal.cx-RightGraph))
	{
		pDC->MoveTo(X,TopGraph);
		pDC->LineTo(X,sizeTotal.cy-DownGraph);
		CString str;
		str.Format("%.*lf",nExpH,gridH*ScaleX/pow(10,powH));
		pDC->TextOut(X,text_y-1,str);

		gridH+=StepH;
		X=int(-minX/ScaleX)+LeftGraph+int(gridH);
	}

	//отрицательная часть
	nTab=int(int(maxX/ScaleX)/StepH);//Количество шагов отступов
	if (nTab>-1) nTab=-1;
	gridH=StepH*nTab;

	X=int(-minX/ScaleX)+LeftGraph+int(gridH);
	while (X>LeftGraph)
	{
		pDC->MoveTo(X,TopGraph);
		pDC->LineTo(X,sizeTotal.cy-DownGraph);
		CString str;
		str.Format("%.*lf",nExpH,gridH*ScaleX/pow(10,powH));
		pDC->TextOut(X,text_y-1,str);

		gridH-=StepH;
		X=int(-minX/ScaleX)+LeftGraph+int(gridH);
	}

	int nExpV=0;//Число десятичных знаков после запятой	
	do
	{
		StepV=50;
		StepV=int(StepV*ScaleY*pow(10,nExpV+powV))/(pow(10,nExpV+powV)*ScaleY);
//		if (StepV==0)
//		{
//			CString str;
//			str.Format("StepV=%lf",StepV);
//			pDC->TextOut(50,50,str);
//			return;
//		}
		nExpV++;
	}
	while ((StepV*ScaleY*pow(10,nExpV+powV-1))<1);
	nExpV--;

	pDC->SetTextAlign(TA_RIGHT|TA_BASELINE);	
	//положительная часть
	nTab=int(int(minY/ScaleY)/StepV);//Количество шагов отступов
	if (nTab<1) nTab=1;
	double gridV=StepV*nTab;

	int Y=sizeTotal.cy-DownGraph+int(minY/ScaleY)-int(gridV);
	while (Y>TopGraph)
	{
		pDC->MoveTo(LeftGraph,Y);
		pDC->LineTo(sizeTotal.cx-RightGraph,Y);
		CString str;
		str.Format("%.*lf",nExpV,gridV*ScaleY/pow(10,powV));
		pDC->TextOut(text_x-1,Y-1,str);

		gridV+=StepV;
		Y=sizeTotal.cy-DownGraph+int(minY/ScaleY)-int(gridV);
	}

	//отрицательная часть
	nTab=int(int(maxY/ScaleY)/StepV);//Количество шагов отступов
	if (nTab>-1) nTab=-1;
	gridV=StepV*nTab;

	Y=sizeTotal.cy-DownGraph+int(minY/ScaleY)-int(gridV);
	while (Y<(sizeTotal.cy-DownGraph))
	{
		pDC->MoveTo(LeftGraph,Y);
		pDC->LineTo(sizeTotal.cx-RightGraph,Y);
		CString str;
		str.Format("%.*lf",nExpV,gridV*ScaleY/pow(10,powV));
		pDC->TextOut(text_x-1,Y-1,str);

		gridV-=StepV;
		Y=sizeTotal.cy-DownGraph+int(minY/ScaleY)-int(gridV);
	}
	//Подписываем степени, если есть
	CFont font2;
	font2.CreatePointFont(65,_T("Arial"), 0);//MS Sans Serif
	if (powH)
	{
		pDC->SetTextAlign(TA_RIGHT|TA_BOTTOM);	
		pDC->SelectObject(font1);
		pDC->TextOut(sizeTotal.cx-25,text_y-15,_T("*10"));
		pDC->SelectObject(font2);
		CString str;
		str.Format("%d",powH);
		pDC->TextOut(sizeTotal.cx-20,text_y-22,str);
	}
	if (powV)
	{
		pDC->SetTextAlign(TA_RIGHT|TA_BOTTOM);	
		pDC->SelectObject(font1);
		pDC->TextOut(text_x-5,TopGraph-1,_T("*10"));
		pDC->SelectObject(font2);
		CString str;
		str.Format("%d",powV);
		pDC->TextOut(text_x,TopGraph-7,str);
	}
*/
/*
	//экспоненциальная часть
	int powV=(int)maxD(log10(fabs(maxV)),log10(fabs(minV)) );
	//Новый шаг сетки
	stepV=int(stepV*ScaleY*pow(10,powV+3))/1000.0/ScaleY;
	//число пикселов сверху по вертикали
	int nV0=int(  (sizeTotal.cy-2*TopGraph+(minV/ScaleY))/stepV+0.99 );
	int nV=	int((double)(sizeTotal.cy-2*TopGraph)/stepV);

//	int horz=int((double)sizeTotal.cx/step);
//	int vert=int((double)sizeTotal.cy/step);
//	horz-=(horz>2?1:0);

//	int MultX=(int)log10(sizex*pDoc->m_Step);
//	int ypos=GetScrollPosition().y;
//	pDC->SetTextAlign(TA_CENTER|TA_BASELINE);
//	for (int i=0;i<(horz-1);i++)
//	{
//		pDC->MoveTo(LeftGraph+i*step,TopGraph);
//		pDC->LineTo(LeftGraph+i*step,sizeTotal.cy-TopGraph);
//
//		if (((i%2)==0)&&(i!=0))
//		{
//			CString str;
//			str.Format("%.2lf",(i*step*pDoc->m_Step/ScaleX)/pow(10,MultX) );
//			pDC->TextOut(LeftGraph+i*step,ypos+12,str);
//		}
//	}
//	CString str2;
//	if (MultX!=0)
//	{
//		pDC->SetTextAlign(TA_RIGHT|TA_BASELINE);
//		str2.Format("*10^%d",MultX);
//		pDC->TextOut(sizeTotal.cx-2,ypos+12,str2);
//	}

//	int xpos=GetScrollPosition().x;
	//степень вертикальной координаты
//	int MultY=(int)maxD(log10(fabs(maxV)),log10(fabs(minV)) );
	pDC->SetTextAlign(TA_RIGHT|TA_BASELINE);
	for (int j=0;j<(nV-1);j++)
	{
		pDC->MoveTo(LeftGraph,
			int(sizeTotal.cy-TopGraph+(minV/ScaleY)+(j-nV0)*stepV) );
		pDC->LineTo(sizeTotal.cx-LeftGraph,
			int(sizeTotal.cy-TopGraph+(minV/ScaleY)+(j-nV0)*stepV) );

		CString str;
		str.Format("%.3lf",(nV0-j)*stepV*ScaleY/pow(10,powV) );
		pDC->TextOut(LeftGraph-4, int(5+sizeTotal.cy-TopGraph+(minV/ScaleY)+(j-nV0)*stepV),
			str);
	}*/
//	if (MultY!=0)
//	{
//		str2.Format("*10^%d",MultY);
//		pDC->TextOut(LeftGraph-2, 12,str2);
//	}

	//подписываем вертикальную ось
/*	CString str;
	switch (Type)
	{
	case 0:
			str=_T("Ux");
			break;
	case 1:
			str=_T("Uy");
			break;
	case 2:
			str=_T("Ua");
			break;
	case 3:
			str=_T("Ux`");
			break;
	case 4:
			str=_T("Uy`");
			break;
	case 5:
			str=_T("Ua`");
			break;
	}
	pDC->SetTextAlign(TA_LEFT|TA_BASELINE);
	pDC->TextOut(LeftGraph+2, 22, str);

*/	
	//контур
	pDC->SelectObject(pen4);
	pDC->MoveTo(LeftGraph,TopGraph);
	pDC->LineTo(LeftGraph,               sizeTotal.cy-DownGraph);
	pDC->LineTo(sizeTotal.cx-RightGraph, sizeTotal.cy-DownGraph);
	pDC->LineTo(sizeTotal.cx-RightGraph, TopGraph);
	pDC->LineTo(LeftGraph, TopGraph);

	//график
	pDC->SelectObject(&pen2);
	pDC->MoveTo(LeftGraph+int((pRowX[0]-minX)/ScaleX),
		        sizeTotal.cy-DownGraph-int((pRowY[0]-minY)/ScaleY));
	for (int t=1;t<SizeX;t++)
	{
		int X=int((pRowX[t]-minX)/ScaleX)+LeftGraph;
		int Y=sizeTotal.cy-DownGraph-int((pRowY[t]-minY)/ScaleY);
		
		pDC->LineTo(X,Y);
	}
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOld);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphView diagnostics

#ifdef _DEBUG
void CGraphView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGraphView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphView message handlers

void CGraphView::OnHoradd() 
{
	// TODO: Add your command handler code here
	ScaleX/=1.2;
	Invalidate();
}

void CGraphView::OnHorsub() 
{
	// TODO: Add your command handler code here
	ScaleX*=1.2;
	Invalidate();
}

void CGraphView::OnVertadd() 
{
	// TODO: Add your command handler code here
	ScaleY/=1.2;
	Invalidate();
}

void CGraphView::OnVertsub() 
{
	// TODO: Add your command handler code here
	ScaleY*=1.2;
	Invalidate();
}

BOOL CGraphView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL ret=CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
	Invalidate();
	return ret;
}

void CGraphView::OnUpdateAutosize(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(AutoSizing);
}

void CGraphView::OnAutosize() 
{
	// TODO: Add your command handler code here
	AutoSizing=!AutoSizing;
}

void CGraphView::OnUpdateSaverez(CCmdUI* pCmdUI) 
{
	CShemeDoc* pDoc = (CShemeDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your command update UI handler code here
/*	if (pKnot)
	{
		int NumFree=pKnot->FirstFree+(Type<3?Type:Type-3);
		BOOL State=pDoc->matr_RezY1.SizeY>NumFree;
		State=State&&(NumFree>=0);
		pCmdUI->Enable(State);
	}*/
}

void CGraphView::OnSaverez() 
{
	CShemeDoc* pDoc = (CShemeDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your command handler code here
	double h=pDoc->ParamIntegr.Step;	
	CFileDialog dlg(FALSE);
	CString ext("rez");
	dlg.m_ofn.lpstrDefExt=ext;
	TCHAR title[]="Сохранение результата";
	dlg.m_ofn.lpstrTitle=title;
	CString filter=("Файлы данных (*.rez)");
	filter+=(TCHAR)NULL;
	filter+="*.rez";
	filter+=("Все файлы (*.*)");
	filter+=(TCHAR)NULL;
	filter+="*.*";
	filter+=(TCHAR)NULL;
	filter+=(TCHAR)NULL;

	dlg.m_ofn.lpstrFilter=filter;
	dlg.m_ofn.nFilterIndex=0;

	//указатели на массивы данных для осей
	double *pRowX, *pRowY;

	switch (TypeX)
	{
	case 0: pRowX=pDoc->matr_RezY1.GetRow(pKnot->nXRez);	break;
	case 1: pRowX=pDoc->matr_RezY1.GetRow(pKnot->nYRez);	break;
	case 2: pRowX=pDoc->matr_RezY1.GetRow(pKnot->nARez[0]); break;
	case 3: pRowX=pDoc->matr_RezY2.GetRow(pKnot->nXRez);	break;
	case 4: pRowX=pDoc->matr_RezY2.GetRow(pKnot->nYRez);	break;
	case 5: pRowX=pDoc->matr_RezY2.GetRow(pKnot->nARez[0]); break;
	case 6: pRowX=Tt; break;
	}
	
	switch (TypeY)
	{
	case 0: pRowY=pDoc->matr_RezY1.GetRow(pKnot->nXRez);	break;
	case 1: pRowY=pDoc->matr_RezY1.GetRow(pKnot->nYRez);	break;
	case 2: pRowY=pDoc->matr_RezY1.GetRow(pKnot->nARez[0]); break;
	case 3: pRowY=pDoc->matr_RezY2.GetRow(pKnot->nXRez);	break;
	case 4: pRowY=pDoc->matr_RezY2.GetRow(pKnot->nYRez);	break;
	case 5: pRowY=pDoc->matr_RezY2.GetRow(pKnot->nARez[0]); break;
	case 6: pRowY=Tt; break;
	}

	if (dlg.DoModal()==IDOK)
	{
		fstream out(dlg.GetPathName(),ios::out);
		for (int i=0;i<pDoc->matr_RezY1.SizeX;i++)
		{
			out << pRowX[i] << "      ";
			out << pRowY[i] << endl;
		}
	}
}

