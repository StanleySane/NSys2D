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

class CShemeDoc;
class CSheme;

class CObjectSheme  
{
public:
	virtual void Serialize( CArchive &ar, int sv );
	static POINT ShemeToScreen(CCoordD &coord, CParamView *pParamView);
	virtual void Draw(CDC *dc, CParamView* pParamView)=0;
	virtual void DrawGL( CShemeDoc*, int ) = 0;

	CObjectSheme( CSheme *p = NULL );
	virtual ~CObjectSheme();
	CObjectSheme( const CObjectSheme& );
	CObjectSheme& operator=( const CObjectSheme& );

	CSheme *m_pSheme;//указатель на схему, к которой прикреплён объект

};

#endif // !defined(AFX_OBJECTSHEME_H__6CF72FA4_C76C_11D2_AF23_BB2B1C460D22__INCLUDED_)
