// ValueSource.cpp: implementation of the Value class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"

#include"FileHeader.h"
#include"ScriptPtrHeader.h"
#include"ArrayHeader.h"
#include"ValueHeader.h"
#include"AlgolMatr.h"
#include"MatrPtr.h"
#include"RodPtr.h"
#include"HardRodPtr.h"
#include"SpringPtr.h"
#include"DemferPtr.h"
#include"MassPtr.h"
#include"KnotPtr.h"
//#include"ShemePtr.h"

#include<cmath>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////
void Value::Destruct()
{
	switch( m_tType )
	{
	case TYPE_STRING:
		delete m_pString;
		break;
	case TYPE_FILE:
		delete m_pFile;
		break;
	case TYPE_SCRIPT:
		delete m_pScript;
		break;
	case TYPE_MATR:
		delete m_pMatr;
		break;
	case TYPE_ROD:
		delete m_pRod;
		break;
	case TYPE_HARDROD:
		delete m_pHardRod;
		break;
	case TYPE_SPRING:
		delete m_pSpring;
		break;
	case TYPE_DEMFER:
		delete m_pDemfer;
		break;
	case TYPE_MASS:
		delete m_pMass;
		break;
	case TYPE_KNOT:
		delete m_pKnot;
		break;
//	case TYPE_SHEME:
//		delete m_pSheme;
//		break;
	default:
		if( Array::IsArray(m_tType) )
			delete m_pArray;
		break;
	}
	m_tType = TYPE_UNKNOWN;
	m_vDouble = 0.0;
}

void Value::SetBool( bool v )
{
	if( m_tType != TYPE_BOOL )
		Destruct();
	m_tType = TYPE_BOOL;
	m_vBool = v;
}

void Value::SetInt( int v )
{
	if( m_tType != TYPE_INT )
		Destruct();
	m_tType = TYPE_INT;
	m_vInt = v;
}

void Value::SetDouble( double v )
{
	if( m_tType != TYPE_DOUBLE )
		Destruct();
	m_tType = TYPE_DOUBLE;
	m_vDouble = v;
}

void Value::SetString( const std::string &v )
{
	if( m_tType != TYPE_STRING )
	{
		Destruct();
		m_tType = TYPE_STRING;
		try
		{
			m_pString = new string(v);
		}
		catch( bad_alloc& )
		{
			m_pString = NULL;
			m_tType = TYPE_UNKNOWN;
		}
	}
	else
	{
		*m_pString = v;
	}
}

void Value::SetArray( const Array &v )
{
	if( !Array::IsArray(m_tType) )
	{
		Destruct();
		ASSERT( v.GetType() != TYPE_UNKNOWN );
		m_tType = v.GetType();
		try
		{
			m_pArray = new Array(v);
		}
		catch( bad_alloc& )
		{
			m_pArray = NULL;
			m_tType = TYPE_UNKNOWN;
		}
	}
	else
	{
		*m_pArray = v;
	}
}

void Value::SetFile( const File &v )
{
	if( m_tType != TYPE_FILE )
	{
		Destruct();
		m_tType = TYPE_FILE;
		try
		{
			m_pFile = new File(v);
		}
		catch( bad_alloc& )
		{
			m_pFile = NULL;
			m_tType = TYPE_UNKNOWN;
		}
	}
	else
	{
		*m_pFile = v;
	}
}

void Value::SetScript( const ScriptPtr &v )
{
	if( m_tType != TYPE_SCRIPT )
	{
		Destruct();
		m_tType = TYPE_SCRIPT;
		try
		{
			m_pScript = new ScriptPtr(v);
		}
		catch( bad_alloc& )
		{
			m_pScript = NULL;
			m_tType = TYPE_UNKNOWN;
		}
	}
	else
	{
		*m_pScript = v;
	}
}

void Value::SetMatr( const MatrPtr &v )
{
	if( m_tType != TYPE_MATR )
	{
		Destruct();
		m_tType = TYPE_MATR;
		try
		{
			m_pMatr = new MatrPtr(v);
		}
		catch( bad_alloc& )
		{
			m_pMatr = NULL;
			m_tType = TYPE_UNKNOWN;
		}
	}
	else
	{
		*m_pMatr = v;
	}
}

void Value::SetMatr( const AlgolMatr &v )
{
	if( m_tType != TYPE_MATR )
	{
		Destruct();
		m_tType = TYPE_MATR;
		try
		{
			m_pMatr = new MatrPtr(v);
		}
		catch( bad_alloc& )
		{
			m_pMatr = NULL;
			m_tType = TYPE_UNKNOWN;
		}
	}
	else
	{
		*m_pMatr = MatrPtr(v);
	}
}

void Value::SetRod( const RodPtr &v )
{
	if( m_tType != TYPE_ROD )
	{
		Destruct();
		m_tType = TYPE_ROD;
		try
		{
			m_pRod = new RodPtr(v);
		}
		catch( bad_alloc& )
		{
			m_pRod = NULL;
			m_tType = TYPE_UNKNOWN;
		}
	}
	else
	{
		*m_pRod = v;
	}
}

void Value::SetHardRod( const HardRodPtr &v )
{
	if( m_tType != TYPE_HARDROD )
	{
		Destruct();
		m_tType = TYPE_HARDROD;
		try
		{
			m_pHardRod = new HardRodPtr(v);
		}
		catch( bad_alloc& )
		{
			m_pHardRod = NULL;
			m_tType = TYPE_UNKNOWN;
		}
	}
	else
	{
		*m_pHardRod = v;
	}
}

void Value::SetSpring( const SpringPtr &v )
{
	if( m_tType != TYPE_SPRING )
	{
		Destruct();
		m_tType = TYPE_SPRING;
		try
		{
			m_pSpring = new SpringPtr(v);
		}
		catch( bad_alloc& )
		{
			m_pSpring = NULL;
			m_tType = TYPE_UNKNOWN;
		}
	}
	else
	{
		*m_pSpring = v;
	}
}

