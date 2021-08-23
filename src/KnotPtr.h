// KnotPtr.h: interface for the KnotPtr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KNOTPTR_H__6F6FDCC7_531C_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_KNOTPTR_H__6F6FDCC7_531C_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include<map>
#include<string>

class CKnot;

class KnotPtr
{
	CKnot *m_pKnot;

	bool Construct();
	void Destruct();
	void InitBy( const KnotPtr& );
public:
	typedef std::map<CKnot*,int> Refs;
	typedef Refs::value_type MakeRef;
	typedef std::pair<Refs::iterator,bool> Pair;
	static Refs m_RefMap;

	KnotPtr& operator = ( const KnotPtr &v )
	{
		if( this != &v )
			InitBy(v);
		return *this;
	}
	KnotPtr( const KnotPtr &v ):m_pKnot(NULL)
	{
		InitBy(v);
	}
	KnotPtr():m_pKnot(NULL)
	{}
	~KnotPtr()
	{	Destruct();	}

	//ф-ции-члены
	CKnot* GetKnot() const;
	bool Attach( CKnot* );
	bool Detach();
	bool Create( double, double );
	static bool AddRef( CKnot* );
	static bool RemoveRef( CKnot* );
};

typedef std::map<std::string,KnotPtr> VarKnot;
typedef VarKnot::value_type MakeKnot;

#endif // !defined(AFX_KNOTPTR_H__6F6FDCC7_531C_11D6_B89D_FE2BA355A53D__INCLUDED_)
