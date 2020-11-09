
/*
*
* \author Spencer Cassetta
* DecorCastle.cpp
*/
#include "pch.h"
#include "DecorCastle.h"
#include <string>
#include "Item.h"
#include "Aquarium.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring CastleImageName = L"images/castle.png";

/*Constructor for castle
\param aquarium is an aquarium
*/
CDecorCastle::CDecorCastle(CAquarium* aquarium) : CItem(aquarium, CastleImageName) {}

/// Saves the aquarium into an xml node
///\param node is the node it saves the values into
///\return the node in which xml data is saved
std::shared_ptr<xmlnode::CXmlNode> CDecorCastle::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	//run CItem Xml save first
	auto itemNode = CItem::XmlSave(node);
	//then add the type to the xml
	itemNode->SetAttribute(L"type", L"castle");
	return itemNode;
}