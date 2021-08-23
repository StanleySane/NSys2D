// Knot.cpp: implementation of the CKnot class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "Knot.h"

#include "StdAfxMy.h"

#include "ShemeDoc.h"
#include "MovieView.h"
#include "ShemeVarsTable.h"
#include "Sheme.h"
#include "KnotPropertySheet.h"

#include<algorithm>
#include<cmath>

using namespace std;
	
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKnot::CKnot( const CKnot &knot ):CObjectSheme(knot)
{
	InitBy(knot);
}

CKnot::CKnot( CSheme *p )
:CObjectSheme(p), SpPx(p), SpPy(p), SpUx(p), SpUy(p)
{
	SetCoord( 0.0, 0.0 );
	Init();
}

CKnot::CKnot( double x, double y, CSheme *p )
:CObjectSheme(p), SpPx(p), SpPy(p), SpUx(p), SpUy(p)
{
	SetCoord( x, y );
	Init();
}

CKnot::~CKnot()
{
}

double CKnot::GetCoordX( double multmove/*=0*/)
{
	return coord.x+multmove*MoveX;
}

double CKnot::GetCoordY( double multmove/*=0*/)
{
	return coord.y+multmove*MoveY;
}

CCoordD CKnot::GetCoord(double multmove/*=0*/)
{
	return CCoordD(coord.x+multmove*MoveX, coord.y+multmove*MoveY);
}

int CKnot::SetCoord( double x, double y )
{
	coord.x = x;
	coord.y = y;
	return 1;
}

void CKnot::SetVarState( double x, double v, double a, double t )
{
//ф-ция заполняет переменные таблицы значениями данного узла:
// x - перемещение, v - скорость, a - ускорение, t - время
	if( m_pSheme )
	{
		m_pSheme->m_VarsTable.SetVarValue("x",x);
		m_pSheme->m_VarsTable.SetVarValue("v",v);
		m_pSheme->m_VarsTable.SetVarValue("t",t);
		m_pSheme->m_VarsTable.SetVarValue("a",a);
		m_pSheme->m_VarsTable.SetVarValue("w",0.0);
		m_pSheme->m_VarsTable.SetVarValue("cx",coord.x);
		m_pSheme->m_VarsTable.SetVarValue("cy",coord.y);
		m_pSheme->m_VarsTable.SetVarValue("cx1",coord.x);
		m_pSheme->m_VarsTable.SetVarValue("cy1",coord.y);
		m_pSheme->m_VarsTable.SetVarValue("cx2",coord.x);
		m_pSheme->m_VarsTable.SetVarValue("cy2",coord.y);
	}
}

