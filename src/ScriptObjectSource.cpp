// ScriptObjectSource.cpp: implementation of the ScriptObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"

#include "ScriptObject.h"
#include "OutputView.h"
#include "ScriptDoc.h"

/*
#include"AlgolMatr.h"

#include"MatrPtr.h"
#include"RodPtr.h"
#include"HardRodPtr.h"
#include"SpringPtr.h"
#include"DemferPtr.h"
#include"MassPtr.h"
#include"KnotPtr.h"
#include"ShemePtr.h"
*/

#include<cmath>
#include<new>
#include<algorithm>
#include<limits>
#include<cstdarg>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCommand::~CCommand()
{}

ScriptObject::ScriptObject()
{
	m_bDebug = true;
	m_bBreak = false;
	m_pCurrentUserFunc = NULL;
	m_bRunable = false;
	m_pDoc = NULL;
}

ScriptObject::~ScriptObject()
{
	ClearData();
	if( m_pCurrentUserFunc != NULL )
	{
		delete m_pCurrentUserFunc;
		m_pCurrentUserFunc = NULL;
	}
}

inline bool operator < ( const ForLevel &fs1, const ForLevel &fs2 )
{
	return fs1.var < fs2.var;
}
inline bool operator == ( const ForLevel &fs1, const ForLevel &fs2 )
{
	return fs1.var == fs2.var;
}

inline bool operator < ( const CmdPos &cp1, const CmdPos &cp2 )
{
	return cp1.m_cp < cp2.m_cp;
}
inline bool operator == ( const CmdPos &cp1, const CmdPos &cp2 )
{
	return cp1.m_cp == cp2.m_cp;
}

inline bool operator == ( const ScriptData &obj1, const ScriptData &obj2 )
{
	return obj1.FileName == obj2.FileName;
}
inline bool operator != ( const ScriptData &obj1, const ScriptData &obj2 )
{
	return obj1.FileName != obj2.FileName;
}
inline bool operator > ( const ScriptData &obj1, const ScriptData &obj2 )
{
	return obj1.FileName > obj2.FileName;
}
inline bool operator < ( const ScriptData &obj1, const ScriptData &obj2 )
{
	return obj1.FileName < obj2.FileName;
}

std::string FormatString( const char *format, ... )
{
	va_list args;
	char buf[1024];
	va_start( args, format );
	vsprintf( buf, format, args );
	va_end(args);
	return string(buf);
}

void MakeLower( std::string &str )
{
	CString tmp(str.c_str());
	tmp.MakeLower();
	str = static_cast<LPCTSTR>(tmp);
}

bool IsEmptyString( const std::string &str )
{
//ф-ция проверяет - содержит ли str только управляющие символы
	int sz = str.size();
	for( int i = 0; i < sz; i++ )
	{
		if( (str[i]!=' ')&&
			(str[i]!='\r')&&
			(str[i]!='\n')&&
			(str[i]!='\t') )
		{
			return false;
		}
	}	
	return true;
}

void CutEOL( std::string &str )
{
//ф-ция удаляет из строки находящиеся в конце управляющие символы
	if( str.empty() )	return;
	int sz;
	while( (str[sz=(str.size()-1)] == '\r')||
			(str[sz] == '\n')||
			(str[sz] == '\t')||
			(str[sz] == ' ') )
	{
		if( sz == 0 )	break;
		str.erase( sz, 1 );
	}
}
////////////////////////////////////////////////////////////////
bool ScriptObject::FatalCrash()
{
//ф-ция возвращает истину, если произошла фатальная ошибка
//при компиляции или выполнении скрипта, и дальнейшее использование
//данного скрипта невозможно: надо закрыть прогу или перезагрузиться.
	return m_bFatalCrash;
}

void ScriptObject::DestructValList( ValList &lst )
{
	while( !lst.empty() )
	{
		ValList::iterator it = lst.begin();
		if( (*it).first != NULL )
		{
			delete (*it).first;
			(*it).first = NULL;
		}
		if( (*it).second != NULL )
		{
			delete (*it).second;
			(*it).second = NULL;
		}
		lst.erase( it );
	}
}

bool ScriptObject::IsValidAssignment( TypeID tp )
{
//ф-ция проверяет - можно ли переменной типа tp
//что либо присваивать ?
	if( (tp == TYPE_INT)||
		(tp == TYPE_BOOL)||
		(tp == TYPE_DOUBLE)||
		(tp == TYPE_MATR)||
		(tp == TYPE_STRING) )
		return true;
	if( Array::IsArray(tp) )
		return true;
	return false;
}

errorsT ScriptObject::AssignVar( const std::string &name, Variables &VarMap, const Value &val )
{
//ф-ция выполняется только для типов, перечисленных в IsValidAssignment.
//ф-ция заносит в переменную с именем name, находящуюся в карте VarMap,
//значение val. Тип переменной и значения должны быть одинаковы; иначе - ошибка.
//Кроме того, такая переменная действительно должна быть в карте.
	ASSERT( val.Type() != TYPE_UNKNOWN );
	string tmp(name);
	MakeLower(tmp);

	switch( val.Type() )
	{
	case TYPE_INT:
		{
			VarInteger::iterator it = VarMap.IntMap()->find( tmp );
			ASSERT( it != VarMap.IntMap()->end() );
			(*it).second = val.GetInt();
		}
		break;
	case TYPE_BOOL:
		{
			VarBool::iterator it = VarMap.BoolMap()->find( tmp );
			ASSERT( it != VarMap.BoolMap()->end() );
			(*it).second = val.GetBool();
		}
		break;
	case TYPE_DOUBLE:
		{
			VarDouble::iterator it = VarMap.DoubleMap()->find( tmp );
			ASSERT( it != VarMap.DoubleMap()->end() );
			(*it).second = val.GetDouble();
		}
		break;
	case TYPE_STRING:
		{
			VarString::iterator it = VarMap.StringMap()->find( tmp );
			ASSERT( it != VarMap.StringMap()->end() );
			(*it).second = val.GetString();
		}
		break;
	case TYPE_ARRAY_INT:
	case TYPE_ARRAY_DOUBLE:
	case TYPE_ARRAY_BOOL:
	case TYPE_ARRAY_STRING:
		{
			errorsT er = VarMap.AssignArray( tmp, val );
			if( er != NOERR )
				return er;
		}
		break;
	case TYPE_MATR:
		{
			errorsT er = VarMap.AssignMatr( tmp, val );
			if( er != NOERR )
				return er;
		}
		break;
	default:
		ASSERT(FALSE);
		break;
	}//switch(tid)
	return NOERR;
}

void ScriptObject::Set( CScriptDoc *pDoc )
{
	m_pDoc = pDoc;
	if( m_pDoc )
	{
		ASSERT( m_pDoc->m_pView );
		string str( m_pDoc->m_pView->m_Text.LockBuffer() );
		m_pDoc->m_pView->m_Text.UnlockBuffer();
		SetScriptText( str );
	}
}

void ScriptObject::SetOutput( const std::string &str )
{
	m_strOutput = str;
	if( m_pDoc )
	{
		m_pDoc->m_Buf.WriteOut( CString(m_strOutput.c_str()) );
		CSyncObject *pObj[] = {	&m_pDoc->m_Break	};
		CMultiLock Lock( pObj, 1 );
		switch( Lock.Lock(5) )
		{
		case WAIT_OBJECT_0:
			m_bBreak = true;
			break;
		default:
			break;
		}
	}
}

void ScriptObject::GetOutput( std::string &str )
{
	str = m_strOutput;	
	m_strOutput.erase( m_strOutput.begin(), m_strOutput.end() );
}

void ScriptObject::SetScriptText( const std::string &str )
{
	m_bRunable = false;
	m_Text = str;
	m_Text += "\r\n";
}

bool ScriptObject::Compile()
{
	ClearData();
	SetOutput("<--------------------------Compiling of script...--------------------------->\r\n");
	if( m_Text.empty() )
	{
		SetOutput("\r\n<--------------------------Compiling done Ok--------------------------->\r\n");
		return true;
	}
	prog = m_Text.begin();
	m_bRunable = false;
	m_bCompiling = true;
	m_ErrNum = 0;
	m_WarningNum = 0;
	GetNewLabelName(true);
	if( m_pCurrentUserFunc != NULL )
	{
		delete m_pCurrentUserFunc;
		m_pCurrentUserFunc = NULL;
	}
	//компиляция
	try 
	{
		ScanScriptText();
		do
		{
			SBtokensT prev;//показывает какая команда сейчас компилировалась
			token_type = get_token();
			// check for assignment statement 
			switch(token_type)
			{
			case VARIABLE:
				putback(); // return the var to the input stream
				Compile_assignment(); // must be assignment statement
				break;
			case FUNCTION:
				putback(); // return the var to the input stream
				Compile_CallFunc();
				break;
			case TYPE:
				putback(); // return the type to the input stream
				VarDeclare();//объявление переменных
				break;
			case NUMBER://метка
				ChangeCurrentPosition( token );
				break;
				//здесь break не нужен, т.к. сразу должен выполняться default !
			default://какая-то команда
				prev = tok;
				switch( tok )
				{
				case PRINT:
					Compile_print();
					break;
				case GOTO:
					Compile_goto();
					break;
				case IF:
					Compile_if();
					break;
				case FOR:
					Compile_for();
					break;
				case NEXT:
					Compile_next();
					break;
				case GOSUB:
					Compile_gosub();
					break;
				case RETURN:
					Compile_return();
					break;
				case REM:
					Compile_rem();
					break;
				case BREAK:
					Compile_break();
					break;
				case END:
					Compile_end();
					break;
				case UNKNCOM:
					if( tok != EOL )	find_eol();
					ErrMesCompile(SERROR);
					break;
				}// end of switch(tok)
				if( prev == IF )
				{
					m_bIFExec = true;
				}
				else
				{
					m_bIFExec = false;
					if( !m_InternalLabel.empty() )
					{
						InsertInternalLabel();
					}
				}
				break;
			}//switch(token_type)
		} while( tok != FINISHED );
		//проверяем стэки
		if( !m_ForStack.empty() )
		{
			ErrMesCompile(FOR_ERR);
			while( !m_ForStack.empty() )//очистка стека
				m_ForStack.pop();
		}
	} // end of try block
  	catch( errorsT )
	{
		//сюда попадаем только при вызове ErrMesFatal
		m_bCompiling = false;
		if( m_pCurrentUserFunc != NULL )
		{
			delete m_pCurrentUserFunc;
			m_pCurrentUserFunc = NULL;
		}
		return false;
	}
	CompileScripts();
	//если всё в порядке, то можно запускать
	m_bCompiling = false;
	if( m_ErrNum != 0 )
	{
		SetOutput( FormatString("\r\n<--------------------------Compiling done with %d errors------------------------>\r\n", m_ErrNum ) );
		if( m_pCurrentUserFunc != NULL )
		{
			delete m_pCurrentUserFunc;
			m_pCurrentUserFunc = NULL;
		}
		return false;
	}
	SetOutput("\r\n<--------------------------Compiling done Ok--------------------------->\r\n");
	m_bRunable = true;
	if( m_pCurrentUserFunc != NULL )
	{
		delete m_pCurrentUserFunc;
		m_pCurrentUserFunc = NULL;
	}
	return true;
}

bool ScriptObject::Run()
{
	if( !m_bRunable )
	{
		//надо сначала откомпилять
		if( !Compile() )
			return false;
	}
	if( m_Code.empty() )
		return true;
	PrepareCode();
	m_bCompiling = false;
	if( m_bDebug )	return true;
	if( (m_WarningNum != 0)&&
		AfxMessageBox("Запустить скрипт?", MB_TASKMODAL|MB_YESNO|MB_ICONQUESTION ) != IDYES )
		return false;
	m_CurrentPosition = m_Code.begin();
	errorsT res = RunCode(NULL);//запускаем код на исполнение с самого начала
	if( res != NOERR )
	{
		ErrMesRun(res);
	}
	return (res == NOERR)||(res == END_CMD);
}

