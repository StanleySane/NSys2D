// VarTablesSource.cpp: implementation of the VarTables class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"

#include"ValueHeader.h"
#include"VarTables.h"
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
//	members of VarTables class
//////////////////////////////////////////////////////////////////////
TypeID VarTables::GetVarType( const std::string &var ) const
{
//ф-ция ищет в своих картах переменную с именем var
//и возвращает её тип. Если её нет, то возвращается TYPE_UNKNOWN.
//ВНИМАНИЕ: var уже должна быть в нижнем регистре !
	if( m_vBool.find(var) != m_vBool.end() )
		return TYPE_BOOL;
	if( m_vInt.find(var) != m_vInt.end() )
		return TYPE_INT;
	if( m_vDouble.find(var) != m_vDouble.end() )
		return TYPE_DOUBLE;
	if( m_vString.find(var) != m_vString.end() )
		return TYPE_STRING;
	VarArray::const_iterator itArr = m_vArray.find(var);
	if( itArr != m_vArray.end() )
	{
		TypeID tp = (*itArr).second.GetType();
		ASSERT( tp != TYPE_UNKNOWN );
		return tp;
	}
	if( m_vFile.find(var) != m_vFile.end() )
		return TYPE_FILE;
	if( m_vScript.find(var) != m_vScript.end() )
		return TYPE_SCRIPT;
	if( m_vMatr.find(var) != m_vMatr.end() )
		return TYPE_MATR;
	if( m_vRod.find(var) != m_vRod.end() )
		return TYPE_ROD;
	if( m_vHardRod.find(var) != m_vHardRod.end() )
		return TYPE_HARDROD;
	if( m_vSpring.find(var) != m_vSpring.end() )
		return TYPE_SPRING;
	if( m_vDemfer.find(var) != m_vDemfer.end() )
		return TYPE_DEMFER;
	if( m_vMass.find(var) != m_vMass.end() )
		return TYPE_MASS;
	if( m_vKnot.find(var) != m_vKnot.end() )
		return TYPE_KNOT;
	if( m_vSheme.find(var) != m_vSheme.end() )
		return TYPE_SHEME;
	
	return TYPE_UNKNOWN;
}

MatrPtr* VarTables::GetMatr( const std::string &name )
{
//ф-ция возвращает указатель на мцу с именем name из данной
//карты, или NULL, если такой м-цы в карте нет.
//ВНИМАНИЕ: name должен быть в нижнем регистре !
	VarMatr::iterator it = m_vMatr.find(name);
	if( it != m_vMatr.end() )
		return &(*it).second;
	return NULL;
}

Array* VarTables::GetArray( const std::string &name )
{
//ф-ция возвращает указатель на массив с именем name из данной
//карты, или NULL, если такого массива в карте нет.
//ВНИМАНИЕ: name должен быть в нижнем регистре !
	VarArray::iterator it = m_vArray.find(name);
	if( it != m_vArray.end() )
		return &(*it).second;
	return NULL;
}

File* VarTables::GetFile( const std::string &name )
{
//ф-ция возвращает указатель на файл с именем name из данной
//карты, или NULL, если такого файла в карте нет.
//ВНИМАНИЕ: name должен быть в нижнем регистре !
	VarFile::iterator it = m_vFile.find(name);
	if( it != m_vFile.end() )
		return &(*it).second;
	return NULL;
}

ScriptPtr* VarTables::GetScript( const std::string &name )
{
//ф-ция возвращает указатель на скрипт с именем name из данной
//карты, или NULL, если такого файла в карте нет.
//ВНИМАНИЕ: name должен быть в нижнем регистре !
	VarScript::iterator it = m_vScript.find(name);
	if( it != m_vScript.end() )
		return &(*it).second;
	return NULL;
}

RodPtr* VarTables::GetRod( const std::string &name )
{
//ф-ция возвращает указатель на элемент с именем name из данной
//карты, или NULL, если такого элемента в карте нет.
//ВНИМАНИЕ: name должен быть в нижнем регистре !
	VarRod::iterator it = m_vRod.find(name);
	if( it != m_vRod.end() )
		return &(*it).second;
	return NULL;
}

HardRodPtr* VarTables::GetHardRod( const std::string &name )
{
//ф-ция возвращает указатель на элемент с именем name из данной
//карты, или NULL, если такого элемента в карте нет.
//ВНИМАНИЕ: name должен быть в нижнем регистре !
	VarHardRod::iterator it = m_vHardRod.find(name);
	if( it != m_vHardRod.end() )
		return &(*it).second;
	return NULL;
}

SpringPtr* VarTables::GetSpring( const std::string &name )
{
//ф-ция возвращает указатель на элемент с именем name из данной
//карты, или NULL, если такого элемента в карте нет.
//ВНИМАНИЕ: name должен быть в нижнем регистре !
	VarSpring::iterator it = m_vSpring.find(name);
	if( it != m_vSpring.end() )
		return &(*it).second;
	return NULL;
}

