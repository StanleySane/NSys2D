// Knot.cpp: implementation of the CKnot class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "Knot.h"
//#include "KnotDlg.h"

#include "KnotPropertySheet.h"
#include<algorithm>
	
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKnot::CKnot()
{
	SetCoord("0","0");
	Init();
}

CKnot::CKnot(CString strx, CString stry)
{
	SetCoord(strx,stry);
	Init();
}

CKnot::~CKnot()
{
}

CCoordD CKnot::GetCoord(double multmove/*=0*/)
{
	return CCoordD(coord.x+multmove*MoveX, coord.y+multmove*MoveY);
}

int CKnot::SetCoord(CString strx, CString stry)
{
	CExpression e;
	CCoordD c;
	int ret1,ret2;

	ret1=e.IsNum(strx,&c.x);
	ret2=e.IsNum(stry,&c.y);

	if ((!ret1)&&(!ret2))
	{
		coord=c;
		str_X=strx;
		str_Y=stry;
		return 1;
	}
	return 0;
}

void CKnot::Draw(CDC * pDC, CParamView* pParamView)
{
	POINT point=ShemeToScreen(GetCoord(pParamView->MultMove),pParamView);

	bool bGray = (pParamView->Gray)?true:false;
	bool bDraw = !pParamView->m_vecSelNumbers.empty();

	if( pParamView->m_iClickedObjects == 2 )	bGray = false;

	int iOldMode;
	if( bDraw )
	{
		if( bDraw )	iOldMode = SelectMode;
		//если рисуются одни элементы, то узлы рисовать не надо
		SelectMode = 0;
		bGray = true;

		if( (pParamView->m_bSelType==false)||(pParamView->m_iClickedObjects!=1) )
		{
			//рисуются одни узлы
			ARRAY::iterator it = std::find( pParamView->m_vecSelNumbers.begin(),
									pParamView->m_vecSelNumbers.end(), Num );
			if( it != pParamView->m_vecSelNumbers.end() )
			{
				//этот узел рисуется
				if( ((pParamView->m_iClickedObjects==0)&&(pParamView->m_bSelType==false))
					||(pParamView->m_iClickedObjects==2) )
				{
					SelectMode = 1;
					bGray = false;
				}
			}
			else
			{
				if( pParamView->m_iClickedObjects == 2 )
				{
					bGray = false;
				}
			}
		}
	}

	const int diam=3;	
	COLORREF col;
	col=(SelectMode?RGB(250,0,0):RGB(0,0,250));

	if (bGray)
		col=RGB(200,200,200);

	CPen pen(PS_SOLID|PS_GEOMETRIC,1,col);
	CPen *pOld=(CPen*)pDC->SelectObject(&pen);
	CBrush *pOldbrush;//,*pOldbrush2;

	COLORREF col2;
	//Если узел выбран, то красный
	if (SelectMode) col2=RGB(250,0,0);
	//иначе если жестко и есть закрепление, то синий
	else if ((ConnectType==0)&&(FixedType==0)) col2=RGB(0,0,250);
		//иначе цвет окна
	    else col2=pDC->IsPrinting()?RGB(255,255,255):GetSysColor(COLOR_WINDOW);

	if( bGray )	col2 = RGB(200,200,200);
	
	CBrush brush(col2);
	pOldbrush=(CBrush*)pDC->SelectObject(&brush);

	//Номер узла надо выводить и при рисовании одних только
	//узлов и при рисовании элементов, если элемент содержит
	//данный узел
	if ( (Num)&&((!pParamView->Gray)||(!bGray))&&(pParamView->m_bNumKnots) )
	{

//		CFont font1;
//		font1.CreatePointFont(100,_T("Arial"), 0);//MS Sans Serif//75
		pDC->SetBkColor(pDC->IsPrinting()?RGB(255,255,255):GetSysColor(COLOR_WINDOW));
		pDC->SetTextAlign(TA_RIGHT|TA_BOTTOM);	
//		CFont *pOldFont=(CFont*)pDC->SelectObject(&font1);
		CFont *pOldFont = (CFont*)pDC->SelectObject(&(pParamView->m_fntKnot));

		CString str; 
		str.Format("%d",Num);

		COLORREF oldClr = pDC->SetTextColor(pParamView->m_clrNumKnots);
		int oldBkMode = pDC->SetBkMode(TRANSPARENT);
		pDC->TextOut(point.x-2,point.y-2,str);
		pDC->SetBkMode(oldBkMode);
		pDC->SetTextColor(oldClr);

		pDC->SelectObject(pOldFont);
	}

	//Стрелочки (приложение возмущения)
	if (!pParamView->Gray) DrawPower(pDC, point, pParamView);
	//рисуем номера степеней свободы:
	if( pParamView->m_bFreeNums )
		DrawFreeNums( pDC, point, pParamView );
	//Закрепление
	if ((FixedType)&&( (!pParamView->Gray)||(!bGray) ) ) DrawFixed(pDC,point,pParamView);

	if ( (FixedType!=4) || ((FixedType==4)&&(SelectMode)) )
		pDC->Ellipse(point.x-diam,point.y-diam,point.x+diam,point.y+diam);

	pDC->SelectObject(pOldbrush);

	pDC->SelectObject(pOld);

	if( bDraw )	SelectMode = iOldMode;
}

