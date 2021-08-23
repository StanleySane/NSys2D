// GraphicView.cpp : implementation file
//

#include "stdafx.h"
#include "NSys2D.h"
#include "GraphicView.h"
#include "ShemeDoc.h"

#include<fstream>
#include "Sheme.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicView

IMPLEMENT_DYNCREATE(CGraphicView, CView)

const int ScreenStep=10;

CGraphicView::CGraphicView()
{
	maxY=maxX=12;
	minY=minX=-12;
	ScaleX=ScaleY=1;
	PointBeg=PointEnd=PointNew=CPoint(0,0);
	CoordOnly=RectOnly=false;
	SizeX=0;
	Mode_GetCoord=0;

	field.down=field.right=field.left=10;
	field.top=30;
	str_title=_T("График функции");

	pT=pRowX=pRowY=0;
	TypeX=TypeY=0;

	AutoSizing=true;
	Graph2Enable=false;

//	RegionMaxY[0]=RegionMaxY[1]=0;
//	RegionMinY[0]=RegionMinY[1]=0;
	RegionPoint[0]=RegionPoint[1]=CPoint(-50,-50);

}

CGraphicView::~CGraphicView()
{
	if (pT) delete pT;
	pT=0;
}


BEGIN_MESSAGE_MAP(CGraphicView, CView)
	//{{AFX_MSG_MAP(CGraphicView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_AUTOSIZE, OnAutosize)
	ON_UPDATE_COMMAND_UI(ID_AUTOSIZE, OnUpdateAutosize)
	ON_COMMAND(ID_GETCOORD, OnGetcoord)
	ON_UPDATE_COMMAND_UI(ID_GETCOORD, OnUpdateGetcoord)
	ON_COMMAND(ID_SAVEREZ, OnSaverez)
	ON_UPDATE_COMMAND_UI(ID_SAVEREZ, OnUpdateSaverez)
	ON_UPDATE_COMMAND_UI(ID_GRAPH2, OnUpdateGraph2)
	ON_COMMAND(ID_GRAPH2, OnGraph2)
	ON_COMMAND(ID_LOADGRAPH2, OnLoadgraph2)
	ON_COMMAND(ID_CALCMAT, OnCalcmat)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicView drawing

