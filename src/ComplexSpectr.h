// ComplexSpectr.h: interface for the CComplexSpectr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPLEXSPECTR_H__EAB8D3E2_B1FD_11D3_9811_BF05434AD432__INCLUDED_)
#define AFX_COMPLEXSPECTR_H__EAB8D3E2_B1FD_11D3_9811_BF05434AD432__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "knot.h"

class CComplexSpectr  
{
public:
	void Serialize(CArchive& ar);
	BOOL operator == (CComplexSpectr &cs);
	CComplexSpectr();
	virtual ~CComplexSpectr();
	CKnot *pKn1,*pKn2;
	int Free1, Free2;//0...2
	CSpectrParam Sp;
	//CString strSpectr;
};

#endif // !defined(AFX_COMPLEXSPECTR_H__EAB8D3E2_B1FD_11D3_9811_BF05434AD432__INCLUDED_)
