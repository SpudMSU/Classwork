#pragma once

///visitor class for CTreeItem
class CTreeItemVisitor
{
public:

	///reset function
	void Reset() { mFruit = false; }

	///function for when it visits fruit
	void VisitFruit() { mFruit = true; }

	///function to tell if it visited a fruit
	///\return mFruit
	bool isFruit() { return mFruit; }


private:
	///member variable for if it visited a fruit
	bool mFruit = false;
};

