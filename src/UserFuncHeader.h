/////////////////////////////////////////////////////////////////
//	file UserFuncHeader.h
/////////////////////////////////////////////////////////////////

#ifndef _USER_FUNC_HEADER_H_
#define _USER_FUNC_HEADER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include"ScriptDefs.h"

#include"CommandHeader.h"
#include"VariablesHeader.h"

#include<list>

class UserFuncParam
{
//�����, �������������� ������ �� ���������� ���������������� �-���
	void InitBy( const UserFuncParam &fp )
	{
		m_tType = fp.m_tType;
		m_name = fp.m_name;
	}
public:
	TypeID m_tType;//��� ���-��
	std::string m_name;//��� ����������
	UserFuncParam& operator = ( const UserFuncParam &fp )
	{
		if( this == &fp )	return *this;
		InitBy(fp);
		return *this;
	}
	UserFuncParam( const UserFuncParam &fp )
	{
		InitBy(fp);
	}
	UserFuncParam(){}
	~UserFuncParam(){}

	friend bool operator < ( const UserFuncParam&, const UserFuncParam& );
	friend bool operator == ( const UserFuncParam&, const UserFuncParam& );
	friend bool operator != ( const UserFuncParam&, const UserFuncParam& );
	friend bool operator > ( const UserFuncParam&, const UserFuncParam& );

};

typedef std::list<UserFuncParam> ParamList;

class UserFunc
{
//�����, �������������� ������ � ���������������� �-���.
//������������ ��� ���������� ���� (�������� � ����. �����).
	void InitBy( const UserFunc& );
public:
	Variables m_LocalVars;//������� ��������� ���������� ���������������� �-���
	//(� ��� ����� ���������� �-���)
	ParamList m_Params;//������ ���������� �-���
	std::string m_label;//��� ����� ������ ���� �-���
	CommandPointer m_cp;//������� ������ ���� �-��� � ���� ���������
	TypeID m_RetType;//��� ������������� �������� 
	//(��� ���������������� �-��� ������ ����-������ �������)
	UserFunc& operator = ( const UserFunc &uf )
	{
		if( this == &uf )	return *this;
		InitBy(uf);
		return *this;
	}
	UserFunc( const UserFunc &uf )
	{
		InitBy(uf);
	}
	UserFunc(){}
	~UserFunc(){}
};
typedef std::map<std::string,UserFunc> UserFuncTable;
typedef UserFuncTable::value_type MakeUserFunc;

#endif //_USER_FUNC_HEADER_H_