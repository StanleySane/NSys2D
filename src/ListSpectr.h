// ListSpectr.h: interface for the CListSpectr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTSPECTR_H__EAB8D3E3_B1FD_11D3_9811_BF05434AD432__INCLUDED_)
#define AFX_LISTSPECTR_H__EAB8D3E3_B1FD_11D3_9811_BF05434AD432__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>
#include "complexspectr.h"

class CListSpectr : public CList<CComplexSpectr*, CComplexSpectr*>  
{
public:
	void Clear();
	void DelSpectr(CComplexSpectr & Dat);
	CComplexSpectr* AddSpectr(CComplexSpectr &Dat);
	CListSpectr();
	virtual ~CListSpectr();

};

#endif // !defined(AFX_LISTSPECTR_H__EAB8D3E3_B1FD_11D3_9811_BF05434AD432__INCLUDED_)
