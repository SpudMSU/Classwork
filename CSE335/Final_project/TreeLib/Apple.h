#pragma once
#include "Fruit.h"
#include "TreeItemImage.h"
/**Class for apples*/
class CApple :
	public CFruit, public CTreeItemImage
{
private:

	///size of the apple
	double mSize = 10;

	///tells if has been harvested
	bool mHarvested = false;


public:

	///default constructor
	///\param tree
	///\param angle
	///\param image
	CApple(CFruitTree* tree, double angle, Gdiplus::Bitmap* image) : CTreeItemImage(tree, angle, image) {}
	

	/** Default constructor disabled */
	CApple() = delete;
	/** Copy constructor disabled */
	CApple(const CApple&) = delete;
	/** Assignment operator disabled */
	void operator=(const CApple&) = delete;

	///adjusts the location according to parents
	void AdjustLocation() override;

	///Accept function for the visitor
	///\param visitor
	void Accept(CTreeItemVisitor* visitor) override { visitor->VisitFruit(); }

	/**
 * Set the position of the fruit in the basket
 *
 * This position is relative to the basket, so
 * it will be added to the basket location passed
 * to DrawInBasket when we draw it
 * \param x X position in pixels
 * \param y Y position in pixels
 */
	void SetBasketPosition(int x, int y) { SetLocation(x, y); }

	/**
	 * Draw the fruit in the position specified
	 * \param graphics The graphics object to draw on
	 * \param pAngle is the angle sum of the parrent
	 */
	void Draw(Gdiplus::Graphics* graphics, double pAngle);
	/**
	 * Draw the fruit in the basket
	 * \param graphics The graphics object to draw on
	 * \param x X location of the basket
	 * \param y Y location of the basket
	 */
	void DrawInBasket(Gdiplus::Graphics* graphics, int x, int y);

	///setter for size member variable
	///\param size is he size being set
	void SetSize(double size) { mSize = size; }

	///grow function
	///\param lenG is random number to determine lenght grow speed
	///\param angle is random angle of right child
	///\param angle2 is random angle of left child
	///\param dev is a random number to deviate the random numbers more
	///\param newlimbs is a vector containing new limbs to add to mItem
	void Grow(double lenG, double angle, double angle2, double dev, std::vector<std::shared_ptr<CTreeItem>>* newlimbs);
};

