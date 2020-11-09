/**
 * \file FishBeta.h
 *
 * \author Spencer Cassetta
 *
 * Class for a fish of type Beta
 */

#pragma once
#include <memory>

#include "Item.h"
#include "Fish.h"

 /**
  * Class for a fish of type Beta
 */
class CFishBeta : public CFish
{
public:

	/**
	* function to get fishes size
	*\return width in pixels/2
	*/
	double GetPWidth() { return 62.5; }

	///GetHeight
	///\return height in pixels/2
	double GetPHeight() { return 58.5; }

	///constructor
	///\param aquarium is an aquarium
	CFishBeta::CFishBeta(CAquarium* aquarium);

	/// Default constructor (disabled)
	CFishBeta() = delete;

	/// Copy constructor (disabled)
	CFishBeta(const CFishBeta&) = delete;


	/**
	* Saves the aquarium into an xml node
	*\param node is the node it saves the values into
	*\return the node in which xml data is saved
	*/
	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

};
