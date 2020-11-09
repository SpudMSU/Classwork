#pragma once
#include "Drawable.h"
#include "Tree.h"
#include "FruitTree.h"
#include "Fruit.h"
#include "AnimChannelAngle.h"
#include "Timeline.h"
#include "TreeSeedDlg.h"
#include <string>
#include "BasketAdapter.h"


///adapter class for the tree
class CTreeAdapter :
	public CDrawable
{
public:

	///constructor
	///\param name
	///\param delay is the time delay to grow the tree
	///\param x
	///\param y
	///\param harvest
	///\param b
	///\param seed
	CTreeAdapter(const std::wstring name, int delay, int x, int y, int harvest, std::shared_ptr<CBasketAdapter> b, int seed = -1);


	/** Default constructor disabled */
	CTreeAdapter() = delete;
	/** Copy constructor disabled */
	CTreeAdapter(const CTreeAdapter&) = delete;
	/** Assignment operator disabled */
	void operator=(const CTreeAdapter&) = delete;

	///draw function
	///\param graphics
	void Draw(Gdiplus::Graphics* graphics);

	///harvest function
	///\return  the harvested fruit
	std::vector<std::shared_ptr<CFruit>> Harvest() { return mTree->Harvest(); }


	/** Test to see if we have been clicked on by the mouse
	 * \param pos Position to test
	 * \return true if clicked on */
	bool HitTest(Gdiplus::Point pos) { return false; }

	///function for show dialog box
	void ShowDialogBox();
	
private:

	///delay member variable
	int mDelay = 0;

	///tree member variable
	std::shared_ptr<CTree> mTree;

	///member variable to set when to harvest the apples
	int mHarvestFrame = 500;


	///basket the tree is using
	std::shared_ptr<CBasketAdapter> mBasket;
};