errorsT ScriptObject::RunCode( Value *val )
{
//ф-ция выполняет код с текущей позиции до появления команд
//END или RETF.
//при появлении RETF ф-ция заносит в *val (если он не нулевой)
//значение выражения, стоящего в RETF.
//если val!=NULL, то значит выполняется пользовательская ф-ция.
	bool finish = false;
	while( !finish )
	{
		errorsT er = NOERR;
		try
		{
			switch( (*m_CurrentPosition)->GetCommandID() )
			{
			case CMD_MOV_EXPR:
				er = Exec_MovExpr( *m_CurrentPosition );
				break;
			case CMD_ADD:
				er = Exec_Add( *m_CurrentPosition );
				break;
			case CMD_PRINT:
				er = Exec_Print( *m_CurrentPosition );
				break;
			case CMD_CMP_VAR_EXPR:
				er = Exec_CmpVarExpr( *m_CurrentPosition );
				break;
			case CMD_CMP_EXPR_VAL:
				er = Exec_CmpExprVal( *m_CurrentPosition );
				break;
			case CMD_JMP:
				er = Exec_Jmp( *m_CurrentPosition );
				break;
			case CMD_JE:
				er = Exec_Je( *m_CurrentPosition );
				break;
			case CMD_JG:
				er = Exec_Jg( *m_CurrentPosition );
				break;
			case CMD_JL:
				er = Exec_Jl( *m_CurrentPosition );
				break;
			case CMD_CALL:
				er = Exec_Call( *m_CurrentPosition );
				break;
			case CMD_PUSH_SUB:
				er = Exec_PushSub( *m_CurrentPosition );
				break;
			case CMD_RET:
				er = Exec_Ret( *m_CurrentPosition );
				break;
			case CMD_RETF:
				if( val == NULL )
				{
					//в главном коде программы (вне любой пользовательской ф-ции)
					//не должна встречаться команда RETF
					return RUN_ERR;
				}
				else
				{
					CComRetf *com = static_cast<CComRetf*>(*m_CurrentPosition);
					(*val) = com->m_expr.GetValue();
					errorsT er = com->m_expr.GetRunErrorCode();
					if( er != NOERR )
						return er;
					finish = true;
				}
				break;
			case CMD_END:
				if( val )	(*val).SetBool(false);
				finish = true;
				return END_CMD;
				break;
			case CMD_LABEL:
				++m_CurrentPosition;
				break;
			default:
				ASSERT(FALSE);
				return RUN_ERR;
				break;
			}//switch
		}
		catch( errorsT er )
		{
			ASSERT(FALSE);
			return er;
		}
		if( er != NOERR )
			return er;
		if( m_bBreak )
			return UNKN_ERR;
	}//while(!finish)
	return NOERR;
}

std::string ScriptObject::GetScriptText() const
{
	return m_Text;
}

std::string ScriptObject::GetScriptParamName( int n )
{
//ф-ция возвращает имя параметра скрипта номер n.
	ASSERT( n > 0 );
	return FormatString("scriptparam%d", n);
}

errorsT ScriptObject::SetParam( int n, const Value &v )
{
//ф-ция задаёт параметру скрипта номер n значение v
	string name = ScriptObject::GetScriptParamName(n);
	TypeID tid = m_Vars.GetVarType( name );
	if( tid == TYPE_UNKNOWN )
		return NOT_VAR;
	Value val;
	val = v;
	if( !val.ConvertTo(tid) )
		return CONVERT_ERR;
	errorsT er;
	er = ScriptObject::AssignVar( name, m_Vars, val );
	ASSERT( er == NOERR );
	return NOERR;
}

errorsT ScriptObject::GetParam( int n, Value &v )
{
//ф-ция заносит в v значение параметра скрипта номер n.
	string name = ScriptObject::GetScriptParamName(n);
	TypeID tid = m_Vars.GetVarType( name );
	if( tid == TYPE_UNKNOWN )
		return NOT_VAR;
	m_Vars.GetVarValue( name, tid, v );
	ASSERT( v.Type() != TYPE_UNKNOWN );
	return NOERR;
}

void ScriptObject::ScanScriptText()
{
//ф-ция сканирует текст скрипта и ищет все метки и 
//объявления пользовательских ф-ций.
	string::iterator temp;

	m_LabelTable.erase( m_LabelTable.begin(), m_LabelTable.end() );
	temp = prog;  // save pointer to top of program 

	// if the first token in the file is a label 
	get_token();
	if( token_type == NUMBER ) 
	{
		m_LabelTable.insert( MakeLabel(token,prog) );
		CComLabel *cmd;
		try
		{
			cmd = new CComLabel( token );
		}
		catch( bad_alloc& )
		{
			ErrMesFatal(NOMEM);
		}
		m_Code.push_back( static_cast<CCommand*>(cmd) );
	}
	else
	{
		if( token_type == TYPE )
		{
			//тогда это возможно объявление пользовательской ф-ции
			string TypeName = token;
			get_token();
			if( !TOKEN_ERR )
			{
				if( tok == USER_FUNC )
				{
					DeclareUserFunc(TypeName);
				}
			}			
		}
	}

	find_eol();
	do
	{
		get_token();
		if( token_type == NUMBER ) 
		{
			if( m_LabelTable.find(token) != m_LabelTable.end() )
			{
				find_eol();
				ErrMesCompile(DUP_LAB);
				continue;
			}
			m_LabelTable.insert( MakeLabel(token,prog) );
			CComLabel *cmd;
			try
			{
				cmd = new CComLabel( token );
			}
			catch( bad_alloc& )
			{
				ErrMesFatal(NOMEM);
			}
			m_Code.push_back( static_cast<CCommand*>(cmd) );
		}
		else
		{
			if( token_type == TYPE )
			{
				//тогда это возможно объявление пользовательской ф-ции
				string TypeName = token;
				get_token();
				if( !TOKEN_ERR )
				{
					if( tok == USER_FUNC )
					{
						DeclareUserFunc(TypeName);
					}
				}			
			}
		}//else

		// if not on a blank line, find next line 
		if( tok != EOL ) find_eol();
	} while( tok != FINISHED );
	prog = temp; // restore original location
	m_CurrentPosition = m_Code.begin();
}

// Find the start of the next line.
void ScriptObject::find_eol()
{
	string::iterator fin = m_Text.end();
	while( (*prog != '\n')&&(prog != fin) ) ++prog;
	if( prog != fin )	++prog;
}


// Find location of given label.  A null is returned
// if label is not found; otherwise a pointer to the
// position of the label is returned.
std::string::iterator ScriptObject::find_label( const std::string &s, bool test/*=false*/)
{
//	test показывает, надо ли проверять найденную метку
//	на возможность разрушения стека циклов и т.п.
//	test == true только при выполнении команды GOTO,
//	т.к., вообще говоря, при вызове GOSUB выполнение
//	возвращается в точку вызова и разрушение стека произойти
//	не может. В этом случае ответственность за сохранность
//	стека циклов лежит целиком на совести юзера,
//	вызвавшего, например, GOTO в подпрограмме.
	Labels::iterator it = m_LabelTable.find(s);
	if( it == m_LabelTable.end() )
	{
		ErrMesCompile(UNDEF_LAB); // label not defined 
		return m_Text.end();
	}
	Labels::referent_type val = (*it).second;//найденное в таблице значение метки
	if( test )
	{
		int count_for = 0;//счётчик, показывающий уровень вложенности циклов,
		// полученный при выполнении данного GOTO. Если count_for > 0, то мы вошли
		// в цикл без его начальной инициализации -> ошибка.
		// если count_for == 0, то ничего делать не надо.
		// если count_for < 0, то это означает выход из нескольких циклов с помощью
		// GOTO и надо проверить число этих циклов.
		// если (-count_for) > m_ForStack.size(), то мы вышли из слишком многих циклов,
		// т.е., скорее всего, нам встретились лишние NEXTы.
		Labels::referent_type temp = prog, until;
		if( prog > val )
		{
			//GOTO назад
			until = prog;
			prog = val;
		}
		else
		{
			//GOTO вперёд
			until = val;
		}
		//проверка:
		do
		{
			get_token();
			if( TOKEN_ERR )
				return m_Text.end();
			if( tok == FINISHED )
			{
				ErrMesCompile(UNKN_ERR);
				return m_Text.end();
			}
			switch( tok )
			{
			case FOR:
				count_for++;
				break;
			case NEXT:
				count_for--;
				break;
			case REM:
			case IF:
				find_eol();
				break;
			}//switch(tok)

		}	while( prog < until );
		prog = temp;
		if( count_for > 0 )
		{
			ErrMesCompile(STACK_CRASH);
			return m_Text.end();
		}
		if( count_for < 0 )
		{
			if( (-count_for) > m_ForStack.size() )
			{
				ErrMesCompile(SERROR);
				return m_Text.end();
			}
		}
	}
	return val;
}

void ScriptObject::VarDeclare()
{
	//сохраняем итератор начала строки
	string::iterator beg = prog;
	//взять имя типа
	get_token();
	if( TOKEN_ERR )
		return;
	string name(token);
	MakeLower(name);

	Types::iterator it = m_TypeTable.find( name );
	if( it == m_TypeTable.end() )
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile(WRONG_SIMBOL);
		ErrMesExpr(name);
		return;
	}
	//проверяем - не определение ли это пользовательской ф-ции?
	get_token();
	if( TOKEN_ERR )	return;
	if( tok == USER_FUNC )
	{
		if( m_pCurrentUserFunc != NULL )
		{
			//если до сих пор разбирается какая-то ф-ция 
			//(т.е. не было команды "END func_name"),
			//и мы пытаемся объявить новую, то ошибка
			if( tok != EOL )	find_eol();
			ErrMesCompile( USER_FUNC_ERR );
			return;
		}
		Compile_UserFunc( (*it).second );
		return;
	}
	else	putback();

	UserFuncTable::iterator ituf;
	if( m_pCurrentUserFunc != NULL )
	{
		//если сейчас компилится пользовательская ф-ция, то
		//переменные надо заносить в её локальную карту
		ituf = m_UserFuncTable.find(m_pCurrentUserFunc->m_name);
		ASSERT( ituf != m_UserFuncTable.end() );
	}
	int cv = 0;//счётчик переменных
	bool err = false;
	for(;;)
	{
		get_token();
		if( TOKEN_ERR )
			return;
		if( tok == EOL || tok == FINISHED )	break;
		if( (token_type != VARIABLE)&&(token_type != OPERATOR) )
		{
			ErrMesCompile( SERROR, false );
			ErrMesExpr( string(beg,prog) );
			err = true;
			continue;
		}
		if( token_type == OPERATOR )
		{
			if( token[0] != ',' )
			{
				ErrMesCompile( SERROR, false );
				ErrMesExpr( string(beg,prog) );
				err = true;
				continue;
			}
		}
		else
		{
			//значит там имя переменной
			string VarName(token);
			MakeLower(token);
			if( IsReservedWord(token) )
			{
				ErrMesCompile( RESERVED_WORD, false );
				ErrMesExpr( string(beg,prog) );
				err = true;
				continue;
			}
			if( IsReDeclare(token) )
			{
				ErrMesCompile( REDECLARE, false );
				ErrMesExpr( string(beg,prog) );
				err = true;
				continue;
			}
			
			string ScriptName;
			if( (*it).second == TYPE_SCRIPT )
			{
				//если это скрипт, то за имененем должно идти имя файла
				get_token();
				if( TOKEN_ERR )
					return;
				if( tok == EOL || tok == FINISHED )
				{
					ErrMesCompile( SERROR, false );
					ErrMesExpr( string(beg,prog) );
					err = true;
					break;
				}
				if( (token_type != OPERATOR)||(token[0] != '(') )
				{
					ErrMesCompile( SERROR, false );
					ErrMesExpr( string(beg,prog) );
					err = true;
					continue;
				}
				//читаем имя
				get_token();
				if( TOKEN_ERR )
					return;
				if( tok == EOL || tok == FINISHED )
				{
					ErrMesCompile( SERROR, false );
					ErrMesExpr( string(beg,prog) );
					err = true;
					break;
				}
				if( token_type != QUOTE )
				{
					ErrMesCompile( SERROR, false );
					ErrMesExpr( token );
					err = true;
				}
				else
				{
					ScriptName = token;
					MakeLower(ScriptName);
				}
				//читаем закрывающую скобку:
				get_token();
				if( TOKEN_ERR )
					return;
				if( tok == EOL || tok == FINISHED )
				{
					ErrMesCompile( SERROR, false );
					ErrMesExpr( string(beg,prog) );
					err = true;
					break;
				}
				if( (token_type != OPERATOR)||(token[0] != ')') )
				{
					ErrMesCompile( SERROR, false );
					ErrMesExpr( string(beg,prog) );
					err = true;
					continue;
				}
			}//if( (*it).second == TYPE_SCRIPT )
			
			Variables *vars = NULL;//указатель на карту переменных, куда заносятся разбираемые
			if( m_pCurrentUserFunc != NULL )
			{
				//если сейчас компилится пользовательская ф-ция, то
				//переменные надо заносить в её локальную карту
				string ParamName(token);
				MakeLower(ParamName);
				ParamList::iterator itp = (*ituf).second.m_Params.begin();
				while( itp != (*ituf).second.m_Params.end() )
				{
					if( (*itp).m_name == ParamName )
					{
						ErrMesCompile( REDECLARE, false );
						ErrMesExpr( string(beg,prog) );
						err = true;
						break;;
					}
					++itp;
				}//while
				vars = &(*ituf).second.m_LocalVars;
			}
			else
			{
				//иначе в глобальное пр-во имён
				vars = &m_Vars;
			}
			vars->AddVar( VarName, (*it).second );
			
			if( !ScriptName.empty() )
			{
				//если сейчас разбирается объявление скриптов,
				//то надо прочитанную переменную позже проинициализировать,
				//а пока запомнить имя файла
				ASSERT( vars->IsScript(VarName) );
				ScriptData dat;
				dat.FileName = ScriptName;
				dat.VarName = VarName;
				m_ScriptList.push_back( dat );
			}			
			cv++;
		}

	}//	while( token[0] != ')' );

	if( tok != EOL && tok != FINISHED )
	{
		//если не пусто, то что-то не то
		ErrMesCompile( SERROR, false );
		ErrMesExpr( string(beg,prog) );
		err = true;
		find_eol();
	}
	if( cv == 0 )
	{
		ErrMesCompile( SERROR, false );
		ErrMesExpr( string(beg,prog) );
		err = true;
	}
	if( err )
	{
		ErrMesCompile(CERROR);
	}
}

