// ListSpectr.cpp: implementation of the CListSpectr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "ListSpectr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListSpectr::CListSpectr()
{

}

CListSpectr::~CListSpectr()
{
	POSITION pos=GetHeadPosition();
	while (pos)
	{
		CComplexSpectr *pCS=(CComplexSpectr*)GetNext(pos);
		if (pCS) delete pCS;
	}
}

CComplexSpectr* CListSpectr::AddSpectr(CComplexSpectr & Dat)
{
	if ((Dat.pKn1==Dat.pKn2)&&(Dat.Free1==Dat.Free2)) return 0;
	POSITION pos=GetHeadPosition();
	while (pos)
	{
		CComplexSpectr *pCS=(CComplexSpectr*)GetNext(pos);
		if (Dat==(*pCS))
			return pCS;
	}
	CComplexSpectr *pCS=new CComplexSpectr;
	(*pCS)=Dat;
	AddTail(pCS);
	return pCS;
}

void CListSpectr::DelSpectr(CComplexSpectr & Dat)
{
	POSITION pos_prev ,pos=GetHeadPosition();
	while (pos)
	{
		pos_prev=pos;
		CComplexSpectr *pCS=(CComplexSpectr*)GetNext(pos);
		if (Dat==(*pCS))
		{
			RemoveAt(pos_prev);
			return;
		}
	}
}

void CListSpectr::Clear()
{
	POSITION pos=GetHeadPosition();
	while (pos)
	{
		delete GetNext(pos);
	}
	RemoveAll();
}
