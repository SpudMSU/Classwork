/**
 * \file PictureFactory.cpp
 *
 * \author Spencer D Cassetta
 *
 *
 */



#include "pch.h"
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "ImageDrawable.h"
#include "PhillFactory.h"
/** Factory method to create a new picture.
* \returns The created picture
*/

using namespace std;
using namespace Gdiplus;
std::shared_ptr<CPicture> CPictureFactory::Create()
{
	std::shared_ptr<CPicture> picture = std::make_shared<CPicture>();

	// Create the background and add it
	auto background = make_shared<CActor>(L"Background");
	background->SetClickable(false);
	background->SetPosition(Point(-100, 0));
	auto backgroundI =
		make_shared<CImageDrawable>(L"Background", L"images/Background.png");
	background->AddDrawable(backgroundI);
	background->SetRoot(backgroundI);
	picture->AddActor(background);

	// Create and add Harold
	CHaroldFactory factory;
	CPhillFactory factory2;
	auto harold = factory.Create();
	auto phill = factory2.Create();

	// This is where Harold will start out.
	harold->SetPosition(Gdiplus::Point(400, 500));
	phill->SetPosition(Gdiplus::Point(700, 500));
	picture->AddActor(harold);
	picture->AddActor(phill);

	return picture;
}