// ShemeVarsTable.cpp: implementation of the CShemeVarsTable class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "NSys2D.h"
#include "ShemeVarsTable.h"

#include<new>
#include<vector>
#include<algorithm>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void MakeLower( std::string& );

bool IsLowerCase( const std::string &str )
{
	string::const_iterator fin = str.end();
	for( string::const_iterator it = str.begin(); it != fin; ++it )
	{
		if( (isalpha(*it))&&(islower(*it) == 0) )
			return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShemeVarsTable::CShemeVarsTable()
{
	//инициализируем таблицу переменных:
	AddInternalVar( string("x"), 0.0 );//перемещение степени свободы
	AddInternalVar( string("v"), 0.0 );//скорость степени свободы
	AddInternalVar( string("a"), 0.0 );//ускорение
	AddInternalVar( string("t"), 0.0 );//текущее время
	AddInternalVar( string("cx"), 0.0 );//коор-та X узла
	AddInternalVar( string("cy"), 0.0 );//коор-та Y узла
	AddInternalVar( string("cx1"), 0.0 );//коор-та X первого узла элемента
	AddInternalVar( string("cy1"), 0.0 );//коор-та Y первого узла элемента
	AddInternalVar( string("cx2"), 0.0 );//коор-та X второго узла элемента
	AddInternalVar( string("cy2"), 0.0 );//коор-та Y второго узла элемента
	AddInternalVar( string("w"), 0.0 );//частота
	AddInternalVar( string("pi"), CNSys2DApp::M_PI );
}

CShemeVarsTable::~CShemeVarsTable()
{
	while( !m_VarsTable.empty() )
	{
		ShemeVarsTable::iterator it = m_VarsTable.begin();
		delete (*it).second;
		m_VarsTable.erase( it );
	}
}
//////////////////////////////////////////////////////////////////////
// Member functions
//////////////////////////////////////////////////////////////////////
void CShemeVarsTable::AddInternalVar( std::string &name, double val )
{
	MakeLower(name);
	CShemeExpr *se;
	try
	{
		se = new CShemeExpr( val, this );
	}
	catch( bad_alloc& )
	{
		se = NULL;
		AfxMessageBox("Ошибка выделения памяти!!!");
		return;
	}
	ShemeExprErr er = se->GetCompileErrorCode();
	ASSERT( er == SEE_NOERR );
	ShemeVarsPair pr = m_VarsTable.insert( MakeShemeVar(name,se) );
	ASSERT( pr.second == true );
}

bool CShemeVarsTable::IsVarName( const std::string &name )
{
//	ShemeVarsTable::iterator it = m_VarsTable.find(name);
//	ShemeVarsTable::iterator fin = m_VarsTable.end();
//	return ( it != fin );
	return ( m_VarsTable.find(name) != m_VarsTable.end() );
}

std::string CShemeVarsTable::GetErrorCause( const std::string &str )
{
	string name(str);
	MakeLower(name);
	ShemeVarsTable::iterator it = m_VarsTable.find(name);
	if( it == m_VarsTable.end() )
	{
		return string("");
	}
	return (*it).second->GetErrorCause();
}

ShemeExprErr CShemeVarsTable::GetCompileErrorCode( const std::string &str )
{
	string name(str);
	MakeLower(name);
	ShemeVarsTable::iterator it = m_VarsTable.find(name);
	if( it == m_VarsTable.end() )
	{
		return SEE_UNKN_ERR;
	}
	return (*it).second->GetCompileErrorCode();
}

bool CShemeVarsTable::SetVarValue( const std::string &name, double val )
{
	ASSERT( IsLowerCase(name) );
	if( !IsValidateParam(name) )
		return false;
	ShemeVarsTable::iterator it = m_VarsTable.find(name);
	if( it == m_VarsTable.end() )
		return false;
	(*it).second->SetValue(val);
	return true;
}

double CShemeVarsTable::GetVarValue( const std::string &name, ShemeExprErr &err )
{
	ShemeVarsTable::iterator it = m_VarsTable.find(name);
	if( it == m_VarsTable.end() )
	{
		err = SEE_WRONG_SIMBOL;
		return 0.0;
	}
	list<string>::iterator fin = m_lstActiveNames.end();
	list<string>::iterator itlst = find( m_lstActiveNames.begin(), fin, name );
	if( itlst != fin )
	{
		//значит такая переменная уже вычисляется 
		//и пытается обратиться к самой себе - зацикливание.
		err = SEE_CYCLE;
		return 0.0;
	}
	itlst = m_lstActiveNames.insert( fin, name );
	double res = (*it).second->GetValue();
	err = (*it).second->GetRunErrorCode();
	m_lstActiveNames.erase( itlst );
	if( err != SEE_NOERR )
		return 0.0;
	return res;
}

bool CShemeVarsTable::IsValidateParam( const std::string &name )
{
//ф-ция проверяет - является ли name изменяемой внутренней переменной?
	if( (name == "x")||
		(name == "v")||
		(name == "a")||
		(name == "t")||
		(name == "cx")||
		(name == "cy")||
		(name == "cx1")||
		(name == "cy1")||
		(name == "cx2")||
		(name == "cy2")||
		(name == "w") )
		return true;
	return false;
}

bool CShemeVarsTable::IsReservedVarName( const std::string &str )
{
	string name(str);
	MakeLower(name);
	if(	IsValidateParam(name) )
		return true;
	if( name == "pi" )
		return true;
	if( CShemeExpr::m_FuncTable.find(name) != CShemeExpr::m_FuncTable.end() )
		return true;
	return false;
}

bool CShemeVarsTable::IsValidExpr( const CString &expr, CString &mes )
{
	string ec;
	ShemeExprErr err = IsValidExpr(string(static_cast<LPCTSTR>(expr)), ec );
	if( err == SEE_NOERR )
	{
		mes.Empty();
		return true;
	}
	mes = CShemeExpr::GetErrorMessage(err).c_str();
	if( !ec.empty() )
	{
		mes += CString(": ") + CString( ec.c_str() );
	}
	return false;
}

ShemeExprErr CShemeVarsTable::IsValidExpr( const std::string &expr, std::string &cause )
{
	cause = "";
	CShemeExpr se( expr, this );
	ShemeExprErr er = se.GetCompileErrorCode();
	if( er != SEE_NOERR )
	{
		cause = se.GetErrorCause();
	}
	return er;
}
	
bool CShemeVarsTable::IsValidVarName( const std::string &str )
{
	if( str.empty() )
		return false;
	string name(str);
	string::iterator it = name.begin();
	if( !isalpha(*it)&&(*it != '_') )
		return false;
	string::iterator fin = name.end();
	for(; it != fin; ++it )
	{
		if( !isalpha(*it)&&(*it != '_')&&(!isdigit(*it)) )
			return false;
	}
	return true;
}

ShemeExprErr CShemeVarsTable::AddVar( std::string &name, const std::string &expr, bool flg )
{
//flg - флаг о проверке синтаксиса выражения
	MakeLower(name);
	if( !IsValidVarName(name) )
		return SEE_SERROR;
	if( IsVarName(name) )
		return SEE_UNKN_ERR;
	CShemeExpr *se;
	try
	{
		se = new CShemeExpr( expr, this );
	}
	catch( bad_alloc& )
	{
		se = NULL;
		return SEE_NOMEM;
	}
	ShemeExprErr er = se->GetCompileErrorCode();
	if( flg && (er != SEE_NOERR) )
		return er;
	ShemeVarsPair pr = m_VarsTable.insert( MakeShemeVar(name,se) );
	ASSERT( pr.second == true );
	return SEE_NOERR;
}

ShemeExprErr CShemeVarsTable::ResetVar( std::string &name, const std::string &expr )
{
	MakeLower(name);
	ShemeVarsTable::iterator it = m_VarsTable.find(name);
	if( it == m_VarsTable.end() )
	{
		return SEE_WRONG_SIMBOL;
	}
	return (*it).second->Reset(expr);
}

bool CShemeVarsTable::DelVar( const std::string &str )
{
	string name(str);
	MakeLower(name);
	ShemeVarsTable::iterator it = m_VarsTable.find(name);
	if( it == m_VarsTable.end() )
	{
		return false;
	}
	delete (*it).second;
	m_VarsTable.erase( it );
	return true;
}

void CShemeVarsTable::Serialize( CArchive &ar )
{
//	ShemeVersion sv = static_cast<ShemeVersion>(_sv);
	if (ar.IsStoring())
	{	// storing code
		vector<pair<CString,CString> > vec;
		ShemeVarsTable::iterator it = m_VarsTable.begin(), fin = m_VarsTable.end();
		int c = 0;//число переменных
		for(; it != fin; ++it )
		{
			string name = (*it).first;
			if( !CShemeVarsTable::IsReservedVarName(name) )
			{
				CString strName(name.c_str()), strExpr((*it).second->GetExpr().c_str());
				vec.push_back( make_pair(strName,strExpr) );
				c++;
			}
		}
		ar << c;
		for( int i = 0; i < c; i++ )
			ar << vec[i].first << vec[i].second;
	}
	else
	{	// loading code
		int c = 0;
		ar >> c;
		for( int i = 0; i < c; i++ )
		{
			CString strName, strExpr;
			ar >> strName >> strExpr;
			AddVar( string(static_cast<LPCTSTR>(strName)),
				string(static_cast<LPCTSTR>(strExpr)), false );
		}
		UpdateTable();
	}
}

void CShemeVarsTable::UpdateTable()
{
	ShemeVarsTable::iterator it = m_VarsTable.begin(), fin = m_VarsTable.end();
	for(; it != fin; ++it )
	{
		string name = (*it).first;
		if( !CShemeVarsTable::IsReservedVarName(name) )
		{
			(*it).second->Reset( (*it).second->GetExpr(), this );
		}
	}
}
