// ScriptObject.h: interface for the ScriptObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIPTHEADER_H__88C31017_C0BB_11D5_B89C_FE2BA355A53D__INCLUDED_)
#define AFX_SCRIPTHEADER_H__88C31017_C0BB_11D5_B89C_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include"ScriptDefs.h"

#include"FileHeader.h"
#include"ExprHeader.h"
#include"ArrayHeader.h"
#include"ValueHeader.h"
#include"ScriptPtrHeader.h"
#include"VariablesHeader.h"
#include"CommandHeader.h"

#include<stack>
#include<list>
#include<vector>

class CScriptDoc;
///////////////////////////////////////////////////////////////
// support for FOR loops 
class ForLevel
{
	void InitBy( const ForLevel &fs )
	{
		var = fs.var;
		step = fs.step;
		lab1 = fs.lab1;
		lab2 = fs.lab2;
	}
public:
	std::string var;// counter variable 	
	Expression step;//шаг приращения
	std::string lab1, lab2;//метки положения при выполнении NEXT
	//и при невыполнении цикла вообще соответственно
	ForLevel& operator = ( const ForLevel &fs )
	{
		if( this == &fs )	return *this;
		InitBy(fs);
		return *this;
	}
	ForLevel( const ForLevel &fs )
	{
		InitBy(fs);
	}
	ForLevel( ScriptObject *p = NULL ):step(p)
	{}
	~ForLevel(){};

	friend bool operator < ( const ForLevel &fs1, const ForLevel &fs2 );
	friend bool operator == ( const ForLevel &fs1, const ForLevel &fs2 );
};

typedef std::stack<ForLevel> ForStack;
////////////////////////////////////////////////////////////////
class ScriptData
{
public:
	std::string FileName;
	std::string VarName;

	friend bool operator < ( const ScriptData&, const ScriptData& );
	friend bool operator == ( const ScriptData&, const ScriptData& );
	friend bool operator > ( const ScriptData&, const ScriptData& );
	friend bool operator != ( const ScriptData&, const ScriptData& );
};
typedef std::list<ScriptData> ScriptList;
////////////////////////////////////////////////////////////////

class ScriptObject
{
	///////////////////////////////////////////////////////////
	//вложенные классы
	////////////////////////////////////////////////////////////////
//классы элементарных команд:
class CComLabel: public CCommand
{
//класс временной команды "метка"
//после компиляции объекты данного класса должны быть удалены
//из списка кода, а ссылки на них в командах типа Jxx (jmp, jge, ...)
//должны быть заменены на итераторы команд, следующих за
//данным объектом "метка" в списке кода
	CComLabel& operator=(const CComLabel&);
	CComLabel( const CComLabel& );

public:
	std::string m_label;

	CComLabel( const std::string &name ):CCommand(CMD_LABEL),
		m_label(name)
	{}
	virtual ~CComLabel(){}
};

class CComMovExpr: public CCommand
{
//класс команды "mov variable,expression"
//в переменную name заносится значение выражения expr
	CComMovExpr& operator=(const CComMovExpr&);
	CComMovExpr( const CComMovExpr& );

public:
	std::string m_name;
	Expression m_expr;

	CComMovExpr( const std::string &name, const Expression &expr ):CCommand(CMD_MOV_EXPR),
		m_name(name), m_expr(expr)
	{}
	virtual ~CComMovExpr(){}
};

class CComAdd: public CCommand
{
//класс команды "add variable,value"
//к переменной name прибавляется величина val,
//а результат заносится в name
	CComAdd& operator=(const CComAdd&);
	CComAdd( const CComAdd& );

public:
	std::string m_name;//имя переменной (всегда типа int !)
	Expression m_val;//прибавляемое к ней значение

	CComAdd( const std::string &name, const Expression &val ):CCommand(CMD_ADD),
		m_name(name), m_val(val)
	{}
	virtual ~CComAdd(){}
};

class CComPrint: public CCommand
{
//класс команды "print expression"
//вывод на экран выражения (или значения выражения) expr
	CComPrint& operator=(const CComPrint&);
	CComPrint( const CComPrint& );

public:
	PrintList m_expr;

