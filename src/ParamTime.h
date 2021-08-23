// ParamTime.h: interface for the CParamTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMTIME_H__DF62A942_DE3E_11D3_9814_BF05434AD432__INCLUDED_)
#define AFX_PARAMTIME_H__DF62A942_DE3E_11D3_9814_BF05434AD432__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CParamTime  
{
public:
	void Serialize( CArchive &, int );
	CParamTime();
	virtual ~CParamTime();
//	CString strT0, strT1, strdT;
	double T0, T1, dT;
};

#endif // !defined(AFX_PARAMTIME_H__DF62A942_DE3E_11D3_9814_BF05434AD432__INCLUDED_)
