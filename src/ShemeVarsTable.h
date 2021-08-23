// ShemeVarsTable.h: interface for the CShemeVarsTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHEMEVARSTABLE_H__0C943222_936F_11D6_B89E_FE2BA355A53D__INCLUDED_)
#define AFX_SHEMEVARSTABLE_H__0C943222_936F_11D6_B89E_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ShemeExpr.h"

class CShemeVarsTable  
{
	ShemeVarsTable m_VarsTable;
	std::list<std::string> m_lstActiveNames;

	void AddInternalVar( std::string&, double );

	CShemeVarsTable( const CShemeVarsTable& );
	CShemeVarsTable& operator=( const CShemeVarsTable& );
public:
	CShemeVarsTable();
	~CShemeVarsTable();

	void Serialize( CArchive& );

	ShemeVarsTable* GetVarsTable()
	{	return &m_VarsTable;	}
	double GetVarValue( const std::string&, ShemeExprErr& );
	bool SetVarValue( const std::string&, double );
	bool IsVarName( const std::string& );
	ShemeExprErr IsValidExpr( const std::string&, std::string& );
	bool IsValidExpr( const CString&, CString& );

	bool DelVar( const std::string& );
	ShemeExprErr AddVar( std::string&, const std::string&, bool flg = true );
	ShemeExprErr ResetVar( std::string&, const std::string& );
	ShemeExprErr GetCompileErrorCode( const std::string& );
	std::string GetErrorCause( const std::string& );
	void UpdateTable();
	
	static bool IsValidVarName( const std::string& );
	static bool IsReservedVarName( const std::string& );
	static bool IsValidateParam( const std::string& );

};

#endif // !defined(AFX_SHEMEVARSTABLE_H__0C943222_936F_11D6_B89E_FE2BA355A53D__INCLUDED_)
