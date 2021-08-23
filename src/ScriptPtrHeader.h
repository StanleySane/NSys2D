/////////////////////////////////////////////////////////////////
//	file ScriptPtrHeader.h
/////////////////////////////////////////////////////////////////

#ifndef _SCRIPT_PTR_HEADER_H_
#define _SCRIPT_PTR_HEADER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include"ScriptDefs.h"

class ScriptObject;
class Value;

class ScriptPtr
{
	ScriptObject *m_pScript;
	std::string m_Name;//имя файла

	void Destruct();
	void InitBy( const ScriptPtr& );
public:
	typedef std::map<ScriptObject*,int> Refs;
	typedef Refs::value_type MakeScriptRef;
	typedef std::pair<Refs::iterator,bool> Pair;
	static Refs m_ScriptRefMap;

	ScriptPtr& operator = ( const ScriptPtr &v )
	{
		if( this != &v )
		{
			InitBy(v);
		}
		return *this;
	}
	ScriptPtr( const ScriptPtr &v ):m_pScript(NULL)
	{
		InitBy(v);
	}
	ScriptPtr():m_pScript(NULL)
	{}
	~ScriptPtr()
	{	Destruct();	}

	//ф-ции-члены
	std::string GetFileName() const;
	std::string GetScriptText() const;
	bool Run() const;
	errorsT GetParam( int, Value& );
	errorsT SetParam( int, const Value& );
	errorsT Construct( const std::string& );
	bool Compile();
	void SetScriptText( const std::string& );
	bool FatalCrash();
	void GetOutput( std::string& );
	void SetDebug(bool);
};

typedef std::map<std::string,ScriptPtr> VarScript;
typedef VarScript::value_type MakeScript;

#endif //_SCRIPT_PTR_HEADER_H_