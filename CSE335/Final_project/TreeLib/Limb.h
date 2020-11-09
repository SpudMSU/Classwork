#pragma once
#include <vector>
#include "TreeItem.h"
#include <string>

/**Class for tree branches*/
class CLimb :
	public CTreeItem
{
private:


	///list of all children
	std::vector<std::shared_ptr<CTreeItem>> mChildren;

	///length
	double mLength = 10;

	///width
	double mWidth = 3;

	///bool to see if it has been spawned (drawn on) yet
	bool mSpawned = false;

	///member variable for ending x position
	double endX = 0; 

	///member variable for ending y position
	double endY = 0;

public:
	/** Default constructor disabled */
	CLimb() = delete;
	/** Copy constructor disabled */
	CLimb(const CLimb&) = delete;
	/** Assignment operator disabled */
	void operator=(const CLimb&) = delete;

	///constructor, inherits tree item constructor
	///\param tree
	///\param angle
	CLimb(CFruitTree* tree, double angle);

	///function to spawn item
	void Spawn();

	///grow function
	///\param lenG is random number to determine lenght grow speed
	///\param angle is random angle of right child
	///\param angle2 is random angle of left child
	///\param dev is a random number to deviate the random numbers more
	///\param newlimbs is a vector containing new limbs to add to mItem
	virtual void Grow(double lenG, double angle, double angle2, double dev, std::vector<std::shared_ptr<CTreeItem>>* newlimbs) override;

	///function to check if spawned
	///\return if it has been spawned yet
	bool CheckSpawned() { return mSpawned; }

	///adds a child
	///\param item is the child
	void AddChild(std::shared_ptr<CTreeItem> item);

	///function to give leaf
	virtual void GiveLeaf();

	///draw funcion
	///\param graphics
	///\param pAngle is the angle sum of the parents
	virtual void Draw(Gdiplus::Graphics *graphics, double pAngle);

	///getter for the length
	///\return the length
	double GetLength() { return mLength; }

	///setter for the length
	///\param len is the length too set
	void SetLength(double len) { mLength = len; }

	///getter for width
	///\returns the width
	double GetWidth() { return mWidth; }

	///setter for the width
	///\param len is the length too set
	void SetWidth(double len) { mWidth = len; }

	///getter for the child count
	///\return the child count
	int GetChildCount() { return mChildren.size(); }

	///setter for the ending x position
	///\param x
	void SetEndX(double x) { endX = x; }

	///setter for the ending y position
	///\param y
	void SetEndY(double y) { endY = y; }

	///getter for ending x position
	///\return ending x position
	double GetEndX() { return endX; }

	///function to adjust the location
	virtual void AdjustLocation() {}

	///getter for ending y position
	///\return ending y position
	double GetEndY() { return endY; }
};

