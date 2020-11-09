/**
 * \file Fish.cpp
 *
 * \author Spencer D Cassetta
 *
 * Class that implements the Fish Class and is parent for all other fish
 */
#include "pch.h"
#include "Fish.h"
#include "Aquarium.h"

/// Maximum speed in the X direction in
/// in pixels per second


/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * \param elapsed Time elapsed since the class call
 */
void CFish::Update(double elapsed)
{
	SetLocation(GetX() + mSpeedX * elapsed *9,
		GetY() + mSpeedY * elapsed);

	if (mSpeedX > 0 && GetX() >= GetAquarium()->GetWidth() - GetPWidth())
	{
		mSpeedX = -mSpeedX;
		SetMirror(mSpeedX < 0);
	}
	//this if could be or'd with the last however then it'd be too long
	//reverses the fish if it hits the left side
	if (mSpeedX < 0 && GetX() <= 0 + GetPWidth())
	{
		mSpeedX = -mSpeedX;
		SetMirror(mSpeedX < 0);
	}
	//if you hit the top or bottom reverse speed
	if (GetY() < GetPHeight()){
		mSpeedY = abs(mSpeedY);
	}
	//had to ceiling and floor different due to fish getting stuck between boundaries
	if (GetY() > (GetAquarium()->GetHeight()) - GetPHeight()) {
		mSpeedY = -abs(mSpeedY);
	}
}

///constructor
CFish::CFish(CAquarium* aquarium, const std::wstring& filename) : CItem(aquarium, filename) {}

///Function that loads in the aquarium from node which contains xml info
///\param node is the node that contains the values
///\returns none
void CFish::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	CItem::XmlLoad(node);
	mSpeedX = node->GetAttributeDoubleValue(L"speedX", 0);
	mSpeedY = node->GetAttributeDoubleValue(L"speedY", 0);
	//if x is negative then mirror the image
	SetMirror(mSpeedX < 0);
}

///Saves the aquarium into an xml node
///\param node is the node it saves the values into
///\return the node in which xml data is saved
std::shared_ptr<xmlnode::CXmlNode> CFish::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	//do CItems XML Save
	auto itemNode = CItem::XmlSave(node);

	//then add the speed in there
	itemNode->SetAttribute(L"speedX", mSpeedX);
	itemNode->SetAttribute(L"speedY", mSpeedY);
	return itemNode;
}