void CGraphicView::OnDraw(CDC* pDC)
{
	CShemeDoc* pDoc = (CShemeDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code here

	if (Mode_GetCoord)
	{
		if (RegionPoint[1]!=RegionPoint[0])
		{
			CPen pen(PS_SOLID|PS_GEOMETRIC,1,RGB(0,255,0));
			CPen *pOld=(CPen*)pDC->SelectObject(&pen);
			int oldpop2=pDC->SetROP2(R2_XORPEN);

			DrawRect(pDC, RegionPoint[1].x-ScreenStep,RegionPoint[1].y-ScreenStep,
					 RegionPoint[1].x+ScreenStep,RegionPoint[1].y+ScreenStep);

			DrawRect(pDC, RegionPoint[0].x-ScreenStep, RegionPoint[0].y-ScreenStep,
					 RegionPoint[0].x+ScreenStep, RegionPoint[0].y+ScreenStep);

			pDC->SetROP2(oldpop2);
			pDC->SelectObject(pOld);
		}
		RegionPoint[1]=RegionPoint[0];
		if (CoordOnly) 
		{
			CoordOnly=false;
			return;
		}
	}
	if (RectOnly)
	{
		RectOnly=false;
		if (AutoSizing) return;

		CPen pen(PS_DOT|PS_GEOMETRIC,1,RGB(0,0,0));
		CPen *pOld=(CPen*)pDC->SelectObject(&pen);
		int oldpop2=pDC->SetROP2(R2_XORPEN);

		if (PointEnd!=PointNew)
		{
			DrawRect(pDC, PointBeg.x,PointBeg.y,PointEnd.x,PointEnd.y);
			DrawRect(pDC, PointBeg.x,PointBeg.y,PointNew.x,PointNew.y);
		}
		PointEnd=PointNew;

		pDC->SetROP2(oldpop2);
		pDC->SelectObject(pOld);
		return;
	}

//Получаем размер клиентской части окна
	CRect clrect;
	GetClientRect(&clrect);

//Предварительная обработка данных
	//выбор нужных массивов из результатов расчета
	if (pKnot)
	{
		SizeX=pDoc->m_pSheme->matr_RezY1.SizeX;
		if (pT) delete pT;
		pT=0;
		if ((TypeX==9)||(TypeY==9))
		{
			pT=new double[SizeX];
			for (int r=0;r<SizeX;r++) 
				pT[r]=r*pDoc->m_pSheme->ParamIntegr.Step;
		}

		switch (TypeX)
		{
		case 0: pRowX=(pKnot->nXRez>=0?pDoc->m_pSheme->matr_RezY1.GetRow(pKnot->nXRez):0);	break;
		case 1: pRowX=(pKnot->nYRez>=0?pDoc->m_pSheme->matr_RezY1.GetRow(pKnot->nYRez):0);	break;
		case 2: pRowX=(pKnot->nARez[0]>=0?pDoc->m_pSheme->matr_RezY1.GetRow(pKnot->nARez[0]):0); break;
		case 3: pRowX=(pKnot->nXRez>=0?pDoc->m_pSheme->matr_RezY2.GetRow(pKnot->nXRez):0);	break;
		case 4: pRowX=(pKnot->nYRez>=0?pDoc->m_pSheme->matr_RezY2.GetRow(pKnot->nYRez):0);	break;
		case 5: pRowX=(pKnot->nARez[0]>=0?pDoc->m_pSheme->matr_RezY2.GetRow(pKnot->nARez[0]):0); break;
		case 6: pRowX=((pKnot->nXRez>=0)&&(pDoc->m_pSheme->matr_RezY3.SizeX>2)?pDoc->m_pSheme->matr_RezY3.GetRow(pKnot->nXRez):0);	break;
		case 7: pRowX=((pKnot->nYRez>=0)&&(pDoc->m_pSheme->matr_RezY3.SizeX>2)?pDoc->m_pSheme->matr_RezY3.GetRow(pKnot->nYRez):0);	break;
		case 8: pRowX=((pKnot->nARez[0]>=0)&&(pDoc->m_pSheme->matr_RezY3.SizeX>2)?pDoc->m_pSheme->matr_RezY3.GetRow(pKnot->nARez[0]):0); break;
		case 9: pRowX=pT; break;
		}
		
		switch (TypeY)
		{
		case 0: pRowY=(pKnot->nXRez>=0?pDoc->m_pSheme->matr_RezY1.GetRow(pKnot->nXRez):0);	break;
		case 1: pRowY=(pKnot->nYRez>=0?pDoc->m_pSheme->matr_RezY1.GetRow(pKnot->nYRez):0);	break;
		case 2: pRowY=(pKnot->nARez[0]>=0?pDoc->m_pSheme->matr_RezY1.GetRow(pKnot->nARez[0]):0); break;
		case 3: pRowY=(pKnot->nXRez>=0?pDoc->m_pSheme->matr_RezY2.GetRow(pKnot->nXRez):0);	break;
		case 4: pRowY=(pKnot->nYRez>=0?pDoc->m_pSheme->matr_RezY2.GetRow(pKnot->nYRez):0);	break;
		case 5: pRowY=(pKnot->nARez[0]>=0?pDoc->m_pSheme->matr_RezY2.GetRow(pKnot->nARez[0]):0); break;
		case 6: pRowY=((pKnot->nXRez>=0)&&(pDoc->m_pSheme->matr_RezY3.SizeX>2)?pDoc->m_pSheme->matr_RezY3.GetRow(pKnot->nXRez):0);	break;
		case 7: pRowY=((pKnot->nYRez>=0)&&(pDoc->m_pSheme->matr_RezY3.SizeX>2)?pDoc->m_pSheme->matr_RezY3.GetRow(pKnot->nYRez):0);	break;
		case 8: pRowY=((pKnot->nARez[0]>=0)&&(pDoc->m_pSheme->matr_RezY3.SizeX>2)?pDoc->m_pSheme->matr_RezY3.GetRow(pKnot->nARez[0]):0); break;
		case 9: pRowY=pT; break;
		}
	}
	else
	{
		SizeX=Dat.SizeX;
		pRowX=Dat.GetRow(0);		
		pRowY=Dat.GetRow(1);		
	}
	if ((!pRowX)||(!pRowY)||(SizeX==0))
	{
		//Вывод заголовка
		DrawTitle(pDC, clrect);
		//Рисование рамки
		DrawOutLine(pDC, clrect);
		CFont font;
		font.CreatePointFont(100,_T("Times New Roman"), 0);//MS Sans Serif
		pDC->SetBkColor(pDC->IsPrinting()?RGB(255,255,255):GetSysColor(COLOR_WINDOW));
		pDC->SetTextAlign(TA_LEFT|TA_TOP);	
		CFont *pOldFont=pDC->SelectObject(&font);
		pDC->TextOut(field.left+5,field.top+15,_T("Нет результатов расчета"));
		pDC->TextOut(field.left+5,field.top+40,_T("для этой степени свободы"));
		pDC->SelectObject(pOldFont);
		return;
	}

	if (AutoSizing) SetMaxMin();

	//Координаты для текста на графике
	CPoint c_text=CPoint(field.left,clrect.Height()-field.down);
	//Оси
	CPoint p=ShemeToScreen(CCoordD(0,0));
	if ((p.x>field.left)&&(p.x<(clrect.Width()-field.right)) )
		c_text.x=p.x;
	if ((p.y>field.top) &&(p.y<(clrect.Height()-field.down)) )
		c_text.y=p.y;

//Описание всех используемых карандашей
	//Сетка|PS_INSIDEFRAME
	//CPen pen1(PS_DOT|PS_GEOMETRIC,1,RGB(0,150,0));
	CPen pen1(PS_DOT,1,RGB(0,150,0));
	//График
//	CPen pen2(PS_SOLID|PS_GEOMETRIC,2,RGB(240,0,0));//220
	CPen pen2(PS_SOLID|PS_GEOMETRIC,1,pDC->IsPrinting()?RGB(0,0,0):RGB(240,0,0));//220
	//Оси
	CPen pen3(PS_SOLID|PS_GEOMETRIC,2,RGB(0,0,0));
	//Второй график
	CPen pen5(PS_SOLID|PS_GEOMETRIC,1,pDC->IsPrinting()?RGB(0,0,0):RGB(0,0,240));//220
	
	CPen *pOld=(CPen*)pDC->SelectObject(&pen1);

//Вывод заголовка
	DrawTitle(pDC, clrect);

//Рисование сетки
	//Установка шрифтов
	CFont font1;
	font1.CreatePointFont(75,_T("Arial"), 0);//MS Sans Serif
	pDC->SetBkColor(pDC->IsPrinting()?RGB(255,255,255):GetSysColor(COLOR_WINDOW));
	pDC->SetTextAlign(TA_CENTER|TA_BOTTOM);	
	CFont *pOldFont=pDC->SelectObject(&font1);

	pDC->SelectObject(&pen1);

	//Ориентировочный шаг сетки
	double ScrStepX=50;//шаг сетки
	double ScrStepY=50;//шаг сетки

	CString str;
	double StepX=GetStandartStep((maxX-minX)/(clrect.Width()-field.left-field.right)*ScrStepX);
	double StepY=GetStandartStep((maxY-minY)/(clrect.Height()-field.top-field.down)*ScrStepY);
	//ось X	
	if (StepX>0)
	{
		int nwidth=int(StepX/(maxX-minX)*(clrect.Width()-field.left-field.right)*0.8);
		double x=ceil(minX/StepX)*StepX;

		int pr=(int)floor(log10(StepX));
		if (pr>0) pr=0;
		
		int count=0;
		while (x<=maxX)
		{
			CPoint p1=ShemeToScreen(CCoordD(x, minY));
			CPoint p2=ShemeToScreen(CCoordD(x, maxY));
			pDC->MoveTo(p1);
			pDC->LineTo(p2);

			if (fabs(x)>(StepX*1E-5))
			{
				if( fabs(x) > 1e10 )	str.Format("%.*e", -pr+1, x);
				else	str.Format("%.*lf", -pr+1, x);
				int realwidth=pDC->GetTextExtent(str).cx;
				if ( (realwidth<nwidth) || (count%(realwidth/nwidth+1)==0) )
					pDC->TextOut(p1.x, c_text.y-1, str);
			}
			x+=StepX;
			count++;
		}
	}

	//ось Y
	if (StepY>0)
	{
		pDC->SetTextAlign(TA_LEFT|TA_BASELINE);
		double y=ceil(minY/StepY)*StepY;

		int pr=(int)floor(log10(StepY));
		if (pr>0) pr=0;

		while (y<=maxY)
		{
			CPoint p1=ShemeToScreen(CCoordD(minX, y));
			CPoint p2=ShemeToScreen(CCoordD(maxX, y));
			pDC->MoveTo(p1);
			pDC->LineTo(p2);

			if (fabs(y)>(StepY*1E-5))
			{
				if( fabs(y) > 1e10 )	str.Format("%.*e", -pr+1, y);
				else	str.Format("%.*lf", -pr+1, y);
				pDC->TextOut(c_text.x+2, p1.y, str);
			}

			y+=StepY;
		}
	}
	pDC->SelectObject(pOldFont);
	
	//Рисование рамки
	DrawOutLine(pDC, clrect);

	//Рисование осей
	//Оси
	pDC->SelectObject(&pen3);
	CPoint p1=ShemeToScreen(CCoordD(minX, 0));
	if ((p1.y>field.top)&&(p1.y<clrect.Height()-field.down))
	{
		CPoint p2=ShemeToScreen(CCoordD(maxX, 0));
		pDC->MoveTo(p1);
		pDC->LineTo(p2);
	}
	p1=ShemeToScreen(CCoordD(0, minY));
	if ((p1.x>field.left)&&(p1.x<clrect.Width()-field.right))
	{
		CPoint p2=ShemeToScreen(CCoordD(0, maxY));
		pDC->MoveTo(p1);
		pDC->LineTo(p2);
	}

	//Подписывание осей	

	//Рисование графика
	CRect rect(field.left, field.top, clrect.Width()-field.right, clrect.Height()-field.down);
	//if (pDC->IsPrinting()) 
		pDC->LPtoDP(&rect);

	CRgn rgn;
	rgn.CreateRectRgnIndirect(&rect);
	pDC->SelectObject(&rgn);
	//rgn.CreateRectRgn(field.left, field.top, clrect.Width()-field.right, clrect.Height()-field.down);
	//rgn.SetRectRgn(&rect);
	//LPtoDP(rgn);

	//pDC->SelectClipRgn(&rgn, RGN_COPY);
	//график
		if (Graph2Enable)
		{
			pDC->SelectObject(&pen5);
			p=ShemeToScreen(CCoordD(Graph2[0][0], Graph2[1][0]));
			pDC->MoveTo(p);
			for (int t=1;t<Graph2.SizeX;t++)
			{
				p=ShemeToScreen(CCoordD(Graph2[0][t], Graph2[1][t]));
				if (p.x<-32000) p.x=-32000;
				if (p.x> 32000) p.x= 32000;
				if (p.y<-32000) p.y=-32000;
				if (p.y> 32000) p.y= 32000;
				pDC->LineTo(p);
			}
		}
	
	pDC->SelectObject(&pen2);
	p=ShemeToScreen(CCoordD(pRowX[0],pRowY[0]));
	pDC->MoveTo(p);
	for (int t=1;t<SizeX;t++)
	{
		p=ShemeToScreen(CCoordD(pRowX[t],pRowY[t]));
		if (p.x<-32000) p.x=-32000;
		if (p.x> 32000) p.x= 32000;
		if (p.y<-32000) p.y=-32000;
		if (p.y> 32000) p.y= 32000;
		pDC->LineTo(p);
	}
	pDC->SelectClipRgn(0);

	pDC->SelectObject(pOld);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicView diagnostics

#ifdef _DEBUG
void CGraphicView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicView message handlers

void CGraphicView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CView::OnLButtonDown(nFlags, point);
	
	if (Mode_GetCoord)
	{
		//Вычисление максимумов и минимумов, попадающих в квадрат
		CCoordD c=ScreenToSheme(RegionPoint[0]);
		CCoordD c1=ScreenToSheme(CPoint(RegionPoint[0].x+ScreenStep, RegionPoint[0].y+ScreenStep));
		double dx=fabs(c.x-c1.x);
		double dy=fabs(c.y-c1.y);

		double maxY=0, minY=0, maxX=0, minX=0;
		BOOL existcoord=false, first=true;
		for (int i=0;i<(SizeX-1);i++)
		{
			double x1=pRowX[i];
			double y1=pRowY[i];
			
			if ( (fabs(x1-c.x)<dx) && (fabs(y1-c.y)<dy) )
			{
				if ((first)||(maxY<y1)) 
				{ maxY=y1; existcoord=true; }
				if ((first)||(minY>y1)) 
				{ minY=y1; existcoord=true; }
				if ((first)||(maxX<x1)) 
				{ maxX=x1; existcoord=true; }
				if ((first)||(minX>x1)) 
				{ minX=x1; existcoord=true; }

				if (existcoord) first=false;
			}
		}
		if (Graph2Enable)
		{
			for (int i=0;i<Graph2.SizeX;i++)
			{
				double x1=Graph2[0][i];
				double y1=Graph2[1][i];
				
				if ( (fabs(x1-c.x)<dx) && (fabs(y1-c.y)<dy) )
				{
					if ((first)||(maxY<y1)) 
					{ maxY=y1; existcoord=true; }
					if ((first)||(minY>y1)) 
					{ minY=y1; existcoord=true; }
					if ((first)||(maxX<x1)) 
					{ maxX=x1; existcoord=true; }
					if ((first)||(minX>x1)) 
					{ minX=x1; existcoord=true; }
					if (existcoord) first=false;
				}
			}
		}
		if (existcoord)
		{		
			CString str;
			str.Format("max Y = %.5lg\nmin Y = %.5lg\nmax X = %.5lg\nmin X = %.5lg",
				maxY, minY, maxX, minX);

			//Вывод сообщения
			MessageBox(str,"Значения");
		}


		return;

	}

	NormalizePoint(&point);
	PointNew=PointEnd=PointBeg=point;
}

void CGraphicView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CView::OnMouseMove(nFlags, point);

	if (Mode_GetCoord)
	{
		NormalizePoint(&point);
		RegionPoint[0]=point;
		CoordOnly=true;
		Invalidate(false);
		return;
	}
	if (nFlags&MK_LBUTTON)
	{
		NormalizePoint(&point);
		PointNew=point;
		RectOnly=true;
		Invalidate(FALSE);
		return;
	}
}

