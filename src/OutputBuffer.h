// OutputBuffer.h: interface for the COutputBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTBUFFER_H__981535C4_4FDA_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_OUTPUTBUFFER_H__981535C4_4FDA_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include<afxmt.h>

class COutputBuffer  
{
	CCriticalSection m_Sec;
	CString m_str;
public:
	void WriteOut( const CString& );
	CString ReadOut();
	COutputBuffer();
	~COutputBuffer();

	CEvent m_NotFree;
};

#endif // !defined(AFX_OUTPUTBUFFER_H__981535C4_4FDA_11D6_B89D_FE2BA355A53D__INCLUDED_)
