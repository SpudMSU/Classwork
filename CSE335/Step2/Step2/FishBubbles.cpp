/**
 * \file FishBubbles.cpp
 *
 * \author Spencer Cassetta
 *
 */

#include "pch.h"
#include <string>
#include "Item.h"
#include "FishBubbles.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring FishBubblesImageName = L"images/bubbles.png";

/**
* Constructor
*/
CFishBubbles::CFishBubbles(CAquarium* aquarium) : CFish(aquarium, FishBubblesImageName)
{
	SetSpeed(((double)rand() / RAND_MAX) * 50, ((double)rand() / RAND_MAX) * 10 + 20);
}

///Saves the aquarium into an xml node
///\param node is the node it saves the values into
///\return the node in which xml data is saved
std::shared_ptr<xmlnode::CXmlNode> CFishBubbles::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	//run CFish xml save
	auto itemNode = CFish::XmlSave(node);

	//then save the fish type
	itemNode->SetAttribute(L"type", L"bubbles");

	return itemNode;
}