void CGraphicView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if ((!AutoSizing)&&(!Mode_GetCoord))
	{
		if ((PointBeg.x==PointEnd.x)||(PointBeg.y==PointEnd.y))
		{
			CCoordD c=ScreenToSheme(point);
			CCoordD csize=CCoordD((maxX-minX)*0.5, (maxY-minY)*0.5);

			const double mult=0.5;
			maxX=c.x+csize.x*mult;
			minX=c.x-csize.x*mult;
			maxY=c.y+csize.y*mult;
			minY=c.y-csize.y*mult;
		}
		else
		{
			CCoordD c1=ScreenToSheme(PointBeg);
			CCoordD c2=ScreenToSheme(PointEnd);

			minX=min(c1.x, c2.x);
			minY=min(c1.y, c2.y);
			maxX=max(c1.x, c2.x);
			maxY=max(c1.y, c2.y);
		}

		PointNew=PointEnd=PointBeg;
		Invalidate(true);
	}

	CView::OnLButtonUp(nFlags, point);
}

inline CCoordD CGraphicView::ScreenToSheme(POINT & p)
{
	CRect cl;
	GetClientRect(&cl);

	return CCoordD(
		(maxX-minX)*(p.x-field.left)/(cl.Width()-field.left-field.right)+minX,
	   -(maxY-minY)*(p.y-field.top)/(cl.Height()-field.top-field.down)+maxY);
}

