// RodPtr.h: interface for the RodPtr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RODPTR_H__6F6FDCC2_531C_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_RODPTR_H__6F6FDCC2_531C_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include<map>
#include<string>

class CRod;
class KnotPtr;
class AlgolMatr;

class RodPtr
{
	CRod *m_pElem;

	bool Construct( KnotPtr*, KnotPtr* );
	void Destruct();
	void InitBy( const RodPtr& );
public:
	typedef std::map<CRod*,int> Refs;
	typedef Refs::value_type MakeRef;
	typedef std::pair<Refs::iterator,bool> Pair;
	static Refs m_RefMap;

	RodPtr& operator = ( const RodPtr &v )
	{
		if( this != &v )
			InitBy(v);
		return *this;
	}
	RodPtr( const RodPtr &v ):m_pElem(NULL)
	{
		InitBy(v);
	}
	RodPtr():m_pElem(NULL)
	{}
	~RodPtr()
	{	Destruct();	}

	//ф-ции-члены
	CRod* GetElem() const;
	bool Create( KnotPtr*, KnotPtr* );
	bool SetM( double );
	bool SetJ( double );
	bool SetF( double );
	bool SetE( double );
	double GetM() const;
	double GetJ() const;
	double GetF() const;
	double GetE() const;

	double GetLength() const;
	AlgolMatr GetMatrM() const;
	AlgolMatr GetMatrD() const;
	AlgolMatr GetMatrC() const;
};

typedef std::map<std::string,RodPtr> VarRod;
typedef VarRod::value_type MakeRod;

#endif // !defined(AFX_RODPTR_H__6F6FDCC2_531C_11D6_B89D_FE2BA355A53D__INCLUDED_)