void CKnot::DrawGL( CShemeDoc *pDoc, int Time )
{
	ASSERT( pDoc->m_pMovieView );

	if( (FixedType == 0)||(!pDoc->m_pMovieView->m_bShowKnots) )
		return;

	glColor3f( 0.0f, 0.0f, 0.0f );

	double x, y;
	if( Time < 0 )
	{
		x = coord.x;
		y = coord.y;
	}
	else
	{
		if( nXRez >= 0 )
			x = pDoc->m_pMovieView->m_Res( nXRez + 1, Time );
		else
		{
			x = coord.x;
		}
		if( nYRez >= 0 )
			y = pDoc->m_pMovieView->m_Res( nYRez + 1, Time );
		else
		{
			y = coord.y;
		}
		/*
		if( nARez[0] >= 0 )
		{
			fi = pDoc->m_pMovieView->m_Res( nARez[0] + 1, Time );
			fi *= 180.0/CNSys2DApp::M_PI;
		}
		*/
	}
	glPushMatrix();
	glTranslatef( x, y, 0.0f );
	GLdouble H = pDoc->m_pMovieView->m_Width/20.0;//характерный размер
	switch( FixedType )
	{
	case 1: 
		{
			//запрещён Y
			int N = 6;//число штрихов
			GLdouble H2 = H/2.0, H3 = H/GLdouble(N), H4 = 1.3*H3;

			glLineWidth( 2 );
			glBegin(GL_LINES);
				glVertex2d( 0.0f, 0.0f );
				glVertex2d( 0.0f, -H );
				glVertex2d( -H2, -H );
				glVertex2d( H2, -H );
			glEnd();

			glLineWidth( 1 );
			glBegin(GL_LINES);
				for( int i = 0; i < N; i++ )
				{
					GLdouble tmp1 = i*H3 - H2;
					glVertex2d( tmp1 + H3, -H );
					glVertex2d( tmp1, -H - H4 );
				}
			glEnd();

			if( pDoc->m_pMovieView->m_pQuad != NULL )
			{
				GLdouble rad = H/7.0;//радиус шарнира
				GLdouble tmp = rad/2.0;
				gluQuadricDrawStyle( pDoc->m_pMovieView->m_pQuad, GLU_FILL );
				gluDisk( pDoc->m_pMovieView->m_pQuad, 0.0f, rad, 10, 2 );
				glColor3f( 1.0f, 1.0f, 1.0f );
				gluDisk( pDoc->m_pMovieView->m_pQuad, 0.0f, tmp, 10, 2 );
				glPushMatrix();
				glTranslated( 0.0f, -H, 0.0f );
				glColor3f( 0.0f, 0.0f, 0.0f );
				gluDisk( pDoc->m_pMovieView->m_pQuad, 0.0f, rad, 10, 2 );
				glColor3f( 1.0f, 1.0f, 1.0f );
				gluDisk( pDoc->m_pMovieView->m_pQuad, 0.0f, tmp, 10, 2 );
				glPopMatrix();
			}
		}	
		break;
	case 2: 
		//запрещён X
		{
			int N = 6;//число штрихов
			GLdouble H2 = H/2.0, H3 = H/GLdouble(N), H4 = 1.3*H3;

			glLineWidth( 2 );
			glBegin(GL_LINES);
				glVertex2d( 0.0f, 0.0f );
				glVertex2d( H, 0.0f );
				glVertex2d( H, -H2 );
				glVertex2d( H, H2 );
			glEnd();

			glLineWidth( 1 );
			glBegin(GL_LINES);
				for( int i = 0; i < N; i++ )
				{
					GLdouble tmp1 = -i*H3 + H2;
					glVertex2d( H, tmp1 - H3 );
					glVertex2d( H + H4, tmp1 );
				}
			glEnd();

			if( pDoc->m_pMovieView->m_pQuad != NULL )
			{
				GLdouble rad = H/7.0;//радиус шарнира
				GLdouble tmp = rad/2.0;
				gluQuadricDrawStyle( pDoc->m_pMovieView->m_pQuad, GLU_FILL );
				gluDisk( pDoc->m_pMovieView->m_pQuad, 0.0f, rad, 10, 2 );
				glColor3f( 1.0f, 1.0f, 1.0f );
				gluDisk( pDoc->m_pMovieView->m_pQuad, 0.0f, tmp, 10, 2 );
				glPushMatrix();
				glTranslated( H, 0.0f, 0.0f );
				glColor3f( 0.0f, 0.0f, 0.0f );
				gluDisk( pDoc->m_pMovieView->m_pQuad, 0.0f, rad, 10, 2 );
				glColor3f( 1.0f, 1.0f, 1.0f );
				gluDisk( pDoc->m_pMovieView->m_pQuad, 0.0f, tmp, 10, 2 );
				glPopMatrix();
			}
		}
		break;
	case 3: 
		//запрещены X,Y разрешён только FI
		{
			int N = 6;//число штрихов
			GLdouble H2 = H/2.0, H3 = H/GLdouble(N), H4 = H/4.0, H5 = 1.3*H3;

			glLineWidth( 2 );
			glBegin(GL_LINES);
				glVertex2d( 0.0f, 0.0f );
				glVertex2d( -H4, -H );
				glVertex2d( 0.0f, 0.0f );
				glVertex2d( H4, -H );
				//горизонтальная
				glVertex2d( -H2, -H );
				glVertex2d( H2, -H );
			glEnd();

			glLineWidth( 1 );
			glBegin(GL_LINES);
				for( int i = 0; i < N; i++ )
				{
					GLdouble tmp1 = i*H3 - H2;
					glVertex2d( tmp1 + H3, -H );
					glVertex2d( tmp1, -H - H5 );
				}
			glEnd();

			if( pDoc->m_pMovieView->m_pQuad != NULL )
			{
				GLdouble rad = H/7.0;//радиус шарнира
				gluQuadricDrawStyle( pDoc->m_pMovieView->m_pQuad, GLU_FILL );
				gluDisk( pDoc->m_pMovieView->m_pQuad, 0.0f, rad, 10, 2 );
				glColor3f( 1.0f, 1.0f, 1.0f );
				gluDisk( pDoc->m_pMovieView->m_pQuad, 0.0f, rad/2.0, 10, 2 );
			}
		}
		break;
	case 4:
		//заделка - все перемещения запрещены
		{
			int N = 6;//число штрихов
			GLdouble H2 = H/2.0, H3 = H/GLdouble(N), H4 = 1.3*H3;
			GLdouble ang;
			if( FriendCoord.GetNorm() > 0.0 )
			{
				ang = (FriendCoord - CCoordD(x,y)).GetAng() - CNSys2DApp::M_PI_2;
				ang *= 180.0/CNSys2DApp::M_PI;
			}
			else	ang = GLdouble(90.0);
			glPushMatrix();
			glRotated( ang, 0.0f, 0.0f, 1.0f );
			glLineWidth( 2 );
			glBegin(GL_LINES);
				//горизонтальная
				glVertex2d( -H2, 0.0f );
				glVertex2d( H2, 0.0f );
			glEnd();

			glLineWidth( 1 );
			glBegin(GL_LINES);
				for( int i = 0; i < N; i++ )
				{
					GLdouble tmp1 = i*H3 - H2;
					glVertex2d( tmp1 + H3, 0.0f );
					glVertex2d( tmp1, -H4 );
				}
			glEnd();
			glPopMatrix();
		}
		break;
	case 5:
		//запрещён только поворот
		{
			GLdouble h = H/7.0, h2 = 3.0*h;
			GLdouble tmp1 = h + h2, tmp2 = -h - h2;

			glLineWidth(1);
			//левый верхний:
			glBegin(GL_LINE_LOOP);
				glVertex2d( -h, h );
				glVertex2d( -h, tmp1 );
				glVertex2d( tmp2, h );
			glEnd();
			//правый верхний:
			glBegin(GL_LINE_LOOP);
				glVertex2d( h, h );
				glVertex2d( h, tmp1 );
				glVertex2d( tmp1, h );
			glEnd();
			//левый нижний:
			glBegin(GL_LINE_LOOP);
				glVertex2d( -h, -h );
				glVertex2d( -h, tmp2 );
				glVertex2d( tmp2, -h );
			glEnd();
			//правый нижний:
			glBegin(GL_LINE_LOOP);
				glVertex2d( h, -h );
				glVertex2d( h, tmp2 );
				glVertex2d( tmp1, -h );
			glEnd();
		}
		break;
	case 6:
		//запрещены Y,FI разрешён только X
		{
			GLdouble h = H/7.0, h2 = 3.0*h;
			GLdouble tmp1 = h + h2, tmp2 = -h - h2;

			glLineWidth(1);
			//левый верхний:
			glBegin(GL_LINE_LOOP);
				glVertex2d( -h, h );
				glVertex2d( -h, tmp1 );
				glVertex2d( tmp2, h );
			glEnd();
			//правый верхний:
			glBegin(GL_LINE_LOOP);
				glVertex2d( h, h );
				glVertex2d( h, tmp1 );
				glVertex2d( tmp1, h );
			glEnd();
			//левый нижний:
			glBegin(GL_LINE_LOOP);
				glVertex2d( -h, -h );
				glVertex2d( -h, tmp2 );
				glVertex2d( tmp2, -h );
			glEnd();
			//правый нижний:
			glBegin(GL_LINE_LOOP);
				glVertex2d( h, -h );
				glVertex2d( h, tmp2 );
				glVertex2d( tmp1, -h );
			glEnd();

			int N = 6;//число штрихов
			GLdouble H2 = H/2.0, H3 = H/GLdouble(N), H4 = 1.3*H3;

			glLineWidth( 2 );
			glBegin(GL_LINES);
				glVertex2d( 0.0f, -h );
				glVertex2d( 0.0f, -H );
				glVertex2d( -H2, -H );
				glVertex2d( H2, -H );
			glEnd();

			glLineWidth( 1 );
			glBegin(GL_LINES);
				for( int i = 0; i < N; i++ )
				{
					GLdouble tmp1 = i*H3 - H2;
					glVertex2d( tmp1 + H3, -H );
					glVertex2d( tmp1, -H - H4 );
				}
			glEnd();

			if( pDoc->m_pMovieView->m_pQuad != NULL )
			{
				GLdouble rad = H/7.0;//радиус шарнира
				gluQuadricDrawStyle( pDoc->m_pMovieView->m_pQuad, GLU_FILL );
				glPushMatrix();
				glTranslated( 0.0f, -H, 0.0f );
				glColor3f( 0.0f, 0.0f, 0.0f );
				gluDisk( pDoc->m_pMovieView->m_pQuad, 0.0f, rad, 10, 2 );
				glColor3f( 1.0f, 1.0f, 1.0f );
				gluDisk( pDoc->m_pMovieView->m_pQuad, 0.0f, rad/2.0, 10, 2 );
				glPopMatrix();
			}
		}
		break;
	case 7:
		//запрещены X,FI разрешён только Y
		{
			GLdouble h = H/7.0, h2 = 3.0*h;
			GLdouble tmp1 = h + h2, tmp2 = -h - h2;

			glLineWidth(1);
			//левый верхний:
			glBegin(GL_LINE_LOOP);
				glVertex2d( -h, h );
				glVertex2d( -h, tmp1 );
				glVertex2d( tmp2, h );
			glEnd();
			//правый верхний:
			glBegin(GL_LINE_LOOP);
				glVertex2d( h, h );
				glVertex2d( h, tmp1 );
				glVertex2d( tmp1, h );
			glEnd();
			//левый нижний:
			glBegin(GL_LINE_LOOP);
				glVertex2d( -h, -h );
				glVertex2d( -h, tmp2 );
				glVertex2d( tmp2, -h );
			glEnd();
			//правый нижний:
			glBegin(GL_LINE_LOOP);
				glVertex2d( h, -h );
				glVertex2d( h, tmp2 );
				glVertex2d( tmp1, -h );
			glEnd();

			int N = 6;//число штрихов
			GLdouble H2 = H/2.0, H3 = H/GLdouble(N), H4 = 1.3*H3;

			glLineWidth( 2 );
			glBegin(GL_LINES);
				glVertex2d( h, 0.0f );
				glVertex2d( H, 0.0f );
				glVertex2d( H, -H2 );
				glVertex2d( H, H2 );
			glEnd();

			glLineWidth( 1 );
			glBegin(GL_LINES);
				for( int i = 0; i < N; i++ )
				{
					GLdouble tmp1 = -i*H3 + H2;
					glVertex2d( H, tmp1 - H3 );
					glVertex2d( H + H4, tmp1 );
				}
			glEnd();

			if( pDoc->m_pMovieView->m_pQuad != NULL )
			{
				GLdouble rad = H/7.0;//радиус шарнира
				gluQuadricDrawStyle( pDoc->m_pMovieView->m_pQuad, GLU_FILL );
				glPushMatrix();
				glTranslated( H, 0.0f, 0.0f );
				glColor3f( 0.0f, 0.0f, 0.0f );
				gluDisk( pDoc->m_pMovieView->m_pQuad, 0.0f, rad, 10, 2 );
				glColor3f( 1.0f, 1.0f, 1.0f );
				gluDisk( pDoc->m_pMovieView->m_pQuad, 0.0f, rad/2.0, 10, 2 );
				glPopMatrix();
			}
		}
		break;
	default:
		ASSERT(FALSE);
	}
	glPopMatrix();
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

CString CKnot::GetFullName()
{
	CString name = GetName();
	CString str;
	str.Format(" Ux=%s,Uy=%s,Ua=%s,Ux'=%s,Uy'=%s,Ua'=%s", 
		m_Ux.GetExpr().c_str(), m_Uy.GetExpr().c_str(), m_Ua.GetExpr().c_str(),
		m_Uxp.GetExpr().c_str(), m_Uyp.GetExpr().c_str(), m_Uap.GetExpr().c_str() );
	name += str;
	if( PxEnable )
	{
		str.Empty();
		switch( TypePx )
		{
		case 0:
			str.Format(" Px=%.16g*sin(%.16g*t+%.16g)", Ax, Wx, Fix );
			break;
		case 1:
			str.Format(" Px=%s", m_Px.GetExpr().c_str() );
			break;
		case 2:
			str = _T(" Px-случайное");
			break;
		default:
			ASSERT(FALSE);
		}
		name += str;
	}
	if( PyEnable )
	{
		str.Empty();
		switch( TypePy )
		{
		case 0:
			str.Format(" Py=%.16g*sin(%.16g*t+%.16g)", Ay, Wy, Fiy );
			break;
		case 1:
			str.Format(" Py=%s", m_Py.GetExpr().c_str() );
			break;
		case 2:
			str = _T(" Py-случайное");
			break;
		default:
			ASSERT(FALSE);
		}
		name += str;
	}
	if( UxEnable )
	{
		str.Empty();
		switch( TypeUx )
		{
		case 0:
			str.Format(" uUx=%.16g*sin(%.16g*t+%.16g)", uAx, uWx, uFix );
			break;
		case 1:
			str.Format(" uUx=%s", m_uUx.GetExpr().c_str() );
			break;
		case 2:
			str = _T(" uUx-случайное");
			break;
		default:
			ASSERT(FALSE);
		}
		name += str;
	}
	if( UyEnable )
	{
		str.Empty();
		switch( TypeUy )
		{
		case 0:
			str.Format(" uUy=%.16g*sin(%.16g*t+%.16g)", uAy, uWy, uFiy );
			break;
		case 1:
			str.Format(" uUy=%s", m_uUy.GetExpr().c_str() );
			break;
		case 2:
			str = _T(" uUy-случайное");
			break;
		default:
			ASSERT(FALSE);
		}
		name += str;
	}
	return name;
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
			//запрещён Y
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
			//запрещён X
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
			//запрещены X,Y разрешён только FI
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
		//заделка - все перемещения запрещены
		{
			double ang=-CNSys2DApp::M_PI_2;
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

			double sa = sin(ang), ca = cos(ang);
			dc->MoveTo( int(point.x+10*sa), int(point.y-10*ca));
			dc->LineTo( int(point.x-10*sa), int(point.y+10*ca));

			dc->SelectObject(&pen1);
			
			for(i=0;i<7;i++)
			{
				CPoint p=CPoint(-8+3*i,0);
				CPoint p2=CPoint(int(-p.y*sa+p.x*ca),int(p.y*ca+p.x*sa) );
				dc->MoveTo(point.x-p2.y,point.y+p2.x);
				p=CPoint(-8+3*i-3,4);
				p2=CPoint(int(-p.y*sa+p.x*ca),int(p.y*ca+p.x*sa) );
				dc->LineTo(point.x-p2.y,point.y+p2.x);
			}
		}
		break;
	case 5:
		{
			//запрещён только поворот
			dc->SelectObject( &pen1 );

			int tmp = 3*rad, rad2 = rad;
			CPoint pl[3] = { CPoint( point.x-rad2, point.y-rad2 ),
							CPoint( point.x-rad2, point.y-tmp ),
							CPoint( point.x-tmp, point.y-rad2 ) };
			dc->Polygon( pl, 3 );
			pl[0] = CPoint( point.x+rad2, point.y-rad2 );
			pl[1] = CPoint( point.x+rad2, point.y-tmp );
			pl[2] = CPoint( point.x+tmp, point.y-rad2 );
			dc->Polygon( pl, 3 );
			pl[0] = CPoint( point.x-rad2, point.y+rad2 );
			pl[1] = CPoint( point.x-rad2, point.y+tmp );
			pl[2] = CPoint( point.x-tmp, point.y+rad2 );
			dc->Polygon( pl, 3 );
			pl[0] = CPoint( point.x+rad2, point.y+rad2 );
			pl[1] = CPoint( point.x+rad2, point.y+tmp );
			pl[2] = CPoint( point.x+tmp, point.y+rad2 );
			dc->Polygon( pl, 3 );
		}
		break;
	case 6:
			//запрещены Y,FI разрешён только X
		{
			dc->MoveTo(point.x-8,point.y+12);
			dc->LineTo(point.x+8,point.y+12);

			CPen pen4( PS_SOLID|PS_GEOMETRIC, 3, RGB(0,0,0) );
			dc->SelectObject( &pen4 );

			dc->MoveTo(point.x,point.y);
			dc->LineTo(point.x,point.y+12);			

			dc->SelectObject(&pen1);
			
			for(i=0;i<6;i++)
			{
				dc->MoveTo(point.x-7+3*i,point.y+12);
				dc->LineTo(point.x-7+3*i-3,point.y+16);
			}
			
			int tmp = 3*rad, rad2 = rad;
			CPoint pl[3] = { CPoint( point.x-rad2, point.y-rad2 ),
							CPoint( point.x-rad2, point.y-tmp ),
							CPoint( point.x-tmp, point.y-rad2 ) };
			dc->Polygon( pl, 3 );
			pl[0] = CPoint( point.x+rad2, point.y-rad2 );
			pl[1] = CPoint( point.x+rad2, point.y-tmp );
			pl[2] = CPoint( point.x+tmp, point.y-rad2 );
			dc->Polygon( pl, 3 );
			pl[0] = CPoint( point.x-rad2, point.y+rad2 );
			pl[1] = CPoint( point.x-rad2, point.y+tmp );
			pl[2] = CPoint( point.x-tmp, point.y+rad2 );
			dc->Polygon( pl, 3 );
			pl[0] = CPoint( point.x+rad2, point.y+rad2 );
			pl[1] = CPoint( point.x+rad2, point.y+tmp );
			pl[2] = CPoint( point.x+tmp, point.y+rad2 );
			dc->Polygon( pl, 3 );

			dc->Ellipse(point.x-rad,point.y+12-rad,	
				point.x+rad,point.y+12+rad);

		}
		break;
	case 7:
			//запрещены X,FI разрешён только Y
		{
			dc->MoveTo(point.x+12,point.y-8);
			dc->LineTo(point.x+12,point.y+8);

			CPen pen4( PS_SOLID|PS_GEOMETRIC, 3, RGB(0,0,0) );
			dc->SelectObject( &pen4 );
			
			dc->MoveTo(point.x,point.y);
			dc->LineTo(point.x+12,point.y);			

			dc->SelectObject(&pen1);
			
			for(i=0;i<6;i++)
			{
				dc->MoveTo(point.x+12,point.y-7+3*i);
				dc->LineTo(point.x+16,point.y-7+3*i-3);
			}
			
			int tmp = 3*rad, rad2 = rad;
			CPoint pl[3] = { CPoint( point.x-rad2, point.y-rad2 ),
							CPoint( point.x-rad2, point.y-tmp ),
							CPoint( point.x-tmp, point.y-rad2 ) };
			dc->Polygon( pl, 3 );
			pl[0] = CPoint( point.x+rad2, point.y-rad2 );
			pl[1] = CPoint( point.x+rad2, point.y-tmp );
			pl[2] = CPoint( point.x+tmp, point.y-rad2 );
			dc->Polygon( pl, 3 );
			pl[0] = CPoint( point.x-rad2, point.y+rad2 );
			pl[1] = CPoint( point.x-rad2, point.y+tmp );
			pl[2] = CPoint( point.x-tmp, point.y+rad2 );
			dc->Polygon( pl, 3 );
			pl[0] = CPoint( point.x+rad2, point.y+rad2 );
			pl[1] = CPoint( point.x+rad2, point.y+tmp );
			pl[2] = CPoint( point.x+tmp, point.y+rad2 );
			dc->Polygon( pl, 3 );

			dc->Ellipse(point.x+12-rad,point.y-rad,
				point.x+12+rad,point.y+rad);

			//dc->Ellipse(point.x-rad,point.y-rad,point.x+rad,point.y+rad);
		}
		break;
	default:
		ASSERT(FALSE);
	}
	dc->SelectObject(pOldbrush);
	dc->SelectObject(pOldpen);
}

