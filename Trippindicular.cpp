// Trippindicular.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Trippindicular.h"
#include "MainFrm.h"

#include "D3DWrapper.h"

#include "ThreadMgr.h"

#include "VectorGraphics.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Bool	g_bCustomShader							= false;

CVisualizer CTrippindicularApp::m_Viz;

// CTrippindicularApp

BEGIN_MESSAGE_MAP(CTrippindicularApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CTrippindicularApp::OnAppAbout)
END_MESSAGE_MAP()

// CTrippindicularApp construction

CTrippindicularApp::CTrippindicularApp()
{
	//_CrtSetBreakAlloc(68);

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

CTrippindicularApp::~CTrippindicularApp()
{
	WriteProfileInt("Settings", "VideoWidth", m_vBufferSize.X);
	WriteProfileInt("Settings", "VideoHeight", m_vBufferSize.Y);
}

// The one and only CTrippindicularApp object

CTrippindicularApp theApp;


// CTrippindicularApp initialization

BOOL CTrippindicularApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CGLibMFCApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("GWare"));

	m_vBufferSize.X = GetProfileInt("Settings", "VideoWidth", 0);
	m_vBufferSize.Y = GetProfileInt("Settings", "VideoHeight", 0);

	if (m_vBufferSize.X == 0 || m_vBufferSize.Y == 0)
		m_vBufferSize = Vec2u(1600, 900);

	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);






	// The one and only window has been initialized, so show and update it
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow();

	SetInitFunc(TFunctor(&CTrippindicularApp::MainInit));
	SetUpdateFunc(TFunctor(&CTrippindicularApp::MainUpdateLoop));

	BeginThread();
	
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

DWORD CTrippindicularApp::MainInit(LPVOID data)
{
	srand(time(NULL));
	
	if (m_Viz.Init(Vec2u(m_vBufferSize.X, m_vBufferSize.Y)) != 0)
		return -1;

	if (g_bCustomShader)
		if (!m_Viz.LoadEffect("CustomShader.fx"))
			return -1;

	//just once since the camera never moves
	g_D3D->UpdateCamera();

	return 0;
}

DWORD CTrippindicularApp::MainUpdateLoop(LPVOID data)
{
	//not needed in this app (yet)
	//g_D3D->UpdateCamera();

	m_Viz.HandleInput();

	if (D3D::Exists() && g_D3D->BeginScene(true))
	{
		if (g_bCustomShader)
		{
			m_Viz.CustomShader();
		}
		else
		{
			m_Viz.Update();
			m_Viz.Render(0);
			g_D3D->EndScene(false);

			g_D3D->BeginScene(true, false);
			m_Viz.Render(1);
			g_D3D->EndScene();
		}
	}

	return 0;
}

// CTrippindicularApp message handlers




///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CTrippindicularApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CTrippindicularApp message handlers

