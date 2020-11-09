/**
* \file FishStinky.h
*
* \author Spencer Cassetta
*
* Class for a fish of type Stinky
**/

#pragma once
#include <memory>
#include "Fish.h"
#include "Item.h"

/**
 * Class for a fish of type Stinky
*/
class CFishStinky : public CFish
{
public:

	/**
	* function to get fishes size
	* \return size in pixels/2
	*/
	double GetPWidth() { return 100; }

	///GetHeight
	///\return height in pixels/2
	double GetPHeight() { return 63.5; }

	///Constructor for stinky fish
	///\param aquarium is an aquarium
	CFishStinky::CFishStinky(CAquarium* aquarium);

	/// Default constructor (disabled)
	CFishStinky() = delete;

	/// Copy constructor (disabled)
	CFishStinky(const CFishStinky&) = delete;


	/**
	* Saves the aquarium into an xml node
	*\param node is the node it saves the values into
	*\return the node in which xml data is saved
	*/
	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

};