void CKnot::InitBy( const CKnot &knot )
{
//	m_pSheme = knot.m_pSheme;

	coord=knot.coord;
	Num=knot.Num;
	OldMode=0;
	SelectMode=0;

	FixedType=knot.FixedType;

	m_Ux.InitBy( knot.m_Ux );
	m_Uy.InitBy( knot.m_Uy );
	m_Ua.InitBy( knot.m_Ua );
	m_Uxp.InitBy( knot.m_Uxp );
	m_Uyp.InitBy( knot.m_Uyp );
	m_Uap.InitBy( knot.m_Uap );

	//Силовое Возмущение
	Ax=knot.Ax;
	Wx=knot.Wx;
	Fix=knot.Fix;
	TypePx=knot.TypePx;
	m_Px.InitBy( knot.m_Px );
	PxEnable=knot.PxEnable;
	SpPx=knot.SpPx;

	Ay=knot.Ay;
	Wy=knot.Wy;
	Fiy=knot.Fiy;
	TypePy=knot.TypePy;
	m_Py.InitBy( knot.m_Py );
	PyEnable=knot.PyEnable;
	SpPy=knot.SpPy;

	//Кинематическое возмущение
	uAx=knot.uAx;
	uWx=knot.uWx;
	uFix=knot.uFix;
	TypeUx=knot.TypeUx;
	m_uUx.InitBy( knot.m_uUx );
	UxEnable=knot.UxEnable;
	SpUx=knot.SpUx;

	uAy=knot.uAy;
	uWy=knot.uWy;
	uFiy=knot.uFiy;
	TypeUy=knot.TypeUy;
	m_uUy.InitBy( knot.m_uUy );
	UyEnable=knot.UyEnable;
	SpUy=knot.SpUy;
}

