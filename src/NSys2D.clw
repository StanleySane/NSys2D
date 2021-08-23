; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CShemeView
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "NSys2D.h"
ODLFile=NSys2D.odl
LastPage=0

ClassCount=57
Class1=CNSys2DApp
Class2=CShemeDoc
Class3=CShemeView
Class4=CMainFrame
Class7=CGraphFrame
Class8=CScriptDoc

ResourceCount=73
Resource1=IDD_KNOTPAGE3
Resource2=IDR_SHEMETYPE1
Resource3=IDR_NSYS2DTYPE
Resource4=IDR_FORMSTYPE
Resource5=IDD_KNOTSPECTR
Class9=CScriptFrame
Class5=CAboutDlg
Class6=CShemeFrame
Resource6=IDD_DIALOGROD
Resource7=IDR_MAINFRAME
Resource8=IDR_GRAPHTYPE
Resource9=IDD_FREQDLG
Class10=CRodDlg
Class11=CKnotDlg
Class12=CComboBoxElem
Class13=CComboBox_FixedType
Class14=CComboBox_ConnectType
Resource10=IDD_KNOTPAGE2
Class15=CDemfDlg
Resource11=IDD_DIALOGCOORD
Class16=CSpringDlg
Resource12=IDD_DIALOGSPRING
Class17=CMassDlg
Resource13=IDD_FREQVIEW
Class18=CElemDlg
Class19=CScriptView
Class20=CPreCalcDlg
Class21=CMeshElemDlg
Resource14=IDD_PROGRESSDIALOG
Class22=CKnotPropertySheet
Class23=CKnotPropertyFrame
Class24=CKnotPropertyPage1
Class25=CKnotPropertyPage2
Class26=CKnotPropertyPage4
Class27=CTypeGraphDlg
Resource15=IDD_DIALOGMASS
Resource16=IDD_DIALOGELEM
Resource17=IDD_DIALOGPRECALC
Class28=CProgressDlg
Resource18=IDD_DIALOG4
Class29=CKnotPropertyPage3
Resource19=IDR_POPUPMENUSHEME
Class30=CGraphicView
Resource20=IDD_COMPLEXSPECTR
Class31=CFreqDlg
Resource21=IDD_KNOTPAGE4
Class32=COutputFrame
Class33=COutputView
Class34=CFormsView
Resource22=IDD_KNOTPAGE1
Class35=CFormsFrame
Resource23=IDD_DIALOGDEMF
Resource24=IDD_SHEME_VARS (Russian)
Class36=CConvertToDlg
Class37=CKnotSpectr
Resource25=IDD_SPECTRDLG
Class38=CComplexSpectrDlg
Resource26=IDD_DIALOGTYPEGRAPH
Class39=CSpectrDlg
Resource27=IDD_ABOUTBOX
Class40=CGraphTimeDlg
Resource28=IDR_SHEMETYPE
Resource29=IDD_DESCRIPTION (Russian)
Resource30=IDD_KNOTPAGE2 (Russian)
Resource31=IDR_MAINFRAME (Russian)
Resource32=IDD_DIALOG4 (Russian)
Resource33=IDD_ABOUTBOX (Russian)
Resource34=IDD_GROUP_LIST (Russian)
Resource35=IDD_GROUP_NEW (Russian)
Resource36=IDR_MOVIE (Russian)
Resource37=IDD_KNOTSPECTR (Russian)
Resource38=IDD_DIALOGMASS (Russian)
Resource39=IDR_SHEMETYPE (Russian)
Resource40=IDD_MOVIE_STYLES (Russian)
Resource41=IDR_MAINFRAME (English (U.S.))
Resource42=IDD_DIALOGROD (Russian)
Resource43=IDD_DIALOGSPRING (Russian)
Resource44=IDR_OUTPUT (Russian)
Resource45=IDD_DIALOGELEM (Russian)
Resource46=IDD_VIEW_STYLES (Russian)
Resource47=IDR_POPUPMENUSHEME (Russian)
Resource48=IDD_FREQVIEW (Russian)
Resource49=IDR_FORMSTYPE (Russian)
Resource50=IDR_GRAPHTYPE (Russian)
Resource51=IDD_DIALOGPRECALC (Russian)
Resource52=IDD_COMPLEXSPECTR (Russian)
Resource53=IDD_DIALOG_MESH_ELEM (Russian)
Resource54=IDD_PROGRESSDIALOG (Russian)
Resource55=IDD_TIME_DLG (Russian)
Class41=CHardRodDlg
Class42=CEVMDialog
Resource56=IDD_KNOTPAGE4 (Russian)
Class43=CViewStyles
Resource57=IDD_GRAPHS_PROPERTIES (Russian)
Class44=CNewGroupDlg
Resource58=IDD_SPECTRDLG (Russian)
Class45=CGroupListDlg
Resource59=IDD_DIALOGDEMF (Russian)
Class46=CGroupEditDlg
Resource60=IDD_DIALOGTYPEGRAPH (Russian)
Class47=CGroupPreviewDlg
Resource61=IDD_FREQDLG (Russian)
Resource62=IDD_GRAPH_EDIT (Russian)
Resource63=IDD_DIALOGCOORD (Russian)
Resource64=IDD_SHEME_VAR_NEW (Russian)
Resource65=IDD_CONVERT_TO (Russian)
Class48=CMovieFrame
Class49=CMovieView
Resource66=IDD_KNOTPAGE1 (Russian)
Class50=CMovieParams
Resource67=IDR_SCRIPT (Russian)
Resource68=IDD_DIALOGHARDROD (Russian)
Class51=CShemeVars
Resource69=IDD_FORMS_BAR (Russian)
Class52=ShemeVarNewDlg
Resource70=IDD_KNOTPAGE3 (Russian)
Class53=CDescriptionDlg
Resource71=IDD_GROUP_EDIT (Russian)
Class54=CGraphProp
Class55=CGraphListBox
Resource72=IDD_DIALOG_GROUP_SHOW (Russian)
Class56=CGraphDlg
Class57=CColorButton
Resource73=IDD_EV_METHODS (Russian)

[CLS:CNSys2DApp]
Type=0
HeaderFile=NSys2D.h
ImplementationFile=NSys2D.cpp
Filter=N
LastObject=CNSys2DApp

[CLS:CShemeDoc]
Type=0
HeaderFile=ShemeDoc.h
ImplementationFile=ShemeDoc.cpp
Filter=W
BaseClass=CDocument
VirtualFilter=DC
LastObject=CShemeDoc

[CLS:CShemeView]
Type=0
HeaderFile=ShemeView.h
ImplementationFile=ShemeView.cpp
Filter=T
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=CShemeView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_FREEFORM_CALC
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CShemeFrame]
Type=0
HeaderFile=ShemeFrm.h
ImplementationFile=ShemeFrm.cpp
Filter=M
LastObject=ID_FILE_OPEN
BaseClass=CMDIChildWnd
VirtualFilter=mfWC

[CLS:CAboutDlg]
Type=0
HeaderFile=NSys2D.cpp
ImplementationFile=NSys2D.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308481
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308353
Control8=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_SCALEADD
Command5=ID_SCALESUB
Command6=ID_CALC
Command7=ID_SETNULL
Command8=ID_SETROD
Command9=ID_SETSPRING
Command10=ID_SETDEMF
Command11=ID_SETMASS
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_NSYS2DTYPE]
Type=1
Class=CShemeView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
CommandCount=21
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT
Command4=ID_FILE_SAVE
Command5=ID_ACCEL32874
Command6=ID_NEXT_PANE
Command7=ID_PREV_PANE
Command8=ID_CALC
CommandCount=8

