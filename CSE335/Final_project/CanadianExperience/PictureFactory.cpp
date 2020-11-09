/**
 * \file PictureFactory.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "ImageDrawable.h"
#include "Tree.h"
#include "Basket.h"
#include "TreeFactory.h"
#include "TreeAdapter.h"
#include "BasketAdapter.h"

using namespace std;
using namespace Gdiplus;

CPictureFactory::CPictureFactory()
{
}


CPictureFactory::~CPictureFactory()
{
}


/** Factory method to create a new picture.
* \returns The created picture
*/
std::shared_ptr<CPicture> CPictureFactory::Create()
{
    shared_ptr<CPicture> picture = make_shared<CPicture>();

    // Create the background and add it



    auto background = make_shared<CActor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(Point(-100, 0));
    auto backgroundI = make_shared<CImageDrawable>(L"Background", L"images/Background.png");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add Harold
    CHaroldFactory factory;
    auto harold = factory.Create();

    // This is where Harold will start out.
    harold->SetPosition(Point(400, 500));

    picture->AddActor(harold);

    // Create and add Sparty
    CSpartyFactory sfactory;
    auto sparty = sfactory.Create();

    sparty->SetPosition(Point(200, 500));
    picture->AddActor(sparty);

	auto basketActor = make_shared<CActor>(L"basket");
	auto basketAdapter = make_shared<CBasketAdapter>(L"basket", 600, 500);
	basketActor->AddDrawable(basketAdapter);

	auto tree1Actor = make_shared<CActor>(L"tree1");
	auto treeAdapter = make_shared<CTreeAdapter>(L"tree1", 100, 800, 500, 600, basketAdapter);
	tree1Actor->AddDrawable(treeAdapter);


	auto tree2Actor = make_shared<CActor>(L"tree2");
	auto treeAdapter2 = make_shared<CTreeAdapter>(L"tree2", 300, 500, 500, 870, basketAdapter, 946);
	tree2Actor->AddDrawable(treeAdapter2);


	picture->AddActor(tree1Actor);
	picture->AddActor(tree2Actor);
	picture->AddActor(basketActor);

	picture->AddTree(treeAdapter);
	picture->AddTree(treeAdapter2);
	picture->AddBasket(basketAdapter);

    return picture;
}
