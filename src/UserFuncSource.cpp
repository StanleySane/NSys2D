// UserFuncSource.cpp: implementation of the UserFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"

#include"UserFuncHeader.h"
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
bool operator < ( const UserFuncParam &v1, const UserFuncParam &v2 )
{
	return v1.m_name < v2.m_name;
}
bool operator == ( const UserFuncParam &v1, const UserFuncParam &v2 )
{
	return v1.m_name == v2.m_name;
}
bool operator != ( const UserFuncParam &v1, const UserFuncParam &v2 )
{
	return v1.m_name != v2.m_name;
}
bool operator > ( const UserFuncParam &v1, const UserFuncParam &v2 )
{
	return v1.m_name > v2.m_name;
}
//////////////////////////////////////////////////////////////////////
//	members of UserFunc class
//////////////////////////////////////////////////////////////////////
void UserFunc::InitBy( const UserFunc &uf )
{
	m_Params = uf.m_Params;
	m_label = uf.m_label;
	m_cp = uf.m_cp;
	m_RetType = uf.m_RetType;
	m_LocalVars = uf.m_LocalVars;
}
