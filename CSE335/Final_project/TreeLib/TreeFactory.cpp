/**
 * \file TreeFactory.cpp
 *
 * \author Charles Owen
 *
 * You are allowed to change this file.
 */

#include "pch.h"
#include "TreeFactory.h"
#include "Tree.h"
#include "FruitTree.h"
#include "Basket.h"
#include "Limb.h"
#include "TreeItem.h"
#include "ActualBasket.h"
#include "Root.h"

using namespace std;

/**
 * Constructor
 */
CTreeFactory::CTreeFactory()
{
}


/**
 * Destructor
 */
CTreeFactory::~CTreeFactory()
{
}


/**
 * Create a Tree object
 * \returns Object of type CTree
 */
std::shared_ptr<CTree> CTreeFactory::CreateTree()
{

	auto image = Gdiplus::Bitmap::FromFile(L"images/leaf3.png");
	if (image->GetLastStatus() != Gdiplus::Ok)
	{
		AfxMessageBox(L"Failed to open images/leaf.png");
	}
	auto image2 = Gdiplus::Bitmap::FromFile(L"images/apple.png");
	if (image2->GetLastStatus() != Gdiplus::Ok)
	{
		AfxMessageBox(L"Failed to open images/apple.png");
	}
	auto tree = make_shared<CFruitTree>();
	tree->SetLeafImage(image);
	tree->SetFruitImage(image2);
	auto limb1 = make_shared<CRoot>(&(*tree), 0);
	limb1->SetParent(&(*limb1));
	limb1->SetRoot(&(*limb1));
	limb1->SetDepth(0);
	tree->AddItem(limb1);
    return tree;
}


/**
 * Create a Basket object
 * \returns Object of type CBasket
 */
std::shared_ptr<CBasket> CTreeFactory::CreateBasket()
{
    return make_shared<CActualBasket>();
}

