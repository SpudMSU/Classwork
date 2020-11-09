#pragma once
#include "Basket.h"
#include "Fruit.h"
#include <vector>

///Class for the actual basket being used
class CActualBasket :
	public CBasket
{
private:

	///basket x position
	int mX = 0;

	///basket y position
	int mY = 0;

	///fruit in the basker
	std::vector<std::shared_ptr<CFruit>> mBasket;

	///image for the basket
	Gdiplus::Bitmap* mImage;

	///image for the front of the basket
	Gdiplus::Bitmap* mImageFront;


public: 

	///default constructor
	CActualBasket();

	/** Copy constructor disabled */
	CActualBasket(const CActualBasket&) = delete;
	/** Assignment operator disabled */
	void operator=(const CActualBasket&) = delete;

	/**
	* Set the position for the basket.
	* \param x X location (pixels)
	* \param y Y location (pixels)
	*/
	void SetBasketLocation(int x, int y) { mX = x; mY = y; }

	/**
	* Draw the basket at the currently specified location
	* \param graphics GDI+ Graphics object
	*/
	void DrawBasket(Gdiplus::Graphics* graphics);

	/**
	 * Add fruit to the basket
	 * \param fruit Vector of fruit objects
	 */
	void AddToBasket(std::vector < std::shared_ptr<CFruit>> fruit);

	/**
	 * Empty all fruit from the basket
	 */
	void EmptyBasket();
};