CString CKnot::GetName(UINT num/*=0*/)
{
	CString str;
	if (Num)
		str.Format("№%d  [%.2lf,%.2lf]",Num,coord.x,coord.y);
	else
		str.Format("[%.2lf,%.2lf]",coord.x,coord.y);
	return str;
}

CString CKnot::GetStrX()
{
	return str_X;
}

CString CKnot::GetStrY()
{
	return str_Y;
}

CPoint CKnot::GetScreenCoord(CParamView* pParamView)
{
	return (CPoint)ShemeToScreen(GetCoord(pParamView->MultMove),pParamView);//-pParamView->pos;
}

int CKnot::GoDlg( bool full /*true*/)
{
	//full показывает надо ли выводить полный диалог
	//или достаточно вывода общих св-в узлов
	CKnotPropertySheet *pdlg = new CKnotPropertySheet(this, 0, full );
	if( pdlg->DoModal() == IDOK )
	{
		return 1;	
	}
	return 0;
}

void CKnot::DrawFixed(CDC * dc, POINT & point, CParamView *pParamView)
{
	CPen pen1(PS_SOLID|PS_GEOMETRIC,1,RGB(0,0,0));	
	CPen pen2(PS_SOLID|PS_GEOMETRIC,2,RGB(0,0,0));	
	CPen pen3(PS_SOLID|PS_GEOMETRIC,1,GetSysColor(COLOR_WINDOW));	
	CPen *pOldpen=(CPen*)dc->SelectObject(&pen2);
	CBrush brush(GetSysColor(COLOR_WINDOW));
	CBrush *pOldbrush=(CBrush*)dc->SelectObject(&brush);

	int rad=3,i;

	switch (FixedType)
	{
	case 1: 
			dc->MoveTo(point.x,point.y);
			dc->LineTo(point.x,point.y+12);
			
			dc->MoveTo(point.x-8,point.y+12);
			dc->LineTo(point.x+8,point.y+12);

			dc->SelectObject(&pen1);
			
			for(i=0;i<6;i++)
			{
				dc->MoveTo(point.x-7+3*i,point.y+12);
				dc->LineTo(point.x-7+3*i-3,point.y+16);
			}
			
			dc->Ellipse(point.x-rad,point.y+12-rad,
					point.x+rad,point.y+12+rad);

			dc->Ellipse(point.x-rad,point.y-rad,
					point.x+rad,point.y+rad);
			
			break;
	case 2: 
			dc->MoveTo(point.x,point.y);
			dc->LineTo(point.x+12,point.y);
			
			dc->MoveTo(point.x+12,point.y-8);
			dc->LineTo(point.x+12,point.y+8);

			dc->SelectObject(&pen1);
			
			for(i=0;i<6;i++)
			{
				dc->MoveTo(point.x+12,point.y-7+3*i);
				dc->LineTo(point.x+16,point.y-7+3*i-3);
			}
			
			dc->Ellipse(point.x+12-rad,point.y-rad,
					point.x+12+rad,point.y+rad);

			dc->Ellipse(point.x-rad,point.y-rad,
					point.x+rad,point.y+rad);
			
			break;
	case 3: 
			dc->MoveTo(point.x-10,point.y+12);
			dc->LineTo(point.x+10,point.y+12);

			dc->MoveTo(point.x,point.y);
			dc->LineTo(point.x-7,point.y+12);
			
			dc->MoveTo(point.x,point.y);
			dc->LineTo(point.x+7,point.y+12);

			dc->SelectObject(&pen1);
			
			for(i=0;i<7;i++)
			{
				dc->MoveTo(point.x-8+3*i,point.y+12);
				dc->LineTo(point.x-8+3*i-3,point.y+16);
			}

			dc->Ellipse(point.x-rad,point.y-rad,
					point.x+rad,point.y+rad);

			break;
	case 4:
		{
			double ang=-acos(-1)/2.0;
			if (FriendCoord.GetNorm()>0)
			{
				CPoint p=ShemeToScreen(FriendCoord,pParamView);
				ang=CCoordD(p-point).GetAng();
			}
			
			/*if (SelectMode)
			{
				dc->SelectObject(&pen3);
				dc->Ellipse(point.x-rad,point.y-rad,
						point.x+rad,point.y+rad);
				dc->SelectObject(&pen1);
				dc->Ellipse(point.x-2,point.y-2,
						point.x+2,point.y+2);
				dc->SelectObject(&pen2);
			}*/

			dc->MoveTo(int(point.x+10*sin(ang)),int(point.y-10*cos(ang)));
			dc->LineTo(int(point.x-10*sin(ang)),int(point.y+10*cos(ang)));

			dc->SelectObject(&pen1);
			
			for(i=0;i<7;i++)
			{
				CPoint p=CPoint(-8+3*i,0);
				CPoint p2=CPoint(int(-p.y*sin(ang)+p.x*cos(ang)),int(p.y*cos(ang)+p.x*sin(ang)) );
				dc->MoveTo(point.x-p2.y,point.y+p2.x);
				p=CPoint(-8+3*i-3,4);
				p2=CPoint(int(-p.y*sin(ang)+p.x*cos(ang)),int(p.y*cos(ang)+p.x*sin(ang)) );
				dc->LineTo(point.x-p2.y,point.y+p2.x);
			}
		}
		break;
	case 5:
			dc->MoveTo(point.x-5,point.y+3);
			dc->LineTo(point.x+3,point.y-5);
			
			dc->MoveTo(point.x-3,point.y+5);
			dc->LineTo(point.x+5,point.y-3);
			break;
	default:
		ASSERT(FALSE);
	}
	dc->SelectObject(pOldbrush);
	dc->SelectObject(pOldpen);
}

