// MassPtr.h: interface for the MassPtr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MASSPTR_H__6F6FDCC6_531C_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_MASSPTR_H__6F6FDCC6_531C_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include<map>
#include<string>

class CMass;
class KnotPtr;
class AlgolMatr;
class CElem;

class MassPtr
{
	CMass *m_pElem;

	bool Construct( KnotPtr* );
	void Destruct();
	void InitBy( const MassPtr& );
public:
	typedef std::map<CMass*,int> Refs;
	typedef Refs::value_type MakeRef;
	typedef std::pair<Refs::iterator,bool> Pair;
	static Refs m_RefMap;

	MassPtr& operator = ( const MassPtr &v )
	{
		if( this != &v )
			InitBy(v);
		return *this;
	}
	MassPtr( const MassPtr &v ):m_pElem(NULL)
	{
		InitBy(v);
	}
	MassPtr():m_pElem(NULL)
	{}
	~MassPtr()
	{	Destruct();	}

	//ф-ции-члены
	CElem* GetElem() const;
	bool Create( KnotPtr* );
	bool Attach( CElem* );
	bool Detach();
	int GetRefCount();

	bool SetM( double );
	bool SetJ( double );
	double GetM() const;
	double GetJ() const;
	AlgolMatr GetMatrM() const;
	AlgolMatr GetMatrD() const;
	AlgolMatr GetMatrC() const;
};

typedef std::map<std::string,MassPtr> VarMass;
typedef VarMass::value_type MakeMass;

#endif // !defined(AFX_MASSPTR_H__6F6FDCC6_531C_11D6_B89D_FE2BA355A53D__INCLUDED_)
