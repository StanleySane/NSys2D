# Microsoft Developer Studio Generated NMAKE File, Based on NSys2D.dsp
!IF "$(CFG)" == ""
CFG=NSys2D - Win32 debug
!MESSAGE No configuration specified. Defaulting to NSys2D - Win32 debug.
!ENDIF 

!IF "$(CFG)" != "NSys2D - Win32 debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NSys2D.mak" CFG="NSys2D - Win32 debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NSys2D - Win32 debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\NSys2D.exe"

!ELSE 

ALL : "$(OUTDIR)\NSys2D.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ComboBox_ConnectType.obj"
	-@erase "$(INTDIR)\ComboBox_FixedType.obj"
	-@erase "$(INTDIR)\Complex.obj"
	-@erase "$(INTDIR)\ComplexMatr.obj"
	-@erase "$(INTDIR)\ComplexSpectr.obj"
	-@erase "$(INTDIR)\ComplexSpectrDlg.obj"
	-@erase "$(INTDIR)\CoordD.obj"
	-@erase "$(INTDIR)\Demf.obj"
	-@erase "$(INTDIR)\DemfDlg.obj"
	-@erase "$(INTDIR)\Elem.obj"
	-@erase "$(INTDIR)\ElemDlg.obj"
	-@erase "$(INTDIR)\Expression.obj"
	-@erase "$(INTDIR)\FormsFrame.obj"
	-@erase "$(INTDIR)\FormsView.obj"
	-@erase "$(INTDIR)\FreqDlg.obj"
	-@erase "$(INTDIR)\FreqParam.obj"
	-@erase "$(INTDIR)\FreqViewDlg.obj"
	-@erase "$(INTDIR)\GraphFrm.obj"
	-@erase "$(INTDIR)\GraphicView.obj"
	-@erase "$(INTDIR)\GraphTimeDlg.obj"
	-@erase "$(INTDIR)\GraphView.obj"
	-@erase "$(INTDIR)\Knot.obj"
	-@erase "$(INTDIR)\KnotDlg.obj"
	-@erase "$(INTDIR)\KnotPropertyFrame.obj"
	-@erase "$(INTDIR)\KnotPropertyPage1.obj"
	-@erase "$(INTDIR)\KnotPropertySheet.obj"
	-@erase "$(INTDIR)\KnotSpectr.obj"
	-@erase "$(INTDIR)\ListKnot.obj"
	-@erase "$(INTDIR)\ListSpectr.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Mass.obj"
	-@erase "$(INTDIR)\MassDlg.obj"
	-@erase "$(INTDIR)\Matr.obj"
	-@erase "$(INTDIR)\msflexgrid.obj"
	-@erase "$(INTDIR)\NSys2D.obj"
	-@erase "$(INTDIR)\NSys2D.pch"
	-@erase "$(INTDIR)\NSys2D.res"
	-@erase "$(INTDIR)\ObjectSheme.obj"
	-@erase "$(INTDIR)\ParamIntegr.obj"
	-@erase "$(INTDIR)\ParamTime.obj"
	-@erase "$(INTDIR)\ParamView.obj"
	-@erase "$(INTDIR)\PreCalcDlg.obj"
	-@erase "$(INTDIR)\ProgressDlg.obj"
	-@erase "$(INTDIR)\Result.obj"
	-@erase "$(INTDIR)\Rod.obj"
	-@erase "$(INTDIR)\RodDlg.obj"
	-@erase "$(INTDIR)\rowcursor.obj"
	-@erase "$(INTDIR)\ShemeDoc.obj"
	-@erase "$(INTDIR)\ShemeFrm.obj"
	-@erase "$(INTDIR)\ShemeView.obj"
	-@erase "$(INTDIR)\SpectrDlg.obj"
	-@erase "$(INTDIR)\SpectrParam.obj"
	-@erase "$(INTDIR)\Spring.obj"
	-@erase "$(INTDIR)\SpringDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TypeGraphDlg.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\NSys2D.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NSys2D.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\NSys2D.pdb" /machine:I386 /out:"$(OUTDIR)\NSys2D.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ComboBox_ConnectType.obj" \
	"$(INTDIR)\ComboBox_FixedType.obj" \
	"$(INTDIR)\Complex.obj" \
	"$(INTDIR)\ComplexMatr.obj" \
	"$(INTDIR)\ComplexSpectr.obj" \
	"$(INTDIR)\ComplexSpectrDlg.obj" \
	"$(INTDIR)\CoordD.obj" \
	"$(INTDIR)\Demf.obj" \
	"$(INTDIR)\DemfDlg.obj" \
	"$(INTDIR)\Elem.obj" \
	"$(INTDIR)\ElemDlg.obj" \
	"$(INTDIR)\Expression.obj" \
	"$(INTDIR)\FormsFrame.obj" \
	"$(INTDIR)\FormsView.obj" \
	"$(INTDIR)\FreqDlg.obj" \
	"$(INTDIR)\FreqParam.obj" \
	"$(INTDIR)\FreqViewDlg.obj" \
	"$(INTDIR)\GraphFrm.obj" \
	"$(INTDIR)\GraphicView.obj" \
	"$(INTDIR)\GraphTimeDlg.obj" \
	"$(INTDIR)\GraphView.obj" \
	"$(INTDIR)\Knot.obj" \
	"$(INTDIR)\KnotDlg.obj" \
	"$(INTDIR)\KnotPropertyFrame.obj" \
	"$(INTDIR)\KnotPropertyPage1.obj" \
	"$(INTDIR)\KnotPropertySheet.obj" \
	"$(INTDIR)\KnotSpectr.obj" \
	"$(INTDIR)\ListKnot.obj" \
	"$(INTDIR)\ListSpectr.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Mass.obj" \
	"$(INTDIR)\MassDlg.obj" \
	"$(INTDIR)\Matr.obj" \
	"$(INTDIR)\msflexgrid.obj" \
	"$(INTDIR)\NSys2D.obj" \
	"$(INTDIR)\NSys2D.res" \
	"$(INTDIR)\ObjectSheme.obj" \
	"$(INTDIR)\ParamIntegr.obj" \
	"$(INTDIR)\ParamTime.obj" \
	"$(INTDIR)\ParamView.obj" \
	"$(INTDIR)\PreCalcDlg.obj" \
	"$(INTDIR)\ProgressDlg.obj" \
	"$(INTDIR)\Result.obj" \
	"$(INTDIR)\Rod.obj" \
	"$(INTDIR)\RodDlg.obj" \
	"$(INTDIR)\rowcursor.obj" \
	"$(INTDIR)\ShemeDoc.obj" \
	"$(INTDIR)\ShemeFrm.obj" \
	"$(INTDIR)\ShemeView.obj" \
	"$(INTDIR)\SpectrDlg.obj" \
	"$(INTDIR)\SpectrParam.obj" \
	"$(INTDIR)\Spring.obj" \
	"$(INTDIR)\SpringDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TypeGraphDlg.obj"