CKnot& CKnot::operator =( const CKnot &knot )
{
	if( this != &knot )
		InitBy(knot);
	return *this;
}

double CKnot::GetUx( double x, double v, double a, double Tt, std::string *pMsg, int p/*=0*/)
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
		if( TypeUx == 1 )
		{
			double val, val1, val2;
			double h = (Tt!=0.0?0.001*Tt:0.001);

			SetVarState( x, v, a, Tt+h );
			val2 = m_uUx.GetValue();
			if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
			{
				ShemeExprErr err = m_uUx.GetRunErrorCode();
				if( err != SEE_NOERR )
				{
					(*pMsg) = m_uUx.GetFullErrorMsg(err);
					return -1;
				}
			}
			if( m_pSheme )
			{
				m_pSheme->m_VarsTable.SetVarValue("t",Tt-h);
			}
			val1 = m_uUx.GetValue();
			if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
			{
				ShemeExprErr err = m_uUx.GetRunErrorCode();
				if( err != SEE_NOERR )
				{
					(*pMsg) = m_uUx.GetFullErrorMsg(err);
					return -1;
				}
			}
			if( m_pSheme )
			{
				m_pSheme->m_VarsTable.SetVarValue("t",Tt);
			}
			val = m_uUx.GetValue();
			if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
			{
				ShemeExprErr err = m_uUx.GetRunErrorCode();
				if( err != SEE_NOERR )
				{
					(*pMsg) = m_uUx.GetFullErrorMsg(err);
					return -1;
				}
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

			val2 = SpUx.GetValue(Tt+h);
			val1 = SpUx.GetValue(Tt-h);
			val = SpUx.GetValue(Tt);

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
		if( p == 2 )
			return 0.0;
		SetVarState( x, v, a, Tt );
		switch(p)
		{
		case 0:
			{
				double val = m_Ux.GetValue(); 
				if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
				{
					ShemeExprErr err = m_Ux.GetRunErrorCode();
					if( err != SEE_NOERR )
					{
						(*pMsg) = m_Ux.GetFullErrorMsg(err);
						return -1;
					}
				}
				return val;
			}
		case 1:
			{
				double val = m_Uxp.GetValue();
				if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
				{
					ShemeExprErr err = m_Uxp.GetRunErrorCode();
					if( err != SEE_NOERR )
					{
						(*pMsg) = m_Uxp.GetFullErrorMsg(err);
						return -1;
					}
				}
				return val;
			}
		}
	}
	return 0.0;
}

