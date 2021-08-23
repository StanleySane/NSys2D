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
	Expression step;//��� ����������
	std::string lab1, lab2;//����� ��������� ��� ���������� NEXT
	//� ��� ������������ ����� ������ ��������������
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
	//��������� ������
	////////////////////////////////////////////////////////////////
//������ ������������ ������:
class CComLabel: public CCommand
{
//����� ��������� ������� "�����"
//����� ���������� ������� ������� ������ ������ ���� �������
//�� ������ ����, � ������ �� ��� � �������� ���� Jxx (jmp, jge, ...)
//������ ���� �������� �� ��������� ������, ��������� ��
//������ �������� "�����" � ������ ����
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
//����� ������� "mov variable,expression"
//� ���������� name ��������� �������� ��������� expr
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
//����� ������� "add variable,value"
//� ���������� name ������������ �������� val,
//� ��������� ��������� � name
	CComAdd& operator=(const CComAdd&);
	CComAdd( const CComAdd& );

public:
	std::string m_name;//��� ���������� (������ ���� int !)
	Expression m_val;//������������ � ��� ��������

	CComAdd( const std::string &name, const Expression &val ):CCommand(CMD_ADD),
		m_name(name), m_val(val)
	{}
	virtual ~CComAdd(){}
};

class CComPrint: public CCommand
{
//����� ������� "print expression"
//����� �� ����� ��������� (��� �������� ���������) expr
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
//����� ������� "cmp varname,expression"
//������������ �������� ���������� � ��������� � ������������ ��������������� ����.
//� ������ ������ ������� ���� ���������� � ��������� ������ INT.
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
//����� ������� "cmp expression,value"
//������������ �������� ��������� expr � �������� val
//� ������������ ��������������� ����.
//��� ���������� �������� ��������� m_expr ��� �������� ����������
//� ���� �������� m_val.
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
//����� ������� "jmp label"
//����������� ������� �� ����� label
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
//����� ������� "je label"
//�������� ������� �� ����� label, ���� ���� ��������� � �������� EQ
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
//����� ������� "jg label"
//�������� ������� �� ����� label, ���� ���� ��������� � �������� GT
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
//����� ������� "jl label"
//�������� ������� �� ����� label, ���� ���� ��������� � �������� LT
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
//����� ������� "call func"
//�������� �� ���������� �-��� name
	CComCall& operator=(const CComCall&);
	CComCall( const CComCall& );

public:
	Expression m_func;//�-���

	CComCall( const Expression &name ):CCommand(CMD_CALL),
		m_func(name)
	{}
	virtual ~CComCall(){}
};

class CComEnd: public CCommand
{
//����� ������� "end"
//���������� ���������� ���������
	CComEnd& operator=(const CComEnd&);
	CComEnd( const CComEnd& );

public:
	CComEnd():CCommand(CMD_END)
	{}
	virtual ~CComEnd(){}
};

class CComPushSub: public CCommand
{
//����� ������� "push_sub label"
//������ � ���� ����������� ��������� ������� (��������� ����� �� ������ label),
//������� ������ ���� ������� ��� ���������� RETURN ������ ��� ������� GOSUB.
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
//����� ������� "ret"
//������ �� ����� ����������� ��������� �������, ��������� ����� �� GOSUB��,
//��������� ������ ������������ � ������� �� � ����������.
	CComRet& operator=(const CComRet&);
	CComRet( const CComRet& );

public:
	CComRet():CCommand(CMD_RET)
	{}
	virtual ~CComRet(){}
};

class CComRetf: public CCommand
{
//����� ������� "retf expr"
//���������� ��������� expr � ��������� ��� �������� � ������ �����
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
//�����, �������������� ������ � ������� ����������� ����������������
//�-���. ������������ ������ ��� ����������.
	void InitBy( const CurrentUserFunc &uf )
	{
		m_label = uf.m_label;
		m_name = uf.m_name;
		m_RetType = uf.m_RetType;
	}
public:
	std::string m_Start;//����� ������ ���� �-���.
	bool m_bIsReturn;//���� � ���, ��� � ���� ������� �-���
	//���� ������� "RETURN expr". ���� �� �� ���� (m_bIsReturn==false),
	//�� ��� ������.
	std::string m_label;//��� �����, ������ ����� �� ���� �-����.
	//��� ����� ���� ������� ����� �� �������� "END func_name".
	std::string m_name;//��� ���������������� �-���.
	TypeID m_RetType;//��� ������������� �������� 
	//(��� ���������������� �-��� ������ ����-������ �������)
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
	//������������� �-��� � ����������
	bool m_bDebug;//��������� ���� �� �������
	bool m_bBreak;//���� � ���������� ����������

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
	//�-���
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
	//������������� ������
	static Commands InitCommandTable();
	static Functions InitFuncTable();
	static Types InitTypeTable();
	static Variables InitConstTable();
	static std::vector<std::string> InitErrMesTable();

