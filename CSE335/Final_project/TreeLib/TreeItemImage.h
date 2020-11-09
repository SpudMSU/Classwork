#pragma once
#include "TreeItem.h"
#include <string>
/**Base class for tree items that use images*/
class CTreeItemImage : public CTreeItem
{
protected:

	///image path
	Gdiplus::Bitmap* mImage;

	///bool to tell if object is at max size
	bool mMaxSize = false;

public:
	/** Default constructor disabled */
	CTreeItemImage() = delete;
	/** Copy constructor disabled */
	CTreeItemImage(const CTreeItemImage&) = delete;
	/** Assignment operator disabled */
	void operator=(const CTreeItemImage&) = delete;

	///constructor
	///\param tree
	///\param angle
	///\param image
	CTreeItemImage(CFruitTree* tree, double angle, Gdiplus::Bitmap* image);

	///draw function
	///\param graphics
	///\param pAngle
	virtual void Draw(Gdiplus::Graphics* graphics, double pAngle);

	///grow function
	///\param lenG is random number to determine lenght grow speed
	///\param angle is random angle of right child
	///\param angle2 is random angle of left child
	///\param dev is a random number to deviate the random numbers more
	///\param newlimbs is a vector containing new limbs to add to mItem
	virtual void Grow(double lenG, double angle, double angle2, double dev, std::vector<std::shared_ptr<CTreeItem>>* newlimbs) {}
};