	CComPrint( const PrintList &expr ):CCommand(CMD_PRINT),
		m_expr(expr)
	{}
	virtual ~CComPrint(){}
};

class CComCmpVarExpr: public CCommand
{
//класс команды "cmp varname,expression"
//сравниваются значения переменной и выражения и выставляется соответствующий флаг.
//в данной версии скрипта типы переменной и выражения всегда INT.
	CComCmpVarExpr& operator=(const CComCmpVarExpr&);
	CComCmpVarExpr( const CComCmpVarExpr& );

public:
	std::string m_name;
	Expression m_expr;

	CComCmpVarExpr( const std::string &name, const Expression &expr ):CCommand(CMD_CMP_VAR_EXPR),
		m_name(name), m_expr(expr)
	{}
	virtual ~CComCmpVarExpr(){}
};

class CComCmpExprVal: public CCommand
{
//класс команды "cmp expression,value"
//сравниваются значение выражения expr и величина val
//и выставляется соответствующий флаг.
//при вычислении значения выражения m_expr его величина приводится
//к типу величины m_val.
	CComCmpExprVal& operator=(const CComCmpExprVal&);
	CComCmpExprVal( const CComCmpExprVal& );

public:
	Expression m_expr;
	Value m_val;

	CComCmpExprVal( const Expression &expr, const Value &val ):CCommand(CMD_CMP_EXPR_VAL),
		m_expr(expr), m_val(val)
	{}
	virtual ~CComCmpExprVal(){}
};

class CComJmp: public CCommand
{
//класс команды "jmp label"
//безусловный переход на метку label
	CComJmp& operator=(const CComJmp&);
	CComJmp( const CComJmp& );

public:
	CommandPointer m_cp;
	std::string m_label;

	CComJmp( const std::string &lab ):CCommand(CMD_JMP),
		m_label(lab)
	{}
	virtual ~CComJmp(){}
};

class CComJe: public CCommand
{
//класс команды "je label"
//условный переход на метку label, если флаг выставлен в значение EQ
	CComJe& operator=(const CComJe&);
	CComJe( const CComJe& );

public:
	CommandPointer m_cp;
	std::string m_label;

	CComJe( const std::string &lab ):CCommand(CMD_JE),
		m_label(lab)
	{}
	virtual ~CComJe(){}
};

class CComJg: public CCommand
{
//класс команды "jg label"
//условный переход на метку label, если флаг выставлен в значение GT
	CComJg& operator=(const CComJg&);
	CComJg( const CComJg& );

public:
	CommandPointer m_cp;
	std::string m_label;

	CComJg( const std::string &lab ):CCommand(CMD_JG),
		m_label(lab)
	{}
	virtual ~CComJg(){}
};

class CComJl: public CCommand
{
//класс команды "jl label"
//условный переход на метку label, если флаг выставлен в значение LT
	CComJl& operator=(const CComJl&);
	CComJl( const CComJl& );

public:
	CommandPointer m_cp;
	std::string m_label;

	CComJl( const std::string &lab ):CCommand(CMD_JL),
		m_label(lab)
	{}
	virtual ~CComJl(){}
};

class CComCall: public CCommand
{
//класс команды "call func"
//вызывает на выполнение ф-цию name
	CComCall& operator=(const CComCall&);
	CComCall( const CComCall& );

public:
	Expression m_func;//ф-ция

	CComCall( const Expression &name ):CCommand(CMD_CALL),
		m_func(name)
	{}
	virtual ~CComCall(){}
};

class CComEnd: public CCommand
{
//класс команды "end"
//прекращает выполнение программы
	CComEnd& operator=(const CComEnd&);
	CComEnd( const CComEnd& );

public:
	CComEnd():CCommand(CMD_END)
	{}
	virtual ~CComEnd(){}
};

class CComPushSub: public CCommand
{
//класс команды "push_sub label"
//запись в стэк подпрограмм итератора команды (следующей сразу за меткой label),
//которая должна быть вызвана при исполнении RETURN именно для данного GOSUB.
	CComPushSub& operator=(const CComPushSub&);
	CComPushSub( const CComPushSub& );

public:
	CommandPointer m_cp;
	std::string m_label;

