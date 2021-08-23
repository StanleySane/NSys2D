// ScriptFunctions.cpp: implementation of the ScriptObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NSys2D.h"

#include "ScriptObject.h"
//#include "OutputView.h"
//#include "ScriptDoc.h"

#include"AlgolMatr.h"
#include"Elem.h"

#include"MatrPtr.h"
#include"RodPtr.h"
#include"HardRodPtr.h"
#include"SpringPtr.h"
#include"DemferPtr.h"
#include"MassPtr.h"
#include"KnotPtr.h"
#include"ShemePtr.h"

#include<cmath>
#include<new>
#include<algorithm>
#include<limits>
#include<cstdarg>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

double CNSys2DApp::M_PI = CNSys2DApp::InitPI();
double CNSys2DApp::M_PI_2 = CNSys2DApp::InitPI_2();

ShemePtr::Refs ShemePtr::m_RefMap;
RodPtr::Refs RodPtr::m_RefMap;
HardRodPtr::Refs HardRodPtr::m_RefMap;
SpringPtr::Refs SpringPtr::m_RefMap;
DemferPtr::Refs DemferPtr::m_RefMap;
MassPtr::Refs MassPtr::m_RefMap;
KnotPtr::Refs KnotPtr::m_RefMap;
MatrPtr::Refs MatrPtr::m_MatrRefMap;
ScriptPtr::Refs ScriptPtr::m_ScriptRefMap;
Variables::Refs Variables::m_VarsRefMap;

vector<string> ScriptObject::m_ErrMesTable = ScriptObject::InitErrMesTable();
Commands ScriptObject::m_CommandTable = ScriptObject::InitCommandTable();
Variables ScriptObject::m_ConstTable = ScriptObject::InitConstTable();
Functions ScriptObject::m_FuncTable = ScriptObject::InitFuncTable();
Types ScriptObject::m_TypeTable = ScriptObject::InitTypeTable();
bool ScriptObject::m_bFatalCrash = false;
const int ScriptObject::TAB_SIZE = 8;
const int ScriptObject::MAX_ERRMES_LEN = 100;

const double CShemeExpr::DOUBLE_ZERO = 1e-300;

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

errorsT ScriptObject::Fun_PrintAllReservedWords( const ValList &lst, Value *val )
{
	if( val == NULL )
	{
		if( lst.size() != 0 )
		{
			StackErr(0);
			return WRONG_FUNC_PARAM_NUM;
		}
		return NOERR;
	}
	//возвращаемое значение
	int i = 0;
	for( Expression::InternalFuncMap::iterator itf = Expression::m_FuncTable.begin();
			itf != Expression::m_FuncTable.end(); ++itf )
	{
		SetOutput("\r\n");
		SetOutput( (*itf).first );
		i++;
	}
	for( Commands::iterator itc = m_CommandTable.begin();
			itc != m_CommandTable.end(); ++itc )
	{
		SetOutput("\r\n");
		SetOutput( (*itc).first );
		i++;
	}
	for( FuncIter it = m_FuncTable.begin();
			it != m_FuncTable.end(); ++it )
	{
		SetOutput("\r\n");
		SetOutput( (*it).first );
		i++;
	}
	for( Types::iterator itt = m_TypeTable.begin();
			itt != m_TypeTable.end(); ++itt )
	{
		SetOutput("\r\n");
		SetOutput( (*itt).first );
		i++;
	}
	//константы
	for( VarBool::iterator itb = m_ConstTable.BoolMap()->begin();
			itb != m_ConstTable.BoolMap()->end(); ++itb )
	{
		SetOutput("\r\n");
		SetOutput( (*itb).first );
		i++;
	}
	for( VarInteger::iterator iti = m_ConstTable.IntMap()->begin();
			iti != m_ConstTable.IntMap()->end(); ++iti )
	{
		SetOutput("\r\n");
		SetOutput( (*iti).first );
		i++;
	}
	for( VarDouble::iterator itd = m_ConstTable.DoubleMap()->begin();
			itd != m_ConstTable.DoubleMap()->end(); ++itd )
	{
		SetOutput("\r\n");
		SetOutput( (*itd).first );
		i++;
	}	
	val->SetInt( i );
	return NOERR;
}

errorsT ScriptObject::Fun_PrintCode( const ValList &lst, Value *val )
{
	if( val == NULL )
	{
		if( lst.size() != 0 )
		{
			StackErr(0);
			return WRONG_FUNC_PARAM_NUM;
		}
		return NOERR;
	}
	//возвращаемое значение
	val->SetInt( m_Code.size() );

	CommandPointer cp;
	for( cp = m_Code.begin(); cp != m_Code.end(); ++cp )
	{
		string CmdName, Params;
		switch( (*cp)->GetCommandID() )
		{
		case CMD_LABEL:
			CmdName = " LABEL ";
			Params += (static_cast<CComLabel*>(*cp))->m_label;
			break;
		case CMD_MOV_EXPR:
			CmdName = " MOV ";
			Params += (static_cast<CComMovExpr*>(*cp))->m_name;
			CutEOL(Params);
			Params += ",";
			Params += (static_cast<CComMovExpr*>(*cp))->m_expr.GetExpr();
			CutEOL(Params);
			break;
		case CMD_ADD:
			CmdName = " ADD ";
			Params += (static_cast<CComAdd*>(*cp))->m_name;
			CutEOL(Params);
			Params += ",";
			Params += (static_cast<CComAdd*>(*cp))->m_val.GetExpr();
			CutEOL(Params);
			break;
		case CMD_PRINT:
			{
				CmdName = " PRINT ";
				CComPrint *cmd = static_cast<CComPrint*>(*cp);
				PrintList::iterator it = cmd->m_expr.begin(), fin = cmd->m_expr.end();
				for(; it != fin; ++it )
				{
					Params += (*it).first.GetExpr();
					Params += (*it).second;
				}
				CutEOL(Params);
			}
			break;
		case CMD_CMP_VAR_EXPR:
			CmdName = " CMP ";
			Params += (static_cast<CComCmpVarExpr*>(*cp))->m_name;
			CutEOL(Params);
			Params += ",";
			Params += (static_cast<CComCmpVarExpr*>(*cp))->m_expr.GetExpr();
			CutEOL(Params);
			break;
		case CMD_CMP_EXPR_VAL:
			{
				CmdName = " CMP ";
				Params += (static_cast<CComCmpExprVal*>(*cp))->m_expr.GetExpr();
				CutEOL(Params);
				Params += ",";
				Value val = (static_cast<CComCmpExprVal*>(*cp))->m_val;
				Params += val.StringVariant();
			}
			break;
		case CMD_JMP:
			CmdName = " JMP ";
			Params += (static_cast<CComJmp*>(*cp))->m_label;
			break;
		case CMD_JE:
			CmdName = " JE ";
			Params += (static_cast<CComJe*>(*cp))->m_label;
			break;
		case CMD_JG:
			CmdName = " JG ";
			Params += (static_cast<CComJg*>(*cp))->m_label;
			break;
		case CMD_JL:
			CmdName = " JL ";
			Params += (static_cast<CComJl*>(*cp))->m_label;
			break;
		case CMD_CALL:
			CmdName = " CALL ";
			Params += (static_cast<CComCall*>(*cp))->m_func.GetExpr();
			break;
		case CMD_END:
			CmdName = " END ";
			Params = "";
			break;
		case CMD_PUSH_SUB:
			CmdName = " PUSH_SUB ";
			Params += (static_cast<CComPushSub*>(*cp))->m_label;
			break;
		case CMD_RET:
			CmdName = " RET ";
			Params = "";
			break;
		case CMD_RETF:
			CmdName = " RETF ";
			Params += (static_cast<CComRetf*>(*cp))->m_expr.GetExpr();
			CutEOL(Params);
			break;
		default:
			ASSERT(FALSE);
			break;
		}
		SetOutput( CmdName );
		if( !Params.empty() )
			SetOutput( Params );
		SetOutput("\r\n");
	}
	return NOERR;
}

