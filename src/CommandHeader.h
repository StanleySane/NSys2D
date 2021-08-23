/////////////////////////////////////////////////////////////////
//	file CommandHeader.h
/////////////////////////////////////////////////////////////////

#ifndef _COMMAND_HEADER_H_
#define _COMMAND_HEADER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include"ScriptDefs.h"

#include<list>
#include<stack>

class CCommand
{
//класс, базовый для всех CCom...

	CommandID m_CmdID;//идентификатор команды
public:
	CCommand( CommandID id = CMD_NONE )
	{	m_CmdID = id;	}
	virtual ~CCommand() = 0;

	CommandID GetCommandID()
	{	return m_CmdID;	}
};

//собственно откомпилированная последовательность команд:
typedef std::list<CCommand*> Code;
//по аналогии с ассемблером CommandPointer - регистр ip:
typedef Code::iterator CommandPointer;
////////////////////////////////////////////////////////////////
class CmdPos
{
//класс для использования CommandPointer в stack
	void InitBy( const CmdPos &cp )
	{
		m_cp = cp.m_cp;
	}
public:
	CommandPointer m_cp;

	CmdPos& operator = ( const CmdPos &cp )
	{
		if( this == &cp )	return *this;
		InitBy(cp);
		return *this;
	}
	CmdPos( const CmdPos &cp )
	{
		InitBy(cp);
	}
	CmdPos(){}
	CmdPos( const CommandPointer &cp ):m_cp(cp)
	{}
	~CmdPos(){};

	friend bool operator < ( const CmdPos&, const CmdPos& );
	friend bool operator == ( const CmdPos&, const CmdPos& );
};
typedef std::stack<CmdPos> SubStack;

#endif //_COMMAND_HEADER_H_