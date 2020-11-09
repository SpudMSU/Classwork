#pragma once
#include "Drawable.h"
#include "Basket.h"
#include "ActualBasket.h"
#include <string>


///adapter class for the basket
class CBasketAdapter :
	public CDrawable
{
public:

	///constructor
	///\param name
	///\param x
	///\param y
	CBasketAdapter(const std::wstring name, int x, int y);

	/** Default constructor disabled */
	CBasketAdapter() = delete;
	/** Copy constructor disabled */
	CBasketAdapter(const CBasketAdapter&) = delete;
	/** Assignment operator disabled */
	void operator=(const CBasketAdapter&) = delete;

	///draw function
	///\param graphics
	void Draw(Gdiplus::Graphics* graphics) { mBasket->DrawBasket(graphics); }

	/** Test to see if we have been clicked on by the mouse
	 * \param pos Position to test
	 * \return true if clicked on */
	bool HitTest(Gdiplus::Point pos) { return false; }

	/**
	* Add fruit to the basket
	* \param fruit Vector of fruit objects
	*/
	void AddToBasket(std::vector <std::shared_ptr<CFruit>> fruit) { mBasket->AddToBasket(fruit); }

	/**
	 * Empty all fruit from the basket
	 */
	void EmptyBasket() { mBasket->EmptyBasket(); }

private:
	///member variable to hold the basket we are wrapping
	std::shared_ptr<CBasket> mBasket;
};

