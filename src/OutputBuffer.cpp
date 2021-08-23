// OutputBuffer.cpp: implementation of the COutputBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "OutputBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COutputBuffer::COutputBuffer()
{

}

COutputBuffer::~COutputBuffer()
{

}

CString COutputBuffer::ReadOut()
{
	CString str;
	m_Sec.Lock();
	str = m_str;
	m_str.Empty();
	m_Sec.Unlock();
	return str;
}

void COutputBuffer::WriteOut(const CString &str )
{
	CString tmp(str);
	m_Sec.Lock();
	m_str += tmp;
	m_NotFree.SetEvent();
	m_Sec.Unlock();
}
