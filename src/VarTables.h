/////////////////////////////////////////////////////////////////
//	file VarTables.h
/////////////////////////////////////////////////////////////////

#ifndef _VAR_TABLES_H_
#define _VAR_TABLES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include"ScriptDefs.h"

#include"ArrayHeader.h"
#include"FileHeader.h"
#include"ScriptPtrHeader.h"
#include"MatrPtr.h"
#include"RodPtr.h"
#include"HardRodPtr.h"
#include"SpringPtr.h"
#include"DemferPtr.h"
#include"MassPtr.h"
#include"KnotPtr.h"

class Value;

class VarTables
{
//класс, поддерживающий таблицу переменных разных типов.
//например таблицу переменных, объявленных пользователем.
	inline void InitBy( const VarTables& );
public:
	VarBool m_vBool;
	VarInteger m_vInt;
	VarDouble m_vDouble;
	VarString m_vString;
	VarArray m_vArray;
	VarFile m_vFile;
	VarScript m_vScript;
	VarMatr m_vMatr;
	VarRod m_vRod;
	VarHardRod m_vHardRod;
	VarSpring m_vSpring;
	VarDemf m_vDemfer;
	VarMass m_vMass;
	VarKnot m_vKnot;

	VarTables& operator = ( const VarTables &vt )
	{
		if( this == &vt )	InitBy(vt);
		return *this;
	}
	VarTables( const VarTables &vt )
	{
		InitBy(vt);
	}
	VarTables(){}
	~VarTables()
	{	Clear();	}
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

	void GetVarValue( const std::string&, TypeID, Value& ) const;
	void AddVar( const std::string&, TypeID );
	void Clear();

};

#endif //_VAR_TABLES_H_