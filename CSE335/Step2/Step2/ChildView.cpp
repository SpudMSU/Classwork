/**
 * \file ChildView.cpp
 *
 * \author Spencer D Cassetta
 */

#include "pch.h"
#include "framework.h"
#include "Step2.h"
#include "ChildView.h"
#include "FishBeta.h"
#include "FishAngel.h"
#include "DoubleBufferDC.h"
#include "FishBubbles.h"
#include "FishStinky.h"
#include "DecorCastle.h"
using namespace Gdiplus;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/// Frame duration in milliseconds
const int FrameDuration = 30;

 /**
  * Constructor
  */

/**
 * Destructor
 */
CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_ADDFISH_BETAFISH, &CChildView::OnAddfishBetafish)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ADDFISH_ANGELFISH, &CChildView::OnAddfishAngelfish)
	ON_COMMAND(ID_ADDFISH_BUBBLEFISH, &CChildView::OnAddfishBubblefish)
	ON_COMMAND(ID_ADDFISH_STINKY, &CChildView::OnAddfishStinky)
	ON_COMMAND(ID_ADDSCENERY_ADDCASTLE32776, &CChildView::OnAddCastle)
	ON_COMMAND(ID_FILE_SAVEAS32778, &CChildView::OnFileSaveAs)
	ON_COMMAND(ID_FILE_OPEN32779, &CChildView::OnFileOpen)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CChildView message handlers

/** This function is called before the window is created.
 * \param cs A structure with the window creation parameters
 * \returns TRUE
 */
 /** Constructor */
CChildView::CChildView()
{
	srand((unsigned int)time(nullptr));
}

///process of creating a window
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

/** This function is called to draw in the window.
*
* This function is called in response to a drawing message
* whenever we need to redraw the window on the screen.
* It is responsible for painting the window.
*/
void CChildView::OnPaint(){



	CPaintDC paintDC(this);     // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting
	Graphics graphics(dc.m_hDC);

	mAquarium.OnDraw(&graphics);

	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		 * Initialize the elapsed time system
		 */
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}

	/*
	* Compute the elapsed time since the last draw
	*/
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	mAquarium.Update(elapsed);
}

/*
* When menu item is selected it adds a beta fish
*/
void CChildView::OnAddfishBetafish()
{
	auto fish = make_shared<CFishBeta>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}


/**
 * Called when there is a left mouse button press
 * \param nFlags Flags associated with the mouse button press
 * \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	mGrabbedItem = mAquarium.HitTest(point.x, point.y);
	if (mGrabbedItem != nullptr)
	{
		mAquarium.replaceItem(mGrabbedItem);
	}
}


/**
 * Called when the left mouse button is released
 * \param nFlags Flags associated with the mouse button release
 * \param point Where the button was pressed
 */
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	OnMouseMove(nFlags, point);
}


/**
 * Called when the mouse is moved
 * \param nFlags Flags associated with the mouse movement
 * \param point Where the button was pressed
 */
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			mGrabbedItem->SetLocation(point.x, point.y);
		}
		else
		{
			// When the left button is released, we release the
			// item.
			mGrabbedItem = nullptr;
		}

		// Force the screen to redraw
		Invalidate();
	}
}


/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

/*
* When menu item is selected it adds a Angel fish
*/
void CChildView::OnAddfishAngelfish()
{
	auto fish = make_shared<CFishAngel>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

/*
* When menu item is selected it adds a Bubble fish
*/
void CChildView::OnAddfishBubblefish()
{
	auto fish = make_shared<CFishBubbles>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

/*
* When menu item is selected it adds a Stinky fish
*/
void CChildView::OnAddfishStinky()
{
	auto fish = make_shared<CFishStinky>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

///Menu option for add castle
void CChildView::OnAddCastle()
{
	auto castle = make_shared<CDecorCastle>(&mAquarium);
	castle->SetLocation(InitialX, InitialY);
	mAquarium.Add(castle);
	Invalidate();
}

///Menu option for saving the aquarium
void CChildView::OnFileSaveAs()
{
	CFileDialog dlg(false,  // false = Save dialog box
		L".aqua",           // Default file extension
		nullptr,            // Default file name (none)
		OFN_OVERWRITEPROMPT,      // Flags (warn it overwriting file)
		L"Aquarium Files (*.aqua)|*.aqua|All Files (*.*)|*.*||"); // Filter

	if (dlg.DoModal() != IDOK)
		return;

	wstring filename = dlg.GetPathName();
	mAquarium.Save(filename);
}


/**
 * This function is called when an File Open menu item is selected.
 *
 * It loads the aquarium from a file.
 */
void CChildView::OnFileOpen()
{
	CFileDialog dlg(true,  // true = Open dialog box
		L".aqua",           // Default file extension
		nullptr,            // Default file name (none)
		0,    // Flags
		L"Aquarium Files (*.aqua)|*.aqua|All Files (*.*)|*.*||");  // Filter
	if (dlg.DoModal() != IDOK)
		return;

	wstring filename = dlg.GetPathName();

	mAquarium.Load(filename);
	Invalidate();
}

/**
* Timer the fish speed depends on
* \param nIDEvent is the Id of the event
*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}