void Value::SetDemfer( const DemferPtr &v )
{
	if( m_tType != TYPE_DEMFER )
	{
		Destruct();
		m_tType = TYPE_DEMFER;
		try
		{
			m_pDemfer = new DemferPtr(v);
		}
		catch( bad_alloc& )
		{
			m_pDemfer = NULL;
			m_tType = TYPE_UNKNOWN;
		}
	}
	else
	{
		*m_pDemfer = v;
	}
}

void Value::SetMass( const MassPtr &v )
{
	if( m_tType != TYPE_MASS )
	{
		Destruct();
		m_tType = TYPE_MASS;
		try
		{
			m_pMass = new MassPtr(v);
		}
		catch( bad_alloc& )
		{
			m_pMass = NULL;
			m_tType = TYPE_UNKNOWN;
		}
	}
	else
	{
		*m_pMass = v;
	}
}

void Value::SetKnot( const KnotPtr &v )
{
	if( m_tType != TYPE_KNOT )
	{
		Destruct();
		m_tType = TYPE_KNOT;
		try
		{
			m_pKnot = new KnotPtr(v);
		}
		catch( bad_alloc& )
		{
			m_pKnot = NULL;
			m_tType = TYPE_UNKNOWN;
		}
	}
	else
	{
		*m_pKnot = v;
	}
}

bool Value::GetBool() const
{
	ASSERT( m_tType == TYPE_BOOL );
	return m_vBool;
}

int Value::GetInt() const
{
	ASSERT( m_tType == TYPE_INT );
	return m_vInt;
}

double Value::GetDouble() const
{
	ASSERT( m_tType == TYPE_DOUBLE );
	return m_vDouble;
}

std::string Value::GetString() const
{
	ASSERT( m_tType == TYPE_STRING );
	return *m_pString;
}

Array* Value::GetArray() const
{
	ASSERT( Array::IsArray(m_tType) );
	return m_pArray;
}

File* Value::GetFile() const
{
	ASSERT( m_tType == TYPE_FILE );
	return m_pFile;
}

ScriptPtr* Value::GetScript() const
{
	ASSERT( m_tType == TYPE_SCRIPT );
	return m_pScript;
}

MatrPtr* Value::GetMatr() const
{
	ASSERT( m_tType == TYPE_MATR );
	return m_pMatr;
}

RodPtr* Value::GetRod() const
{
	ASSERT( m_tType == TYPE_ROD );
	return m_pRod;
}

HardRodPtr* Value::GetHardRod() const
{
	ASSERT( m_tType == TYPE_HARDROD );
	return m_pHardRod;
}

SpringPtr* Value::GetSpring() const
{
	ASSERT( m_tType == TYPE_SPRING );
	return m_pSpring;
}

DemferPtr* Value::GetDemfer() const
{
	ASSERT( m_tType == TYPE_DEMFER );
	return m_pDemfer;
}

MassPtr* Value::GetMass() const
{
	ASSERT( m_tType == TYPE_MASS );
	return m_pMass;
}

KnotPtr* Value::GetKnot() const
{
	ASSERT( m_tType == TYPE_KNOT );
	return m_pKnot;
}

void Value::InitBy( const Value &v )
{
	switch( v.m_tType )
	{
	case TYPE_INT:
		SetInt( v.m_vInt );
		break;
	case TYPE_BOOL:
		SetBool( v.m_vBool );
		break;
	case TYPE_DOUBLE:
		SetDouble( v.m_vDouble );
		break;
	case TYPE_STRING:
		SetString( *v.m_pString );
		break;
	case TYPE_FILE:
		SetFile( *v.m_pFile );
		break;
	case TYPE_SCRIPT:
		SetScript( *v.m_pScript );
		break;
	case TYPE_MATR:
		SetMatr( *v.m_pMatr );
		break;
	case TYPE_ROD:
		SetRod( *v.m_pRod );
		break;
	case TYPE_HARDROD:
		SetHardRod( *v.m_pHardRod );
		break;
	case TYPE_SPRING:
		SetSpring( *v.m_pSpring );
		break;
	case TYPE_DEMFER:
		SetDemfer( *v.m_pDemfer );
		break;
	case TYPE_MASS:
		SetMass( *v.m_pMass );
		break;
	case TYPE_KNOT:
		SetKnot( *v.m_pKnot );
		break;
	default:
		if( Array::IsArray(v.m_tType) )
			SetArray( *v.m_pArray );
		else
			ASSERT(FALSE);
	}
}

bool Value::SetType( TypeID t )
{
	switch( t )
	{
	case TYPE_INT:
		SetInt( 0 );
		break;
	case TYPE_BOOL:
		SetBool( false );
		break;
	case TYPE_DOUBLE:
		SetDouble( 0.0 );
		break;
	case TYPE_STRING:
		SetString( string() );
		break;
	case TYPE_FILE:
		SetFile( File() );
		break;
	case TYPE_SCRIPT:
		SetScript( ScriptPtr() );
		break;
	case TYPE_MATR:
		SetMatr( MatrPtr() );
		break;
	case TYPE_ROD:
		SetRod( RodPtr() );
		break;
	case TYPE_HARDROD:
		SetHardRod( HardRodPtr() );
		break;
	case TYPE_SPRING:
		SetSpring( SpringPtr() );
		break;
	case TYPE_DEMFER:
		SetDemfer( DemferPtr() );
		break;
	case TYPE_MASS:
		SetMass( MassPtr() );
		break;
	case TYPE_KNOT:
		SetKnot( KnotPtr() );
		break;
	case TYPE_UNKNOWN:
		Destruct();
		return true;
		break;
	default:
		if( Array::IsArray(t) )
			SetArray( Array() );
		else
			ASSERT(FALSE);
	}
	if( m_tType == t )
		return true;
	return false;
}