inline CPoint CGraphicView::ShemeToScreen(CCoordD & c)
{
	CRect cl;
	GetClientRect(&cl);

	double x=(c.x-minX)*(cl.Width()-field.left-field.right)/(maxX-minX)+field.left;
	double y=(c.y-maxY)*(cl.Height()-field.top-field.down)/(minY-maxY)+field.top;

	const int maxint=32000;

	if (x>maxint)  x=maxint;
	if (x<-maxint) x=-maxint;
	if (y>maxint)  y=maxint;
	if (y<-maxint) y=-maxint;

	return CPoint( int(x), int(y) );
}

inline BOOL CGraphicView::NormalizePoint(CPoint *p)
{
	CRect cl;
	GetClientRect(&cl);

	BOOL Change=false;

	if (p->x<field.left)
	{
		p->x=field.left;
		Change=true;
	}
	if (p->x>(cl.Width()-field.right))  
	{
		p->x=cl.Width()-field.right;
		Change=true;
	}
	if (p->y<field.top)				    
	{
		p->y=field.top;
		Change=true;
	}
	if (p->y>(cl.Height()-field.down))  
	{
		p->y=cl.Height()-field.down;
		Change=true;
	}
	return Change;
}


//Рамка
inline void CGraphicView::DrawOutLine(CDC * pDC, CRect &clrect)
{
	CPen pen(PS_SOLID|PS_GEOMETRIC,1,RGB(0,0,0));
	CPen *pOld=(CPen*)pDC->SelectObject(&pen);

	DrawRect(pDC, field.left, field.top, clrect.Width()-field.right, clrect.Height()-field.down);
	pDC->SelectObject(pOld);
}

