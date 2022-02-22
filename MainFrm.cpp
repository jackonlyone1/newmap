// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MapDemo.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFOPFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFOPFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_VIEW_DRAWBAR, OnViewDrawbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DRAWBAR, OnUpdateViewDrawbar)
	ON_COMMAND(ID_VIEW_FORMATBAR, OnViewFormatbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FORMATBAR, OnUpdateViewFormatbar)
	ON_WM_CREATE()
	ON_COMMAND(ID_HELP_ONTHEWEB, OnHelpOntheweb)
	ON_COMMAND(IDM_MAIL_ME, OnMailMe)
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullscreen)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FULLSCREEN, OnUpdateViewFullscreen)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(FOP_WM_VIEWVALID, OnViewValidMsg)
	ON_REGISTERED_MESSAGE(FOP_WM_VIEWINVALID, OnViewInValidMsg)
	ON_REGISTERED_MESSAGE(FOP_WM_SHAPECHANGED,   OnShapeChangedMsg)
	ON_REGISTERED_MESSAGE(FOP_WM_VIEW_UPDATE,   OnCanvasChangedMsg)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_FO_INDEX_MOUSEPOS,
	ID_FO_INDEX_WIDTH,
	ID_FO_INDEX_HEIGHT,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	ShowMenuImage();
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT LPCREATESTRUCT)
{
	if (CFOPFrameWnd::OnCreate(LPCREATESTRUCT) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_wndPanBar.Create(this, _T("Pan Window"), WS_CHILD|WS_VISIBLE|CBRS_LEFT|CBRS_TOOLTIPS|CBRS_SIZE_DYNAMIC|CBRS_FLOAT_MULTI, 
		CBRS_FOP_DEFAULT|CBRS_FOP_BDSP, 20002))
	{
		TRACE(_T("Failed to create List Bar\n"));
		return -1;
	}

	// Create toolbox
	if (!m_wndTableBar.Create(this, _T("ToolBox Bar"), WS_CHILD|WS_VISIBLE|CBRS_LEFT|CBRS_TOOLTIPS|CBRS_SIZE_DYNAMIC, 
		CBRS_FOP_DEFAULT|CBRS_FOP_BDSP, 1212))
	{
		TRACE(_T("Failed to create List Bar\n"));
		return -1;
	}
	
	m_wndToolBar.SetWindowText(_T("Standard"));
	m_wndTableBar.SetWindowText(_T("States"));
	
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndPanBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndTableBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndToolBar);
	DockControlBarEx(&m_wndPanBar, AFX_IDW_DOCKBAR_LEFT, 50, 200);
	DockControlBarBottomOf(&m_wndTableBar, &m_wndPanBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	//E-XD++ Library add lines.
	int DesktopWidth  = GetSystemMetrics(SM_CXSCREEN);
	int DesktopHeight = GetSystemMetrics(SM_CYSCREEN);

	// Just Make It Small So We Will Not Feel a "Blink"
	CRect MainWindow_Rect(0,0, DesktopWidth, DesktopHeight); // First Opening Screen

	cs.x = (DesktopWidth - MainWindow_Rect.right)/2;
	cs.y = (DesktopHeight - MainWindow_Rect.bottom)/2;

    cs.cx = MainWindow_Rect.right;
	cs.cy = MainWindow_Rect.bottom;
	if( !CFOPFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREAFOAPPWIZARDRUCT cs
	//E-XD++ Library add lines.
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFOPFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFOPFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


//E-XD++ Library add lines.
void CMainFrame::OnViewDrawbar() 
{
	// TODO: Add your command handler code here

}

void CMainFrame::OnUpdateViewDrawbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}
//E-XD++ Library add lines.
void CMainFrame::OnViewFormatbar() 
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnUpdateViewFormatbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}


void CMainFrame::OnHelpOntheweb() 
{
	// TODO: Add your command handler code here
	LaunchURL("http://www.ucancode.net");
}

void CMainFrame::LaunchURL(CString sURL)
{
	ShellExecute(NULL, 
				_T("open"), 
				sURL, 
				NULL,NULL, 
				SW_SHOW);
}

void CMainFrame::OnMailMe() 
{
    // First try ShellExecute()
	HINSTANCE result = ShellExecute(NULL, _T("open"), _T("mailto:support@ucancode.net?subject= Ask questions about E-XD++"),NULL,NULL, SW_SHOWNORMAL);
    // If it failed, get the .htm regkey and lookup the program
	result;
}

void CMainFrame::OnViewFullscreen() 
{
	// TODO: Add your command handler code here
	ShowFullScreen();
}

void CMainFrame::OnUpdateViewFullscreen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(IsFullScreen());
}

LRESULT CMainFrame::OnViewValidMsg (WPARAM wparam, LPARAM lp)
{
	lp;
	CFODrawView* pView = (CFODrawView*) wparam;
	
	m_wndPanBar.SetActiveView(pView);

	return 1;
}

LRESULT CMainFrame::OnViewInValidMsg (WPARAM wparam, LPARAM lp)
{
	CFODrawView* ActiveView = (CFODrawView*) wparam;
	CFODrawView* DeactiveView = (CFODrawView*) lp;

	// VERY important change, handling the case when switch to othe app.
	if(ActiveView == DeactiveView) 
		return 1;

	if (m_wndPanBar.GetActiveView()==DeactiveView)
	  m_wndPanBar.SetActiveView(NULL);

	return 1;
}

LRESULT CMainFrame::OnShapeChangedMsg(WPARAM wP,LPARAM /*lP*/)
{
	m_wndPanBar.UpdateWnd(FALSE);
	return TRUE;
}

LRESULT CMainFrame::OnCanvasChangedMsg(WPARAM wP,LPARAM lP)
{
	if(m_wndPanBar.m_hWnd == NULL)
		return FALSE;

	int nLong = (int)lP;
	if(nLong == 100)
	{
		m_wndPanBar.UpdateWnd(TRUE);
		m_wndPanBar.RedrawWindow();
	}
	else if(nLong == 200)
	{
		m_wndPanBar.UpdateWnd(FALSE);
		m_wndPanBar.UpdateZoomScale();
	}
	else
	{
		m_wndPanBar.UpdateWnd(FALSE);
	}
	return TRUE;
}
