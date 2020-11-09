#pragma once
#include "Limb.h"
///class for left limbs
class CLeftLimb :
	public CLimb
{
public:

	/** Default constructor disabled */
	CLeftLimb() = delete;
	/** Copy constructor disabled */
	CLeftLimb(const CLeftLimb&) = delete;
	/** Assignment operator disabled */
	void operator=(const CLeftLimb&) = delete;

	///new default constructor for left limb
	///\param tree is the tree limb belongs too
	///\param angle is the angle too set
	CLeftLimb(CFruitTree* tree, double angle): CLimb(tree, angle){}

	///adjusts the location of the limb
	void AdjustLocation() override;

	///grow function
	///\param lenG is random number to determine lenght grow speed
	///\param angle is random angle of right child
	///\param angle2 is random angle of left child
	///\param dev is a random number to deviate the random numbers more
	///\param newlimbs is a vector containing new limbs to add to mItem
	virtual void Grow(double lenG, double angle, double angle2, double dev, std::vector<std::shared_ptr<CTreeItem>>* newlimbs) override;
};

