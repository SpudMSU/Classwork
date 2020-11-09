
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "ElevatorApp.h"
#include "Controller.h"
#include "MainFrm.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_SCALE_1X, &CMainFrame::OnScale1x)
	ON_UPDATE_COMMAND_UI(ID_SCALE_1X, &CMainFrame::OnUpdateScale1x)
	ON_COMMAND(ID_SCALE_2X, &CMainFrame::OnScale2x)
	ON_UPDATE_COMMAND_UI(ID_SCALE_2X, &CMainFrame::OnUpdateScale2x)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	if (!mElevator.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

    Initialize();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	auto scaleStr = AfxGetApp()->GetProfileStringW(L"settings", L"scale", L"1");
	auto scale = _wtof(scaleStr);
	if (scale < 1)
	{
		scale = 1;
	}
	else if (scale > 2)
	{
		scale = 2;
	}

	mElevator.SetScale(scale);

    // An attempt to estimate the size we need to accomodate the elevator
    int borderX = 2 * (GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(SM_CXEDGE) * 2);
    int borderY = 2 * (GetSystemMetrics(SM_CYSIZEFRAME) + GetSystemMetrics(SM_CYEDGE) * 2) +
        GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU) * 2;
    int y = GetSystemMetrics(SM_CYMENU);

    cs.cx = mElevator.GetWidth() + borderX;
    cs.cy = mElevator.GetHeight() + borderY;


	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the view window
	mElevator.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (mElevator.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


/**
 * Initialize the elevator simulation we will use
 */
void CMainFrame::Initialize()
{
	auto controller = make_shared<CController>();
	mElevator.SetController(controller);
}


void CMainFrame::OnScale1x()
{
	SetScale(1);
}


void CMainFrame::OnUpdateScale1x(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mElevator.GetScale() == 1);
}


void CMainFrame::OnScale2x()
{
	SetScale(2);
}


void CMainFrame::OnUpdateScale2x(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mElevator.GetScale() == 2);
}

void CMainFrame::SetScale(double scale)
{
	mElevator.SetScale(scale);

	// An attempt to estimate the size we need to accomodate the elevator
	int borderX = 2 * (GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(SM_CXEDGE) * 2);
	int borderY = 2 * (GetSystemMetrics(SM_CYSIZEFRAME) + GetSystemMetrics(SM_CYEDGE) * 2) +
		GetSystemMetrics(SM_CYMENU) * 2;
	int y = GetSystemMetrics(SM_CYMENU);

	int wid = mElevator.GetWidth() + borderX;
	int hit = mElevator.GetHeight() + borderY;
	SetWindowPos(nullptr, 0, 0, wid, hit, SWP_NOMOVE);

	auto app = AfxGetApp();
	app->WriteProfileStringW(L"settings", L"scale", std::to_wstring(scale).c_str());
}