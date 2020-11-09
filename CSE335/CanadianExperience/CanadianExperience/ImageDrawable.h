/**
 * \file ImageDrawable.h
 *
 * \author Spencer D Cassetta
 *
 *
 */

#include "pch.h"
#include "Drawable.h"
/**Is the class that creates objects which can be created with Images
*/
class CImageDrawable :public CDrawable
{
public:
	///constructor
	///\param name
	CImageDrawable(const std::wstring& name, const std::wstring& filename);

	/** Default constructor disabled */
	CImageDrawable() = delete;
	/** Copy constructor disabled */
	CImageDrawable(const CImageDrawable&) = delete;
	/** Assignment operator disabled */
	void operator=(const CImageDrawable&) = delete;

	/** Draws the object
	*\param graphics it uses to draw */
	void Draw(Gdiplus::Graphics* graphics);

	/** test if you hit the actor
	*\param pos is the point to hittest
	*\return the drawable that you hit*/
	bool HitTest(Gdiplus::Point pos);


	/**Getter for the center
	*\return the center point*/
	Gdiplus::Point GetCenter() { return mCenter; }


	/**Setter for the center
	*\param center is point to set center too*/
	void SetCenter(Gdiplus::Point center) { mCenter = center; }

protected:

	///member variable for the image
	std::unique_ptr<Gdiplus::Bitmap> mImage;
private:
	///member variable for the center
	Gdiplus::Point mCenter = Gdiplus::Point(0, 0);
};
