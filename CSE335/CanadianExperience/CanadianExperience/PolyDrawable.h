/**
 * \file PolyDrawable.h
 *
 * \author Spencer D Cassetta
 *
 *
 */

#pragma once
#include <iostream>
#include <vector>

#include "Drawable.h"
/**
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
class CPolyDrawable : public CDrawable
{
public:

	/** Default constructor disabled */
	CPolyDrawable() = delete;
	/** Copy constructor disabled */
	CPolyDrawable(const CPolyDrawable&) = delete;
	/** Assignment operator disabled */
	void operator=(const CPolyDrawable&) = delete;

	///constructor inherited
	///\param name
	CPolyDrawable(const std::wstring& name) : CDrawable(name) {}

	/**Getter for the color
	*\return the color*/
	Gdiplus::Color GetColor() { return mColor; }

	/**Setter for the color
	*\param color to set it too*/
	void SetColor(Gdiplus::Color color) { mColor = color; }


	/** draws the drawable
	*\param graphics to use to draw */
	void Draw(Gdiplus::Graphics *graphics);

	/** test if you hit the actor
	*\param pos is the point to hittest
	*\return the drawable that you hit*/
	bool HitTest(Gdiplus::Point pos);

	/**Adds a point
	*\param point to add*/
	void AddPoint(Gdiplus::Point point);
private:
	///color
	Gdiplus::Color mColor = Gdiplus::Color(0,0,0);
	///point array
	std::vector<Gdiplus::Point> mPoints;
};

