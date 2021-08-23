# Microsoft Developer Studio Project File - Name="NSys2D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=NSys2D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NSys2D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NSys2D.mak" CFG="NSys2D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NSys2D - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NSys2D - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NSys2D - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "NSys2D - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"StdAfx.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "NSys2D - Win32 Release"
# Name "NSys2D - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AlgolMatr.cpp
# End Source File
# Begin Source File

SOURCE=.\ArraySource.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorButton.cpp
# End Source File
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

SOURCE=.\ConvertToDlg.cpp
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

SOURCE=.\DemferPtr.cpp
# End Source File
# Begin Source File

SOURCE=.\DescriptionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Elem.cpp
# End Source File
# Begin Source File

SOURCE=.\ElemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EqualDegrees.cpp
# End Source File
# Begin Source File

SOURCE=.\EVMDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ExprSource.cpp
# End Source File
# Begin Source File

SOURCE=.\FileSource.cpp
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

SOURCE=.\GraphDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphicView.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphProp.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphTimeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupPreviewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HardRod.cpp
# End Source File
# Begin Source File

SOURCE=.\HardRodDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HardRodPtr.cpp
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

SOURCE=.\KnotPtr.cpp
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

SOURCE=.\MassPtr.cpp
# End Source File
# Begin Source File

SOURCE=.\Matr.cpp
# End Source File
# Begin Source File

SOURCE=.\MatrPtr.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshElemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MovieFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MovieParams.cpp
# End Source File
# Begin Source File

SOURCE=.\MovieView.cpp
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\NewGroupDlg.cpp
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

SOURCE=.\OutputBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputView.cpp
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

SOURCE=.\Rod.cpp
# End Source File
# Begin Source File

SOURCE=.\RodDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RodPtr.cpp
# End Source File
# Begin Source File

SOURCE=.\rowcursor.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptObjectSource.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptPtrSource.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptSource.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptView.cpp
# End Source File
# Begin Source File

SOURCE=.\Sheme.cpp
# End Source File
# Begin Source File

SOURCE=.\ShemeDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ShemeExpr.cpp
# End Source File
# Begin Source File

SOURCE=.\ShemeFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ShemeGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\ShemePtr.cpp
# End Source File
# Begin Source File

SOURCE=.\ShemeVarNewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ShemeVars.cpp
# End Source File
# Begin Source File

SOURCE=.\ShemeVarsTable.cpp
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

SOURCE=.\SpringPtr.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\TypeGraphDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\UserFuncSource.cpp
# End Source File
# Begin Source File

SOURCE=.\ValueSource.cpp
# End Source File
# Begin Source File

SOURCE=.\VariablesSource.cpp
# End Source File
# Begin Source File

SOURCE=.\VarTablesSource.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewStyles.cpp
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

SOURCE=.\ColorButton.h
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

SOURCE=.\DescriptionDlg.h
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

SOURCE=.\GraphDlg.h
# End Source File
# Begin Source File

SOURCE=.\GraphFrm.h
# End Source File
# Begin Source File

SOURCE=.\GraphicView.h
# End Source File
# Begin Source File

SOURCE=.\GraphListBox.h
# End Source File
# Begin Source File

SOURCE=.\GraphProp.h
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

SOURCE=.\MovieFrame.h
# End Source File
# Begin Source File

SOURCE=.\MovieParams.h
# End Source File
# Begin Source File

SOURCE=.\MovieView.h
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

SOURCE=.\ShemeExpr.h
# End Source File
# Begin Source File

SOURCE=.\ShemeFrm.h
# End Source File
# Begin Source File

SOURCE=.\ShemeGroup.h
# End Source File
# Begin Source File

SOURCE=.\ShemePtr.h
# End Source File
# Begin Source File

SOURCE=.\ShemeVarNewDlg.h
# End Source File
# Begin Source File

SOURCE=.\ShemeVars.h
# End Source File
# Begin Source File

SOURCE=.\ShemeVarsTable.h
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

SOURCE=.\StdAfxMy.h
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

SOURCE=.\res\bitmap_1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_6.bmp
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

SOURCE=.\res\cursor2.cur
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

SOURCE=.\res\idr_form.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_grap.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_movi.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_outp.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_scri.ico
# End Source File
# Begin Source File

SOURCE=.\res\movie.bmp
# End Source File
# Begin Source File

SOURCE=.\res\NSys2D.ico
# End Source File
# Begin Source File

SOURCE=.\res\NSys2D.rc2
# End Source File
# Begin Source File

SOURCE=.\res\output.bmp
# End Source File
# Begin Source File

SOURCE=.\res\script.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShemeDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\ShemeDoc2.ico
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

SOURCE=.\res\X3.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\NSys2D.reg
# End Source File
# End Target
# End Project
