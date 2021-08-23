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
//класс, поддерживающий данные об параметрах пользовательской ф-ции
	void InitBy( const UserFuncParam &fp )
	{
		m_tType = fp.m_tType;
		m_name = fp.m_name;
	}
public:
	TypeID m_tType;//тип пар-ра
	std::string m_name;//имя переменной
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
//класс, поддерживающий данные о пользовательской ф-ции.
//Используется при исполнении кода (хранится в спец. карте).
	void InitBy( const UserFunc& );
public:
	Variables m_LocalVars;//таблица локальных переменных пользовательской ф-ции
	//(в том числе параметров ф-ции)
	ParamList m_Params;//список параметров ф-ции
	std::string m_label;//имя метки начала тела ф-ции
	CommandPointer m_cp;//позиция начала тела ф-ции в коде программы
	TypeID m_RetType;//тип возвращаемого значения 
	//(все пользовательские ф-ции должны чего-нибудь вернуть)
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