void ScriptObject::DeclareUserFunc( const std::string &tpname )
{
//ф-ция разбирает заголовок пользовательской ф-ции
//и заносит информацию о ф-ции в спец.карту.
	Types::iterator itt = m_TypeTable.find(tpname);
	ASSERT( itt != m_TypeTable.end() );
	TypeID tp = (*itt).second;

	//взять имя ф-ции
	get_token();
	if( TOKEN_ERR )	return;

	string name(token);
	if( IsReservedWord(name) )
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile( RESERVED_WORD );
		ErrMesExpr( name );
		return;
	}
	if( IsReDeclare(name) )
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile( REDECLARE );
		ErrMesExpr( name );
		return;
	}
	MakeLower(name);

	get_token();
	if( TOKEN_ERR )	return;
	if( token[0] != '(' )
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile(SERROR);
		return;
	}
	UserFunc uf;
	uf.m_RetType = tp;//тип возвращаемого значения 
	//читаем параметры
	do
	{
		//тип
		get_token();
		if( TOKEN_ERR )	return;
		if( tok == EOL || tok == FINISHED )	break;
		if( token_type != TYPE )
		{
			if( token[0] == ')' )	break;
			if( tok != EOL )	find_eol();
			ErrMesCompile( SERROR );
			return;
		}
		Types::iterator it = m_TypeTable.find(token);
		TypeID tPar = (*it).second;//тип параметра
		//имя
		get_token();
		if( TOKEN_ERR )	return;
		if( tok == EOL || tok == FINISHED )	break;
		if( token_type != VARIABLE )
		{
			if( tok != EOL )	find_eol();
			ErrMesCompile( SERROR );
			return;
		}
		string VarName(token);
		if( IsReservedWord(VarName) )
		{
			if( tok != EOL )	find_eol();
			ErrMesCompile( RESERVED_WORD );
			ErrMesExpr( VarName );
			return;
		}
		MakeLower(VarName);
		//запятая или конец разбора
		get_token();
		if( TOKEN_ERR )	return;
		if( tok == EOL || tok == FINISHED )	break;
		if( token_type != OPERATOR )
		{
			if( tok != EOL )	find_eol();
			ErrMesCompile( SERROR );
			return;
		}
		if( token[0] != ')' )
		{
			if( token[0] != ',' )
			{
				if( tok != EOL )	find_eol();
				ErrMesCompile( SERROR );
				return;
			}
		}
		UserFuncParam fp;
		fp.m_tType = tPar;//тип пар-ра
		fp.m_name = VarName;//имя переменной
		uf.m_Params.push_back(fp);
		uf.m_LocalVars.AddVar( VarName, tPar );

	}	while( token[0] != ')' );

	if( tok == EOL || tok == FINISHED )
	{
		ErrMesCompile(PARENS);
		return;
	}
	get_token();//взять дальше за закрывающейся скобкой
	if( TOKEN_ERR )	return;
	if( tok != EOL && tok != FINISHED )
	{
		//если не пусто, то что-то не то
		find_eol();
		ErrMesCompile(SERROR);
		return;
	}	
	uf.m_label = GetNewLabelName();//имя метки начала тела ф-ции
	m_UserFuncTable.insert( MakeUserFunc(name,uf) );
}

void ScriptObject::CompileScripts()
{
//ф-ция компилирует все, включённые в программу, скрипты.
	ScriptList::iterator it = m_ScriptList.begin(), fin = m_ScriptList.end();
	for(; it != fin; ++it )
	{
		Variables *vars = GetVarTable( (*it).VarName );
		TypeID tid = vars->GetVarType( (*it).VarName );
		ASSERT( tid != TYPE_UNKNOWN );
		ScriptPtr *pScr = vars->GetScript( (*it).VarName );
		ASSERT( pScr );
		errorsT er = pScr->Construct( (*it).FileName );
		if( er != NOERR )
		{
			ErrMesCompile(er);
			continue;
		}
		//читаем файл:
		FILE *f;
		if( (f = fopen( (*it).FileName.c_str(), "rb")) == NULL )
		{
			ErrMesCompile(FILE_OPEN);
			continue;
		}
		string tmp;
		for( int ch = getc(f); !feof(f); ch = getc(f) )
		{
			tmp += ch;
		}
		fclose(f);
		//задаём текст:
		pScr->SetScriptText( tmp );
		tmp = FormatString("\r\n<-----------Compiling of module %s ...------------>\r\n", (*it).FileName.c_str() );
		SetOutput( tmp );
		//компилим:
		bool res = pScr->Compile();
		if( res == false )
		{
			if( pScr->FatalCrash() )
				ErrMesFatal(UNKN_ERR);
		}
		//читаем вывод:
		pScr->GetOutput(tmp);
		SetOutput( tmp );
		tmp = FormatString("\r\n<-----------Compiling of module %s done------------>\r\n", (*it).FileName.c_str() );
		SetOutput( tmp );
		if( res == false )
			ErrMesCompile(CERROR);
	}
}

void ScriptObject::Compile_UserFunc( TypeID tp )
{
//tp - тип возвращаемого значения
	//взять имя ф-ции
	get_token();
	if( TOKEN_ERR )	return;

	string name(token);
	MakeLower(name);

	UserFuncTable::iterator it = m_UserFuncTable.find(name);
	if( it == m_UserFuncTable.end() )
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile( SERROR );
		return;
	}
	ASSERT( tp == (*it).second.m_RetType );
	find_eol();

	try
	{
		m_pCurrentUserFunc = new CurrentUserFunc();
	}
	catch( bad_alloc& )
	{
		m_pCurrentUserFunc = NULL;
		ErrMesFatal(NOMEM);
	}
	m_pCurrentUserFunc->m_label = GetNewLabelName();
	m_pCurrentUserFunc->m_name = name;
	m_pCurrentUserFunc->m_RetType = tp;
	m_pCurrentUserFunc->m_Start = (*it).second.m_label;

	CComJmp *cmdJmp;
	try
	{			
		cmdJmp = new CComJmp( m_pCurrentUserFunc->m_label );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdJmp) );
	CComLabel *cmdLab;
	try
	{
		cmdLab = new CComLabel( m_pCurrentUserFunc->m_Start );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdLab) );
}

void ScriptObject::Compile_CallFunc()
{
	string::iterator beg = prog;
	find_eol();
	string str_func = string(beg,prog);
	Expression name( str_func, this );
	errorsT er = name.GetCompileErrorCode();
	if( er != NOERR )
	{
		ErrMesExpr( str_func );
		ErrMesCompile( er );
		return;
	}

	CComCall *cmd;
	try
	{
		cmd = new CComCall( name );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmd) );
}

void ScriptObject::Compile_end()
{
	get_token();//взять дальше
	if( TOKEN_ERR )	return;
	if( tok != EOL && tok != FINISHED )
	{
		//если не пусто, то проверяем - разбирается ли сейчас пользовательская
		//ф-ция?
		if( m_pCurrentUserFunc != NULL )
		{
			string fn(token);
			MakeLower(fn);
			if( fn != m_pCurrentUserFunc->m_name )
			{
				find_eol();
				ErrMesCompile( WRONG_END );
				return;
			}
			get_token();//взять дальше
			if( TOKEN_ERR )	return;
			if( tok != EOL && tok != FINISHED )
			{
				//если опять не пусто, то точно ошибка!
				find_eol();
				ErrMesCompile(SERROR);
				return;
			}
		}
		else
		{
			find_eol();
			ErrMesCompile(SERROR);
			return;
		}
	}

	if( m_pCurrentUserFunc == NULL )
	{
		CComEnd *cmd;
		try
		{
			cmd = new CComEnd();
		}
		catch( bad_alloc& )
		{
			ErrMesFatal(NOMEM);
		}
		m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmd) );
	}
	else
	{
		if( !m_pCurrentUserFunc->m_bIsReturn )
		{
			//если в разобранной ф-ции ни разу не вызывался return,
			//то это ошибка: все пользовательские ф-ции должны возвращать значение
			if( tok != EOL )	find_eol();
			ErrMesCompile( NO_USER_RETURN );
			return;
		}
		CComLabel *cmd;
		try
		{
			cmd = new CComLabel( m_pCurrentUserFunc->m_label );
		}
		catch( bad_alloc& )
		{
			ErrMesFatal(NOMEM);
		}
		m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmd) );
		if( m_pCurrentUserFunc != NULL )
		{
			delete m_pCurrentUserFunc;
			m_pCurrentUserFunc = NULL;
		}
	}
}

// Assign a variable a value.
void ScriptObject::Compile_assignment()
{
	// get the variable name
	get_token();
	if( TOKEN_ERR )
		return;
	if(!isalpha(token[0])) 
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile(NOT_VAR);
		return;
	}

	TypeID tp = IsVariable(token);
	if( tp == TYPE_UNKNOWN )
	{
		//нет такой переменной
		if( tok != EOL )	find_eol();
		ErrMesCompile(WRONG_SIMBOL);
		ErrMesExpr(token);
		return;
	}
	string var(token);//имя переменной

	// get the equal sign
	get_token();
	if( token[0] != '=' )
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile(EQUAL_EXP);
		return;
	}

	//проверяем - можно ли присваивать переменной данного типа
	if( !ScriptObject::IsValidAssignment(tp) )
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile(TYPE_OP_ERR);
		return;
	}

	string::iterator it1 = prog;
	if( tok != EOL )	find_eol();
	string::iterator it2 = prog;
	string str_expr( it1, it2 );

	Expression Expr( str_expr, this );
	errorsT er = Expr.GetCompileErrorCode();
	if( er != NOERR )
	{
		ErrMesExpr( str_expr );
		ErrMesCompile(er);
		return;
	}

	CComMovExpr *cmd;
	try
	{
		cmd = new CComMovExpr( var, Expr );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
		return;
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmd) );
}

