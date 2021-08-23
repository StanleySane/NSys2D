// ShemeExpr.cpp: implementation of the CShemeExpr class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "ShemeExpr.h"

#include "ShemeVarsTable.h"

#include<cmath>
#include<limits>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

CShemeExpr::InternalFuncMap CShemeExpr::m_FuncTable = CShemeExpr::InitFuncTable();

void MakeLower( std::string &str );
std::string FormatString( const char *format, ... );
//////////////////////////////////////////////////////////////////
/*
bool operator < ( const CShemeExpr &obj1, const CShemeExpr &obj2 )
{
	//return obj1.GetExpr() < obj2.GetExpr();
	return true;
}
bool operator == ( const CShemeExpr &obj1, const CShemeExpr &obj2 )
{
	//return obj1.GetExpr() == obj2.GetExpr();
	return true;
}
*/
//////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShemeExpr::CShemeExpr( CShemeVarsTable *p ):m_pVarsTable(p)
{
	Init();
}

CShemeExpr::CShemeExpr( const string &str, CShemeVarsTable *p ):m_expr(str), m_pVarsTable(p)
{
	Init();
}

CShemeExpr::CShemeExpr( const CString &str, CShemeVarsTable *p ):m_expr(static_cast<LPCTSTR>(str)), m_pVarsTable(p)
{
	Init();
}

CShemeExpr::CShemeExpr( double val, CShemeVarsTable *p ):m_pVarsTable(p)
{
	Init( val );
}

/*
CShemeExpr::CShemeExpr( const CShemeExpr &ob )
{
	m_expr = ob.m_expr;
	Init();
}

CShemeExpr& CShemeExpr::operator = ( const CShemeExpr &ob )
{
	if( this == &ob )	return *this;
	Destruct();
	m_expr = ob.m_expr;
	Init();
	return *this;
}
*/

CShemeExpr::~CShemeExpr()
{
	Destruct();
}

void CShemeExpr::Serialize( CArchive &ar )
{
	if (ar.IsStoring())
	{	// storing code
		CString str(m_expr.c_str());
		ar << str;
	}
	else
	{
		CString str;
		ar >> str;
		Reset(str);
	}
}

//////////////////////////////////////////////////////////////////////
//		Members
//////////////////////////////////////////////////////////////////////
std::string CShemeExpr::GetFullErrorMsg( ShemeExprErr err ) const
{
	string mes = GetErrorMessage( err );
	mes += ": " + GetErrorCause();
	return mes;
}

std::string CShemeExpr::GetErrorMessage( const ShemeExprErr &er )
{
	string mes;
	switch( er )
	{
	case SEE_NOERR:
		mes = "Нет ошибки";
		break;
	case SEE_PARENS:
		mes = "Пропущена парная скобка";
		break;
	case SEE_NEG_SQRT:
		mes = "Попытка вычислить квадратный корень из отрицательного числа";
		break;
	case SEE_FP_ERR:
		mes = "Математическая ошибка";
		break;
	case SEE_DIV_ZERO:
		mes = "Деление на ноль";
		break;
	case SEE_UNKN_ERR:
		mes = "Неизвестная ошибка";
		break;
	case SEE_NOEXP:
		mes = "Нет выражения";
		break;
	case SEE_NOMEM:
		mes = "Ошибка выделения памяти";
		break;
	case SEE_SERROR:
		mes = "Синтаксическая ошибка";
		break;
	case SEE_CERROR:
		mes = "Ошибка компиляции";
		break;
	case SEE_WRONG_SIMBOL:
		mes = "Неизвестный символ";
		break;
	case SEE_WRONG_FUNC_PARAM_NUM:
		mes = "Неверное число параметров функции";
		break;
	case SEE_CYCLE:
		mes = "При вычислении выражения произошло зацикливание";
		break;
	default:
		ASSERT(FALSE);
	}
	return mes;
}

bool CShemeExpr::IsInternalFunc( const std::string &name )
{
//ф-ция возвращает true, если name является именем встроенной ф-ции
//иначе - false
	if( m_FuncTable.find(name) == m_FuncTable.end() )
		return false;
	return true;
}

ShemeExprErr CShemeExpr::FindOperation( const char *opers, std::string::iterator &from, const std::string::iterator &to )
{
//ф-ция ищет в интервале [from;to) одну из операций opers
//from после выполнения указывает на найденный знак или на конец строки (т.е. from==to).
//ф-ция возвращает SEE_NOERR если интервал сбалансирован по скобкам и кавычкам,
//иначе SEE_PARENS (и from==to)
	while( (strchr(opers,*from) == NULL)&&(from != to) )
	{	
		if( *from == '(' )
		{
			if( !CShemeExpr::FindParen( from, to ) )
			{
				return SEE_PARENS;
			}
		}
		++from;
	}
	return SEE_NOERR;
}

void CShemeExpr::PassSpaces( std::string::iterator &from, const std::string::iterator &to )
{
	if( from >= to )
		return;
	while( (from != to)&&( (*from == ' ')||(*from == '\t') ) )
		++from;
}
bool CShemeExpr::FindParen( std::string::iterator &from, const std::string::iterator &to )
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

void CShemeExpr::InitBy( const CShemeExpr &expr )
{
	Reset( expr.m_expr, expr.m_pVarsTable );
}

ShemeExprErr CShemeExpr::Reset( const std::string &str, CShemeVarsTable *p/*=NULL*/ )
{
	Destruct();
	if( p != NULL )
		m_pVarsTable = p;
	m_expr = str;
	Init();
	return GetCompileErrorCode();
}

ShemeExprErr CShemeExpr::Reset( const CString &str, CShemeVarsTable *p/*=NULL*/ )
{
	Destruct();
	if( p != NULL )
		m_pVarsTable = p;
	m_expr = static_cast<LPCTSTR>(str);
	Init();
	return GetCompileErrorCode();
}

double CShemeExpr::GetValue()
{
	if( m_CompileErrCode != SEE_NOERR )
	{
		m_RunErrCode = SEE_CERROR;
		return 0.0;
	}
	m_RunErrCode = SEE_NOERR;
	m_Tree->ClearErrCode();
	double res = m_Tree->GetValue( m_pVarsTable );
	if( (m_RunErrCode = m_Tree->GetErrorCode(false)) != SEE_NOERR )
	{
		m_strErrorCause = m_Tree->GetErrorCause();
		return 0.0;
	}
	return res;
}

void CShemeExpr::Destruct()
{
	if( m_Tree != NULL )
	{
		delete m_Tree;
		m_Tree = NULL;
	}
	m_strErrorCause = "";
	m_CompileErrCode = m_RunErrCode = SEE_NOERR;
	m_expr = "";
}

bool CShemeExpr::IsConstant() const
{
	if( m_Tree->GetOperType() != OT_VALUE )
		return false;
	OperValue *op = static_cast<OperValue*>(m_Tree);
	return op->IsConstant();
}

