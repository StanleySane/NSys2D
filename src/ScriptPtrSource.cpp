// ScriptPtrSource.cpp: implementation of the File class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"

#include"ScriptPtrHeader.h"
#include"ScriptObject.h"
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
//	members of ScriptPtr class
//////////////////////////////////////////////////////////////////////
errorsT ScriptPtr::Construct( const std::string &name )
{
	ASSERT( !m_pScript );
	try
	{
		m_pScript = new ScriptObject();
	}
	catch( bad_alloc& )
	{
		return NOMEM;
	}
	m_Name = name;
	Pair p = m_ScriptRefMap.insert( MakeScriptRef(m_pScript,1) );
	if( p.second == false )
	{
		++(*p.first).second;
	}
	return NOERR;
}

void ScriptPtr::Destruct()
{
	if( m_pScript )
	{
		Refs::iterator it = m_ScriptRefMap.find(m_pScript);
		//ASSERT( it != m_ScriptRefMap.end() );
		if( it == m_ScriptRefMap.end() )
		{
			m_pScript = NULL;
			return;
		}
		(*it).second--;
		if( (*it).second == 0 )
		{
			delete m_pScript;
			m_pScript = NULL;
			m_ScriptRefMap.erase(it);
		}
	}
}

void ScriptPtr::InitBy( const ScriptPtr &obj )
{
	if( m_pScript != obj.m_pScript )
	{
		if( m_pScript )
			Destruct();
		m_pScript = obj.m_pScript;
		if( m_pScript )
		{
			Refs::iterator it = m_ScriptRefMap.find(m_pScript);
			ASSERT( it != m_ScriptRefMap.end() );
			(*it).second++;
		}
	}
}

std::string ScriptPtr::GetScriptText() const
{
	ASSERT(m_pScript);
	return m_pScript->GetScriptText();	
}

bool ScriptPtr::Run() const
{
	ASSERT(m_pScript);
	return m_pScript->Run();
}

errorsT ScriptPtr::GetParam( int n, Value &v )
{
	ASSERT(m_pScript);
	return m_pScript->GetParam( n, v );
}

errorsT ScriptPtr::SetParam( int n, const Value &v )
{
	ASSERT(m_pScript);
	return m_pScript->SetParam( n, v );
}

bool ScriptPtr::Compile()
{
	ASSERT(m_pScript);
	return m_pScript->Compile();
}

void ScriptPtr::SetScriptText( const std::string &str )
{
	ASSERT(m_pScript);
	m_pScript->SetScriptText( str );
}

bool ScriptPtr::FatalCrash()
{
	ASSERT(m_pScript);
	return m_pScript->FatalCrash();
}

void ScriptPtr::GetOutput( std::string &str )
{
	ASSERT(m_pScript);
	m_pScript->GetOutput(str);
}

std::string ScriptPtr::GetFileName() const
{
	ASSERT(m_pScript);
	return m_Name;
}

void ScriptPtr::SetDebug( bool flg )
{
	ASSERT(m_pScript);
	m_pScript->m_bDebug = flg;
}