"$(OUTDIR)\NSys2D.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

CPP_PROJ=/nologo /G5 /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /Fp"$(INTDIR)\NSys2D.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL" 
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\NSys2D.res" /d "NDEBUG" /d "_AFXDLL" 

!IF "$(CFG)" == "NSys2D - Win32 debug"
SOURCE=.\ComboBox_ConnectType.cpp
DEP_CPP_COMBO=\
	".\ComboBox_ConnectType.h"\
	".\NSys2D.h"\
	

"$(INTDIR)\ComboBox_ConnectType.obj" : $(SOURCE) $(DEP_CPP_COMBO) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\ComboBox_FixedType.cpp
DEP_CPP_COMBOB=\
	".\ComboBox_FixedType.h"\
	".\NSys2D.h"\
	

"$(INTDIR)\ComboBox_FixedType.obj" : $(SOURCE) $(DEP_CPP_COMBOB) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\Complex.cpp
DEP_CPP_COMPL=\
	".\Complex.h"\
	".\NSys2D.h"\
	

"$(INTDIR)\Complex.obj" : $(SOURCE) $(DEP_CPP_COMPL) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\ComplexMatr.cpp
DEP_CPP_COMPLE=\
	".\Complex.h"\
	".\ComplexMatr.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	

"$(INTDIR)\ComplexMatr.obj" : $(SOURCE) $(DEP_CPP_COMPLE) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\ComplexSpectr.cpp
DEP_CPP_COMPLEX=\
	".\ComplexSpectr.h"\
	".\CoordD.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\ComplexSpectr.obj" : $(SOURCE) $(DEP_CPP_COMPLEX) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\ComplexSpectrDlg.cpp