void ScriptObject::Compile_break()
{
	if( m_ForStack.empty() )
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile(BREAK_ERR);
		return;
	}
	get_token();//взять дальше
	if( TOKEN_ERR )	return;
	if( tok != EOL && tok != FINISHED )
	{
		//если не пусто, то что-то не то
		find_eol();
		ErrMesCompile(SERROR);
		return;
	}
	ForLevel stckvar;
	stckvar = m_ForStack.top(); // read the loop info

	CComJmp *cmd;
	try
	{
		cmd = new CComJmp( stckvar.lab2 );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmd) );
	if( !m_bIFExec )
	{
		//очищаем стэк от информации об этом самом FOR/NEXT
		m_ForStack.pop();
	}
}

void ScriptObject::Compile_rem()
{
	if( tok != EOL )	find_eol();
	return;
}

// Execute a simple version of the BASIC PRINT statement.
void ScriptObject::Compile_print()
{
	////////////////////////////////////////////////////////////////
	string::iterator from = prog;
	if( tok != EOL )	find_eol();
	string::iterator to = prog;
	string prnt( from, to );
	CutEOL(prnt);
	from = prnt.begin();
	to = prnt.end();
	if( from != to )
	{
		string::iterator temp = to;
		--temp;
		if( *temp == '\n' || *temp == '\r' )
			to = temp;
	}

	Expression::PassSpaces( from, to );
	PrintList lst;
	if( from != to )
	{
		//с параметрами
		for(;;)
		{
			//читаем пар-ры
			char opers[] = ",;";
			string::iterator OperBeg = from;
			errorsT er = Expression::FindOperation( opers, from, to );
			if( er != NOERR )
			{
				ErrMesCompile( er );
				return;
			}
			char last_delim = (strchr(opers,*from)&&(*from!='\0'))?(*from):(' ');//разделитель

			string tmp( OperBeg, from );
			Expression par( tmp, this );
			er = par.GetCompileErrorCode();
			if( er != NOERR )
			{
				ErrMesExpr( tmp );
				ErrMesCompile( er );
				return;
			}
			lst.push_back( make_pair(par,last_delim) );
			if( from == to )	break;
			++from;//указатель на символ, стоящий вслед за запятой
			Expression::PassSpaces( from, to );
		}//for(;;)
	}
	////////////////////////////////////////////////////////////////
	CComPrint *cmd;
	try
	{
		cmd = new CComPrint( lst );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmd) );
}

// Execute a GOTO statement. 
void ScriptObject::Compile_goto()
{
	string::iterator loc;

	get_token(); // get label to go to 
	if( TOKEN_ERR )
		return;

	// find the location of the label 
	loc = find_label( token, true );
	if( loc == m_Text.end() )
	{
		return; 
	}
	else
	{
		CComJmp *cmd;
		try
		{
			cmd = new CComJmp( token );
		}
		catch( bad_alloc& )
		{
			ErrMesFatal(NOMEM);
		}
		m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmd) );
	}
}

// Execute an IF statement.
void ScriptObject::Compile_if()
{
	string lab = GetNewLabelName();
	string::iterator from = prog, to;
	for(;;)
	{
		get_token();
		if( TOKEN_ERR )
			return;
		if( (tok==EOL)||(tok==FINISHED) )
		{
			//какая-то синтаксическая ошибка
			//значит надо продолжить разбор без получения выражения,
			//т.к. оно теперь не понадобится из-за ошибки
			prog = from;
			break;
		}
		if( tok == THEN )
		{
			putback();
			to = prog;
			string str_expr( from, to );
			str_expr += "\r\n";
			if( IsEmptyString(str_expr) )
			{
				prog = from;
				find_eol();
				ErrMesCompile(SERROR);
				return;
			}
			Expression Expr( str_expr, this );
			errorsT er = Expr.GetCompileErrorCode();
			if( er != NOERR )
			{
				ErrMesExpr( str_expr );
				ErrMesCompile( er );
				return;
			}
			
			CComCmpExprVal *cmd;
			try
			{
				Value val;
				val.SetBool(false);
				cmd = new CComCmpExprVal( Expr, val );
			}
			catch( bad_alloc& )
			{
				ErrMesFatal(NOMEM);
			}
			m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmd) );
			CComJe *cmdJe;			
			try
			{				
				cmdJe = new CComJe( lab );
			}
			catch( bad_alloc& )
			{
				ErrMesFatal(NOMEM);
			}
			m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdJe) );
			break;
		}
	}

	get_token();
	if( tok != THEN )
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile(THEN_EXP);
		return;
	} // else, target statement will be executed 
	get_token();
	if( TOKEN_ERR )
		return;
	if( tok == EOL )
	{
		//после then должно что-нибудь стоять
		ErrMesCompile( MISSING_IF_CMD );
		return;
	}
	if( tok == FOR )
	{
		//нельзя использовать IF ... THEN FOR ...
		find_eol();
		ErrMesCompile( IF_CMD_ERR );
		return;
	}
	putback();
	//делаем метку о том, что после следующей команды должна быть
	//вставлена внутренняя метка:
	m_InternalLabel = lab;
}

// Execute a FOR loop. 
void ScriptObject::Compile_for()
{
	ForLevel stckvar(this);

	get_token(); // read the control variable 
	if(!isalpha(token[0])) 
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile(NOT_VAR);
		return;
	}
	TypeID tid = IsVariable(token);
	if( tid == TYPE_UNKNOWN )
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile(WRONG_SIMBOL);
		ErrMesExpr(token);
		return;
	}
	else
	{
		if( tid != TYPE_INT )
		{
			if( tok != EOL )	find_eol();
			ErrMesCompile(TYPE_OP_ERR);
			ErrMesExpr(token);
			return;
		}
	}

	string tmp(token);
	MakeLower(tmp);
	stckvar.var = tmp;

	get_token(); // read the equal sign
	if( token[0] != '=' )
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile(EQUAL_EXP);
		return;
	}

	Value StartValue;//значения параметров цикла, если все они константы

	string lab1 = GetNewLabelName(), lab2 = GetNewLabelName();
	string lab3 = GetNewLabelName(), lab4 = GetNewLabelName();
	stckvar.lab1 = lab1;
	stckvar.lab2 = lab2;
	string::iterator from = prog, to;
	for(;;)
	{
		get_token();
		if( TOKEN_ERR )
			return;
		if( (tok==EOL)||(tok==FINISHED) )
		{
			//какая-то синтаксическая ошибка
			//значит надо продолжить разбор без получения выражения,
			//т.к. оно теперь не понадобится из-за ошибки
			prog = from;
			break;
		}
		if( tok == TO )
		{
			putback();
			to = prog;
			string str_expr( from, to );

			if( IsEmptyString(str_expr) )
			{
				prog = from;
				find_eol();
				ErrMesCompile(SERROR);
				return;
			}
			Expression Expr( str_expr, this );
			errorsT er = Expr.GetCompileErrorCode();
			if( er != NOERR )
			{
				ErrMesExpr( str_expr );
				ErrMesCompile(er);
				return;
			}
			if( Expr.IsConstant() )
			{
				StartValue = Expr.GetValue(TYPE_INT);
				ASSERT( Expr.GetRunErrorCode() == NOERR );
			}

			CComMovExpr *cmdMov;
			try
			{
				cmdMov = new CComMovExpr( stckvar.var, Expr );
			}
			catch( bad_alloc& )
			{
				ErrMesFatal(NOMEM);
			}
			m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdMov) );
			CComLabel *cmdLabel;
			try
			{
				cmdLabel = new CComLabel( lab1 );
			}
			catch( bad_alloc& )
			{
				ErrMesFatal(NOMEM);
			}
			m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdLabel) );
			break;
		}
	}

	get_token();
	if( TOKEN_ERR )
		return;
	if( tok != TO )	
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile(TO_EXP); // read and discard the TO
		return;
	}

	from = prog;
	Expression target(this);
	Value TargetValue;
	for(;;)
	{
		get_token();
		if( TOKEN_ERR )
			return;
		if( (tok==EOL)||(tok == STEP)||(tok==FINISHED) )
		{
			putback();
			to = prog;
			string expr = string(from,to);
			//проверяем, содержит ли target чтонибудь "полезное":
			if( IsEmptyString(expr) )
			{
				prog = from;
				find_eol();
				ErrMesCompile(TARGET_EXP);
				return;
			}
			errorsT er;
			if( (er = target.Reset(expr)) != NOERR )
			{
				ErrMesExpr(expr);
				ErrMesCompile(er);
				return;
			}
			if( target.IsConstant() )
			{
				TargetValue = target.GetValue(TYPE_INT);
				ASSERT( target.GetRunErrorCode() == NOERR );
			}
			break;
		}
	}

	get_token(); //прочитать шаг
	if( TOKEN_ERR )
		return;
	if( tok == STEP )
	{
		from = prog;
		for(;;)
		{
			get_token();
			if( TOKEN_ERR )
				return;
			if( (tok==EOL)||(tok==FINISHED) )
			{
				putback();
				to = prog;
				break;
			}
		}//for(;;)
		string Step = string(from,to);
		//проверяем, содержит ли stckvar.step чтонибудь "полезное":
		if( IsEmptyString(Step) )
		{
			prog = from;
			find_eol();
			ErrMesCompile(STEP_ERR);
			return;
		}
		errorsT er;
		if( (er = stckvar.step.Reset(Step)) != NOERR )
		{
			ErrMesExpr( Step );
			ErrMesCompile(er);
			return;
		}
	}
	else	
	{
		putback();
		string Step = string("1");
		errorsT er;
		if( (er = stckvar.step.Reset(Step)) != NOERR )
		{
			ErrMesExpr(Step);
			ErrMesCompile(er);
			return;
		}
	}

	if( stckvar.step.IsConstant() )
	{
		Value StepValue = stckvar.step.GetValue(TYPE_INT);
		ASSERT( stckvar.step.GetRunErrorCode() == NOERR );
		if( (StartValue.Type() != TYPE_UNKNOWN)&&
			(TargetValue.Type() != TYPE_UNKNOWN)&&
			(StepValue.Type() != TYPE_UNKNOWN) )
		{
			//все константы
			ASSERT( (StartValue.Type() == TYPE_INT)&&
					(TargetValue.Type() == TYPE_INT)&&
					(StepValue.Type() == TYPE_INT) );
			if( StartValue.GetInt() == TargetValue.GetInt() )
			{
				ErrMesWarning(ONE_TIME_CYCLE);
			}
			else
			{
				if( StartValue.GetInt() < TargetValue.GetInt() )
				{
					if( StepValue.GetInt() < 0 )
						ErrMesWarning(NO_CYCLE);
					else
					{
						if( StepValue.GetInt() == 0 )
							ErrMesWarning(FOREVER_CYCLE);
					}
				}
				else
				{
					if( StepValue.GetInt() > 0 )
						ErrMesWarning(NO_CYCLE);
					else
					{
						if( StepValue.GetInt() == 0 )
							ErrMesWarning(FOREVER_CYCLE);
					}
				}
			}
		}
	}

	CComCmpExprVal *cmdCmpStep;
	try
	{
		Value val;
		val.SetInt(0);
		cmdCmpStep = new CComCmpExprVal( stckvar.step, val );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdCmpStep) );
	CComJl *cmdJl;
	try
	{				
		cmdJl = new CComJl( lab3 );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdJl) );
	CComCmpVarExpr *cmdCmp;
	try
	{
		cmdCmp = new CComCmpVarExpr( stckvar.var, target );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdCmp) );
	CComJg *cmdJg;
	try
	{				
		//lab2 - метка за рамками цикла (сразу за next)
		cmdJg = new CComJg( lab2 );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdJg) );
	CComJmp *cmdJmp;
	try
	{			
		cmdJmp = new CComJmp( lab4 );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdJmp) );
	CComLabel *cmdLabel3;
	try
	{
		cmdLabel3 = new CComLabel( lab3 );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdLabel3) );
	CComCmpVarExpr *cmdCmp2;
	try
	{
		cmdCmp2 = new CComCmpVarExpr( stckvar.var, target );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdCmp2) );
	CComJl *cmdJl2;
	try
	{				
		cmdJl2 = new CComJl( lab2 );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdJl2) );
	CComLabel *cmdLabel4;
	try
	{
		cmdLabel4 = new CComLabel( lab4 );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdLabel4) );

	m_ForStack.push(stckvar);
}