void CKnot::operator =(CKnot & knot)
{
	coord=knot.coord;
	FixedType=knot.FixedType;
	Num=knot.Num;
	OldMode=0;
	SelectMode=0;
	str_X=knot.str_X;
	str_Y=knot.str_Y;

	str_Ux=knot.str_Ux;
	str_Uy=knot.str_Uy;
	str_Ua=knot.str_Ua;
	str_Uxp=knot.str_Uxp;
	str_Uyp=knot.str_Uyp;
	str_Uap=knot.str_Uap;

	Ux=knot.Ux;
	Uy=knot.Uy;
	Ua=knot.Ua;
	Uxp=knot.Uxp;
	Uyp=knot.Uyp;
	Uap=knot.Uap;

	//Силовое Возмущение
	Ax=knot.Ax;
	Wx=knot.Wx;
	Fix=knot.Fix;
	TypePx=knot.TypePx;
	str_Ax=knot.str_Ax;
	str_Wx=knot.str_Wx;
	str_Fix=knot.str_Fix;
	str_Px=knot.str_Px;
	PxEnable=knot.PxEnable;
	SpPx=knot.SpPx;

	Ay=knot.Ay;
	Wy=knot.Wy;
	Fiy=knot.Fiy;
	TypePy=knot.TypePy;
	str_Ay=knot.str_Ay;
	str_Wy=knot.str_Wy;
	str_Fiy=knot.str_Fiy;
	str_Py=knot.str_Py;
	PyEnable=knot.PyEnable;
	SpPy=knot.SpPy;

	//Кинематическое возмущение
	uAx=knot.uAx;
	uWx=knot.uWx;
	uFix=knot.uFix;
	TypeUx=knot.TypeUx;
	str_uAx=knot.str_uAx;
	str_uWx=knot.str_uWx;
	str_uFix=knot.str_uFix;
	str_uUx=knot.str_uUx;
	UxEnable=knot.UxEnable;
	SpUx=knot.SpUx;

	uAy=knot.uAy;
	uWy=knot.uWy;
	uFiy=knot.uFiy;
	TypeUy=knot.TypeUy;
	str_uAy=knot.str_uAy;
	str_uWy=knot.str_uWy;
	str_uFiy=knot.str_uFiy;
	str_uUy=knot.str_uUy;
	UyEnable=knot.UyEnable;
	SpUy=knot.SpUy;
}

void CKnot::SetFixedKnotMDC(CMatr & mM, CMatr & mD, CMatr & mC)
{
/*	double FixedValue=0, FixedValue2=0;//10E25;

	int n=FirstFree,i;
	if (n<0) return;*/
/*	switch (FixedType)
	{
	case 2:
	case 3:
	case 4:
			for (i=0;i<mC.SizeY;i++)
			{
				mC[i][n]=FixedValue;
				mC[n][i]=FixedValue;
			}
			if (FixedType==2) break;
	case 1:
			for (i=0;i<mC.SizeY;i++)
			{
				mC[i][n+1]=FixedValue;
				mC[n+1][i]=FixedValue;
			}
			if (FixedType!=4) break;

			for (int j=0; j<mC.SizeY;j++)
				for (i=0;i<(fi_General+fi_n);i++)
				{
					mC[j][n+i+2]=FixedValue;
					mC[n+i+2][j]=FixedValue;
				}
			break;
	}*/
	//матрица масс
/*	switch (FixedType)
	{
	case 2:
	case 3:
	case 4:
			for (i=0;i<mM.SizeY;i++)
			{
				mM[i][n]=(i==n?FixedValue2:FixedValue);
				mM[n][i]=(i==n?FixedValue2:FixedValue);
			}
			if (FixedType==2) break;
	case 1:
			for (i=0;i<mC.SizeY;i++)
			{
				mM[i][n+1]=(i==(n+1)?FixedValue2:FixedValue);
				mM[n+1][i]=(i==(n+1)?FixedValue2:FixedValue);
			}
			if (FixedType!=4) break;

			for (int j=0; j<mM.SizeY;j++)
				for (i=0;i<(NumFree-2);i++)
				{
					mM[j][n+i+2]=(j==(n+i+2)?FixedValue2:FixedValue);
					mM[n+i+2][j]=(j==(n+i+2)?FixedValue2:FixedValue);
				}
			break;
	}*/
}

