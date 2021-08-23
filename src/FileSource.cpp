// FileSource.cpp: implementation of the File class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"

#include"FileHeader.h"
#include"ValueHeader.h"
#include"ArrayHeader.h"
#include"MatrPtr.h"
#include"AlgolMatr.h"
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

File::FilePtrs File::m_FilePtrMap;
//////////////////////////////////////////////////////////////////////
//	members of File class
//////////////////////////////////////////////////////////////////////
void File::Destruct()
{
	Close();
}

void File::InitBy( const File &f )
{
	if( (m_pFile)&&( m_pFile != f.m_pFile ) )
	{
		Close();
	}
	m_bBin = f.m_bBin;
	m_bValid = f.m_bValid;
	m_pFile = f.m_pFile;
	if( m_pFile )
	{
		FilePtrs::iterator it = m_FilePtrMap.find(m_pFile);
		ASSERT( it != m_FilePtrMap.end() );
		(*it).second++;
	}
	m_Name = f.m_Name;
}

void File::Close()
{
	if( m_pFile )
	{
		FilePtrs::iterator it = m_FilePtrMap.find(m_pFile);
		//ASSERT( it != m_FilePtrMap.end() );
		if( it == m_FilePtrMap.end() )
		{
			m_pFile = NULL;
			return;
		}
		(*it).second--;
		if( (*it).second == 0 )
		{
			//fclose(m_pFile);
			m_pFile->close();
			delete m_pFile;
			m_pFile = NULL;
			m_FilePtrMap.erase(it);
		}
	}
	m_bBin = true;
	m_bValid = false;
	m_Name.erase( m_Name.begin(), m_Name.end() );
}

bool File::OpenTxt( const std::string &name )
{
	Close();
	//m_pFile = fopen( name.c_str(), "a+t" );
	//if( m_pFile == NULL )	return false;
	try
	{
		m_pFile = new fstream( name.c_str(), ios::in|ios::out|ios::app );
	}
	catch( bad_alloc& )
	{
		m_pFile = NULL;
		return false;
	}
	if( !m_pFile->is_open() )
	{
		delete m_pFile;
		m_pFile = NULL;
		return false;
	}
	m_pFile->precision(15);
	Pair p = m_FilePtrMap.insert( MakeFilePtr(m_pFile,1) );
	if( p.second == false )
	{
		++(*p.first).second;
	}
	m_Name = name;
	m_bBin = false;
	m_bValid = true;
//	Rewind();
	return true;
}

bool File::OpenBin( const std::string &name )
{
	Close();
	//m_pFile = fopen( name.c_str(), "a+b" );
	//if( m_pFile == NULL )	return false;
	try
	{
		m_pFile = new fstream( name.c_str(), ios::in|ios::out|ios::binary|ios::app );
	}
	catch( bad_alloc& )
	{
		m_pFile = NULL;
		return false;
	}
	if( !m_pFile->is_open() )
	{
		delete m_pFile;
		m_pFile = NULL;
		return false;
	}
	m_pFile->precision(15);
	Pair p = m_FilePtrMap.insert( MakeFilePtr(m_pFile,1) );
	if( p.second == false )
	{
		++(*p.first).second;
	}
	m_Name = name;
	m_bBin = true;
	m_bValid = true;
//	Rewind();
	return true;
}

bool File::Rewind()
{
	if( !m_bValid )
		return false;
	ASSERT(m_pFile);
	//if( fseek( m_pFile, 0, SEEK_SET ) != 0 )	return false;
	//rewind( m_pFile );
	m_pFile->seekg( 0, ios::beg );
	m_pFile->seekp( 0, ios::beg );
	return true;
}

std::string File::GetName() const
{
	if( !m_bValid )
		return string("FILE WAS NOT OPENED");
	return m_Name;
}

bool File::Read( Value &v ) const
{
//ф-ция читает из файла значение типа v.m_tType и заносит его в v
	if( !m_bValid )
		return false;
	ASSERT(m_pFile);
	if( m_bBin )
		return ReadBin(v);
	return ReadTxt(v);
}

