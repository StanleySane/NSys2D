/////////////////////////////////////////////////////////////////
//	file ValueHeader.h
/////////////////////////////////////////////////////////////////

#ifndef _VALUE_HEADER_H_
#define _VALUE_HEADER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include"ScriptDefs.h"
#include<list>

class Array;
class File;
class ScriptPtr;
class AlgolMatr;
class MatrPtr;
class RodPtr;
class HardRodPtr;
class SpringPtr;
class DemferPtr;
class MassPtr;
class KnotPtr;
class ShemePtr;

class Value
{
	///////////////////////////////////////////
	//все типы, которые могут возвращать ф-ции:
	union
	{
		double m_vDouble;
		int m_vInt;
		bool m_vBool;
		std::string *m_pString;
		Array *m_pArray;
		File *m_pFile;
		ScriptPtr *m_pScript;
		MatrPtr *m_pMatr;
		RodPtr *m_pRod;
		HardRodPtr *m_pHardRod;
		SpringPtr *m_pSpring;
		DemferPtr *m_pDemfer;
		MassPtr *m_pMass;
		KnotPtr *m_pKnot;
		ShemePtr *m_pSheme;
	};
	TypeID m_tType;//используемый в данный момент тип
	///////////////////////////////////////////

	void InitBy( const Value& );
	void Destruct();
public:

	Value& operator = ( const Value &v )
	{
		if( this == &v )	return *this;
		InitBy(v);
		return *this;
	}
	Value( const Value &v ):m_vDouble(0.0), m_tType(TYPE_UNKNOWN)
	{
		InitBy(v);
	}
	Value():m_vDouble(0.0), m_tType(TYPE_UNKNOWN)
	{}
	~Value()
	{	Destruct();	}

	//ф-ции-члены
	TypeID Type() const
	{	return m_tType;	}
	bool SetType( TypeID );

	void SetBool( bool );
	void SetInt( int );
	void SetDouble( double );
	void SetString( const std::string& );
	void SetArray( const Array& );
	void SetFile( const File& );
	void SetScript( const ScriptPtr& );
	void SetMatr( const MatrPtr& );
	void SetMatr( const AlgolMatr& );
	void SetRod( const RodPtr& );
	void SetHardRod( const HardRodPtr& );
	void SetSpring( const SpringPtr& );
	void SetDemfer( const DemferPtr& );
	void SetMass( const MassPtr& );
	void SetKnot( const KnotPtr& );
	void SetSheme( const ShemePtr& );

	bool GetBool() const;
	int GetInt() const;
	double GetDouble() const;
	std::string GetString() const;
	Array* GetArray() const;
	File* GetFile() const;
	ScriptPtr* GetScript() const;
	MatrPtr* GetMatr() const;
	RodPtr* GetRod() const;
	HardRodPtr* GetHardRod() const;
	SpringPtr* GetSpring() const;
	DemferPtr* GetDemfer() const;
	MassPtr* GetMass() const;
	KnotPtr* GetKnot() const;
	ShemePtr* GetSheme() const;

	bool ConvertTo( TypeID );
	errorsT Power( int );
	bool Negate();
	std::string StringVariant() const;

	friend const Value operator + ( const Value&, const Value& );
	friend const Value operator - ( const Value&, const Value& );
	friend const Value operator * ( const Value&, const Value& );
	friend const Value operator / ( const Value&, const Value& );

	friend bool operator < ( const Value&, const Value& );
	friend bool operator <= ( const Value&, const Value& );
	friend bool operator > ( const Value&, const Value& );
	friend bool operator >= ( const Value&, const Value& );
	friend bool operator == ( const Value&, const Value& );
	friend bool operator != ( const Value&, const Value& );
};

typedef std::list<std::pair<Value*,std::string*> > ValList;

#endif //_VALUE_HEADER_H_