/**
 * \file FishBubbles.h
 *
 * \author Spencer Cassetta
 *
 * Class for a fish of type Bubbles
 */

#pragma once
#include <memory>
#include "Fish.h"
#include "Item.h"

 /**
  * Class for a fish of type Bubbles
 */
class CFishBubbles : public CFish
{
public:

	/**
	* function to get fishes size
	*\return width in pixels/2
	*/
	double GetPWidth() { return 64; }

	///GetHeight
	///\return height in pixels/2
	double GetPHeight() { return 76; }

	///constructor
	///\param aquarium is a aquarium
	CFishBubbles::CFishBubbles(CAquarium* aquarium);

	/// Default constructor (disabled)
	CFishBubbles() = delete;

	/// Copy constructor (disabled)
	CFishBubbles(const CFishBubbles&) = delete;


	/**
	* Saves the aquarium into an xml node
	*\param node is the node it saves the values into
	*\return the node in which xml data is saved
	*/
	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};