double CKnot::GetUx(double Tt, int p/*=0*/)
{
	if (UxEnable)
	{
		if (TypeUx==0)
		{
			switch (p)
			{
			case 0:		return uAx*sin(uWx*Tt+uFix); 
			case 1:		return uAx*uWx*cos(uWx*Tt+uFix); 
			case 2:		return -uAx*uWx*uWx*sin(uWx*Tt+uFix); 
			}
		}
		if (TypeUx==1)
		{
			CString str;
			str.Format("Ошибка в выражении для кинематического\n возмущения в узле № %d",Num);
			double val, val1, val2;
			double h=(Tt!=0.0?0.001*Tt:0.001);

			CExpression e;
			CIDValuesMap idv;

			idv.SetAt(_T("t"),Tt+h);
			if (e.IsNum(str_uUx,&val2,&idv))
			{
				AfxMessageBox(str); 
				return -1;
			}
			idv.SetAt(_T("t"),Tt-h);
			if (e.IsNum(str_uUx,&val1,&idv))
			{
				AfxMessageBox(str); 
				return -1;
			}
			idv.SetAt(_T("t"),Tt);
			if (e.IsNum(str_uUx,&val,&idv))
			{
				AfxMessageBox(str); 
				return -1;
			}

			switch (p)
			{
			case 0:		return val; 
			case 1:		return (val2-val1)/(2*h);
			case 2:		return (val2-2*val+val1)/(h*h);
			}
		}
		if (TypeUx==2)
		{
			double val, val1, val2;
			double h=/*SpUx.dt;//*/(Tt!=0.0?0.001*Tt:0.001);

			val2=SpUx.GetValue(Tt+h);
			val1=SpUx.GetValue(Tt-h);
			val=SpUx.GetValue(Tt);

			switch (p)
			{
			case 0:		return val; 
			case 1:		return (val2-val1)/(2*h);
			case 2:		return (val2-2*val+val1)/(h*h);
			}
		}
	}
	else
	{
		switch (p)
		{
		case 0:		return Ux; 
		case 1:		return Uxp;
		case 2:		return 0;
		}
	}
	return 0;
}

double CKnot::GetUy(double Tt, int p/*=0*/)
{
	if (UyEnable)
	{
		if (TypeUy==0)
		{
			switch (p)
			{
			case 0:		return uAy*sin(uWy*Tt+uFiy); 
			case 1:		return uAy*uWy*cos(uWy*Tt+uFiy); 
			case 2:		return -uAy*uWy*uWy*sin(uWy*Tt+uFiy); 
			}
		}
		if (TypeUy==1)
		{
			CString str;
			str.Format("Ошибка в выражении для кинематического\n возмущения в узле № %d",Num);
			double val, val1, val2;
			double h=(Tt!=0.0?0.001*Tt:0.001);

			CExpression e;
			CIDValuesMap idv;

			idv.SetAt(_T("t"),Tt+h);
			if (e.IsNum(str_uUy,&val2,&idv))
			{
				AfxMessageBox(str); 
				return -1;
			}
			idv.SetAt(_T("t"),Tt-h);
			if (e.IsNum(str_uUy,&val1,&idv))
			{
				AfxMessageBox(str); 
				return -1;
			}
			idv.SetAt(_T("t"),Tt);
			if (e.IsNum(str_uUy,&val,&idv))
			{
				AfxMessageBox(str); 
				return -1;
			}

			switch (p)
			{
			case 0:		return val; 
			case 1:		return (val2-val1)/(2*h);
			case 2:		return (val2-2*val+val1)/(h*h);
			}
		}
		if (TypeUy==2)
		{
			double val, val1, val2;
			double h=SpUy.dt;//(Tt!=0.0?0.001*Tt:0.001);

			val2=SpUy.GetValue(Tt+h);
			val1=SpUy.GetValue(Tt-h);
			val=SpUy.GetValue(Tt);

			switch (p)
			{
			case 0:		return val; 
			case 1:		return (val2-val1)/(2*h);
			case 2:		return (val2-2*val+val1)/(h*h);
			}
		}
	}
	else
	{
		switch (p)
		{
		case 0:		return Uy; 
		case 1:		return Uyp;
		case 2:		return 0;
		}
	}
	return 0;
}

double CKnot::GetUa(int p/*=0*/)
{
	if (p)	return Uap;
	else	return Ua;
}

CString CKnot::GetStrUx(int p/*=0*/)
{
	if (p)	return str_Uxp;
	else	return str_Ux;
}