	static const int TAB_SIZE;//�������� ��������� ��� "print ,"
	//����� ����� ������ ���������, ��� ������� ������, ��� ������ ���������:
	static const int MAX_ERRMES_LEN;

private:
	//��������� �� ����, ���� ��������� ����������:
	CScriptDoc *m_pDoc;
	//������ � ����������� ������ �� �����
	std::string m_strOutput;
	//� ���������� ����� �������� �� ����������,
	//� ������������ �-���:
	void SetOutput( const std::string& );

	//��� ��������� �������� �����
	typedef enum{ FLG_EQ = 0, FLG_GT, FLG_LT }	LogicalFlag;
	//����, ������������ � ��������������� �������� ����� ���������� cmp
	LogicalFlag m_Flag;
	//���� � ���, ��� ������ ����� ���������.
	//������������ ����� ����������
	//� ��������� ����� �������� ������ ������:
	bool m_bRunable;
	//���� � ���, ��� ��� ����������, ����� ��� ����������:
	bool m_bCompiling;
	//���� � ���, ��� ���������� ������� ���� IF 
	//(��� ����� ��� ������������ ������������ NEXT)
	bool m_bIFExec;
	//����� �������:
	std::string m_Text;
	//����������������� ��� �������:
	Code m_Code;
	// ������� ��������, �� ����� ��������
	//���� ��������� ����� ������������� �������:
	CommandPointer m_CurrentPosition;
	//������ � ������ �����, ������� ������ ���� ��������� ����� 
	//��������� �������. ���� ������ ������, �� ������ ��������� �� ����.
	std::string m_InternalLabel;

	std::string::iterator prog; // points into the program 

	//������� ����������������� �-���
	static Functions m_FuncTable;
	//������� �����
	static Types m_TypeTable;
	//������� ������
	static Commands m_CommandTable;
	//������� ���������� ����������
	Variables m_Vars;
	//������� �������
	static Variables m_ConstTable;

	std::string token;//�������, ������ �� ������ ������� ���������
	typesT token_type;
	SBtokensT tok;

	typedef std::map<std::string,std::string::iterator> Labels;//����� �����
	typedef Labels::value_type MakeLabel;
	//������� ��������� � ��������� �����
	Labels m_LabelTable;
	//������ ����������� � ��������� ���������� ��������
	ScriptList m_ScriptList;

	ForStack m_ForStack;// stack ��� ������ FOR/NEXT

	//���� ��� ��������� GOSUB/RETURN. ��� ������ GOSUB ���� ���������
	//�������� ������� � ������������� ���� ��� �������� �� RETURN.
	//���� ������������ ������ ��� ���������� ���� (RUN), �.�. ���
	//���������� ������ ���������� �������� ����� GOSUB ������ ������
	//������������, � ������ ���� ���� ������� ���������� ��� RETURN:
	SubStack m_SubStack;

	//������� ��������� �� �������:
	static std::vector<std::string> m_ErrMesTable;

	//���-�� ��������� ������ ��� ����������
	int m_ErrNum;
	//���-�� ��������� �������������� ��� ����������
	int m_WarningNum;
	//���� � ���, ��� ��������� ��������� ������:
	static bool m_bFatalCrash;

	//��������� �� ����������� � ������ ������ ���������������� �-���
	//���� ������ ����� �-��� ���, �� m_pCurrentUserFunc == NULL !
	CurrentUserFunc *m_pCurrentUserFunc;

	//����� ���������������� �-���
	UserFuncTable m_UserFuncTable;

	//���� ���� ��������� ����������
	//����, ��� ������ ������ ���������������� �-���, ��������� �����
	//� ��������� ���������� (������� ���������), � ����� �������� �� �-���
	//�� ����� ������������� � �����
	LocalVarStack m_LocalVarStack;
	////////////////////////////////////////////////////
	void ScanScriptText();
	void find_eol();
	//����������� ������
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
