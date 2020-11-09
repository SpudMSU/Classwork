/**
 * \file ViewTimeline.cpp
 *
 * \author 
 */


#include "pch.h"
#include "CanadianExperience.h"
#include "ViewTimeline.h"
#include "DoubleBufferDC.h"
#include <sstream>
#include "Timeline.h"
#include "MainFrm.h"
#include "Picture.h"
using namespace std;
using namespace Gdiplus;


/// The window height in pixels
const int WindowHeight = 60;

/// The spacing from the top of the 
/// window to the top of the tick marks in pixels
const int BorderTop = 20;

/// Space to the left of the scale in pixels
const int BorderLeft = 10;

/// Space to the right of the scale in pixels
const int BorderRight = 20;

/// The spacing between ticks on the timeline in pixels
const int TickSpacing = 3;

/// The length of a short tick mark in pixels
const int TickShort = 10;

/// The length of a long tick mark in pixels
const int TickLong = 20;

IMPLEMENT_DYNCREATE(CViewTimeline, CScrollView)

/** Constructor */
CViewTimeline::CViewTimeline()
{
	mPointer = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/pointer-down.png"));
	assert(mPointer->GetLastStatus() == Ok);
}

/** Destructor */
CViewTimeline::~CViewTimeline()
{
}




/** Handle the initial update for this window */
void CViewTimeline::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    int sbHeight = GetSystemMetrics(SM_CXHSCROLL);
    CSize sizeTotal(200, Height - sbHeight - 20);
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/** Draw this window 
 * \param pDC Device context */
void CViewTimeline::OnDraw(CDC* pDC)
{

	// Get the timeline
	CTimeline* timeline = GetPicture()->GetTimeline();

	// Set the scroll system correctly
	CSize sizeTotal(timeline->GetNumFrames() * TickSpacing + BorderLeft + BorderRight, WindowHeight);
	SetScrollSizes(MM_TEXT, sizeTotal);

    CDoubleBufferDC dbDC(pDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context


	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 10);

	SolidBrush brush(Color(0, 0, 0));

	CRect rect;
	GetClientRect(&rect);
	int hit = rect.Height();
	int wid = rect.Width();

	//num of ticks
	int x = 10;
	int y1 = 20;
	int y2 = 30;
	int tickNum = timeline->GetNumFrames();
	Pen tickpen(Color(0, 0, 0), 1);
	for (int i = 0; i <= tickNum; i++)
	{
		y2 = y1 + 10;
		x += 3;
		int rate = timeline->GetFrameRate();
		int remainder = i % rate;
		bool onSecond = remainder == 0;

		if (onSecond)
		{
			y2 += 10;
			// Convert the tick number to seconds in a string
			std::wstringstream str;
			str << i / timeline->GetFrameRate();
			std::wstring wstr = str.str();

			RectF size;
			PointF origin((Gdiplus::REAL)x- (Gdiplus::REAL)5,(Gdiplus::REAL)(y2)+(Gdiplus::REAL)5.0);
			graphics.DrawString(wstr.c_str(), wstr.size(), &font, origin,&brush);
		}
		graphics.DrawLine(&tickpen, x, y1, x, y2);
		std::unique_ptr<Gdiplus::Bitmap> mImage = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/pointer-down.png"));
		//int time = (int)timeline->GetCurrentTime();

		double time = timeline->GetCurrentTime();
		graphics.DrawImage(mImage.get(), (INT)((10-2)+3.0*time*(double)(timeline->GetFrameRate())), 20,
			mImage->GetWidth(), mImage->GetHeight());
	}
}


/** Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context 
 * \return FALSE */
BOOL CViewTimeline::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

/** Handle a press of the keyframe set button on the toolbar
*/
void CViewTimeline::OnEditSetkeyframe()
{
	for (auto actor : *GetPicture())
	{
		actor->SetKeyframe();
	}
}


 /** Handle the Edit>Delete Keyframe menu option */
 void CViewTimeline::OnEditDeletekeyframe()
 {
	 for (auto actor : *GetPicture())
	 {
		 actor->DeleteKeyframe();
	 }
 }

 void CViewTimeline::UpdateObserver()
 {
	 Invalidate();
 }

 // Doxygen sometimes gets confused by these message 
 // maps, since they look like functions. I've found
 // it helps to move them to the end of the file.
 BEGIN_MESSAGE_MAP(CViewTimeline, CScrollView)
	 ON_WM_CREATE()
	 ON_WM_ERASEBKGND()
	 ON_COMMAND(ID_EDIT_SETKEYFRAME, &CViewTimeline::OnEditSetkeyframe)
	 ON_COMMAND(ID_EDIT_DELETEKEYFRAME, &CViewTimeline::OnEditDeletekeyframe)
	 ON_WM_LBUTTONDOWN()
	 ON_WM_MOUSEMOVE()
	 ON_WM_LBUTTONUP()
 END_MESSAGE_MAP()

 void CViewTimeline::OnLButtonDown(UINT nFlags, CPoint point)
 {
	 // Convert mouse coordinates to logical coordinates
	 CClientDC dc(this);
	 OnPrepareDC(&dc);
	 dc.DPtoLP(&point);

	 int x = point.x;

	 // Get the timeline
	 CTimeline* timeline = GetPicture()->GetTimeline();
	 int pointerX = (int)(timeline->GetCurrentTime() *
		 timeline->GetFrameRate() * TickSpacing + BorderLeft);

	 mMovingPointer = x >= pointerX - (int)mPointer->GetWidth() / 2 &&
		 x <= pointerX + (int)mPointer->GetWidth() / 2;

	 if (mMovingPointer)
	 {
		 GetPicture()->SetAnimationTime(((double)x - 8.0) / ((double)timeline->GetFrameRate() * 3.0));
		 GetPicture()->UpdateObservers();
	 }
	 __super::OnLButtonDown(nFlags, point);
 }


 void CViewTimeline::OnMouseMove(UINT nFlags, CPoint point)
 {
	 // TODO: Add your message handler code here and/or call default


	 // Convert mouse coordinates to logical coordinates
	 CClientDC dc(this);
	 OnPrepareDC(&dc);
	 dc.DPtoLP(&point);
	 int x = point.x;
	 CTimeline* timeline = GetPicture()->GetTimeline();

	 int temp = mPointer->GetWidth();
	 bool inBound = x >= BorderLeft-2 && x <= BorderLeft + timeline->GetNumFrames() * 3-2;


	 if (mMovingPointer && inBound)
	 {
		 GetPicture()->SetAnimationTime(((double)x - 8.0) / ((double)timeline->GetFrameRate() * 3.0));
		 GetPicture()->UpdateObservers();
	 }

	 __super::OnMouseMove(nFlags, point);
 }


 void CViewTimeline::OnLButtonUp(UINT nFlags, CPoint point)
 {
	 // TODO: Add your message handler code here and/or call default
	 mMovingPointer = false;
	 __super::OnLButtonUp(nFlags, point);
 }
