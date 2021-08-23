// ParamIntegr.h: interface for the CParamIntegr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMINTEGR_H__7C49F9C2_AC8F_11D3_9811_BF05434AD432__INCLUDED_)
#define AFX_PARAMINTEGR_H__7C49F9C2_AC8F_11D3_9811_BF05434AD432__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CParamIntegr  
{
public:
	void Serialize( CArchive&, int );
	CParamIntegr();
	virtual ~CParamIntegr();

	double Step, Time;
//	CString strStep, strTime;
	
	int TypeMethod;
};

#endif // !defined(AFX_PARAMINTEGR_H__7C49F9C2_AC8F_11D3_9811_BF05434AD432__INCLUDED_)