// Execute a NEXT statement. 
void ScriptObject::Compile_next()
{
	if( m_ForStack.empty() )
	{
		if( tok != EOL )	find_eol();
		ErrMesCompile(NEXT_WO_FOR);
		return;
	}

	ForLevel stckvar = m_ForStack.top(); // read the loop info
	//берём имя переменной цикла
	get_token();
	if( TOKEN_ERR )	return;
	//если там пусто, то значит выполняется NEXT для текущего цикла
	if( (tok != EOL)&&(tok != FINISHED) )
	{
		//иначе надо проверить имя переменной
		string name(token);
		MakeLower(name);
		string tmp(stckvar.var);
		CutEOL(tmp);
		if( name != tmp )
		{
			find_eol();
			ErrMesCompile( NEXT_VAR_ERR );
			return;
		}
		get_token();//взять дальше
		if( TOKEN_ERR )	return;
		if( tok != EOL && tok != FINISHED )
		{
			//если опять не пусто, то точно ошибка!
			find_eol();
			ErrMesCompile(SERROR);
			return;
		}
	}

	CComAdd *cmdAdd;
	try
	{
		cmdAdd = new CComAdd( stckvar.var, stckvar.step );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdAdd) );
	CComJmp *cmdJmp;
	try
	{
		cmdJmp = new CComJmp( stckvar.lab1 );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdJmp) );

	if( !m_bIFExec )
	{
		//если данный NEXT выполняется в рамках команды IF,
		//то выталкивать из стэка информацию об циклах не надо.
		//иначе надо:
		m_ForStack.pop();

		CComLabel *cmdLab;
		try
		{
			cmdLab = new CComLabel( stckvar.lab2 );
		}
		catch( bad_alloc& )
		{
			ErrMesFatal(NOMEM);
		}
		m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdLab) );
	}
	if( tok != EOL )	find_eol();
}

void ScriptObject::Compile_gosub()
{
	string::iterator loc;

	get_token();
	if( TOKEN_ERR )
		return;

	// find the label to call
	loc = find_label(token);
	if( loc == m_Text.end() )
	{
		return;
	}
	else 
	{
		string lab = GetNewLabelName();//получаем имя новой внутренней метки
		CComPushSub *cmdPush;
		try
		{
			cmdPush = new CComPushSub( lab );
		}
		catch( bad_alloc& )
		{
			ErrMesFatal(NOMEM);
		}
		m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdPush) );
		CComJmp *cmd;
		try
		{
			cmd = new CComJmp( token );
		}
		catch( bad_alloc& )
		{
			ErrMesFatal(NOMEM);
		}
		m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmd) );
		//вставляем вслед за jmp метку для возврата по return
		CComLabel *cmdLab;
		try
		{
			cmdLab = new CComLabel( lab );
		}
		catch( bad_alloc& )
		{
			ErrMesFatal(NOMEM);
		}
		m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmdLab) );
	}
}

// Return from GOSUB.
void ScriptObject::Compile_return()
{
	get_token();//взять дальше
	if( TOKEN_ERR )	return;
	Expression Expr(this);
	if( tok != EOL && tok != FINISHED )
	{
		//если не пусто, то проверяем - разбирается ли сейчас пользовательская
		//ф-ция?
		if( m_pCurrentUserFunc != NULL )
		{
			putback();
			string::iterator it1 = prog;
			find_eol();
			string::iterator it2 = prog;
			string str_expr = string( it1, it2 );//возвращаемое выражение

			if( IsEmptyString(str_expr) )
			{
				ErrMesCompile(SERROR);
				return;
			}
			errorsT er;
			if( (er = Expr.Reset(str_expr)) != NOERR )
			{
				ErrMesExpr(str_expr);
				ErrMesCompile(er);
				return;
			}
		}
		else
		{
			find_eol();
			ErrMesCompile(SERROR);
			return;
		}
	}

	if( m_pCurrentUserFunc == NULL )
	{
		CComRet *cmd;
		try
		{
			cmd = new CComRet();
		}
		catch( bad_alloc& )
		{
			ErrMesFatal(NOMEM);
		}
		m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmd) );
	}
	else
	{
		if( !m_bIFExec )
		{
			//если данный RETURN выполняется в рамках команды IF,
			//то выставлять флаг m_bIsReturn не надо.
			//иначе надо:
			m_pCurrentUserFunc->m_bIsReturn = true;
		}
		CComRetf *cmd;
		try
		{
			cmd = new CComRetf(Expr);
		}
		catch( bad_alloc& )
		{
			ErrMesFatal(NOMEM);
		}
		m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmd) );
	}
}

errorsT ScriptObject::Exec_MovExpr( CCommand *cmd )
{
	CComMovExpr *com = static_cast<CComMovExpr*>(cmd);
	string tmp(com->m_name);
	CutEOL(tmp);
	TypeID tid = IsVariable(tmp);
	ASSERT( tid != TYPE_UNKNOWN );//такого не должно происходить, т.к. при компиляции
	//проверяется наличие переменной

	Value val = com->m_expr.GetValue(tid);//значение выражения
	errorsT er = com->m_expr.GetRunErrorCode();
	if( er != NOERR )
		return er;

	Variables *vars = GetVarTable(tmp);
	er = ScriptObject::AssignVar( tmp, (*vars), val );
	if( er != NOERR )
	{
		ErrMesRun(er);
	}

	++m_CurrentPosition;
	return NOERR;
}

errorsT ScriptObject::Exec_Add( CCommand *cmd )
{
	CComAdd *com = static_cast<CComAdd*>(cmd);
	Value val = com->m_val.GetValue(TYPE_INT);//значение выражения
	errorsT er = com->m_val.GetRunErrorCode();
	if( er != NOERR )
		return er;
	string tmp(com->m_name);
	CutEOL(tmp);
	Variables *vars = GetVarTable(tmp);
	ASSERT( vars->GetVarType(tmp) == TYPE_INT );
	VarInteger::iterator it = vars->IntMap()->find(tmp);
	ASSERT( it != vars->IntMap()->end() );
	//- такого не должно происходить, т.к. при компиляции
	//проверяется наличие переменной
	it->second += val.GetInt();

	++m_CurrentPosition;
	return NOERR;
}

errorsT ScriptObject::Exec_Print( CCommand *cmd )
{
	CComPrint *com = static_cast<CComPrint*>(cmd);

	PrintList::iterator it = com->m_expr.begin(), fin = com->m_expr.end();
	char last_delim = '\0';
	int len = 0;
	while( it != fin )
	{
		Value res;
		res = (*it).first.GetValue();
		errorsT er = (*it).first.GetRunErrorCode();
		if( er != NOERR )
			return er;
		string str = res.StringVariant();
		SetOutput( str );
		len += str.length();
		last_delim = (*it).second;
		if( last_delim == ',' )
		{
			int spaces = TAB_SIZE - (len % TAB_SIZE); 
			len += spaces;
			while(spaces)
			{
				SetOutput(" ");
				spaces--;
			}
		}
		else
		{
			if( last_delim == ';' )
			{
				//SetOutput("");
				len += 0;
			}
		}
		++it;
	}//while(it!=fin)
	if( last_delim != ';' && last_delim != ',' )
	{
		SetOutput("\r\n");
	}

	++m_CurrentPosition;
	return NOERR;
}

errorsT ScriptObject::Exec_CmpVarExpr( CCommand *cmd )
{
	CComCmpVarExpr *com = static_cast<CComCmpVarExpr*>(cmd);
	Value val1 = find_var( com->m_name );
	if( val1.Type() == TYPE_UNKNOWN )
		return NOT_VAR;
	Value val2 = com->m_expr.GetValue(TYPE_INT);
	errorsT er = com->m_expr.GetRunErrorCode();
	if( er != NOERR )
		return er;
	try
	{
		if( val1 == val2 )
			m_Flag = FLG_EQ;
		else
		{
			if( val1 > val2 )
				m_Flag = FLG_GT;
			else
				m_Flag = FLG_LT;
		}
	}
	catch( errorsT et )
	{
		return et;
	}
	++m_CurrentPosition;
	return NOERR;
}

errorsT ScriptObject::Exec_CmpExprVal( CCommand *cmd )
{
	CComCmpExprVal *com = static_cast<CComCmpExprVal*>(cmd);
	Value val1 = com->m_expr.GetValue(com->m_val.Type());
	errorsT er = com->m_expr.GetRunErrorCode();
	if( er != NOERR )
		return er;
	Value val2 = com->m_val;

	//здесь не проверяем правильность приведения, 
	//т.к. BOOL к INT всегда можно привести !
	if( val1.Type() == TYPE_BOOL )
		val1.ConvertTo( TYPE_INT );
	if( val2.Type() == TYPE_BOOL )
		val2.ConvertTo( TYPE_INT );
	try
	{
		if( val1 == val2 )
			m_Flag = FLG_EQ;
		else
		{
			if( val1 > val2 )
				m_Flag = FLG_GT;
			else
				m_Flag = FLG_LT;
		}
	}
	catch( errorsT et )
	{
		return et;
	}
	++m_CurrentPosition;
	return NOERR;
}

errorsT ScriptObject::Exec_Jmp( CCommand *cmd )
{
	CComJmp *com = static_cast<CComJmp*>(cmd);
	m_CurrentPosition = com->m_cp;
	return NOERR;
}

errorsT ScriptObject::Exec_Je( CCommand *cmd )
{
	CComJe *com = static_cast<CComJe*>(cmd);
	if( m_Flag == FLG_EQ )
		m_CurrentPosition = com->m_cp;
	else
		++m_CurrentPosition;
	return NOERR;
}

errorsT ScriptObject::Exec_Jg( CCommand *cmd )
{
	CComJg *com = static_cast<CComJg*>(cmd);
	if( m_Flag == FLG_GT )
		m_CurrentPosition = com->m_cp;
	else
		++m_CurrentPosition;
	return NOERR;
}

errorsT ScriptObject::Exec_Jl( CCommand *cmd )
{
	CComJl *com = static_cast<CComJl*>(cmd);
	if( m_Flag == FLG_LT )
		m_CurrentPosition = com->m_cp;
	else
		++m_CurrentPosition;
	return NOERR;
}

errorsT ScriptObject::Exec_Call( CCommand *cmd )
{
	CComCall *com = static_cast<CComCall*>(cmd);

	Value tmp = com->m_func.GetValue();
	errorsT er = com->m_func.GetRunErrorCode();
	if( er != NOERR )
		return er;
	++m_CurrentPosition;
	return NOERR;
}

errorsT ScriptObject::Exec_PushSub( CCommand *cmd )
{
	CComPushSub *com = static_cast<CComPushSub*>(cmd);
	CmdPos cp( com->m_cp );
	m_SubStack.push( cp );
	++m_CurrentPosition;
	return NOERR;
}

errorsT ScriptObject::Exec_Ret( CCommand *cmd )
{
	//CComRet *com = static_cast<CComRet*>(cmd);
	if( m_SubStack.empty() )
		return RET_WO_GOSUB;
	m_CurrentPosition = (m_SubStack.top()).m_cp;
	m_SubStack.pop();
	return NOERR;
}

// Find the value of a variable. 
Value ScriptObject::find_var( const std::string &s )
{
//ф-ция вызывается только при выпонении
	ASSERT( !m_bCompiling );
	Value res;
	res.SetType( TYPE_UNKNOWN );
	ASSERT( isalpha(s[0]) );
//		ErrMesCompile( NOT_VAR, false ); // not a variable
	TypeID t = IsVariable(s);
	if( t != TYPE_UNKNOWN )
	{		
		//выясним - в какой карте надо искать значение переменной
		Variables *vars = GetVarTable(s);
		vars->GetVarValue( s, t, res );
	}
	else
	{
		//поискать среди констант
		t = IsConstant(s);
		if( t != TYPE_UNKNOWN )
		{
			m_ConstTable.GetVarValue( s, t, res );
		}		
	}
	//если строки нет ни среди переменных ни среди констант,
	//то вернётся TYPE_UNKNOWN
	return res;
}

void ScriptObject::ErrMesExpr( const std::string &expr )
{
//ф-ция выводит сообщение об ошибке в выражении и возвращает
//управление в точку вызова.
	string mes, tmp = expr;
	mes += _T("\r\n(ошибка в выражении: ");
	//в выражении expr в конце могут быть пары \r\n
	//при выводе они не нужны
	CutEOL(tmp);

	mes += tmp;
	mes += _T(")");

	SetOutput( mes );
}

