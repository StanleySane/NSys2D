// ShemePtr.h: interface for the ShemePtr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHEMEPTR_H__23A84CC2_8F56_11D6_B89E_FE2BA355A53D__INCLUDED_)
#define AFX_SHEMEPTR_H__23A84CC2_8F56_11D6_B89E_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include<map>
#include<string>

class CSheme;
class AlgolMatr;
class CElem;
class CKnot;

class ShemePtr
{
	CSheme *m_pSheme;
	std::string m_strShemeName;

	bool Construct();
	void Destruct();
	void InitBy( const ShemePtr& );
public:
	typedef std::map<CSheme*,int> Refs;
	typedef Refs::value_type MakeRef;
	typedef std::pair<Refs::iterator,bool> Pair;
	static Refs m_RefMap;

	ShemePtr& operator = ( const ShemePtr &v )
	{
		if( this != &v )
			InitBy(v);
		return *this;
	}
	ShemePtr( const ShemePtr &v ):m_pSheme(NULL)
	{
		InitBy(v);
	}
	ShemePtr():m_pSheme(NULL)
	{}
	~ShemePtr()
	{	Destruct();	}

	static bool AddRef( CSheme* );
	static bool RemoveRef( CSheme* );
	//ф-ции-члены
	std::string GetName() const;
//	CSheme* GetSheme() const;
	bool Open( const std::string& );
	bool Close();
	bool Save();
	bool SaveAs( const std::string& );
	bool SetEVMethod( int );
	bool GetEigen( AlgolMatr&, AlgolMatr& );
	bool SetParamIntegr( int, double, double );
	bool Integrate();
	bool GetResY1( AlgolMatr& );
	bool GetResY2( AlgolMatr& );
	bool GetResY3( AlgolMatr& );
	bool GetMatrMDC( AlgolMatr&, AlgolMatr&, AlgolMatr& );
	CElem* GetElemByNum( int );
	CKnot* GetKnotByNum( int );
	bool DelElem( CElem* );
	bool AddElement( CElem* );
};

typedef std::map<std::string,ShemePtr> VarSheme;
typedef VarSheme::value_type MakeSheme;

#endif // !defined(AFX_SHEMEPTR_H__23A84CC2_8F56_11D6_B89E_FE2BA355A53D__INCLUDED_)
