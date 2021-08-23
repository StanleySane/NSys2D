# Microsoft Developer Studio Project File - Name="NSys2D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=NSys2D - Win32 debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NSys2D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NSys2D.mak" CFG="NSys2D - Win32 debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NSys2D - Win32 debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "NSys2D___Win32_debug"
# PROP BASE Intermediate_Dir "NSys2D___Win32_debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /debug
# Begin Target

# Name "NSys2D - Win32 debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ComboBox_ConnectType.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboBox_FixedType.cpp
# End Source File
# Begin Source File

SOURCE=.\Complex.cpp
# End Source File
# Begin Source File

SOURCE=.\ComplexMatr.cpp
# End Source File
# Begin Source File

SOURCE=.\ComplexSpectr.cpp
# End Source File
# Begin Source File

SOURCE=.\ComplexSpectrDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CoordD.cpp
# End Source File
# Begin Source File

SOURCE=.\Demf.cpp
# End Source File
# Begin Source File

SOURCE=.\DemfDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Elem.cpp
# End Source File
# Begin Source File

SOURCE=.\ElemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Expression.cpp
# End Source File
# Begin Source File

SOURCE=.\FormsFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\FormsView.cpp
# End Source File
# Begin Source File

SOURCE=.\FreqDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FreqParam.cpp
# End Source File
# Begin Source File

SOURCE=.\FreqViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphicView.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphTimeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphView.cpp
# End Source File
# Begin Source File

SOURCE=.\Knot.cpp
# End Source File
# Begin Source File

SOURCE=.\KnotDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\KnotPropertyFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\KnotPropertyPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\KnotPropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\KnotSpectr.cpp
# End Source File
# Begin Source File

SOURCE=.\ListKnot.cpp
# End Source File
# Begin Source File

SOURCE=.\ListSpectr.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Mass.cpp
# End Source File
# Begin Source File

SOURCE=.\MassDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Matr.cpp
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\NSys2D.cpp
# End Source File
# Begin Source File

SOURCE=.\NSys2D.rc
# End Source File
# Begin Source File

SOURCE=.\ObjectSheme.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamIntegr.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamTime.cpp
# End Source File
# Begin Source File

SOURCE=.\ParamView.cpp
# End Source File
# Begin Source File

SOURCE=.\PreCalcDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Result.cpp
# End Source File
# Begin Source File

SOURCE=.\Rod.cpp
# End Source File
# Begin Source File

SOURCE=.\RodDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\rowcursor.cpp
# End Source File
# Begin Source File

SOURCE=.\ShemeDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ShemeFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ShemeView.cpp
# End Source File
# Begin Source File

SOURCE=.\SpectrDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SpectrParam.cpp
# End Source File
# Begin Source File

SOURCE=.\Spring.cpp
# End Source File
# Begin Source File

SOURCE=.\SpringDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TypeGraphDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ComboBox_ConnectType.h
# End Source File
# Begin Source File

SOURCE=.\ComboBox_FixedType.h
# End Source File
# Begin Source File

SOURCE=.\Complex.h
# End Source File
# Begin Source File

SOURCE=.\ComplexMatr.h
# End Source File
# Begin Source File

SOURCE=.\ComplexSpectr.h
# End Source File
# Begin Source File

SOURCE=.\ComplexSpectrDlg.h
# End Source File
# Begin Source File

SOURCE=.\CoordD.h
# End Source File
# Begin Source File

SOURCE=.\Demf.h
# End Source File
# Begin Source File

SOURCE=.\DemfDlg.h
# End Source File
# Begin Source File

SOURCE=.\Elem.h
# End Source File
# Begin Source File

SOURCE=.\ElemDlg.h
# End Source File
# Begin Source File

SOURCE=.\Expression.h
# End Source File
# Begin Source File

SOURCE=.\FormsFrame.h
# End Source File
# Begin Source File

SOURCE=.\FormsView.h
# End Source File
# Begin Source File

SOURCE=.\FreqDlg.h
# End Source File
# Begin Source File

SOURCE=.\FreqParam.h
# End Source File
# Begin Source File

SOURCE=.\FreqViewDlg.h
# End Source File
# Begin Source File

SOURCE=.\GraphFrm.h
# End Source File
# Begin Source File

SOURCE=.\GraphicView.h
# End Source File
# Begin Source File

SOURCE=.\GraphTimeDlg.h
# End Source File
# Begin Source File

SOURCE=.\GraphView.h
# End Source File
# Begin Source File

SOURCE=.\Knot.h
# End Source File
# Begin Source File

SOURCE=.\KnotDlg.h
# End Source File
# Begin Source File

SOURCE=.\KnotPropertyFrame.h
# End Source File
# Begin Source File

SOURCE=.\KnotPropertyPage1.h
# End Source File
# Begin Source File

SOURCE=.\KnotPropertySheet.h
# End Source File
# Begin Source File

SOURCE=.\KnotSpectr.h
# End Source File
# Begin Source File

SOURCE=.\ListKnot.h
# End Source File
# Begin Source File

SOURCE=.\ListSpectr.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Mass.h
# End Source File
# Begin Source File

SOURCE=.\MassDlg.h
# End Source File
# Begin Source File

SOURCE=.\Matr.h
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\NSys2D.h
# End Source File
# Begin Source File

SOURCE=.\ObjectSheme.h
# End Source File
# Begin Source File

SOURCE=.\ParamIntegr.h
# End Source File
# Begin Source File

SOURCE=.\ParamTime.h
# End Source File
# Begin Source File

SOURCE=.\ParamView.h
# End Source File
# Begin Source File

SOURCE=.\PreCalcDlg.h
# End Source File
# Begin Source File

SOURCE=.\ProgressDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Result.h
# End Source File
# Begin Source File

SOURCE=.\Rod.h
# End Source File
# Begin Source File

SOURCE=.\RodDlg.h
# End Source File
# Begin Source File

SOURCE=.\rowcursor.h
# End Source File
# Begin Source File

SOURCE=.\ShemeDoc.h
# End Source File
# Begin Source File

SOURCE=.\ShemeFrm.h
# End Source File
# Begin Source File

SOURCE=.\ShemeView.h
# End Source File
# Begin Source File

SOURCE=.\SpectrDlg.h
# End Source File
# Begin Source File

SOURCE=.\SpectrParam.h
# End Source File
# Begin Source File

SOURCE=.\Spring.h
# End Source File
# Begin Source File

SOURCE=.\SpringDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TypeGraphDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_x.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\formstyp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\idc_grap.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idr_grap.ico
# End Source File
# Begin Source File

SOURCE=.\res\NSys2D.ico
# End Source File
# Begin Source File

SOURCE=.\res\NSys2D.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ShemeDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\spectr1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\X3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Yel16.ico
# End Source File
# Begin Source File

SOURCE=.\res\Yeltsin.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\NSys2D.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section NSys2D : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid
# 	2:10:HeaderFile:msflexgrid.h
# 	2:8:ImplFile:msflexgrid.cpp
# End Section
# Section NSys2D : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid.h
# 	2:16:DefaultSinkClass:CMSFlexGrid
# End Section
# Section NSys2D : {9F6AA700-D188-11CD-AD48-00AA003C9CB6}
# 	2:5:Class:CRowCursor
# 	2:10:HeaderFile:rowcursor.h
# 	2:8:ImplFile:rowcursor.cpp
# End Section
