// ParamView.h: interface for the CParamView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMVIEW_H__6CF72FA3_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_PARAMVIEW_H__6CF72FA3_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxwin.h>
#include "coordd.h"

class CParamView  
{
public:
	void Serialize(CArchive& ar);
	double Scale;
	CCoordD MoveCenter;
	CPoint pos;
	BOOL Gray;
	double MultMove;
	double MultAngl;

//	CParamView(double scale=2, CPoint &point=CPoint(0,0));
	CParamView(double scale=2, 
		   CCoordD &coord=CCoordD(0,0));
	virtual ~CParamView();

};

#endif // !defined(AFX_PARAMVIEW_H__6CF72FA3_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
