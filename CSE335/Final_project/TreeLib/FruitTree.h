#pragma once
#include "Tree.h"

#include <iostream>
#include <vector>
#include "ActualBasket.h"
#include "PseudoRandom.h"
class CLimb;
class CTreeItem;
/** Class for a tree which can grow fruit. Derived from CTree*/
class CFruitTree :
	public CTree
{
private:


	///Vector which contains all the items
	std::vector<std::shared_ptr<CTreeItem>> mItems;

	///vector containing fruit
	std::vector<std::shared_ptr<CFruit>> mFruit;

	///wind speed member variable
	double mWindSpeed = 0;

	///x position
	int mX = 700;
	///y position
	int mY = 550;

	///frame member variable
	int mFrame = 0;

	///used to check if harvested or not
	bool mHarvested = false;

	///seed member variable
	int mSeed = 0;

	///member variable for the basket
	CBasket* mBasket;

	///member variable for fruit size
	double mFruitSize = 10;

	///member variable to hold the leaf image
	Gdiplus::Bitmap* mLeafIm;

	///member variable to hold the fruit image
	Gdiplus::Bitmap* mFruitIm;

	///member variable to tell when tree has been reset
	bool mReset = false;
public:

	///sets leaf image
	///\param image
	void SetLeafImage(Gdiplus::Bitmap* image) { mLeafIm = image; }

	///sets the fruit image
	///\param image
	void SetFruitImage(Gdiplus::Bitmap* image) { mFruitIm = image; }

	///Grow function
	void Grow();

	///Harvest function
	///\return vector of all the fruit harvested
	virtual std::vector<std::shared_ptr<CFruit>> Harvest();

	///Draw function for tree
	///\param graphics
	void DrawTree(Gdiplus::Graphics *graphics) override;

	///sets location
	///\param x position
	///\param y position
	void SetLocation(int x, int y) { mX = x; mY = y; }


	///Getter for location
	///\return x,y position of the tree
	Gdiplus::Point GetLocation() { return Gdiplus::Point(mX, mY); }

	///setter for wind speed
	///\param speed is the wind speed to set mWindSpeed too
	void SetWindSpeed(double speed);

	///setter for tree fram
	///\param frame to set tree too
	void SetTreeFrame(int frame);

	///Getter for the tree frame
	///\return the tree frame
	int GetTreeFrame() { return mFrame; }

	///checks the harvest boolean
	///\returns true if harvested recently, false otherwise
	bool CheckHarvest() { return mHarvested; }

	///getter for the seed
	///\return the seed
	int GetSeed() { return mSeed; }

	///setter for the seed
	///\param seed
	void SetSeed(int seed);
	
	///sets the basket being used
	///\param basket
	void SetBasket(CBasket* basket) { mBasket = basket; }

	///adds item to the tree
	///\param item
	void AddItem(std::shared_ptr<CTreeItem> item) { mItems.push_back(item); }

	///sets the root location
	///\param x
	///\param y
	void SetRootLocation(int x, int y);

	///reset function for tree
	void Reset();

	///getter for leaf image
	///\return leaf image
	Gdiplus::Bitmap* GetLeafImage() { return mLeafIm; }

	///getter for fruit image
	///\return fruit image
	Gdiplus::Bitmap* GetFruitImage() { return mFruitIm; }

	///decreases fruit size
	void DecreaseFruitSize() { mFruitSize -= .008;}

	///getter for fruit size
	///\return the fruit size
	double GetFruitSize() { return mFruitSize; }

	///adds fruit to the tree
	///\param fruit too add to the tree
	void AddFruit(std::shared_ptr<CFruit> fruit) { mFruit.push_back(fruit); }

};