DEP_CPP_COMPLEXS=\
	".\ComplexSpectr.h"\
	".\ComplexSpectrDlg.h"\
	".\CoordD.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\ListKnot.h"\
	".\ListSpectr.h"\
	".\Matr.h"\
	".\msflexgrid.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\ComplexSpectrDlg.obj" : $(SOURCE) $(DEP_CPP_COMPLEXS) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\CoordD.cpp
DEP_CPP_COORD=\
	".\CoordD.h"\
	".\NSys2D.h"\
	

"$(INTDIR)\CoordD.obj" : $(SOURCE) $(DEP_CPP_COORD) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\Demf.cpp
DEP_CPP_DEMF_=\
	".\CoordD.h"\
	".\Demf.h"\
	".\DemfDlg.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\ListKnot.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\Demf.obj" : $(SOURCE) $(DEP_CPP_DEMF_) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\DemfDlg.cpp
DEP_CPP_DEMFD=\
	".\ComboBox_FixedType.h"\
	".\CoordD.h"\
	".\Demf.h"\
	".\DemfDlg.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\KnotDlg.h"\
	".\ListKnot.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\DemfDlg.obj" : $(SOURCE) $(DEP_CPP_DEMFD) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\Elem.cpp
DEP_CPP_ELEM_=\
	".\CoordD.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\ListKnot.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\Elem.obj" : $(SOURCE) $(DEP_CPP_ELEM_) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\ElemDlg.cpp
DEP_CPP_ELEMD=\
	".\CoordD.h"\
	".\Elem.h"\
	".\ElemDlg.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\ListKnot.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\ElemDlg.obj" : $(SOURCE) $(DEP_CPP_ELEMD) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\Expression.cpp
DEP_CPP_EXPRE=\
	".\Expression.h"\
	

"$(INTDIR)\Expression.obj" : $(SOURCE) $(DEP_CPP_EXPRE) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\FormsFrame.cpp
DEP_CPP_FORMS=\
	".\FormsFrame.h"\
	".\NSys2D.h"\
	

"$(INTDIR)\FormsFrame.obj" : $(SOURCE) $(DEP_CPP_FORMS) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\FormsView.cpp
DEP_CPP_FORMSV=\
	".\ComboBox_FixedType.h"\
	".\ComplexSpectr.h"\
	".\CoordD.h"\
	".\Demf.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\FormsView.h"\
	".\FreqParam.h"\
	".\Knot.h"\
	".\KnotPropertyFrame.h"\
	".\KnotPropertyPage1.h"\
	".\KnotPropertySheet.h"\
	".\ListKnot.h"\
	".\ListSpectr.h"\
	".\Mass.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamIntegr.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\ProgressDlg.h"\
	".\Rod.h"\
	".\ShemeDoc.h"\
	".\SpectrParam.h"\
	".\Spring.h"\
	

"$(INTDIR)\FormsView.obj" : $(SOURCE) $(DEP_CPP_FORMSV) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\FreqDlg.cpp
DEP_CPP_FREQD=\
	".\CoordD.h"\
	".\Expression.h"\
	".\FreqDlg.h"\
	".\FreqParam.h"\
	".\Knot.h"\
	".\ListKnot.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\FreqDlg.obj" : $(SOURCE) $(DEP_CPP_FREQD) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\FreqParam.cpp
DEP_CPP_FREQP=\
	".\CoordD.h"\
	".\Expression.h"\
	".\FreqParam.h"\
	".\Knot.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\FreqParam.obj" : $(SOURCE) $(DEP_CPP_FREQP) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\FreqViewDlg.cpp