CString CKnot::GetStrUy(int p/*=0*/)
{
	if (p)	return str_Uyp;
	else	return str_Uy;
}

CString CKnot::GetStrUa(int p/*=0*/)
{
	if (p)	return str_Uap;
	else	return str_Ua;
}

double CKnot::SetStrUx(CString str, int p/*=0*/)
{
	CExpression e;
	double val;

	if (!e.IsNum(str,&val))
	{
		if (p) 
		{
			str_Uxp=str;
			Uxp=val;
		}
		else 
		{
			str_Ux=str;
			Ux=val;
		}
		return val;
	}
	return -1;
}

double CKnot::SetStrUy(CString str, int p/*=0*/)
{
	CExpression e;
	double val;

	if (!e.IsNum(str,&val))
	{
		if (p) 
		{
			str_Uyp=str;
			Uyp=val;
		}
		else 
		{
			str_Uy=str;
			Uy=val;
		}
		return val;
	}
	return -1;
}

double CKnot::SetStrUa(CString str, int p/*=0*/)
{
	CExpression e;
	double val;

	if (!e.IsNum(str,&val))
	{
		if (p) 
		{
			str_Uap=str;
			Uap=val;
		}
		else 
		{
			str_Ua=str;
			Ua=val;
		}
		return val;
	}
	return -1;
}

void CKnot::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << GetStrX();
		ar << GetStrY();
		ar << FixedType;
		ar << ConnectType;
		//пишем начальные условия (перемещения)
		ar << GetStrUx();
		ar << GetStrUy();
		ar << GetStrUa();
		//пишем начальные условия (скорости)
		ar << GetStrUx(1);
		ar << GetStrUy(1);
		ar << GetStrUa(1);

		//Силовое Возмущение
		ar << Ax << Wx << Fix << TypePx;
		ar << Ay << Wy << Fiy << TypePy;
		ar << str_Ax << str_Wx << str_Fix << str_Px << PxEnable;
		ar << str_Ay << str_Wy << str_Fiy << str_Py << PyEnable;
		SpPx.Serialize(ar);
		SpPy.Serialize(ar);

		//Кинематическое возмущение
		ar << uAx << uWx << uFix << TypeUx;
		ar << uAy << uWy << uFiy << TypeUy;
		ar << str_uAx << str_uWx << str_uFix << str_uUx << UxEnable;
		ar << str_uAy << str_uWy << str_uFiy << str_uUy << UyEnable;
		SpUx.Serialize(ar);
		SpUy.Serialize(ar);
		//Параметры вывода графиков
		ParamTime.Serialize(ar);
	}
	else
	{	// loading code
		CString strknx,strkny;
		ar >> strknx >> strkny;
		SetCoord(strknx, strkny);

		Num=0;
		ar >> FixedType;
		ar >> ConnectType;

		CString Ux,Uy,Ua;
		//читаем начальные условия (перемещения)
		ar >> Ux >> Uy >> Ua;
		SetStrUx(Ux);	
		SetStrUy(Uy);	
		SetStrUa(Ua);
		//читаем начальные условия (скорости)
		ar >> Ux >> Uy >> Ua;
		SetStrUx(Ux,1);	
		SetStrUy(Uy,1);	
		SetStrUa(Ua,1);

		//Силовое Возмущение
		ar >> Ax >> Wx >> Fix >> TypePx;
		ar >> Ay >> Wy >> Fiy >> TypePy;
		ar >> str_Ax >> str_Wx >> str_Fix >> str_Px >> PxEnable;
		ar >> str_Ay >> str_Wy >> str_Fiy >> str_Py >> PyEnable;
		SpPx.Serialize(ar);
		SpPy.Serialize(ar);

		//Кинематическое возмущение
		ar >> uAx >> uWx >> uFix >> TypeUx;
		ar >> uAy >> uWy >> uFiy >> TypeUy;
		ar >> str_uAx >> str_uWx >> str_uFix >> str_uUx >> UxEnable;
		ar >> str_uAy >> str_uWy >> str_uFiy >> str_uUy >> UyEnable;
		SpUx.Serialize(ar);
		SpUy.Serialize(ar);

		//Параметры вывода графиков
		ParamTime.Serialize(ar);
	}
}

int CKnot::SetFixedKnot()
{
	switch (FixedType)
	{
	case 0: break;
	case 1: {nYRez=-1; break;}
	case 2: {nXRez=-1; break;}
	case 3: {nXRez=-1; nYRez=-1; break;}
	case 4: {nXRez=-1; nYRez=-1; for(int i=0;i<CntAngle;i++) nARez[i]=-1; break;}
	case 5:	{for(int i=0;i<CntAngle;i++) nARez[i]=-1; break;}
	};
	return 0;
}

