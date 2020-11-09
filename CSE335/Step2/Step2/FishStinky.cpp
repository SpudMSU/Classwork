/**
 * \file FishStinky.cpp
 *
 * \author Spencer Cassetta
 *
 */

#include "pch.h"
#include <string>
#include "FishStinky.h"
#include "Item.h"
#include "Aquarium.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring FishStinkyImageName = L"images/stinky.png";

/*Constructor for stinky fish
\param aquarium is an aquarium
*/
CFishStinky::CFishStinky(CAquarium* aquarium) : CFish(aquarium, FishStinkyImageName)
{
	SetSpeed(((double)rand() / RAND_MAX) * 30, ((double)rand() / RAND_MAX) * 50 +5);
}

///Saves the aquarium into an xml node
///\param node is the node it saves the values into
///\return the node in which xml data is saved
std::shared_ptr<xmlnode::CXmlNode> CFishStinky::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	//run CFish xmlsave
	auto itemNode = CFish::XmlSave(node);

	//then save the type
	itemNode->SetAttribute(L"type", L"stinky");

	return itemNode;
}