	CComPushSub( const std::string &lab ):CCommand(CMD_PUSH_SUB),
		m_label(lab)
	{}
	virtual ~CComPushSub(){}
};

class CComRet: public CCommand
{
//класс команды "ret"
//чтение из стэка подпрограмм итератора команды, следующей сразу за GOSUBом,
//вызвавшим данную подпрограмму и переход на её исполнение.
	CComRet& operator=(const CComRet&);
	CComRet( const CComRet& );

public:
	CComRet():CCommand(CMD_RET)
	{}
	virtual ~CComRet(){}
};

class CComRetf: public CCommand
{
//класс команды "retf expr"
//вычисление выражения expr и занесение его значения в нужное место
	CComRetf& operator=(const CComRetf&);
	CComRetf( const CComRetf& );

public:
	Expression m_expr;

	CComRetf( const Expression &str ):CCommand(CMD_RETF),
		m_expr(str)
	{}
	virtual ~CComRetf(){}
};

class CurrentUserFunc
{
//класс, поддерживающий данные о текущей разбираемой пользовательской
//ф-ции. Используется только при компиляции.
	void InitBy( const CurrentUserFunc &uf )
	{
		m_label = uf.m_label;
		m_name = uf.m_name;
		m_RetType = uf.m_RetType;
	}
public:
	std::string m_Start;//метка начала тела ф-ции.
	bool m_bIsReturn;//флаг о том, что в ходе разбора ф-ции
	//были команды "RETURN expr". если их не было (m_bIsReturn==false),
	//то это ошибка.
	std::string m_label;//имя метки, идущей сразу за этой ф-цией.
	//эту метку надо ставить вслед за командой "END func_name".
	std::string m_name;//имя пользовательской ф-ции.
	TypeID m_RetType;//тип возвращаемого значения 
	//(все пользовательские ф-ции должны чего-нибудь вернуть)
	CurrentUserFunc& operator = ( const CurrentUserFunc &uf )
	{
		if( this == &uf )	return *this;
		InitBy(uf);
		return *this;
	}
	CurrentUserFunc( const CurrentUserFunc &uf )
	{
		InitBy(uf);
	}
	CurrentUserFunc():m_bIsReturn(false)
	{}
	virtual ~CurrentUserFunc(){}
};
////////////////////////////////////////////////////////////////

	ScriptObject& operator=(const ScriptObject&);
	ScriptObject( const ScriptObject& );
public:
	friend class Expression::OperCallFunc;
	friend class Expression::OperValue;

	///////////////////////////////////////////////////
	//общедоступные ф-ции и переменные
	bool m_bDebug;//временный флаг об отладке
	bool m_bBreak;//флаг о прерывании выполнения

	void SetScriptText( const std::string& );
	bool Compile();
	bool Run();
	void GetOutput( std::string& );
	static bool FatalCrash();
	
	void Set( CScriptDoc* );
	///////////////////////////////////////////////////
	errorsT SetParam( int, const Value& );
	errorsT GetParam( int, Value& );
	std::string GetScriptText() const;

	static errorsT AssignVar( const std::string&, Variables&, const Value& );
	static void DestructValList( ValList &lst );
	static std::string GetScriptParamName( int );

	ScriptObject();
	~ScriptObject();

private:
	errorsT RunCode( Value* );
	void PrepareCode();
	void InsertInternalLabel();
	std::string GetNewLabelName( bool flag = false );
	void ChangeCurrentPosition( const std::string &lab );
	bool IsReservedWord( const std::string& );
	bool IsReDeclare( const std::string& );
	static bool IsValidAssignment( TypeID );
	bool TestFuncParams( const FuncIter&, const ValList& );
	errorsT CallReservedFunc( const FuncIter&, const ValList&, Value& );
	errorsT CallFuncFromTable( const FuncIter&, const ValList&, Value* );
	errorsT CallUserFunc( const UserFuncTable::iterator&, const ValList&, Value& );
	void StackErr( int, bool flag = true );

