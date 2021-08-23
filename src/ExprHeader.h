/////////////////////////////////////////////////////////////////
//	file ExprHeader.h
/////////////////////////////////////////////////////////////////

#ifndef _EXPR_HEADER_H_
#define _EXPR_HEADER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include"ScriptDefs.h"
#include"UserFuncHeader.h"
#include<list>

class Value;
class ScriptObject;
class Expression;
typedef std::list<Expression*> FuncParamList;

class Expression
{
public:
	typedef enum
	{
		FPN_ZERO = 0,
		FPN_ONE,
		FPN_TWO,
		FPN_THREE,
		FPN_ONE_TWO = 100
	}	FuncParamNum;//число пар-ров ф-ции
	typedef enum
	{
		OT_WRONG = 0,
		OT_ADDSUB,
		OT_MULTDIV,
		OT_POW,
		OT_VALUE,
		OT_FUNC,
		OT_RELATION
	}	OperType;//типы операций
	//встроенные ф-ции
	typedef enum
	{
		FID_WRONG = 0,
		FID_SIN,
		FID_COS,
		FID_TAN,
		FID_SQRT,
		FID_LOG,
		FID_ASIN,
		FID_ACOS,
		FID_ATAN,
		FID_POWER,
		FID_EXP,
		FID_FLOOR,
		FID_CEIL,
		FID_ROUND,
		FID_FABS,
		FID_ABS,
		FID_FMOD,
		FID_RANDOM,
		FID_ATOI,
		FID_ATOF,
		FID_TRANSPOSE,
		FID_ROWS,
		FID_COLS
	} InternalFuncID;

	//////////////////////////////////////////////////////////////////
	//вложенные классы операций
	class Operation
	{
		Operation( const Operation& );
		Operation& operator=( const Operation& );

		OperType m_OperType;
	protected:
		errorsT m_CompileErrCode, m_RunErrCode;
	public:
		Operation( OperType ot = OT_WRONG ):m_OperType(ot), m_CompileErrCode(NOERR), m_RunErrCode(NOERR)
		{}
		virtual ~Operation()
		{}
		virtual Value GetValue( ScriptObject* ) = 0;
		errorsT GetErrorCode( bool cmpl = true )//cmpl - флаг о том, что надо выводить код ошибки при компиляции
		{	return (cmpl)?m_CompileErrCode:m_RunErrCode;	}
		OperType GetOperType() const
		{	return m_OperType;	}
		void ClearErrCode()
		{	m_RunErrCode = NOERR;	}
		virtual Operation* Optimize() = 0;
	};

private:
	class OperRelation:public Operation
	{
		OperRelation( const OperRelation& );
		OperRelation& operator=( const OperRelation& );

		std::string::iterator m_from, m_to;
		typedef enum{ LE = 1, GE, NE, LT = '<', GT = '>', EQ = '=' }	RelOper;
		RelOper m_OpCode;//код операции
		Operation *m_Left, *m_Right;//операнды

		errorsT MakeTree( ScriptObject *p );
	public:
		OperRelation( const std::string::iterator &from, const std::string::iterator &to, ScriptObject *p );
		virtual ~OperRelation();

		virtual Value GetValue( ScriptObject* );
		virtual Operation* Optimize();
	};

	class OperAddSub:public Operation
	{
		OperAddSub( const OperAddSub& );
		OperAddSub& operator=( const OperAddSub& );

		std::string::iterator m_from, m_to;
		char m_OpCode;//код операции
		Operation *m_Left, *m_Right;//операнды

		errorsT MakeTree( ScriptObject *p );
	public:
		OperAddSub( const std::string::iterator &from, const std::string::iterator &to, ScriptObject *p );
		virtual ~OperAddSub();

		virtual Value GetValue( ScriptObject* );
		virtual Operation* Optimize();
	};

	class OperMultDiv:public Operation
	{
		OperMultDiv( const OperMultDiv& );
		OperMultDiv& operator=( const OperMultDiv& );

		std::string::iterator m_from, m_to;
		char m_OpCode;//код операции
		Operation *m_Left, *m_Right;//операнды

		errorsT MakeTree( ScriptObject *p );
	public:
		OperMultDiv( const std::string::iterator &from, const std::string::iterator &to, ScriptObject *p );
		virtual ~OperMultDiv();

		virtual Value GetValue( ScriptObject* );
		virtual Operation* Optimize();
	};

	class OperPow:public Operation
	{
		OperPow( const OperPow& );
		OperPow& operator=( const OperPow& );

		std::string::iterator m_from, m_to;
		Operation *m_Left, *m_Right;//операнды

		errorsT MakeTree( ScriptObject *p );
	public:
		OperPow( const std::string::iterator &from, const std::string::iterator &to, ScriptObject *p );
		virtual ~OperPow();

		virtual Value GetValue( ScriptObject* );
		virtual Operation* Optimize();
	};

	class OperValue:public Operation
	{
		OperValue( const OperValue& );
		OperValue& operator=( const OperValue& );

