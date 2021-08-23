// ListKnot.h: interface for the CListKnot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTKNOT_H__E2295022_C256_11D2_AF23_BB2B1C460D22__INCLUDED_)
#define AFX_LISTKNOT_H__E2295022_C256_11D2_AF23_BB2B1C460D22__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>
#include "knot.h"

class CListKnot:public CList<CKnot*,CKnot*>
{
public:
	int FindNum(int NumFree);
	int ReNum();
	void Clear();
	CKnot* AddKnot(CKnot &knot);
	CKnot* GetKnotPos(int num);
	UINT FindPos(CKnot *kn, POSITION *position=0);
	CKnot* FindKnot(CString &name);
	CListKnot();
	virtual ~CListKnot();
};

#endif // !defined(AFX_LISTKNOT_H__E2295022_C256_11D2_AF23_BB2B1C460D22__INCLUDED_)