int CKnot::SetMatrmP(CMatr & mP, CMatr & RezY1, CMatr & RezY2, int i, double Tt, CMatr & mUM, CMatr & mUD, CMatr & mUC)
{
	if (nXRez>=0)	mP[nXRez][0]+=GetPx(RezY1[nXRez][i], RezY2[nXRez][i], Tt);
	if (nYRez>=0)	mP[nYRez][0]+=GetPy(RezY1[nYRez][i], RezY2[nYRez][i], Tt);

	if ( (UxEnable)&&(nXRez>=0) )
	{
		for (int i=0;i<mP.SizeY;i++)
/*			mP[i][0]+=	GetUx(Tt,0)*mUC[i][nXRez]+
						GetUx(Tt,1)*mUD[i][nXRez]+
						GetUx(Tt,2)*mUM[i][nXRez];*/
			mP[i][0]-=	GetUx(Tt,0)*mUC[i][nXU]+
						GetUx(Tt,1)*mUD[i][nXU];/*+
						GetUx(Tt,2)*mUM[i][nXU];*/
	}
	if ( (UyEnable)&&(nYRez>=0) )
	{
		for (int i=0;i<mP.SizeY;i++)
/*			mP[i][0]+=	-GetUy(Tt,0)*mUC[i][nYRez]+
						GetUy(Tt,1)*mUD[i][nYRez];*/
			mP[i][0]-=	GetUy(Tt,0)*mUC[i][nYU]+
						GetUy(Tt,1)*mUD[i][nYU];/*+
						GetUy(Tt,2)*mUM[i][nYU];*/
	}
	return 0;
}

void CKnot::Init()
{
	SetStrUx("0");	SetStrUx("0",1);
	SetStrUy("0");	SetStrUy("0",1);
	SetStrUa("0");	SetStrUa("0",1);

	//Силовое возмущение
	str_Ax=_T("0");	str_Wx=_T("0"); str_Fix=_T("0"); str_Px=_T("0"); TypePx=0; PxEnable=false;
	str_Ay=_T("0");	str_Wy=_T("0"); str_Fiy=_T("0"); str_Py=_T("0"); TypePy=0; PyEnable=false;

	//Кинематическое возмущение
	str_uAx=_T("0");	str_uWx=_T("0"); str_uFix=_T("0"); str_uUx=_T("0"); TypeUx=0; UxEnable=false;
	str_uAy=_T("0");	str_uWy=_T("0"); str_uFiy=_T("0"); str_uUy=_T("0"); TypeUy=0; UyEnable=false;

	SelectMode=OldMode=0;
	FixedType=0;
	Num=0;
	ConnectType=0;
	CntAngle=10;

	nXRez=-1;	MoveX=0;
	nYRez=-1;	MoveY=0;
	for (int i=0;i<CntAngle;i++) {	nARez[i]=-1;	MoveA[i]=0;	}
}

int CKnot::SetMatrmP(CMatr & mP, double Tt)
{
	if ( (UxEnable)&&(nXRez>=0) )
		mP[nXRez][0]=GetUx(Tt);

	if ( (UyEnable)&&(nYRez>=0) )
			mP[nYRez][0]=GetUy(Tt);
	
	return 0;
}


double CKnot::GetPx(double x, double x1, double Tt)
{
	if (!PxEnable) return 0;
	if (TypePx==0) return Ax*sin(Wx*Tt+Fix);
	if (TypePx==1)
	{
		CExpression e;
		CIDValuesMap idv;
		idv.SetAt(_T("t"),Tt);
		double val=0;
		idv.SetAt(_T("x") ,x);
		idv.SetAt(_T("x1"),x1);
		if (e.IsNum(str_Px,&val,&idv))	return 0;
		return val;
	}
	if (TypePx==2)	return SpPx.GetValue(Tt);
	return 0;
}

double CKnot::GetPy(double x, double x1, double Tt)
{
	if (!PyEnable) return 0;
	if (TypePy==0) return Ay*sin(Wy*Tt+Fiy);
	if (TypePy==1)
	{
		CExpression e;
		CIDValuesMap idv;
		idv.SetAt(_T("t"),Tt);
		double val=0;
		idv.SetAt(_T("x") ,x);
		idv.SetAt(_T("x1"),x1);
		if (e.IsNum(str_Py,&val,&idv))	return 0;
		return val;
	}
	if (TypePy==2)	return SpPy.GetValue(Tt);
	return 0;
}

int CKnot::BeginIntegr(double T)
{
	int ret=0;
	if (TypePx==2) ret+=SpPx.BeginIntegr(T);
	if (TypePy==2) ret+=SpPy.BeginIntegr(T);
	if (TypeUx==2) ret+=SpUx.BeginIntegr(T);
	if (TypeUy==2) ret+=SpUy.BeginIntegr(T);
	return ret;
}

void CKnot::EndIntegr()
{
	if (TypePx==2) SpPx.EndIntegr();
	if (TypePy==2) SpPy.EndIntegr();
	if (TypeUx==2) SpUx.EndIntegr();
	if (TypeUy==2) SpUy.EndIntegr();
}

