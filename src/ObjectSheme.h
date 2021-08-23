// ObjectSheme.h: interface for the CObjectSheme class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTSHEME_H__6CF72FA4_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_OBJECTSHEME_H__6CF72FA4_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "coordd.h"
#include "ParamView.h"

class CObjectSheme  
{
public:
	virtual void Serialize(CArchive & ar);
	POINT ShemeToScreen(CCoordD &coord, CParamView *pParamView);
	virtual void Draw(CDC *dc, CParamView* pParamView)=0;
	CObjectSheme();
	virtual ~CObjectSheme();

};

#endif // !defined(AFX_OBJECTSHEME_H__6CF72FA4_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
