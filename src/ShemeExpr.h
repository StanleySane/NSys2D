// ShemeExpr.h: interface for the CShemeExpr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHEMEEXPR_H__1EF16442_929F_11D6_B89E_FE2BA355A53D__INCLUDED_)
#define AFX_SHEMEEXPR_H__1EF16442_929F_11D6_B89E_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include<list>
#include<string>
#include<map>

class CShemeExpr;
class CShemeVarsTable;

typedef std::list<CShemeExpr*> ShemeFuncParamList;

typedef std::map<std::string,CShemeExpr*> ShemeVarsTable;
typedef ShemeVarsTable::value_type MakeShemeVar;
typedef std::pair<ShemeVarsTable::iterator,bool> ShemeVarsPair;

typedef enum
{
	SEE_NOERR = 0,
	SEE_PARENS,
	SEE_NEG_SQRT,
	SEE_FP_ERR,
	SEE_DIV_ZERO,
	SEE_UNKN_ERR,
	SEE_NOEXP,
	SEE_NOMEM,
	SEE_SERROR,
	SEE_CERROR,
	SEE_WRONG_SIMBOL,
	SEE_WRONG_FUNC_PARAM_NUM,
	SEE_CYCLE
}	ShemeExprErr;

class CShemeExpr
{
public:
	typedef enum
	{
		FPN_ZERO = 0,
		FPN_ONE,
		FPN_TWO,
		FPN_THREE,
		FPN_ONE_TWO = 100
	}	FuncParamNum;//����� ���-��� �-���
	typedef enum
	{
		OT_WRONG = 0,
		OT_ADDSUB,
		OT_MULTDIV,
		OT_POW,
		OT_VALUE,
		OT_FUNC,
		OT_RELATION
	}	OperType;//���� ��������
	//���������� �-���
	typedef enum
	{
		FID_WRONG = 0,
		FID_SIGN,
		FID_SIN,
		FID_COS,
		FID_SINH,
		FID_COSH,
		FID_TAN,
		FID_SQRT,
		FID_LOG,
		FID_LOG10,
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
		FID_IF,
		FID_HEV
	} InternalFuncID;

	//////////////////////////////////////////////////////////////////
	//��������� ������ ��������
	class Operation
	{
		Operation( const Operation& );
		Operation& operator=( const Operation& );

		OperType m_OperType;
	protected:
		ShemeExprErr m_CompileErrCode, m_RunErrCode;
		std::string m_strErrorCause;//������� ������: ��� �-��� � �.�.
	public:
		Operation( OperType ot = OT_WRONG ):m_OperType(ot), m_CompileErrCode(SEE_NOERR), m_RunErrCode(SEE_NOERR)
		{}
		virtual ~Operation()
		{}
		virtual double GetValue( CShemeVarsTable* ) = 0;
		virtual void ClearErrCode() = 0;
		virtual Operation* Optimize() = 0;

		ShemeExprErr GetErrorCode( bool cmpl = true )//cmpl - ���� � ���, ��� ���� �������� ��� ������ ��� ����������
		{	return (cmpl)?m_CompileErrCode:m_RunErrCode;	}
		std::string GetErrorCause() const
		{	return m_strErrorCause;	}
		OperType GetOperType() const
		{	return m_OperType;	}
	};

private:
	class OperRelation:public Operation
	{
		OperRelation( const OperRelation& );
		OperRelation& operator=( const OperRelation& );

		std::string::iterator m_from, m_to;
		typedef enum{ LE = 1, GE, NE, LT = '<', GT = '>', EQ = '=' }	RelOper;
		RelOper m_OpCode;//��� ��������
		Operation *m_Left, *m_Right;//��������

		ShemeExprErr MakeTree( CShemeVarsTable* );
	public:
		OperRelation( const std::string::iterator &from, const std::string::iterator &to, CShemeVarsTable* );
		virtual ~OperRelation();

		virtual double GetValue( CShemeVarsTable* );
		virtual Operation* Optimize();
		virtual void ClearErrCode();
	};

	class OperAddSub:public Operation
	{
		OperAddSub( const OperAddSub& );
		OperAddSub& operator=( const OperAddSub& );

		std::string::iterator m_from, m_to;
		char m_OpCode;//��� ��������
		Operation *m_Left, *m_Right;//��������

		ShemeExprErr MakeTree( CShemeVarsTable* );
	public:
		OperAddSub( const std::string::iterator &from, const std::string::iterator &to, CShemeVarsTable* );
		virtual ~OperAddSub();

		virtual double GetValue( CShemeVarsTable* );
		virtual Operation* Optimize();
		virtual void ClearErrCode();
	};

	class OperMultDiv:public Operation
	{
		OperMultDiv( const OperMultDiv& );
		OperMultDiv& operator=( const OperMultDiv& );

		std::string::iterator m_from, m_to;
		char m_OpCode;//��� ��������
		Operation *m_Left, *m_Right;//��������

		ShemeExprErr MakeTree( CShemeVarsTable* );
	public:
		OperMultDiv( const std::string::iterator &from, const std::string::iterator &to, CShemeVarsTable* );
		virtual ~OperMultDiv();

		virtual double GetValue( CShemeVarsTable* );
		virtual Operation* Optimize();
		virtual void ClearErrCode();
	};

	class OperPow:public Operation
	{
		OperPow( const OperPow& );
		OperPow& operator=( const OperPow& );

		std::string::iterator m_from, m_to;
		Operation *m_Left, *m_Right;//��������

		ShemeExprErr MakeTree( CShemeVarsTable* );
	public:
		OperPow( const std::string::iterator &from, const std::string::iterator &to, CShemeVarsTable* );
		virtual ~OperPow();