	TypeID IsVariable( const std::string& );
	TypeID IsConstant( const std::string& );
	Variables* GetVarTable( const std::string& );
	void ClearData();
	//ф-ции
	errorsT Fun_PrintAllReservedWords( const ValList&, Value* );
	errorsT Fun_PrintCode( const ValList&, Value* );
	errorsT Fun_Help( const ValList&, Value* );
	errorsT Fun_SetAt( const ValList&, Value* );
	errorsT Fun_GetAt( const ValList&, Value* );
	errorsT Fun_Resize( const ValList&, Value* );
	errorsT Fun_Sizeof( const ValList&, Value* );
	errorsT Fun_FileOpenBin( const ValList&, Value* );
	errorsT Fun_FileOpenTxt( const ValList&, Value* );
	errorsT Fun_FileRead( const ValList&, Value* );
	errorsT Fun_FileWrite( const ValList&, Value* );
	errorsT Fun_FileRewind( const ValList&, Value* );
	errorsT Fun_FileClose( const ValList&, Value* );
	errorsT Fun_FileWriteEOL( const ValList&, Value* );
	errorsT Fun_RunScript( const ValList&, Value* );
	errorsT Fun_CreateKnot( const ValList&, Value* );
	errorsT Fun_CreateElem( const ValList&, Value* );
	errorsT Fun_SetElemM( const ValList&, Value* );
	errorsT Fun_SetElemJ( const ValList&, Value* );
	errorsT Fun_SetElemF( const ValList&, Value* );
	errorsT Fun_SetElemE( const ValList&, Value* );
	errorsT Fun_GetElemM( const ValList&, Value* );
	errorsT Fun_GetElemJ( const ValList&, Value* );
	errorsT Fun_GetElemF( const ValList&, Value* );
	errorsT Fun_GetElemE( const ValList&, Value* );
	errorsT Fun_GetLength( const ValList&, Value* );
	errorsT Fun_GetElemMatrM( const ValList&, Value* );
	errorsT Fun_GetElemMatrD( const ValList&, Value* );
	errorsT Fun_GetElemMatrC( const ValList&, Value* );
	errorsT Fun_LoadIdentity( const ValList&, Value* );
	errorsT Fun_Invert( const ValList&, Value* );
	errorsT Fun_OpenSheme( const ValList&, Value* );
	errorsT Fun_CloseSheme( const ValList&, Value* );
	errorsT Fun_SaveSheme( const ValList&, Value* );
	errorsT Fun_SaveShemeAs( const ValList&, Value* );
	errorsT Fun_GetEigen( const ValList&, Value* );
	errorsT Fun_Integrate( const ValList&, Value* );
	errorsT Fun_GetResY1( const ValList&, Value* );
	errorsT Fun_GetResY2( const ValList&, Value* );
	errorsT Fun_GetResY3( const ValList&, Value* );
	errorsT Fun_GetMatrMDC( const ValList&, Value* );
	errorsT Fun_GetElem( const ValList&, Value* );
	errorsT Fun_DelElem( const ValList&, Value* );
	errorsT Fun_GetKnot( const ValList&, Value* );
	errorsT Fun_Delete( const ValList&, Value* );
	errorsT Fun_AddElement( const ValList&, Value* );

public:
	//инициализация таблиц
	static Commands InitCommandTable();
	static Functions InitFuncTable();
	static Types InitTypeTable();
	static Variables InitConstTable();
	static std::vector<std::string> InitErrMesTable();

	static const int TAB_SIZE;//величина табуляции при "print ,"
	//длина куска текста программы, где найдена ошибка, для вывода сообщения:
	static const int MAX_ERRMES_LEN;

private:
	//указатель на окно, куда выводится информация:
	CScriptDoc *m_pDoc;
	//строка с результатом вывода на экран
	std::string m_strOutput;
	//к переменной лучше напрямую не обращаться,
	//а использовать ф-цию:
	void SetOutput( const std::string& );

	//все возможные значения флага
	typedef enum{ FLG_EQ = 0, FLG_GT, FLG_LT }	LogicalFlag;
	//флаг, выставляемый в соответствующее значение после выполнения cmp
	LogicalFlag m_Flag;
	//флаг о том, что скрипт можно запускать.
	//выставляется после компиляции
	//и снимается после загрузки нового текста:
	bool m_bRunable;
	//флаг о том, что идёт компиляция, иначе идёт выполнение:
	bool m_bCompiling;
	//флаг о том, что предыдущая команда была IF 
	//(это нужно для отслежывания корректности NEXT)
	bool m_bIFExec;
	//текст скрипта:
	std::string m_Text;
	//откомпилированный код скрипта:
	Code m_Code;
	// текущий итератор, на место которого
	//надо вставлять новые откомпиленные команды:
	CommandPointer m_CurrentPosition;
	//строка с именем метки, которая должна быть вставлена после 
	//очередной команды. Если строка пустая, то ничего вставлять не надо.
	std::string m_InternalLabel;