double CKnot::GetUy( double x, double v, double a, double Tt, std::string *pMsg, int p/*=0*/)
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
			double val, val1, val2;
			double h=(Tt!=0.0?0.001*Tt:0.001);

			SetVarState( x, v, a, Tt+h );
			val2 = m_uUy.GetValue();
			if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
			{
				ShemeExprErr err = m_uUy.GetRunErrorCode();
				if( err != SEE_NOERR )
				{
					(*pMsg) = m_uUy.GetFullErrorMsg(err);
					return -1;
				}
			}
			if( m_pSheme )
			{
				m_pSheme->m_VarsTable.SetVarValue("t",Tt-h);
			}
			val1 = m_uUy.GetValue();
			if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
			{
				ShemeExprErr err = m_uUy.GetRunErrorCode();
				if( err != SEE_NOERR )
				{
					(*pMsg) = m_uUy.GetFullErrorMsg(err);
					return -1;
				}
			}
			if( m_pSheme )
			{
				m_pSheme->m_VarsTable.SetVarValue("t",Tt);
			}
			val = m_uUy.GetValue();
			if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
			{
				ShemeExprErr err = m_uUy.GetRunErrorCode();
				if( err != SEE_NOERR )
				{
					(*pMsg) = m_uUy.GetFullErrorMsg(err);
					return -1;
				}
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
		if( p == 2 )
			return 0.0;
		SetVarState( x, v, a, Tt );
		switch(p)
		{
		case 0:
			{
				double val = m_Uy.GetValue(); 
				if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
				{
					ShemeExprErr err = m_Uy.GetRunErrorCode();
					if( err != SEE_NOERR )
					{
						(*pMsg) = m_Uy.GetFullErrorMsg(err);
						return -1;
					}
				}
				return val;
			}
		case 1:
			{
				double val = m_Uyp.GetValue(); 
				if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
				{
					ShemeExprErr err = m_Uyp.GetRunErrorCode();
					if( err != SEE_NOERR )
					{
						(*pMsg) = m_Uyp.GetFullErrorMsg(err);
						return -1;
					}
				}
				return val;
			}
		}
	}
	return 0.0;
}