void CKnot::DrawFreeNums( CDC *pDC, POINT &point, CParamView *pParamView )
{
	CPen pen1( PS_SOLID|PS_GEOMETRIC, 1, RGB(0,0,0) );
	CPen *pOldpen = static_cast<CPen*>(pDC->SelectObject(&pen1));
	CFont *pOldFont = static_cast<CFont*>(pDC->SelectObject(&(pParamView->m_fntKnot)));
	COLORREF oldClr = pDC->SetTextColor( RGB(0,0,0) );
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);

	const int len1 = 10;
	const int len2 = 5;
	const int len3 = 20;

	CString num;
	if( nXRez >= 0 )
	{
		//стрелка вправо
		pDC->MoveTo( point.x-len1,		point.y-len1 );
		pDC->LineTo( point.x+len1,		point.y-len1 );
		pDC->LineTo( point.x+len1-len2,	point.y-len1-len2 );
		pDC->MoveTo( point.x+len1,		point.y-len1 );
		pDC->LineTo( point.x+len1-len2,	point.y-len1+len2 );

		num.Format("%d", nXRez );
		pDC->TextOut( point.x+len1, point.y-len1, num );
		num.Empty();
	}
	if( nYRez >= 0 )
	{
		//стрелка вниз
		pDC->MoveTo( point.x-len1,		point.y-len1 );
		pDC->LineTo( point.x-len1,		point.y+len1 );
		pDC->LineTo( point.x-len1-len2,	point.y+len1-len2 );
		pDC->MoveTo( point.x-len1,		point.y+len1 );
		pDC->LineTo( point.x-len1+len2,	point.y+len1-len2 );

		num.Format("%d", nYRez );
		pDC->TextOut( point.x-len1, point.y+len1, num );
		num.Empty();
	}
	for( int i = 0; i < CntAngle; i++ )
	{
		if( nARez[i] >= 0 )
		{
			CString tmp;
			tmp.Format("%d,", nARez[i] );
			num += tmp;
		}
	}
	if( !num.IsEmpty() )
	{
		num = num.Left( num.GetLength() - 1 );
		//круглая стрелка
		int tmp = 5;
		pDC->Arc(	point.x-len3, point.y-len3,
					point.x+len3, point.y+len3,
					point.x, point.y-len3-tmp,
					point.x-len3-tmp, point.y );
		pDC->MoveTo( point.x,		point.y-len3 );
		pDC->LineTo( point.x-len2,	point.y-len3-len2 );
		pDC->MoveTo( point.x,		point.y-len3 );
		pDC->LineTo( point.x-len2,	point.y-len3+len2 );

		UINT oldAlign = pDC->SetTextAlign( TA_LEFT|TA_BOTTOM );
		pDC->TextOut( point.x, point.y-len3, num );
		pDC->SetTextAlign( oldAlign );
		num.Empty();
	}
	pDC->SetBkMode(oldBkMode);
	pDC->SetTextColor(oldClr);
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldpen);
}

void CKnot::DrawPower(CDC * pDC, POINT & point, CParamView * pParamView)
{
	CPen pen1(PS_SOLID|PS_GEOMETRIC,2,RGB(0,1750,0));	
	CPen pen2(PS_SOLID|PS_GEOMETRIC,2,RGB(255,0,0));	
	CPen *pOldpen=(CPen*)pDC->SelectObject(&pen1);

	const int len1=5;
	const int len2=12;
	const int len3=3;
	const int len4=2;

	if (PxEnable) 
	{
		//pDC->SelectObject(&pen1);
		pDC->MoveTo(point.x-len1,		point.y);
		pDC->LineTo(point.x-len1-len2,	point.y);
		pDC->MoveTo(point.x-len1,		point.y);
		pDC->LineTo(point.x-len1-len3,	point.y-len4);
		pDC->MoveTo(point.x-len1,		point.y);
		pDC->LineTo(point.x-len1-len3,	point.y+len4);
	}
	if (PyEnable) 
	{
		//pDC->SelectObject(&pen1);
		pDC->MoveTo(point.x,		point.y-len1);
		pDC->LineTo(point.x,		point.y-len1-len2);
		pDC->MoveTo(point.x,		point.y-len1);
		pDC->LineTo(point.x-len4,	point.y-len1-len3);
		pDC->MoveTo(point.x,		point.y-len1);
		pDC->LineTo(point.x+len4,	point.y-len1-len3);
	}
	if (UxEnable) 
	{
		pDC->SelectObject(&pen2);
		pDC->MoveTo(point.x-len1,		point.y);
		pDC->LineTo(point.x-len1-len2,	point.y);
		pDC->MoveTo(point.x-len1,		point.y);
		pDC->LineTo(point.x-len1-len3,	point.y-len4);
		pDC->MoveTo(point.x-len1,		point.y);
		pDC->LineTo(point.x-len1-len3,	point.y+len4);
	}
	if (UyEnable) 
	{
		pDC->SelectObject(&pen2);
		pDC->MoveTo(point.x,		point.y-len1);
		pDC->LineTo(point.x,		point.y-len1-len2);
		pDC->MoveTo(point.x,		point.y-len1);
		pDC->LineTo(point.x-len4,	point.y-len1-len3);
		pDC->MoveTo(point.x,		point.y-len1);
		pDC->LineTo(point.x+len4,	point.y-len1-len3);
	}
	pDC->SelectObject(pOldpen);
}

