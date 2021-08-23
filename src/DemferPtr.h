// DemferPtr.h: interface for the DemferPtr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMFERPTR_H__6F6FDCC5_531C_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_DEMFERPTR_H__6F6FDCC5_531C_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include<map>
#include<string>

class CDemf;
class KnotPtr;
class AlgolMatr;
class CElem;

class DemferPtr
{
	CDemf *m_pElem;

	bool Construct( KnotPtr*, KnotPtr* );
	void Destruct();
	void InitBy( const DemferPtr& );
public:
	typedef std::map<CDemf*,int> Refs;
	typedef Refs::value_type MakeRef;
	typedef std::pair<Refs::iterator,bool> Pair;
	static Refs m_RefMap;

	DemferPtr& operator = ( const DemferPtr &v )
	{
		if( this != &v )
			InitBy(v);
		return *this;
	}
	DemferPtr( const DemferPtr &v ):m_pElem(NULL)
	{
		InitBy(v);
	}
	DemferPtr():m_pElem(NULL)
	{}
	~DemferPtr()
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

typedef std::map<std::string,DemferPtr> VarDemf;
typedef VarDemf::value_type MakeDemf;

#endif // !defined(AFX_DEMFERPTR_H__6F6FDCC5_531C_11D6_B89D_FE2BA355A53D__INCLUDED_)