//Вывод заголовка
inline void CGraphicView::DrawTitle(CDC * pDC, CRect &clrect)
{
	CFont font1;
	font1.CreatePointFont(100,_T("Times New Roman"), 0);//MS Sans Serif
	pDC->SetBkColor(pDC->IsPrinting()?RGB(255,255,255):GetSysColor(COLOR_WINDOW));
	pDC->SetTextAlign(TA_CENTER|TA_BASELINE);	
	CFont *pOldFont=pDC->SelectObject(&font1);
	pDC->TextOut(clrect.Width()/2,2*field.top/3,str_title);
	pDC->SelectObject(pOldFont);
}

double CGraphicView::GetStandartStep(double _stp)
{
	const int StandartStep[]={0, 10, 20, 25, 40, 50, 75, 130};

	//временно убираемая степень
	double powX=pow(10,ceil(log10(_stp))-2);
	int stp=int(_stp/powX);

	for (int i=0;i<sizeof(StandartStep)/sizeof(int);i++)
		if ( (stp>StandartStep[i])&&(stp<StandartStep[i+1]) )
		{
			if ((stp-StandartStep[i])>(StandartStep[i+1]-stp))
				 stp=StandartStep[i+1];
			else stp=StandartStep[i];
			break;
		}
	return stp*powX;
}