void ScriptObject::ErrMesWarning( errorsT er )
{
//ф-ция выводит предупрежение при компиляции, но m_ErrNum не инкрементирует
	string mes;

	mes += _T("\r\nWARNING: ");
	mes += m_ErrMesTable[er];

	string::iterator TextBegin = m_Text.begin(), p = TextBegin;
	int linecount = 0;
	while( p != prog ) 
	{
		if( *p == '\r' )
		{
			linecount++;
		}
		++p;
	}
	mes += _T(" в строке номер ") + FormatString("%d", linecount );
	mes += _T(":\r\n<");

	string::iterator temp = p;
	p--;
	p--;
	for( int i = 0; (i<MAX_ERRMES_LEN)&&(p>TextBegin)&&(*p!='\n'); i++, p-- );
	for(; p < temp; p++) 
	{
		if( *p == '\n' || *p == '\r' ) continue;
		mes += *p;
	}
	mes += _T(">");

	SetOutput( mes );
	m_WarningNum++;
}

void ScriptObject::ErrMesRun( errorsT er )
{
//ф-ция выводит сообщение об ошибке во время выполнения скрипта.
	string mes;
	mes += _T("\r\n");
	if( (er != END_CMD)&&(er != NOERR) )
		mes += _T("RUNING ERROR: ");
	mes += m_ErrMesTable[er];
	mes += _T("\r\n");

	SetOutput( mes );
	m_ErrNum++;
}

void ScriptObject::ErrMesFatal( errorsT er )
{
//ф-ция выводит сообщение об фатальной ошибке
//и прекращает работу с данным скриптом, очищая все ресурсы
	m_bFatalCrash = true;
	ClearData();

	string mes;
	mes += _T("\r\nFATAL ERROR: ");
	mes += m_ErrMesTable[er];
	mes += "\r\n";
	SetOutput( mes );	

	//таблица команд:
	m_CommandTable.erase( m_CommandTable.begin(), m_CommandTable.end() );
	//таблица костант:
	m_ConstTable.Clear();

	m_ErrMesTable.erase( m_ErrMesTable.begin(), m_ErrMesTable.end() );
	//таблица зарезервированных ф-ций:
	m_FuncTable.erase( m_FuncTable.begin(), m_FuncTable.end() );
	//таблица типов:
	m_TypeTable.erase( m_TypeTable.begin(), m_TypeTable.end() );

	AfxMessageBox( mes.c_str() );
	throw er;
}

void ScriptObject::ErrMesCompile( errorsT er, bool flag/*=true*/ )
{
//ф-ция выводит сообщение об ошибке er
//на этапе компиляции, 
//т.е. не происходит прекращения компиляции
//flag показывает: надо ли (можно ли ?) считать номер строки
	string mes;

	mes += _T("\r\n");
	if( m_bCompiling )
		mes += _T("COMPILING ");
	mes += _T("ERROR: ");
	mes += m_ErrMesTable[er];

	if( flag )
	{
		string::iterator TextBegin = m_Text.begin(), p = TextBegin;
		int linecount = 0;
		while( p != prog ) 
		{  // find line number of error 
			if( *p == '\r' )
			{
				linecount++;
			}
			++p;
		}
		mes += _T(" в строке номер ") + FormatString("%d", linecount );
		mes += _T(":\r\n<");
	
		string::iterator temp = p;  // display line with error
		p--;
		p--;
		for( int i = 0; (i<MAX_ERRMES_LEN)&&(p>TextBegin)&&(*p!='\n'); i++, p-- );
		for(; p < temp; p++) 
		{
			if( *p == '\n' || *p == '\r' ) continue;
			mes += *p;
		}
		mes += _T(">");
	}

	SetOutput( mes );
	m_ErrNum++;
}

// Get a token. 
typesT ScriptObject::get_token()
{
	typedef enum{ LE=1, GE, NE } double_ops;

	token_type = UNDEFTOK; 
	tok = UNKNCOM;

	string::iterator fin = m_Text.end();
	if( prog == fin )
	{ // end of file or expression
		token = "";
		tok = FINISHED;
		return(token_type=OPERATOR);
	}

	while( is_sp_tab(*prog) ) ++prog;  // skip over white space 

	if( prog == fin )
	{ // end of file or expression
		token = "";
		tok = FINISHED;
		return(token_type=OPERATOR);
	}

	if( *prog == '\r' )
	{ // crlf 
		++prog; ++prog;
		tok = EOL;
		token = "";
		token += '\r';
		token += '\n';
		return (token_type = OPERATOR);
	}

	if( strchr("<>", *prog) )
	{ // check for double op
		token = "";
		switch(*prog)
		{
		case '<':
			if(*(prog+1)=='>') 
			{
				prog++; prog++;
				token += NE;
			}
			else
			{
				if(*(prog+1)=='=') 
				{
					prog++; prog++;
					token += LE;
				}
				else 
				{
					prog++;
					token += '<';
				}
			}
			break;
		case '>':
			if(*(prog+1)=='=') 
			{
				prog++; prog++;
				token += GE;
			}
			else 
			{
				prog++;
				token += '>';
			}
			break;
		}
		return(token_type = OPERATOR);
	}

	if(strchr("+-*^/=;(),", *prog))
	{ // operator
		token = "";
		token += *prog;
		++prog; // advance to next position 
		return (token_type=OPERATOR);
	}
    
	if(*prog=='"')
	{ // quoted string 
		token = "";
		++prog;
		while( (*prog != '"')&&(*prog != '\r') )
		{
			token += *prog;
			++prog;
		}
		if( *prog == '\r' )
		{
			find_eol();
			ErrMesCompile( MISS_QUOTE, true );
			tok = UNKNCOM;
			return token_type = UNDEFTOK;
		}
		++prog;
		return(token_type=QUOTE);
	}
  
	if(isdigit(*prog)) 
	{ // number 
		token = "";
		while( !isdelim(*prog) )
		{
			token += *prog;
			++prog;
		}
		return(token_type = NUMBER);
	}

	if(isalpha(*prog)) 
	{ // var or command 
		token = "";
		while( !isdelim(*prog) )
		{
			token += *prog;
			++prog;
		}
		token_type = STRING;
	}
  
	// see if a string is a command or a variable 
	if( token_type == STRING )
	{
		tok = look_up(token); // convert to internal rep 
		switch(tok)
		{
		case UNKNCOM:
			token_type = VARIABLE;
			break;
		case SOME_FUNC://встроенная или польз-кая ф-ция
			token_type = FUNCTION;
			break;
		case SOME_TYPE://объявление переменной
			token_type = TYPE;
			break;
		default:
			token_type = COMMAND; // is a command 
			break;
		}//switch
	}
	return token_type;
}

// Return a token to input stream. 
void ScriptObject::putback() 
{
//данную ф-цию следует вызывать сразу после get_token()
//т.е. так, чтобы не менялся prog, например после find_eol()
	string::iterator t; 
	t = token.begin();
	for(; t != token.end(); ++t) --prog;
}

//Look up a token's internal representation in the token table.
SBtokensT ScriptObject::look_up( std::string &str )
{
	MakeLower(str);
	// see if token is in table
	Commands::iterator it = m_CommandTable.find(str);
	if( it != m_CommandTable.end() )
		return it->second;
	if( Expression::IsInternalFunc(str) )
		return SOME_FUNC;
	if( m_FuncTable.find(str) != m_FuncTable.end() )
		return SOME_FUNC;
	if( m_TypeTable.find(str) != m_TypeTable.end() )
		return SOME_TYPE;
	if( m_UserFuncTable.find(str) != m_UserFuncTable.end() )
		return SOME_FUNC;

	return UNKNCOM; // unknown command
}

// Return true if c is a delimiter. 
bool ScriptObject::isdelim(char c)
{
	if(strchr(" ;,+-<>/*%^=()", c) || c==9 || c=='\r' || c==0) 
		return true;  
	return false; 
}

// Return true if c is space or tab. 
bool ScriptObject::is_sp_tab(char c)
{
	if( (c == ' ')||(c == '\t') ) return true;
	return false;
}

std::vector<std::string> ScriptObject::InitErrMesTable()
{
	vector<string> emt;

	emt.push_back( string("Нет ошибки") );//NOERR
	emt.push_back( string("Выполнение завершено командой END") );//END_CMD
	emt.push_back( string("Внутренняя ошибка выделения памяти !!!") );//NOMEM
	emt.push_back( string("Ошибка выполнения") );//RUN_ERR
    emt.push_back( string("Синтаксическая ошибка") );//SERROR
	emt.push_back( string("Ошибка") );//CERROR
	emt.push_back( string("Неизвестная ошибка") );//UNKN_ERR
    emt.push_back( string("Выражение не сбалансированно по скобкам") );//PARENS
    emt.push_back( string("Отсутствует выражение") );//NOEXP
    emt.push_back( string("Деление на ноль") );//DIV_ZERO
    emt.push_back( string("Отсутствует знак равенства, необходимый в данном выражении") );//EQUAL_EXP
    emt.push_back( string("Не переменная") );//NOT_VAR
    emt.push_back( string("Дублирование меток") );//DUP_LAB
    emt.push_back( string("Неопределённая метка") );//UNDEF_LAB
    emt.push_back( string("Отсутствует команда THEN") );//THEN_EXP
    emt.push_back( string("Отсутствует команда TO") );//TO_EXP
	emt.push_back( string("Отсутствует условие остановки цикла после команды TO") );//TARGET_EXP
	emt.push_back( string("После STEP должно стоять значение шага приращения") );//STEP_ERR
    emt.push_back( string("Использование NEXT без соответствующего FOR") );//NEXT_WO_FOR
	emt.push_back( string("Имя не соответствует переменной текущего цикла") );//NEXT_VAR_ERR
    emt.push_back( string("Использование RETURN без соответствующего GOSUB") );//RET_WO_GOSUB
    emt.push_back( string("Отсутствуют закрывающиеся кавычки для строки") );//MISS_QUOTE
	emt.push_back( string("Неопределённый символ") );//WRONG_SIMBOL
	emt.push_back( string("Неверные параметры функции") );//WRONG_FUNC_PARAM
	emt.push_back( string("Неверное число параметров функции") );//WRONG_FUNC_PARAM_NUM
	emt.push_back( string("Ошибка приведения типов") );//CONVERT_ERR
	emt.push_back( string("Операция не применима для данного типа") );//TYPE_OP_ERR
	emt.push_back( string("Возводить можно только в целую степень") );//INT_POWER
	emt.push_back( string("Арифметическая ошибка") );//FP_ERR
	emt.push_back( string("Попытка вычислить квадратный корень из отрецательного числа") );//NEG_SQRT
	emt.push_back( string("Использование BREAK вне какого-либо цикла") );//BREAK_ERR
	emt.push_back( string("Разрушение стека при выполнении GOTO") );//STACK_CRASH
	emt.push_back( string("Отсутствует команда после THEN") );//MISSING_IF_CMD
	emt.push_back( string("В операторе IF после THEN нельзя использовать данную команду") );//IF_CMD_ERR
	emt.push_back( string("Программа не сбалансирована по FOR/NEXT") );//FOR_ERR
	emt.push_back( string("Неверное имя разбираемой функции") );//WRONG_END
	emt.push_back( string("Функция должна вернуть какое-нибудь значение") );//NO_USER_RETURN
	emt.push_back( string("Нельзя объявлять функцию внутри другой функции") );//USER_FUNC_ERR
	emt.push_back( string("Нельзя использовать зарезервированные слова") );//RESERVED_WORD
	emt.push_back( string("Повторное объявление") );//REDECLARE
	emt.push_back( string("Возможно зацикливание") );//FOREVER_CYCLE
	emt.push_back( string("Цикл не выполнится ни разу") );//NO_CYCLE
	emt.push_back( string("Цикл выполнится только один раз") );//ONE_TIME_CYCLE
	emt.push_back( string("Выход за пределы массива") );//ARRAY_ACCESS
	emt.push_back( string("Невозможно открыть файл") );//FILE_OPEN

	return emt;
}