DemferPtr* VarTables::GetDemfer( const std::string &name )
{
//ф-ция возвращает указатель на элемент с именем name из данной
//карты, или NULL, если такого элемента в карте нет.
//ВНИМАНИЕ: name должен быть в нижнем регистре !
	VarDemf::iterator it = m_vDemfer.find(name);
	if( it != m_vDemfer.end() )
		return &(*it).second;
	return NULL;
}

MassPtr* VarTables::GetMass( const std::string &name )
{
//ф-ция возвращает указатель на элемент с именем name из данной
//карты, или NULL, если такого элемента в карте нет.
//ВНИМАНИЕ: name должен быть в нижнем регистре !
	VarMass::iterator it = m_vMass.find(name);
	if( it != m_vMass.end() )
		return &(*it).second;
	return NULL;
}

KnotPtr* VarTables::GetKnot( const std::string &name )
{
//ф-ция возвращает указатель на узел с именем name из данной
//карты, или NULL, если такого узла в карте нет.
//ВНИМАНИЕ: name должен быть в нижнем регистре !
	VarKnot::iterator it = m_vKnot.find(name);
	if( it != m_vKnot.end() )
		return &(*it).second;
	return NULL;
}

ShemePtr* VarTables::GetSheme( const std::string &name )
{
//ф-ция возвращает указатель на схему с именем name из данной
//карты, или NULL, если такой схемы в карте нет.
//ВНИМАНИЕ: name должен быть в нижнем регистре !
	VarSheme::iterator it = m_vSheme.find(name);
	if( it != m_vSheme.end() )
		return &(*it).second;
	return NULL;
}