DEP_CPP_FREQV=\
	".\FreqViewDlg.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	

"$(INTDIR)\FreqViewDlg.obj" : $(SOURCE) $(DEP_CPP_FREQV) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\GraphFrm.cpp
DEP_CPP_GRAPH=\
	".\GraphFrm.h"\
	".\NSys2D.h"\
	

"$(INTDIR)\GraphFrm.obj" : $(SOURCE) $(DEP_CPP_GRAPH) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\GraphicView.cpp
DEP_CPP_GRAPHI=\
	".\ComboBox_FixedType.h"\
	".\ComplexSpectr.h"\
	".\CoordD.h"\
	".\Demf.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\FreqParam.h"\
	".\GraphicView.h"\
	".\Knot.h"\
	".\KnotPropertyFrame.h"\
	".\KnotPropertyPage1.h"\
	".\KnotPropertySheet.h"\
	".\ListKnot.h"\
	".\ListSpectr.h"\
	".\Mass.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamIntegr.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\ProgressDlg.h"\
	".\Rod.h"\
	".\ShemeDoc.h"\
	".\SpectrParam.h"\
	".\Spring.h"\
	

"$(INTDIR)\GraphicView.obj" : $(SOURCE) $(DEP_CPP_GRAPHI) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\GraphTimeDlg.cpp
DEP_CPP_GRAPHT=\
	".\Expression.h"\
	".\GraphTimeDlg.h"\
	".\NSys2D.h"\
	".\ParamTime.h"\
	

"$(INTDIR)\GraphTimeDlg.obj" : $(SOURCE) $(DEP_CPP_GRAPHT) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\GraphView.cpp
DEP_CPP_GRAPHV=\
	".\ComboBox_FixedType.h"\
	".\ComplexSpectr.h"\
	".\CoordD.h"\
	".\Demf.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\FreqParam.h"\
	".\GraphFrm.h"\
	".\GraphView.h"\
	".\Knot.h"\
	".\KnotPropertyFrame.h"\
	".\KnotPropertyPage1.h"\
	".\KnotPropertySheet.h"\
	".\ListKnot.h"\
	".\ListSpectr.h"\
	".\Mass.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamIntegr.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\ProgressDlg.h"\
	".\Rod.h"\
	".\ShemeDoc.h"\
	".\SpectrParam.h"\
	".\Spring.h"\
	

"$(INTDIR)\GraphView.obj" : $(SOURCE) $(DEP_CPP_GRAPHV) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\Knot.cpp
DEP_CPP_KNOT_=\
	".\ComboBox_FixedType.h"\
	".\ComplexSpectr.h"\
	".\CoordD.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\KnotPropertyPage1.h"\
	".\KnotPropertySheet.h"\
	".\ListKnot.h"\
	".\ListSpectr.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\Knot.obj" : $(SOURCE) $(DEP_CPP_KNOT_) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\KnotDlg.cpp
DEP_CPP_KNOTD=\
	".\ComboBox_FixedType.h"\
	".\CoordD.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\KnotDlg.h"\
	".\ListKnot.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\KnotDlg.obj" : $(SOURCE) $(DEP_CPP_KNOTD) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\KnotPropertyFrame.cpp
DEP_CPP_KNOTP=\
	".\ComboBox_FixedType.h"\
	".\ComplexSpectr.h"\
	".\CoordD.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\KnotPropertyFrame.h"\
	".\KnotPropertyPage1.h"\
	".\KnotPropertySheet.h"\
	".\ListKnot.h"\
	".\ListSpectr.h"\
	".\Matr.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\KnotPropertyFrame.obj" : $(SOURCE) $(DEP_CPP_KNOTP) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\KnotPropertyPage1.cpp
DEP_CPP_KNOTPR=\
	".\ComboBox_FixedType.h"\
	".\ComplexSpectr.h"\
	".\ComplexSpectrDlg.h"\
	".\CoordD.h"\
	".\Expression.h"\
	".\GraphFrm.h"\
	".\GraphicView.h"\
	".\GraphTimeDlg.h"\
	".\Knot.h"\
	".\KnotPropertyPage1.h"\
	".\ListKnot.h"\
	".\ListSpectr.h"\
	".\Matr.h"\
	".\msflexgrid.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\ProgressDlg.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\KnotPropertyPage1.obj" : $(SOURCE) $(DEP_CPP_KNOTPR) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\KnotPropertySheet.cpp
