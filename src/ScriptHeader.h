// ScriptHeader.h: interface for the CScript class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIPTHEADER_H__72D04B42_48A7_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_SCRIPTHEADER_H__72D04B42_48A7_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include<string>

class COutputView;
class ScriptObject;
class CScript  
{
	ScriptObject *m_pScript;

	CScript& operator=( const CScript& );
	CScript( const CScript& );
public:
	CScript();
	~CScript();
	//ф-ции члены:
	void SetDebug( bool );
	bool GetDebug() const;
	void SetScriptText( const std::string& );
	bool Compile();
	bool Run();
	void GetOutput( std::string& );
	bool FatalCrash();
	void Set( COutputView* );
};

#endif // !defined(AFX_SCRIPTHEADER_H__72D04B42_48A7_11D6_B89D_FE2BA355A53D__INCLUDED_)
