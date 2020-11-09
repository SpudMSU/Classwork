/**
* \file Item.h
*
* \author Spencer Cassetta
*
* Base class for any item in our aquarium.
*/

#pragma once
#include <memory>
#include<iostream>
#include "XmlNode.h"

class CAquarium;

/**
* Base class for any item in our aquarium.
*/
class CItem
{
public:

	/// Get the aquarium this item is in
	/// \returns Aquarium pointer
	CAquarium* GetAquarium() { return mAquarium; }


	/**
	* Function that loads in the aquarium from node which contains xml info
	*\param node is the node that contains the values
	*\returns none
	*/
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Default constructor (disabled)
	CItem() = delete;

	/// Copy constructor (disabled)
	CItem(const CItem&) = delete;

	///destructor
	virtual ~CItem();

	/// Handle updates for animation
	/// \param elapsed The time since the last update
	virtual void Update(double elapsed) {}


	/** The X location of the item
	* \returns X location in pixels */
	double GetX() const { return mX; }

	/** The Y location of the item
	* \returns Y location in pixels */
	double GetY() const { return mY; }

	/// Set the item location
	/// \param x X location
	/// \param y Y location
	///\param updated marks whether SetLocation has already been called to prevent recursion
	void SetLocation(double x, double y, bool updated=false) { mX = x; mY = y; }

	/// Draw this item
	/// \param graphics Graphics device to draw on
	virtual void Draw(Gdiplus::Graphics* graphics);

	/** 
	* Saves the aquarium into an xml node
	*\param node is the node it saves the values into
	*\return the node in which xml data is saved
	*/
	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/** 
	* Test this item to see if it has been clicked on
	* \param x X location on the aquarium to test
	* \param y Y location on the aquarium to test
	* \return true if clicked on */
	bool HitTest(int x, int y);

	/// Set the mirror status
   /// \param m New mirror flag
	void SetMirror(bool m) { mMirror = m; }


protected:

	/** 
	* Constructor
	* \param aquarium The aquarium this item is a member of
	* \param filename is filename of aquarium
	*/
	CItem(CAquarium* aquarium, const std::wstring& filename);

private:

	bool mMirror = false;   ///< True mirrors the item image

	/// The aquarium this item is contained in
	CAquarium* mAquarium;

	///image of the fish
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;

	/// Item location in the aquarium
	double  mX = 0;     ///< X location for the center of the item
	double  mY = 0;     ///< Y location for the center of the item
};