/**
 * \file DecorCastle.h
 *
 * \author Spencer D Cassetta
 *
 * Class that implements the castle structure
 */

#pragma once
#pragma once


#include <memory>

#include "Item.h"

/** 
* Class DecorCastle
* class that handles the castle structure
*/
class CDecorCastle : public CItem
{
public:
	///constructor
	///\param aquarium is an aquarium
	CDecorCastle::CDecorCastle(CAquarium* aquarium);

	/// Default constructor (disabled)
	CDecorCastle() = delete;

	/// Copy constructor (disabled)
	CDecorCastle(const CDecorCastle&) = delete;

	/// Saves the aquarium into an xml node
	///\param node is the node it saves the values into
	///\return the node in which xml data is saved
	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;
};