Commands ScriptObject::InitCommandTable()
{
	Commands ct;

	ct.insert( MakeCommand("print",PRINT) );
	ct.insert( MakeCommand("if",IF) );
	ct.insert( MakeCommand("then",THEN) );
	ct.insert( MakeCommand("goto",GOTO) );
	ct.insert( MakeCommand("for",FOR) );
	ct.insert( MakeCommand("next",NEXT) );
	ct.insert( MakeCommand("to",TO) );
	ct.insert( MakeCommand("step",STEP) );
	ct.insert( MakeCommand("gosub",GOSUB) );
	ct.insert( MakeCommand("return",RETURN) );
	ct.insert( MakeCommand("rem",REM) );
	ct.insert( MakeCommand("break",BREAK) );
	ct.insert( MakeCommand("end",END) );
	ct.insert( MakeCommand("function",USER_FUNC) );

	return ct;
}

Variables ScriptObject::InitConstTable()
{
	Variables ct;

	ct.BoolMap()->insert( MakeBool("true",true) );
	ct.BoolMap()->insert( MakeBool("false",false) );
	ct.DoubleMap()->insert( MakeDouble("pi",CNSys2DApp::M_PI) );
	ct.StringMap()->insert( MakeString("eol",string("\r\n")) );

	return ct;
}

Types ScriptObject::InitTypeTable()
{
	Types tt;

	tt.insert( MakeType("bool", TYPE_BOOL) );
	tt.insert( MakeType("int", TYPE_INT) );
	tt.insert( MakeType("double", TYPE_DOUBLE) );
	tt.insert( MakeType("string", TYPE_STRING) );
	tt.insert( MakeType("array_int", TYPE_ARRAY_INT) );
	tt.insert( MakeType("array_bool", TYPE_ARRAY_BOOL) );
	tt.insert( MakeType("array_double", TYPE_ARRAY_DOUBLE) );
	tt.insert( MakeType("array_string", TYPE_ARRAY_STRING) );
	tt.insert( MakeType("file", TYPE_FILE) );
	tt.insert( MakeType("using", TYPE_SCRIPT) );	
	tt.insert( MakeType("matr", TYPE_MATR) );

	//элементы
	tt.insert( MakeType("sheme", TYPE_SHEME) );
	tt.insert( MakeType("rod", TYPE_ROD) );
	tt.insert( MakeType("hardrod", TYPE_HARDROD) );
	tt.insert( MakeType("spring", TYPE_SPRING) );
	tt.insert( MakeType("demfer", TYPE_DEMFER) );
	tt.insert( MakeType("mass", TYPE_MASS) );
	tt.insert( MakeType("knot", TYPE_KNOT) );

	return tt;
}

Functions ScriptObject::InitFuncTable()
{
	Functions ft;

	ft.insert( MakeFunc("printallreservedwords", FUN_PRINTALLRESERVEDWORDS) );
	ft.insert( MakeFunc("printcode", FUN_PRINTCODE) );
	ft.insert( MakeFunc("help", FUN_HELP) );
	//массивы и м-цы
	ft.insert( MakeFunc("setat", FUN_SETAT) );
	ft.insert( MakeFunc("getat", FUN_GETAT) );
	ft.insert( MakeFunc("resize", FUN_RESIZE) );
	ft.insert( MakeFunc("sizeof", FUN_SIZEOF) );
	ft.insert( MakeFunc("loadidentity", FUN_LOADIDENTITY) );
	ft.insert( MakeFunc("invert", FUN_INVERT) );
	//файлы
	ft.insert( MakeFunc("fileopentxt", FUN_FILEOPENTXT) );
	ft.insert( MakeFunc("fileopenbin", FUN_FILEOPENBIN) );
	ft.insert( MakeFunc("fileread", FUN_FILEREAD) );
	ft.insert( MakeFunc("filewrite", FUN_FILEWRITE) );
	ft.insert( MakeFunc("filerewind", FUN_FILEREWIND) );
	ft.insert( MakeFunc("fileclose", FUN_FILECLOSE) );
	ft.insert( MakeFunc("filewriteeol", FUN_WRITEEOL) );
	//скрипты
	ft.insert( MakeFunc("runscript", FUN_RUNSCRIPT) );
	//элементы
	ft.insert( MakeFunc("createknot", FUN_CREATEKNOT) );
	ft.insert( MakeFunc("createelem", FUN_CREATEELEM) );
	ft.insert( MakeFunc("setelemm", FUN_SETELEMM) );
	ft.insert( MakeFunc("setelemj", FUN_SETELEMJ) );
	ft.insert( MakeFunc("setelemf", FUN_SETELEMF) );
	ft.insert( MakeFunc("seteleme", FUN_SETELEME) );
	ft.insert( MakeFunc("getelemm", FUN_GETELEMM) );
	ft.insert( MakeFunc("getelemj", FUN_GETELEMJ) );
	ft.insert( MakeFunc("getelemf", FUN_GETELEMF) );
	ft.insert( MakeFunc("geteleme", FUN_GETELEME) );
	ft.insert( MakeFunc("getlength", FUN_GETLENGTH) );
	ft.insert( MakeFunc("getelemmatrm", FUN_GETELEMMATRM) );
	ft.insert( MakeFunc("getelemmatrd", FUN_GETELEMMATRD) );
	ft.insert( MakeFunc("getelemmatrc", FUN_GETELEMMATRC) );
	//схемы
	ft.insert( MakeFunc("opensheme", FUN_OPENSHEME) );
	ft.insert( MakeFunc("closesheme", FUN_CLOSESHEME) );
	ft.insert( MakeFunc("savesheme", FUN_SAVESHEME) );
	ft.insert( MakeFunc("saveshemeas", FUN_SAVESHEMEAS) );
	ft.insert( MakeFunc("geteigen", FUN_GETEIGEN) );
	ft.insert( MakeFunc("integrate", FUN_INTEGRATE) );
	ft.insert( MakeFunc("getresy1", FUN_GETRESY1) );
	ft.insert( MakeFunc("getresy2", FUN_GETRESY2) );
	ft.insert( MakeFunc("getresy3", FUN_GETRESY3) );
	ft.insert( MakeFunc("getmatrmdc", FUN_GETMATRMDC) );
	ft.insert( MakeFunc("getelem", FUN_GETELEM) );
	ft.insert( MakeFunc("delelem", FUN_DELELEM) );
	ft.insert( MakeFunc("getknot", FUN_GETKNOT) );
	ft.insert( MakeFunc("delete", FUN_DELETE) );
	ft.insert( MakeFunc("addelement", FUN_ADDELEMENT) );

	return ft;
}

void ScriptObject::ClearData()
{
	m_Vars.Clear();
	m_LabelTable.erase( m_LabelTable.begin(), m_LabelTable.end() );
	m_UserFuncTable.erase( m_UserFuncTable.begin(), m_UserFuncTable.end() );
	m_ScriptList.erase( m_ScriptList.begin(), m_ScriptList.end() );

	while( !m_ForStack.empty() )
		m_ForStack.pop();
	while( !m_SubStack.empty() )
		m_SubStack.pop();
	//очистка кода
	while( !m_Code.empty() )
	{
		delete (*(m_Code.begin()));
		m_Code.erase( m_Code.begin() );
	}
	m_strOutput = "";
	m_bBreak = false;
}

Variables* ScriptObject::GetVarTable( const std::string &str )
{
//ф-ция ищет среди таблиц (текущей локальной и глобальной) ту,
//которая содержит в себе переменную с именем str и возвращает указатель на
//эту таблицу.
	string s(str);
	MakeLower(s);
	if( m_bCompiling && m_pCurrentUserFunc )
	{
		//поищем в локальной карте
		UserFuncTable::iterator it = m_UserFuncTable.find( m_pCurrentUserFunc->m_name );
		ASSERT( it != m_UserFuncTable.end() );
		if( (*it).second.m_LocalVars.GetVarType(s) != TYPE_UNKNOWN )
			return &(*it).second.m_LocalVars;
	}
	else
	{
		if( m_bRunable && !m_LocalVarStack.empty() )
		{
			if( m_LocalVarStack.top().GetVarType(s) != TYPE_UNKNOWN )
				return &m_LocalVarStack.top();
		}
	}
	return &m_Vars;
}

TypeID ScriptObject::GetScriptElemType( int te )
{
//ф-ция возвращает скриптовый вариант типа te.
//где te - тип КЭ.
	TypeID tid = TYPE_UNKNOWN;
	switch( te )
	{
	case IDC_ROD:
		tid = TYPE_ROD;
		break;
	case IDC_HARDROD:
		tid = TYPE_HARDROD;
		break;
	case IDC_SPRING:
		tid = TYPE_SPRING;
		break;
	case IDC_DEMF:
		tid = TYPE_DEMFER;
		break;
	case IDC_MASS:
		tid = TYPE_MASS;
		break;
	default:
		tid = TYPE_UNKNOWN;
		break;
	}
	return tid;
}

TypeID ScriptObject::IsConstant( const std::string &s )
{
	TypeID tp = m_ConstTable.GetVarType(s);
	return tp;
	/*
	if( m_ConstTable.BoolMap()->find(s) != m_ConstTable.BoolMap()->end() )
		return TYPE_BOOL;
	if( m_ConstTable.IntMap()->find(s) != m_ConstTable.IntMap()->end() )
		return TYPE_INT;
	if( m_ConstTable.DoubleMap()->find(s) != m_ConstTable.DoubleMap()->end() )
		return TYPE_DOUBLE;
	if( m_ConstTable.StringMap()->find(s) != m_ConstTable.StringMap()->end() )
		return TYPE_STRING;
	TypeID tp = m_ConstTable.ArrayType( s );
	if( tp != TYPE_UNKNOWN )
		return tp;
	if( m_ConstTable.IsFile(s) )
		return TYPE_FILE;
	if( m_ConstTable.IsScript(s) )
		return TYPE_SCRIPT;

	return TYPE_UNKNOWN;
	*/
}

TypeID ScriptObject::IsVariable( const std::string &var )
{
	string tmp(var);
	MakeLower(tmp);
	if( m_bCompiling && m_pCurrentUserFunc )
	{
		//поищем в локальной карте
		UserFuncTable::iterator it = m_UserFuncTable.find( m_pCurrentUserFunc->m_name );
		ASSERT( it != m_UserFuncTable.end() );
		TypeID tid = (*it).second.m_LocalVars.GetVarType(tmp);
		if( tid != TYPE_UNKNOWN )
			return tid;
	}
	else
	{
		if( m_bRunable && !m_LocalVarStack.empty() )
		{
			TypeID tid = m_LocalVarStack.top().GetVarType(tmp);
			if( tid != TYPE_UNKNOWN )
				return tid;
		}
	}
	return m_Vars.GetVarType(tmp);
}

void ScriptObject::StackErr(int n, bool flag )
{
//	флаг показывает, что за сообщение надо напечатать
//	flag == false - отрицание
//	flag == true - или утверждение
	ErrMesCompile(SERROR);
	if( flag )
		SetOutput( FormatString("\r\nФункция принимает %d параметров", n ) );
	else
		SetOutput( FormatString("\r\nФункция не принимает %d параметров", n ) );
}

errorsT ScriptObject::CallUserFunc( const UserFuncTable::iterator &it, const ValList &lst, Value &res )
{
//ф-ция вызывается только при выполнении
	ASSERT( (*it).second.m_Params.size() == lst.size() );
	//считаем значения параметров
	ParamList::const_iterator ParIt = (*it).second.m_Params.begin(), fin = (*it).second.m_Params.end();
	ValList::const_iterator ValIt = lst.begin();
	errorsT er = NOERR;
	while( ParIt != fin )
	{
		//присваиваем значение
		if( !(*ValIt).first->ConvertTo( (*ParIt).m_tType ) )
		{
			return CONVERT_ERR;
		}
		er = ScriptObject::AssignVar( (*ParIt).m_name, (*it).second.m_LocalVars, *(*ValIt).first );
		if( er != NOERR )
			return er;
		++ParIt;
		++ValIt;
	}
	m_LocalVarStack.push( (*it).second.m_LocalVars );
	CommandPointer tmp = m_CurrentPosition;
	m_CurrentPosition = (*it).second.m_cp;
	er = RunCode( &res );
	m_LocalVarStack.pop();
	m_CurrentPosition = tmp;
	return er;
}