std::string Value::StringVariant() const
{
//ф-ция возвращает значение переменной в виде строки.
	string str;
	switch( m_tType )
	{
	case TYPE_INT:
		{
			str = FormatString("%d", m_vInt );
		}
		break;
	case TYPE_BOOL:
		if( m_vBool )	str = "TRUE";
		else	str = "FALSE";
		break;
	case TYPE_DOUBLE:
		{
			str = FormatString("%.11lf", m_vDouble );
		}
		break;
	case TYPE_STRING:
		str = *m_pString;
		break;
	case TYPE_ARRAY_INT:
	case TYPE_ARRAY_BOOL:
	case TYPE_ARRAY_DOUBLE:
	case TYPE_ARRAY_STRING:
		{
			Value tmp;
			int s = m_pArray->Size();
			for( int i = 0; i < s; i++ )
			{
				bool res = m_pArray->GetAt( i, tmp );
				ASSERT( res == true );
				str += tmp.StringVariant();
				str += " ";
			}
		}
		break;
	case TYPE_FILE:
		str = m_pFile->GetName();
		break;
	case TYPE_SCRIPT:
		str = m_pScript->GetScriptText();
		break;
	case TYPE_MATR:
		{
			int row = m_pMatr->GetMatr()->GetRow(), col = m_pMatr->GetMatr()->GetWidth();
			for( int r = 1; r <= row; r++ )
			{
				for( int c = 0; c < col; c++ )
				{
					str += FormatString("%e ", m_pMatr->GetMatr()->GetAt( r, c ) );
				}
				str += "\r\n";
			}
		}
		break;
	case TYPE_ROD:
		str = string("ELEMENT-ROD");
		break;
	case TYPE_HARDROD:
		str = string("ELEMENT-HARDROD");
		break;
	case TYPE_SPRING:
		str = string("ELEMENT-SPRING");
		break;
	case TYPE_DEMFER:
		str = string("ELEMENT-DEMFER");
		break;
	case TYPE_MASS:
		str = string("ELEMENT-MASS");
		break;
	case TYPE_KNOT:
		str = string("ELEMENT-KNOT");
		break;
//	case TYPE_SHEME:
	default:
		ASSERT(FALSE);
	}//switch
	return str;
}

bool Value::Negate()
{
	if( (m_tType != TYPE_INT)&&(m_tType != TYPE_DOUBLE)&&(m_tType != TYPE_MATR) )
		return false;
	switch( m_tType )
	{
	case TYPE_INT:
		m_vInt = -m_vInt;
		break;
	case TYPE_DOUBLE:
		m_vDouble = -m_vDouble;
		break;
	case TYPE_MATR:
		m_pMatr->GetMatr()->Negate();
		break;
	}
	return true;
}

bool Value::ConvertTo( TypeID t )
{
//привести переменную от типа m_tType к типу t.
	if( m_tType == t )	return true;
	switch( m_tType )
	{
	case TYPE_INT:
		{
			switch(t)
			{
			case TYPE_BOOL:
				{
					bool b = (m_vInt)?true:false;
					SetBool(b);
				}
				break;
			case TYPE_STRING:
				{
					//int->string
					SetString( FormatString("%d", m_vInt ) );
				}
				break;
			case TYPE_DOUBLE:
				{
					//int->double
					double d = static_cast<double>(m_vInt);
					SetDouble( d );
				}
				break;
			case TYPE_MATR:
				{
					//int->matr
					MatrPtr mp;
					mp.Construct( 1, 1 );
					mp.GetMatr()->GetAt( 0, 0 ) = static_cast<double>(m_vInt);
					SetMatr( mp );
				}
				break;
			default:
				return false;
			}//switch(t)
		}
		break;
	case TYPE_BOOL:
		{
			switch(t)
			{
			case TYPE_INT:
				{
					int i = (m_vBool)?1:0;
					SetInt(i);
				}
				break;
			case TYPE_STRING:
				{
					//bool->string
					if( m_vBool )
						SetString("TRUE");
					else
						SetString("FALSE");
				}
				break;
			case TYPE_DOUBLE:
				{
					double d = (m_vBool)?1.0:0.0;
					SetDouble(d);
				}
				break;
			case TYPE_MATR:
				{
					//bool->matr
					MatrPtr mp;
					mp.Construct( 1, 1 );
					mp.GetMatr()->GetAt( 0, 0 ) = static_cast<double>((m_vBool)?1:0);
					SetMatr( mp );
				}
				break;
			default:
				return false;
			}//switch(t)
		}
		break;
	case TYPE_DOUBLE:
		{
			switch(t)
			{
			case TYPE_BOOL:
				{
					bool b = (fabs(m_vDouble) > DOUBLE_ZERO)?true:false;
					SetBool(b);
				}
				break;
			case TYPE_STRING:
				{
					//double->string
					SetString( FormatString("%.21lf", m_vDouble ) );
				}
				break;
			case TYPE_INT:
				{
					//t==int
					int i = static_cast<int>(m_vDouble);
					SetInt(i);
				}
				break;
			case TYPE_MATR:
				{
					//double->matr
					MatrPtr mp;
					mp.Construct( 1, 1 );
					mp.GetMatr()->GetAt( 0, 0 ) = static_cast<double>(m_vDouble);
					SetMatr( mp );
				}
				break;
			default:
				return false;
			}//switch(t)
		}
		break;
	case TYPE_STRING:
	case TYPE_ARRAY_INT:
	case TYPE_ARRAY_BOOL:
	case TYPE_ARRAY_DOUBLE:
	case TYPE_ARRAY_STRING:
	case TYPE_FILE:
	case TYPE_SCRIPT:
	case TYPE_MATR:
	case TYPE_ROD:
	case TYPE_HARDROD:
	case TYPE_SPRING:
	case TYPE_DEMFER:
	case TYPE_MASS:
	case TYPE_KNOT:
	case TYPE_SHEME:
		return false;
	default:
		ASSERT(FALSE);
		return false;
	}
	return true;
}

errorsT Value::Power( int p )
{
	//возведение в степень
	switch( m_tType )
	{
	case TYPE_INT:
		{
			if( (p < 0)&&(m_vInt == 0) )
				return FP_ERR;
			m_vInt = pow( m_vInt, p );
		}
		break;
	case TYPE_DOUBLE:
		{
			if( (p < 0)&&( fabs(m_vDouble) < DOUBLE_ZERO) )
				return FP_ERR;
			m_vDouble = pow( m_vDouble, p );
		}
		break;
	case TYPE_MATR:
		{
			m_pMatr->GetMatr()->Power(p);
		}
		break;
	default:
		return TYPE_OP_ERR;
	}
	return NOERR;
}