double CKnot::GetUa( double x, double v, double a, double t, std::string *pMsg, int p/*=0*/)
{
	if( p == 2 )
		return 0.0;
	SetVarState( x, v, a, t );
	double val = 0.0;
	if( p == 0 )
	{
		val = m_Ua.GetValue();
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
		{
			ShemeExprErr err = m_Ua.GetRunErrorCode();
			if( err != SEE_NOERR )
			{
				(*pMsg) = m_Ua.GetFullErrorMsg(err);
				return -1;
			}
		}
	}
	else
	{
		val = m_Uap.GetValue();
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
		{
			ShemeExprErr err = m_Uap.GetRunErrorCode();
			if( err != SEE_NOERR )
			{
				(*pMsg) = m_Uap.GetFullErrorMsg(err);
				return -1;
			}
		}
	}
	return val;
}

void CKnot::Serialize( CArchive &ar, int _sv )
{
	ShemeVersion sv = static_cast<ShemeVersion>(_sv);
	if (ar.IsStoring())
	{	// storing code
		CString str;
		if( sv <= VER_EQ30 )
		{
			str.Format("%.16g", GetCoordX() );
			ar << str;
			str.Format("%.16g", GetCoordY() );
			ar << str;
		}
		else
		{
			ar << GetCoordX() << GetCoordY();
		}
		ar << FixedType;
		ar << ConnectType;
		//пишем начальные условия (перемещения)
		m_Ux.Serialize(ar);
		m_Uy.Serialize(ar);
		m_Ua.Serialize(ar);
		//пишем начальные условия (скорости)
		m_Uxp.Serialize(ar);
		m_Uyp.Serialize(ar);
		m_Uap.Serialize(ar);

		//Силовое Возмущение
		ar << Ax << Wx << Fix << TypePx;
		ar << Ay << Wy << Fiy << TypePy;
		if( sv <= VER_EQ30 )
		{
			str.Format("%.16g", Ax );
			ar << str;
			str.Format("%.16g", Wx );
			ar << str;
			str.Format("%.16g", Fix );
			ar << str;
		}
		m_Px.Serialize(ar);
		ar << PxEnable;
		if( sv <= VER_EQ30 )
		{
			str.Format("%.16g", Ay );
			ar << str;
			str.Format("%.16g", Wy );
			ar << str;
			str.Format("%.16g", Fiy );
			ar << str;
		}
		m_Py.Serialize(ar);
		ar << PyEnable;

		SpPx.Serialize( ar, _sv );
		SpPy.Serialize( ar, _sv );

		//Кинематическое возмущение
		ar << uAx << uWx << uFix << TypeUx;
		ar << uAy << uWy << uFiy << TypeUy;
		if( sv <= VER_EQ30 )
		{
			str.Format("%.16g", uAx );
			ar << str;
			str.Format("%.16g", uWx );
			ar << str;
			str.Format("%.16g", uFix );
			ar << str;
		}
		m_uUx.Serialize(ar);
		ar << UxEnable;
		if( sv <= VER_EQ30 )
		{
			str.Format("%.16g", uAy );
			ar << str;
			str.Format("%.16g", uWy );
			ar << str;
			str.Format("%.16g", uFiy );
			ar << str;
		}
		m_uUy.Serialize(ar);
		ar << UyEnable;

		SpUx.Serialize( ar, _sv );
		SpUy.Serialize( ar, _sv );
		//Параметры вывода графиков
		ParamTime.Serialize( ar, _sv );
	}
	else
	{	// loading code
		if( sv <= VER_EQ30 )
		{
			CShemeVarsTable *pVT = (m_pSheme)?(&m_pSheme->m_VarsTable):(NULL);
			CShemeExpr se( pVT );
			CString x, y;
			ar >> x >> y;
			se.Reset( x );
			double X = se.GetValue();
			ASSERT( se.GetCompileErrorCode() == SEE_NOERR );
			se.Reset( y );
			double Y = se.GetValue();
			ASSERT( se.GetCompileErrorCode() == SEE_NOERR );
			SetCoord( X, Y );
		}
		else
		{
			double x, y;
			ar >> x >> y;
			SetCoord( x, y );
		}

		Num=0;
		ar >> FixedType;
		ar >> ConnectType;

		//читаем начальные условия (перемещения)
		m_Ux.Serialize(ar);
		m_Uy.Serialize(ar);
		m_Ua.Serialize(ar);
		//читаем начальные условия (скорости)
		m_Uxp.Serialize(ar);
		m_Uyp.Serialize(ar);
		m_Uap.Serialize(ar);

		//Силовое Возмущение
		ar >> Ax >> Wx >> Fix >> TypePx;
		ar >> Ay >> Wy >> Fiy >> TypePy;
		if( sv <= VER_EQ30 )
		{
			CString str;
			ar >> str;//str_Ax
			ar >> str;//str_Wx
			ar >> str;//str_Fix;
		}
		m_Px.Serialize(ar);
		ar >> PxEnable;
		if( sv <= VER_EQ30 )
		{
			CString str;
			ar >> str;//str_Ay
			ar >> str;//str_Wy
			ar >> str;//str_Fiy;
		}
		m_Py.Serialize(ar);
		ar >> PyEnable;

		SpPx.Serialize( ar, _sv );
		SpPy.Serialize( ar, _sv );

		//Кинематическое возмущение
		ar >> uAx >> uWx >> uFix >> TypeUx;
		ar >> uAy >> uWy >> uFiy >> TypeUy;
		if( sv <= VER_EQ30 )
		{
			CString str;
			ar >> str;//str_uAx
			ar >> str;//str_uWx
			ar >> str;//str_uFix;
		}
		m_uUx.Serialize(ar);
		ar >> UxEnable;
		if( sv <= VER_EQ30 )
		{
			CString str;
			ar >> str;//str_uAy
			ar >> str;//str_uWy
			ar >> str;//str_uFiy;
		}
		m_uUy.Serialize(ar);
		ar >> UyEnable;

		SpUx.Serialize( ar, _sv );
		SpUy.Serialize( ar, _sv );

		//Параметры вывода графиков
		ParamTime.Serialize( ar, _sv );
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
	case 6:	{nYRez=-1; for(int i=0;i<CntAngle;i++) nARez[i]=-1; break;}
	case 7:	{nXRez=-1; for(int i=0;i<CntAngle;i++) nARez[i]=-1; break;}
	};
	return 0;
}