	std::string::iterator prog; // points into the program 

	//таблица зарезервированных ф-ций
	static Functions m_FuncTable;
	//таблица типов
	static Types m_TypeTable;
	//таблица команд
	static Commands m_CommandTable;
	//таблицы глобальных переменных
	Variables m_Vars;
	//таблица костант
	static Variables m_ConstTable;

	std::string token;//текущее, взятое из текста скрипта выражение
	typesT token_type;
	SBtokensT tok;

	typedef std::map<std::string,std::string::iterator> Labels;//карта меток
	typedef Labels::value_type MakeLabel;
	//таблица найденных в программе меток
	Labels m_LabelTable;
	//список объявленных в программе включаемых скриптов
	ScriptList m_ScriptList;

	ForStack m_ForStack;// stack для циклов FOR/NEXT

	//стэк для поддержки GOSUB/RETURN. При каждом GOSUB сюда заносится
	//итератор команды в откомпиленном коде для возврата по RETURN.
	//Стэк используется только при исполнении кода (RUN), т.к. при
	//компиляции иногда невозможно выяснить какой GOSUB вызвал данную
	//подпрограмму, а значит куда надо вернуть исполнение при RETURN:
	SubStack m_SubStack;

	//таблица сообщений об ошибках:
	static std::vector<std::string> m_ErrMesTable;

	//кол-во найденных ошибок при компиляции
	int m_ErrNum;
	//кол-во найденных предупреждений при компиляции
	int m_WarningNum;
	//флаг о том, что произошла фатальная ошибка:
	static bool m_bFatalCrash;

	//указатель на разбираемую в данный момент пользовательскую ф-цию
	//если сейчас такой ф-ции нет, то m_pCurrentUserFunc == NULL !
	CurrentUserFunc *m_pCurrentUserFunc;

	//карта пользовательских ф-ций
	UserFuncTable m_UserFuncTable;

	//стэк карт локальных переменных
	//сюда, при каждом вызове пользовательской ф-ции, заносится карта
	//её локальных переменных (включая параметры), а после возврата из ф-ции
	//из стэка выталкивается её карта
	LocalVarStack m_LocalVarStack;
	////////////////////////////////////////////////////
	void ScanScriptText();
	void find_eol();
	//обработчики команд
	void Compile_print();
	void Compile_rem();
	void Compile_break();
	void Compile_goto();
	void Compile_if();
	void Compile_for();
	void Compile_next();
	void Compile_gosub();
	void Compile_return();
	void Compile_assignment();
	void Compile_end();
	void Compile_CallFunc();
	void Compile_UserFunc( TypeID );
	void CompileScripts();

	void VarDeclare();
	void DeclareUserFunc( const std::string& );
	/////////////////////////////
	errorsT Exec_MovExpr( CCommand* );
	errorsT Exec_Add( CCommand* );
	errorsT Exec_Print( CCommand* );
	errorsT Exec_CmpVarExpr( CCommand* );
	errorsT Exec_CmpExprVal( CCommand* );
	errorsT Exec_Jmp( CCommand* );
	errorsT Exec_Je( CCommand* );
	errorsT Exec_Jg( CCommand* );
	errorsT Exec_Jl( CCommand* );
	errorsT Exec_Call( CCommand* );
	errorsT Exec_PushSub( CCommand* );
	errorsT Exec_Ret( CCommand* );
	/////////////////////////////
	std::string::iterator find_label( const std::string &s, bool test = false );

	typesT get_token();
	void putback();

	void ErrMesExpr( const std::string& );
	void ErrMesCompile( errorsT, bool flag = true );
	void ErrMesFatal( errorsT );
	void ErrMesRun( errorsT );
	void ErrMesWarning( errorsT );
	
	Value find_var( const std::string &s );
	bool is_sp_tab(char c);
	bool isdelim(char c);
	SBtokensT look_up( std::string &s );

};//class ScriptObject
////////////////////////////////////////////////////////////////

#endif // !defined(AFX_SCRIPTHEADER_H__88C31017_C0BB_11D5_B89C_FE2BA355A53D__INCLUDED_)