bool operator < ( const Value &res1, const Value &res2 )
{
//проверка на несовместные типы
	if( (res1.m_tType == TYPE_UNKNOWN)||(res2.m_tType == TYPE_UNKNOWN) )
		throw CONVERT_ERR;
	if( (res1.m_tType != TYPE_INT)&&(res1.m_tType != TYPE_DOUBLE)&&
		(res1.m_tType != TYPE_MATR)&&(res1.m_tType != TYPE_BOOL)&&
		(res1.m_tType != TYPE_STRING) )
		throw CONVERT_ERR;
	if( (res2.m_tType != TYPE_INT)&&(res2.m_tType != TYPE_DOUBLE)&&
		(res2.m_tType != TYPE_MATR)&&(res2.m_tType != TYPE_BOOL)&&
		(res2.m_tType != TYPE_STRING) )
		throw CONVERT_ERR;

	bool res;
	if( res1.m_tType == res2.m_tType )
	{
		if( (res1.m_tType == TYPE_BOOL)||(res1.m_tType == TYPE_MATR) )
			throw TYPE_OP_ERR;
		
		switch(res1.m_tType)
		{
		case TYPE_INT:
			res = res1.m_vInt < res2.m_vInt;
			break;
		case TYPE_DOUBLE:
			res = res1.m_vDouble < res2.m_vDouble;
			break;		
		case TYPE_STRING:
			res = (*res1.m_pString) < (*res2.m_pString);
			break;		
		default:
			ASSERT(FALSE);
			break;
		}
	}
	else
	{
		//типы переменных разные
		//надо выбрать наиболее подходящий тип для рез-та
		if( res1.m_tType == TYPE_DOUBLE )
		{
			if( res2.m_tType == TYPE_INT )
			{
				res = res1.m_vDouble < (static_cast<double>(res2.m_vInt));
			}
			else
			{
				//res2.m_tType == matr || bool
				throw TYPE_OP_ERR;
			}
		}
		else
		{
			//значит res1.m_tType == int || matr || bool
			if( res1.m_tType == TYPE_INT )
			{
				if( res2.m_tType == TYPE_DOUBLE )
				{
					res = (static_cast<double>(res1.m_vInt)) < res2.m_vDouble;
				}
				else
				{
					throw TYPE_OP_ERR;
				}
			}
			else
			{
				throw TYPE_OP_ERR;
			}
		}
	}
	return res;
}

bool operator <= ( const Value &res1, const Value &res2 )
{
//проверка на несовместные типы
	if( (res1.m_tType == TYPE_UNKNOWN)||(res2.m_tType == TYPE_UNKNOWN) )
		throw CONVERT_ERR;
	if( (res1.m_tType != TYPE_INT)&&(res1.m_tType != TYPE_DOUBLE)&&
		(res1.m_tType != TYPE_MATR)&&(res1.m_tType != TYPE_BOOL)&&
		(res1.m_tType != TYPE_STRING) )
		throw CONVERT_ERR;
	if( (res2.m_tType != TYPE_INT)&&(res2.m_tType != TYPE_DOUBLE)&&
		(res2.m_tType != TYPE_MATR)&&(res2.m_tType != TYPE_BOOL)&&
		(res2.m_tType != TYPE_STRING) )
		throw CONVERT_ERR;

	bool res;
	if( res1.m_tType == res2.m_tType )
	{
		if( (res1.m_tType == TYPE_BOOL)||(res1.m_tType == TYPE_MATR) )
			throw TYPE_OP_ERR;
		
		switch(res1.m_tType)
		{
		case TYPE_INT:
			res = res1.m_vInt <= res2.m_vInt;
			break;
		case TYPE_DOUBLE:
			res = res1.m_vDouble <= res2.m_vDouble;
			break;		
		case TYPE_STRING:
			res = (*res1.m_pString) <= (*res2.m_pString);
			break;		
		default:
			ASSERT(FALSE);
			break;
		}
	}
	else
	{
		//типы переменных разные
		//надо выбрать наиболее подходящий тип для рез-та
		if( res1.m_tType == TYPE_DOUBLE )
		{
			if( res2.m_tType == TYPE_INT )
			{
				res = res1.m_vDouble <= (static_cast<double>(res2.m_vInt));
			}
			else
			{
				//res2.m_tType == matr || bool
				throw TYPE_OP_ERR;
			}
		}
		else
		{
			//значит res1.m_tType == int || matr || bool
			if( res1.m_tType == TYPE_INT )
			{
				if( res2.m_tType == TYPE_DOUBLE )
				{
					res = (static_cast<double>(res1.m_vInt)) <= res2.m_vDouble;
				}
				else
				{
					throw TYPE_OP_ERR;
				}
			}
			else
			{
				throw TYPE_OP_ERR;
			}
		}
	}
	return res;
}

