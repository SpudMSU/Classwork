/**
 * \file FishAngel.h
 *
 * \author Spencer Cassetta
 *
 * Class for a fish of type Angel
 */

#pragma once
#include <memory>

#include "Item.h"
#include "Fish.h"
#include "Aquarium.h"

 /**
  * Class for a fish of type Angel
 */
class CFishAngel : public CFish
{
public:

	/**
	* function to get fishes size
	* \return size in pixels/2
	*/
	double GetPWidth() { return 64; }

	///GetHeight
	///\return height in pixels/2
	double GetPHeight() { return 60.5;  }

	///constructor
	///\param aquarium is an aquarium
	CFishAngel::CFishAngel(CAquarium* aquarium);

	/// Default constructor (disabled)
	CFishAngel() = delete;

	/// Copy constructor (disabled)
	CFishAngel(const CFishAngel&) = delete;

	/**
	* Saves the aquarium into an xml node
	* \param node is the node it saves the values into
	* \return the node in which xml data is saved
	*/
	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
	

};
