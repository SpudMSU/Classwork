#include "pch.h"
#include "ActualBasket.h"
#include <string>
#include "PseudoRandom.h"
using namespace Gdiplus;


CActualBasket::CActualBasket()
{
	mImage = Gdiplus::Bitmap::FromFile(L"images/basket.png");
	if (mImage->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/basket.png");
	}
	mImageFront = Gdiplus::Bitmap::FromFile(L"images/basket-front.png");
	if (mImage->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/basket-front.png");
	}
}

/**
* Draw the basket at the currently specified location
* \param graphics GDI+ Graphics object
*/
void CActualBasket::DrawBasket(Gdiplus::Graphics* graphics)
{

	//draw the basket
	graphics->DrawImage(mImage, mX, mY-mImage->GetHeight(),
		mImage->GetWidth(), mImage->GetHeight());
	CPseudoRandom randobj;
	for (auto i : mBasket)
	{

		//draw all items in the basket randomly
		int y = randobj.Random(mY - mImage->GetHeight()+50,mY-30);
		int x = randobj.Random(mX+25, mX + mImage->GetWidth()-25);
		i->SetBasketPosition(x, y);
		i->DrawInBasket(graphics, x, y);
	}

	//draw the front of the basket
	graphics->DrawImage(mImageFront, mX, mY - mImage->GetHeight(),
		mImage->GetWidth(), mImage->GetHeight());
}

/**
 * Add fruit to the basket
 * \param fruit Vector of fruit objects
 */
void CActualBasket::AddToBasket(std::vector <std::shared_ptr<CFruit>> fruit)
{
	for (auto i : fruit)
	{
		///add all the items in the vector to the basket
		mBasket.push_back(i);
	}
}

/**
 * Empty all fruit from the basket
 */
void CActualBasket::EmptyBasket()
{
	//clear the basket vector
	mBasket.clear();
}