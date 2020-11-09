
/**
 * \file FishBeta.cpp
 *
 * \author Spencer Cassetta
 *
 */

#include "pch.h"
#include <string>
#include "FishBeta.h"

using namespace Gdiplus;
using namespace std;

/// Fish filename 
const wstring FishBetaImageName = L"images/beta.png";

/**
* Constructor
*/
CFishBeta::CFishBeta(CAquarium* aquarium) : CFish(aquarium, FishBetaImageName)
{
	SetSpeed(((double)rand() / RAND_MAX) * 20, ((double)rand() / RAND_MAX) * 30);
}

/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 */
std::shared_ptr<xmlnode::CXmlNode> CFishBeta::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	//do CFish xml save
	auto itemNode = CFish::XmlSave(node);

	//then save the fish type
	itemNode->SetAttribute(L"type", L"beta");
	return itemNode;
}
