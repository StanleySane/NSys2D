/////////////////////////////////////////////////////////////////////
//	file ScriptDefs.h
/////////////////////////////////////////////////////////////////////

#if !defined(_SCRIPT_DEFS_H_)
#define _SCRIPT_DEFS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include<string>
#include<map>

//макрос, показывающий условие, когда в ф-ции get_token() произошла
//ошибка чтения выражения.
#define TOKEN_ERR (m_bCompiling&&(tok==UNKNCOM)&&(token_type==UNDEFTOK))

void MakeLower( std::string &str );
void CutEOL( std::string& );
std::string FormatString( const char *format, ... );

const double DOUBLE_ZERO = 1e-100;

//все возможные команды в откомпилированном коде:
typedef enum
{
	CMD_NONE = 0,
	CMD_LABEL,
	CMD_MOV_EXPR,
	CMD_ADD,
	CMD_PRINT,
	CMD_CMP_VAR_EXPR,
	CMD_CMP_EXPR_VAL,
	CMD_JMP,
	CMD_JE,
	CMD_JG,
	CMD_JL,
	CMD_CALL,
	CMD_END,
	CMD_PUSH_SUB,
	CMD_RET,
	CMD_RETF
} CommandID;

// The token types.
typedef enum
{
	UNDEFTOK = 0, 
	OPERATOR, 
	NUMBER, 
	VARIABLE, 
	COMMAND, 
	STRING,
	FUNCTION,
	TYPE,
	QUOTE 
} typesT;
// The command tokens.
typedef enum
{ 
	UNKNCOM = 0, 
	PRINT, 
	IF, 
	THEN, 
	FOR, 
	NEXT, 
	TO,
	STEP,
	GOTO, 
	GOSUB, 
	RETURN,
	REM,
	BREAK,
	SOME_FUNC,
	USER_FUNC,
	SOME_TYPE,
	EOL, 
	FINISHED, 
	END 
} SBtokensT;
typedef std::map<std::string,SBtokensT> Commands;
typedef Commands::value_type MakeCommand;

typedef enum 
{
	NOERR = 0, END_CMD, NOMEM, RUN_ERR,
	SERROR, CERROR, UNKN_ERR, PARENS, NOEXP, DIV_ZERO, EQUAL_EXP,
	NOT_VAR, DUP_LAB, UNDEF_LAB,
	THEN_EXP, TO_EXP, TARGET_EXP, STEP_ERR,
	NEXT_WO_FOR, NEXT_VAR_ERR,
	RET_WO_GOSUB, MISS_QUOTE,
	WRONG_SIMBOL, WRONG_FUNC_PARAM, WRONG_FUNC_PARAM_NUM,
	CONVERT_ERR,
	TYPE_OP_ERR, INT_POWER, FP_ERR, NEG_SQRT,
	BREAK_ERR, STACK_CRASH, MISSING_IF_CMD,
	IF_CMD_ERR, FOR_ERR, WRONG_END, NO_USER_RETURN,
	USER_FUNC_ERR, RESERVED_WORD, REDECLARE, 
	FOREVER_CYCLE, NO_CYCLE, ONE_TIME_CYCLE,
	ARRAY_ACCESS, FILE_OPEN
} errorsT;//коды ошибок

//зарезервированные ф-ции
typedef enum
{
	FUN_WRONG = 0,
	FUN_PRINTALLRESERVEDWORDS,
	FUN_PRINTCODE,
	FUN_SETAT,
	FUN_GETAT,
	FUN_RESIZE,
	FUN_SIZEOF,
	FUN_FILEOPENTXT,
	FUN_FILEOPENBIN,
	FUN_FILEREAD,
	FUN_FILEWRITE,
	FUN_FILEREWIND,
	FUN_FILECLOSE,
	FUN_WRITEEOL,
	FUN_RUNSCRIPT,
	FUN_CREATEKNOT,
	FUN_CREATEELEM,
	FUN_SETELEMM,
	FUN_SETELEMJ,
	FUN_SETELEMF,
	FUN_SETELEME,
	FUN_GETELEMM,
	FUN_GETELEMJ,
	FUN_GETELEMF,
	FUN_GETELEME,
	FUN_GETLENGTH,
	FUN_GETELEMMATRM,
	FUN_GETELEMMATRD,
	FUN_GETELEMMATRC,
	FUN_LOADIDENTITY,
	FUN_INVERT
} FunctionID;

typedef std::map<std::string,FunctionID> Functions;
typedef Functions::value_type MakeFunc;
typedef Functions::iterator FuncIter;

//зарезервированные типы
typedef enum
{
	TYPE_UNKNOWN = 0,
	TYPE_BOOL,
	TYPE_INT,
	TYPE_DOUBLE,
	TYPE_STRING,
	TYPE_ARRAY_INT,
	TYPE_ARRAY_DOUBLE,
	TYPE_ARRAY_STRING,
	TYPE_ARRAY_BOOL,
	TYPE_FILE,
	TYPE_SCRIPT,
	TYPE_MATR,
	TYPE_SHEME,
	TYPE_ROD,
	TYPE_HARDROD,
	TYPE_SPRING,
	TYPE_DEMFER,
	TYPE_MASS,
	TYPE_KNOT
	//ниже ещё нету
} TypeID;

typedef std::map<std::string,TypeID> Types;
typedef Types::value_type MakeType;
//далее идут таблицы переменных
typedef std::map<std::string,bool> VarBool;
typedef VarBool::value_type MakeBool;
typedef std::map<std::string,int> VarInteger;
typedef VarInteger::value_type MakeInt;
typedef std::map<std::string,double> VarDouble;
typedef VarDouble::value_type MakeDouble;
typedef std::map<std::string,std::string> VarString;
typedef VarString::value_type MakeString;

#endif // !defined(_SCRIPT_DEFS_H_)