bool ScriptObject::TestFuncParams( const FuncIter &it, const ValList &lst )
{
	return CallFuncFromTable( it, lst, NULL ) == NOERR;
}

errorsT ScriptObject::CallReservedFunc( const FuncIter &it, const ValList &lst, Value &val )
{
	return CallFuncFromTable( it, lst, &val );
}

errorsT ScriptObject::CallFuncFromTable( const FuncIter &it,
								   const ValList &lst,
								   Value *val )
{
	errorsT res;
	switch( (*it).second )
	{
	case FUN_PRINTALLRESERVEDWORDS:
		res = Fun_PrintAllReservedWords( lst, val );
		break;
	case FUN_PRINTCODE:
		res = Fun_PrintCode( lst, val );
		break;
	case FUN_HELP:
		res = Fun_Help( lst, val );
		break;
	case FUN_SETAT:
		res = Fun_SetAt( lst, val );
		break;
	case FUN_GETAT:
		res = Fun_GetAt( lst, val );
		break;
	case FUN_RESIZE:
		res = Fun_Resize( lst, val );
		break;
	case FUN_SIZEOF:
		res = Fun_Sizeof( lst, val );
		break;
	case FUN_FILEOPENTXT:
		res = Fun_FileOpenTxt( lst, val );
		break;
	case FUN_FILEOPENBIN:
		res = Fun_FileOpenBin( lst, val );
		break;
	case FUN_FILEREAD:
		res = Fun_FileRead( lst, val );
		break;
	case FUN_FILEWRITE:
		res = Fun_FileWrite( lst, val );
		break;
	case FUN_FILEREWIND:
		res = Fun_FileRewind( lst, val );
		break;
	case FUN_FILECLOSE:
		res = Fun_FileClose( lst, val );
		break;
	case FUN_WRITEEOL:
		res = Fun_FileWriteEOL( lst, val );
		break;
	case FUN_RUNSCRIPT:
		res = Fun_RunScript( lst, val );
		break;
	case FUN_CREATEKNOT:
		res = Fun_CreateKnot( lst, val );
		break;
	case FUN_CREATEELEM:
		res = Fun_CreateElem( lst, val );
		break;
	case FUN_SETELEMM:
		res = Fun_SetElemM( lst, val );
		break;
	case FUN_SETELEMJ:
		res = Fun_SetElemJ( lst, val );
		break;
	case FUN_SETELEMF:
		res = Fun_SetElemF( lst, val );
		break;
	case FUN_SETELEME:
		res = Fun_SetElemE( lst, val );
		break;
	case FUN_GETELEMM:
		res = Fun_GetElemM( lst, val );
		break;
	case FUN_GETELEMJ:
		res = Fun_GetElemJ( lst, val );
		break;
	case FUN_GETELEMF:
		res = Fun_GetElemF( lst, val );
		break;
	case FUN_GETELEME:
		res = Fun_GetElemE( lst, val );
		break;
	case FUN_GETLENGTH:
		res = Fun_GetLength( lst, val );
		break;
	case FUN_GETELEMMATRM:
		res = Fun_GetElemMatrM( lst, val );
		break;
	case FUN_GETELEMMATRD:
		res = Fun_GetElemMatrD( lst, val );
		break;
	case FUN_GETELEMMATRC:
		res = Fun_GetElemMatrC( lst, val );
		break;
	case FUN_LOADIDENTITY:
		res = Fun_LoadIdentity( lst, val );
		break;
	case FUN_INVERT:
		res = Fun_Invert( lst, val );
		break;
	case FUN_OPENSHEME:
		res = Fun_OpenSheme( lst, val );
		break;
	case FUN_CLOSESHEME:
		res = Fun_CloseSheme( lst, val );
		break;
	case FUN_SAVESHEME:
		res = Fun_SaveSheme( lst, val );
		break;
	case FUN_SAVESHEMEAS:
		res = Fun_SaveShemeAs( lst, val );
		break;
	case FUN_GETEIGEN:
		res = Fun_GetEigen( lst, val );
		break;
	case FUN_INTEGRATE:
		res = Fun_Integrate( lst, val );
		break;
	case FUN_GETRESY1:
		res = Fun_GetResY1( lst, val );
		break;
	case FUN_GETRESY2:
		res = Fun_GetResY2( lst, val );
		break;
	case FUN_GETRESY3:
		res = Fun_GetResY3( lst, val );
		break;
	case FUN_GETMATRMDC:
		res = Fun_GetMatrMDC( lst, val );
		break;
	case FUN_GETELEM:
		res = Fun_GetElem( lst, val );
		break;
	case FUN_DELELEM:
		res = Fun_DelElem( lst, val );
		break;
	case FUN_GETKNOT:
		res = Fun_GetKnot( lst, val );
		break;
	case FUN_DELETE:
		res = Fun_Delete( lst, val );
		break;
	case FUN_ADDELEMENT:
		res = Fun_AddElement( lst, val );
		break;
	default:
		ASSERT(FALSE);
	}
	return res;
}

bool ScriptObject::IsReservedWord(const std::string &expr )
{
	string str(expr);
	MakeLower(str);

	if( m_CommandTable.find(str) != m_CommandTable.end() )
		return true;
	if( Expression::IsInternalFunc(str) )
		return true;
	if( m_FuncTable.find(str) != m_FuncTable.end() )
		return true;
	if( m_TypeTable.find(str) != m_TypeTable.end() )
		return true;
	if( m_ConstTable.BoolMap()->find(str) != m_ConstTable.BoolMap()->end() )
		return true;
	if( m_ConstTable.IntMap()->find(str) != m_ConstTable.IntMap()->end() )
		return true;
	if( m_ConstTable.DoubleMap()->find(str) != m_ConstTable.DoubleMap()->end() )
		return true;
	if( m_ConstTable.StringMap()->find(str) != m_ConstTable.StringMap()->end() )
		return true;
	return false;
}

bool ScriptObject::IsReDeclare(const std::string &expr )
{
//ф-ция возвращает true если expr уже где-то объявлена
//иначе false
	string str(expr);
	MakeLower(str);

	if( m_pCurrentUserFunc )
	{
		//если разбираем пользовательскую ф-цию,
		//то разрешено дублирование имён глобальных переменных,
		//но запрещено дублировать имена локальных переменных
		UserFuncTable::iterator it = m_UserFuncTable.find( m_pCurrentUserFunc->m_name );
		ASSERT( it != m_UserFuncTable.end() );
		if( (*it).second.m_LocalVars.GetVarType(str) != TYPE_UNKNOWN )
			return true;
	}
	else
	{
		//если мы не в польз-ой ф-ции, то дублирование имён
		//запрещено
		if( m_Vars.GetVarType(str) != TYPE_UNKNOWN )
			return true;
	}
	if( m_UserFuncTable.find(str) != m_UserFuncTable.end() )
		return true;
	return false;
}

void ScriptObject::ChangeCurrentPosition( const std::string &lab )
{
//ф-ция меняет текущий итератор при попадании на метку lab
	for( CommandPointer pt = m_Code.begin(); pt != m_Code.end(); ++pt )
	{
		if( (*pt)->GetCommandID() == CMD_LABEL )
		{
			if( (static_cast<CComLabel*>(*pt))->m_label == lab )
			{
				++pt;
				m_CurrentPosition = pt;
				return;
			}
		}
	}
}

std::string ScriptObject::GetNewLabelName( bool flag/*=false*/)
{
//если flag==true, то надо сбросить счётчик меток.
//сброс происходит при начале новой компиляции
	static int counter = 0;
	if( flag )
	{
		counter = 0;
		return string("");
	}
	string lab( FormatString("_InternalLabel%d_", counter ) );
	counter++;
	return lab;
}

void ScriptObject::InsertInternalLabel()
{
	if( m_InternalLabel.empty() )	return;
	CComLabel *cmd;
	try
	{
		cmd = new CComLabel( m_InternalLabel );
	}
	catch( bad_alloc& )
	{
		ErrMesFatal(NOMEM);
	}
	m_Code.insert( m_CurrentPosition, static_cast<CCommand*>(cmd) );
	//стираем строку
	m_InternalLabel.erase( m_InternalLabel.begin(), m_InternalLabel.end() );
}

void ScriptObject::PrepareCode()
{
//ф-ция подготавливает откомпилированный код к исполнению:
//	удаляет метки и заменяет ссылки на них на итераторы
	if( m_bDebug )
	{
		bool tmp = m_bRunable;
		m_bRunable = true;
		Value tmpVal;
		ValList lst;
		Fun_PrintCode( lst, &tmpVal );
		m_bRunable = tmp;
	}
	SetOutput("\r\n<--------Executing:----------->\r\n");
	typedef map<string,CommandPointer> TmpLabels;
	TmpLabels labs;

	CommandPointer cp;
	//проверяем - не стоит ли END самой последней в коде?
	cp = m_Code.end();
	ASSERT(!m_Code.empty());
	--cp;
	if( (*cp)->GetCommandID() != CMD_END )
	{
		//если там не END, то добавляем еёго
		CComEnd *cmd;
		try
		{
			cmd = new CComEnd();
		}
		catch( bad_alloc& )
		{
			ErrMesFatal(NOMEM);
		}
		m_Code.insert( m_Code.end(), static_cast<CCommand*>(cmd) );
	}
	for( cp = m_Code.begin(); cp != m_Code.end(); ++cp )
	{
		if( (*cp)->GetCommandID() == CMD_LABEL )
		{
			CComLabel *cl = static_cast<CComLabel*>(*cp);
			CommandPointer tmp = cp;
			//найдём ближайшую команду - не метку
			do
			{
				++tmp;
				ASSERT( tmp != m_Code.end() );
			}	while( (*tmp)->GetCommandID() == CMD_LABEL );
			//теперь tmp указывает на команду, идушую вслед за меткой
			labs.insert( TmpLabels::value_type(cl->m_label,tmp) );
		}
	}
	//заполняем CommandPointer-ы в командах, где нужно
	for( cp = m_Code.begin(); cp != m_Code.end(); ++cp )
	{
		switch( (*cp)->GetCommandID() )
		{
		case CMD_JE:
			{
				CComJe *cmd = static_cast<CComJe*>(*cp);
				TmpLabels::iterator it = labs.find(cmd->m_label);
				ASSERT( it != labs.end() );
				cmd->m_cp = (*it).second;
			}
			break;
		case CMD_JG:
			{
				CComJg *cmd = static_cast<CComJg*>(*cp);
				TmpLabels::iterator it = labs.find(cmd->m_label);
				ASSERT( it != labs.end() );
				cmd->m_cp = (*it).second;
			}
			break;
		case CMD_JL:
			{
				CComJl *cmd = static_cast<CComJl*>(*cp);
				TmpLabels::iterator it = labs.find(cmd->m_label);
				ASSERT( it != labs.end() );
				cmd->m_cp = (*it).second;
			}
			break;
		case CMD_JMP:
			{
				CComJmp *cmd = static_cast<CComJmp*>(*cp);
				TmpLabels::iterator it = labs.find(cmd->m_label);
				ASSERT( it != labs.end() );
				cmd->m_cp = (*it).second;
			}
			break;
		case CMD_PUSH_SUB:
			{
				CComPushSub *cmd = static_cast<CComPushSub*>(*cp);
				TmpLabels::iterator it = labs.find(cmd->m_label);
				ASSERT( it != labs.end() );
				cmd->m_cp = (*it).second;
			}
			break;
		default:
			break;
		}//switch
	}//for
	UserFuncTable::iterator it = m_UserFuncTable.begin();
	for(; it != m_UserFuncTable.end(); ++it )
	{
		TmpLabels::iterator itt = labs.find( (*it).second.m_label );
		ASSERT( itt != labs.end() );
		(*it).second.m_cp = (*itt).second;
	}
	/*
	//удаляем все метки
	cp = m_Code.begin();
	while(  cp != m_Code.end() )
	{
		if( (*cp)->GetCommandID() == CMD_LABEL )
		{
			delete (*cp);
			cp = m_Code.erase(cp);
		}
		else	
			++cp;
	}
	*/
}

