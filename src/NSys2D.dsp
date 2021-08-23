# Microsoft Developer Studio Project File - Name="NSys2D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
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
!MESSAGE "NSys2D - Win32 DebugMy" (based on "Win32 (x86) Application")
!MESSAGE "NSys2D - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NSys2D - Win32 debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "NSys2D___Win32_debug"
# PROP BASE Intermediate_Dir "NSys2D___Win32_debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
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

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "NSys2D__"
# PROP BASE Intermediate_Dir "NSys2D__"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"StdAfx.h"
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 /nologo /entry:"" /subsystem:windows /incremental:yes /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "NSys2D__"
# PROP BASE Intermediate_Dir "NSys2D__"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL"
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /debug

!ENDIF 

# Begin Target

# Name "NSys2D - Win32 debug"
# Name "NSys2D - Win32 DebugMy"
# Name "NSys2D - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AlgolMatr.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ArraySource.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ComboBox_ConnectType.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ComboBox_FixedType.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Complex.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ComplexMatr.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ComplexSpectr.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ComplexSpectrDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ConvertToDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CoordD.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Demf.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DemfDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DemferPtr.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Elem.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ElemDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\EqualDegrees.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\EVMDialog.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Expression.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ExprSource.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FileSource.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FormsFrame.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FormsView.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FreqDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FreqParam.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FreqViewDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GraphFrm.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GraphicView.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GraphTimeDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GroupEditDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GroupListDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GroupPreviewDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HardRod.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HardRodDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HardRodPtr.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Knot.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KnotDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KnotPropertyFrame.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KnotPropertyPage1.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KnotPropertySheet.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KnotPtr.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KnotSpectr.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ListKnot.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ListSpectr.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Mass.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MassDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MassPtr.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Matr.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MatrPtr.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MeshElemDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\msflexgrid.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NewGroupDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NSys2D.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\NSys2D.rc

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ObjectSheme.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OutputBuffer.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OutputFrame.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\OutputView.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ParamIntegr.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ParamTime.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ParamView.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PreCalcDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ProgressDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Result.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rod.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RodDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RodPtr.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rowcursor.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ScriptDoc.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ScriptFrame.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ScriptObjectSource.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ScriptPtrSource.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ScriptSource.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ScriptView.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sheme.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ShemeDoc.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ShemeFrm.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ShemeGroup.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ShemeView.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SpectrDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SpectrParam.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Spring.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SpringDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SpringPtr.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TypeGraphDlg.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\UserFuncSource.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ValueSource.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VariablesSource.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VarTablesSource.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ViewStyles.cpp

!IF  "$(CFG)" == "NSys2D - Win32 debug"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 DebugMy"

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Release"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AlgolMatr.h
# End Source File
# Begin Source File

SOURCE=.\ArrayHeader.h
# End Source File
# Begin Source File

SOURCE=.\ComboBox_ConnectType.h
# End Source File
# Begin Source File

SOURCE=.\ComboBox_FixedType.h
# End Source File
# Begin Source File

SOURCE=.\CommandHeader.h
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

SOURCE=.\ConvertToDlg.h
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

SOURCE=.\DemferPtr.h
# End Source File
# Begin Source File

SOURCE=.\Elem.h
# End Source File
# Begin Source File

SOURCE=.\ElemDlg.h
# End Source File
# Begin Source File

SOURCE=.\EqualDegrees.h
# End Source File
# Begin Source File

SOURCE=.\EVMDialog.h
# End Source File
# Begin Source File

SOURCE=.\Expression.h
# End Source File
# Begin Source File

SOURCE=.\ExprHeader.h
# End Source File
# Begin Source File

SOURCE=.\FileHeader.h
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

SOURCE=.\GroupEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\GroupListDlg.h
# End Source File
# Begin Source File

SOURCE=.\GroupPreviewDlg.h
# End Source File
# Begin Source File

SOURCE=.\HardRod.h
# End Source File
# Begin Source File

SOURCE=.\HardRodDlg.h
# End Source File
# Begin Source File

SOURCE=.\HardRodPtr.h
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

SOURCE=.\KnotPtr.h
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

SOURCE=.\MassPtr.h
# End Source File
# Begin Source File

SOURCE=.\Matr.h
# End Source File
# Begin Source File

SOURCE=.\MatrPtr.h
# End Source File
# Begin Source File

SOURCE=.\MeshElemDlg.h
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\NewGroupDlg.h
# End Source File
# Begin Source File

SOURCE=.\NSys2D.h
# End Source File
# Begin Source File

SOURCE=.\ObjectSheme.h
# End Source File
# Begin Source File

SOURCE=.\OutputBuffer.h
# End Source File
# Begin Source File

SOURCE=.\OutputFrame.h
# End Source File
# Begin Source File

SOURCE=.\OutputView.h
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

SOURCE=.\RodPtr.h
# End Source File
# Begin Source File

SOURCE=.\rowcursor.h
# End Source File
# Begin Source File

SOURCE=.\ScriptDefs.h
# End Source File
# Begin Source File

SOURCE=.\ScriptDoc.h
# End Source File
# Begin Source File

SOURCE=.\ScriptFrame.h
# End Source File
# Begin Source File

SOURCE=.\ScriptHeader.h
# End Source File
# Begin Source File

SOURCE=.\ScriptObject.h
# End Source File
# Begin Source File

SOURCE=.\ScriptPtrHeader.h
# End Source File
# Begin Source File

SOURCE=.\ScriptView.h
# End Source File
# Begin Source File

SOURCE=.\Sheme.h
# End Source File
# Begin Source File

SOURCE=.\ShemeDoc.h
# End Source File
# Begin Source File

SOURCE=.\ShemeFrm.h
# End Source File
# Begin Source File

SOURCE=.\ShemeGroup.h
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

SOURCE=.\SpringPtr.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TypeGraphDlg.h
# End Source File
# Begin Source File

SOURCE=.\UserFuncHeader.h
# End Source File
# Begin Source File

SOURCE=.\ValueHeader.h
# End Source File
# Begin Source File

SOURCE=.\VariablesHeader.h
# End Source File
# Begin Source File

SOURCE=.\VarTables.h
# End Source File
# Begin Source File

SOURCE=.\ViewStyles.h
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

SOURCE=.\Res\idr_form.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_grap.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_outp.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_scri.ico
# End Source File
# Begin Source File

SOURCE=.\res\NSys2D.ico
# End Source File
# Begin Source File

SOURCE=.\res\NSys2D.rc2
# End Source File
# Begin Source File

SOURCE=.\Res\output.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\script.bmp
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
# Section NSys2D : {9F6AA700-D188-11CD-AD48-00AA003C9CB6}
# 	2:5:Class:CRowCursor
# 	2:10:HeaderFile:rowcursor.h
# 	2:8:ImplFile:rowcursor.cpp
# End Section
# Section NSys2D : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid
# 	2:10:HeaderFile:msflexgrid.h
# 	2:8:ImplFile:msflexgrid.cpp
# End Section
# Section NSys2D : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid.h
# 	2:16:DefaultSinkClass:CMSFlexGrid
# End Section
