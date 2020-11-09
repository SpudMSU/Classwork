#include "pch.h"
#include "BasketAdapter.h"
#include "TreeFactory.h"
CBasketAdapter::CBasketAdapter( const std::wstring name, int x, int y) : CDrawable(name) 
{ 
	CTreeFactory factory;
	mBasket = factory.CreateBasket();
	mBasket->SetBasketLocation(x, y);
}