int CKnot::SetMatrmP( CMatr &mP, CMatr &RezY1, CMatr &RezY2, CMatr *pRezY3, int i, double Tt, CMatr &mUM, CMatr &mUD, CMatr &mUC, std::string *pMsg )
{
	double x = 0.0, y = 0.0, Vx = 0.0, Vy = 0.0, Ax = 0.0, Ay = 0.0;//перемещения, скорости, ускорения.
	if( nXRez >= 0 )
	{
		x = RezY1[nXRez][i];
		Vx = RezY2[nXRez][i];
		Ax = (pRezY3)?(pRezY3->GetAt(nXRez,i)):(0.0);
		mP[nXRez][0] += GetPx( x, Vx, Ax, Tt, pMsg );
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
			return -1;
	}
	if( nYRez >= 0 )
	{
		y = RezY1[nYRez][i];
		Vy = RezY2[nYRez][i];
		Ay = (pRezY3)?(pRezY3->GetAt(nYRez,i)):(0.0);
		mP[nYRez][0] += GetPy( y, Vy, Ay, Tt, pMsg );
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
			return -1;
	}

	if ( (UxEnable)&&(nXRez>=0) )
	{
		for( int j = 0; j < mP.SizeY; j++ )
		{
			mP[j][0] -=	GetUx( x, Vx, Ax, Tt, pMsg, 0)*mUC[j][nXU]+
						GetUx( x, Vx, Ax, Tt, pMsg, 1)*mUD[j][nXU];
			if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
				return -1;
		}
	}
	if ( (UyEnable)&&(nYRez>=0) )
	{
		for( int j = 0; j < mP.SizeY; j++ )
		{
			mP[j][0] -=	GetUy( y, Vy, Ay, Tt, pMsg, 0)*mUC[j][nYU]+
						GetUy( y, Vy, Ay, Tt, pMsg, 1)*mUD[j][nYU];
			if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
				return -1;
		}
	}
	return 0;
}

int CKnot::SetMatrmP( CMatr & mP, CMatr &RezY1, CMatr &RezY2, CMatr *pRezY3, int i, double Tt, std::string *pMsg )
{
	if ( (UxEnable)&&(nXRez>=0) )
	{
		mP[nXRez][0] = GetUx( RezY1[nXRez][i], RezY2[nXRez][i], (pRezY3)?(pRezY3->GetAt(nXRez,i)):(0.0), Tt, pMsg );
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
			return -1;
	}

	if ( (UyEnable)&&(nYRez>=0) )
	{
		mP[nYRez][0] = GetUy( RezY1[nYRez][i], RezY2[nYRez][i], (pRezY3)?(pRezY3->GetAt(nYRez,i)):(0.0), Tt, pMsg );
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
			return -1;
	}
	
	return 0;
}

