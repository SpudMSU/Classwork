#pragma once
#include <iostream>
#include "TreeItemVisitor.h"
#include <vector>
class CFruitTree;
class CLimb;
/** tree item class. Base class for leaves and fruit */
class CTreeItem
{
private:

	///angle sum member variable
	double mAngleSum = 0;

	///parent member variable
	CLimb* mParent;

	///root node
	CLimb* mRoot;

	///depth member variable
	int mDepth = 0;

	///age member variable
	int mAge = 0;

	///angle member variable
	double mAngle = 0;

	///member variable to tell if the tree item has a leaf
	bool mHasLeaf = false;

	///Tree item will belong too
	CFruitTree* mTree;

	///x position
	int mX = 0;

	///y position
	int mY = 0;

public:

	///getter for leaf bool variable
	///\return bool value of mHasLeaf
	bool HasLeaf() { return mHasLeaf; }

	///setter for mLead
	///\param v is value too set bool too
	void SetLeaf(bool v) { mHasLeaf = v; }

	/** Default constructor disabled */
	CTreeItem() = delete;
	/** Copy constructor disabled */
	CTreeItem(const CTreeItem&) = delete;
	/** Assignment operator disabled */
	void operator=(const CTreeItem&) = delete;

	///constructor
	///\param tree
	///\param angle
	CTreeItem(CFruitTree *tree, double angle) { mTree = tree; mAngle = angle; }


	///draw function
	///\param graphics
	///\param pAngle
	virtual void Draw(Gdiplus::Graphics* graphics, double pAngle) {}

	///grow function
	///\param lenG is random number to determine lenght grow speed
	///\param angle is random angle of right child
	///\param angle2 is random angle of left child
	///\param dev is a random number to deviate the random numbers more
	///\param newlimbs is a vector containing new limbs to add to mItem
	virtual void Grow(double lenG, double angle, double angle2, double dev, std::vector<std::shared_ptr<CTreeItem>>* newlimbs){}


	///accept function for the visitor
	///\param visitor
	virtual void Accept(CTreeItemVisitor* visitor){}

	///setter for the size
	///\param size
	virtual void SetSize(double size) {}


	///setter for age
	///\param age
	void SetAge(int age) { mAge = age; }

	///getter for age
	///\return mAge
	int GetAge() { return mAge; }

	///getter for location
	///\return location
	int GetX() { return mX; }

	///getter for y position
	///\return y
	int GetY() { return mY; }

	///getter for the tree
	///\return the tree
	CFruitTree* GetTree() { return mTree; }

	///setter for location
	///\param x
	///\param y
	void SetLocation(int x, int y) { mX = x; mY = y; }

	///getter for depth
	///\return the depth
	int GetDepth() { return mDepth; }

	///setter for depth
	///\param depth
	void SetDepth(int depth) { mDepth = depth; }

	///setter for parent
	///\param limb is the limb to set as parent
	void SetParent(CLimb* limb) { mParent = limb; }

	///getter for parent
	///\return parent
	CLimb* GetParent() { return mParent; }


	///sets the root node
	///\param root
	void SetRoot(CLimb* root) { mRoot = root; }

	///getter for the root
	///\return the root
	CLimb* GetRoot() { return mRoot; }

	///getter for angle
	///\return the angle
	double GetAngle() { return mAngle; }

	///setter for angle
	///\param angle
	void SetAngle(double angle) { mAngle = angle; }

	///getter for angle sum
	///\return the angle sum
	double GetAngleSum() { return mAngleSum; }

	///setter for angle sum
	///\param angle
	void SetAngleSum(double angle) { mAngleSum = angle; }

	///adjusts location of the item
	virtual void AdjustLocation() {}
};


