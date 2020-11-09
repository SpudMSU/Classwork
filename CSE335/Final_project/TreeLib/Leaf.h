#pragma once
#include "TreeItemImage.h"
#include <string>
#include "FruitTree.h"
/**Class for leaf objects*/
class CLeaf :
	public CTreeItemImage
{
public:

	/** Default constructor disabled */
	CLeaf() = delete;
	/** Copy constructor disabled */
	CLeaf(const CLeaf&) = delete;
	/** Assignment operator disabled */
	void operator=(const CLeaf&) = delete;

	///new default constructor for lead
	///\param tree
	///\param angle
	///\param image
	CLeaf(CFruitTree* tree, double angle, Gdiplus::Bitmap* image) : CTreeItemImage(tree, angle, image) {}

	///function to adjust the location
	void AdjustLocation() override;

	///grow function
	///\param lenG is random number to determine lenght grow speed
	///\param angle is random angle of right child
	///\param angle2 is random angle of left child
	///\param dev is a random number to deviate the random numbers more
	///\param newlimbs is a vector containing new limbs to add to mItem
	void Grow(double lenG, double angle, double angle2, double dev, std::vector<std::shared_ptr<CTreeItem>>* newlimbs) {}
};