DEP_CPP_KNOTPRO=\
	".\ComboBox_FixedType.h"\
	".\ComplexSpectr.h"\
	".\CoordD.h"\
	".\Demf.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\FreqParam.h"\
	".\Knot.h"\
	".\KnotPropertyFrame.h"\
	".\KnotPropertyPage1.h"\
	".\KnotPropertySheet.h"\
	".\ListKnot.h"\
	".\ListSpectr.h"\
	".\Mass.h"\
	".\Matr.h"\
	".\ObjectSheme.h"\
	".\ParamIntegr.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\ProgressDlg.h"\
	".\Rod.h"\
	".\ShemeDoc.h"\
	".\SpectrParam.h"\
	".\Spring.h"\
	

"$(INTDIR)\KnotPropertySheet.obj" : $(SOURCE) $(DEP_CPP_KNOTPRO) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\KnotSpectr.cpp
DEP_CPP_KNOTS=\
	".\CoordD.h"\
	".\Expression.h"\
	".\GraphFrm.h"\
	".\GraphicView.h"\
	".\Knot.h"\
	".\KnotSpectr.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\ProgressDlg.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\KnotSpectr.obj" : $(SOURCE) $(DEP_CPP_KNOTS) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\ListKnot.cpp
DEP_CPP_LISTK=\
	".\CoordD.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\ListKnot.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\ListKnot.obj" : $(SOURCE) $(DEP_CPP_LISTK) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\ListSpectr.cpp
DEP_CPP_LISTS=\
	".\ComplexSpectr.h"\
	".\CoordD.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\ListSpectr.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\ListSpectr.obj" : $(SOURCE) $(DEP_CPP_LISTS) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\NSys2D.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\Mass.cpp
DEP_CPP_MASS_=\
	".\CoordD.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\ListKnot.h"\
	".\Mass.h"\
	".\MassDlg.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\Mass.obj" : $(SOURCE) $(DEP_CPP_MASS_) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\MassDlg.cpp
DEP_CPP_MASSD=\
	".\CoordD.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\ListKnot.h"\
	".\Mass.h"\
	".\MassDlg.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\MassDlg.obj" : $(SOURCE) $(DEP_CPP_MASSD) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\Matr.cpp
DEP_CPP_MATR_=\
	".\Matr.h"\
	".\NSys2D.h"\
	

"$(INTDIR)\Matr.obj" : $(SOURCE) $(DEP_CPP_MATR_) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\msflexgrid.cpp
DEP_CPP_MSFLE=\
	".\msflexgrid.h"\
	".\rowcursor.h"\
	

"$(INTDIR)\msflexgrid.obj" : $(SOURCE) $(DEP_CPP_MSFLE) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\NSys2D.cpp
DEP_CPP_NSYS2=\
	".\ComboBox_FixedType.h"\
	".\ComplexSpectr.h"\
	".\CoordD.h"\
	".\Demf.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\FormsFrame.h"\
	".\FormsView.h"\
	".\FreqParam.h"\
	".\GraphFrm.h"\
	".\GraphicView.h"\
	".\Knot.h"\
	".\KnotPropertyFrame.h"\
	".\KnotPropertyPage1.h"\
	".\KnotPropertySheet.h"\
	".\ListKnot.h"\
	".\ListSpectr.h"\
	".\MainFrm.h"\
	".\Mass.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamIntegr.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\ProgressDlg.h"\
	".\Rod.h"\
	".\ShemeDoc.h"\
	".\ShemeFrm.h"\
	".\ShemeView.h"\
	".\SpectrParam.h"\
	".\Spring.h"\
	

