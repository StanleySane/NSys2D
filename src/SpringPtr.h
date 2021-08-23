// SpringPtr.h: interface for the SpringPtr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRINGPTR_H__6F6FDCC4_531C_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_SPRINGPTR_H__6F6FDCC4_531C_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include<map>
#include<string>

class CSpring;
class KnotPtr;
class AlgolMatr;
class CElem;

class SpringPtr
{
	CSpring *m_pElem;

	bool Construct( KnotPtr*, KnotPtr* );
	void Destruct();
	void InitBy( const SpringPtr& );
public:
	typedef std::map<CSpring*,int> Refs;
	typedef Refs::value_type MakeRef;
	typedef std::pair<Refs::iterator,bool> Pair;
	static Refs m_RefMap;

	SpringPtr& operator = ( const SpringPtr &v )
	{
		if( this != &v )
			InitBy(v);
		return *this;
	}
	SpringPtr( const SpringPtr &v ):m_pElem(NULL)
	{
		InitBy(v);
	}
	SpringPtr():m_pElem(NULL)
	{}
	~SpringPtr()
	{	Destruct();	}

	//ф-ции-члены
	CElem* GetElem() const;
	bool Create( KnotPtr*, KnotPtr* );
	bool Attach( CElem* );
	bool Detach();
	int GetRefCount();

	double GetLength() const;
	AlgolMatr GetMatrM() const;
	AlgolMatr GetMatrD() const;
	AlgolMatr GetMatrC() const;
};

typedef std::map<std::string,SpringPtr> VarSpring;
typedef VarSpring::value_type MakeSpring;

#endif // !defined(AFX_SPRINGPTR_H__6F6FDCC4_531C_11D6_B89D_FE2BA355A53D__INCLUDED_)