void CKnot::Init()
{
	Ax = Wx = Fix = Ay = Wy = Fiy = uAx = uWx = uFix = uAy = uWy = uFiy = 0.0;
	CShemeVarsTable *pVT = (m_pSheme)?(&m_pSheme->m_VarsTable):(NULL);
	string Zero("0");

	m_Ux.Reset( Zero, pVT );
	m_Uy.Reset( Zero, pVT );
	m_Ua.Reset( Zero, pVT );
	m_Uxp.Reset( Zero, pVT );
	m_Uyp.Reset( Zero, pVT );
	m_Uap.Reset( Zero, pVT );

	//Силовое возмущение
	m_Px.Reset( Zero, pVT );
	TypePx=0;
	PxEnable=false;
	m_Py.Reset( Zero, pVT );
	TypePy=0;
	PyEnable=false;

	//Кинематическое возмущение
	m_uUx.Reset( Zero, pVT );
	TypeUx = 0;
	nXU = 0;
	UxEnable=false;
	m_uUy.Reset( Zero, pVT );
	TypeUy = 0;
	nYU = 0;
	UyEnable=false;

	SelectMode=OldMode=0;
	FixedType=0;
	Num=0;
	ConnectType=0;
	CntAngle=10;

	nXRez=-1;	MoveX=0;
	nYRez=-1;	MoveY=0;
	for (int i=0;i<CntAngle;i++) {	nARez[i]=-1;	MoveA[i]=0;	}
}

double CKnot::GetPx(double x, double x1, double a, double Tt, std::string *pMsg )
{
	if( !PxEnable ) return 0.0;
	if( TypePx == 0 ) return Ax*sin(Wx*Tt+Fix);
	if( TypePx == 1 )
	{
		double val = 0.0;
		SetVarState( x, x1, a, Tt );
		val = m_Px.GetValue();
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
		{
			ShemeExprErr err = m_Px.GetRunErrorCode();
			if( err != SEE_NOERR )
			{
				(*pMsg) = m_Px.GetFullErrorMsg(err);
				return 0.0;
			}
		}
		return val;
	}
	if( TypePx == 2 )	return SpPx.GetValue(Tt);
	ASSERT(FALSE);
	return 0.0;
}

double CKnot::GetPy(double x, double x1, double a, double Tt, std::string *pMsg )
{
	if (!PyEnable) return 0;
	if (TypePy==0) return Ay*sin(Wy*Tt+Fiy);
	if (TypePy==1)
	{
		double val = 0.0;
		SetVarState( x, x1, a, Tt );
		val = m_Py.GetValue();
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg )
		{
			ShemeExprErr err = m_Py.GetRunErrorCode();
			if( err != SEE_NOERR )
			{
				(*pMsg) = m_Py.GetFullErrorMsg(err);
				return 0.0;
			}
		}
		return val;
	}
	if (TypePy==2)	return SpPy.GetValue(Tt);
	ASSERT(FALSE);
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

int CKnot::SetKinematicPos( CMatr &Y1, CMatr &Y2, CMatr *pY3, int i, double Tt, std::string *pMsg )
{
	if( UxEnable )
	{
		double x = Y1[nXRez][i], v = Y2[nXRez][i], a = (pY3)?(pY3->GetAt(nXRez,i)):(0.0);
		Y1[nXRez][i] = GetUx( x, v, a, Tt, pMsg );
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
			return -1;
		Y2[nXRez][i] = GetUx( x, v, a, Tt, pMsg, 1 );
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
			return -1;
	}
	if( UyEnable )
	{
		double y = Y1[nYRez][i], v = Y2[nYRez][i], a = (pY3)?(pY3->GetAt(nYRez,i)):(0.0);
		Y1[nYRez][i] = GetUy( y, v, a, Tt, pMsg );
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
			return -1;
		Y2[nYRez][i] = GetUy( y, v, a, Tt, pMsg, 1 );
		if( m_pSheme && m_pSheme->m_bValidateExpr && pMsg && !pMsg->empty() )
			return -1;
	}
	return 0;
}

void CKnot::SetCommonProperties( CKnot *pKnot )
{
	m_Ux.InitBy( pKnot->m_Ux );
	m_Uy.InitBy( pKnot->m_Uy );
	m_Ua.InitBy( pKnot->m_Ua );
	m_Uxp.InitBy( pKnot->m_Uxp );
	m_Uyp.InitBy( pKnot->m_Uyp );
	m_Uap.InitBy( pKnot->m_Uap );

	m_Px.InitBy( pKnot->m_Px );
	m_Py.InitBy( pKnot->m_Py );

	Ax = pKnot->Ax;
	Wx = pKnot->Wx;
	Fix = pKnot->Fix;
	Ay = pKnot->Ay;
	Wy = pKnot->Wy;
	Fiy = Fiy;

	/*
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
	*/
	SpPx = pKnot->SpPx;
	SpPy = pKnot->SpPy;
	SpUx = pKnot->SpUx;
	SpUy = pKnot->SpUy;
	//Произвольное, гармоническое или случайное возмущение
	TypePx = pKnot->TypePx;
	TypePy = pKnot->TypePy;
	//Флаг наличия возмущения
	PxEnable = pKnot->PxEnable;
	PyEnable = pKnot->PyEnable;

	//КИНЕМАТИЧЕСКОЕ ВОЗМУЩЕНИЕ (амплитуда, частота, фаза, произвольное возмущение)
	m_uUx.InitBy( pKnot->m_uUx );
	m_uUy.InitBy( pKnot->m_uUy );

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