"$(INTDIR)\NSys2D.obj" : $(SOURCE) $(DEP_CPP_NSYS2) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\NSys2D.rc
DEP_RSC_NSYS2D=\
	".\arrow.cur"\
	".\res\bitmap1.bmp"\
	".\res\bitmap2.bmp"\
	".\res\bitmap3.bmp"\
	".\res\bitmap4.bmp"\
	".\res\bitmap_x.bmp"\
	".\res\bmp00001.bmp"\
	".\res\bmp00002.bmp"\
	".\res\bmp00003.bmp"\
	".\res\bmp00004.bmp"\
	".\res\bmp00005.bmp"\
	".\res\bmp00006.bmp"\
	".\res\bmp00007.bmp"\
	".\res\bmp00008.bmp"\
	".\res\formstyp.bmp"\
	".\res\icon2.ico"\
	".\res\idr_grap.ico"\
	".\res\NSys2D.ico"\
	".\res\NSys2D.rc2"\
	".\res\Toolbar.bmp"\
	".\res\toolbar1.bmp"\
	".\resource.hm"\
	

"$(INTDIR)\NSys2D.res" : $(SOURCE) $(DEP_RSC_NSYS2D) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ObjectSheme.cpp
DEP_CPP_OBJEC=\
	".\CoordD.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamView.h"\
	

"$(INTDIR)\ObjectSheme.obj" : $(SOURCE) $(DEP_CPP_OBJEC) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\ParamIntegr.cpp
DEP_CPP_PARAM=\
	".\NSys2D.h"\
	".\ParamIntegr.h"\
	

"$(INTDIR)\ParamIntegr.obj" : $(SOURCE) $(DEP_CPP_PARAM) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\ParamTime.cpp
DEP_CPP_PARAMT=\
	".\NSys2D.h"\
	".\ParamTime.h"\
	

"$(INTDIR)\ParamTime.obj" : $(SOURCE) $(DEP_CPP_PARAMT) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\ParamView.cpp
DEP_CPP_PARAMV=\
	".\CoordD.h"\
	".\NSys2D.h"\
	".\ParamView.h"\
	

"$(INTDIR)\ParamView.obj" : $(SOURCE) $(DEP_CPP_PARAMV) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\PreCalcDlg.cpp
DEP_CPP_PRECA=\
	".\Expression.h"\
	".\NSys2D.h"\
	".\ParamIntegr.h"\
	".\PreCalcDlg.h"\
	

"$(INTDIR)\PreCalcDlg.obj" : $(SOURCE) $(DEP_CPP_PRECA) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\ProgressDlg.cpp
DEP_CPP_PROGR=\
	".\NSys2D.h"\
	".\ProgressDlg.h"\
	

"$(INTDIR)\ProgressDlg.obj" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\Result.cpp
DEP_CPP_RESUL=\
	".\NSys2D.h"\
	".\Result.h"\
	

"$(INTDIR)\Result.obj" : $(SOURCE) $(DEP_CPP_RESUL) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\Rod.cpp
DEP_CPP_ROD_C=\
	".\ComboBox_ConnectType.h"\
	".\CoordD.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\ListKnot.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\Rod.h"\
	".\RodDlg.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\Rod.obj" : $(SOURCE) $(DEP_CPP_ROD_C) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\RodDlg.cpp
DEP_CPP_RODDL=\
	".\ComboBox_ConnectType.h"\
	".\ComboBox_FixedType.h"\
	".\CoordD.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\KnotDlg.h"\
	".\ListKnot.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\Rod.h"\
	".\RodDlg.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\RodDlg.obj" : $(SOURCE) $(DEP_CPP_RODDL) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\rowcursor.cpp
DEP_CPP_ROWCU=\
	".\rowcursor.h"\
	

