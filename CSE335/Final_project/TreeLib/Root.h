#pragma once
#include "Limb.h"

///class for the root
class CRoot :
	public CLimb
{
public:

	/** Default constructor disabled */
	CRoot() = delete;
	/** Copy constructor disabled */
	CRoot(const CRoot&) = delete;
	/** Assignment operator disabled */
	void operator=(const CRoot&) = delete;

	///constructor for the root
	///\param tree
	///\param angle
	CRoot(CFruitTree* tree, double angle);

	///draw funcion
	///\param graphics
	///\param pAngle
	void Draw(Gdiplus::Graphics* graphics, double pAngle);

	///function to adjust the location
	void AdjustLocation() override;
};