[CLS:CGraphFrame]
Type=0
HeaderFile=GraphFrm.h
ImplementationFile=GraphFrm.cpp
BaseClass=CMDIChildWnd
Filter=C
LastObject=CGraphFrame
VirtualFilter=mfWC

[MNU:IDR_SHEMETYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_REFRESH
Command14=ID_ADDROD
Command15=ID_ADDDEMF
Command16=ID_ADDSPRING
Command17=ID_ADDMASS
Command18=ID_DELELEM
Command19=ID_LISTELEM
Command20=ID_CALC
Command21=ID_FREEFORM_CALC
Command22=ID_ADDGRAPH
Command23=ID_FREQ_CALC
Command24=ID_SPECTR_CALC
Command25=ID_WINDOW_CASCADE
Command26=ID_WINDOW_TILE_HORZ
Command27=ID_WINDOW_ARRANGE
Command28=ID_APP_ABOUT
CommandCount=28

[DLG:IDD_DIALOGCOORD]
Type=1
Class=CKnotDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_COMBO1,combobox,1344339987

[DLG:IDD_DIALOGROD]
Type=1
Class=CRodDlg
ControlCount=22
Control1=IDC_COMBO2,combobox,1344339971
Control2=IDC_COMBO1,combobox,1344340499
Control3=IDC_COMBO3,combobox,1344339971
Control4=IDC_COMBO4,combobox,1344340499
Control5=IDC_EDIT4,edit,1350631552
Control6=IDC_EDIT1,edit,1350631552
Control7=IDC_EDIT2,edit,1350631552
Control8=IDC_EDIT3,edit,1350631552
Control9=IDOK,button,1342242817
Control10=IDCANCEL,button,1342242816
Control11=IDC_BUTNEWKNOT,button,1342242816
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352

[MNU:IDR_POPUPMENUSHEME]
Type=1
Class=CShemeView
CommandCount=0

[CLS:CRodDlg]
Type=0
HeaderFile=RodDlg.h
ImplementationFile=RodDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT4

[CLS:CKnotDlg]
Type=0
HeaderFile=KnotDlg.h
ImplementationFile=KnotDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT2
VirtualFilter=dWC

[CLS:CComboBoxElem]
Type=0
HeaderFile=ComboBoxElem.h
ImplementationFile=ComboBoxElem.cpp
BaseClass=CComboBox
Filter=W

[CLS:CComboBox_FixedType]
Type=0
HeaderFile=ComboBox_FixedType.h
ImplementationFile=ComboBox_FixedType.cpp
BaseClass=CComboBox
Filter=W
LastObject=CComboBox_FixedType

[CLS:CComboBox_ConnectType]
Type=0
HeaderFile=ComboBox_ConnectType.h
ImplementationFile=ComboBox_ConnectType.cpp
BaseClass=CComboBox
Filter=W

[CLS:CDemfDlg]
Type=0
HeaderFile=DemfDlg.h
ImplementationFile=DemfDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CDemfDlg
VirtualFilter=dWC

[DLG:IDD_DIALOGDEMF]
Type=1
Class=CDemfDlg
ControlCount=25
Control1=IDC_COMBO2,combobox,1344339971
Control2=IDC_COMBO3,combobox,1344339971
Control3=IDC_RADIO1,button,1342308361
Control4=IDC_RADIO2,button,1342308361
Control5=IDC_RADIO3,button,1342308361
Control6=IDC_RADIO4,button,1342308361
Control7=IDC_RADIO5,button,1342308361
Control8=IDC_EDIT1,edit,1350762624
Control9=IDC_EDIT2,edit,1484980352
Control10=IDC_EDIT3,edit,1484980352
Control11=IDC_EDIT4,edit,1484980352
Control12=IDC_EDIT5,edit,1484980352
Control13=IDOK,button,1342242817
Control14=IDCANCEL,button,1342242816
Control15=IDC_BUTNEWKNOT,button,1342242816
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342177294
Control22=IDC_STATIC,static,1342177294
Control23=IDC_STATIC,static,1342177294
Control24=IDC_STATIC,static,1342177294
Control25=IDC_STATIC,static,1342177294

[DLG:IDD_DIALOGSPRING]
Type=1
Class=CSpringDlg
ControlCount=21
Control1=IDC_COMBO2,combobox,1344339971
Control2=IDC_COMBO3,combobox,1344339971
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1484849280
Control5=IDC_EDIT3,edit,1484849280
Control6=IDC_EDIT4,edit,1484849280
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816
Control9=IDC_BUTNEWKNOT,button,1342242816
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_RADIO2,button,1342308361
Control16=IDC_RADIO3,button,1342308361
Control17=IDC_RADIO1,button,1342308361
Control18=IDC_STATIC,static,1342177294
Control19=IDC_STATIC,static,1342177294
Control20=IDC_STATIC,static,1342177294
Control21=IDC_RADIO4,button,1342308361

[CLS:CSpringDlg]
Type=0
HeaderFile=SpringDlg.h
ImplementationFile=SpringDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSpringDlg

[DLG:IDD_DIALOGMASS]
Type=1
Class=CMassDlg
ControlCount=11
Control1=IDC_COMBO1,combobox,1344339971
Control2=IDC_BUTNEWKNOT,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=65535,button,1342177287
Control8=65535,button,1342177287
Control9=65535,static,1342308352
Control10=65535,static,1342308352
Control11=65535,static,1342308352

[CLS:CMassDlg]
Type=0
HeaderFile=MassDlg.h
ImplementationFile=MassDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=65535

[TB:IDR_GRAPHTYPE]
Type=1
Class=CGraphFrame
Command1=ID_AUTOSIZE
Command2=ID_GETCOORD
Command3=ID_LOADGRAPH2
Command4=ID_SAVEREZ
Command5=ID_GRAPH2
Command6=ID_CALCMAT
CommandCount=6

[DLG:IDD_DIALOGELEM]
Type=1
Class=CElemDlg
ControlCount=4
Control1=IDC_LISTCONTROL,SysListView32,1350633485
Control2=IDC_BUTTONPROP,button,1342242816
Control3=IDC_BUTTONDEL,button,1342242816
Control4=IDOK,button,1342242817

[CLS:CElemDlg]
Type=0
HeaderFile=ElemDlg.h
ImplementationFile=ElemDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CElemDlg

[DLG:IDD_DIALOGPRECALC]
Type=1
Class=CPreCalcDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT2,edit,1350631552
Control8=IDC_STATIC,button,1342177287
Control9=IDC_RADIO1,button,1342373897
Control10=IDC_RADIO2,button,1342177289
Control11=IDC_RADIO3,button,1342177289
Control12=IDC_RADIO4,button,1476395017

[CLS:CPreCalcDlg]
Type=0
HeaderFile=PreCalcDlg.h
ImplementationFile=PreCalcDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPreCalcDlg

[CLS:CKnotPropertySheet]
Type=0
HeaderFile=KnotPropertySheet.h
ImplementationFile=KnotPropertySheet.cpp
BaseClass=CPropertySheet
LastObject=CKnotPropertySheet
Filter=C
VirtualFilter=hWC

[CLS:CKnotPropertyFrame]
Type=0
HeaderFile=KnotPropertyFrame.h
ImplementationFile=KnotPropertyFrame.cpp
BaseClass=CMiniFrameWnd
Filter=T

[CLS:CKnotPropertyPage1]
Type=0
HeaderFile=KnotPropertyPage1.h
ImplementationFile=KnotPropertyPage1.cpp
BaseClass=CPropertyPage
LastObject=CKnotPropertyPage1
Filter=W
VirtualFilter=idWC

[CLS:CKnotPropertyPage2]
Type=0
HeaderFile=KnotPropertyPage1.h
ImplementationFile=KnotPropertyPage1.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CKnotPropertyPage2

[DLG:IDD_KNOTPAGE1]
Type=1
Class=CKnotPropertyPage1
ControlCount=7
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_COMBO1,combobox,1344339987

[DLG:IDD_KNOTPAGE2]
Type=1
Class=CKnotPropertyPage2
ControlCount=16
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_EDIT3,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT5,edit,1350631552
Control8=IDC_EDIT6,edit,1350631552
Control9=IDC_EDIT7,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,button,1342177287

[DLG:IDD_DIALOGTYPEGRAPH]
Type=1
Class=CTypeGraphDlg
ControlCount=24
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIO1,button,1342308361
Control5=IDC_RADIO2,button,1342177289
Control6=IDC_RADIO3,button,1342177289
Control7=IDC_RADIO4,button,1342177289
Control8=IDC_RADIO5,button,1342177289
Control9=IDC_RADIO6,button,1342177289
Control10=IDC_RADIO15,button,1342177289
Control11=IDC_RADIO16,button,1342177289
Control12=IDC_RADIO17,button,1342177289
Control13=IDC_RADIO7,button,1342177289
Control14=IDC_STATIC,button,1342177287
Control15=IDC_RADIO8,button,1342308361
Control16=IDC_RADIO9,button,1342177289
Control17=IDC_RADIO10,button,1342177289
Control18=IDC_RADIO11,button,1342177289
Control19=IDC_RADIO12,button,1342177289
Control20=IDC_RADIO13,button,1342177289
Control21=IDC_RADIO18,button,1342177289
Control22=IDC_RADIO19,button,1342177289
Control23=IDC_RADIO20,button,1342177289
Control24=IDC_RADIO14,button,1342177289

[CLS:CTypeGraphDlg]
Type=0
HeaderFile=TypeGraphDlg.h
ImplementationFile=TypeGraphDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTypeGraphDlg

[DLG:IDD_PROGRESSDIALOG]
Type=1
Class=CProgressDlg
ControlCount=2
Control1=IDCANCEL,button,1342242817
Control2=IDC_PROGRESS1,msctls_progress32,1350565888

[CLS:CProgressDlg]
Type=0
HeaderFile=ProgressDlg.h
ImplementationFile=ProgressDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_DETAILS

[DLG:IDD_KNOTPAGE3]
Type=1
Class=CKnotPropertyPage3
ControlCount=30
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,button,1342177287
Control3=IDC_CHECK1,button,1342242819
Control4=IDC_CHECK3,button,1342259203
Control5=IDC_STATIC,static,1342177280
Control6=IDC_STATIC,static,1342177280
Control7=IDC_STATIC,static,1342177280
Control8=IDC_STATIC,static,1342177280
Control9=IDC_STATIC,static,1342177280
Control10=IDC_STATIC,static,1342177280
Control11=IDC_RADIO1,button,1342373897
Control12=IDC_EDIT1,edit,1350631552
Control13=IDC_EDIT2,edit,1350631552
Control14=IDC_EDIT3,edit,1350631552
Control15=IDC_RADIO2,button,1342373897
Control16=IDC_EDIT5,edit,1350631552
Control17=IDC_RADIO5,button,1342373897
Control18=IDC_SPECTRPX,button,1342242816
Control19=IDC_CSPECPX,button,1342242816
Control20=IDC_CHECK2,button,1342242819
Control21=IDC_CHECK4,button,1342259203
Control22=IDC_RADIO3,button,1342373897
Control23=IDC_EDIT6,edit,1350631552
Control24=IDC_EDIT7,edit,1350631552
Control25=IDC_EDIT8,edit,1350631552
Control26=IDC_RADIO4,button,1342373897
Control27=IDC_EDIT10,edit,1350631552
Control28=IDC_RADIO6,button,1342373897
Control29=IDC_SPECTRPY,button,1342373888
Control30=IDC_CSPECPY,button,1342242816

[CLS:CKnotPropertyPage3]
Type=0
HeaderFile=KnotPropertyPage1.h
ImplementationFile=KnotPropertyPage1.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_CHECK1
VirtualFilter=idWC

[DLG:IDD_KNOTPAGE4]
Type=1
Class=CKnotPropertyPage4
ControlCount=30
Control1=IDC_STATIC,static,1342177280
Control2=IDC_STATIC,static,1342177280
Control3=IDC_STATIC,static,1342177280
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342177280
Control6=IDC_STATIC,static,1342177280
Control7=IDC_STATIC,static,1342177280
Control8=IDC_STATIC,button,1342177287
Control9=IDC_CHECK1,button,1342242819
Control10=IDC_CHECK3,button,1342259203
Control11=IDC_RADIO1,button,1342373897
Control12=IDC_EDIT1,edit,1350631552
Control13=IDC_EDIT2,edit,1350631552
Control14=IDC_EDIT3,edit,1350631552
Control15=IDC_RADIO2,button,1342373897
Control16=IDC_EDIT5,edit,1350631552
Control17=IDC_RADIO5,button,1342373897
Control18=IDC_BUTTON1,button,1342242816
Control19=IDC_CSPECUX,button,1342242816
Control20=IDC_CHECK2,button,1342242819
Control21=IDC_CHECK4,button,1342259203
Control22=IDC_RADIO3,button,1342373897
Control23=IDC_EDIT6,edit,1350631552
Control24=IDC_EDIT7,edit,1350631552
Control25=IDC_EDIT8,edit,1350631552
Control26=IDC_RADIO4,button,1342373897
Control27=IDC_EDIT10,edit,1350631552
Control28=IDC_RADIO6,button,1342373897
Control29=IDC_BUTTON2,button,1342242816
Control30=IDC_CSPECUY,button,1342242816

[CLS:CKnotPropertyPage4]
Type=0
HeaderFile=KnotPropertyPage1.h
ImplementationFile=KnotPropertyPage1.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_CHECK4

[CLS:CGraphicView]
Type=0
HeaderFile=GraphicView.h
ImplementationFile=GraphicView.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=ID_CALCMAT

[DLG:IDD_FREQDLG]
Type=1
Class=CFreqDlg
ControlCount=33
Control1=IDC_RADIO1,button,1342373897
Control2=IDC_RADIO2,button,1342242825
Control3=IDC_RADIO3,button,1342242825
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_EDIT2,edit,1350631552
Control6=IDC_EDIT3,edit,1350631552
Control7=IDC_CHECK1,button,1476460547
Control8=IDC_COMBO1,combobox,1344339971
Control9=IDC_RADIO4,button,1342373897
Control10=IDC_RADIO5,button,1342242825
Control11=IDC_RADIO6,button,1342242825
Control12=IDC_COMBO2,combobox,1344339971
Control13=IDC_RADIO7,button,1342373897
Control14=IDC_RADIO8,button,1342242825
Control15=IDC_RADIO9,button,1342242825
Control16=IDC_RADIO10,button,1342373897
Control17=IDC_RADIO11,button,1342242825
Control18=IDC_RADIO12,button,1342242825
Control19=IDC_RADIO13,button,1342373897
Control20=IDC_RADIO14,button,1342242825
Control21=IDOK,button,1342242817
Control22=IDCANCEL,button,1342242816
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,button,1342177287
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,button,1342177287
Control29=IDC_STATIC,button,1342177287
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,button,1342177287
Control33=IDC_STATIC,button,1342177287

[CLS:CFreqDlg]
Type=0
HeaderFile=FreqDlg.h
ImplementationFile=FreqDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFreqDlg

[DLG:IDD_FREQVIEW]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352663296

[CLS:CFormsView]
Type=0
HeaderFile=FormsView.h
ImplementationFile=FormsView.cpp
BaseClass=CScrollView
Filter=C
VirtualFilter=VWC
LastObject=CFormsView

[CLS:CFormsFrame]
Type=0
HeaderFile=FormsFrame.h
ImplementationFile=FormsFrame.cpp
BaseClass=CMDIChildWnd
Filter=M
LastObject=CFormsFrame
VirtualFilter=mfWC

[TB:IDR_FORMSTYPE]
Type=1
Class=CFormsView
Command1=ID_FREQPREW
Command2=ID_FREQNEXT
Command3=ID_MOVEADD
Command4=ID_MOVESUB
Command5=ID_UPDATEFORMS
CommandCount=5

[MNU:IDR_SHEMETYPE1]
Type=1
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=ID_REFRESH
Command11=ID_ADDROD
Command12=ID_ADDDEMF
Command13=ID_ADDSPRING
Command14=ID_ADDMASS
Command15=ID_ADDGRAPH
Command16=ID_DELELEM
Command17=ID_LISTELEM
Command18=ID_CALC
Command19=ID_FREQ_CALC
Command20=ID_FREEFORM_CALC
Command21=ID_WINDOW_CASCADE
Command22=ID_WINDOW_TILE_HORZ
Command23=ID_WINDOW_ARRANGE
Command24=ID_APP_ABOUT
CommandCount=24

[DLG:IDD_KNOTSPECTR]
Type=1
Class=CKnotSpectr
ControlCount=56
Control1=IDC_RADIO1,button,1342382089
Control2=IDC_RADIO2,button,1342251017
Control3=IDC_RADIO3,button,1342251017
Control4=IDC_RADIO4,button,1342251017
Control5=IDC_RADIO5,button,1342251017
Control6=IDC_RADIO6,button,1342242825
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_EDIT1,edit,1350631552
Control21=IDC_EDIT2,edit,1350631552
Control22=IDC_EDIT3,edit,1350631552
Control23=IDC_EDIT4,edit,1350631552
Control24=IDC_EDIT5,edit,1350631552
Control25=IDC_EDIT6,edit,1350631552
Control26=IDC_EDIT7,edit,1350631552
Control27=IDC_EDIT8,edit,1350631552
Control28=IDC_EDIT9,edit,1350631552
Control29=IDC_EDIT10,edit,1350631552
Control30=IDC_EDIT11,edit,1350631552
Control31=IDC_EDIT12,edit,1350631552
Control32=IDC_EDIT13,edit,1350631552
Control33=IDC_EDIT14,edit,1350631552
Control34=IDC_STATIC,button,1342177287
Control35=IDC_EDIT15,edit,1350631552
Control36=IDC_EDIT16,edit,1350631552
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC,button,1342177287
Control40=IDC_RADIO7,button,1342373897
Control41=IDC_RADIO8,button,1342242825
Control42=IDC_EDIT17,edit,1350631552
Control43=IDC_STATIC,button,1342177287
Control44=IDC_EDIT19,edit,1350631552
Control45=IDC_STATIC,static,1342308352
Control46=IDC_EDIT18,edit,1350631552
Control47=IDC_STATIC,static,1342308352
Control48=IDOK,button,1342242817
Control49=IDCANCEL,button,1342242816
Control50=IDC_STATIC,static,1342177294
Control51=IDC_STATIC,static,1342177294
Control52=IDC_STATIC,static,1342177294
Control53=IDC_STATIC,static,1342177294
Control54=IDC_STATIC,static,1342177294
Control55=IDC_CHECK1,button,1342242819
Control56=IDC_STATIC,static,1342308352

[CLS:CKnotSpectr]
Type=0
HeaderFile=KnotSpectr.h
ImplementationFile=KnotSpectr.cpp
BaseClass=CDialog
Filter=D
LastObject=CKnotSpectr
VirtualFilter=dWC

[DLG:IDD_COMPLEXSPECTR]
Type=1
Class=CComplexSpectrDlg
ControlCount=9
Control1=IDC_COMBO1,combobox,1344339971
Control2=IDC_COMBO2,combobox,1344339971
Control3=IDC_BUTTON2,button,1342242817
Control4=IDC_BUTTON3,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_BUTTON1,button,1342242816
Control8=IDOK,button,1342242816
Control9=IDC_MSFLEXGRID1,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816

[CLS:CComplexSpectrDlg]
Type=0
HeaderFile=ComplexSpectrDlg.h
ImplementationFile=ComplexSpectrDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CComplexSpectrDlg

[DLG:IDD_SPECTRDLG]
Type=1
Class=CSpectrDlg
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO1,combobox,1344339971
Control4=IDC_COMBO2,combobox,1344339971
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT1,edit,1350631552
Control9=IDC_EDIT2,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT3,edit,1350631552
Control15=IDC_CHECK1,button,1476460547

[CLS:CSpectrDlg]
Type=0
HeaderFile=SpectrDlg.h
ImplementationFile=SpectrDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSpectrDlg

[DLG:IDD_DIALOG4]
Type=1
Class=CGraphTimeDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT3,edit,1350631552
Control9=IDC_STATIC,button,1342177287

[CLS:CGraphTimeDlg]
Type=0
HeaderFile=GraphTimeDlg.h
ImplementationFile=GraphTimeDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

[DLG:IDD_FREQVIEW (Russian)]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352663296

[MNU:IDR_SHEMETYPE (Russian)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_AUTO_SCALE
Command14=ID_VIEW_STYLES
Command15=ID_REFRESH
Command16=ID_ADDROD
Command17=ID_ADDHARDROD
Command18=ID_ADDDEMF
Command19=ID_ADDSPRING
Command20=ID_ADDMASS
Command21=ID_DELELEM
Command22=ID_MESH_ELEM
Command23=ID_CONVERT_TO
Command24=ID_LISTELEM
Command25=ID_SHEME_VARS
Command26=ID_FREE_NUMS
Command27=ID_DESCRIPT
Command28=ID_GROUP_CLICK_ELEMS
Command29=ID_GROUP_CLICK_KNOTS
Command30=ID_ELEMGROUP_DEL
Command31=ID_ELEMGROUP_PROP
Command32=ID_GROUP_CONVERT_TO
Command33=ID_ALL_RODS
Command34=ID_ALL_HARDRODS
Command35=ID_ALL_DEMF
Command36=ID_ALL_SPRINGS
Command37=ID_ALL_MASSES
Command38=ID_AUTOCORRECT
Command39=ID_TOOL_TIPS
Command40=ID_CALC
Command41=ID_FREEFORM_CALC
Command42=ID_MAKE_MOVIE
Command43=ID_SHEME_PARAMS
Command44=ID_ADDGRAPH
Command45=ID_FREQ_CALC
Command46=ID_SPECTR_CALC
Command47=ID_GROUP_NEW
Command48=ID_GROUP_LIST
Command49=ID_GROUP_PREVIEW
Command50=ID_WINDOW_CASCADE
Command51=ID_WINDOW_TILE_HORZ
Command52=ID_WINDOW_ARRANGE
Command53=ID_APP_ABOUT
CommandCount=53

[MNU:IDR_POPUPMENUSHEME (Russian)]
Type=1
Class=?
CommandCount=0

[MNU:IDR_MAINFRAME (Russian)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[DLG:IDD_DIALOGCOORD (Russian)]
Type=1
Class=CKnotDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_COMBO1,combobox,1344339987

[DLG:IDD_DIALOGROD (Russian)]
Type=1
Class=CRodDlg
ControlCount=22
Control1=IDC_COMBO2,combobox,1344339971
Control2=IDC_COMBO1,combobox,1344340499
Control3=IDC_COMBO3,combobox,1344339971
Control4=IDC_COMBO4,combobox,1344340499
Control5=IDC_EDIT4,edit,1350631552
Control6=IDC_EDIT1,edit,1350631552
Control7=IDC_EDIT2,edit,1350631552
Control8=IDC_EDIT3,edit,1350631552
Control9=IDOK,button,1342242817
Control10=IDCANCEL,button,1342242816
Control11=IDC_BUTNEWKNOT,button,1342242816
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOGDEMF (Russian)]
Type=1
Class=CDemfDlg
ControlCount=25
Control1=IDC_COMBO2,combobox,1344339971
Control2=IDC_COMBO3,combobox,1344339971
Control3=IDC_RADIO1,button,1342308361
Control4=IDC_RADIO2,button,1342308361
Control5=IDC_RADIO3,button,1342308361
Control6=IDC_RADIO4,button,1342308361
Control7=IDC_RADIO5,button,1342308361
Control8=IDC_EDIT1,edit,1350762624
Control9=IDC_EDIT2,edit,1484980352
Control10=IDC_EDIT3,edit,1484980352
Control11=IDC_EDIT4,edit,1484980352
Control12=IDC_EDIT5,edit,1484980352
Control13=IDOK,button,1342242817
Control14=IDCANCEL,button,1342242816
Control15=IDC_BUTNEWKNOT,button,1342242816
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342177294
Control22=IDC_STATIC,static,1342177294
Control23=IDC_STATIC,static,1342177294
Control24=IDC_STATIC,static,1342177294
Control25=IDC_STATIC,static,1342177294

[DLG:IDD_DIALOGSPRING (Russian)]
Type=1
Class=CSpringDlg
ControlCount=21
Control1=IDC_COMBO2,combobox,1344339971
Control2=IDC_COMBO3,combobox,1344339971
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1484849280
Control5=IDC_EDIT3,edit,1484849280
Control6=IDC_EDIT4,edit,1484849280
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816
Control9=IDC_BUTNEWKNOT,button,1342242816
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_RADIO2,button,1342308361
Control16=IDC_RADIO3,button,1342308361
Control17=IDC_RADIO1,button,1342308361
Control18=IDC_STATIC,static,1342177294
Control19=IDC_STATIC,static,1342177294
Control20=IDC_STATIC,static,1342177294
Control21=IDC_RADIO4,button,1342308361

[DLG:IDD_DIALOGMASS (Russian)]
Type=1
Class=CMassDlg
ControlCount=11
Control1=IDC_COMBO1,combobox,1344339971
Control2=IDC_BUTNEWKNOT,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=65535,button,1342177287
Control8=65535,button,1342177287
Control9=65535,static,1342308352
Control10=65535,static,1342308352
Control11=65535,static,1342308352

[DLG:IDD_DIALOGELEM (Russian)]
Type=1
Class=CElemDlg
ControlCount=4
Control1=IDC_LISTCONTROL,SysListView32,1350633485
Control2=IDC_BUTTONPROP,button,1342242816
Control3=IDC_BUTTONDEL,button,1342242816
Control4=IDOK,button,1342242817

[DLG:IDD_ABOUTBOX (Russian)]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308481
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308353
Control6=IDC_STATIC,static,1342308353
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308353

[DLG:IDD_DIALOGPRECALC (Russian)]
Type=1
Class=CPreCalcDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT2,edit,1350631552
Control8=IDC_STATIC,button,1342177287
Control9=IDC_RADIO1,button,1342373897
Control10=IDC_RADIO2,button,1342177289
Control11=IDC_RADIO3,button,1342177289
Control12=IDC_RADIO4,button,1476395017

[DLG:IDD_KNOTPAGE1 (Russian)]
Type=1
Class=CKnotPropertyPage1
ControlCount=7
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_COMBO1,combobox,1344339987

[DLG:IDD_KNOTPAGE2 (Russian)]
Type=1
Class=CKnotPropertyPage2
ControlCount=16
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_EDIT3,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT5,edit,1350631552
Control8=IDC_EDIT6,edit,1350631552
Control9=IDC_EDIT7,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,button,1342177287

[DLG:IDD_DIALOGTYPEGRAPH (Russian)]
Type=1
Class=CTypeGraphDlg
ControlCount=24
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIO1,button,1342308361
Control5=IDC_RADIO2,button,1342177289
Control6=IDC_RADIO3,button,1342177289
Control7=IDC_RADIO4,button,1342177289
Control8=IDC_RADIO5,button,1342177289
Control9=IDC_RADIO6,button,1342177289
Control10=IDC_RADIO15,button,1342177289
Control11=IDC_RADIO16,button,1342177289
Control12=IDC_RADIO17,button,1342177289
Control13=IDC_RADIO7,button,1342177289
Control14=IDC_STATIC,button,1342177287
Control15=IDC_RADIO8,button,1342308361
Control16=IDC_RADIO9,button,1342177289
Control17=IDC_RADIO10,button,1342177289
Control18=IDC_RADIO11,button,1342177289
Control19=IDC_RADIO12,button,1342177289
Control20=IDC_RADIO13,button,1342177289
Control21=IDC_RADIO18,button,1342177289
Control22=IDC_RADIO19,button,1342177289
Control23=IDC_RADIO20,button,1342177289
Control24=IDC_RADIO14,button,1342177289

[DLG:IDD_PROGRESSDIALOG (Russian)]
Type=1
Class=CProgressDlg
ControlCount=3
Control1=IDCANCEL,button,1342242817
Control2=IDC_DETAILS,edit,1342244996
Control3=IDC_PROGRESS1,msctls_progress32,1350565888

[DLG:IDD_KNOTPAGE3 (Russian)]
Type=1
Class=CKnotPropertyPage3
ControlCount=30
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,button,1342177287
Control3=IDC_CHECK1,button,1342242819
Control4=IDC_CHECK3,button,1342259203
Control5=IDC_RADIO1,button,1342373897
Control6=IDC_RADIO2,button,1342242825
Control7=IDC_RADIO5,button,1342242825
Control8=IDC_EDIT1,edit,1350631552
Control9=IDC_EDIT2,edit,1350631552
Control10=IDC_EDIT3,edit,1350631552
Control11=IDC_EDIT5,edit,1350631552
Control12=IDC_SPECTRPX,button,1342242816
Control13=IDC_CSPECPX,button,1342242816
Control14=IDC_STATIC,static,1342177280
Control15=IDC_STATIC,static,1342177280
Control16=IDC_STATIC,static,1342177280
Control17=IDC_CHECK2,button,1342242819
Control18=IDC_CHECK4,button,1342259203
Control19=IDC_RADIO3,button,1342373897
Control20=IDC_RADIO4,button,1342242825
Control21=IDC_RADIO6,button,1342242825
Control22=IDC_EDIT6,edit,1350631552
Control23=IDC_EDIT7,edit,1350631552
Control24=IDC_EDIT8,edit,1350631552
Control25=IDC_EDIT10,edit,1350631552
Control26=IDC_SPECTRPY,button,1342373888
Control27=IDC_CSPECPY,button,1342242816
Control28=IDC_STATIC,static,1342177280
Control29=IDC_STATIC,static,1342177280
Control30=IDC_STATIC,static,1342177280

[DLG:IDD_KNOTPAGE4 (Russian)]
Type=1
Class=CKnotPropertyPage4
ControlCount=30
Control1=IDC_STATIC,static,1342177280
Control2=IDC_STATIC,static,1342177280
Control3=IDC_STATIC,static,1342177280
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342177280
Control6=IDC_STATIC,static,1342177280
Control7=IDC_STATIC,static,1342177280
Control8=IDC_STATIC,button,1342177287
Control9=IDC_CHECK1,button,1342242819
Control10=IDC_CHECK3,button,1342259203
Control11=IDC_RADIO1,button,1342373897
Control12=IDC_EDIT1,edit,1350631552
Control13=IDC_EDIT2,edit,1350631552
Control14=IDC_EDIT3,edit,1350631552
Control15=IDC_RADIO2,button,1342373897
Control16=IDC_EDIT5,edit,1350631552
Control17=IDC_RADIO5,button,1342373897
Control18=IDC_BUTTON1,button,1342242816
Control19=IDC_CSPECUX,button,1342242816
Control20=IDC_CHECK2,button,1342242819
Control21=IDC_CHECK4,button,1342259203
Control22=IDC_RADIO3,button,1342373897
Control23=IDC_EDIT6,edit,1350631552
Control24=IDC_EDIT7,edit,1350631552
Control25=IDC_EDIT8,edit,1350631552
Control26=IDC_RADIO4,button,1342373897
Control27=IDC_EDIT10,edit,1350631552
Control28=IDC_RADIO6,button,1342373897
Control29=IDC_BUTTON2,button,1342242816
Control30=IDC_CSPECUY,button,1342242816

[DLG:IDD_FREQDLG (Russian)]
Type=1
Class=CFreqDlg
ControlCount=33
Control1=IDC_RADIO1,button,1342373897
Control2=IDC_RADIO2,button,1342242825
Control3=IDC_RADIO3,button,1342242825
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_EDIT2,edit,1350631552
Control6=IDC_EDIT3,edit,1350631552
Control7=IDC_CHECK1,button,1476460547
Control8=IDC_COMBO1,combobox,1344339971
Control9=IDC_RADIO4,button,1342373897
Control10=IDC_RADIO5,button,1342242825
Control11=IDC_RADIO6,button,1342242825
Control12=IDC_COMBO2,combobox,1344339971
Control13=IDC_RADIO7,button,1342373897
Control14=IDC_RADIO8,button,1342242825
Control15=IDC_RADIO9,button,1342242825
Control16=IDC_RADIO10,button,1342373897
Control17=IDC_RADIO11,button,1342242825
Control18=IDC_RADIO12,button,1342242825
Control19=IDC_RADIO13,button,1342373897
Control20=IDC_RADIO14,button,1342242825
Control21=IDOK,button,1342242817
Control22=IDCANCEL,button,1342242816
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,button,1342177287
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,button,1342177287
Control29=IDC_STATIC,button,1342177287
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,button,1342177287
Control33=IDC_STATIC,button,1342177287

[DLG:IDD_KNOTSPECTR (Russian)]
Type=1
Class=CKnotSpectr
ControlCount=56
Control1=IDC_RADIO1,button,1342382089
Control2=IDC_RADIO2,button,1342251017
Control3=IDC_RADIO3,button,1342251017
Control4=IDC_RADIO4,button,1342251017
Control5=IDC_RADIO5,button,1342251017
Control6=IDC_RADIO6,button,1342242825
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_EDIT1,edit,1350631552
Control21=IDC_EDIT2,edit,1350631552
Control22=IDC_EDIT3,edit,1350631552
Control23=IDC_EDIT4,edit,1350631552
Control24=IDC_EDIT5,edit,1350631552
Control25=IDC_EDIT6,edit,1350631552
Control26=IDC_EDIT7,edit,1350631552
Control27=IDC_EDIT8,edit,1350631552
Control28=IDC_EDIT9,edit,1350631552
Control29=IDC_EDIT10,edit,1350631552
Control30=IDC_EDIT11,edit,1350631552
Control31=IDC_EDIT12,edit,1350631552
Control32=IDC_EDIT13,edit,1350631552
Control33=IDC_EDIT14,edit,1350631552
Control34=IDC_STATIC,button,1342177287
Control35=IDC_EDIT15,edit,1350631552
Control36=IDC_EDIT16,edit,1350631552
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC,button,1342177287
Control40=IDC_RADIO7,button,1342373897
Control41=IDC_RADIO8,button,1342242825
Control42=IDC_EDIT17,edit,1350631552
Control43=IDC_STATIC,button,1342177287
Control44=IDC_EDIT19,edit,1350631552
Control45=IDC_STATIC,static,1342308352
Control46=IDC_EDIT18,edit,1350631552
Control47=IDC_STATIC,static,1342308352
Control48=IDOK,button,1342242817
Control49=IDCANCEL,button,1342242816
Control50=IDC_STATIC,static,1342177294
Control51=IDC_STATIC,static,1342177294
Control52=IDC_STATIC,static,1342177294
Control53=IDC_STATIC,static,1342177294
Control54=IDC_STATIC,static,1342177294
Control55=IDC_CHECK1,button,1342242819
Control56=IDC_STATIC,static,1342308352

[DLG:IDD_COMPLEXSPECTR (Russian)]
Type=1
Class=CComplexSpectrDlg
ControlCount=9
Control1=IDC_COMBO1,combobox,1344339971
Control2=IDC_COMBO2,combobox,1344339971
Control3=IDC_BUTTON2,button,1342242817
Control4=IDC_BUTTON3,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_BUTTON1,button,1342242816
Control8=IDOK,button,1342242816
Control9=IDC_MSFLEXGRID1,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816

[DLG:IDD_SPECTRDLG (Russian)]
Type=1
Class=CSpectrDlg
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO1,combobox,1344339971
Control4=IDC_COMBO2,combobox,1344339971
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT1,edit,1350631552
Control9=IDC_EDIT2,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT3,edit,1350631552
Control15=IDC_CHECK1,button,1476460547

[DLG:IDD_DIALOG4 (Russian)]
Type=1
Class=CGraphTimeDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT3,edit,1350631552
Control9=IDC_STATIC,button,1342177287

[TB:IDR_GRAPHTYPE (Russian)]
Type=1
Class=?
Command1=ID_AUTOSIZE
Command2=ID_GETCOORD
Command3=ID_SAVEREZ
Command4=ID_GRAPH_PROP
Command5=ID_MAIN_GRAPH
Command6=ID_CALCMAT
CommandCount=6

[TB:IDR_MAINFRAME (Russian)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_REFRESH
Command5=ID_BUTTON_AUTO_SIZE
Command6=ID_SCALEADD
Command7=ID_SCALESUB
Command8=ID_CALC
Command9=ID_SETNULL
Command10=ID_SETROD
Command11=ID_SETHARDROD
Command12=ID_SETSPRING
Command13=ID_SETDEMF
Command14=ID_SETMASS
Command15=ID_BUTTON_DEL_FREE_KNOTS
Command16=ID_BUTTON_GRCLICK_ELEMS
Command17=ID_BUTTON_GRCLICK_KNOTS
Command18=ID_APP_ABOUT
CommandCount=18

[TB:IDR_FORMSTYPE (Russian)]
Type=1
Class=?
Command1=ID_FREQPREW
Command2=ID_FREQNEXT
Command3=ID_MOVEADD
Command4=ID_MOVESUB
Command5=ID_UPDATEFORMS
CommandCount=5

[DLG:IDD_FORMS_BAR (Russian)]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_BAR_FREQ,static,1342308352
Control4=IDC_BAR_T,static,1342308352

[DLG:IDD_DIALOGHARDROD (Russian)]
Type=1
Class=CHardRodDlg
ControlCount=22
Control1=IDC_COMBO2,combobox,1344339971
Control2=IDC_COMBO1,combobox,1344340499
Control3=IDC_COMBO3,combobox,1344339971
Control4=IDC_COMBO4,combobox,1344340499
Control5=IDC_EDIT4,edit,1350631552
Control6=IDC_EDIT1,edit,1350631552
Control7=IDC_EDIT2,edit,1350631552
Control8=IDC_EDIT3,edit,1350631552
Control9=IDOK,button,1342242817
Control10=IDCANCEL,button,1342242816
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_BUTNEWKNOT,button,1342242816

[CLS:CHardRodDlg]
Type=0
HeaderFile=HardRodDlg.h
ImplementationFile=HardRodDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTNEWKNOT
VirtualFilter=dWC

[CLS:CEVMDialog]
Type=0
HeaderFile=EVMDialog.h
ImplementationFile=EVMDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CEVMDialog

[DLG:IDD_EV_METHODS (Russian)]
Type=1
Class=CEVMDialog
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIO_JACOBY,button,1342319881
Control5=IDC_RADIO_QR_ELM,button,1342188809
Control6=IDC_RADIO_QR_DIR,button,1342188809
Control7=IDC_RADIO_QR_ORT,button,1342188809
Control8=IDC_STATIC,button,1342177287
Control9=IDC_RADIO_HARDMETHOD_0,button,1342319881
Control10=IDC_RADIO_HARDMETHOD_1,button,1476406537
Control11=IDC_RADIO_HARDMETHOD_2,button,1342188809
Control12=IDC_CHECK_INTEGR_TEST,button,1342242819
Control13=IDC_STATIC,button,1342177287
Control14=IDC_RADIO_INVERT_0,button,1342319881
Control15=IDC_RADIO_INVERT_1,button,1342188809
Control16=IDC_CHECK_VALIDATE_EXPR,button,1342242819

[DLG:IDD_VIEW_STYLES (Russian)]
Type=1
Class=CViewStyles
ControlCount=19
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_TEXT_OUT,button,1342254851
Control5=IDC_STATIC,static,1342308352
Control6=IDC_FREE_FONT,static,1342308352
Control7=IDC_BUTTON_FREE_FONT,button,1342242816
Control8=IDC_STATIC,button,1342177287
Control9=IDC_CHECK_NUM_KNOTS,button,1342242819
Control10=IDC_CHECK_NUM_ELEMS,button,1342242819
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_NUM_KNOTS,static,1342308352
Control14=IDC_BUTTON_NUM_KNOTS_FONT,button,1342242816
Control15=IDC_NUM_ELEMS,static,1342308352
Control16=IDC_BUTTON_NUM_ELEMS_FONT,button,1342242816
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT_ZERO_ROT,edit,1350631552
Control19=IDC_RICH_CALC,button,1342242819

[CLS:CViewStyles]
Type=0
HeaderFile=ViewStyles.h
ImplementationFile=ViewStyles.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RICH_CALC
VirtualFilter=dWC

[DLG:IDD_GROUP_NEW (Russian)]
Type=1
Class=CNewGroupDlg
ControlCount=9
Control1=IDC_EDIT_GROUP,edit,1350631428
Control2=IDC_EDIT_GROUP_NAME,edit,1350631552
Control3=IDC_RADIO_GROUP_TYPE,button,1342308361
Control4=IDC_RADIO_GROUP_TYPE2,button,1342177289
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308352

[CLS:CNewGroupDlg]
Type=0
HeaderFile=NewGroupDlg.h
ImplementationFile=NewGroupDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CNewGroupDlg

[DLG:IDD_GROUP_LIST (Russian)]
Type=1
Class=CGroupListDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_GRLIST,listbox,1352728833
Control4=IDC_BUTTON_DEL_GROUP,button,1342242816
Control5=IDC_BUTTON_EDIT_GROUP,button,1342242816
Control6=IDC_BUTTON_GROUP_SHOW,button,1342242816
Control7=IDC_BUTTON_GROUP_OPEN,button,1342242816
Control8=IDC_BUTTON_GROUP_SAVE,button,1342242816

[CLS:CGroupListDlg]
Type=0
HeaderFile=GroupListDlg.h
ImplementationFile=GroupListDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_GRLIST

[DLG:IDD_GROUP_EDIT (Russian)]
Type=1
Class=CGroupEditDlg
ControlCount=10
Control1=IDC_EDIT_GROUP_INEDIT,edit,1350631556
Control2=IDC_EDIT_GROUP_NAME_INEDIT,edit,1350631424
Control3=IDOK,button,1342242817
Control4=IDC_BUTTON_REFRESH,button,1342242816
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_GROUP_TYPE_INEDIT,edit,1350633472
Control9=IDC_EDIT_GROUP_SET,edit,1352730692
Control10=IDC_BUTTON_PACK,button,1342242816

[CLS:CGroupEditDlg]
Type=0
HeaderFile=GroupEditDlg.h
ImplementationFile=GroupEditDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CGroupEditDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_GROUP_SHOW (Russian)]
Type=1
Class=CGroupPreviewDlg
ControlCount=1
Control1=IDOK,button,1342242817

[CLS:CGroupPreviewDlg]
Type=0
HeaderFile=GroupPreviewDlg.h
ImplementationFile=GroupPreviewDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CGroupPreviewDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_MESH_ELEM (Russian)]
Type=1
Class=CMeshElemDlg
ControlCount=21
Control1=IDC_RADIO1,button,1342308361
Control2=IDC_RADIO2,button,1342177289
Control3=IDC_EDIT_ELEMS_COUNT,edit,1350631552
Control4=IDC_SLIDER1,msctls_trackbar32,1342242840
Control5=IDC_EDIT_LEFT_LENGTH,edit,1350631424
Control6=IDC_EDIT_RIGHT_LENGTH,edit,1350631424
Control7=IDC_EDIT_LEFT_PROC,edit,1350633472
Control8=IDC_EDIT_RIGHT_PROC,edit,1350633472
Control9=IDOK,button,1342242817
Control10=IDCANCEL,button,1342242816
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_LEFT_KNOT,edit,1350633600
Control15=IDC_EDIT_RIGHT_KNOT,edit,1350633600
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT_LENGTH,edit,1350633472

[CLS:CMeshElemDlg]
Type=0
HeaderFile=MeshElemDlg.h
ImplementationFile=MeshElemDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMeshElemDlg

[DLG:IDD_CONVERT_TO (Russian)]
Type=1
Class=CConvertToDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_NEW_ELEM_TYPE,edit,1350633600

[CLS:CConvertToDlg]
Type=0
HeaderFile=ConvertToDlg.h
ImplementationFile=ConvertToDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CConvertToDlg

[CLS:CScriptView]
Type=0
HeaderFile=ScriptView.h
ImplementationFile=ScriptView.cpp
BaseClass=CEditView
Filter=C
LastObject=ID_MOVIE_MOVE_UP
VirtualFilter=VWC

[CLS:CScriptFrame]
Type=0
HeaderFile=ScriptFrame.h
ImplementationFile=ScriptFrame.cpp
BaseClass=CMDIChildWnd
Filter=M
VirtualFilter=mfWC
LastObject=CScriptFrame

[MNU:IDR_SCRIPT (Russian)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
CommandCount=7

[TB:IDR_SCRIPT (Russian)]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_SCRIPT_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_COMPILE_SCRIPT
Command5=ID_RUN_SCRIPT
CommandCount=5

[CLS:CScriptDoc]
Type=0
HeaderFile=ScriptDoc.h
ImplementationFile=ScriptDoc.cpp
BaseClass=CDocument
Filter=N
VirtualFilter=DC

[CLS:COutputFrame]
Type=0
HeaderFile=OutputFrame.h
ImplementationFile=OutputFrame.cpp
BaseClass=CMDIChildWnd
Filter=C
VirtualFilter=mfWC

[CLS:COutputView]
Type=0
HeaderFile=OutputView.h
ImplementationFile=OutputView.cpp
BaseClass=CEditView
Filter=C
VirtualFilter=VWC

[TB:IDR_OUTPUT (Russian)]
Type=1
Class=?
Command1=ID_OUTPUT_FILE_SAVE
Command2=ID_OUTPUT_BREAK
CommandCount=2

[TB:IDR_MOVIE (Russian)]
Type=1
Class=?
Command1=ID_MOVIE_PREV_STEP
Command2=ID_MOVIE_RUN
Command3=ID_MOVIE_PAUSE
Command4=ID_MOVIE_STOP
Command5=ID_MOVIE_NEXT_STEP
Command6=ID_MOVIE_AUTO_SCALE
Command7=ID_MOVIE_SCALE_INC
Command8=ID_MOVIE_SCALE_DEC
Command9=ID_MOVIE_MOVE_UP
Command10=ID_MOVIE_MOVE_DOWN
Command11=ID_MOVIE_MOVE_LEFT
Command12=ID_MOVIE_MOVE_RIGHT
Command13=ID_MOVIE_PARAMS
CommandCount=13

[CLS:CMovieFrame]
Type=0
HeaderFile=MovieFrame.h
ImplementationFile=MovieFrame.cpp
BaseClass=CMDIChildWnd
Filter=M
VirtualFilter=mfWC

[CLS:CMovieView]
Type=0
HeaderFile=MovieView.h
ImplementationFile=MovieView.cpp
BaseClass=CScrollView
Filter=C
VirtualFilter=VWC
LastObject=CMovieView

[DLG:IDD_MOVIE_STYLES (Russian)]
Type=1
Class=CMovieParams
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_TIMER_ELAPSE,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_START_TIME,edit,1350631552
Control7=IDC_CHECK_SHOW_KNOTS,button,1342242819

[CLS:CMovieParams]
Type=0
HeaderFile=MovieParams.h
ImplementationFile=MovieParams.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMovieParams

[DLG:IDD_TIME_DLG (Russian)]
Type=1
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=ID_CURRENT_TIME,static,1342308352

[ACL:IDR_MOVIE (Russian)]
Type=1
Class=?
Command1=ID_MOVIE_SCALE_INC
Command2=ID_MOVIE_MOVE_DOWN
Command3=ID_MOVIE_MOVE_LEFT
Command4=ID_MOVIE_MOVE_RIGHT
Command5=ID_MOVIE_SCALE_DEC
Command6=ID_MOVIE_MOVE_UP
CommandCount=6

[DLG:IDD_SHEME_VARS (Russian)]
Type=1
Class=CShemeVars
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_VARS_LIST,SysListView32,1350633477
Control3=IDC_ADD_VAR,button,1342242816
Control4=IDC_RECALC,button,1342242816
Control5=IDC_EDIT_VAR,button,1342242816
Control6=IDC_DEL_VAR,button,1342242816

[CLS:CShemeVars]
Type=0
HeaderFile=ShemeVars.h
ImplementationFile=ShemeVars.cpp
BaseClass=CDialog
Filter=D
LastObject=CShemeVars
VirtualFilter=dWC

[DLG:IDD_SHEME_VAR_NEW (Russian)]
Type=1
Class=ShemeVarNewDlg
ControlCount=6
Control1=IDC_EDIT_NAME,edit,1350631552
Control2=IDC_EDIT_EXPR,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:ShemeVarNewDlg]
Type=0
HeaderFile=ShemeVarNewDlg.h
ImplementationFile=ShemeVarNewDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_EXPR

[DLG:IDD_DESCRIPTION (Russian)]
Type=1
Class=CDescriptionDlg
ControlCount=3
Control1=IDC_EDIT_DESCRIPTION,edit,1353781444
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[CLS:CDescriptionDlg]
Type=0
HeaderFile=DescriptionDlg.h
ImplementationFile=DescriptionDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDescriptionDlg

[DLG:IDD_GRAPHS_PROPERTIES (Russian)]
Type=1
Class=CGraphProp
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_GRAPH_LIST,listbox,1353781521
Control3=IDC_GRAPH_EDIT,button,1342242816
Control4=IDC_GRAPH_NEW,button,1342242816
Control5=IDC_GRAPH_DEL,button,1342242816

[CLS:CGraphProp]
Type=0
HeaderFile=GraphProp.h
ImplementationFile=GraphProp.cpp
BaseClass=CDialog
Filter=D
LastObject=CGraphProp
VirtualFilter=dWC

[CLS:CGraphListBox]
Type=0
HeaderFile=GraphListBox.h
ImplementationFile=GraphListBox.cpp
BaseClass=CCheckListBox
Filter=W
LastObject=CGraphListBox
VirtualFilter=bWC

[DLG:IDD_GRAPH_EDIT (Russian)]
Type=1
Class=CGraphDlg
ControlCount=12
Control1=IDC_CAPTION,edit,1350631552
Control2=IDC_GRAPH_SCALE,edit,1350631552
Control3=IDC_GRAPH_LOAD,button,1342242816
Control4=IDC_EDIT_GRAPH_COLOR,button,1342242816
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_GRAPH_FILE_NAME,edit,1342244992
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_GRAPH_COLOR,button,1342275595

[CLS:CGraphDlg]
Type=0
HeaderFile=GraphDlg.h
ImplementationFile=GraphDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CGraphDlg

[CLS:CColorButton]
Type=0
HeaderFile=ColorButton.h
ImplementationFile=ColorButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC

