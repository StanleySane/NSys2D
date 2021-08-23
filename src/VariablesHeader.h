/////////////////////////////////////////////////////////////////
//	file VariablesHeader.h
/////////////////////////////////////////////////////////////////

#ifndef _VARIABLES_HEADER_H_
#define _VARIABLES_HEADER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include"ScriptDefs.h"

#include<stack>

class VarTables;
class File;
class Array;
class ScriptPtr;
class MatrPtr;
class Value;

class RodPtr;
class HardRodPtr;
class SpringPtr;
class DemferPtr;
class MassPtr;
class KnotPtr;
class ShemePtr;

class Variables
{
//класс, поддерживающий таблицу переменных разных типов.
//например таблицу переменных, объ€вленных пользователем.
	VarTables *m_pVars;

	void InitBy( const Variables& );
	void Destruct();
public:
	typedef std::map<VarTables*,int> Refs;
	typedef Refs::value_type MakeVarsRef;
	typedef std::pair<Refs::iterator,bool> Pair;
	static Refs m_VarsRefMap;

	Variables& operator = ( const Variables &vt )
	{
		if( this != &vt )	InitBy(vt);
		return *this;
	}
	Variables( const Variables &vt ):m_pVars(NULL)
	{
		InitBy(vt);
	}
	Variables();
	~Variables()
	{	Destruct();	}

	//ф-ции члены:
	TypeID GetVarType( const std::string& ) const;
	Array* GetArray( const std::string& );
	File* GetFile( const std::string& );
	ScriptPtr* GetScript( const std::string& );
	MatrPtr* GetMatr( const std::string& );
	RodPtr* GetRod( const std::string& );
	HardRodPtr* GetHardRod( const std::string& );
	SpringPtr* GetSpring( const std::string& );
	DemferPtr* GetDemfer( const std::string& );
	MassPtr* GetMass( const std::string& );
	KnotPtr* GetKnot( const std::string& );
	ShemePtr* GetSheme( const std::string& );

	void GetVarValue( const std::string&, TypeID, Value& ) const;
	void AddVar( const std::string&, TypeID );
	void Clear();
	errorsT AssignArray( const std::string&, const Value& );
	errorsT AssignMatr( const std::string&, const Value& );
	bool IsScript( const std::string& ) const;
	bool IsFile( const std::string& ) const;
	TypeID ArrayType( const std::string& ) const;
	static bool IsElem( TypeID );

	VarInteger* IntMap() const;
	VarBool* BoolMap() const;
	VarDouble* DoubleMap() const;
	VarString* StringMap() const;
	///////////////////////////////////////////////////////////////////
	friend bool operator < ( const Variables &vt1, const Variables &vt2 );
	friend bool operator == ( const Variables &vt1, const Variables &vt2 );
};

typedef std::stack<Variables> LocalVarStack;

#endif //_VARIABLES_HEADER_H_
