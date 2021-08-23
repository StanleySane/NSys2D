// CoordD.cpp: implementation of the CCoordD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "CoordD.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCoordD::CCoordD(double a)
{
	x=y=a;
}

CCoordD::~CCoordD()
{

}

CCoordD::CCoordD(double _x, double _y)
{
	x=_x;	y=_y;
}

int CCoordD::operator ==(CCoordD & c)
{
	if ((x==c.x)&&(y==c.y)) return 1;// ??? исправить сравнение double-ов
	return 0;
}

CCoordD::CCoordD(CPoint &point)
{
	x=point.x;
	y=point.y;
}

CCoordD::CCoordD(CSize &size)
{
	x=size.cx;
	y=size.cy;
}

CCoordD CCoordD::operator - (CCoordD & c)
{
	return CCoordD(x-c.x,y-c.y);
}

CCoordD CCoordD::operator *(double num)
{
	return CCoordD(x*num, y*num);
}

double CCoordD::GetNorm()
{
	return sqrt(x*x+y*y);
}

CCoordD CCoordD::operator /(double num)
{
	return CCoordD(x/num, y/num);
}

double CCoordD::GetAng()
{
//	double M_PI=acos(-1);
//	double M_PI_2=M_PI/2.0;
	if (x>0.0)               return atan(y/x);
    if ((x<0.0)&&(y>=0.0))   return (CNSys2DApp::M_PI+atan(y/x));
    if ((x<0.0)&&(y<0.0))    return (-CNSys2DApp::M_PI+atan(y/x));
    if ((x==0.0)&&(y>0.0))   return (CNSys2DApp::M_PI_2);
    if ((x==0.0)&&(y<0.0))   return (-CNSys2DApp::M_PI_2);

    return 0.0;
}

CCoordD &CCoordD::operator *=(double num)
{
	x*=num;
	y*=num;
	return *this;
}

CCoordD CCoordD::operator +(CCoordD & c)
{
	return CCoordD(x+c.x,y+c.y);
}
