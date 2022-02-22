// MapDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MapDemo.h"

#include "MainFrm.h"
#include "MapDemoDoc.h"
#include "MapDemoView.h"
#include "FOHyperLink.h"
#include "FOPGDIPlusProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapDemoApp

BEGIN_MESSAGE_MAP(CMapDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CMapDemoApp)
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
// CMapDemoApp construction

CMapDemoApp::CMapDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMapDemoApp object

CMapDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMapDemoApp initialization

BOOL CMapDemoApp::InitInstance()
{
	// E-XD++ Library Add line.
	if(!AfxOleInit())
	{
		//AfxMessageBox(IDP_OLE_INIT_FAILED);
		AfxMessageBox("Failed!");
		return FALSE;
	}
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	
	FOEnableXPStyle(TRUE);
	gfxData.InitGUIType(GUI_BLUE);
	//E-XD++ Library add lines.
	FOInit();//RUNTIME_CLASS(CFOPGDIPlusProxy));


#if _MSC_VER <= 1200 // MFC 6.0 or earlier
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif // MFC 6.0 or earlier

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMapDemoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMapDemoView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
	{
		CString strPathX = AfxGetApp()->m_pszHelpFilePath;
		strPathX = strPathX.Left(strPathX.ReverseFind('\\'));
		CString strOtherFile;
		strOtherFile = strPathX+_T("\\usamap.map");
		this->OpenDocumentFile(strOtherFile);
	}
	else if (!ProcessShellCommand(cmdInfo))
	{
		return FALSE;
	}

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

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
	CFOHyperLink m_Home;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnButton1();
	virtual BOOL OnInitDialog();
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
	DDX_Control(pDX, IDC_HOMEPAGE, m_Home);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_BUTTON_SYS1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMapDemoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CCustomMSampleApp message handlers


void CAboutDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	HKEY hKey1;
	LONG res = RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("SOFTWARE\\Microsoft\\Shared Tools\\MSInfo"),0L,KEY_ALL_ACCESS,&hKey1);
	if (res == ERROR_SUCCESS)
	{
		DWORD bufsize = _MAX_PATH;
		char msinfo[_MAX_PATH];

		res = RegQueryValueEx(hKey1,_T("Path"),0L,0,(LPBYTE)msinfo,(LPDWORD)&bufsize);
		RegCloseKey(hKey1);
		if (res == ERROR_SUCCESS) WinExec(msinfo, SW_SHOW);
	}
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// TODO: Add extra initialization here
	m_Home.SetColors(RGB(0,0,255), RGB(0,0,255), RGB(51,102,153) );
	m_Home.SetURL(_T("http://www.ucancode.net"));
	GetDlgItem(IDC_EDIT_SYS1)->SetWindowText(_T("If you want to learn more about E-XD++ Visualization Enterprise Edition,Visit:http://www.ucancode.net"));
	return TRUE;
}