bool operator > ( const Value &res1, const Value &res2 )
{
//проверка на несовместные типы
	if( (res1.m_tType == TYPE_UNKNOWN)||(res2.m_tType == TYPE_UNKNOWN) )
		throw CONVERT_ERR;
	if( (res1.m_tType != TYPE_INT)&&(res1.m_tType != TYPE_DOUBLE)&&
		(res1.m_tType != TYPE_MATR)&&(res1.m_tType != TYPE_BOOL)&&
		(res1.m_tType != TYPE_STRING) )
		throw CONVERT_ERR;
	if( (res2.m_tType != TYPE_INT)&&(res2.m_tType != TYPE_DOUBLE)&&
		(res2.m_tType != TYPE_MATR)&&(res2.m_tType != TYPE_BOOL)&&
		(res2.m_tType != TYPE_STRING) )
		throw CONVERT_ERR;

	bool res;
	if( res1.m_tType == res2.m_tType )
	{
		if( (res1.m_tType == TYPE_BOOL)||(res1.m_tType == TYPE_MATR) )
			throw TYPE_OP_ERR;
		
		switch(res1.m_tType)
		{
		case TYPE_INT:
			res = res1.m_vInt > res2.m_vInt;
			break;
		case TYPE_DOUBLE:
			res = res1.m_vDouble > res2.m_vDouble;
			break;		
		case TYPE_STRING:
			res = (*res1.m_pString) > (*res2.m_pString);
			break;		
		default:
			ASSERT(FALSE);
			break;
		}
	}
	else
	{
		//типы переменных разные
		//надо выбрать наиболее подходящий тип для рез-та
		if( res1.m_tType == TYPE_DOUBLE )
		{
			if( res2.m_tType == TYPE_INT )
			{
				res = res1.m_vDouble > (static_cast<double>(res2.m_vInt));
			}
			else
			{
				//res2.m_tType == matr || bool
				throw TYPE_OP_ERR;
			}
		}
		else
		{
			//значит res1.m_tType == int || matr || bool
			if( res1.m_tType == TYPE_INT )
			{
				if( res2.m_tType == TYPE_DOUBLE )
				{
					res = (static_cast<double>(res1.m_vInt)) > res2.m_vDouble;
				}
				else
				{
					throw TYPE_OP_ERR;
				}
			}
			else
			{
				throw TYPE_OP_ERR;
			}
		}
	}
	return res;
}

bool operator >= ( const Value &res1, const Value &res2 )
{
//проверка на несовместные типы
	if( (res1.m_tType == TYPE_UNKNOWN)||(res2.m_tType == TYPE_UNKNOWN) )
		throw CONVERT_ERR;
	if( (res1.m_tType != TYPE_INT)&&(res1.m_tType != TYPE_DOUBLE)&&
		(res1.m_tType != TYPE_MATR)&&(res1.m_tType != TYPE_BOOL)&&
		(res1.m_tType != TYPE_STRING) )
		throw CONVERT_ERR;
	if( (res2.m_tType != TYPE_INT)&&(res2.m_tType != TYPE_DOUBLE)&&
		(res2.m_tType != TYPE_MATR)&&(res2.m_tType != TYPE_BOOL)&&
		(res2.m_tType != TYPE_STRING) )
		throw CONVERT_ERR;

	bool res;
	if( res1.m_tType == res2.m_tType )
	{
		if( (res1.m_tType == TYPE_BOOL)||(res1.m_tType == TYPE_MATR) )
			throw TYPE_OP_ERR;
		
		switch(res1.m_tType)
		{
		case TYPE_INT:
			res = res1.m_vInt >= res2.m_vInt;
			break;
		case TYPE_DOUBLE:
			res = res1.m_vDouble >= res2.m_vDouble;
			break;		
		case TYPE_STRING:
			res = (*res1.m_pString) >= (*res2.m_pString);
			break;		
		default:
			ASSERT(FALSE);
			break;
		}
	}
	else
	{
		//типы переменных разные
		//надо выбрать наиболее подходящий тип для рез-та
		if( res1.m_tType == TYPE_DOUBLE )
		{
			if( res2.m_tType == TYPE_INT )
			{
				res = res1.m_vDouble >= (static_cast<double>(res2.m_vInt));
			}
			else
			{
				//res2.m_tType == matr || bool
				throw TYPE_OP_ERR;
			}
		}
		else
		{
			//значит res1.m_tType == int || matr || bool
			if( res1.m_tType == TYPE_INT )
			{
				if( res2.m_tType == TYPE_DOUBLE )
				{
					res = (static_cast<double>(res1.m_vInt)) >= res2.m_vDouble;
				}
				else
				{
					throw TYPE_OP_ERR;
				}
			}
			else
			{
				throw TYPE_OP_ERR;
			}
		}
	}
	return res;
}

bool operator == ( const Value &res1, const Value &res2 )
{
//проверка на несовместные типы
	if( (res1.m_tType == TYPE_UNKNOWN)||(res2.m_tType == TYPE_UNKNOWN) )
		throw CONVERT_ERR;
	if( (res1.m_tType != TYPE_INT)&&(res1.m_tType != TYPE_DOUBLE)&&
		(res1.m_tType != TYPE_MATR)&&(res1.m_tType != TYPE_BOOL)&&
		(res1.m_tType != TYPE_STRING) )
		throw CONVERT_ERR;
	if( (res2.m_tType != TYPE_INT)&&(res2.m_tType != TYPE_DOUBLE)&&
		(res2.m_tType != TYPE_MATR)&&(res2.m_tType != TYPE_BOOL)&&
		(res2.m_tType != TYPE_STRING) )
		throw CONVERT_ERR;

	bool res;
	if( res1.m_tType == res2.m_tType )
	{
		if( res1.m_tType == TYPE_MATR )
			throw TYPE_OP_ERR;
		
		switch(res1.m_tType)
		{
		case TYPE_INT:
			res = res1.m_vInt == res2.m_vInt;
			break;
		case TYPE_DOUBLE:
			res = fabs( res1.m_vDouble - res2.m_vDouble ) < DOUBLE_ZERO;
			break;
		case TYPE_BOOL:
			res = res1.m_vBool == res2.m_vBool;
			break;
		case TYPE_STRING:
			res = (*res1.m_pString) == (*res2.m_pString);
			break;		
		case TYPE_MATR:
			res = (*res1.m_pMatr->GetMatr()) == (*res2.m_pMatr->GetMatr());
			break;
		default:
			ASSERT(FALSE);
			break;
		}
	}
	else
	{
		//типы переменных разные
		//надо выбрать наиболее подходящий тип для рез-та
		if( res1.m_tType == TYPE_DOUBLE )
		{
			if( res2.m_tType == TYPE_INT )
			{
				res = fabs( res1.m_vDouble - (static_cast<double>(res2.m_vInt)) ) < DOUBLE_ZERO;
			}
			else
			{
				//res2.m_tType == matr || bool
				throw TYPE_OP_ERR;
			}
		}
		else
		{
			//значит res1.m_tType == int || matr || bool
			if( res1.m_tType == TYPE_INT )
			{
				if( res2.m_tType == TYPE_DOUBLE )
				{
					res = fabs( (static_cast<double>(res1.m_vInt)) - res2.m_vDouble ) < DOUBLE_ZERO;
				}
				else
				{
					throw TYPE_OP_ERR;
				}
			}
			else
			{
				throw TYPE_OP_ERR;
			}
		}
	}
	return res;
}

