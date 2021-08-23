// Expression.cpp: implementation of the Expression class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include"ScriptObject.h"
#include"ExprHeader.h"

#include"MatrPtr.h"
#include"AlgolMatr.h"

#include<algorithm>
#include<new>
#include<limits>
#include<cmath>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

Expression::InternalFuncMap Expression::m_FuncTable = Expression::InitFuncTable();
//////////////////////////////////////////////////////////////////
bool operator < ( const Expression &obj1, const Expression &obj2 )
{
	return obj1.GetExpr() < obj2.GetExpr();
}
bool operator == ( const Expression &obj1, const Expression &obj2 )
{
	return obj1.GetExpr() == obj2.GetExpr();
}
//////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Expression::Expression( ScriptObject *p/*=NULL*/ ):m_pScript(p)
{
	Init();
}

Expression::Expression( const string &str, ScriptObject *p ):m_expr(str), m_pScript(p)
{
	Init();
}

Expression::Expression( const Expression &ob )
{
	m_expr = ob.m_expr;
	m_pScript = ob.m_pScript;
	Init();
}

Expression& Expression::operator = ( const Expression &ob )
{
	if( this == &ob )	return *this;
	Destruct();
	m_expr = ob.m_expr;
	m_pScript = ob.m_pScript;
	Init();
	return *this;
}

Expression::~Expression()
{
	Destruct();
}

//////////////////////////////////////////////////////////////////////
//		Members
//////////////////////////////////////////////////////////////////////
bool Expression::IsInternalFunc( const std::string &name )
{
//ф-ция возвращает true, если name является именем встроенной ф-ции
//иначе - false
	if( m_FuncTable.find(name) == m_FuncTable.end() )
		return false;
	return true;
}

errorsT Expression::FindOperation( const char *opers, std::string::iterator &from, const std::string::iterator &to )
{
//ф-ция ищет в интервале [from;to) одну из операций opers
//from после выполнения указывает на найденный знак или на конец строки (т.е. from==to).
//ф-ция возвращает NOERR если интервал сбалансирован по скобкам и кавычкам,
//иначе PARENS или MISS_QUOTE (и from==to)
	while( (strchr(opers,*from) == NULL)&&(from != to) )
	{	
		if( *from == '(' )
		{
			if( !Expression::FindParen( from, to ) )
			{
				return PARENS;
			}
		}
		else
		{
			if( *from == '"' )
			{
				do
				{
					++from;
				}	while( (from != to)&&(*from != '"') );
				if( from == to )
					return MISS_QUOTE;
			}
		}
		++from;
	}
	return NOERR;
}

void Expression::PassSpaces( std::string::iterator &from, const std::string::iterator &to )
{
	if( from >= to )
		return;
	while( (from != to)&&( (*from == ' ')||(*from == '\t') ) )
		++from;
}
bool Expression::FindParen( std::string::iterator &from, const std::string::iterator &to )
{
//ф-ция находит скобку, парную той, на которую указывает from
//ф-ция возвращает true если парная скобка найдена и false в противном случае
	if( from >= to )
		return false;
	int cp = 0;//счётчик скобок
	do
	{
		switch(*from)
		{
		case '(':
			cp++;
			break;
		case ')':
			cp--;
			break;
		case '"':
			do
			{
				++from;
			}	while( (from != to)&&(*from != '"') );
			break;
		}//switch
		if( from == to )
			break;
		++from;
	}	while( (from != to)&&(cp != 0) );
	if( from != to )
	{
		--from;
		return true;
	}
	else
	{
		if( cp == 0 )
		{
			//значит парная скобка стояла в самом конце строки
			--from;
			return true;
		}
	}
	//from указывает либо на конец строки, если парной скобки нет
	//либо на найденную парную скобку
	return false;
}

errorsT Expression::Reset( const std::string &str )
{
	Destruct();
	m_expr = str;
	Init();
	return GetCompileErrorCode();
}

Value Expression::GetValue( TypeID tp )
{
	Value res;
	if( m_CompileErrCode != NOERR )
	{
		m_RunErrCode = CERROR;
		return res;
	}
	m_Tree->ClearErrCode();
	res = m_Tree->GetValue(m_pScript);
	if( (m_RunErrCode = m_Tree->GetErrorCode(false)) != NOERR )
		return res;
	if( (tp != TYPE_UNKNOWN) && !res.ConvertTo(tp) )
		m_RunErrCode = CONVERT_ERR;
	return res;
}

void Expression::Destruct()
{
	if( m_Tree != NULL )
	{
		delete m_Tree;
		m_Tree = NULL;
	}
}

bool Expression::IsConstant() const
{
	if( m_Tree->GetOperType() != OT_VALUE )
		return false;
	OperValue *op = static_cast<OperValue*>(m_Tree);
	return op->IsConstant();
}

