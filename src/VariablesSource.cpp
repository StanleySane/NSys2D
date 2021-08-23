// VariablesSource.cpp: implementation of the Variables class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"

#include"ValueHeader.h"
#include"VariablesHeader.h"
#include"VarTables.h"
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//Variables::Refs Variables::m_VarsRefMap;
/////////////////////////////////////////////////////////////////
bool operator < ( const Variables &vt1, const Variables &vt2 )
{
//	return vt1.m_vBool.size() < vt2.m_vBool.size();
	return true;
}

bool operator == ( const Variables &vt1, const Variables &vt2 )
{
//	return vt1.m_vBool.size() == vt2.m_vBool.size();
	return false;
}
//////////////////////////////////////////////////////////////////////
//	members of Variables class
//////////////////////////////////////////////////////////////////////
Variables::Variables()
{
	try
	{
		m_pVars = new VarTables();
		Pair p = m_VarsRefMap.insert( MakeVarsRef(m_pVars,1) );
		if( p.second == false )
		{
			++(*p.first).second;
		}
	}
	catch( bad_alloc& )
	{
		m_pVars = NULL;
	}
}

void Variables::InitBy( const Variables &obj )
{
	if( m_pVars != obj.m_pVars )
	{
		if( m_pVars )
			Destruct();
		m_pVars = obj.m_pVars;
		if( m_pVars )
		{
			Refs::iterator it = m_VarsRefMap.find(m_pVars);
			ASSERT( it != m_VarsRefMap.end() );
			(*it).second++;
		}
	}
}

void Variables::Destruct()
{
	if( m_pVars )
	{
		Refs::iterator it = m_VarsRefMap.find(m_pVars);
		ASSERT( it != m_VarsRefMap.end() );
		(*it).second--;
		if( (*it).second == 0 )
		{
			delete m_pVars;
			m_pVars = NULL;
			m_VarsRefMap.erase(it);
		}
	}
}

void Variables::GetVarValue( const std::string &name, TypeID t, Value &val ) const
{
	ASSERT(m_pVars);
	m_pVars->GetVarValue( name, t, val );
}

TypeID Variables::GetVarType( const std::string &name ) const
{
	ASSERT(m_pVars);
	return m_pVars->GetVarType( name );
}

void Variables::AddVar( const std::string &name, TypeID t )
{
	ASSERT(m_pVars);
	m_pVars->AddVar( name, t );
}

MatrPtr* Variables::GetMatr( const std::string &name )
{
	ASSERT(m_pVars);
	return m_pVars->GetMatr( name );
}

ScriptPtr* Variables::GetScript( const std::string &name )
{
	ASSERT(m_pVars);
	return m_pVars->GetScript( name );
}

Array* Variables::GetArray( const std::string &name )
{
	ASSERT(m_pVars);
	return m_pVars->GetArray( name );
}

File* Variables::GetFile( const std::string &name )
{
	ASSERT(m_pVars);
	return m_pVars->GetFile( name );
}

RodPtr* Variables::GetRod( const std::string &name )
{
	ASSERT(m_pVars);
	return m_pVars->GetRod( name );
}

HardRodPtr* Variables::GetHardRod( const std::string &name )
{
	ASSERT(m_pVars);
	return m_pVars->GetHardRod( name );
}

SpringPtr* Variables::GetSpring( const std::string &name )
{
	ASSERT(m_pVars);
	return m_pVars->GetSpring( name );
}

DemferPtr* Variables::GetDemfer( const std::string &name )
{
	ASSERT(m_pVars);
	return m_pVars->GetDemfer( name );
}

MassPtr* Variables::GetMass( const std::string &name )
{
	ASSERT(m_pVars);
	return m_pVars->GetMass( name );
}

KnotPtr* Variables::GetKnot( const std::string &name )
{
	ASSERT(m_pVars);
	return m_pVars->GetKnot( name );
}

void Variables::Clear()
{
	ASSERT(m_pVars);
	m_pVars->Clear();
}

VarInteger* Variables::IntMap() const
{
	ASSERT(m_pVars);
	return &m_pVars->m_vInt;
}

VarBool* Variables::BoolMap() const
{
	ASSERT(m_pVars);
	return &m_pVars->m_vBool;
}

VarDouble* Variables::DoubleMap() const
{
	ASSERT(m_pVars);
	return &m_pVars->m_vDouble;
}

VarString* Variables::StringMap() const
{
	ASSERT(m_pVars);
	return &m_pVars->m_vString;
}

errorsT Variables::AssignArray( const std::string &name, const Value &val )
{
//ф-ция заносит в массив с именем name, находящийся в данной карте,
//значение val.
//ВНИМАНИЕ!: name должен быть в нижнем регистре, и действительно быть в карте.
	ASSERT(m_pVars);
	if( !m_pVars )	return NOMEM;
	VarArray::iterator it = m_pVars->m_vArray.find( name );
	ASSERT( it != m_pVars->m_vArray.end() );
	if( (*it).second.GetType() != val.GetArray()->GetType() )
		return CONVERT_ERR;
	(*it).second = *val.GetArray();
	return NOERR;
}

errorsT Variables::AssignMatr( const std::string &name, const Value &val )
{
//ф-ция заносит в матрицу с именем name, находящуюся в данной карте,
//значение val.
//ВНИМАНИЕ!: name должен быть в нижнем регистре, и действительно быть в карте.
	ASSERT(m_pVars);
	if( !m_pVars )	return NOMEM;
	VarMatr::iterator it = m_pVars->m_vMatr.find( name );
	ASSERT( it != m_pVars->m_vMatr.end() );
	//сделано для исключения ссылки на один указатель:
	(*it).second = MatrPtr( *(val.GetMatr()->GetMatr()) );
	return NOERR;
}

bool Variables::IsScript( const std::string &name ) const
{
//ф-ция проверяет - есть ли в данной карте переменная типа СКРИПТ
//с имененем name.
	ASSERT(m_pVars);
	return ( m_pVars->m_vScript.find(name) != m_pVars->m_vScript.end() );
}

bool Variables::IsFile( const std::string &name ) const
{
//ф-ция проверяет - есть ли в данной карте переменная типа ФАЙЛ
//с имененем name.
	ASSERT(m_pVars);
	return ( m_pVars->m_vFile.find(name) != m_pVars->m_vFile.end() );
}

bool Variables::IsElem( TypeID tp )
{
//ф-ция проверяет - является ли tp одним из типов элементов.
	if( (tp == TYPE_ROD)||
		(tp == TYPE_HARDROD)||
		(tp == TYPE_SPRING)||
		(tp == TYPE_DEMFER)||
		(tp == TYPE_MASS) )
		return true;
	return false;
}

TypeID Variables::ArrayType( const std::string &name ) const
{
//ф-ция возвращает тип массива с именем name, хранимого в карте.
//Если такой переменно типа МАССИВ нет, то возвращается TYPE_UNKNOWN.
	ASSERT(m_pVars);
	VarArray::iterator it = m_pVars->m_vArray.find( name );
	if( it != m_pVars->m_vArray.end() )
		return (*it).second.GetType();
	return TYPE_UNKNOWN;
}