void VarTables::GetVarValue( const std::string &str, TypeID tp, Value &val ) const
{
//ф-ция ищет переменную name типа tp у себя в картах и заносит
//значение найденной переменной в val.
//Если такой переменной нет, то на выходе val.m_tType==TYPE_UNKNOWN
	string name(str);
	MakeLower(name);
	val.SetType( TYPE_UNKNOWN );
	switch(tp)
	{
	case TYPE_BOOL:
		{
			VarBool::const_iterator it = m_vBool.find(name);
			if( it != m_vBool.end() )
			{
				val.SetBool( (*it).second );
			}
		}
		break;
	case TYPE_INT:
		{
			VarInteger::const_iterator it = m_vInt.find(name);
			if( it != m_vInt.end() )
			{
				val.SetInt( (*it).second );
			}
		}
		break;
	case TYPE_DOUBLE:
		{
			VarDouble::const_iterator it = m_vDouble.find(name);
			if( it != m_vDouble.end() )
				val.SetDouble( (*it).second );
		}
		break;
	case TYPE_STRING:
		{
			VarString::const_iterator it = m_vString.find(name);
			if( it != m_vString.end() )
				val.SetString( (*it).second );
		}
		break;
	case TYPE_ARRAY_INT:
	case TYPE_ARRAY_BOOL:
	case TYPE_ARRAY_DOUBLE:
	case TYPE_ARRAY_STRING:
		{
			VarArray::const_iterator it = m_vArray.find(name);
			if( it != m_vArray.end() )
				val.SetArray( (*it).second );
		}
		break;
	case TYPE_FILE:
		{
			VarFile::const_iterator it = m_vFile.find(name);
			if( it != m_vFile.end() )
				val.SetFile( (*it).second );
		}
		break;
	case TYPE_SCRIPT:
		{
			VarScript::const_iterator it = m_vScript.find(name);
			if( it != m_vScript.end() )
				val.SetScript( (*it).second );
		}
		break;
	case TYPE_MATR:
		{
			VarMatr::const_iterator it = m_vMatr.find(name);
			if( it != m_vMatr.end() )
				val.SetMatr( (*it).second );
		}
		break;
	case TYPE_ROD:
		{
			VarRod::const_iterator it = m_vRod.find(name);
			if( it != m_vRod.end() )
				val.SetRod( (*it).second );
		}
		break;
	case TYPE_HARDROD:
		{
			VarHardRod::const_iterator it = m_vHardRod.find(name);
			if( it != m_vHardRod.end() )
				val.SetHardRod( (*it).second );
		}
		break;
	case TYPE_SPRING:
		{
			VarSpring::const_iterator it = m_vSpring.find(name);
			if( it != m_vSpring.end() )
				val.SetSpring( (*it).second );
		}
		break;
	case TYPE_DEMFER:
		{
			VarDemf::const_iterator it = m_vDemfer.find(name);
			if( it != m_vDemfer.end() )
				val.SetDemfer( (*it).second );
		}
		break;
	case TYPE_MASS:
		{
			VarMass::const_iterator it = m_vMass.find(name);
			if( it != m_vMass.end() )
				val.SetMass( (*it).second );
		}
		break;
	case TYPE_KNOT:
		{
			VarKnot::const_iterator it = m_vKnot.find(name);
			if( it != m_vKnot.end() )
				val.SetKnot( (*it).second );
		}
		break;
	case TYPE_SHEME:
		{
			VarSheme::const_iterator it = m_vSheme.find(name);
			if( it != m_vSheme.end() )
				val.SetSheme( (*it).second );
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}//switch
}

void VarTables::AddVar( const std::string &name, TypeID tp )
{
//ф-ция заносит в карту переменных map новую переменную
//с именем name и типом tp
	string tmp(name);
	MakeLower(tmp);
	switch( tp )
	{
	case TYPE_BOOL:
		m_vBool.insert( MakeBool(tmp,true) );
		break;
	case TYPE_INT:
		m_vInt.insert( MakeInt(tmp,0) );
		break;
	case TYPE_DOUBLE:
		m_vDouble.insert( MakeDouble(tmp,0.0) );
		break;
	case TYPE_STRING:
		m_vString.insert( MakeString(tmp,string("")) );
		break;
	case TYPE_ARRAY_INT:
	case TYPE_ARRAY_BOOL:
	case TYPE_ARRAY_DOUBLE:
	case TYPE_ARRAY_STRING:
		m_vArray.insert( MakeArray(tmp,Array(tp)) );
		break;
	case TYPE_FILE:
		m_vFile.insert( MakeFile(tmp,File()) );
		break;
	case TYPE_SCRIPT:
		m_vScript.insert( MakeScript(tmp,ScriptPtr()) );
		break;
	case TYPE_MATR:
		m_vMatr.insert( MakeMatr(tmp,MatrPtr()) );
		break;
	case TYPE_ROD:
		m_vRod.insert( MakeRod(tmp,RodPtr()) );
		break;
	case TYPE_HARDROD:
		m_vHardRod.insert( MakeHardRod(tmp,HardRodPtr()) );
		break;
	case TYPE_SPRING:
		m_vSpring.insert( MakeSpring(tmp,SpringPtr()) );
		break;
	case TYPE_DEMFER:
		m_vDemfer.insert( MakeDemf(tmp,DemferPtr()) );
		break;
	case TYPE_MASS:
		m_vMass.insert( MakeMass(tmp,MassPtr()) );
		break;
	case TYPE_KNOT:
		m_vKnot.insert( MakeKnot(tmp,KnotPtr()) );
		break;
	case TYPE_SHEME:
		m_vSheme.insert( MakeSheme(tmp,ShemePtr()) );
		break;
	default:
		ASSERT(FALSE);
		break;
	}//switch
}

void VarTables::Clear()
{
	m_vBool.erase( m_vBool.begin(), m_vBool.end() );
	m_vInt.erase( m_vInt.begin(), m_vInt.end() );
	m_vDouble.erase( m_vDouble.begin(), m_vDouble.end() );
	m_vString.erase( m_vString.begin(), m_vString.end() );

	m_vArray.erase( m_vArray.begin(), m_vArray.end() );
	m_vFile.erase( m_vFile.begin(), m_vFile.end() );
	m_vScript.erase( m_vScript.begin(), m_vScript.end() );
	m_vMatr.erase( m_vMatr.begin(), m_vMatr.end() );

	m_vRod.erase( m_vRod.begin(), m_vRod.end() );
	m_vHardRod.erase( m_vHardRod.begin(), m_vHardRod.end() );
	m_vSpring.erase( m_vSpring.begin(), m_vSpring.end() );
	m_vDemfer.erase( m_vDemfer.begin(), m_vDemfer.end() );
	m_vMass.erase( m_vMass.begin(), m_vMass.end() );
	m_vKnot.erase( m_vKnot.begin(), m_vKnot.end() );
	m_vSheme.erase( m_vSheme.begin(), m_vSheme.end() );
}

inline void VarTables::InitBy( const VarTables &vt )
{
	m_vBool = vt.m_vBool;
	m_vInt = vt.m_vInt;
	m_vDouble = vt.m_vDouble;
	m_vString = vt.m_vString;

	m_vArray = vt.m_vArray;
	m_vFile = vt.m_vFile;
	m_vScript = vt.m_vScript;
	m_vMatr = vt.m_vMatr;

	m_vRod = vt.m_vRod;
	m_vHardRod = vt.m_vHardRod;
	m_vSpring = vt.m_vSpring;
	m_vDemfer = vt.m_vDemfer;
	m_vMass = vt.m_vMass;
	m_vKnot = vt.m_vKnot;
	m_vSheme = vt.m_vSheme;
}