bool operator != ( const Value &res1, const Value &res2 )
{
//проверка на несовместные типы
	if( (res1.m_tType == TYPE_UNKNOWN)||(res2.m_tType == TYPE_UNKNOWN) )
		throw CONVERT_ERR;
	if( (res1.m_tType != TYPE_INT)&&(res1.m_tType != TYPE_DOUBLE)&&
		(res1.m_tType != TYPE_MATR)&&(res1.m_tType != TYPE_BOOL)&&
		(res1.m_tType != TYPE_STRING) )
		throw CONVERT_ERR;
	if( (res2.m_tType != TYPE_INT)&&(res2.m_tType != TYPE_DOUBLE)&&
		(res2.m_tType != TYPE_MATR)&&(res2.m_tType != TYPE_BOOL)&&
		(res2.m_tType != TYPE_STRING) )
		throw CONVERT_ERR;

	bool res;
	if( res1.m_tType == res2.m_tType )
	{
		if( res1.m_tType == TYPE_MATR )
			throw TYPE_OP_ERR;
		
		switch(res1.m_tType)
		{
		case TYPE_INT:
			res = res1.m_vInt != res2.m_vInt;
			break;
		case TYPE_DOUBLE:
			res = fabs( res1.m_vDouble - res2.m_vDouble ) > DOUBLE_ZERO;
			break;
		case TYPE_BOOL:
			res = res1.m_vBool != res2.m_vBool;
			break;
		case TYPE_STRING:
			res = (*res1.m_pString) != (*res2.m_pString);
			break;		
		case TYPE_MATR:
			res = (*res1.m_pMatr->GetMatr()) != (*res2.m_pMatr->GetMatr());
			break;
		default:
			ASSERT(FALSE);
			break;
		}
	}
	else
	{
		//типы переменных разные
		//надо выбрать наиболее подходящий тип для рез-та
		if( res1.m_tType == TYPE_DOUBLE )
		{
			if( res2.m_tType == TYPE_INT )
			{
				res = fabs( res1.m_vDouble - (static_cast<double>(res2.m_vInt)) ) > DOUBLE_ZERO;
			}
			else
			{
				//res2.m_tType == matr || bool
				throw TYPE_OP_ERR;
			}
		}
		else
		{
			//значит res1.m_tType == int || matr || bool
			if( res1.m_tType == TYPE_INT )
			{
				if( res2.m_tType == TYPE_DOUBLE )
				{
					res = fabs( (static_cast<double>(res1.m_vInt)) - res2.m_vDouble ) > DOUBLE_ZERO;
				}
				else
				{
					throw TYPE_OP_ERR;
				}
			}
			else
			{
				throw TYPE_OP_ERR;
			}
		}
	}
	return res;
}


const Value operator / ( const Value &res1, const Value &res2 )
{
	//проверка на несовместные типы
	if( (res1.m_tType == TYPE_UNKNOWN)||(res2.m_tType == TYPE_UNKNOWN) )
		throw CONVERT_ERR;
	if( (res1.m_tType != TYPE_INT)&&(res1.m_tType != TYPE_DOUBLE)&&
		(res1.m_tType != TYPE_MATR) )
		throw CONVERT_ERR;
	if( (res2.m_tType != TYPE_INT)&&(res2.m_tType != TYPE_DOUBLE)&&
		(res2.m_tType != TYPE_MATR) )
		throw CONVERT_ERR;

	errorsT er = NOERR;
	if( res1.m_tType == res2.m_tType )
	{
		if( res1.m_tType == TYPE_MATR )//в данной версии делить матрицы друг на друга нельзя
			throw TYPE_OP_ERR;
		Value res;
		switch(res1.m_tType)
		{
		case TYPE_INT:
			if( res2.m_vInt == 0 )
			{
				er =  DIV_ZERO;
				break;
			}
			res.SetInt( res1.m_vInt/res2.m_vInt );
			return res;
			break;
		case TYPE_DOUBLE:
			if( res2.m_vDouble == 0.0 )
			{
				er = DIV_ZERO;
				break;
			}
			res.SetDouble( res1.m_vDouble/res2.m_vDouble );
			return res;
			break;
		case TYPE_MATR:
		default:
			ASSERT(FALSE);
			break;
		}
	}
	else
	{
		Value res;
		//типы переменных разные
		//надо выбрать наиболее подходящий тип для рез-та
		if( res1.m_tType == TYPE_DOUBLE )
		{
			if( res2.m_tType == TYPE_INT )
			{
				if( res2.m_vInt == 0 )	er = DIV_ZERO;
				else
				{
					res.SetDouble( res1.m_vDouble/res2.m_vInt );
					return res;
				}
			}
			else
			{
				//res2.m_tType == TYPE_MATR
				er = TYPE_OP_ERR;
			}
		}
		else
		{
			//значит res1.m_tType или int или matr
			if( res1.m_tType == TYPE_INT )
			{
				if( res2.m_tType == TYPE_DOUBLE )
				{
					if( res2.m_vDouble == 0.0 )	er = DIV_ZERO;
					else
					{
						res.SetDouble( res1.m_vInt/res2.m_vDouble );
						return res;
					}
				}
				else
				{
					er = TYPE_OP_ERR;
				}
			}
			else
			{
				//res1.m_tType == TYPE_MATR
				if( res1.m_tType == TYPE_MATR )
				{
					if( res2.m_tType == TYPE_INT )
					{
						res.SetMatr( (*res1.m_pMatr->GetMatr())/res2.GetInt() );
						return res;
					}
					else
					{
						if( res2.m_tType == TYPE_DOUBLE )
						{
							res.SetMatr( (*res1.m_pMatr->GetMatr())/res2.GetDouble() );
							return res;
						}
						else
						{
							er = TYPE_OP_ERR;
						}
					}
				}
				else
				{
					ASSERT(FALSE);
				}
			}
		}
	}
	if( er != NOERR )
		throw er;
	//до этой точки выполнение добраться не должно, т.к. корректные значения
	//должны вернутся из глубины тела ф-ции, а при некорректной операции
	//над Value должно активироваться исключение.
	ASSERT(FALSE);
	return Value();//вернём чего нибудь, чтобы Visual не ругался
}

