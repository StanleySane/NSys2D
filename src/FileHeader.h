/////////////////////////////////////////////////////////////////
//	file FileHeader.h
/////////////////////////////////////////////////////////////////

#ifndef _FILE_HEADER_H_
#define _FILE_HEADER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include<string>
#include<map>
#include<fstream>

class Value;
class File
{
	std::fstream *m_pFile;
	bool m_bBin;//флаг о том, что это бинарный файл. иначе текстовый.
	bool m_bValid;//флаг о том, что файл успешо открыт и готов к использованию
	std::string m_Name;//имя файла

	void Destruct();
	void InitBy( const File& );

	bool ReadBin( Value& ) const;
	bool ReadTxt( Value& ) const;
	bool WriteBin( const Value& ) const;
	bool WriteTxt( const Value& ) const;
public:
	typedef std::map<std::fstream*,int> FilePtrs;
	typedef FilePtrs::value_type MakeFilePtr;
	typedef std::pair<FilePtrs::iterator,bool> Pair;
	static FilePtrs m_FilePtrMap;

	File& operator = ( const File &v )
	{
		if( this == &v )	return *this;
		InitBy(v);
		return *this;
	}
	File( const File &v ):m_pFile(NULL), m_bBin(true), m_bValid(false)
	{
		InitBy(v);
	}
	File():m_pFile(NULL), m_bBin(true), m_bValid(false)
	{}
	~File()
	{	Destruct();	}

	//ф-ции-члены
	void Close();
	bool OpenTxt( const std::string& );
	bool OpenBin( const std::string& );
	bool Rewind();
	std::string GetName() const;

	bool Read( Value& ) const;
	bool Write( const Value& ) const;
	bool WriteEOL() const;
};

typedef std::map<std::string,File> VarFile;
typedef VarFile::value_type MakeFile;

#endif //_FILE_HEADER_H_