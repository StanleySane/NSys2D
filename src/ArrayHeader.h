/////////////////////////////////////////////////////////////////
//	file ArrayHeader.h
/////////////////////////////////////////////////////////////////

#ifndef _ARRAY_HEADER_H_
#define _ARRAY_HEADER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include<vector>

#include"ScriptDefs.h"

class Value;
class Array
{
	std::vector<Value*> *m_vec;
	TypeID m_tType;//тип массива

	void Destruct();
	void InitBy( const Array& );
public:

	Array& operator = ( const Array &v )
	{
		if( this == &v )	return *this;
		InitBy(v);
		return *this;
	}
	Array( const Array &v ):m_vec(NULL), m_tType(TYPE_UNKNOWN)
	{
		InitBy(v);
	}
	Array( TypeID tp = TYPE_UNKNOWN ):m_vec(NULL), m_tType(tp)
	{}
	~Array()
	{	Destruct();	}

	//ф-ции-члены
	int Size() const
	{
		if( m_vec == NULL )
			return 0;
		return m_vec->size();
	}
	bool SetAt( int, const Value& );
	bool GetAt( int, Value& ) const;
	bool SetType( TypeID );
	bool Resize(int);
	TypeID GetType() const
	{
		return m_tType;
	}
	static bool IsArray( TypeID );
	static TypeID GetValType( TypeID );

};

typedef std::map<std::string,Array> VarArray;
typedef VarArray::value_type MakeArray;

#endif //_ARRAY_HEADER_H_