bool Expression::IsVarName() const
{
	if( m_Tree->GetOperType() != OT_VALUE )
		return false;
	OperValue *op = static_cast<OperValue*>(m_Tree);
	return op->IsVarName();
}
/////////////////////////////////////////////////////////////////////////////////
//		внутренние ф-ции
/////////////////////////////////////////////////////////////////////////////////
inline Value Expression::InternalFunc::FunSin( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		x.SetDouble( sin(x.GetDouble()) );
	}
	return x;
}
inline Value Expression::InternalFunc::FunCos( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		x.SetDouble( cos(x.GetDouble()) );
	}
	return x;
}
inline Value Expression::InternalFunc::FunTan( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		x.SetDouble( tan(x.GetDouble()) );
	}
	return x;
}
inline Value Expression::InternalFunc::FunSqrt( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		double tmp = x.GetDouble();
		if( tmp < DOUBLE_ZERO )
		{
			er = NEG_SQRT;
			return x;
		}
		x.SetDouble( sqrt(tmp) );
	}
	return x;
}
inline Value Expression::InternalFunc::FunLog( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		x.SetDouble( log(x.GetDouble()) );
	}
	return x;
}
inline Value Expression::InternalFunc::FunAsin( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		double tmp = x.GetDouble();
		if( (tmp < -1.0) || (tmp > 1.0) )
		{
			er = FP_ERR;
			return x;
		}
		x.SetDouble( asin(tmp) );
	}
	return x;
}
inline Value Expression::InternalFunc::FunAcos( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		double tmp = x.GetDouble();
		if( (tmp < -1.0) || (tmp > 1.0) )
		{
			er = FP_ERR;
			return x;
		}
		x.SetDouble( acos(tmp) );
	}
	return x;
}
inline Value Expression::InternalFunc::FunExp( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		x.SetDouble( exp(x.GetDouble()) );
	}
	return x;
}
inline Value Expression::InternalFunc::FunFloor( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		x.SetDouble( floor(x.GetDouble()) );
	}
	return x;
}
inline Value Expression::InternalFunc::FunCeil( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		x.SetDouble( ceil(x.GetDouble()) );
	}
	return x;
}
inline Value Expression::InternalFunc::FunFabs( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		x.SetDouble( fabs(x.GetDouble()) );
	}
	return x;
}
inline Value Expression::InternalFunc::FunAbs( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_INT);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		x.SetInt( abs(x.GetInt()) );
	}
	return x;
}
inline Value Expression::InternalFunc::FunAtan( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		x.SetDouble( atan(x.GetDouble()) );
	}
	return x;
}
inline Value Expression::InternalFunc::FunFmod( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 2 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er != NOERR )
		return x;
	double tmpx = x.GetDouble();
	if( fabs(tmpx) < DOUBLE_ZERO )
	{
		er = FP_ERR;
		return x;
	}
	++it;
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value y = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er != NOERR )
		return y;
	y.SetDouble( fmod(tmpx,y.GetDouble()) );
	return y;
}
inline Value Expression::InternalFunc::FunPower( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 2 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er != NOERR )
		return x;
	++it;
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value y = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er != NOERR )
		return y;
	double tmpx = x.GetDouble(), tmpy = y.GetDouble();
	if( (fabs(tmpx) < DOUBLE_ZERO)&&(tmpy < 0.0) )
	{
		er = DIV_ZERO;
		return x;
	}
	y.SetDouble( pow(tmpx,tmpy) );
	return y;
}
inline Value Expression::InternalFunc::FunRound( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	//round(x,prec)
	int s = pl.size();
	ASSERT( (s == 1)||(s == 2) );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_DOUBLE);
	er = (*it)->GetRunErrorCode();
	if( er != NOERR )
		return x;
	double tmpprec = 1.0;
	if( s == 2 )
	{
		++it;
		ASSERT( (*it)->GetCompileErrorCode() == NOERR );
		Value prec;
		prec = (*it)->GetValue(TYPE_DOUBLE);
		er = (*it)->GetRunErrorCode();
		if( er != NOERR )
			return x;
		tmpprec = prec.GetDouble();
		if( fabs(tmpprec) < DOUBLE_ZERO )
		{
			er = FP_ERR;
			return x;
		}
	}
	x.SetDouble( x.GetDouble() / tmpprec );//!!! здесь идёт нехилая потеря точности
	double tmpx = x.GetDouble(), flr = floor(tmpx);
	if( fabs(tmpx - flr) < 0.5 )
		x.SetDouble(flr);
	else
		x.SetDouble( ceil(tmpx) );
	x.SetDouble( x.GetDouble() * tmpprec );
	return x;
}
Value Expression::InternalFunc::FunRandom( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_INT);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		x.SetInt( rand()%x.GetInt() );
	}
	return x;
}
Value Expression::InternalFunc::FunAtoi( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_STRING);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		x.SetInt( atoi(x.GetString().c_str()) );
	}
	return x;
}
Value Expression::InternalFunc::FunAtof( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_STRING);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		x.SetDouble( atof(x.GetString().c_str()) );
	}
	return x;
}
Value Expression::InternalFunc::FunTranspose( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_MATR);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		AlgolMatr *m = x.GetMatr()->GetMatr();
		if( m != NULL )
		{
			AlgolMatr matr( *m );
			if( !matr.Transpose() )
			{
				er = FP_ERR;
				return x;
			}
			x.SetMatr( MatrPtr( matr ) );
		}
		else
		{
			x.SetMatr( MatrPtr( AlgolMatr() ) );
		}
	}
	return x;
}
Value Expression::InternalFunc::FunRows( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_MATR);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		AlgolMatr *m = x.GetMatr()->GetMatr();
		int s = 0;
		if( m != NULL )
			s = m->GetRow();
		x.SetInt( s );
	}
	return x;
}
Value Expression::InternalFunc::FunCols( const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	ASSERT( pl.size() == 1 );
	FuncParamList::iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == NOERR );
	Value x = (*it)->GetValue(TYPE_MATR);
	er = (*it)->GetRunErrorCode();
	if( er == NOERR )
	{
		AlgolMatr *m = x.GetMatr()->GetMatr();
		int s = 0;
		if( m != NULL )
			s = m->GetWidth();
		x.SetInt( s );
	}
	return x;
}