void CGraphicView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!AutoSizing)
	{
		if (nFlags&MK_LBUTTON)
		{
			PointNew=PointEnd=PointBeg;
		}
		else
		{
			CCoordD c=ScreenToSheme(point);
			CCoordD csize=CCoordD((maxX-minX)*0.5, (maxY-minY)*0.5);

			const double mult=3;
			maxX=c.x+csize.x*mult;
			minX=c.x-csize.x*mult;
			maxY=c.y+csize.y*mult;
			minY=c.y-csize.y*mult;
		}
		Invalidate(true);
	}
	
	CView::OnRButtonDown(nFlags, point);
}


void CGraphicView::SetMaxMin()
{
	CShemeDoc* pDoc = (CShemeDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	if ((pRowX)&&(pRowY))
	{
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
		maxX+=(maxX-minX)*0.05;
		minX-=(maxX-minX)*0.05;
		maxY+=(maxY-minY)*0.05;
		minY-=(maxY-minY)*0.05;
		if (maxY==minY)
		{	
			if (maxY==0.0)
			{	
				maxY=1;			
				minY=-1;	
			}
			else		
			{	
				maxY*=1.2;		
				minY*=0.8;	
			}
		}
		if (maxX==minX)
		{
			if (maxX==0.0){	maxX=1;			minX=-1;	}
			else		{	maxX*=1.2;		minX*=0.8;	}
		}
	}
}

void CGraphicView::OnAutosize() 
{
	// TODO: Add your command handler code here
	AutoSizing=!AutoSizing;
	if (AutoSizing) Invalidate(true);
}

void CGraphicView::OnUpdateAutosize(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((AutoSizing)&&(pRowX)&&(pRowY));	
}

void CGraphicView::OnGetcoord() 
{
	// TODO: Add your command handler code here
	Mode_GetCoord=!Mode_GetCoord;
	if (!Mode_GetCoord)
	{
		RegionPoint[0]=RegionPoint[1]=CPoint(-50,-50);
		CoordOnly=false;
		Invalidate(true);
	}

}

void CGraphicView::OnUpdateGetcoord(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((Mode_GetCoord)&&(pRowX)&&(pRowY));
}

void CGraphicView::DrawRect(CDC* pDC, int x1, int y1, int x2, int y2)
{
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y1);
	pDC->LineTo(x2,y2);
	pDC->LineTo(x1,y2);
	pDC->LineTo(x1,y1);
}

