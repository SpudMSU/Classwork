/**
 * \file HeadTop.cpp
 *
 * \author Spencer D Cassetta
 *
 *
 */


#include "pch.h"
#include "HeadTop.h"

///conversion constant
const double RtoD = 57.295779513;
/** Transform a point from a location on the bitmap to
*  a location on the screen.
* \param  p Point to transform
* \returns Transformed point
*/
Gdiplus::Point CHeadTop::TransformPoint(Gdiplus::Point p)
{
	// Make p relative to the image center
	Gdiplus::Point x = p - GetCenter();
	// Rotate as needed and offset
	return RotatePoint(x, mPlacedR) + mPlacedPosition;
}

void CHeadTop::Draw(Gdiplus::Graphics* graphics) {

	float wid = 15.0f;
	float hid = 20.0f;
	CImageDrawable::Draw(graphics);
	Gdiplus::SolidBrush brush(Gdiplus::Color::Black);
	Gdiplus::SolidBrush brush2(Gdiplus::Color::Gray);

	Gdiplus::Point p1(TransformPoint(Gdiplus::Point(40, 85)));
	Gdiplus::Point p2(TransformPoint(Gdiplus::Point(70, 85)));
	Gdiplus::Point p3(TransformPoint(Gdiplus::Point(40, 65)));
	Gdiplus::Point p4(TransformPoint(Gdiplus::Point(70, 65)));
	auto state = graphics->Save();
	graphics->TranslateTransform((Gdiplus::REAL)p1.X, (Gdiplus::REAL)p1.Y);
	graphics->RotateTransform((float)(-mPlacedR * RtoD));
	graphics->FillEllipse(&brush, -wid/ 2, -hid / 2, wid, hid);
	graphics->Restore(state);

	state = graphics->Save();
	graphics->TranslateTransform((Gdiplus::REAL)p2.X, (Gdiplus::REAL)p2.Y);
	graphics->RotateTransform((float)(-mPlacedR * RtoD));
	graphics->FillEllipse(&brush, -wid / 2, -hid / 2, wid, hid);
	graphics->Restore(state);
	
	state = graphics->Save();
	graphics->TranslateTransform((Gdiplus::REAL)p3.X, (Gdiplus::REAL)p3.Y);
	graphics->RotateTransform((float)(-mPlacedR * RtoD));
	graphics->FillRectangle(&brush2, -wid / 2, -hid / 2, wid, 5.0f);
	graphics->Restore(state);

	state = graphics->Save();
	graphics->TranslateTransform((Gdiplus::REAL)p4.X, (Gdiplus::REAL)p4.Y);
	graphics->RotateTransform((float)(-mPlacedR * RtoD));
	graphics->FillRectangle(&brush2, -wid / 2, -hid / 2, wid, 5.0f);
	graphics->Restore(state);
}