Value Expression::InternalFunc::GetValue( InternalFuncID id, const FuncParamList &pl, errorsT &er, ScriptObject *p )
{
	Value res;
	switch( id )
	{
	case FID_SIN:
		res = Expression::InternalFunc::FunSin( pl, er, p );
		break;
	case FID_COS:
		res = Expression::InternalFunc::FunCos( pl, er, p );
		break;
	case FID_TAN:
		res = Expression::InternalFunc::FunTan( pl, er, p );
		break;
	case FID_SQRT:
		res = Expression::InternalFunc::FunSqrt( pl, er, p );
		break;
	case FID_LOG:
		res = Expression::InternalFunc::FunLog( pl, er, p );
		break;
	case FID_ASIN:
		res = Expression::InternalFunc::FunAsin( pl, er, p );
		break;
	case FID_ACOS:
		res = Expression::InternalFunc::FunAcos( pl, er, p );
		break;
	case FID_EXP:
		res = Expression::InternalFunc::FunExp( pl, er, p );
		break;
	case FID_FLOOR:
		res = Expression::InternalFunc::FunFloor( pl, er, p );
		break;
	case FID_CEIL:
		res = Expression::InternalFunc::FunCeil( pl, er, p );
		break;
	case FID_FABS:
		res = Expression::InternalFunc::FunFabs( pl, er, p );
		break;
	case FID_ABS:
		res = Expression::InternalFunc::FunAbs( pl, er, p );
		break;
	case FID_ATAN:
		res = Expression::InternalFunc::FunAtan( pl, er, p );
		break;
	case FID_FMOD:
		res = Expression::InternalFunc::FunFmod( pl, er, p );
		break;
	case FID_POWER:
		res = Expression::InternalFunc::FunPower( pl, er, p );
		break;
	case FID_ROUND:
		res = Expression::InternalFunc::FunRound( pl, er, p );
		break;
	case FID_RANDOM:
		res = Expression::InternalFunc::FunRandom( pl, er, p );
		break;
	case FID_ATOI:
		res = Expression::InternalFunc::FunAtoi( pl, er, p );
		break;
	case FID_ATOF:
		res = Expression::InternalFunc::FunAtof( pl, er, p );
		break;
	case FID_TRANSPOSE:
		res = Expression::InternalFunc::FunTranspose( pl, er, p );
		break;
	case FID_ROWS:
		res = Expression::InternalFunc::FunRows( pl, er, p );
		break;
	case FID_COLS:
		res = Expression::InternalFunc::FunCols( pl, er, p );
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	return res;
}

bool Expression::InternalFunc::IsValidParamNum( int c )
{
//ф-ция проверяет - может ли соответствовать c числу пар-ров данной ф-ции
	switch(m_ParamNum)
	{
	case FPN_ZERO:
		return c == 0;
		break;
	case FPN_ONE:
		return c == 1;
		break;
	case FPN_TWO:
		return c == 2;
		break;
	case FPN_THREE:
		return c == 3;
		break;
	case FPN_ONE_TWO:
		return (c == 1)||(c == 2);
		break;
	default:
		return false;
	}
	return false;
}

Expression::InternalFuncMap Expression::InitFuncTable()
{
	InternalFuncMap fm;

	fm.insert( InternalFuncMap::value_type( "sin",InternalFunc(FID_SIN,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "cos",InternalFunc(FID_COS,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "tan",InternalFunc(FID_TAN,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "sqrt",InternalFunc(FID_SQRT,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "log",InternalFunc(FID_LOG,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "asin",InternalFunc(FID_ASIN,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "acos",InternalFunc(FID_ACOS,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "exp",InternalFunc(FID_EXP,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "floor",InternalFunc(FID_FLOOR,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "ceil",InternalFunc(FID_CEIL,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "fabs",InternalFunc(FID_FABS,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "abs",InternalFunc(FID_ABS,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "atan",InternalFunc(FID_ATAN,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "fmod",InternalFunc(FID_FMOD,FPN_TWO) ) );
	fm.insert( InternalFuncMap::value_type( "power",InternalFunc(FID_POWER,FPN_TWO) ) );
	fm.insert( InternalFuncMap::value_type( "round",InternalFunc(FID_ROUND,FPN_ONE_TWO) ) );
	fm.insert( InternalFuncMap::value_type( "random",InternalFunc(FID_RANDOM,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "atoi",InternalFunc(FID_ATOI,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "atof",InternalFunc(FID_ATOF,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "transpose",InternalFunc(FID_TRANSPOSE,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "rows",InternalFunc(FID_ROWS,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "cols",InternalFunc(FID_COLS,FPN_ONE) ) );

	return fm;
}

void Expression::Init()
{
	m_Tree = NULL;
	if( !m_pScript )
	{
		m_CompileErrCode = UNKN_ERR;
		return;
	}
	m_CompileErrCode = NOERR;
	CutEOL(m_expr);
	if( !m_expr.empty() )
	{
		string::iterator from = m_expr.begin(), to = m_expr.end();
		Expression::PassSpaces( from, to );
		if( from != to )
			MakeTree();
		else
			m_CompileErrCode = NOEXP;
	}
	else	m_CompileErrCode = NOEXP;
}

void Expression::MakeTree()
{
	string::iterator from = m_expr.begin(), to = m_expr.end();
	while( from != to )
	{
		if( *from == '"' )
		{
			do
			{
				++from;
			}	while( (from != to)&&(*from != '"') );
			//теперь from указывает на парную кавычку
			//или на конец строки
		}
		if( from == to )
		{
			m_CompileErrCode = MISS_QUOTE;
			return;
		}
		++from;
	}
	try
	{
		m_Tree = new OperRelation( m_expr.begin(), m_expr.end(), m_pScript );
	}
	catch( bad_alloc& )
	{
		m_CompileErrCode = NOMEM;
	}
	m_CompileErrCode = m_Tree->GetErrorCode();
	if( m_CompileErrCode == NOERR )
		Optimize();
}

void Expression::Optimize()
{
//оптимизация дерева:
	Operation *op = m_Tree;
	while( (op = op->Optimize()) != NULL )
	{
		delete m_Tree;
		m_Tree = op;
	}
}
//////////////////////////////////////////////////////////////////
Expression::OperRelation::OperRelation( const std::string::iterator &from, const std::string::iterator &to, ScriptObject *p ):Operation(Expression::OT_RELATION)
{
	m_from = from;
	m_to = to;
	m_Left = m_Right = NULL;
	m_OpCode = EQ;
	//////////////////////////////////////////////////////////////////////
	m_CompileErrCode = MakeTree(p);
}

Expression::Operation* Expression::OperRelation::Optimize()
{
//оптимизация дерева:
	ASSERT( (m_Left != NULL)||(m_Right != NULL) );
	ASSERT( m_CompileErrCode == NOERR );
	
	Operation *op = NULL;
	if( (m_Left != NULL)&&(m_Right != NULL) )
	{
		op = m_Left;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Left;
			m_Left = op;
		}
		op = m_Right;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Right;
			m_Right = op;
		}
		return NULL;
	}
	if( m_Left != NULL )
	{
		op = m_Left;
		m_Left = NULL;
	}
	else
	{
		//m_Right != NULL
		op = m_Right;
		m_Right = NULL;
	}
	return op;
}

errorsT Expression::OperRelation::MakeTree( ScriptObject *p )
{
	Expression::PassSpaces( m_from, m_to );
	string::iterator OperBeg = m_from;//начало операнда
	char opers[] = "<>=";
	errorsT er = Expression::FindOperation( opers, m_from, m_to );
	if( er != NOERR )
		return er;
	try
	{
		//первый операнд:
		m_Left = new OperAddSub( OperBeg, m_from, p );
	}
	catch(bad_alloc&)
	{
		return NOMEM;
	}
	if( (m_CompileErrCode = m_Left->GetErrorCode()) != NOERR )
		return m_CompileErrCode;
	if( m_from != m_to )
	{
		//если второй операнд всё-таки есть
		char op = *m_from;
		++m_from;
		switch(op)
		{
		case '>':
			if( *m_from == '=' )
			{
				++m_from;
				m_OpCode = GE;
			}
			else	m_OpCode = GT;
			break;
		case '<':
			if( *m_from == '=' )
			{
				++m_from;
				m_OpCode = LE;
			}
			else
			{
				if( *m_from == '>' )
				{
					++m_from;
					m_OpCode = NE;
				}
				else	m_OpCode = LT;
			}
			break;
		case '=':
			m_OpCode = EQ;
			break;
		}
		Expression::PassSpaces( m_from, m_to );
		if( m_from == m_to )
			return SERROR;
		try
		{
			m_Right = new OperAddSub( m_from, m_to, p );
		}
		catch(bad_alloc&)
		{
			return NOMEM;
		}
		if( (m_CompileErrCode = m_Right->GetErrorCode()) != NOERR )
			return m_CompileErrCode;
	}
	return NOERR;
}

Expression::OperRelation::~OperRelation()
{
	if( m_Left != NULL )
	{
		delete m_Left;
		m_Left = NULL;
	}
	if( m_Right != NULL )
	{
		delete m_Right;
		m_Right = NULL;
	}
}

Value Expression::OperRelation::GetValue( ScriptObject *p )
{
	Value res;
	if( m_CompileErrCode != NOERR )
	{
		m_RunErrCode = CERROR;
		return res;
	}
	if( !m_Left || !m_Right )
	{
		if( m_Left )
		{
			res = m_Left->GetValue(p);
			m_RunErrCode = m_Left->GetErrorCode(false);
			return res;
		}
		if( m_Right )
		{
			res = m_Right->GetValue(p);
			m_RunErrCode = m_Right->GetErrorCode(false);
			return res;
		}
		ASSERT(FALSE);
	}
	//если оба ненулевые, то надо проверить отношение
	Value left;
	ASSERT( m_Left );
	left = m_Left->GetValue(p);
	if( (m_RunErrCode = m_Left->GetErrorCode(false)) != NOERR )
		return res;

	Value right;
	ASSERT( m_Right );
	right = m_Right->GetValue(p);
	if( (m_RunErrCode = m_Right->GetErrorCode(false)) != NOERR )
		return res;

	bool tmp;
	try
	{
		switch(m_OpCode)
		{
		case LE:
			tmp = left <= right;
			break;
		case GE:
			tmp = left >= right;
			break;
		case NE:
			tmp = left != right;
			break;
		case GT:
			tmp = left > right;
			break;
		case LT:
			tmp = left < right;
			break;
		case EQ:
			tmp = left == right;
			break;
		}//switch
	}
	catch( errorsT er )
	{
		m_RunErrCode = er;
	}
	res.SetBool(tmp);
	return res;
}
//////////////////////////////////////////////////////////////////
Expression::OperAddSub::OperAddSub( const std::string::iterator &from, const std::string::iterator &to, ScriptObject *p ):Operation(Expression::OT_ADDSUB)
{
	m_from = from;
	m_to = to;
	m_Left = m_Right = NULL;
	m_OpCode = '+';
	//////////////////////////////////////////////////////////////////////
	m_CompileErrCode = MakeTree(p);
}

Expression::Operation* Expression::OperAddSub::Optimize()
{
//оптимизация дерева:
	ASSERT( (m_Left != NULL)||(m_Right != NULL) );
	ASSERT( m_CompileErrCode == NOERR );
	
	Operation *op = NULL;
	if( (m_Left != NULL)&&(m_Right != NULL) )
	{
		op = m_Left;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Left;
			m_Left = op;
		}
		op = m_Right;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Right;
			m_Right = op;
		}
		return NULL;
	}
	if( m_Left != NULL )
	{
		op = m_Left;
		m_Left = NULL;
	}
	else
	{
		//m_Right != NULL
		op = m_Right;
		m_Right = NULL;
	}
	return op;
}

errorsT Expression::OperAddSub::MakeTree( ScriptObject *p )
{
	Expression::PassSpaces( m_from, m_to );
	string::iterator OperBeg = m_from;//начало операнда
	char opers[] = "+-";
	if( strchr(opers,*m_from) != NULL )	++m_from;//унарный знак
	errorsT er = Expression::FindOperation( opers, m_from, m_to );
	if( er != NOERR )
		return er;
	try
	{
		//первый операнд:
		m_Left = new OperMultDiv( OperBeg, m_from, p );
	}
	catch(bad_alloc&)
	{
		return NOMEM;
	}
	if( (m_CompileErrCode = m_Left->GetErrorCode()) != NOERR )
		return m_CompileErrCode;
	if( m_from != m_to )
	{
		//если второй операнд всё-таки есть
		m_OpCode = *m_from;
		++m_from;
		OperBeg = m_from;
		Expression::PassSpaces( m_from, m_to );
		if( m_from == m_to )
			return SERROR;
		if( strchr("+-*/^",*m_from) )
			return SERROR;
		m_from = OperBeg;
		try
		{
			m_Right = new OperMultDiv( m_from, m_to, p );
		}
		catch(bad_alloc&)
		{
			return NOMEM;
		}
		if( (m_CompileErrCode = m_Right->GetErrorCode()) != NOERR )
			return m_CompileErrCode;
	}
	return NOERR;
}

Expression::OperAddSub::~OperAddSub()
{
	if( m_Left != NULL )
	{
		delete m_Left;
		m_Left = NULL;
	}
	if( m_Right != NULL )
	{
		delete m_Right;
		m_Right = NULL;
	}
}

Value Expression::OperAddSub::GetValue( ScriptObject *p )
{
	Value res;
	if( m_CompileErrCode != NOERR )
	{
		m_RunErrCode = CERROR;
		return res;
	}
	if( !m_Left || !m_Right )
	{
		if( m_Left )
		{
			res = m_Left->GetValue(p);
			m_RunErrCode = m_Left->GetErrorCode(false);
			return res;
		}
		if( m_Right )
		{
			res = m_Right->GetValue(p);
			m_RunErrCode = m_Right->GetErrorCode(false);
			return res;
		}
		ASSERT(FALSE);
	}
	//если оба ненулевые:
	Value left;
	ASSERT( m_Left );
	left = m_Left->GetValue(p);
	if( (m_RunErrCode = m_Left->GetErrorCode(false)) != NOERR )
		return res;

	Value right;
	ASSERT( m_Right );
	right = m_Right->GetValue(p);
	if( (m_RunErrCode = m_Right->GetErrorCode(false)) != NOERR )
		return res;

	try
	{
		if( m_OpCode == '+' )
		{
			//сложение
			res = left + right;
		}
		else
		{
			//вычитание
			res = left - right;
		}
	}
	catch( errorsT er )
	{
		m_RunErrCode = er;
	}
	return res;
}
//////////////////////////////////////////////////////////////////////////
Expression::OperMultDiv::OperMultDiv( const std::string::iterator &from, const std::string::iterator &to, ScriptObject *p ):Operation(Expression::OT_MULTDIV)
{
	m_from = from;
	m_to = to;
	m_Left = m_Right = NULL;
	m_OpCode = '*';
	//////////////////////////////////////////////////////////////////////
	m_CompileErrCode = MakeTree(p);
}

Expression::Operation* Expression::OperMultDiv::Optimize()
{
//оптимизация дерева:
	ASSERT( (m_Left != NULL)||(m_Right != NULL) );
	ASSERT( m_CompileErrCode == NOERR );
	
	Operation *op = NULL;
	if( (m_Left != NULL)&&(m_Right != NULL) )
	{
		op = m_Left;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Left;
			m_Left = op;
		}
		op = m_Right;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Right;
			m_Right = op;
		}
		return NULL;
	}
	if( m_Left != NULL )
	{
		op = m_Left;
		m_Left = NULL;
	}
	else
	{
		//m_Right != NULL
		op = m_Right;
		m_Right = NULL;
	}
	return op;
}

errorsT Expression::OperMultDiv::MakeTree( ScriptObject *p )
{
	Expression::PassSpaces( m_from, m_to );
	string::iterator OperBeg = m_from;//начало операнда
	//ищем сначала операции "+-"
	char opers[] = "+-";
	if( strchr(opers,*m_from) != NULL )	++m_from;//унарный знак
	errorsT er = Expression::FindOperation( opers, m_from, m_to );
	if( er != NOERR )
		return er;
	if( m_from != m_to )
	{
		//если такая операция есть, то
		try
		{
			m_Left = new OperPow( OperBeg, m_to, p );
		}
		catch(bad_alloc&)
		{
			return NOMEM;
		}
		if( (m_CompileErrCode = m_Left->GetErrorCode()) != NOERR )
			return m_CompileErrCode;
		return NOERR;
	}
	//если "+-" нету, то ищем "*/"
	m_from = OperBeg;
	opers[0] = '*';
	opers[1] = '/';
	er = Expression::FindOperation( opers, m_from, m_to );
	if( er != NOERR )
		return er;
	try
	{
		//первый операнд:
		m_Left = new OperPow( OperBeg, m_from, p );
	}
	catch(bad_alloc&)
	{
		return NOMEM;
	}
	if( (m_CompileErrCode = m_Left->GetErrorCode()) != NOERR )
		return m_CompileErrCode;
	if( m_from != m_to )
	{
		//если второй операнд всё-таки есть
		m_OpCode = *m_from;
		++m_from;
		try
		{
			m_Right = new OperPow( m_from, m_to, p );
		}
		catch(bad_alloc&)
		{
			return NOMEM;
		}
		if( (m_CompileErrCode = m_Right->GetErrorCode()) != NOERR )
			return m_CompileErrCode;
	}
	return NOERR;
}

Expression::OperMultDiv::~OperMultDiv()
{
	if( m_Left != NULL )
	{
		delete m_Left;
		m_Left = NULL;
	}
	if( m_Right != NULL )
	{
		delete m_Right;
		m_Right = NULL;
	}
}

Value Expression::OperMultDiv::GetValue( ScriptObject *p )
{
	Value res;
	if( m_CompileErrCode != NOERR )
	{
		m_RunErrCode = CERROR;
		return res;
	}
	if( !m_Left || !m_Right )
	{
		if( m_Left )
		{
			res = m_Left->GetValue(p);
			m_RunErrCode = m_Left->GetErrorCode(false);
			return res;
		}
		if( m_Right )
		{
			res = m_Right->GetValue(p);
			m_RunErrCode = m_Right->GetErrorCode(false);
			return res;
		}
		ASSERT(FALSE);
	}
	//если оба ненулевые:
	Value left;
	ASSERT( m_Left );
	left = m_Left->GetValue(p);
	if( (m_RunErrCode = m_Left->GetErrorCode(false)) != NOERR )
		return res;

	Value right;
	ASSERT( m_Right );
	right = m_Right->GetValue(p);
	if( (m_RunErrCode = m_Right->GetErrorCode(false)) != NOERR )
		return res;

	try
	{
		if( m_OpCode == '*' )
		{
			//умножение
			res = left * right;
		}
		else
		{
			//деление
			res = left/right;
		}
	}
	catch( errorsT er )
	{
		m_RunErrCode = er;
	}
	return res;
}
///////////////////////////////////////////////////////////////////////////////
Expression::OperPow::OperPow( const std::string::iterator &from, const std::string::iterator &to, ScriptObject *p ):Operation(Expression::OT_POW)
{
	m_from = from;
	m_to = to;
	m_Left = m_Right = NULL;
	//////////////////////////////////////////////////////////////////////
	m_CompileErrCode = MakeTree(p);
}

Expression::Operation* Expression::OperPow::Optimize()
{
//оптимизация дерева:
	ASSERT( (m_Left != NULL)||(m_Right != NULL) );
	ASSERT( m_CompileErrCode == NOERR );
	
	Operation *op = NULL;
	if( (m_Left != NULL)&&(m_Right != NULL) )
	{
		op = m_Left;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Left;
			m_Left = op;
		}
		op = m_Right;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Right;
			m_Right = op;
		}
		return NULL;
	}
	if( m_Left != NULL )
	{
		op = m_Left;
		m_Left = NULL;
	}
	else
	{
		//m_Right != NULL
		op = m_Right;
		m_Right = NULL;
	}
	return op;
}

errorsT Expression::OperPow::MakeTree( ScriptObject *p )
{
	Expression::PassSpaces( m_from, m_to );
	string::iterator OperBeg = m_from;//начало операнда
	//ищем сначала операции "+-*/"
	if( strchr("+-",*m_from) != NULL )	++m_from;//унарный знак
	char opers[] = "+-*/";
	errorsT er = Expression::FindOperation( opers, m_from, m_to );
	if( er != NOERR )
		return er;
	if( m_from != m_to )
	{
		//если такая операция есть, то
		try
		{
			//первый операнд:
			m_Left = new OperValue( OperBeg, m_to, p );
		}
		catch(bad_alloc&)
		{
			return NOMEM;
		}
		if( (m_CompileErrCode = m_Left->GetErrorCode()) != NOERR )
			return m_CompileErrCode;
		return NOERR;
	}
	//если "+-*/" нету, то ищем "^"
	m_from = OperBeg;
	while( (*m_from != '^')&&(m_from != m_to) )
	{	
		if( *m_from == '(' )
		{
			if( !Expression::FindParen( m_from, m_to ) )
			{
				return PARENS;
			}
		}
		else
		{
			if( *m_from == '"' )
			{
				do
				{
					++m_from;
				}	while( (m_from != m_to)&&(*m_from != '"') );
				ASSERT( m_from != m_to );//парность кавычек проверена выше
			}
		}
		++m_from;
	}
	try
	{
		//первый операнд:
		m_Left = new OperValue( OperBeg, m_from, p );
	}
	catch(bad_alloc&)
	{
		return NOMEM;
	}
	if( (m_CompileErrCode = m_Left->GetErrorCode()) != NOERR )
		return m_CompileErrCode;
	if( m_from != m_to )
	{
		//если есть "^", то их и делаем
		++m_from;
		try
		{
			m_Right = new OperValue( m_from, m_to, p );
		}
		catch(bad_alloc&)
		{
			return NOMEM;
		}
		if( (m_CompileErrCode = m_Right->GetErrorCode()) != NOERR )
			return m_CompileErrCode;
	}
	return NOERR;
}

Expression::OperPow::~OperPow()
{
	if( m_Left != NULL )
	{
		delete m_Left;
		m_Left = NULL;
	}
	if( m_Right != NULL )
	{
		delete m_Right;
		m_Right = NULL;
	}
}

Value Expression::OperPow::GetValue( ScriptObject *p )
{
	Value left;
	if( m_CompileErrCode != NOERR )
	{
		m_RunErrCode = CERROR;
		return left;
	}
	if( m_Left )
	{
		left = m_Left->GetValue(p);
		if( (m_RunErrCode = m_Left->GetErrorCode(false)) != NOERR )
			return left;
	}
	if( m_Right )
	{
		Value right = m_Right->GetValue(p);
		if( (m_RunErrCode = m_Right->GetErrorCode(false)) != NOERR )
			return left;
		if( !right.ConvertTo(TYPE_INT) )
		{
			m_RunErrCode = CONVERT_ERR;
			return left;
		}
		m_RunErrCode = left.Power( right.GetInt() );
	}
	return left;
}
/////////////////////////////////////////////////////////////////////
Expression::OperValue::OperValue( const std::string::iterator &from, const std::string::iterator &to, ScriptObject *p ):Operation(Expression::OT_VALUE)
{
	m_Tree = NULL;
	m_bNeg = false;
	m_pValue = NULL;
	m_from = from;
	m_to = to;
	//////////////////////////////////////////////////////////////////////
	m_CompileErrCode = MakeTree(p);
}

Expression::Operation* Expression::OperValue::Optimize()
{
//оптимизация дерева:
	ASSERT( m_CompileErrCode == NOERR );
	
	if( m_Tree == NULL )
		return NULL;
	if( m_bNeg )
		return NULL;
	Operation *op = m_Tree;
	while( (op = op->Optimize()) != NULL )
	{
		delete m_Tree;
		m_Tree = op;
	}
	op = m_Tree;
	m_Tree = NULL;
	return op;
}

errorsT Expression::OperValue::MakeTree( ScriptObject *p )
{
	Expression::PassSpaces( m_from, m_to );
	if( strchr("+-",*m_from) != NULL )
	{
		if( *m_from == '-' )
			m_bNeg = true;
		++m_from;//унарный знак
	}
	Expression::PassSpaces( m_from, m_to );
	string::iterator OperBeg = m_from;//начало операнда
	string::iterator OperEnd = m_to;//конец операнда
	//отбросим наружные парные скобки, если такие есть, т.е. напр: (((1+2)))
	while( *m_from == '(' )
	{
		OperBeg = m_from;//OperBeg указывает на первую скобку
		if( !Expression::FindParen( m_from, m_to ) )
		{
			return PARENS;
		}
		OperEnd = m_from;//OperEnd - на парную ей
		++m_from;
		Expression::PassSpaces( m_from, m_to );
		if( m_from != m_to )
		{
			//если за скобкой, парной предыдущей, что-то есть,
			//то значит эта пара скобок не самая наружная, напр: ((1-1)*3)
			//и её нельзя удалять
			m_from = OperBeg;
			OperEnd = m_to;
			break;
		}
		m_to = OperEnd;
		++OperBeg;
		m_from = OperBeg;
		Expression::PassSpaces( m_from, m_to );
	}
	m_from = OperBeg;
	m_to = OperEnd;

	bool bExpr = false;//флаг о том, что в [m_from;m_to) находится выражение
	for( ; m_from != m_to; ++m_from )
	{
		if( *m_from == '"' )
		{
			do
			{
				++m_from;
			}	while( (m_from != m_to)&&(*m_from != '"') );
			ASSERT( m_from != m_to );
		}
		else
		{
			if( strchr("+-*/()^,",*m_from) != NULL )
			{
				bExpr = true;
				break;
			}
		}
	}
	m_from = OperBeg;
	
	if( bExpr )
	{
		//значит там выражение.
		//проверяем: можно ли разобрать его на операнды?
		//ищем операции "+-*/"
		char opers[] = "+-*/^";
		errorsT er = Expression::FindOperation( opers, m_from, m_to );
		ASSERT(er == NOERR);//такого не должно быть
		if( m_from == m_to )
		{
			//значит его нельзя разобрать на операнды
			m_from = OperBeg;
			//проверим: не ф-ция ли это?
			Expression::PassSpaces( m_from, m_to );
			OperBeg = m_from;//указатель на первый символ имени ф-ции
			if( !isalpha(*m_from) && (*m_from != '_') )
			{
				//значит там недопустимое имя ф-ции
				return SERROR;
			}
			//ищем конец имени
			++m_from;
			while( isdigit(*m_from)||isalpha(*m_from)||(*m_from == '_') )
				++m_from;
			string FuncName( OperBeg, m_from );//имя ф-ции
			Expression::PassSpaces( m_from, m_to );
			if( *m_from != '(' )
			{
				return SERROR;
			}
			OperBeg = m_from + 1;//указатель на начало строки с пар-ми ф-ции
			//отбросим скобки:
			if( !Expression::FindParen( m_from, m_to ) )
			{
				//такого не должно быть, т.к. парность скобок проверена выше
				return PARENS;
			}
			string FuncParams( OperBeg, m_from );//пар-ры ф-ции без скобок
			++m_from;
			Expression::PassSpaces( m_from, m_to );
			if( m_from != m_to )
			{
				//если за скобкой, парной предыдущей, что-то есть,
				//то это ошибка:
				return SERROR;
			}
			//иначе - это вызов ф-ции
			try
			{
				m_Tree = new OperCallFunc( FuncName, FuncParams, p );
			}
			catch( bad_alloc& )
			{
				return NOMEM;
			}
			return m_Tree->GetErrorCode();
		}
		try
		{
			m_Tree = new OperAddSub( OperBeg, m_to, p );
		}
		catch( bad_alloc& )
		{
			return NOMEM;
		}
		return m_Tree->GetErrorCode();
	}
	Expression::PassSpaces( m_from, m_to );
	OperBeg = m_from;
	while( (m_from != m_to)&&(*m_from != ' ')&&(*m_from != '\t') )
	{
		if( *m_from == '"' )
		{
			do
			{
				++m_from;
			}	while( (m_from != m_to)&&(*m_from != '"') );
			ASSERT( m_from != m_to );
			//теперь from указывает на парную кавычку
		}
		++m_from;
	}
	OperEnd = m_from;
	Expression::PassSpaces( m_from, m_to );
	if( m_from != m_to )
	{
		return SERROR;
	}
	m_from = OperBeg;
	string tmp = string( m_from, OperEnd );
	if( tmp.empty() )
		return SERROR;

	if( isalpha(*m_from) || (*m_from == '_') )
	{
		//возможно переменная
		m_VarName = tmp;
		MakeLower(m_VarName);
		TypeID t = p->IsVariable(m_VarName);
		if( t == TYPE_UNKNOWN )
		{
			t = p->IsConstant(m_VarName);
			if( t == TYPE_UNKNOWN )
				return WRONG_SIMBOL;
			else
			{
				//если константа, то её значение можно получить сразу.
				try
				{
					m_pValue = new Value();
				}
				catch( bad_alloc& )
				{
					m_pValue = NULL;
					return NOMEM;
				}
				p->m_ConstTable.GetVarValue( m_VarName, t, *m_pValue );
				if( m_bNeg && !m_pValue->Negate() )
					return TYPE_OP_ERR;
				m_VarName.erase( m_VarName.begin(), m_VarName.end() );
			}
		}
		return NOERR;
	}
	//здесь уже точно знаем, что это не переменная.
	try
	{
		m_pValue = new Value();
	}
	catch( bad_alloc& )
	{
		m_pValue = NULL;
		return NOMEM;
	}
	//проверяем правильность написания констант:
	int s = tmp.size();
	if( tmp[0] == '"' )
	{
		ASSERT(tmp[s-1] == '"');
		OperBeg = tmp.begin();
		++OperBeg;
		OperEnd = tmp.end();
		--OperEnd;
		m_pValue->SetString( string(OperBeg, OperEnd) );
		return NOERR;
	}
	bool bExp = false, bInteger = true;
	for( int i = 0; i < s; i++ )
	{
		if( !isdigit(tmp[i]) && (tmp[i] != '.') )
		{
			//если это не цифра или точка, то проверяем:
			//не разбирается ли сейчас экспоненциальная часть числа?
			if( bExp )
			{
				//если буквы 'E' или 'e' уже были, то это может быть
				//только знак
				if( (tmp[i]!='+')&&(tmp[i]!='-') )
					return SERROR;
			}
			else
			{
				//если не было, то проверяем не нужная ли это буква ?
				if( (tmp[i] != 'e')&&(tmp[i] != 'E') )
					return SERROR;
				bExp = true;
				bInteger = false;
			}
		}
		else
		{
			if( tmp[i] == '.' )
				bInteger = false;
		}
	}//for
	if( bInteger )
		m_pValue->SetInt( atoi(tmp.c_str()) );
	else
		m_pValue->SetDouble( atof( tmp.c_str() ) );
	if( m_bNeg && !m_pValue->Negate() )
	{
		return TYPE_OP_ERR;
	}
	return NOERR;
}

Expression::OperValue::~OperValue()
{
	if( m_Tree != NULL )
	{
		delete m_Tree;
		m_Tree = NULL;
	}
	delete m_pValue;
	m_pValue = NULL;
}

Value Expression::OperValue::GetValue( ScriptObject *p )
{
	Value res;
	if( m_CompileErrCode != NOERR )
	{
		m_RunErrCode = CERROR;
		return res;
	}
	if( m_Tree )
	{
		//если это не переменная или константа, то выражение или ф-ция
		res = m_Tree->GetValue(p);
		if( (m_RunErrCode = m_Tree->GetErrorCode(false)) != NOERR )
			return res;
		if( m_bNeg && !res.Negate() )
		{
			m_RunErrCode = TYPE_OP_ERR;
		}
		return res;
	}
	//иначе:
	if( !m_VarName.empty() )
	{
		//значит переменная
		res = p->find_var(m_VarName);
		if( res.Type() == TYPE_UNKNOWN )
		{
			m_RunErrCode = WRONG_SIMBOL;
		}
		else
		{
			if( m_bNeg && !res.Negate() )
				m_RunErrCode = TYPE_OP_ERR;
		}
		return res;
	}
	//иначе константа
	ASSERT(m_pValue);
	return *m_pValue;
}

bool Expression::OperValue::IsConstant() const
{
	if( m_Tree != NULL )
		return false;
	if( !m_VarName.empty() )
		return false;
	return true;
}

bool Expression::OperValue::IsVarName() const
{
	if( m_Tree != NULL )
		return false;
	if( !m_VarName.empty() )
	{
		if( m_bNeg )
			return false;
		return true;
	}
	return false;
}
/////////////////////////////////////////////////////////////////////
Expression::OperCallFunc::OperCallFunc( const std::string &name, const std::string &params, ScriptObject *p ):Operation(Expression::OT_FUNC)
{
	m_FuncName = name;
	MakeLower(m_FuncName);
	m_Params = params;
	m_ft = FT_INTERNAL;
	//////////////////////////////////////////////////////////////////////
	m_CompileErrCode = MakeTree(p);
}

Expression::Operation* Expression::OperCallFunc::Optimize()
{
//оптимизация дерева:
	ASSERT( m_CompileErrCode == NOERR );
	return NULL;
}

errorsT Expression::OperCallFunc::MakeTree( ScriptObject *p )
{
	//узнаем пренадлежность ф-ции
	//проверяем, есть ли такая ф-ция среди встроенных:
	Expression::InternalFuncMap::iterator it = Expression::m_FuncTable.find(m_FuncName);
	if( it == Expression::m_FuncTable.end() )
	{
		//такой ф-ции нет.
		//проверим среди зарезервированных в скриптах
		m_ReservedIt = p->m_FuncTable.find( m_FuncName );
		if( m_ReservedIt == p->m_FuncTable.end() )
		{
			m_UserIt = p->m_UserFuncTable.find( m_FuncName );
			if( m_UserIt == p->m_UserFuncTable.end() )
			{
				return WRONG_SIMBOL;
			}
			//пользовательская ф-ция
			m_ft = FT_USER;
		}
		else
		{
			m_ft = FT_RESERVED;
		}
	}
	else
	{
		m_FuncID = (*it).second.m_ID;
		m_ft = FT_INTERNAL;
	}
	////////////////////////////////////////////////////
	string::iterator from = m_Params.begin(), to = m_Params.end();
	Expression::PassSpaces( from, to );
	if( from != to )
	{
		//с параметрами
		for(;;)
		{
			//читаем пар-ры
			char opers[] = ",";
			string::iterator OperBeg = from;
			errorsT er = Expression::FindOperation( opers, from, to );
			ASSERT(er == NOERR);//такого не должно быть
			Expression *pPar;//указатель на пар-р ф-ции
			try
			{
				pPar = new Expression( string(OperBeg,from), p );
			}
			catch( bad_alloc& )
			{
				return NOMEM;
			}
			er = pPar->GetCompileErrorCode();
			if( er != NOERR )	
			{
				delete pPar;
				return er;
			}
			m_ParamsList.push_back(pPar);
			if( from == to )	break;
			++from;//указатель на символ, стоящий вслед за запятой
			Expression::PassSpaces( from, to );
		}//for(;;)
	}
	int s = m_ParamsList.size();
	switch( m_ft )
	{
	case FT_INTERNAL:
		if( !(*it).second.IsValidParamNum( s ) )
		{
			p->StackErr( s, false );
			return WRONG_FUNC_PARAM_NUM;
		}
		break;
	case FT_RESERVED:
		{
			ValList lst;
			FuncParamList::iterator itFp = m_ParamsList.begin(), fin = m_ParamsList.end();
			while( itFp != fin )
			{
				string *pStr = NULL;
				if( (*itFp)->IsVarName() )
				{
					try
					{
						pStr = new string( (*itFp)->GetExpr() );
					}
					catch( bad_alloc& )
					{
						ScriptObject::DestructValList(lst);
						pStr = NULL;
						return NOMEM;
					}
				}
				Value *pVal = NULL;
				lst.push_back( make_pair(pVal,pStr) );
				++itFp;
			}//while
			if( !p->TestFuncParams( m_ReservedIt, lst ) )
			{
				ScriptObject::DestructValList(lst);
				return WRONG_FUNC_PARAM_NUM;
			}
			ScriptObject::DestructValList(lst);
		}
		break;
	case FT_USER:
		if( (*m_UserIt).second.m_Params.size() != s )
			return WRONG_FUNC_PARAM_NUM;
		break;
	default:
		ASSERT(FALSE);
	}//switch
	return NOERR;
}

Expression::OperCallFunc::~OperCallFunc()
{
	while( !m_ParamsList.empty() )
	{
		delete (*m_ParamsList.begin());
		m_ParamsList.erase( m_ParamsList.begin() );
	}
}

Value Expression::OperCallFunc::GetValue( ScriptObject *p )
{
	Value res;
	if( m_CompileErrCode != NOERR )
	{
		m_RunErrCode = CERROR;
		return res;
	}
	switch( m_ft )
	{
	case FT_INTERNAL:
		res = Expression::InternalFunc::GetValue( m_FuncID, m_ParamsList, m_RunErrCode, p );
		break;
	case FT_USER:
	case FT_RESERVED:
		{
			ValList lst;
			FuncParamList::iterator it = m_ParamsList.begin(), fin = m_ParamsList.end();
			errorsT er;
			while( it != fin )
			{
				string *pStr = NULL;
				if( (*it)->IsVarName() )
				{
					try
					{
						pStr = new string( (*it)->GetExpr() );
					}
					catch( bad_alloc& )
					{
						ScriptObject::DestructValList(lst);
						m_RunErrCode = NOMEM;
						return res;
					}
				}
				Value *pVal = NULL;
				try
				{
					pVal = new Value();
				}
				catch( bad_alloc& )
				{
					ScriptObject::DestructValList(lst);
					m_RunErrCode = NOMEM;
					return res;
				}
				(*pVal) = (*it)->GetValue();
				er = (*it)->GetRunErrorCode();
				if( er != NOERR )
				{
					ScriptObject::DestructValList(lst);
					m_RunErrCode = er;
					return res;
				}
				lst.push_back( make_pair(pVal,pStr) );
				++it;
			}
			if( m_ft == FT_USER )
			{
				if( (er = p->CallUserFunc( m_UserIt, lst, res )) != NOERR )
				{
					ScriptObject::DestructValList(lst);
					m_RunErrCode = er;
					return res;
				}
			}
			else
			{
				if( (er = p->CallReservedFunc( m_ReservedIt, lst, res )) != NOERR )
				{
					ScriptObject::DestructValList(lst);
					m_RunErrCode = er;
					return res;
				}
			}
			ScriptObject::DestructValList(lst);
		}
		break;
	default:
		ASSERT(FALSE);
	}//switch
	return res;
}