bool CShemeExpr::IsVarName() const
{
	if( m_Tree->GetOperType() != OT_VALUE )
		return false;
	OperValue *op = static_cast<OperValue*>(m_Tree);
	return op->IsVarName();
}
/////////////////////////////////////////////////////////////////////////////////
//		внутренние ф-ции
/////////////////////////////////////////////////////////////////////////////////
inline double CShemeExpr::InternalFunc::FunSign( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		if( x > 0.0 )
			return 1.0;
		if( x < 0.0 )
			return -1.0;
		return 0.0;
	}
	return 0.0;
}
inline double CShemeExpr::InternalFunc::FunSin( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		return sin(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunCos( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		return cos(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunCosh( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		return cosh(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunSinh( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		return sinh(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunTan( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		return tan(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunSqrt( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		if( x < DOUBLE_ZERO )
		{
			er = SEE_NEG_SQRT;
			strErrorCause = string("sqrt(")+(*it)->GetExpr()+string(")");
			return 0.0;
		}
		return sqrt(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunLog( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		return log(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunLog10( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		return log10(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunAsin( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		if( (x < -1.0) || (x > 1.0) )
		{
			er = SEE_FP_ERR;
			strErrorCause = string("asin(")+(*it)->GetExpr()+string(")");
			return x;
		}
		return asin(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunAcos( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		if( (x < -1.0) || (x > 1.0) )
		{
			er = SEE_FP_ERR;
			strErrorCause = string("acos(")+(*it)->GetExpr()+string(")");
			return x;
		}
		return acos(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunExp( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		return exp(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunFloor( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		return floor(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunCeil( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		return ceil(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunFabs( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		return fabs(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunAbs( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	return CShemeExpr::InternalFunc::FunFabs( pl, er, strErrorCause );
}
inline double CShemeExpr::InternalFunc::FunAtan( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		return atan(x);
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunFmod( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 2 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er != SEE_NOERR )
		return x;
	if( fabs(x) < DOUBLE_ZERO )
	{
		er = SEE_FP_ERR;
		strErrorCause = string("fmod(")+(*it)->GetExpr();
		++it;
		strErrorCause += string(",")+(*it)->GetExpr()+string(")");
		return x;
	}
	++it;
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double y = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er != SEE_NOERR )
		return y;
	return fmod(x,y);
}
inline double CShemeExpr::InternalFunc::FunPower( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 2 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er != SEE_NOERR )
		return x;
	++it;
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double y = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er != SEE_NOERR )
		return y;
	if( (fabs(x) < DOUBLE_ZERO)&&(y < 0.0) )
	{
		er = SEE_DIV_ZERO;
		--it;
		strErrorCause = string("power(")+(*it)->GetExpr()+string(",");
		++it;
		strErrorCause = (*it)->GetExpr()+string(")");
		return x;
	}
	return pow(x,y);
}
inline double CShemeExpr::InternalFunc::FunRound( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	//round(x,prec)
	int s = pl.size();
	ASSERT( (s == 1)||(s == 2) );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er != SEE_NOERR )
		return x;
	double tmpprec = 1.0;
	if( s == 2 )
	{
		++it;
		ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
		double prec;
		prec = (*it)->GetValue();
		er = (*it)->GetRunErrorCode();
		if( er != SEE_NOERR )
			return x;
		tmpprec = prec;
		if( fabs(tmpprec) < DOUBLE_ZERO )
		{
			er = SEE_FP_ERR;
			--it;
			strErrorCause = string("round(")+(*it)->GetExpr()+string(",");
			++it;
			strErrorCause = (*it)->GetExpr()+string(")");
			return x;
		}
	}
	x /= tmpprec;//!!! здесь идёт нехилая потеря точности
	double flr = floor(x);
	if( fabs(x - flr) < 0.5 )
		x = flr;
	else
		x = ceil(x);
	return (x*tmpprec);
}
inline double CShemeExpr::InternalFunc::FunRandom( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		return static_cast<double>(rand())*x/RAND_MAX;
//		return fmod( static_cast<double>(rand()), x );
	}
	return x;
}
inline double CShemeExpr::InternalFunc::FunIf( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 3 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double res = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er != SEE_NOERR )
		return 0.0;
	if( fabs(res) > DOUBLE_ZERO )
	{
		++it;
	}
	else
	{
		++it;
		++it;
	}
	res = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er != SEE_NOERR )
		return 0.0;
	return res;
}
inline double CShemeExpr::InternalFunc::FunHev( const ShemeFuncParamList &pl, ShemeExprErr &er, std::string &strErrorCause )
{
	ASSERT( pl.size() == 1 );
	ShemeFuncParamList::const_iterator it = pl.begin();
	ASSERT( (*it)->GetCompileErrorCode() == SEE_NOERR );
	double x = (*it)->GetValue();
	er = (*it)->GetRunErrorCode();
	if( er == SEE_NOERR )
	{
		return (x>=0.0)?(1.0):(0.0);
	}
	return x;
}

double CShemeExpr::InternalFunc::GetValue( InternalFuncID id, const ShemeFuncParamList &pl, ShemeExprErr &er, CShemeVarsTable *p, std::string &strErrorCause )
{
	double res;
	switch( id )
	{
	case FID_SIGN:
		res = CShemeExpr::InternalFunc::FunSign( pl, er, strErrorCause );
		break;
	case FID_SIN:
		res = CShemeExpr::InternalFunc::FunSin( pl, er, strErrorCause );
		break;
	case FID_COS:
		res = CShemeExpr::InternalFunc::FunCos( pl, er, strErrorCause );
		break;
	case FID_SINH:
		res = CShemeExpr::InternalFunc::FunSinh( pl, er, strErrorCause );
		break;
	case FID_COSH:
		res = CShemeExpr::InternalFunc::FunCosh( pl, er, strErrorCause );
		break;
	case FID_TAN:
		res = CShemeExpr::InternalFunc::FunTan( pl, er, strErrorCause );
		break;
	case FID_SQRT:
		res = CShemeExpr::InternalFunc::FunSqrt( pl, er, strErrorCause );
		break;
	case FID_LOG:
		res = CShemeExpr::InternalFunc::FunLog( pl, er, strErrorCause );
		break;
	case FID_LOG10:
		res = CShemeExpr::InternalFunc::FunLog10( pl, er, strErrorCause );
		break;
	case FID_ASIN:
		res = CShemeExpr::InternalFunc::FunAsin( pl, er, strErrorCause );
		break;
	case FID_ACOS:
		res = CShemeExpr::InternalFunc::FunAcos( pl, er, strErrorCause );
		break;
	case FID_EXP:
		res = CShemeExpr::InternalFunc::FunExp( pl, er, strErrorCause );
		break;
	case FID_FLOOR:
		res = CShemeExpr::InternalFunc::FunFloor( pl, er, strErrorCause );
		break;
	case FID_CEIL:
		res = CShemeExpr::InternalFunc::FunCeil( pl, er, strErrorCause );
		break;
	case FID_FABS:
		res = CShemeExpr::InternalFunc::FunFabs( pl, er, strErrorCause );
		break;
	case FID_ABS:
		res = CShemeExpr::InternalFunc::FunAbs( pl, er, strErrorCause );
		break;
	case FID_ATAN:
		res = CShemeExpr::InternalFunc::FunAtan( pl, er, strErrorCause );
		break;
	case FID_FMOD:
		res = CShemeExpr::InternalFunc::FunFmod( pl, er, strErrorCause );
		break;
	case FID_POWER:
		res = CShemeExpr::InternalFunc::FunPower( pl, er, strErrorCause );
		break;
	case FID_ROUND:
		res = CShemeExpr::InternalFunc::FunRound( pl, er, strErrorCause );
		break;
	case FID_RANDOM:
		res = CShemeExpr::InternalFunc::FunRandom( pl, er, strErrorCause );
		break;
	case FID_IF:
		res = CShemeExpr::InternalFunc::FunIf( pl, er, strErrorCause );
		break;
	case FID_HEV:
		res = CShemeExpr::InternalFunc::FunHev( pl, er, strErrorCause );
		break;
	default:
		ASSERT(FALSE);
		break;
	}
	return res;
}

bool CShemeExpr::InternalFunc::IsValidParamNum( int c )
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

CShemeExpr::InternalFuncMap CShemeExpr::InitFuncTable()
{
	InternalFuncMap fm;

	fm.insert( InternalFuncMap::value_type( "sign",InternalFunc(FID_SIGN,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "sin",InternalFunc(FID_SIN,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "cos",InternalFunc(FID_COS,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "sinh",InternalFunc(FID_SINH,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "cosh",InternalFunc(FID_COSH,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "tan",InternalFunc(FID_TAN,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "sqrt",InternalFunc(FID_SQRT,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "log",InternalFunc(FID_LOG,FPN_ONE) ) );
	fm.insert( InternalFuncMap::value_type( "log10",InternalFunc(FID_LOG10,FPN_ONE) ) );
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
	fm.insert( InternalFuncMap::value_type( "if",InternalFunc(FID_IF,FPN_THREE) ) );
	fm.insert( InternalFuncMap::value_type( "hev",InternalFunc(FID_HEV,FPN_ONE) ) );

	return fm;
}

void CShemeExpr::Init()
{
	m_Tree = NULL;
	/*
	if( m_pVarsTable == NULL )
	{
		m_CompileErrCode = SEE_UNKN_ERR;
		m_strErrorCause = "неинициализирована таблица переменных";
		return;
	}
	*/
	m_CompileErrCode = SEE_NOERR;
//	CutEOL(m_expr);
	if( !m_expr.empty() )
	{
		string::iterator from = m_expr.begin(), to = m_expr.end();
		CShemeExpr::PassSpaces( from, to );
		if( from != to )
			MakeTree();
		else
			m_CompileErrCode = SEE_NOEXP;
	}
	else	m_CompileErrCode = SEE_NOEXP;
}

void CShemeExpr::Init( double val )
{
	m_Tree = NULL;
	/*
	if( m_pVarsTable == NULL )
	{
		m_CompileErrCode = SEE_UNKN_ERR;
		m_strErrorCause = "неинициализирована таблица переменных";
		return;
	}
	*/
	m_CompileErrCode = SetValue(val);
}

ShemeExprErr CShemeExpr::SetValue( double val )
{
	if( (m_Tree != NULL)&&(m_Tree->GetOperType() == OT_VALUE) )
	{
		OperValue *op = static_cast<OperValue*>(m_Tree);
		if( op->IsConstant() )
		{
			m_CompileErrCode = op->SetValue(val);
			if( m_CompileErrCode != SEE_NOERR )
				m_strErrorCause = m_Tree->GetErrorCause();
			return m_CompileErrCode;
		}
	}
	Destruct();
	m_expr = FormatString("%.16g", val );
	try
	{
		m_Tree = new OperValue( val, m_pVarsTable );
	}
	catch( bad_alloc& )
	{
		m_Tree = NULL;
		return (m_CompileErrCode = SEE_NOMEM);
	}
	OperValue *op = static_cast<OperValue*>(m_Tree);
	m_CompileErrCode = op->SetValue(val);
	if( m_CompileErrCode != SEE_NOERR )
		m_strErrorCause = m_Tree->GetErrorCause();
	return m_CompileErrCode;
}

void CShemeExpr::MakeTree()
{
	string::iterator from = m_expr.begin(), to = m_expr.end();
	try
	{
		m_Tree = new OperRelation( from, to, m_pVarsTable );
	}
	catch( bad_alloc& )
	{
		m_CompileErrCode = SEE_NOMEM;
		return;
	}
	m_CompileErrCode = m_Tree->GetErrorCode();
	if( m_CompileErrCode == SEE_NOERR )
		Optimize();
	else
		m_strErrorCause = m_Tree->GetErrorCause();
}

void CShemeExpr::Optimize()
{
//оптимизация дерева:
	Operation *op = m_Tree;
	while( (op = op->Optimize()) != NULL )
	{
		delete m_Tree;
		m_Tree = op;
	}
	ASSERT( m_Tree );
	m_CompileErrCode = m_Tree->GetErrorCode();
}
//////////////////////////////////////////////////////////////////

CShemeExpr::OperRelation::OperRelation( const std::string::iterator &from, const std::string::iterator &to, CShemeVarsTable *p ):Operation(CShemeExpr::OT_RELATION)
{
	m_from = from;
	m_to = to;
	m_Left = m_Right = NULL;
	m_OpCode = EQ;
	//////////////////////////////////////////////////////////////////////
	m_CompileErrCode = MakeTree(p);
}

void CShemeExpr::OperRelation::ClearErrCode()
{
	m_RunErrCode = SEE_NOERR;
	if( m_Left )
		m_Left->ClearErrCode();
	if( m_Right )
		m_Right->ClearErrCode();
}

CShemeExpr::Operation* CShemeExpr::OperRelation::Optimize()
{
//оптимизация дерева:
	ASSERT( (m_Left != NULL)||(m_Right != NULL) );
	ASSERT( m_CompileErrCode == SEE_NOERR );
	
	Operation *op = NULL;
	if( (m_Left != NULL)&&(m_Right != NULL) )
	{
		op = m_Left;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Left;
			m_Left = op;
		}
		ASSERT( m_Left );
		m_CompileErrCode = m_Left->GetErrorCode();
		if( m_CompileErrCode != SEE_NOERR )
			return NULL;
		op = m_Right;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Right;
			m_Right = op;
		}
		ASSERT( m_Right );
		m_CompileErrCode = m_Right->GetErrorCode();
		if( m_CompileErrCode != SEE_NOERR )
			return NULL;
		if( m_Left->GetOperType() == OT_VALUE )
		{
			if( m_Right->GetOperType() == OT_VALUE )
			{
				OperValue *opl = static_cast<OperValue*>(m_Left);
				if( !opl->IsConstant() )
					return NULL;
				OperValue *opr = static_cast<OperValue*>(m_Right);
				if( !opr->IsConstant() )
					return NULL;
				//если оба константы, то их оптимизируем
				double vl = opl->GetValue(NULL), vr = opr->GetValue(NULL);
				bool tmp;
				switch(m_OpCode)
				{
				case LE:
					tmp = vl <= vr;
					break;
				case GE:
					tmp = vl >= vr;
					break;
				case NE:
					tmp = vl != vr;
					break;
				case GT:
					tmp = vl > vr;
					break;
				case LT:
					tmp = vl < vr;
					break;
				case EQ:
					tmp = vl == vr;
					break;
				}//switch
				try
				{
					op = new OperValue( (tmp)?(1.0):(0.0), NULL );
				}
				catch( bad_alloc& )
				{
					op = NULL;
					m_CompileErrCode = SEE_NOMEM;
					return NULL;
				}
				return op;
			}
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

ShemeExprErr CShemeExpr::OperRelation::MakeTree( CShemeVarsTable *p )
{
	CShemeExpr::PassSpaces( m_from, m_to );
	string::iterator OperBeg = m_from;//начало операнда
	char opers[] = "<>=";
	ShemeExprErr er = CShemeExpr::FindOperation( opers, m_from, m_to );
	if( er != SEE_NOERR )
		return er;
	try
	{
		//первый операнд:
		m_Left = new OperAddSub( OperBeg, m_from, p );
	}
	catch(bad_alloc&)
	{
		m_Left = NULL;
		return SEE_NOMEM;
	}
	if( (m_CompileErrCode = m_Left->GetErrorCode()) != SEE_NOERR )
	{
		m_strErrorCause = m_Left->GetErrorCause();
		return m_CompileErrCode;
	}
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
		CShemeExpr::PassSpaces( m_from, m_to );
		if( m_from == m_to )
			return SEE_SERROR;
		try
		{
			m_Right = new OperAddSub( m_from, m_to, p );
		}
		catch(bad_alloc&)
		{
			m_Right = NULL;
			return SEE_NOMEM;
		}
		if( (m_CompileErrCode = m_Right->GetErrorCode()) != SEE_NOERR )
		{
			m_strErrorCause = m_Right->GetErrorCause();
			return m_CompileErrCode;
		}
	}
	return SEE_NOERR;
}

CShemeExpr::OperRelation::~OperRelation()
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

double CShemeExpr::OperRelation::GetValue( CShemeVarsTable *p )
{
	if( m_CompileErrCode != SEE_NOERR )
	{
		m_RunErrCode = SEE_CERROR;
		return 0.0;
	}
	if( !m_Left || !m_Right )
	{
		if( m_Left )
		{
			double res = m_Left->GetValue(p);
			if( (m_RunErrCode = m_Left->GetErrorCode(false)) != SEE_NOERR )
			{
				m_strErrorCause = m_Left->GetErrorCause();
			}
			return res;
		}
		if( m_Right )
		{
			double res = m_Right->GetValue(p);
			if( (m_RunErrCode = m_Right->GetErrorCode(false)) != SEE_NOERR )
			{
				m_strErrorCause = m_Right->GetErrorCause();
			}
			return res;
		}
		ASSERT(FALSE);
	}
	//если оба ненулевые, то надо проверить отношение
	ASSERT( m_Left );
	ASSERT( m_Right );
	double left = m_Left->GetValue(p);
	if( (m_RunErrCode = m_Left->GetErrorCode(false)) != SEE_NOERR )
	{
		m_strErrorCause = m_Left->GetErrorCause();
		return 0.0;
	}

	double right = m_Right->GetValue(p);
	if( (m_RunErrCode = m_Right->GetErrorCode(false)) != SEE_NOERR )
	{
		m_strErrorCause = m_Right->GetErrorCause();
		return 0.0;
	}

	bool tmp;
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
	return (tmp)?(1.0):(0.0);
}

//////////////////////////////////////////////////////////////////
CShemeExpr::OperAddSub::OperAddSub( const std::string::iterator &from, const std::string::iterator &to, CShemeVarsTable *p ):Operation(CShemeExpr::OT_ADDSUB)
{
	m_from = from;
	m_to = to;
	m_Left = m_Right = NULL;
	m_OpCode = '+';
	//////////////////////////////////////////////////////////////////////
	m_CompileErrCode = MakeTree(p);
}

void CShemeExpr::OperAddSub::ClearErrCode()
{
	m_RunErrCode = SEE_NOERR;
	if( m_Left )
		m_Left->ClearErrCode();
	if( m_Right )
		m_Right->ClearErrCode();
}

CShemeExpr::Operation* CShemeExpr::OperAddSub::Optimize()
{
//оптимизация дерева:
	ASSERT( (m_Left != NULL)||(m_Right != NULL) );
	ASSERT( m_CompileErrCode == SEE_NOERR );
	
	Operation *op = NULL;
	if( (m_Left != NULL)&&(m_Right != NULL) )
	{
		op = m_Left;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Left;
			m_Left = op;
		}
		ASSERT( m_Left );
		m_CompileErrCode = m_Left->GetErrorCode();
		if( m_CompileErrCode != SEE_NOERR )
			return NULL;
		op = m_Right;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Right;
			m_Right = op;
		}
		ASSERT( m_Right );
		m_CompileErrCode = m_Right->GetErrorCode();
		if( m_CompileErrCode != SEE_NOERR )
			return NULL;
		if( m_Left->GetOperType() == OT_VALUE )
		{
			if( m_Right->GetOperType() == OT_VALUE )
			{
				OperValue *opl = static_cast<OperValue*>(m_Left);
				if( !opl->IsConstant() )
					return NULL;
				OperValue *opr = static_cast<OperValue*>(m_Right);
				if( !opr->IsConstant() )
					return NULL;
				//если оба константы, то их оптимизируем
				double vl = opl->GetValue(NULL), vr = opr->GetValue(NULL);
				if( m_OpCode == '+' )
				{
					//сложение
					try
					{
						op = new OperValue( vl+vr, NULL );
					}
					catch( bad_alloc& )
					{
						op = NULL;
						m_CompileErrCode = SEE_NOMEM;
						return NULL;
					}
					return op;
				}
				else
				{
					//вычитание
					try
					{
						op = new OperValue( vl-vr, NULL );
					}
					catch( bad_alloc& )
					{
						op = NULL;
						m_CompileErrCode = SEE_NOMEM;
						return NULL;
					}
					return op;
				}
			}
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

ShemeExprErr CShemeExpr::OperAddSub::MakeTree( CShemeVarsTable *p )
{
	CShemeExpr::PassSpaces( m_from, m_to );
	string::iterator OperBeg = m_from;//начало операнда
	char opers[] = "+-";
	if( strchr(opers,*m_from) != NULL )	++m_from;//унарный знак
	ShemeExprErr er = CShemeExpr::FindOperation( opers, m_from, m_to );
	if( er != SEE_NOERR )
		return er;
	try
	{
		//первый операнд:
		m_Left = new OperMultDiv( OperBeg, m_from, p );
	}
	catch(bad_alloc&)
	{
		m_Left = NULL;
		return SEE_NOMEM;
	}
	if( (m_CompileErrCode = m_Left->GetErrorCode()) != SEE_NOERR )
	{
		m_strErrorCause = m_Left->GetErrorCause();
		return m_CompileErrCode;
	}
	if( m_from != m_to )
	{
		//если второй операнд всё-таки есть
		m_OpCode = *m_from;
		++m_from;
		OperBeg = m_from;
		CShemeExpr::PassSpaces( m_from, m_to );
		if( m_from == m_to )
			return SEE_SERROR;
		if( strchr("+-*/^",*m_from) )
			return SEE_SERROR;
		m_from = OperBeg;
		try
		{
			m_Right = new OperMultDiv( m_from, m_to, p );
		}
		catch(bad_alloc&)
		{
			m_Right = NULL;
			return SEE_NOMEM;
		}
		if( (m_CompileErrCode = m_Right->GetErrorCode()) != SEE_NOERR )
		{
			m_strErrorCause = m_Right->GetErrorCause();
			return m_CompileErrCode;
		}
	}
	return SEE_NOERR;
}

CShemeExpr::OperAddSub::~OperAddSub()
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

double CShemeExpr::OperAddSub::GetValue( CShemeVarsTable *p )
{
	if( m_CompileErrCode != SEE_NOERR )
	{
		m_RunErrCode = SEE_CERROR;
		return 0.0;
	}
	if( !m_Left || !m_Right )
	{
		if( m_Left )
		{
			double res = m_Left->GetValue(p);
			if( (m_RunErrCode = m_Left->GetErrorCode(false)) != SEE_NOERR )
			{
				m_strErrorCause = m_Left->GetErrorCause();
			}
			return res;
		}
		if( m_Right )
		{
			double res = m_Right->GetValue(p);
			if( (m_RunErrCode = m_Right->GetErrorCode(false)) != SEE_NOERR )
			{
				m_strErrorCause = m_Right->GetErrorCause();
			}
			return res;
		}
		ASSERT(FALSE);
	}
	//если оба ненулевые:
	ASSERT( m_Left );
	ASSERT( m_Right );
	double left = m_Left->GetValue(p);
	if( (m_RunErrCode = m_Left->GetErrorCode(false)) != SEE_NOERR )
	{
		m_strErrorCause = m_Left->GetErrorCause();
		return 0.0;
	}

	double right = m_Right->GetValue(p);
	if( (m_RunErrCode = m_Right->GetErrorCode(false)) != SEE_NOERR )
	{
		m_strErrorCause = m_Right->GetErrorCause();
		return 0.0;
	}

	if( m_OpCode == '+' )
	{
		//сложение
		left += right;
	}
	else
	{
		//вычитание
		left -= right;
	}
	return left;
}
//////////////////////////////////////////////////////////////////////////
CShemeExpr::OperMultDiv::OperMultDiv( const std::string::iterator &from, const std::string::iterator &to, CShemeVarsTable *p ):Operation(CShemeExpr::OT_MULTDIV)
{
	m_from = from;
	m_to = to;
	m_Left = m_Right = NULL;
	m_OpCode = '*';
	//////////////////////////////////////////////////////////////////////
	m_CompileErrCode = MakeTree(p);
}

void CShemeExpr::OperMultDiv::ClearErrCode()
{
	m_RunErrCode = SEE_NOERR;
	if( m_Left )
		m_Left->ClearErrCode();
	if( m_Right )
		m_Right->ClearErrCode();
}

CShemeExpr::Operation* CShemeExpr::OperMultDiv::Optimize()
{
//оптимизация дерева:
	ASSERT( (m_Left != NULL)||(m_Right != NULL) );
	ASSERT( m_CompileErrCode == SEE_NOERR );
	
	Operation *op = NULL;
	if( (m_Left != NULL)&&(m_Right != NULL) )
	{
		op = m_Left;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Left;
			m_Left = op;
		}
		ASSERT( m_Left );
		m_CompileErrCode = m_Left->GetErrorCode();
		if( m_CompileErrCode != SEE_NOERR )
			return NULL;
		op = m_Right;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Right;
			m_Right = op;
		}
		ASSERT( m_Right );
		m_CompileErrCode = m_Right->GetErrorCode();
		if( m_CompileErrCode != SEE_NOERR )
			return NULL;
		if( m_Left->GetOperType() == OT_VALUE )
		{
			if( m_Right->GetOperType() == OT_VALUE )
			{
				OperValue *opl = static_cast<OperValue*>(m_Left);
				if( !opl->IsConstant() )
					return NULL;
				OperValue *opr = static_cast<OperValue*>(m_Right);
				if( !opr->IsConstant() )
					return NULL;
				//если оба константы, то их оптимизируем
				double vl = opl->GetValue(NULL), vr = opr->GetValue(NULL);
				if( m_OpCode == '*' )
				{
					try
					{
						op = new OperValue( vl*vr, NULL );
					}
					catch( bad_alloc& )
					{
						op = NULL;
						m_CompileErrCode = SEE_NOMEM;
						return NULL;
					}
					return op;
				}
				else
				{
					if( fabs(vr) < DOUBLE_ZERO )
					{
						m_CompileErrCode = SEE_DIV_ZERO;
						m_strErrorCause = "операция /";
						return NULL;
					}
					try
					{
						op = new OperValue( vl/vr, NULL );
					}
					catch( bad_alloc& )
					{
						op = NULL;
						m_CompileErrCode = SEE_NOMEM;
						return NULL;
					}
					return op;
				}
			}
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

ShemeExprErr CShemeExpr::OperMultDiv::MakeTree( CShemeVarsTable *p )
{
	CShemeExpr::PassSpaces( m_from, m_to );
	string::iterator OperBeg = m_from;//начало операнда
	//ищем сначала операции "+-"
	char opers[] = "+-";
	if( strchr(opers,*m_from) != NULL )	++m_from;//унарный знак
	ShemeExprErr er = CShemeExpr::FindOperation( opers, m_from, m_to );
	if( er != SEE_NOERR )
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
			m_Left = NULL;
			return SEE_NOMEM;
		}
		if( (m_CompileErrCode = m_Left->GetErrorCode()) != SEE_NOERR )
		{
			m_strErrorCause = m_Left->GetErrorCause();
			return m_CompileErrCode;
		}
		return SEE_NOERR;
	}
	//если "+-" нету, то ищем "*/"
	m_from = OperBeg;
	opers[0] = '*';
	opers[1] = '/';
	er = CShemeExpr::FindOperation( opers, m_from, m_to );
	if( er != SEE_NOERR )
		return er;
	try
	{
		//первый операнд:
		m_Left = new OperPow( OperBeg, m_from, p );
	}
	catch(bad_alloc&)
	{
		m_Left = NULL;
		return SEE_NOMEM;
	}
	if( (m_CompileErrCode = m_Left->GetErrorCode()) != SEE_NOERR )
	{
		m_strErrorCause = m_Left->GetErrorCause();
		return m_CompileErrCode;
	}
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
			m_Right = NULL;
			return SEE_NOMEM;
		}
		if( (m_CompileErrCode = m_Right->GetErrorCode()) != SEE_NOERR )
		{
			m_strErrorCause = m_Right->GetErrorCause();
			return m_CompileErrCode;
		}
	}
	return SEE_NOERR;
}

CShemeExpr::OperMultDiv::~OperMultDiv()
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

double CShemeExpr::OperMultDiv::GetValue( CShemeVarsTable *p )
{
	if( m_CompileErrCode != SEE_NOERR )
	{
		m_RunErrCode = SEE_CERROR;
		return 0.0;
	}
	if( !m_Left || !m_Right )
	{
		if( m_Left )
		{
			double res = m_Left->GetValue(p);
			if( (m_RunErrCode = m_Left->GetErrorCode(false)) != SEE_NOERR )
			{
				m_strErrorCause = m_Left->GetErrorCause();
			}
			return res;
		}
		if( m_Right )
		{
			double res = m_Right->GetValue(p);
			if( (m_RunErrCode = m_Right->GetErrorCode(false)) != SEE_NOERR )
			{
				m_strErrorCause = m_Right->GetErrorCause();
			}
			return res;
		}
		ASSERT(FALSE);
	}
	//если оба ненулевые:
	ASSERT( m_Left );
	ASSERT( m_Right );
	double left = m_Left->GetValue(p);
	if( (m_RunErrCode = m_Left->GetErrorCode(false)) != SEE_NOERR )
	{
		m_strErrorCause = m_Left->GetErrorCause();
		return 0.0;
	}

	double right = m_Right->GetValue(p);
	if( (m_RunErrCode = m_Right->GetErrorCode(false)) != SEE_NOERR )
	{
		m_strErrorCause = m_Right->GetErrorCause();
		return 0.0;
	}

	if( m_OpCode == '*' )
	{
		//умножение
		left *= right;
	}
	else
	{
		//деление
		if( fabs(right) < DOUBLE_ZERO )
		{
			left = numeric_limits<double>::max();
			m_RunErrCode = SEE_DIV_ZERO;
			m_strErrorCause = "операция /";
		}
		else
		{
			left /= right;
		}
	}
	return left;
}
///////////////////////////////////////////////////////////////////////////////
CShemeExpr::OperPow::OperPow( const std::string::iterator &from, const std::string::iterator &to, CShemeVarsTable *p ):Operation(CShemeExpr::OT_POW)
{
	m_from = from;
	m_to = to;
	m_Left = m_Right = NULL;
	//////////////////////////////////////////////////////////////////////
	m_CompileErrCode = MakeTree(p);
}

void CShemeExpr::OperPow::ClearErrCode()
{
	m_RunErrCode = SEE_NOERR;
	if( m_Left )
		m_Left->ClearErrCode();
	if( m_Right )
		m_Right->ClearErrCode();
}

CShemeExpr::Operation* CShemeExpr::OperPow::Optimize()
{
//оптимизация дерева:
	ASSERT( (m_Left != NULL)||(m_Right != NULL) );
	ASSERT( m_CompileErrCode == SEE_NOERR );
	
	Operation *op = NULL;
	if( (m_Left != NULL)&&(m_Right != NULL) )
	{
		op = m_Left;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Left;
			m_Left = op;
		}
		ASSERT( m_Left );
		m_CompileErrCode = m_Left->GetErrorCode();
		if( m_CompileErrCode != SEE_NOERR )
			return NULL;
		op = m_Right;
		while( (op = op->Optimize()) != NULL )
		{
			delete m_Right;
			m_Right = op;
		}
		ASSERT( m_Right );
		m_CompileErrCode = m_Right->GetErrorCode();
		if( m_CompileErrCode != SEE_NOERR )
			return NULL;
		if( m_Left->GetOperType() == OT_VALUE )
		{
			if( m_Right->GetOperType() == OT_VALUE )
			{
				OperValue *opl = static_cast<OperValue*>(m_Left);
				if( !opl->IsConstant() )
					return NULL;
				OperValue *opr = static_cast<OperValue*>(m_Right);
				if( !opr->IsConstant() )
					return NULL;
				//если оба константы, то их оптимизируем
				double vl = opl->GetValue(NULL), vr = opr->GetValue(NULL);
				if( (vr < 0.0)&&(fabs(vl) < DOUBLE_ZERO) )
				{
					m_CompileErrCode = SEE_DIV_ZERO;
					m_strErrorCause = "операция ^";
					return NULL;
				}
				vl = pow( vl, vr );
				if( (vl > numeric_limits<double>::max())||
					(vl < numeric_limits<double>::min()) )
				{
					m_strErrorCause = "операция ^";
					m_CompileErrCode = SEE_FP_ERR;
					return NULL;
				}
				try
				{
					op = new OperValue( vl, NULL );
				}
				catch( bad_alloc& )
				{
					op = NULL;
					m_CompileErrCode = SEE_NOMEM;
					return NULL;
				}
				return op;
			}
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

ShemeExprErr CShemeExpr::OperPow::MakeTree( CShemeVarsTable *p )
{
	CShemeExpr::PassSpaces( m_from, m_to );
	string::iterator OperBeg = m_from;//начало операнда
	//ищем сначала операции "+-*/"
	if( strchr("+-",*m_from) != NULL )	++m_from;//унарный знак
	char opers[] = "+-*/";
	ShemeExprErr er = CShemeExpr::FindOperation( opers, m_from, m_to );
	if( er != SEE_NOERR )
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
			m_Left = NULL;
			return SEE_NOMEM;
		}
		if( (m_CompileErrCode = m_Left->GetErrorCode()) != SEE_NOERR )
		{
			m_strErrorCause = m_Left->GetErrorCause();
			return m_CompileErrCode;
		}
		return SEE_NOERR;
	}
	//если "+-*/" нету, то ищем "^"
	m_from = OperBeg;
	while( (*m_from != '^')&&(m_from != m_to) )
	{	
		if( *m_from == '(' )
		{
			if( !CShemeExpr::FindParen( m_from, m_to ) )
			{
				return SEE_PARENS;
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
		m_Left = NULL;
		return SEE_NOMEM;
	}
	if( (m_CompileErrCode = m_Left->GetErrorCode()) != SEE_NOERR )
	{
		m_strErrorCause = m_Left->GetErrorCause();
		return m_CompileErrCode;
	}
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
			m_Right = NULL;
			return SEE_NOMEM;
		}
		if( (m_CompileErrCode = m_Right->GetErrorCode()) != SEE_NOERR )
		{
			m_strErrorCause = m_Right->GetErrorCause();
			return m_CompileErrCode;
		}
	}
	return SEE_NOERR;
}

CShemeExpr::OperPow::~OperPow()
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

double CShemeExpr::OperPow::GetValue( CShemeVarsTable *p )
{
	if( m_CompileErrCode != SEE_NOERR )
	{
		m_RunErrCode = SEE_CERROR;
		return 0.0;
	}
	double left = 0.0;
	if( m_Left )
	{
		left = m_Left->GetValue(p);
		if( (m_RunErrCode = m_Left->GetErrorCode(false)) != SEE_NOERR )
		{
			m_strErrorCause = m_Left->GetErrorCause();
			return 0.0;
		}
	}
	if( m_Right )
	{
		double right = m_Right->GetValue(p);
		if( (m_RunErrCode = m_Right->GetErrorCode(false)) != SEE_NOERR )
		{
			m_strErrorCause = m_Right->GetErrorCause();
			return 0.0;
		}
		if( (right < 0.0)&&(fabs(left) < DOUBLE_ZERO) )
		{
			m_RunErrCode = SEE_DIV_ZERO;
			m_strErrorCause = "операция ^";
			return numeric_limits<double>::max();
		}
		left = pow( left, right );
		if( (left > numeric_limits<double>::max())||
			(left < numeric_limits<double>::min()) )
		{
			m_strErrorCause = "операция ^";
			m_RunErrCode = SEE_FP_ERR;
			left = 0.0;
		}
	}
	return left;
}
/////////////////////////////////////////////////////////////////////
CShemeExpr::OperValue::OperValue( const std::string::iterator &from, const std::string::iterator &to, CShemeVarsTable *p ):Operation(CShemeExpr::OT_VALUE)
{
	m_Tree = NULL;
	m_bNeg = false;
	m_dValue = 0.0;
	m_from = from;
	m_to = to;
	//////////////////////////////////////////////////////////////////////
	m_CompileErrCode = MakeTree(p);
}

CShemeExpr::OperValue::OperValue( double val, CShemeVarsTable *p ):Operation(CShemeExpr::OT_VALUE)
{
	m_Tree = NULL;
	m_bNeg = false;
	m_VarName = "";
	m_dValue = val;
	m_CompileErrCode = SEE_NOERR;
}

void CShemeExpr::OperValue::ClearErrCode()
{
	m_RunErrCode = SEE_NOERR;
	if( m_Tree )
		m_Tree->ClearErrCode();
}

CShemeExpr::Operation* CShemeExpr::OperValue::Optimize()
{
//оптимизация дерева:
	ASSERT( m_CompileErrCode == SEE_NOERR );
	
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
	ASSERT( m_Tree );
	m_CompileErrCode = m_Tree->GetErrorCode();
	if( m_CompileErrCode != SEE_NOERR )
		return NULL;
	op = m_Tree;
	m_Tree = NULL;
	return op;
}

ShemeExprErr CShemeExpr::OperValue::MakeTree( CShemeVarsTable *p )
{
	CShemeExpr::PassSpaces( m_from, m_to );
	if( strchr("+-",*m_from) != NULL )
	{
		if( *m_from == '-' )
			m_bNeg = true;
		++m_from;//унарный знак
	}
	CShemeExpr::PassSpaces( m_from, m_to );
	string::iterator OperBeg = m_from;//начало операнда
	string::iterator OperEnd = m_to;//конец операнда
	//отбросим наружные парные скобки, если такие есть, т.е. напр: (((1+2)))
	while( *m_from == '(' )
	{
		OperBeg = m_from;//OperBeg указывает на первую скобку
		if( !CShemeExpr::FindParen( m_from, m_to ) )
		{
			return SEE_PARENS;
		}
		OperEnd = m_from;//OperEnd - на парную ей
		++m_from;
		CShemeExpr::PassSpaces( m_from, m_to );
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
		CShemeExpr::PassSpaces( m_from, m_to );
	}
	m_from = OperBeg;
	m_to = OperEnd;

	bool bExpr = false;//флаг о том, что в [m_from;m_to) находится выражение
	for( ; m_from != m_to; ++m_from )
	{
		if( strchr("+-*/()^,",*m_from) != NULL )
		{
			bExpr = true;
			break;
		}
	}
	m_from = OperBeg;
	
	if( bExpr )
	{
		//значит там выражение.
		//проверяем: можно ли разобрать его на операнды?
		//ищем операции "+-*/"
		char opers[] = "+-*/^";
		ShemeExprErr er = CShemeExpr::FindOperation( opers, m_from, m_to );
		ASSERT(er == SEE_NOERR);//такого не должно быть
		if( m_from == m_to )
		{
			//значит его нельзя разобрать на операнды
			m_from = OperBeg;
			//проверим: не ф-ция ли это?
			CShemeExpr::PassSpaces( m_from, m_to );
			OperBeg = m_from;//указатель на первый символ имени ф-ции
			if( !isalpha(*m_from) && (*m_from != '_') )
			{
				//значит там недопустимое имя ф-ции
				return SEE_SERROR;
			}
			//ищем конец имени
			++m_from;
			while( isdigit(*m_from)||isalpha(*m_from)||(*m_from == '_') )
				++m_from;
			string FuncName( OperBeg, m_from );//имя ф-ции
			CShemeExpr::PassSpaces( m_from, m_to );
			if( *m_from != '(' )
			{
				return SEE_SERROR;
			}
			OperBeg = m_from + 1;//указатель на начало строки с пар-ми ф-ции
			//отбросим скобки:
			if( !CShemeExpr::FindParen( m_from, m_to ) )
			{
				//такого не должно быть, т.к. парность скобок проверена выше
				ASSERT(FALSE);
				return SEE_PARENS;
			}
			string FuncParams( OperBeg, m_from );//пар-ры ф-ции без скобок
			++m_from;
			CShemeExpr::PassSpaces( m_from, m_to );
			if( m_from != m_to )
			{
				//если за скобкой, парной предыдущей, что-то есть,
				//то это ошибка:
				return SEE_SERROR;
			}
			//иначе - это вызов ф-ции
			try
			{
				m_Tree = new OperCallFunc( FuncName, FuncParams, p );
			}
			catch( bad_alloc& )
			{
				m_Tree = NULL;
				return SEE_NOMEM;
			}
			if( (m_CompileErrCode = m_Tree->GetErrorCode()) != SEE_NOERR )
			{
				m_strErrorCause = m_Tree->GetErrorCause();
			}
			return m_CompileErrCode;
		}
		try
		{
			m_Tree = new OperAddSub( OperBeg, m_to, p );
		}
		catch( bad_alloc& )
		{
			m_Tree = NULL;
			return SEE_NOMEM;
		}
		if( (m_CompileErrCode = m_Tree->GetErrorCode()) != SEE_NOERR )
		{
			m_strErrorCause = m_Tree->GetErrorCause();
		}
		return m_CompileErrCode;
	}
	//значит здесь переменная или константа
	CShemeExpr::PassSpaces( m_from, m_to );
	OperBeg = m_from;
	while( (m_from != m_to)&&(*m_from != ' ')&&(*m_from != '\t') )
	{
		++m_from;
	}
	OperEnd = m_from;
	CShemeExpr::PassSpaces( m_from, m_to );
	if( m_from != m_to )
	{
		return SEE_SERROR;
	}
	m_from = OperBeg;
	string tmp = string( m_from, OperEnd );
	if( tmp.empty() )
		return SEE_SERROR;

	if( isalpha(*m_from) || (*m_from == '_') )
	{
		//возможно переменная
		m_VarName = tmp;
		MakeLower(m_VarName);
		if( p == NULL )
		{
			m_strErrorCause = "неинициализирована таблица переменных";
			return SEE_UNKN_ERR;
		}
		if( !p->IsVarName(m_VarName) )
		{
			m_strErrorCause = tmp;
			return SEE_WRONG_SIMBOL;
		}
		return SEE_NOERR;
	}
	//здесь уже точно знаем, что это не переменная.
	m_dValue = atof( tmp.c_str() );
	if( m_bNeg )
	{
		m_dValue = -m_dValue;
	}
	return SEE_NOERR;
}

CShemeExpr::OperValue::~OperValue()
{
	if( m_Tree != NULL )
	{
		delete m_Tree;
		m_Tree = NULL;
	}
}

ShemeExprErr CShemeExpr::OperValue::SetValue( double val )
{
	if( m_Tree != NULL )
	{
		delete m_Tree;
		m_Tree = NULL;
	}
	m_bNeg = false;
	m_VarName = "";
	m_dValue = val;
	return (m_CompileErrCode = SEE_NOERR);
}

double CShemeExpr::OperValue::GetValue( CShemeVarsTable *p )
{
	if( m_CompileErrCode != SEE_NOERR )
	{
		m_RunErrCode = SEE_CERROR;
		return 0.0;
	}
	if( m_Tree )
	{
		//если это не переменная или константа, то выражение или ф-ция
		double res = m_Tree->GetValue(p);
		if( (m_RunErrCode = m_Tree->GetErrorCode(false)) != SEE_NOERR )
		{
			m_strErrorCause = m_Tree->GetErrorCause();
			return 0.0;
		}
		if( m_bNeg )
			res = -res;
		return res;
	}
	//иначе:
	if( !m_VarName.empty() )
	{
		//значит переменная
		ShemeExprErr er;
		if( p == NULL )
		{
			m_strErrorCause = "неинициализирована таблица переменных";
			m_RunErrCode = SEE_UNKN_ERR;
			return 0.0;
		}
		double res = p->GetVarValue( m_VarName, er );
		if( er != SEE_NOERR )
		{
			m_RunErrCode = er;
			m_strErrorCause = m_VarName;
			return 0.0;
		}
		if( m_bNeg )
			res = -res;
		return res;
	}
	//иначе константа
	return m_dValue;
}

bool CShemeExpr::OperValue::IsConstant() const
{
	if( m_Tree != NULL )
		return false;
	if( !m_VarName.empty() )
		return false;
	return true;
}

bool CShemeExpr::OperValue::IsVarName() const
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
CShemeExpr::OperCallFunc::OperCallFunc( const std::string &name, const std::string &params, CShemeVarsTable *p ):Operation(CShemeExpr::OT_FUNC)
{
	m_FuncName = name;
	MakeLower(m_FuncName);
	m_Params = params;
	//m_ft = FT_INTERNAL;
	//////////////////////////////////////////////////////////////////////
	m_CompileErrCode = MakeTree(p);
}

void CShemeExpr::OperCallFunc::ClearErrCode()
{
	m_RunErrCode = SEE_NOERR;
}

CShemeExpr::Operation* CShemeExpr::OperCallFunc::Optimize()
{
//оптимизация дерева:
	ASSERT( m_CompileErrCode == SEE_NOERR );
	if( (m_FuncID == FID_RANDOM)||(m_FuncID ==  FID_WRONG) )
		return NULL;
	bool bConst = true;
	ShemeFuncParamList::iterator it = m_ParamsList.begin(), fin = m_ParamsList.end();
	for(; it != fin; ++it )
	{
		if( !(*it)->IsConstant() )
		{
			bConst = false;
			break;
		}
	}
	if( bConst )
	{
		//если все параметры ф-ции константы, то её можно оптимизировать
		double val = GetValue( NULL );
		if( m_RunErrCode != SEE_NOERR )
			return NULL;
		Operation *op;
		try
		{
			op = new OperValue( val, NULL );
		}
		catch( bad_alloc& )
		{
			op = NULL;
			m_CompileErrCode = SEE_NOMEM;
			return NULL;
		}
		return op;
	}
	return NULL;
}

ShemeExprErr CShemeExpr::OperCallFunc::MakeTree( CShemeVarsTable *p )
{
	//узнаем пренадлежность ф-ции
	//проверяем, есть ли такая ф-ция среди встроенных:
	CShemeExpr::InternalFuncMap::iterator it = CShemeExpr::m_FuncTable.find(m_FuncName);
	if( it == CShemeExpr::m_FuncTable.end() )
	{
		//такой ф-ции нет.
		m_strErrorCause = m_FuncName;
		return SEE_WRONG_SIMBOL;
	}
	else
	{
		m_FuncID = (*it).second.m_ID;
		//m_ft = FT_INTERNAL;
	}
	////////////////////////////////////////////////////
	string::iterator from = m_Params.begin(), to = m_Params.end();
	CShemeExpr::PassSpaces( from, to );
	if( from != to )
	{
		//с параметрами
		for(;;)
		{
			//читаем пар-ры
			char opers[] = ",";
			string::iterator OperBeg = from;
			ShemeExprErr er = CShemeExpr::FindOperation( opers, from, to );
			ASSERT(er == SEE_NOERR);//такого не должно быть
			CShemeExpr *pPar;//указатель на пар-р ф-ции
			try
			{
				pPar = new CShemeExpr( string(OperBeg,from), p );
			}
			catch( bad_alloc& )
			{
				pPar = NULL;
				return SEE_NOMEM;
			}
			er = pPar->GetCompileErrorCode();
			if( er != SEE_NOERR )	
			{
				m_strErrorCause = pPar->GetErrorCause();
				delete pPar;
				return er;
			}
			m_ParamsList.push_back(pPar);
			if( from == to )	break;
			++from;//указатель на символ, стоящий вслед за запятой
			CShemeExpr::PassSpaces( from, to );
		}//for(;;)
	}
	int s = m_ParamsList.size();
	if( !(*it).second.IsValidParamNum( s ) )
	{
		m_strErrorCause = m_FuncName;
		return SEE_WRONG_FUNC_PARAM_NUM;
	}
	return SEE_NOERR;
}

CShemeExpr::OperCallFunc::~OperCallFunc()
{
	while( !m_ParamsList.empty() )
	{
		delete (*m_ParamsList.begin());
		m_ParamsList.erase( m_ParamsList.begin() );
	}
}

double CShemeExpr::OperCallFunc::GetValue( CShemeVarsTable *p )
{
	if( m_CompileErrCode != SEE_NOERR )
	{
		m_RunErrCode = SEE_CERROR;
		return 0.0;
	}
	return CShemeExpr::InternalFunc::GetValue( m_FuncID, m_ParamsList, m_RunErrCode, p, m_strErrorCause );
}