		virtual double GetValue( CShemeVarsTable* );
		virtual Operation* Optimize();
		virtual void ClearErrCode();
	};

	class OperValue:public Operation
	{
		OperValue( const OperValue& );
		OperValue& operator=( const OperValue& );

		std::string::iterator m_from, m_to;
		Operation *m_Tree;//������� - ��������� ��� �-���
		std::string m_VarName;//��� ����������
		double m_dValue;//���������
		bool m_bNeg;//���� � ���, ��� �������� � ������� �������

		ShemeExprErr MakeTree( CShemeVarsTable* );
	public:
		OperValue( const std::string::iterator &from, const std::string::iterator &to, CShemeVarsTable* );
		OperValue( double val, CShemeVarsTable* );
		virtual ~OperValue();

		virtual double GetValue( CShemeVarsTable* );
		ShemeExprErr SetValue( double );
		virtual Operation* Optimize();
		virtual void ClearErrCode();

		bool IsConstant() const;
		bool IsVarName() const;
	};

	class OperCallFunc:public Operation
	{
		OperCallFunc( const OperCallFunc& );
		OperCallFunc& operator=( const OperCallFunc& );

		/*
		typedef enum
		{
			FT_INTERNAL = 0,//����������
			FT_RESERVED,//����������������� � ��������
			FT_USER//����������������
		}	FuncType;//�������������� �-���
		FuncType m_ft;
		*/
		std::string m_FuncName;//��� �-��� (� ����� �������� !)
		std::string m_Params;//���������
		ShemeFuncParamList m_ParamsList;//������ ���-��� �-���
		InternalFuncID m_FuncID;//���� ���������� �-��� �������, ����� � ID

		ShemeExprErr MakeTree( CShemeVarsTable* );
	public:
		OperCallFunc( const std::string &name, const std::string &params, CShemeVarsTable* );
		virtual ~OperCallFunc();

		virtual double GetValue( CShemeVarsTable* );
		virtual Operation* Optimize();
		virtual void ClearErrCode();
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
		static double FunSin( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunSign( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunCos( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunCosh( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunSinh( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunTan( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunSqrt( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunLog( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunLog10( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunAsin( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunAcos( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunExp( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunFloor( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunCeil( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunFabs( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunAbs( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunAtan( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunFmod( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunPower( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunRound( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunRandom( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunIf( const ShemeFuncParamList&, ShemeExprErr&, std::string& );
		static double FunHev( const ShemeFuncParamList&, ShemeExprErr&, std::string& );

		FuncParamNum m_ParamNum;//����� ���������� �-���
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
		static double GetValue( InternalFuncID, const ShemeFuncParamList&, ShemeExprErr&, CShemeVarsTable*, std::string& );
	};
	//////////////////////////////////////////////////////////////////
	typedef std::map<std::string,InternalFunc> InternalFuncMap;
	static InternalFuncMap m_FuncTable;
	static const double DOUBLE_ZERO;
private:
	friend class OperCallFunc;
	friend class InternalFunc;

	CShemeVarsTable *m_pVarsTable;
	std::string m_expr;
	std::string m_strErrorCause;
	ShemeExprErr m_CompileErrCode;//��� ������, ��������� ��� ������� ���������
	//������������ ����� ����� ������� ��������� (� ������������) ��� ����� Reset
	ShemeExprErr m_RunErrCode;//��� ������, ��������� ��� ������ GetValue, �.�. ��� ����������.
	//������������ ����� ������ GetValue, ������� ���� ��������� m_RunErrCode
	//����� ����� GetValue, ����� ���� ��������� � ���, ��� ��������, 
	//������������ ������ �-����, ����� �����!
	Operation *m_Tree;

	static InternalFuncMap InitFuncTable();
	void Init();
	void Init( double );
	void Destruct();
	void MakeTree();
	void Optimize();

	CShemeExpr& operator = ( const CShemeExpr& );
	CShemeExpr( const CShemeExpr& );
public:
	CShemeExpr( CShemeVarsTable *p = NULL );
	explicit CShemeExpr( const std::string &str, CShemeVarsTable* );
	explicit CShemeExpr( const CString &str, CShemeVarsTable* );
	explicit CShemeExpr( double, CShemeVarsTable* );
	virtual ~CShemeExpr();
	void InitBy( const CShemeExpr& );
	void Serialize( CArchive& );

	bool IsConstant() const;
	bool IsVarName() const;
	std::string GetExpr() const
	{	return m_expr;	}
	ShemeExprErr SetValue( double );
	ShemeExprErr Reset( const std::string&, CShemeVarsTable *p = NULL );
	ShemeExprErr Reset( const CString&, CShemeVarsTable *p = NULL );
	double GetValue();
	ShemeExprErr GetCompileErrorCode() const
	{
		return m_CompileErrCode;
	}
	ShemeExprErr GetRunErrorCode() const
	{
		return m_RunErrCode;
	}
	std::string GetErrorCause() const
	{	return m_strErrorCause;	}
	std::string GetFullErrorMsg( ShemeExprErr ) const;

	static std::string GetErrorMessage( const ShemeExprErr& );
	static void PassSpaces( std::string::iterator&, const std::string::iterator& );
	static bool FindParen( std::string::iterator&, const std::string::iterator& );
	static ShemeExprErr FindOperation( const char*, std::string::iterator&, const std::string::iterator& );
	static bool IsInternalFunc( const std::string &name );

//	friend bool operator < ( const CShemeExpr&, const CShemeExpr& );
//	friend bool operator == ( const CShemeExpr&, const CShemeExpr& );

};//class Expression

#endif // !defined(AFX_SHEMEEXPR_H__1EF16442_929F_11D6_B89E_FE2BA355A53D__INCLUDED_)
