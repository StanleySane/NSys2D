// NSys2D.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "NSys2D.h"

#include "MainFrm.h"
#include "ShemeFrm.h"
#include "ShemeDoc.h"
#include "ShemeView.h"

#include "FormsView.h"
#include "FormsFrame.h"

#include "GraphFrm.h"
#include "GraphicView.h"

#include "ScriptFrame.h"
#include "ScriptView.h"
#include "ScriptDoc.h"

#include "OutputFrame.h"
#include "OutputView.h"

#include "MovieView.h"
#include "MovieFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNSys2DApp

BEGIN_MESSAGE_MAP(CNSys2DApp, CWinApp)
        //{{AFX_MSG_MAP(CNSys2DApp)
        ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
                // NOTE - the ClassWizard will add and remove mapping macros here.
                //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG_MAP
        // Standard file based document commands
        ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
        ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
        // Standard print setup command
        ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNSys2DApp construction

CNSys2DApp::CNSys2DApp()
{
        // TODO: add construction code here,
        // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNSys2DApp object

double CNSys2DApp::InitPI()
{
	double pi = 3.14;
	__asm
	{
		fldpi
		fst pi
	}
	return pi;
}
double CNSys2DApp::InitPI_2()
{
	double pi = 3.14;
	__asm
	{
		fldpi
		fst pi
	}
	return pi/2.0;
}

CNSys2DApp theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

/////////////////////////////////////////////////////////////////////////////
// CNSys2DApp initialization

BOOL CNSys2DApp::InitInstance()
{
        AfxEnableControlContainer();

        // Standard initialization
        // If you are not using these features and wish to reduce the size
        //  of your final executable, you should remove from the following
        //  the specific initialization routines you do not need.

#ifdef _AFXDLL
        Enable3dControls();                     // Call this when using MFC in a shared DLL
#else
        Enable3dControlsStatic();       // Call this when linking to MFC statically
#endif

        // Change the registry key under which our settings are stored.
        // You should modify this string to be something appropriate
        // such as the name of your company or organization.
        SetRegistryKey(_T("Local AppWizard-Generated Applications"));

        LoadStdProfileSettings();  // Load standard INI file options (including MRU)

        // Register the application's document templates.  Document templates
        //  serve as the connection between documents, frame windows and views.

        CMultiDocTemplate* pDocTemplate;
        pDocTemplate = new CMultiDocTemplate(
                IDR_SHEMETYPE,
                RUNTIME_CLASS(CShemeDoc),
                RUNTIME_CLASS(CShemeFrame), // custom MDI child frame
                RUNTIME_CLASS(CShemeView));
        AddDocTemplate(pDocTemplate);
        
        pDocTemplate = new CMultiDocTemplate(
                IDR_GRAPHTYPE,
                RUNTIME_CLASS(CShemeDoc),
                RUNTIME_CLASS(CGraphFrame), // custom MDI child frame
                RUNTIME_CLASS(CGraphicView));
        AddDocTemplate(pDocTemplate);
		
        pDocTemplate = new CMultiDocTemplate(
                IDR_FORMSTYPE,
                RUNTIME_CLASS(CShemeDoc),
                RUNTIME_CLASS(CFormsFrame), // custom MDI child frame
                RUNTIME_CLASS(CFormsView));
        AddDocTemplate(pDocTemplate);

		//???????:
        pDocTemplate = new CMultiDocTemplate(
                IDR_SCRIPT,
                RUNTIME_CLASS(CScriptDoc),
                RUNTIME_CLASS(CScriptFrame), // custom MDI child frame
                RUNTIME_CLASS(CScriptView));
        AddDocTemplate(pDocTemplate);

        pDocTemplate = new CMultiDocTemplate(
                IDR_OUTPUT,
                RUNTIME_CLASS(CScriptDoc),
                RUNTIME_CLASS(COutputFrame), // custom MDI child frame
                RUNTIME_CLASS(COutputView));
        AddDocTemplate(pDocTemplate);

		//????????:
        pDocTemplate = new CMultiDocTemplate(
                IDR_MOVIE,
                RUNTIME_CLASS(CShemeDoc),
                RUNTIME_CLASS(CMovieFrame), // custom MDI child frame
                RUNTIME_CLASS(CMovieView));
        AddDocTemplate(pDocTemplate);

        // create main MDI Frame window
        CMainFrame* pMainFrame = new CMainFrame;
        if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
                return FALSE;
        m_pMainWnd = pMainFrame;

        // Enable drag/drop open
        m_pMainWnd->DragAcceptFiles();

        // Enable DDE Execute open
        EnableShellOpen();
        RegisterShellFileTypes(TRUE);

        // Parse command line for standard shell commands, DDE, file open
        CCommandLineInfo cmdInfo;
        ParseCommandLine(cmdInfo);

        // Dispatch commands specified on the command line
        if (!ProcessShellCommand(cmdInfo))
                return FALSE;

        // The main window has been initialized, so show and update it.
        pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);//m_nCmdShow);
        pMainFrame->UpdateWindow();

        return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
        CAboutDlg();

// Dialog Data
        //{{AFX_DATA(CAboutDlg)
        enum { IDD = IDD_ABOUTBOX };
        //}}AFX_DATA

        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CAboutDlg)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

// Implementation
protected:
        //{{AFX_MSG(CAboutDlg)
                // No message handlers
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
        //{{AFX_DATA_INIT(CAboutDlg)
        //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CAboutDlg)
        //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
        //{{AFX_MSG_MAP(CAboutDlg)
                // No message handlers
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CNSys2DApp::OnAppAbout()
{
        CAboutDlg aboutDlg;
        aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CNSys2DApp commands
