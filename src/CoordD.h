// CoordD.h: interface for the CCoordD class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COORDD_H__C2505584_C05A_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_COORDD_H__C2505584_C05A_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CCoordD  
{
public:
	CCoordD operator + (CCoordD &c2);
	CCoordD &operator *= (double num);
	double GetAng();
	CCoordD operator / (double num);
	double GetNorm();
	CCoordD operator * (double num);
	CCoordD operator - (CCoordD &c);
	CCoordD(CSize &size);
	CCoordD(CPoint &point);
	int operator == (CCoordD &c);
	CCoordD(double _x, double _y);
	double y;
	double x;
	CCoordD(double a=0);
	virtual ~CCoordD();
};

#endif // !defined(AFX_COORDD_H__C2505584_C05A_11D2_AF23_BB2B1C460D22__INCLUDED_)
