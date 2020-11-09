#pragma once
#include "Limb.h"

///class for the right limb
class CRightLimb : public CLimb
{
public:
	/** Default constructor disabled */
	CRightLimb() = delete;
	/** Copy constructor disabled */
	CRightLimb(const CRightLimb&) = delete;
	/** Assignment operator disabled */
	void operator=(const CRightLimb&) = delete;

	///new default constructor for right limb
	///\param tree
	///\param angle
	CRightLimb(CFruitTree* tree, double angle) : CLimb(tree, angle) {}


	///function to adjust the location
	void AdjustLocation() override;

	///grow function
	///\param lenG is random number to determine lenght grow speed
	///\param angle is random angle of right child
	///\param angle2 is random angle of left child
	///\param dev is a random number to deviate the random numbers more
	///\param newlimbs is a vector containing new limbs to add to mItem
	virtual void Grow(double lenG, double angle, double angle2,  double dev, std::vector<std::shared_ptr<CTreeItem>>* newlimbs) override;
};

