#include "pch.h"
#include "FruitTree.h"
#include "TreeItem.h"
#include "Limb.h"
#include <sstream>
#include "TreeFactory.h"
#include "PseudoRandom.h"
#include "RightLimb.h"
#include "LeftLimb.h"
#include "Root.h"
#include "TreeItemVisitor.h"
#include "TreeItemImage.h"
#include "Leaf.h"
#include "Apple.h"
using namespace Gdiplus;
using namespace std;


bool x = false;

void CFruitTree::DrawTree(Gdiplus::Graphics *graphics) {
	for (auto i : mItems)
	{//go through all items
		i->AdjustLocation(); // the tree grew and the items need to have their location reset based on parents new position
		double angle = i->GetParent()->GetAngleSum();
		//then call the draw function
		i->Draw(graphics, angle);
	}
}

///Grow function
void CFruitTree::Grow()
{

	std::vector<std::shared_ptr<CTreeItem>> newlimbs;

	CPseudoRandom rand(GetSeed());
	CTreeItemVisitor visitor;
	double lenG = rand.Random(20, 45);
	double angle1 = ((double)rand.Random(3, 10) / 10.0);
	double angle2 = ((double)rand.Random(3, 10) / 10.0);
	double dev = (rand.Random(0, 5) / 100);
	for (auto i : mItems)
	{//go through all items
		//and call grow for all of them
		i->Grow(lenG, angle1, angle2, dev, &newlimbs);
	}
	for (auto i : newlimbs)
	{//add all the new limbs to mItems
		mItems.push_back(i);
	}
	
}

///Harvest function
///\return vector of all the fruit harvested


void CFruitTree::SetRootLocation(int x, int y)
{
	mX = x;
	mY = y;
}

void CFruitTree::Reset()
{
	//resets tree back to only 1 limb
	mItems.clear();
	auto limb1 = make_shared<CRoot>(&(*this), 0);
	limb1->SetDepth(0);
	limb1->SetRoot(&(*limb1));
	limb1->SetParent(&(*limb1));
	AddItem(limb1);
	mFrame = 0;
	mFruitSize = 10;
	mReset = true;
}
void CFruitTree::SetTreeFrame(int frame) 
{ 
	bool r = false;
	if (frame < mFrame)
	{//if frames smaller, reset
		Reset();
	}
	while (frame > mFrame)
	{//grow to the desired frame
		mFrame++;
		Grow();
	}
	if (mReset)
	{//if it was reset, reset the windspeed aswell
		double speed = mWindSpeed;
		mWindSpeed = 0;
		SetWindSpeed(speed);
		mReset = false;
	}
}

std::vector<std::shared_ptr<CFruit>> CFruitTree::Harvest()
{
	CTreeItemVisitor Visitor;
	for (size_t i=0; i<mItems.size(); i++)
	{//for all items
		auto item = mItems[i];
		item->Accept(&Visitor);
		if (Visitor.isFruit())
		{//if its a fruit, remove the item 
			item->SetSize(mFruitSize);//save the size
			mItems.erase(mItems.begin() + i);
			i = 0;
		}
		Visitor.Reset();
	}
	///save the fruit array, clear it, then save it
	auto save = mFruit;
	mFruit.clear();
	return save;
}

void CFruitTree::SetWindSpeed(double speed) 
{
	double add = speed - mWindSpeed;
	mWindSpeed = speed;
	for (auto i : mItems)
	{
		//for all items
		if (i->GetDepth() == 1)
		{//if its the 2nd level

			//add to the angle based upon the difference in wind speeds
			i->SetAngle(i->GetAngle() + (-add / 300));
		}
	}
}

void CFruitTree::SetSeed(int seed) 
{ 
	//set the seed and reset the tree
	mSeed = seed; 
	int frame = mFrame;
	Reset();
	SetTreeFrame(frame);
}