"$(INTDIR)\rowcursor.obj" : $(SOURCE) $(DEP_CPP_ROWCU) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\ShemeDoc.cpp
DEP_CPP_SHEME=\
	".\ComboBox_FixedType.h"\
	".\Complex.h"\
	".\ComplexMatr.h"\
	".\ComplexSpectr.h"\
	".\ComplexSpectrDlg.h"\
	".\CoordD.h"\
	".\Demf.h"\
	".\Elem.h"\
	".\ElemDlg.h"\
	".\Expression.h"\
	".\FormsFrame.h"\
	".\FormsView.h"\
	".\FreqParam.h"\
	".\FreqViewDlg.h"\
	".\Knot.h"\
	".\KnotPropertyFrame.h"\
	".\KnotPropertyPage1.h"\
	".\KnotPropertySheet.h"\
	".\ListKnot.h"\
	".\ListSpectr.h"\
	".\Mass.h"\
	".\Matr.h"\
	".\msflexgrid.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamIntegr.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\PreCalcDlg.h"\
	".\ProgressDlg.h"\
	".\Rod.h"\
	".\ShemeDoc.h"\
	".\SpectrParam.h"\
	".\Spring.h"\
	

"$(INTDIR)\ShemeDoc.obj" : $(SOURCE) $(DEP_CPP_SHEME) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\ShemeFrm.cpp
DEP_CPP_SHEMEF=\
	".\NSys2D.h"\
	".\ShemeFrm.h"\
	

"$(INTDIR)\ShemeFrm.obj" : $(SOURCE) $(DEP_CPP_SHEMEF) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\ShemeView.cpp
DEP_CPP_SHEMEV=\
	".\ComboBox_FixedType.h"\
	".\Complex.h"\
	".\ComplexMatr.h"\
	".\ComplexSpectr.h"\
	".\CoordD.h"\
	".\Demf.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\FreqDlg.h"\
	".\FreqParam.h"\
	".\GraphFrm.h"\
	".\GraphicView.h"\
	".\Knot.h"\
	".\KnotPropertyFrame.h"\
	".\KnotPropertyPage1.h"\
	".\KnotPropertySheet.h"\
	".\ListKnot.h"\
	".\ListSpectr.h"\
	".\Mass.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamIntegr.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\ProgressDlg.h"\
	".\Rod.h"\
	".\ShemeDoc.h"\
	".\ShemeView.h"\
	".\SpectrDlg.h"\
	".\SpectrParam.h"\
	".\Spring.h"\
	".\TypeGraphDlg.h"\
	

"$(INTDIR)\ShemeView.obj" : $(SOURCE) $(DEP_CPP_SHEMEV) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\SpectrDlg.cpp
DEP_CPP_SPECT=\
	".\CoordD.h"\
	".\Expression.h"\
	".\FreqParam.h"\
	".\Knot.h"\
	".\ListKnot.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrDlg.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\SpectrDlg.obj" : $(SOURCE) $(DEP_CPP_SPECT) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\SpectrParam.cpp
DEP_CPP_SPECTR=\
	".\Expression.h"\
	".\KnotSpectr.h"\
	".\NSys2D.h"\
	".\SpectrParam.h"\
	

"$(INTDIR)\SpectrParam.obj" : $(SOURCE) $(DEP_CPP_SPECTR) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\Spring.cpp
DEP_CPP_SPRIN=\
	".\CoordD.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\ListKnot.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	".\Spring.h"\
	".\SpringDlg.h"\
	

"$(INTDIR)\Spring.obj" : $(SOURCE) $(DEP_CPP_SPRIN) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\SpringDlg.cpp
DEP_CPP_SPRING=\
	".\CoordD.h"\
	".\Elem.h"\
	".\Expression.h"\
	".\Knot.h"\
	".\ListKnot.h"\
	".\Matr.h"\
	".\NSys2D.h"\
	".\ObjectSheme.h"\
	".\ParamTime.h"\
	".\ParamView.h"\
	".\SpectrParam.h"\
	".\Spring.h"\
	".\SpringDlg.h"\
	

"$(INTDIR)\SpringDlg.obj" : $(SOURCE) $(DEP_CPP_SPRING) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
CPP_SWITCHES=/nologo /G5 /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\NSys2D.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\NSys2D.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


SOURCE=.\TypeGraphDlg.cpp
DEP_CPP_TYPEG=\
	".\NSys2D.h"\
	".\TypeGraphDlg.h"\
	

"$(INTDIR)\TypeGraphDlg.obj" : $(SOURCE) $(DEP_CPP_TYPEG) "$(INTDIR)"\
 "$(INTDIR)\NSys2D.pch"



!ENDIF 