void CGraphicView::OnSaverez() 
{
	CShemeDoc* pDoc = (CShemeDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your command handler code here

//	double h=pDoc->m_Step;	

	CFileDialog dlg(FALSE);
	CString ext("rez");
	dlg.m_ofn.lpstrDefExt=ext;
	TCHAR title[]="Сохранение результата";
	dlg.m_ofn.lpstrTitle=title;
	CString filter=("Файлы данных (*.rez)");
	filter+=(TCHAR)NULL;
	filter+="*.rez";
	filter+=(TCHAR)NULL;
	filter+=("Все файлы (*.*)");
	filter+=(TCHAR)NULL;
	filter+="*.*";
	filter+=(TCHAR)NULL;
	filter+=(TCHAR)NULL;

	dlg.m_ofn.lpstrFilter=filter;
	dlg.m_ofn.nFilterIndex=1;

	if (dlg.DoModal()==IDOK)
	{
		fstream out(dlg.GetPathName(),ios::out);
		out << SizeX << endl;
		for (int i=0;i<SizeX;i++)
			out << pRowX[i] << " " << pRowY[i] << endl;
	}
}

void CGraphicView::OnUpdateSaverez(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((pRowX)&&(pRowY));		
}

void CGraphicView::OnUpdateGraph2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck((Graph2Enable)&&(Graph2.SizeX));			
	pCmdUI->Enable((Graph2.SizeX));			
}