const Value operator * ( const Value &res1, const Value &res2 )
{
	//проверка на несовместные типы
	if( (res1.m_tType == TYPE_UNKNOWN)||(res2.m_tType == TYPE_UNKNOWN) )
		throw CONVERT_ERR;
	if( (res1.m_tType != TYPE_INT)&&(res1.m_tType != TYPE_DOUBLE)&&
		(res1.m_tType != TYPE_MATR) )
		throw CONVERT_ERR;
	if( (res2.m_tType != TYPE_INT)&&(res2.m_tType != TYPE_DOUBLE)&&
		(res2.m_tType != TYPE_MATR) )
		throw CONVERT_ERR;

	errorsT er = NOERR;
	if( res1.m_tType == res2.m_tType )
	{
		Value res;
		switch(res1.m_tType)
		{
		case TYPE_INT:
			res.SetInt( res1.m_vInt*res2.m_vInt );
			return res;
			break;
		case TYPE_DOUBLE:
			res.SetDouble( res1.m_vDouble*res2.m_vDouble );
			return res;
			break;
		case TYPE_MATR:
			if( (res1.GetMatr()->GetMatr()->GetRow()!=res2.GetMatr()->GetMatr()->GetRow())||
				(res1.GetMatr()->GetMatr()->GetWidth()!=res2.GetMatr()->GetMatr()->GetWidth()) )
			{
				er = TYPE_OP_ERR;
			}
			else
			{
				res.SetMatr( (*res1.GetMatr()->GetMatr())*(*res2.GetMatr()->GetMatr()) );
				return res;
			}
			break;
		default:
			ASSERT(FALSE);
			break;
		}
	}
	else
	{
		Value res;
		//типы переменных разные
		//надо выбрать наиболее подходящий тип для рез-та
		if( res1.m_tType == TYPE_DOUBLE )
		{
			if( res2.m_tType == TYPE_INT )
			{
				res.SetDouble( res1.m_vDouble*res2.m_vInt );
				return res;
			}
			else
			{
				//res2.m_tType == TYPE_MATR
				ASSERT(res2.m_tType == TYPE_MATR);
				if( res2.m_tType == TYPE_MATR )
				{
					res.SetMatr( (*res2.GetMatr()->GetMatr())*res1.GetDouble() );
					return res;
				}
			}
		}
		else
		{
			//значит res1.m_tType или int или matr
			if( res1.m_tType == TYPE_INT )
			{
				if( res2.m_tType == TYPE_DOUBLE )
				{
					res.SetDouble( res1.m_vInt*res2.m_vDouble );
					return res;
				}
				else
				{
					ASSERT( res2.m_tType == TYPE_MATR );
					res.SetMatr( (*res2.GetMatr()->GetMatr())*res1.GetInt() );
					return res;
				}
			}
			else
			{
				//res1.m_tType == TYPE_MATR
				ASSERT( res1.m_tType == TYPE_MATR );
				if( res2.m_tType == TYPE_INT )
				{
					res.SetMatr( (*res1.GetMatr()->GetMatr())*res2.GetInt() );
					return res;
				}
				else
				{
					if( res2.m_tType == TYPE_DOUBLE )
					{
						res.SetMatr( (*res1.GetMatr()->GetMatr())*res2.GetDouble() );
						return res;
					}
					else
					{
						er = TYPE_OP_ERR;
					}
				}
			}
		}
	}
	if( er != NOERR )
		throw er;
	ASSERT(FALSE);
	return Value();
}

const Value operator - ( const Value &res1, const Value &res2 )
{
	//проверка на несовместные типы
	if( (res1.m_tType == TYPE_UNKNOWN)||(res2.m_tType == TYPE_UNKNOWN) )
		throw CONVERT_ERR;
	if( (res1.m_tType != TYPE_INT)&&(res1.m_tType != TYPE_DOUBLE)&&
		(res1.m_tType != TYPE_MATR) )
		throw CONVERT_ERR;
	if( (res2.m_tType != TYPE_INT)&&(res2.m_tType != TYPE_DOUBLE)&&
		(res2.m_tType != TYPE_MATR) )
		throw CONVERT_ERR;

	errorsT er = NOERR;
	if( res1.m_tType == res2.m_tType )
	{
		Value res;
		switch(res1.m_tType)
		{
		case TYPE_INT:
			res.SetInt( res1.m_vInt-res2.m_vInt );
			return res;
			break;
		case TYPE_DOUBLE:
			res.SetDouble( res1.m_vDouble-res2.m_vDouble );
			return res;
			break;
		case TYPE_MATR:
			if( (res1.GetMatr()->GetMatr()->GetRow()!=res2.GetMatr()->GetMatr()->GetRow())||
				(res1.GetMatr()->GetMatr()->GetWidth()!=res2.GetMatr()->GetMatr()->GetWidth()) )
			{
				er = TYPE_OP_ERR;
			}
			else
			{
				res.SetMatr( (*res1.GetMatr()->GetMatr())-(*res2.GetMatr()->GetMatr()) );
				return res;
			}
			break;
		default:
			ASSERT(FALSE);
			break;
		}
	}
	else
	{
		Value res;
		//типы переменных разные
		//надо выбрать наиболее подходящий тип для рез-та
		if( res1.m_tType == TYPE_DOUBLE )
		{
			if( res2.m_tType == TYPE_INT )
			{
				res.SetDouble( res1.m_vDouble-res2.m_vInt );
				return res;
			}
			else
			{
				//res2.m_tType == TYPE_MATR
				ASSERT( res2.m_tType == TYPE_MATR );
				res2.GetMatr()->GetMatr()->Negate();
				res.SetMatr( (*res2.GetMatr()->GetMatr())+res1.GetDouble() );
				return res;
			}
		}
		else
		{
			//значит res1.m_tType или int или matr
			if( res1.m_tType == TYPE_INT )
			{
				if( res2.m_tType == TYPE_DOUBLE )
				{
					res.SetDouble( res1.m_vInt-res2.m_vDouble );
					return res;
				}
				else
				{
					ASSERT( res2.m_tType == TYPE_MATR );
					res2.GetMatr()->GetMatr()->Negate();
					res.SetMatr( (*res2.GetMatr()->GetMatr())+res1.GetInt() );
					return res;
				}
			}
			else
			{
				//res1.m_tType == TYPE_MATR
				if( res1.m_tType == TYPE_MATR )
				{
					if( res2.m_tType == TYPE_INT )
					{
						res.SetMatr( (*res1.GetMatr()->GetMatr())-res2.GetInt() );
						return res;
					}
					else
					{
						if( res2.m_tType == TYPE_DOUBLE )
						{
							res.SetMatr( (*res1.GetMatr()->GetMatr())-res2.GetDouble() );
							return res;
						}
						else	er = TYPE_OP_ERR;
					}
				}
				else	ASSERT(FALSE);
			}
		}
	}
	if( er != NOERR )
		throw er;
	ASSERT(FALSE);
	return Value();
}