int CKnot::SetKinematicPos(CMatr & matr_RezY1, CMatr & matr_RezY2, int i, double Tt)
{
	if (UxEnable) 
	{
		matr_RezY1[nXRez][i]=GetUx(Tt);
		matr_RezY2[nXRez][i]=GetUx(Tt,1);
	}
	if (UyEnable) 
	{
		matr_RezY1[nYRez][i]=GetUy(Tt);
		matr_RezY2[nYRez][i]=GetUy(Tt,1);
	}
	return 0;
}

void CKnot::SetCommonProperties( CKnot *pKnot )
{
	str_Ux = pKnot->str_Ux;
	str_Uy = pKnot->str_Uy;
	str_Ua = pKnot->str_Ua;
	str_Uxp = pKnot->str_Uxp;
	str_Uyp = pKnot->str_Uyp;
	str_Uap = pKnot->str_Uap;
	Ux = pKnot->Ux;
	Uy = pKnot->Uy;
	Ua = pKnot->Ua;
	Uxp = pKnot->Uxp;
	Uyp = pKnot->Uyp;
	Uap = pKnot->Uap;

	str_Ax = pKnot->str_Ax;
	str_Wx = pKnot->str_Wx;
	str_Fix = pKnot->str_Fix;
	str_Px = pKnot->str_Px;
	str_Ay = str_Ay;
	str_Wy = pKnot->str_Wy;
	str_Fiy = pKnot->str_Fiy;
	str_Py = pKnot->str_Py;
	Ax = pKnot->Ax;
	Wx = pKnot->Wx;
	Fix = pKnot->Fix;
	Ay = pKnot->Ay;
	Wy = pKnot->Wy;
	Fiy = Fiy;

	SpPx.TypeSpectr = pKnot->SpPx.TypeSpectr;
	SpPx.TypeInit = pKnot->SpPx.TypeInit;
	SpPy.TypeSpectr = pKnot->SpPy.TypeSpectr;
	SpPy.TypeInit = pKnot->SpPy.TypeInit;
	SpUx.TypeSpectr = pKnot->SpUx.TypeSpectr;
	SpUx.TypeInit = pKnot->SpUx.TypeInit;
	SpUy.TypeSpectr = pKnot->SpUy.TypeSpectr;
	SpUy.TypeInit = pKnot->SpUy.TypeInit;
	for( int i = 0; i < 20; i++ )
	{
		SpPx.strEdit[i] = pKnot->SpPx.strEdit[i];
		SpPx.param[i] = pKnot->SpPx.param[i];
		SpPy.strEdit[i] = pKnot->SpPy.strEdit[i];
		SpPy.param[i] = pKnot->SpPy.param[i];
		SpUx.strEdit[i] = pKnot->SpUx.strEdit[i];
		SpUx.param[i] = pKnot->SpUx.param[i];
		SpUy.strEdit[i] = pKnot->SpUy.strEdit[i];
		SpUy.param[i] = pKnot->SpUy.param[i];
	}
	//Произвольное, гармоническое или случайное возмущение
	TypePx = pKnot->TypePx;
	TypePy = pKnot->TypePy;
	//Флаг наличия возмущения
	PxEnable = pKnot->PxEnable;
	PyEnable = pKnot->PyEnable;

	//КИНЕМАТИЧЕСКОЕ ВОЗМУЩЕНИЕ (амплитуда, частота, фаза, произвольное возмущение)
	str_uAx = pKnot->str_uAx;
	str_uWx = pKnot->str_uWx;
	str_uFix = pKnot->str_uFix;
	str_uUx = pKnot->str_uUx;
	str_uAy = pKnot->str_uAy;
	str_uWy = pKnot->str_uWy;
	str_uFiy = pKnot->str_uFiy;
	str_uUy = pKnot->str_uUy;
	uAx = pKnot->uAx;
	uWx = pKnot->uWx;
	uFix = pKnot->uFix;
	uAy = pKnot->uAy;
	uWy = pKnot->uWy;
	uFiy = pKnot->uFiy;
	//Произвольное, гармоническое или случайное возмущение
	TypeUx = pKnot->TypeUx;
	TypeUy = pKnot->TypeUy;
	//Флаг наличия возмущения
	UxEnable = pKnot->UxEnable;
	UyEnable = pKnot->UyEnable;
	//Тип закрепления в узле
	FixedType = pKnot->FixedType;
	//Тип соединения в узле (жёстко=0/шарнирно)
	ConnectType = pKnot->ConnectType;
}