errorsT ScriptObject::Fun_Help( const ValList &lst, Value *val )
{
	int s = lst.size();
	if( val == NULL )
	{
		if( (s != 0)&&(s != 1) )
		{
			StackErr( s, false );
			return WRONG_FUNC_PARAM_NUM;
		}
		return NOERR;
	}
	ValList::const_iterator it = lst.begin();
	bool flg = true;
	if( s == 1 )
	{
		if( !(*it).first->ConvertTo(TYPE_BOOL) )
		{
			ErrMesRun(CONVERT_ERR);
			return NOERR;
		}
		flg = (*it).first->GetBool();
	}
	if( flg )
	{
		string mes("Краткая справка по численным методам:\r\n");
		mes += "\tМетоды поиска собственных значений (четвёртый параметр функции GetEigen):\r\n";
		mes += "\t0 - Метод Якоби с понижением нормы для матриц общего вида\r\n";
		mes += "\t1 - QR-алгоритм для полных матриц с приведением исходной матрицы к верхней форме Хессенберга\r\n";
		mes += "\t2 - Что и предыдущий, но с применением накопления скалярного произведения с повышенной точностью\r\n";
		mes += "\t3 - С помощью элементарных ортогональных преобразований с сохранением числа обусловленности отдельных собственных значений\r\n";
		mes += "\tМетоды интегрирования (второй параметр функции Integrate):\r\n";
		mes += "\t0 - Метод Рунге-Кутта\r\n";
		mes += "\t1 - Метод Парка\r\n";
		mes += "\t2 - Метод Ньюмарка\r\n";
		mes += "Конец справки.\r\n";
		SetOutput( mes );
	}
	val->SetString("NSys2D v3.0 Script System v1.0");
	return NOERR;
}