bool File::ReadBin( Value &v ) const
{
	switch( v.Type() )
	{
	case TYPE_BOOL:
		{
			bool tmp;
			//if( fread( &tmp, sizeof(tmp), 1, m_pFile ) == 1 )
			(*m_pFile) >> tmp;
			if( m_pFile->good() )
			{
				v.SetBool(tmp);
				return true;
			}
		}
		break;
	case TYPE_INT:
		{
			int tmp;
			//if( fread( &tmp, sizeof(tmp), 1, m_pFile ) == 1 )
			(*m_pFile) >> tmp;
			if( m_pFile->good() )
			{
				v.SetInt(tmp);
				return true;
			}
		}
		break;
	case TYPE_DOUBLE:
		{
			double tmp;
			//if( fread( &tmp, sizeof(tmp), 1, m_pFile ) == 1 )
			(*m_pFile) >> tmp;
			if( m_pFile->good() )
			{
				v.SetDouble(tmp);
				return true;
			}
		}
		break;
	case TYPE_STRING:
		break;
	case TYPE_ARRAY_INT:
	case TYPE_ARRAY_BOOL:
	case TYPE_ARRAY_DOUBLE:
	case TYPE_ARRAY_STRING:
		{
			Value tmp;
			tmp.SetType( Array::GetValType( v.Type() ) );
			int s = v.GetArray()->Size();
			for( int i = 0; i < s; i++ )
			{
				bool res = ReadBin(tmp);
				if( res == false )
					return false;
				res = v.GetArray()->SetAt( i, tmp );
				ASSERT( res == true );
			}
			return true;
		}
		break;
	case TYPE_MATR:
		{
			double tmp;
			AlgolMatr *pM = v.GetMatr()->GetMatr();
			if( !pM )	return false;
			int row = pM->GetRow(), col = pM->GetWidth();
			for( int r = 1; r <= row; r++ )
				for( int c = 0; c < col; c++ )
				{
					(*m_pFile) >> tmp;
					if( !m_pFile->good() )
						return false;
					pM->GetAt( r, c ) = tmp;
				}
			return true;
		}
		break;
	case TYPE_ROD:
	case TYPE_HARDROD:
	case TYPE_SPRING:
	case TYPE_DEMFER:
	case TYPE_MASS:
	case TYPE_KNOT:
	case TYPE_SHEME:
	case TYPE_FILE:
	case TYPE_SCRIPT:
	default:
		ASSERT(false);
	}
	return false;
}

bool File::ReadTxt( Value &v ) const
{
	switch( v.Type() )
	{
	case TYPE_BOOL:
		{
			int tmp;
			//if( fscanf( m_pFile, "%d", &tmp ) > 0 )
			(*m_pFile) >> tmp;
			if( m_pFile->good() )
			{
				v.SetBool( (tmp==0)?(false):(true) );
				return true;
			}
		}
		break;
	case TYPE_INT:
		{
			int tmp;
			//if( fscanf( m_pFile, "%d", &tmp ) > 0 )
			(*m_pFile) >> tmp;
			if( m_pFile->good() )
			{
				v.SetInt(tmp);
				return true;
			}
		}
		break;
	case TYPE_DOUBLE:
		{
			double tmp;
			//if( fscanf( m_pFile, "%e", &tmp ) > 0 )
			(*m_pFile) >> tmp;
			if( m_pFile->good() )
			{
				v.SetDouble(tmp);
				return true;
			}
		}
		break;
	case TYPE_STRING:
		{
			const int s = 81;
			//if( fscanf( m_pFile, "%s", str ) > 0 )
			char str[s];
			m_pFile->getline( str, s, ' ' );
			if( m_pFile->good() )
			{
				v.SetString( string(str) );
				return true;
			}
		}
		break;
	case TYPE_ARRAY_INT:
	case TYPE_ARRAY_BOOL:
	case TYPE_ARRAY_DOUBLE:
	case TYPE_ARRAY_STRING:
		{
			Value tmp;
			tmp.SetType( Array::GetValType( v.Type() ) );
			int s = v.GetArray()->Size();
			for( int i = 0; i < s; i++ )
			{
				bool res = ReadTxt(tmp);
				if( res == false )
					return false;
				res = v.GetArray()->SetAt( i, tmp );
				ASSERT( res == true );
			}
			return true;
		}
		break;
	case TYPE_MATR:
		{
			double tmp;
			AlgolMatr *pM = v.GetMatr()->GetMatr();
			if( !pM )	return false;
			int row = pM->GetRow(), col = pM->GetWidth();
			for( int r = 1; r <= row; r++ )
				for( int c = 0; c < col; c++ )
				{
					(*m_pFile) >> tmp;
					if( !m_pFile->good() )
						return false;
					pM->GetAt( r, c ) = tmp;
				}
			return true;
		}
		break;
	case TYPE_ROD:
	case TYPE_HARDROD:
	case TYPE_SPRING:
	case TYPE_DEMFER:
	case TYPE_MASS:
	case TYPE_KNOT:
	case TYPE_SHEME:
	case TYPE_FILE:
	case TYPE_SCRIPT:
	default:
		ASSERT(false);
	}
	return false;
}

bool File::WriteEOL() const
{
	if( !m_bValid || m_bBin )
		return false;
	ASSERT(m_pFile);
	//if( fprintf( m_pFile, "\n" ) > 0 )	return true;
	(*m_pFile) << "\r\n";
	if( m_pFile->good() )
		return true;
	return false;
}

bool File::Write( const Value &v ) const
{
//ф-ция читает из файла значение типа v.m_tType и заносит его в v
	if( !m_bValid )
		return false;
	ASSERT(m_pFile);
	bool res;
	if( m_bBin )
		res = WriteBin(v);
	else
		res = WriteTxt(v);
	if( res == false )
		return false;
	//if( fflush(m_pFile) == EOF )	return false;
	m_pFile->flush();
	if( !m_pFile->good() )
		return false;
	return true;
}

