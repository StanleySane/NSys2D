// HardRodPtr.h: interface for the HardRodPtr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HARDRODPTR_H__6F6FDCC3_531C_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_HARDRODPTR_H__6F6FDCC3_531C_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include<map>
#include<string>

class CHardRod;
class KnotPtr;
class AlgolMatr;

class HardRodPtr
{
	CHardRod *m_pElem;

	bool Construct( KnotPtr*, KnotPtr* );
	void Destruct();
	void InitBy( const HardRodPtr& );
public:
	typedef std::map<CHardRod*,int> Refs;
	typedef Refs::value_type MakeRef;
	typedef std::pair<Refs::iterator,bool> Pair;
	static Refs m_RefMap;

	HardRodPtr& operator = ( const HardRodPtr &v )
	{
		if( this != &v )
			InitBy(v);
		return *this;
	}
	HardRodPtr( const HardRodPtr &v ):m_pElem(NULL)
	{
		InitBy(v);
	}
	HardRodPtr():m_pElem(NULL)
	{}
	~HardRodPtr()
	{	Destruct();	}

	//ф-ции-члены
	CHardRod* GetElem() const;
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

typedef std::map<std::string,HardRodPtr> VarHardRod;
typedef VarHardRod::value_type MakeHardRod;

#endif // !defined(AFX_HARDRODPTR_H__6F6FDCC3_531C_11D6_B89D_FE2BA355A53D__INCLUDED_)