errorsT ScriptObject::Fun_SetAt( const ValList &lst, Value *val )
{
//данная версия ф-ции работает с массивами и с м-цами
	ValList::const_iterator it = lst.begin();
	int s = lst.size();
	if( val == NULL )
	{
		//компиляция
		if( (s != 3)&&(s != 4) )
		{
			StackErr( s, false );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string Name = *(*it).second;
	Variables *vars = GetVarTable( Name );
	TypeID tid = vars->GetVarType( Name );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		bool bIsArr = Array::IsArray(tid);
		if( !bIsArr && (tid != TYPE_MATR) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		else
		{
			//значит это массив ( bIsArr == true ) или матрица
			if( (bIsArr && (s != 3))||(!bIsArr && (s != 4)) )
				return WRONG_FUNC_PARAM_NUM;
		}
		return NOERR;
	}

	val->SetBool( false );
	//вычисляем значение второго пар-ра - индекса:
	++it;
	if( !(*it).first->ConvertTo(TYPE_INT) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}
	int pos = (*it).first->GetInt(), pos2 = 0;
	Array *ar = NULL;
	MatrPtr *m = NULL;
	if( s == 3 )
	{
		//массив
		ar = vars->GetArray( Name );
		ASSERT( ar != NULL );
		tid = ar->GetType();//тип массива
		ASSERT( tid != TYPE_UNKNOWN );
		tid = Array::GetValType(tid);//тип хранимого в массиве значения
		ASSERT( tid != TYPE_UNKNOWN );
	}
	else
	{
		//s == 4
		//м-ца:
		//вычисляем значение 3-го пар-ра:
		++it;
		if( !(*it).first->ConvertTo( TYPE_INT ) )
		{
			ErrMesRun(CONVERT_ERR);
			return NOERR;
		}
		pos2 = (*it).first->GetInt();
		m = vars->GetMatr( Name );
		ASSERT( m );
		tid = TYPE_DOUBLE;
	}
	//вычисляем значение последнего пар-ра (3-го или 4-го):
	++it;
	if( !(*it).first->ConvertTo( tid ) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}
	if( s == 3 )
	{
		//массив:
		if( ar->SetAt( pos, *(*it).first ) == false )
		{
			ErrMesRun(ARRAY_ACCESS);
			return NOERR;
		}
	}
	else
	{
		//м-ца:
		if( m->SetAt( pos, pos2, *(*it).first ) == false )
		{
			ErrMesRun(ARRAY_ACCESS);
			return NOERR;
		}
	}
	//возвращаемое значение
	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_GetAt( const ValList &lst, Value *val )
{
//данная версия ф-ции работает с массивами и матрицами
	ValList::const_iterator it = lst.begin();
	int s = lst.size();
	if( val == NULL )
	{
		//компиляция
		if( (s != 2)&&(s != 3) )
		{
			StackErr( s, false );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string Name = *(*it).second;
	Variables *vars = GetVarTable( Name );
	TypeID tid = vars->GetVarType( Name );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		bool bIsArr = Array::IsArray(tid);
		if( !bIsArr && (tid != TYPE_MATR) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		else
		{
			//значит это массив ( bIsArr == true ) или матрица
			if( (bIsArr && (s != 2))||(!bIsArr && (s != 3)) )
				return WRONG_FUNC_PARAM_NUM;
		}
		return NOERR;
	}

	//вычисляем значение второго пар-ра - индекса:
	++it;
	if( !(*it).first->ConvertTo(TYPE_INT) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}
	int pos = (*it).first->GetInt();
	if( s == 2 )
	{
		Array *ar = vars->GetArray( Name );
		ASSERT( ar != NULL );
		tid = ar->GetType();//тип массива
		ASSERT( tid != TYPE_UNKNOWN );
		if( ar->GetAt( pos, *val ) == false )
		{
			ErrMesRun(ARRAY_ACCESS);
			return ARRAY_ACCESS;
		}
	}
	else
	{
		//вычисляем значение второго индекса:
		++it;
		if( !(*it).first->ConvertTo(TYPE_INT) )
		{
			ErrMesRun(CONVERT_ERR);
			return NOERR;
		}
		MatrPtr *m = vars->GetMatr( Name );
		ASSERT( m );
		if( m->GetAt( pos, (*it).first->GetInt(), *val ) == false )
		{
			ErrMesRun(ARRAY_ACCESS);
			return ARRAY_ACCESS;
		}
	}
	return NOERR;
}

errorsT ScriptObject::Fun_Resize( const ValList &lst, Value *val )
{
//данная версия ф-ции работает с массивами и матрицами
	ValList::const_iterator it = lst.begin();
	int s = lst.size();
	if( val == NULL )
	{
		//компиляция
		if( (s != 2)&&(s != 3) )
		{
			StackErr( s, false );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string Name = *(*it).second;//имя массива или м-цы
	Variables *vars = GetVarTable( Name );
	TypeID tid = vars->GetVarType( Name );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		bool bIsArr = Array::IsArray(tid);
		if( !bIsArr && (tid != TYPE_MATR) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		else
		{
			//значит это массив ( bIsArr == true ) или матрица
			if( (bIsArr && (s != 2))||(!bIsArr && (s != 3)) )
				return WRONG_FUNC_PARAM_NUM;
		}
		return NOERR;
	}

	val->SetBool( false );
	//вычисляем значение второго пар-ра - размера:
	++it;
	if( !(*it).first->ConvertTo(TYPE_INT) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}
	int len = (*it).first->GetInt();
	if( s == 2 )
	{
		//массив
		Array *ar = vars->GetArray( Name );
		ASSERT( ar != NULL );
//		tid = ar->GetType();//тип массива
//		ASSERT( tid != TYPE_UNKNOWN );

		if( ar->Resize( len ) == false )
		{
			return NOERR;
		}
	}
	else
	{
		//м-ца
		//вычисляем значение второго пар-ра - столбцы:
		++it;
		if( !(*it).first->ConvertTo(TYPE_INT) )
		{
			ErrMesRun(CONVERT_ERR);
			return NOERR;
		}
		MatrPtr *m = vars->GetMatr( Name );
		ASSERT( m != NULL );
		if( m->Resize( len, (*it).first->GetInt() ) == false )
			return NOERR;
	}
	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_Sizeof( const ValList &lst, Value *val )
{
//данная версия ф-ции работает с массивами и м-цами
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr(1);
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string Name = *(*it).second;
	Variables *vars = GetVarTable( Name );
	TypeID tid = vars->GetVarType( Name );
	ASSERT( tid != TYPE_UNKNOWN );
	bool bIsArr = Array::IsArray(tid);
	if( val == NULL )
	{
		if( (tid != TYPE_MATR) && !bIsArr )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	val->SetInt(0);

	int sz = 0;
	if( bIsArr )
	{
		Array *ar = vars->GetArray( Name );
		ASSERT( ar != NULL );
		sz = ar->Size();
	}
	else
	{
		MatrPtr *m = vars->GetMatr( Name );
		ASSERT( m );
		AlgolMatr *pAM = m->GetMatr();
		if( pAM != NULL )
			sz = pAM->GetRow()*pAM->GetWidth();
	}
	val->SetInt( sz );

	return NOERR;
}

errorsT ScriptObject::Fun_FileOpenBin( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 2 )
		{
			StackErr(2);
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string Name = *(*it).second;
	Variables *vars = GetVarTable( Name );
	TypeID tid = vars->GetVarType( Name );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_FILE )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}
	//вычисляем значение второго пар-ра - имени файла:
	++it;
	if( !(*it).first->ConvertTo(TYPE_STRING) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}
	File *f = vars->GetFile( Name );
	ASSERT( f != NULL );
	val->SetBool( f->OpenBin( (*it).first->GetString() ) );
	return NOERR;
}

errorsT ScriptObject::Fun_FileOpenTxt( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 2 )
		{
			StackErr(2);
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string Name = *(*it).second;
	Variables *vars = GetVarTable( Name );
	TypeID tid = vars->GetVarType( Name );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_FILE )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}
	//вычисляем значение второго пар-ра - имени файла:
	++it;
	if( !(*it).first->ConvertTo(TYPE_STRING) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}
	File *f = vars->GetFile( Name );
	ASSERT( f != NULL );
	val->SetBool( f->OpenTxt( (*it).first->GetString() ) );
	return NOERR;
}

errorsT ScriptObject::Fun_FileRead( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 2 )
		{
			StackErr(2);
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string FileName = *(*it).second;
	Variables *varsFile = GetVarTable( FileName );
	TypeID tid = varsFile->GetVarType( FileName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_FILE )
		{
			ErrMesCompile(CONVERT_ERR);
		}
	}

	//вычисляем значение второго пар-ра - имени переменной:
	++it;
	if( val == NULL )
	{
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string VarName = *(*it).second;
	Variables *varsVar = GetVarTable( VarName );
	tid = varsVar->GetVarType( VarName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !ScriptObject::IsValidAssignment(tid) )
		{
			ErrMesCompile(TYPE_OP_ERR);
		}
		return NOERR;
	}

	File *f = varsFile->GetFile( FileName );
	ASSERT( f != NULL );
	val->SetBool( f->Read( *(*it).first ) );
	errorsT er = ScriptObject::AssignVar( VarName, *varsVar, *(*it).first );
	ASSERT( er == NOERR );
	return NOERR;
}

errorsT ScriptObject::Fun_FileWrite( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 2 )
		{
			StackErr(2);
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string FileName = *(*it).second;
	Variables *vars = GetVarTable( FileName );
	TypeID tid = vars->GetVarType( FileName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_FILE )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}
	//вычисляем значение второго пар-ра:
	++it;
	File *f = vars->GetFile( FileName );
	ASSERT( f != NULL );
	val->SetBool( f->Write( *(*it).first ) );
	return NOERR;
}

errorsT ScriptObject::Fun_FileWriteEOL( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr(1);
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string FileName = *(*it).second;
	Variables *vars = GetVarTable( FileName );
	TypeID tid = vars->GetVarType( FileName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_FILE )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}
	File *f = vars->GetFile( FileName );
	ASSERT( f != NULL );
	val->SetBool( f->WriteEOL() );
	return NOERR;
}

errorsT ScriptObject::Fun_FileRewind( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr(1);
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string FileName = *(*it).second;
	Variables *vars = GetVarTable( FileName );
	TypeID tid = vars->GetVarType( FileName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_FILE )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}
	File *f = vars->GetFile( FileName );
	ASSERT( f != NULL );
	val->SetBool( f->Rewind() );
	return NOERR;
}

errorsT ScriptObject::Fun_FileClose( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr(1);
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string FileName = *(*it).second;
	Variables *vars = GetVarTable( FileName );
	TypeID tid = vars->GetVarType( FileName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_FILE )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}
	File *f = vars->GetFile( FileName );
	ASSERT( f != NULL );
	f->Close();
	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_RunScript( const ValList &lst, Value *val )
{
	ValList::const_iterator beg = lst.begin(), fin = lst.end();
	ValList::const_iterator it = beg;
	if( val == NULL )
	{
		int s = lst.size();
		//компиляция
		if( s < 1 )
		{
			StackErr( s, false );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ScrName = *(*it).second;
	Variables *vars = GetVarTable( ScrName );
	TypeID tid = vars->GetVarType( ScrName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_SCRIPT )
		{
			ErrMesCompile(CONVERT_ERR);
			return NOERR;
		}
	}
	ScriptPtr *pScr = vars->GetScript( ScrName );
	ASSERT( pScr != NULL );
	//вычисляем значения пар-ров:
	++it;
	while( it != fin )
	{
		//выставляем значения соответствующих параметров скрипта:
		errorsT er;
		if( val == NULL )
		{
			//компиляция:
			if( (*it).second == NULL )
			{
				ErrMesCompile(NOT_VAR);
				return NOERR;
			}
			vars = GetVarTable( *(*it).second );
			tid = vars->GetVarType( *(*it).second );
			ASSERT( tid != TYPE_UNKNOWN );
			if( !ScriptObject::IsValidAssignment(tid) )
			{
				ErrMesExpr( *(*it).second );
				ErrMesCompile(TYPE_OP_ERR);
				return NOERR;
			}
		}
		else
		{
			//выполнение:
			if( (er = pScr->SetParam( distance(beg,it), *(*it).first )) != NOERR )
			{
				ErrMesRun(er);
			}
		}
		++it;
	}
	if( val == NULL )
		return NOERR;
	val->SetBool( false );
	string tmp = pScr->GetFileName();
	SetOutput( FormatString("\r\n<------------Executing of module %s ...---->\r\n",
				tmp.c_str() ) );
	pScr->SetDebug(false);
	bool res = pScr->Run();
	pScr->GetOutput(tmp);
	SetOutput( tmp );
	SetOutput( FormatString("\r\n<------------Executing of module %s done---->\r\n",
				pScr->GetFileName().c_str() ) );
	if( res == false )
	{
		ErrMesRun(RUN_ERR);
		return NOERR;
	}
	//если скрипт выполнился правильно:
	it = beg;
	++it;
	res = true;
	for(; it != fin; ++it )
	{
		errorsT er;
		Value val;//значение пар-ра
		if( (er = pScr->GetParam( distance(beg,it), val )) != NOERR )
		{
			ErrMesRun(er);
			res = false;
			continue;
		}
		string VarName = *(*it).second;
		vars = GetVarTable( VarName );
		tid = vars->GetVarType( VarName );
		ASSERT( tid != TYPE_UNKNOWN );
		er = ScriptObject::AssignVar( VarName, *vars, val );
		ASSERT( er == NOERR );
	}
	val->SetBool(res);
	return NOERR;
}

errorsT ScriptObject::Fun_CreateKnot( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 3 )
		{
			StackErr( 3 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string Name = *(*it).second;//имя узла
	Variables *vars = GetVarTable( Name );
	TypeID tid = vars->GetVarType( Name );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_KNOT )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	val->SetBool( false );
	//вычисляем значение второго пар-ра - коор-ты X:
	++it;
	if( !(*it).first->ConvertTo(TYPE_DOUBLE) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}
	double x = (*it).first->GetDouble();
	//вычисляем значение 3-го пар-ра - коор-ты X:
	++it;
	if( !(*it).first->ConvertTo(TYPE_DOUBLE) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}
	KnotPtr *kn = vars->GetKnot( Name );
	ASSERT( kn );
	if( kn->Create( x, (*it).first->GetDouble() ) == false )
		return NOERR;

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_CreateElem( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	int s = lst.size();
	if( val == NULL )
	{
		//компиляция
		if( (s != 2)&&(s != 3) )
		{
			StackErr( s, false );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя элемента
	Variables *ElemVars = GetVarTable( ElemName );
	TypeID ElemType = ElemVars->GetVarType( ElemName );
	ASSERT( ElemType != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(ElemType) )
		{
			ErrMesCompile(CONVERT_ERR);
			return NOERR;
		}
		if( (ElemType == TYPE_MASS)&&(s == 3) )
			return WRONG_FUNC_PARAM_NUM;
	}
	//вычисляем второй пар-р - имя узла:
	++it;
	string Knot1Name = *(*it).second, Knot2Name;//имена узлов
	Variables *Knot1Vars = GetVarTable( Knot1Name ), *Knot2Vars = NULL;
	TypeID tid = Knot1Vars->GetVarType( Knot1Name );
	ASSERT( tid != TYPE_UNKNOWN );
	if( (val == NULL)&&(tid != TYPE_KNOT) )
	{
		ErrMesCompile(CONVERT_ERR);
		return NOERR;
	}
	if( s == 3 )
	{
		//вычисляем 3-й пар-р - имя узла:
		++it;
		Knot2Name = *(*it).second;
		Knot2Vars = GetVarTable( Knot2Name );
		tid = Knot2Vars->GetVarType( Knot2Name );
		ASSERT( tid != TYPE_UNKNOWN );
		if( (val == NULL)&&(tid != TYPE_KNOT) )
		{
			ErrMesCompile(CONVERT_ERR);
			return NOERR;
		}
	}
	if( val == NULL )
		return NOERR;
	
	val->SetBool( false );

	KnotPtr *kn1 = Knot1Vars->GetKnot( Knot1Name ), *kn2 = NULL;
	ASSERT( kn1 );
	if( s == 3 )
	{
		kn2 = Knot2Vars->GetKnot( Knot2Name );
		ASSERT( kn2 );
	}

	switch( ElemType )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			if( elem->Create( kn1, kn2 ) == false )
				return NOERR;
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			if( elem->Create( kn1, kn2 ) == false )
				return NOERR;
		}
		break;
	case TYPE_SPRING:
		{
			SpringPtr *elem = ElemVars->GetSpring( ElemName );
			ASSERT( elem );
			if( elem->Create( kn1, kn2 ) == false )
				return NOERR;
		}
		break;
	case TYPE_DEMFER:
		{
			DemferPtr *elem = ElemVars->GetDemfer( ElemName );
			ASSERT( elem );
			if( elem->Create( kn1, kn2 ) == false )
				return NOERR;
		}
		break;
	case TYPE_MASS:
		{
			MassPtr *elem = ElemVars->GetMass( ElemName );
			ASSERT( elem );
			if( elem->Create( kn1 ) == false )
				return NOERR;
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_SetElemM( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 2 )
		{
			StackErr( 2 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя эл-та
	Variables *ElemVars = GetVarTable( ElemName );
	TypeID tid = ElemVars->GetVarType( ElemName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		if( (tid == TYPE_DEMFER)||(tid == TYPE_SPRING) )
			return TYPE_OP_ERR;
		return NOERR;
	}

	val->SetBool( false );
	//вычисляем значение второго пар-ра:
	++it;
	if( !(*it).first->ConvertTo(TYPE_DOUBLE) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}

	switch( tid )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			if( elem->SetM( (*it).first->GetDouble() ) == false )
				return NOERR;
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			if( elem->SetM( (*it).first->GetDouble() ) == false )
				return NOERR;
		}
		break;
	case TYPE_MASS:
		{
			MassPtr *elem = ElemVars->GetMass( ElemName );
			ASSERT( elem );
			if( elem->SetM( (*it).first->GetDouble() ) == false )
				return NOERR;
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_SetElemJ( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 2 )
		{
			StackErr( 2 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя эл-та
	Variables *ElemVars = GetVarTable( ElemName );
	TypeID tid = ElemVars->GetVarType( ElemName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		if( (tid == TYPE_DEMFER)||(tid == TYPE_SPRING) )
			return TYPE_OP_ERR;
		return NOERR;
	}

	val->SetBool( false );
	//вычисляем значение второго пар-ра:
	++it;
	if( !(*it).first->ConvertTo(TYPE_DOUBLE) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}

	switch( tid )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			if( elem->SetJ( (*it).first->GetDouble() ) == false )
				return NOERR;
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			if( elem->SetJ( (*it).first->GetDouble() ) == false )
				return NOERR;
		}
		break;
	case TYPE_MASS:
		{
			MassPtr *elem = ElemVars->GetMass( ElemName );
			ASSERT( elem );
			if( elem->SetJ( (*it).first->GetDouble() ) == false )
				return NOERR;
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_SetElemF( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 2 )
		{
			StackErr( 2 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя эл-та
	Variables *ElemVars = GetVarTable( ElemName );
	TypeID tid = ElemVars->GetVarType( ElemName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		if( (tid != TYPE_ROD)&&(tid != TYPE_HARDROD) )
			return TYPE_OP_ERR;
		return NOERR;
	}

	val->SetBool( false );
	//вычисляем значение второго пар-ра:
	++it;
	if( !(*it).first->ConvertTo(TYPE_DOUBLE) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}

	switch( tid )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			if( elem->SetF( (*it).first->GetDouble() ) == false )
				return NOERR;
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			if( elem->SetF( (*it).first->GetDouble() ) == false )
				return NOERR;
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_SetElemE( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 2 )
		{
			StackErr( 2 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя эл-та
	Variables *ElemVars = GetVarTable( ElemName );
	TypeID tid = ElemVars->GetVarType( ElemName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		if( (tid != TYPE_ROD)&&(tid != TYPE_HARDROD) )
			return TYPE_OP_ERR;
		return NOERR;
	}

	val->SetBool( false );
	//вычисляем значение второго пар-ра:
	++it;
	if( !(*it).first->ConvertTo(TYPE_DOUBLE) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}

	switch( tid )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			if( elem->SetE( (*it).first->GetDouble() ) == false )
				return NOERR;
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			if( elem->SetE( (*it).first->GetDouble() ) == false )
				return NOERR;
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_GetElemM( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя эл-та
	Variables *ElemVars = GetVarTable( ElemName );
	TypeID tid = ElemVars->GetVarType( ElemName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		if( (tid == TYPE_DEMFER)||(tid == TYPE_SPRING) )
			return TYPE_OP_ERR;
		return NOERR;
	}

	switch( tid )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			val->SetDouble( elem->GetM() );
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			val->SetDouble( elem->GetM() );
		}
		break;
	case TYPE_MASS:
		{
			MassPtr *elem = ElemVars->GetMass( ElemName );
			ASSERT( elem );
			val->SetDouble( elem->GetM() );
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}
	return NOERR;
}

errorsT ScriptObject::Fun_GetElemJ( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя эл-та
	Variables *ElemVars = GetVarTable( ElemName );
	TypeID tid = ElemVars->GetVarType( ElemName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		if( (tid == TYPE_DEMFER)||(tid == TYPE_SPRING) )
			return TYPE_OP_ERR;
		return NOERR;
	}

	switch( tid )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			val->SetDouble( elem->GetJ() );
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			val->SetDouble( elem->GetJ() );
		}
		break;
	case TYPE_MASS:
		{
			MassPtr *elem = ElemVars->GetMass( ElemName );
			ASSERT( elem );
			val->SetDouble( elem->GetJ() );
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}
	return NOERR;
}

errorsT ScriptObject::Fun_GetElemF( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя эл-та
	Variables *ElemVars = GetVarTable( ElemName );
	TypeID tid = ElemVars->GetVarType( ElemName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		if( (tid != TYPE_ROD)&&(tid != TYPE_HARDROD) )
			return TYPE_OP_ERR;
		return NOERR;
	}

	switch( tid )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			val->SetDouble( elem->GetF() );
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			val->SetDouble( elem->GetF() );
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}
	return NOERR;
}

errorsT ScriptObject::Fun_GetElemE( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя эл-та
	Variables *ElemVars = GetVarTable( ElemName );
	TypeID tid = ElemVars->GetVarType( ElemName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		if( (tid != TYPE_ROD)&&(tid != TYPE_HARDROD) )
			return TYPE_OP_ERR;
		return NOERR;
	}

	switch( tid )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			val->SetDouble( elem->GetE() );
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			val->SetDouble( elem->GetE() );
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}
	return NOERR;
}

errorsT ScriptObject::Fun_GetLength( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя эл-та
	Variables *ElemVars = GetVarTable( ElemName );
	TypeID tid = ElemVars->GetVarType( ElemName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		if( tid == TYPE_MASS )
			return TYPE_OP_ERR;
		return NOERR;
	}

	val->SetDouble( 0.0 );

	switch( tid )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			val->SetDouble( elem->GetLength() );
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			val->SetDouble( elem->GetLength() );
		}
		break;
	case TYPE_SPRING:
		{
			SpringPtr *elem = ElemVars->GetSpring( ElemName );
			ASSERT( elem );
			val->SetDouble( elem->GetLength() );
		}
		break;
	case TYPE_DEMFER:
		{
			DemferPtr *elem = ElemVars->GetDemfer( ElemName );
			ASSERT( elem );
			val->SetDouble( elem->GetLength() );
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}
	return NOERR;
}

errorsT ScriptObject::Fun_GetElemMatrM( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя эл-та
	Variables *ElemVars = GetVarTable( ElemName );
	TypeID tid = ElemVars->GetVarType( ElemName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	switch( tid )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrM() );
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrM() );
		}
		break;
	case TYPE_SPRING:
		{
			SpringPtr *elem = ElemVars->GetSpring( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrM() );
		}
		break;
	case TYPE_DEMFER:
		{
			DemferPtr *elem = ElemVars->GetDemfer( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrM() );
		}
		break;
	case TYPE_MASS:
		{
			MassPtr *elem = ElemVars->GetMass( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrM() );
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}
	return NOERR;
}

errorsT ScriptObject::Fun_GetElemMatrD( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя эл-та
	Variables *ElemVars = GetVarTable( ElemName );
	TypeID tid = ElemVars->GetVarType( ElemName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	switch( tid )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrD() );
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrD() );
		}
		break;
	case TYPE_SPRING:
		{
			SpringPtr *elem = ElemVars->GetSpring( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrD() );
		}
		break;
	case TYPE_DEMFER:
		{
			DemferPtr *elem = ElemVars->GetDemfer( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrD() );
		}
		break;
	case TYPE_MASS:
		{
			MassPtr *elem = ElemVars->GetMass( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrD() );
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}
	return NOERR;
}

errorsT ScriptObject::Fun_GetElemMatrC( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя эл-та
	Variables *ElemVars = GetVarTable( ElemName );
	TypeID tid = ElemVars->GetVarType( ElemName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	switch( tid )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrC() );
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrC() );
		}
		break;
	case TYPE_SPRING:
		{
			SpringPtr *elem = ElemVars->GetSpring( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrC() );
		}
		break;
	case TYPE_DEMFER:
		{
			DemferPtr *elem = ElemVars->GetDemfer( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrC() );
		}
		break;
	case TYPE_MASS:
		{
			MassPtr *elem = ElemVars->GetMass( ElemName );
			ASSERT( elem );
			val->SetMatr( elem->GetMatrC() );
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}
	return NOERR;
}

errorsT ScriptObject::Fun_LoadIdentity( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string Name = *(*it).second;
	Variables *vars = GetVarTable( Name );
	TypeID tid = vars->GetVarType( Name );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_MATR )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	val->SetBool( false );

	MatrPtr *m = vars->GetMatr( Name );
	ASSERT( m );
	AlgolMatr *pAM = m->GetMatr();
	if( pAM == NULL )
		return NOERR;
	if( pAM->LoadIdentity() == false )
		return NOERR;

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_Invert( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string Name = *(*it).second;
	Variables *vars = GetVarTable( Name );
	TypeID tid = vars->GetVarType( Name );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_MATR )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	val->SetBool( false );

	MatrPtr *m = vars->GetMatr( Name );
	ASSERT( m );
	if( m->GetMatr()->Invert() == false )
		return NOERR;

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_OpenSheme( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 2 )
		{
			StackErr( 2 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string Name = *(*it).second;//имя схемы
	Variables *vars = GetVarTable( Name );
	TypeID tid = vars->GetVarType( Name );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_SHEME )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	val->SetBool( false );

	//вычисляем значение второго пар-ра - имени файла:
	++it;
	if( !(*it).first->ConvertTo(TYPE_STRING) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}

	ShemePtr *p = vars->GetSheme( Name );
	ASSERT( p );
	if( p->Open( (*it).first->GetString() ) == false )
		return NOERR;

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_CloseSheme( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string Name = *(*it).second;//имя схемы
	Variables *vars = GetVarTable( Name );
	TypeID tid = vars->GetVarType( Name );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_SHEME )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	val->SetBool( false );

	ShemePtr *p = vars->GetSheme( Name );
	ASSERT( p );
	if( p->Close() == false )
		return NOERR;

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_SaveSheme( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string Name = *(*it).second;//имя схемы
	Variables *vars = GetVarTable( Name );
	TypeID tid = vars->GetVarType( Name );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_SHEME )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	val->SetBool( false );

	ShemePtr *p = vars->GetSheme( Name );
	ASSERT( p );
	if( p->Save() == false )
		return NOERR;

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_SaveShemeAs( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 2 )
		{
			StackErr( 2 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string Name = *(*it).second;//имя схемы
	Variables *vars = GetVarTable( Name );
	TypeID tid = vars->GetVarType( Name );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_SHEME )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	val->SetBool( false );

	//вычисляем значение второго пар-ра - имени файла:
	++it;
	if( !(*it).first->ConvertTo(TYPE_STRING) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}

	ShemePtr *p = vars->GetSheme( Name );
	ASSERT( p );
	if( p->SaveAs( (*it).first->GetString() ) == false )
		return NOERR;

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_GetEigen( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 4 )
		{
			StackErr( 4 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ShemeName = *(*it).second;//имя схемы или м-цы
	Variables *ShemeVars = GetVarTable( ShemeName );
	TypeID tid = ShemeVars->GetVarType( ShemeName );
	ASSERT( tid != TYPE_UNKNOWN );
	bool IsMatr;//флаг о том, что ищутся собств.значения м-цы
	if( val == NULL )
	{
		if( (tid != TYPE_SHEME)&&(tid != TYPE_MATR) )
		{
			ErrMesCompile(CONVERT_ERR);
			return NOERR;
		}
		IsMatr = (tid == TYPE_MATR);
	}
	//вычисляем значение второго пар-ра - имени матрицы частот:
	++it;
	if( val == NULL )
	{
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string FreqName = *(*it).second;
	Variables *FreqVars = GetVarTable( FreqName );
	tid = FreqVars->GetVarType( FreqName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_MATR )
		{
			ErrMesCompile(CONVERT_ERR);
			return NOERR;
		}
	}
	//вычисляем значение третьего пар-ра - имени матрицы форм:
	++it;
	if( val == NULL )
	{
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string FormsName = *(*it).second;
	Variables *FormsVars = GetVarTable( FormsName );
	tid = FormsVars->GetVarType( FormsName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_MATR )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}
	//вычисляем значение 4-го пар-ра - метода поиска собств частот и форм:
	++it;
	if( !(*it).first->ConvertTo(TYPE_INT) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}

	val->SetBool( false );

	MatrPtr *pMatrFreq = FreqVars->GetMatr( FreqName );
	ASSERT( pMatrFreq );
	MatrPtr *pMatrForms = FormsVars->GetMatr( FormsName );
	ASSERT( pMatrForms );
	if( pMatrFreq->GetMatr() == NULL )
		pMatrFreq->Construct( 0, 0 );
	if( pMatrForms->GetMatr() == NULL )
		pMatrForms->Construct( 0, 0 );
	AlgolMatr *pFreqs = pMatrFreq->GetMatr(), *pForms = pMatrForms->GetMatr();

	if( IsMatr )
	{
		MatrPtr *pMatr = ShemeVars->GetMatr( ShemeName );
		ASSERT( pMatr );
		if( pMatr->GetEigen( *pFreqs, *pForms, (*it).first->GetInt() ) == false )
			return NOERR;
	}
	else
	{
		ShemePtr *pSh = ShemeVars->GetSheme( ShemeName );
		ASSERT( pSh );
		if( pSh->SetEVMethod( (*it).first->GetInt() ) == false )
			return NOERR;
		if( pSh->GetEigen( *pFreqs, *pForms ) == false )
			return NOERR;
	}

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_Integrate( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 4 )
		{
			StackErr( 4 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ShemeName = *(*it).second;//имя схемы
	Variables *ShemeVars = GetVarTable( ShemeName );
	TypeID tid = ShemeVars->GetVarType( ShemeName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_SHEME )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}
	//вычисляем значение второго пар-ра - метода интегрирования:
	++it;
	if( !(*it).first->ConvertTo(TYPE_INT) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}
	int iMethod = (*it).first->GetInt();
	//вычисляем значение третьего пар-ра - времени интегрирования:
	++it;
	if( !(*it).first->ConvertTo(TYPE_DOUBLE) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}
	double dTime = (*it).first->GetDouble();
	//вычисляем значение 4-го пар-ра - шага интегрирования:
	++it;
	if( !(*it).first->ConvertTo(TYPE_DOUBLE) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}

	val->SetBool( false );

	ShemePtr *pSh = ShemeVars->GetSheme( ShemeName );
	ASSERT( pSh );
	if( pSh->SetParamIntegr( iMethod, dTime, (*it).first->GetDouble() ) == false )
		return NOERR;
	if( pSh->Integrate() == false )
		return NOERR;

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_GetResY1( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ShemeName = *(*it).second;//имя схемы
	Variables *ShemeVars = GetVarTable( ShemeName );
	TypeID tid = ShemeVars->GetVarType( ShemeName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_SHEME )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	ShemePtr *pSh = ShemeVars->GetSheme( ShemeName );
	ASSERT( pSh );
	AlgolMatr m;
	pSh->GetResY1( m );
	val->SetMatr( m );

	return NOERR;
}

errorsT ScriptObject::Fun_GetResY2( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ShemeName = *(*it).second;//имя схемы
	Variables *ShemeVars = GetVarTable( ShemeName );
	TypeID tid = ShemeVars->GetVarType( ShemeName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_SHEME )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	ShemePtr *pSh = ShemeVars->GetSheme( ShemeName );
	ASSERT( pSh );
	AlgolMatr m;
	pSh->GetResY2( m );
	val->SetMatr( m );

	return NOERR;
}

errorsT ScriptObject::Fun_GetResY3( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ShemeName = *(*it).second;//имя схемы
	Variables *ShemeVars = GetVarTable( ShemeName );
	TypeID tid = ShemeVars->GetVarType( ShemeName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_SHEME )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	ShemePtr *pSh = ShemeVars->GetSheme( ShemeName );
	ASSERT( pSh );
	AlgolMatr m;
	pSh->GetResY3( m );
	val->SetMatr( m );

	return NOERR;
}

errorsT ScriptObject::Fun_GetMatrMDC( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 4 )
		{
			StackErr( 4 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ShemeName = *(*it).second;//имя схемы
	Variables *ShemeVars = GetVarTable( ShemeName );
	TypeID tid = ShemeVars->GetVarType( ShemeName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_SHEME )
		{
			ErrMesCompile(CONVERT_ERR);
			return NOERR;
		}
	}
	//вычисляем значение второго пар-ра - имени матрицы масс:
	++it;
	if( val == NULL )
	{
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string MName = *(*it).second;
	Variables *MVars = GetVarTable( MName );
	tid = MVars->GetVarType( MName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_MATR )
		{
			ErrMesCompile(CONVERT_ERR);
			return NOERR;
		}
	}
	//вычисляем значение третьего пар-ра - имени матрицы демпфирования:
	++it;
	if( val == NULL )
	{
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string DName = *(*it).second;
	Variables *DVars = GetVarTable( DName );
	tid = DVars->GetVarType( DName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_MATR )
		{
			ErrMesCompile(CONVERT_ERR);
			return NOERR;
		}
	}
	//вычисляем значение 4-го пар-ра - м-цы жёсткости:
	++it;
	if( val == NULL )
	{
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string CName = *(*it).second;
	Variables *CVars = GetVarTable( CName );
	tid = CVars->GetVarType( CName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_MATR )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	val->SetBool( false );

	ShemePtr *pSh = ShemeVars->GetSheme( ShemeName );
	ASSERT( pSh );
	MatrPtr *pMatrM = MVars->GetMatr( MName );
	ASSERT( pMatrM );
	MatrPtr *pMatrD = DVars->GetMatr( DName );
	ASSERT( pMatrD );
	MatrPtr *pMatrC = CVars->GetMatr( CName );
	ASSERT( pMatrC );

	if( pMatrM->GetMatr() == NULL )
		pMatrM->Construct( 0, 0 );
	if( pMatrD->GetMatr() == NULL )
		pMatrD->Construct( 0, 0 );
	if( pMatrC->GetMatr() == NULL )
		pMatrC->Construct( 0, 0 );
	AlgolMatr *pM = pMatrM->GetMatr();
	AlgolMatr *pD = pMatrD->GetMatr();
	AlgolMatr *pC = pMatrC->GetMatr();

	if( pSh->GetMatrMDC( *pM, *pD, *pC ) == false )
		return NOERR;

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_GetElem( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 3 )
		{
			StackErr( 3 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя элемента
	Variables *ElemVars = GetVarTable( ElemName );
	TypeID tid = ElemVars->GetVarType( ElemName ), tEl;
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
			return NOERR;
		}
	}
	tEl = tid;
	//вычисляем значение 3-го пар-ра - имени схемы:
	++it;
	++it;
	if( val == NULL )
	{
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ShemeName = *(*it).second;//имя схемы
	Variables *ShemeVars = GetVarTable( ShemeName );
	tid = ShemeVars->GetVarType( ShemeName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_SHEME )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}
	//вычисляем значение второго пар-ра - номера элемента:
	--it;
	if( !(*it).first->ConvertTo(TYPE_INT) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}

	val->SetBool( false );

	ShemePtr *pSh = ShemeVars->GetSheme( ShemeName );
	ASSERT( pSh );
	CElem *pEl = pSh->GetElemByNum( (*it).first->GetInt() );
	if( pEl == NULL )
		return NOERR;
	if( ScriptObject::GetScriptElemType( pEl->TypeElem ) != tEl )
		return NOERR;
	switch( tEl )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			if( elem->Attach( pEl ) == false )
				return NOERR;
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			if( elem->Attach( pEl ) == false )
				return NOERR;
		}
		break;
	case TYPE_MASS:
		{
			MassPtr *elem = ElemVars->GetMass( ElemName );
			ASSERT( elem );
			if( elem->Attach( pEl ) == false )
				return NOERR;
		}
		break;
	case TYPE_DEMFER:
		{
			DemferPtr *elem = ElemVars->GetDemfer( ElemName );
			ASSERT( elem );
			if( elem->Attach( pEl ) == false )
				return NOERR;
		}
		break;
	case TYPE_SPRING:
		{
			SpringPtr *elem = ElemVars->GetSpring( ElemName );
			ASSERT( elem );
			if( elem->Attach( pEl ) == false )
				return NOERR;
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}
	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_DelElem( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 2 )
		{
			StackErr( 2 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	//вычисляем значение 1-го пар-ра - имени схемы:
	string ShemeName = *(*it).second;//имя схемы
	Variables *ShemeVars = GetVarTable( ShemeName );
	TypeID tid = ShemeVars->GetVarType( ShemeName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_SHEME )
		{
			ErrMesCompile(CONVERT_ERR);
			return NOERR;
		}
	}
	//вычисляем значение второго пар-ра - имени элемента:
	++it;
	if( val == NULL )
	{
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя элемента
	Variables *ElemVars = GetVarTable( ElemName );
	tid = ElemVars->GetVarType( ElemName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	val->SetBool( false );

	ShemePtr *pSh = ShemeVars->GetSheme( ShemeName );
	ASSERT( pSh );
	switch( tid )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			int c = elem->GetRefCount();
			ASSERT( c > 0 );
			if( c != 1 )
			{
				//вероятно, на элемент ссылается несколько переменных.
				return NOERR;
			}
			if( pSh->DelElem( elem->GetElem() ) == false )
				return NOERR;
			elem->Detach();
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			int c = elem->GetRefCount();
			ASSERT( c > 0 );
			if( c != 1 )
			{
				//вероятно, на элемент ссылается несколько переменных.
				return NOERR;
			}
			if( pSh->DelElem( elem->GetElem() ) == false )
				return NOERR;
			elem->Detach();
		}
		break;
	case TYPE_MASS:
		{
			MassPtr *elem = ElemVars->GetMass( ElemName );
			ASSERT( elem );
			int c = elem->GetRefCount();
			ASSERT( c > 0 );
			if( c != 1 )
			{
				//вероятно, на элемент ссылается несколько переменных.
				return NOERR;
			}
			if( pSh->DelElem( elem->GetElem() ) == false )
				return NOERR;
			elem->Detach();
		}
		break;
	case TYPE_DEMFER:
		{
			DemferPtr *elem = ElemVars->GetDemfer( ElemName );
			ASSERT( elem );
			int c = elem->GetRefCount();
			ASSERT( c > 0 );
			if( c != 1 )
			{
				//вероятно, на элемент ссылается несколько переменных.
				return NOERR;
			}
			if( pSh->DelElem( elem->GetElem() ) == false )
				return NOERR;
			elem->Detach();
		}
		break;
	case TYPE_SPRING:
		{
			SpringPtr *elem = ElemVars->GetSpring( ElemName );
			ASSERT( elem );
			int c = elem->GetRefCount();
			ASSERT( c > 0 );
			if( c != 1 )
			{
				//вероятно, на элемент ссылается несколько переменных.
				return NOERR;
			}
			if( pSh->DelElem( elem->GetElem() ) == false )
				return NOERR;
			elem->Detach();
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}
	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_GetKnot( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 3 )
		{
			StackErr( 3 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string KnotName = *(*it).second;//имя узла
	Variables *KnotVars = GetVarTable( KnotName );
	TypeID tid = KnotVars->GetVarType( KnotName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_KNOT )
		{
			ErrMesCompile(CONVERT_ERR);
			return NOERR;
		}
	}
	//вычисляем значение 3-го пар-ра - имени схемы:
	++it;
	++it;
	if( val == NULL )
	{
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ShemeName = *(*it).second;//имя схемы
	Variables *ShemeVars = GetVarTable( ShemeName );
	tid = ShemeVars->GetVarType( ShemeName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_SHEME )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}
	//вычисляем значение второго пар-ра - номера узла:
	--it;
	if( !(*it).first->ConvertTo(TYPE_INT) )
	{
		ErrMesRun(CONVERT_ERR);
		return NOERR;
	}

	val->SetBool( false );

	ShemePtr *pSh = ShemeVars->GetSheme( ShemeName );
	ASSERT( pSh );
	CKnot *pKn = pSh->GetKnotByNum( (*it).first->GetInt() );
	if( pKn == NULL )
		return NOERR;
	KnotPtr *kn = KnotVars->GetKnot( KnotName );
	ASSERT( kn );
	if( kn->Attach( pKn ) == false )
		return NOERR;

	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_Delete( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 1 )
		{
			StackErr( 1 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	//вычисляем значение 1-го пар-ра - имени:
	string Name = *(*it).second;//имя
	Variables *Vars = GetVarTable( Name );
	TypeID tid = Vars->GetVarType( Name );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( (tid != TYPE_KNOT)&&(!Variables::IsElem(tid)) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	val->SetBool( false );

	if( tid == TYPE_KNOT )
	{
		KnotPtr *p = Vars->GetKnot( Name );
		p->Detach();
	}
	else
	{
		switch( tid )
		{
		case TYPE_ROD:
			{
				RodPtr *elem = Vars->GetRod( Name );
				ASSERT( elem );
				elem->Detach();
			}
			break;
		case TYPE_HARDROD:
			{
				HardRodPtr *elem = Vars->GetHardRod( Name );
				ASSERT( elem );
				elem->Detach();
			}
			break;
		case TYPE_MASS:
			{
				MassPtr *elem = Vars->GetMass( Name );
				ASSERT( elem );
				elem->Detach();
			}
			break;
		case TYPE_DEMFER:
			{
				DemferPtr *elem = Vars->GetDemfer( Name );
				ASSERT( elem );
				elem->Detach();
			}
			break;
		case TYPE_SPRING:
			{
				SpringPtr *elem = Vars->GetSpring( Name );
				ASSERT( elem );
				elem->Detach();
			}
			break;
		default:
			ASSERT(FALSE);
			return NOERR;
		}
	}
	val->SetBool( true );
	return NOERR;
}

errorsT ScriptObject::Fun_AddElement( const ValList &lst, Value *val )
{
	ValList::const_iterator it = lst.begin();
	if( val == NULL )
	{
		//компиляция
		if( lst.size() != 2 )
		{
			StackErr( 2 );
			return WRONG_FUNC_PARAM_NUM;
		}
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	//вычисляем значение 1-го пар-ра - имени схемы:
	string ShemeName = *(*it).second;//имя схемы
	Variables *ShemeVars = GetVarTable( ShemeName );
	TypeID tid = ShemeVars->GetVarType( ShemeName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( tid != TYPE_SHEME )
		{
			ErrMesCompile(CONVERT_ERR);
			return NOERR;
		}
	}
	//вычисляем значение второго пар-ра - имени элемента:
	++it;
	if( val == NULL )
	{
		if( (*it).second == NULL )
		{
			ErrMesCompile(NOT_VAR);
			return NOERR;
		}
	}
	string ElemName = *(*it).second;//имя элемента
	Variables *ElemVars = GetVarTable( ElemName );
	tid = ElemVars->GetVarType( ElemName );
	ASSERT( tid != TYPE_UNKNOWN );
	if( val == NULL )
	{
		if( !Variables::IsElem(tid) )
		{
			ErrMesCompile(CONVERT_ERR);
		}
		return NOERR;
	}

	val->SetBool( false );

	ShemePtr *pSh = ShemeVars->GetSheme( ShemeName );
	ASSERT( pSh );
	switch( tid )
	{
	case TYPE_ROD:
		{
			RodPtr *elem = ElemVars->GetRod( ElemName );
			ASSERT( elem );
			if( pSh->AddElement( elem->GetElem() ) == false )
				return NOERR;
		}
		break;
	case TYPE_HARDROD:
		{
			HardRodPtr *elem = ElemVars->GetHardRod( ElemName );
			ASSERT( elem );
			if( pSh->AddElement( elem->GetElem() ) == false )
				return NOERR;
		}
		break;
	case TYPE_MASS:
		{
			MassPtr *elem = ElemVars->GetMass( ElemName );
			ASSERT( elem );
			if( pSh->AddElement( elem->GetElem() ) == false )
				return NOERR;
		}
		break;
	case TYPE_DEMFER:
		{
			DemferPtr *elem = ElemVars->GetDemfer( ElemName );
			ASSERT( elem );
			if( pSh->AddElement( elem->GetElem() ) == false )
				return NOERR;
		}
		break;
	case TYPE_SPRING:
		{
			SpringPtr *elem = ElemVars->GetSpring( ElemName );
			ASSERT( elem );
			if( pSh->AddElement( elem->GetElem() ) == false )
				return NOERR;
		}
		break;
	default:
		ASSERT(FALSE);
		return NOERR;
	}
	val->SetBool( true );
	return NOERR;
}