const Value operator + ( const Value &res1, const Value &res2 )
{
	//проверка на несовместные типы
	if( (res1.m_tType == TYPE_UNKNOWN)||(res2.m_tType == TYPE_UNKNOWN) )
		throw CONVERT_ERR;
	if( (res1.m_tType != TYPE_INT)&&(res1.m_tType != TYPE_DOUBLE)&&
		(res1.m_tType != TYPE_MATR)&&(res1.m_tType != TYPE_STRING) )
		throw CONVERT_ERR;
	if( (res2.m_tType != TYPE_INT)&&(res2.m_tType != TYPE_DOUBLE)&&
		(res2.m_tType != TYPE_MATR)&&(res2.m_tType != TYPE_STRING) )
		throw CONVERT_ERR;

	errorsT er = NOERR;
	if( res1.m_tType == res2.m_tType )
	{
		Value res;
		switch(res1.m_tType)
		{
		case TYPE_INT:
			res.SetInt( res1.m_vInt+res2.m_vInt );
			return res;
			break;
		case TYPE_DOUBLE:
			res.SetDouble( res1.m_vDouble+res2.m_vDouble );
			return res;
			break;
		case TYPE_STRING:
			res.SetString( *res1.m_pString + *res2.m_pString );
			return res;
			break;
		case TYPE_MATR:
			if( (res1.GetMatr()->GetMatr()->GetRow()!=res2.GetMatr()->GetMatr()->GetRow())||
				(res1.GetMatr()->GetMatr()->GetWidth()!=res2.GetMatr()->GetMatr()->GetWidth()) )
			{
				er = TYPE_OP_ERR;
			}
			else
			{
				res.SetMatr( (*res1.GetMatr()->GetMatr()) + (*res2.GetMatr()->GetMatr()) );
				return res;
			}
			break;
		default:
			ASSERT(FALSE);
			break;
		}
	}
	else
	{
		Value res;
		//типы переменных разные
		//надо выбрать наиболее подходящий тип для рез-та
		if( res1.m_tType == TYPE_DOUBLE )
		{
			if( res2.m_tType == TYPE_INT )
			{
				res.SetDouble( res1.m_vDouble+res2.m_vInt );
				return res;
			}
			else
			{
				if( res2.m_tType == TYPE_STRING )
				{
					res.SetString( FormatString("%.21lf", res1.m_vDouble) + *res2.m_pString );
					return res;
				}
				else
				{
					ASSERT( res2.m_tType == TYPE_MATR );
					res.SetMatr( (*res2.GetMatr()->GetMatr())+res1.GetDouble() );
					return res;
				}
			}
		}
		else
		{
			//значит res1.m_tType или int или matr || string
			if( res1.m_tType == TYPE_INT )
			{
				if( res2.m_tType == TYPE_DOUBLE )
				{
					res.SetDouble( res1.m_vInt+res2.m_vDouble );
					return res;
				}
				else
				{
					if( res2.m_tType == TYPE_STRING )
					{
						res.SetString( FormatString("%d", res1.m_vInt) + *res2.m_pString );
						return res;
					}
					else
					{
						ASSERT( res2.m_tType == TYPE_MATR );
						res.SetMatr( (*res2.GetMatr()->GetMatr())+res1.GetInt() );
						return res;
					}
				}
			}
			else
			{
				if( res1.m_tType == TYPE_STRING )
				{
					if( res2.m_tType == TYPE_DOUBLE )
					{
						//string+double
						res.SetString( *res1.m_pString + FormatString("%.21lf", res2.m_vDouble) );
						return res;
					}
					else
					{
						if( res2.m_tType == TYPE_INT )
						{
							//string+int
							res.SetString( *res1.m_pString + FormatString("%d", res2.m_vInt) );
							return res;
						}
						else
						{
							er = TYPE_OP_ERR;
						}
					}					
				}
				else
				{
					//res1.m_tType == TYPE_MATR
					ASSERT( res1.m_tType == TYPE_MATR );
					if( res2.m_tType == TYPE_INT )
					{
						res.SetMatr( (*res1.GetMatr()->GetMatr())+res2.GetInt() );
						return res;
					}
					else
					{
						if( res2.m_tType == TYPE_DOUBLE )
						{
							res.SetMatr( (*res1.GetMatr()->GetMatr())+res2.GetDouble() );
							return res;
						}
						else	er = TYPE_OP_ERR;
					}
				}
			}
		}
	}
	if( er != NOERR )
		throw er;
	ASSERT(FALSE);
	return Value();
}
///////////////////////////////////////////////////////////////////


