/**
 * \file PolyDrawable.cpp
 *
 * \author Spencer D Cassetta
 *
 *
 */

#include "pch.h"
#include "PolyDrawable.h"

using namespace Gdiplus;

void CPolyDrawable::Draw(Gdiplus::Graphics* graphics) {
	SolidBrush brush(mColor);

	// Transform the points
	std::vector<Point> points;
	for (auto point : mPoints)
	{
		points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
	}

	graphics->FillPolygon(&brush, &points[0], (int)points.size());
}
void CPolyDrawable::AddPoint(Gdiplus::Point point) {

	mPoints.push_back(point);
}

/** Test to see if we hit this object with a mouse click
 * \param pos Click position
 * \returns true it hit
 */
bool CPolyDrawable::HitTest(Gdiplus::Point pos)
{
	// Transform the points
	std::vector<Point> points;
	for (auto point : mPoints)
	{
		points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
	}

	GraphicsPath path;
	path.AddPolygon(&points[0], (int)points.size());
	return path.IsVisible(pos) ? true : false;
}