bool File::WriteBin( const Value &v ) const
{
	switch( v.Type() )
	{
	case TYPE_BOOL:
		{
			bool tmp = v.GetBool();
			//if( fwrite( &tmp, sizeof(tmp), 1, m_pFile ) == 1 )
			(*m_pFile) << tmp;
			if( m_pFile->good() )
				return true;
		}
		break;
	case TYPE_INT:
		{
			int tmp = v.GetInt();
			//if( fwrite( &tmp, sizeof(tmp), 1, m_pFile ) == 1 )
			(*m_pFile) << tmp;
			if( m_pFile->good() )
				return true;
		}
		break;
	case TYPE_DOUBLE:
		{
			double tmp = v.GetDouble();
			//if( fwrite( &tmp, sizeof(tmp), 1, m_pFile ) == 1 )
			(*m_pFile) << tmp;
			if( m_pFile->good() )
				return true;
		}
		break;
	case TYPE_STRING:
		break;
	case TYPE_ARRAY_INT:
	case TYPE_ARRAY_BOOL:
	case TYPE_ARRAY_DOUBLE:
	case TYPE_ARRAY_STRING:
		{
			Value tmp;
			int s = v.GetArray()->Size();
			for( int i = 0; i < s; i++ )
			{
				bool res = v.GetArray()->GetAt( i, tmp );
				ASSERT( res == true );
				res = WriteBin(tmp);
				if( res == false )
					return false;
			}
			return true;
		}
		break;
	case TYPE_MATR:
		{
			AlgolMatr *pM = v.GetMatr()->GetMatr();
			if( !pM )	return false;
			int row = pM->GetRow(), col = pM->GetWidth();
			for( int r = 1; r <= row; r++ )
				for( int c = 0; c < col; c++ )
				{
					double tmp = pM->GetAt( r, c );
					(*m_pFile) << tmp;
					if( !m_pFile->good() )
						return false;
				}
			return true;
		}
		break;
	case TYPE_ROD:
	case TYPE_HARDROD:
	case TYPE_SPRING:
	case TYPE_DEMFER:
	case TYPE_MASS:
	case TYPE_KNOT:
	case TYPE_SHEME:
	case TYPE_FILE:
	case TYPE_SCRIPT:
	default:
		ASSERT(false);
	}
	return false;
}

bool File::WriteTxt( const Value &v ) const
{
	switch( v.Type() )
	{
	case TYPE_BOOL:
		{
			//if( fprintf( m_pFile, "%d ", (v.GetBool())?(1):(0) ) > 0 )
			(*m_pFile) << (v.GetBool())?(1):(0) << ' ';
			if( m_pFile->good() )
				return true;
		}
		break;
	case TYPE_INT:
		{
			//if( fprintf( m_pFile, "%d ", v.GetInt() ) > 0 )
			(*m_pFile) << v.GetInt() << ' ';
			if( m_pFile->good() )
				return true;
		}
		break;
	case TYPE_DOUBLE:
		{
			//if( fprintf( m_pFile, "%e ", v.GetDouble() ) > 0 )
			(*m_pFile) << v.GetDouble() << ' ';
			if( m_pFile->good() )
				return true;
		}
		break;
	case TYPE_STRING:
		{
			//if( fprintf( m_pFile, "%s ", v.GetString().c_str() ) > 0 )
			(*m_pFile) << v.GetString().c_str() << ' ';
			if( m_pFile->good() )
				return true;
		}
		break;
	case TYPE_ARRAY_INT:
	case TYPE_ARRAY_BOOL:
	case TYPE_ARRAY_DOUBLE:
	case TYPE_ARRAY_STRING:
		{
			Value tmp;
			int s = v.GetArray()->Size();
			for( int i = 0; i < s; i++ )
			{
				bool res = v.GetArray()->GetAt( i, tmp );
				ASSERT( res == true );
				res = WriteTxt(tmp);
				if( res == false )
					return false;
			}
			return true;
		}
		break;
	case TYPE_MATR:
		{
			AlgolMatr *pM = v.GetMatr()->GetMatr();
			if( !pM )	return false;
			int row = pM->GetRow(), col = pM->GetWidth();
			for( int r = 1; r <= row; r++ )
			{
				for( int c = 0; c < col; c++ )
				{
					double tmp = pM->GetAt( r, c );
					(*m_pFile) << tmp << ' ';
					if( !m_pFile->good() )
						return false;
				}
				(*m_pFile) << "\r\n";
				if( !m_pFile->good() )
					return false;
			}
			return true;
		}
		break;
	case TYPE_ROD:
	case TYPE_HARDROD:
	case TYPE_SPRING:
	case TYPE_DEMFER:
	case TYPE_MASS:
	case TYPE_KNOT:
	case TYPE_SHEME:
	case TYPE_FILE:
	case TYPE_SCRIPT:
	default:
		ASSERT(false);
	}
	return false;
}
