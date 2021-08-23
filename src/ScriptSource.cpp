// ScriptSource.cpp: implementation of the CScript class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"

#include "ScriptHeader.h"
#include "ScriptObject.h"

#include "ScriptDoc.h"

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScript::CScript()
{
	try
	{
		m_pScript = new ScriptObject();
	}
	catch( bad_alloc& )
	{
		m_pScript = NULL;
	}
}

CScript::~CScript()
{
	delete m_pScript;
}

//////////////////////////////////////////////////////////////////////
//	members
//////////////////////////////////////////////////////////////////////
void CScript::SetDebug( bool flg )
{
	if( m_pScript )
		m_pScript->m_bDebug = flg;
}

bool CScript::GetDebug() const
{
	if( m_pScript )
		return m_pScript->m_bDebug;
	return false;
}

void CScript::SetScriptText( const std::string &txt )
{
	if( m_pScript )
		m_pScript->SetScriptText(txt);
}

bool CScript::Compile()
{
	if( m_pScript )
		return m_pScript->Compile();
	return false;
}

bool CScript::Run()
{
	if( m_pScript )
		return m_pScript->Run();
	return false;
}

void CScript::GetOutput( std::string &str )
{
	if( m_pScript )
		m_pScript->GetOutput( str );
}

bool CScript::FatalCrash()
{
	return ScriptObject::FatalCrash();
}

void CScript::Set( CScriptDoc *p )
{
	if( !m_pScript )
		return;
	m_pScript->Set(p);
}