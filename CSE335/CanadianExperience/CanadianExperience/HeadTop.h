/**
 * \file HeadTop.h
 *
 * \author Spencer D Cassetta
 *
 *
 */

#pragma once
#include "ImageDrawable.h"

/**Class to create the headtop*/
class CHeadTop : public CImageDrawable
{
public:
	///constructor
	///\param name
	///\param filename
	CHeadTop(const std::wstring& name, const std::wstring& filename) :CImageDrawable(name, filename){}

	/** Default constructor disabled */
	CHeadTop() = delete;
	/** Copy constructor disabled */
	CHeadTop(const CHeadTop&) = delete;
	/** Assignment operator disabled */
	void operator=(const CHeadTop&) = delete;

	/** Draws the headtop
	*\param graphics it uses to draw */
	void Draw(Gdiplus::Graphics* graphics);

	/**function to see if object is movable
	*\return true because it is movable*/
	bool IsMovable() { return true; }

	/** transforms point to be rotated with the object
	*\param p is the old point
	*\return new point*/
	Gdiplus::Point CHeadTop::TransformPoint(Gdiplus::Point p);
};

