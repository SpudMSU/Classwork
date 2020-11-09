/**
 * \file Fish.h
 *
 * \author Spencer D Cassetta
 *
 * Class that implements the Fish Class and is parent for all other fish
 */

#pragma once
#include "Item.h"


/**
 * Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class CFish : public CItem
{
public:
	/// Default constructor (disabled)
	CFish() = delete;

	/// Copy constructor (disabled)
	CFish(const CFish&) = delete;

	///GetHeight
	///\return height in pixels/2
	virtual double GetPHeight() { return 0; }

	/// Handle updates for animation
	///\param elapsed The time since the last update
	void Update(double elapsed);

	///function to get fishes size
	///\return 0 since this is a virtual class
	virtual double GetPWidth() { return 0; }

	///Function that loads in the aquarium from node which contains xml info
	///\param node is the node that contains the values
	///\returns none
	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

	///Saves the aquarium into an xml node
	///\param node is the node it saves the values into
	///\return the node in which xml data is saved
	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node);

protected:

	///setter for speed, used in the fish constructors
	///\param x is the x speed
	///\param y is the y speed
	///\return none
	void SetSpeed(double x, double y) { mSpeedX = x, mSpeedY = y; }

	///Getter for the X speed
	///\return the x speed
	double GetSpeedX() { return mSpeedX; }

	///Getter for the Y speed
	///\return the y speed
	double GetSpeedY() { return mSpeedY; }

	/**
	* Constructor
	* \param aquarium The aquarium we are in
	* \param filename Filename for the image we use
	*/
	CFish(CAquarium* aquarium, const std::wstring& filename);

private:
	/// Fish speed in the X direction
	double mSpeedX=0;

	/// Fish speed in the Y direction
	double mSpeedY=0;
};

