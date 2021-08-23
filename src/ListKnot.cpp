// ListKnot.cpp: implementation of the CListKnot class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"
#include "ListKnot.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListKnot::CListKnot()
{

}

CListKnot::~CListKnot()
{
	POSITION pos=GetHeadPosition();
	while (pos)
	{
		CKnot* pkn=GetNext(pos);
		if (pkn) delete pkn;
	}
}

CKnot* CListKnot::FindKnot(CString & name)
{
	POSITION pos=GetHeadPosition();
	while (pos)
	{
		CKnot* kn=GetNext(pos);
		if (kn->GetName()==name) return kn;
	}
	return 0;
}

UINT CListKnot::FindPos(CKnot * knot, POSITION *position/*=0*/)
{
	UINT count=0;

	POSITION pos2,pos=GetHeadPosition();
	while (pos)
	{
		pos2=pos;
		CKnot* kn=GetNext(pos);
		count++;
		kn->Num=count;
		if (kn==knot) 
		{
			if (position) *position=pos2;
			return count;
		}
	}
	return 0;
}

CKnot* CListKnot::GetKnotPos(int num)
{
	int count=0;

	POSITION pos=GetHeadPosition();
	while (pos)
	{
		CKnot* kn=GetNext(pos);
		if (num==count) return kn;
		count++;
	}
	return NULL;
}

CKnot* CListKnot::AddKnot(CKnot & knot)
{
	CKnot *kn,*pKnot;
	int count=0;

	POSITION pos=GetHeadPosition();
	while (pos)
	{
		kn=GetNext(pos);
		count++;
//		kn->Num=count;
		if (kn->GetCoord()==knot.GetCoord())
		{
			*kn=knot;
			return kn;
		}
	}
	pKnot = new CKnot(knot.m_pSheme);
	*pKnot=knot;
	//Определение номера узла
	int NewNum=0;
	int ExistNum=1;
	while (ExistNum)
	{
		ExistNum=0;
		NewNum++;
		POSITION pos=GetHeadPosition();
		while (pos)	if (GetNext(pos)->Num==NewNum) ExistNum=1;
	}
	pKnot->Num=NewNum;//ReNum();//count+1
	AddTail(pKnot);
	return pKnot;
}

void CListKnot::Clear()
{
	POSITION pos=GetHeadPosition();
	while (pos)
	{
		delete GetNext(pos);
	}
	RemoveAll();
}

int CListKnot::ReNum()
{
	CKnot *kn;
	int count=0;

	POSITION pos=GetHeadPosition();
	while (pos)
	{
		kn=GetNext(pos);
		count++;
		kn->Num=count;
	}
	return count+1;
}

int CListKnot::FindNum(int NumFree)
{
	POSITION pos=GetHeadPosition();
	while (pos)
	{
		CKnot* kn=GetNext(pos);
		if (kn->nXRez==NumFree) return kn->Num;
		if (kn->nYRez==NumFree) return kn->Num;
		for (int i=0;i<10;i++)
			if (kn->nARez[i]==NumFree) return kn->Num;
	}
	return 0;
}
