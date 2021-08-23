// MatrPtr.h: interface for the MatrPtr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRPTR_H__ABD44843_50BF_11D6_B89D_FE2BA355A53D__INCLUDED_)
#define AFX_MATRPTR_H__ABD44843_50BF_11D6_B89D_FE2BA355A53D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include"ScriptDefs.h"

class AlgolMatr;
class Value;

class MatrPtr
{
	AlgolMatr *m_pMatr;

	void Destruct();
	void InitBy( const MatrPtr& );
public:
	typedef std::map<AlgolMatr*,int> Refs;
	typedef Refs::value_type MakeMatrRef;
	typedef std::pair<Refs::iterator,bool> Pair;
	static Refs m_MatrRefMap;

	MatrPtr& operator = ( const MatrPtr &v )
	{
		if( this != &v )
		{
			InitBy(v);
		}
		return *this;
	}
	MatrPtr( const MatrPtr &v ):m_pMatr(NULL)
	{
		InitBy(v);
	}
	MatrPtr():m_pMatr(NULL)
	{}
	MatrPtr( const AlgolMatr& );
	~MatrPtr()
	{	Destruct();	}

	//ф-ции-члены
	AlgolMatr* GetMatr() const;
	errorsT Construct( int r, int c );
	bool Resize( int, int );
	bool SetAt( int, int, const Value& );
	bool GetAt( int, int, Value& );
};

typedef std::map<std::string,MatrPtr> VarMatr;
typedef VarMatr::value_type MakeMatr;

#endif // !defined(AFX_MATRPTR_H__ABD44843_50BF_11D6_B89D_FE2BA355A53D__INCLUDED_)