void CGraphicView::OnGraph2() 
{
	// TODO: Add your command handler code here
	Graph2Enable=!Graph2Enable;
	Invalidate(true);
}

void CGraphicView::OnLoadgraph2() 
{
	CShemeDoc* pDoc = (CShemeDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your command handler code here

	CString filter=("Файлы данных (*.rez)");
	filter+=(TCHAR)NULL;
	filter+="*.rez";
	filter+=(TCHAR)NULL;
	filter+=("Все файлы (*.*)");
	filter+=(TCHAR)NULL;
	filter+="*.*";
	filter+=(TCHAR)NULL;
	filter+=(TCHAR)NULL;

	CFileDialog dlg(true);
	CString ext("rez");
	dlg.m_ofn.lpstrDefExt=ext;

	TCHAR title[]="Чтение данных";
	dlg.m_ofn.lpstrTitle=title;

	dlg.m_ofn.lpstrFilter=filter;
	dlg.m_ofn.nFilterIndex=1;

	if (dlg.DoModal()==IDOK)
	{
		fstream fin(dlg.GetPathName(), ios::in);
		if (!fin) return;
		//Считаем размер данных
		double tmp; 
		int cnt=0;
		while (!fin.eof())
		{
			fin >> tmp >> tmp;
			cnt++;
		}
		if (cnt<2) return;
		Graph2.ReSize(2,cnt-1);
		fin.close();
		//читаем данные
		fin.open(dlg.GetPathName(), ios::in);
		//fin.rdbuf()->seekpos(0,ios::in);
		for (int i=0;i<Graph2.SizeX;i++)
			fin >> Graph2[0][i] >> Graph2[1][i]; 

		Graph2Enable=true;
		Invalidate(true);
	}	
}


BOOL CGraphicView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// TODO: call DoPreparePrinting to invoke the Print dialog box
	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(1);
	return DoPreparePrinting(pInfo);
	
//	return CView::OnPreparePrinting(pInfo);
}

void CGraphicView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect clrect;
	GetClientRect(&clrect);
	pDC->SetMapMode(MM_ISOTROPIC);

	pDC->SetWindowExt(clrect.Width(), clrect.Height());
	pDC->SetWindowOrg(0,0);
	
	CSize sizePaper=CSize(pDC->GetDeviceCaps(HORZRES),
						  pDC->GetDeviceCaps(VERTRES));

	CRect rect(0,0,sizePaper.cx,sizePaper.cy);
	pDC->SetViewportExt(rect.Width(), rect.Height());

//	pDC->LPtoDP(&rect);
	pInfo->m_rectDraw=rect;
	OnDraw( pDC );
	
	//CView::OnPrint(pDC, pInfo);
}

void CGraphicView::OnCalcmat() 
{
	// TODO: Add your command handler code here
	CShemeDoc* pDoc = (CShemeDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: Add your command handler code here

	double matt=0;
	double disp=0;

	for (int i=0;i<SizeX;i++)
	{
		matt+=pRowY[i];
	}

	if( SizeX == 0 )	matt = 0;
	else	matt /= SizeX;

	for (int j=0;j<SizeX;j++)
	{
		disp+=(pRowY[j]-matt)*(pRowY[j]-matt);
	}
	disp/=SizeX-1;
	CString str;

	if( (fabs(matt) > 1e10)||(fabs(disp) > 1e10) )
		str.Format("Математическое ожидание =%.*e\nДисперсия               =%.*e\nСреднеквадр. отклонение =%.*e",matt,disp,sqrt(disp));
	else
		str.Format("Математическое ожидание =%.10lg\nДисперсия               =%.10lg\nСреднеквадр. отклонение =%.10lg",matt,disp,sqrt(disp));
	MessageBox(str,"Статистики");
}