		std::string::iterator m_from, m_to;
		Operation *m_Tree;//операнд - выражение или ф-ция
		std::string m_VarName;//имя переменной
		Value *m_pValue;//константа
		bool m_bNeg;//флаг о том, что значение с унарным минусом

		errorsT MakeTree( ScriptObject* );
	public:
		OperValue( const std::string::iterator &from, const std::string::iterator &to, ScriptObject* );
		virtual ~OperValue();

		virtual Value GetValue( ScriptObject* );
		virtual Operation* Optimize();
		bool IsConstant() const;
		bool IsVarName() const;
	};

	class OperCallFunc:public Operation
	{
		OperCallFunc( const OperCallFunc& );
		OperCallFunc& operator=( const OperCallFunc& );

		typedef enum
		{
			FT_INTERNAL = 0,//встроенная
			FT_RESERVED,//зарезервированная в скриптах
			FT_USER//пользовательская
		}	FuncType;//пренадлежность ф-ции
		FuncType m_ft;
		std::string m_FuncName;//имя ф-ции (в любом регистре !)
		std::string m_Params;//параметры
		FuncParamList m_ParamsList;//список пар-ров ф-ции
		InternalFuncID m_FuncID;//если встроенная ф-ция найдена, здесь её ID
		FuncIter m_ReservedIt;//итератор найденной зарезервированной ф-ции
		UserFuncTable::iterator m_UserIt;

		errorsT MakeTree( ScriptObject* );
	public:
		OperCallFunc( const std::string &name, const std::string &params, ScriptObject* );
		virtual ~OperCallFunc();

		virtual Value GetValue( ScriptObject* );
		virtual Operation* Optimize();
	};
	//////////////////////////////////////////////////////////////////
public:
	class InternalFunc
	{
		void InitBy( const InternalFunc &ob )
		{
			m_ParamNum = ob.m_ParamNum;
			m_ID = ob.m_ID;
		}
	public:
		static Value FunSin( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunCos( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunTan( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunSqrt( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunLog( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunAsin( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunAcos( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunExp( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunFloor( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunCeil( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunFabs( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunAbs( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunAtan( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunFmod( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunPower( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunRound( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunRandom( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunAtoi( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunAtof( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunTranspose( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunRows( const FuncParamList&, errorsT&, ScriptObject* );
		static Value FunCols( const FuncParamList&, errorsT&, ScriptObject* );

		FuncParamNum m_ParamNum;//число параметров ф-ции
		InternalFuncID m_ID;

		InternalFunc( InternalFuncID id = FID_WRONG, FuncParamNum c = FPN_ZERO ):m_ParamNum(c),m_ID(id)
		{}
		~InternalFunc()
		{}
		InternalFunc( const InternalFunc &ob )
		{	InitBy(ob);	}
		InternalFunc& operator = ( const InternalFunc &ob )
		{	if( this == &ob )	return *this;
			InitBy(ob);
			return *this;
		}

		bool IsValidParamNum( int );
		static Value GetValue( InternalFuncID, const FuncParamList&, errorsT&, ScriptObject* );
	};
	//////////////////////////////////////////////////////////////////
	typedef std::map<std::string,InternalFunc> InternalFuncMap;
	static InternalFuncMap m_FuncTable;
private:
	friend class OperCallFunc;
	friend class InternalFunc;

	ScriptObject *m_pScript;
	std::string m_expr;
	errorsT m_CompileErrCode;//код ошибки, найденной при разборе выражения
	//выставляется сразу после разбора выражения (в конструкторе) или после Reset
	errorsT m_RunErrCode;//код ошибки, найденной при вызове GetValue, т.е. при выполнении.
	//выставляется после вызова GetValue, поэтому надо проверять m_RunErrCode
	//сразу после GetValue, чтобы быть уверенным в том, что значение, 
	//возвращённое данной ф-цией, имеет смысл!
	Operation *m_Tree;

	static InternalFuncMap InitFuncTable();
	void Init();
	void Destruct();
	void MakeTree();
	void Optimize();
public:
	Expression( ScriptObject *p = NULL );
	explicit Expression( const std::string &str, ScriptObject *p );
	Expression& operator = ( const Expression& );
	Expression( const Expression& );
	virtual ~Expression();

	bool IsConstant() const;
	bool IsVarName() const;
	std::string GetExpr() const
	{	return m_expr;	}
	errorsT Reset( const std::string& );
	Value GetValue( TypeID tp = TYPE_UNKNOWN );
	errorsT GetCompileErrorCode() const
	{
		return m_CompileErrCode;
	}
	errorsT GetRunErrorCode() const
	{
		return m_RunErrCode;
	}
	static void PassSpaces( std::string::iterator&, const std::string::iterator& );
	static bool FindParen( std::string::iterator&, const std::string::iterator& );
	static errorsT FindOperation( const char*, std::string::iterator&, const std::string::iterator& );
	static bool IsInternalFunc( const std::string &name );

	friend bool operator < ( const Expression&, const Expression& );
	friend bool operator == ( const Expression&, const Expression& );

};//class Expression

typedef std::list<std::pair<Expression,char> > PrintList;

#endif //_EXPR_HEADER_H_