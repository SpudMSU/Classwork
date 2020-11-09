/**
 * \file FishAngel.cpp
 *
 * \author Spencer Cassetta
 *
 */

#include "pch.h"
#include <string>
#include "Item.h"
#include "FishAngel.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring FishAngelImageName = L"images/angelfish.png";

/**
* Constructor
*/
CFishAngel::CFishAngel(CAquarium* aquarium) : CFish(aquarium, FishAngelImageName) 
{
	SetSpeed(((double)rand() / RAND_MAX) *50 + 5, ((double)rand() / RAND_MAX) * 50 + 10);
}

///Saves the aquarium into an xml node
///\param node is the node it saves the values into
///\return the node in which xml data is saved
std::shared_ptr<xmlnode::CXmlNode> CFishAngel::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	auto itemNode = CFish::XmlSave(node);
	itemNode->SetAttribute(L"type", L"angel");

	return itemNode;
}