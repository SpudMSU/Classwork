#include "pch.h"
#include "TreeAdapter.h"
#include "TreeFactory.h"

CTreeAdapter::CTreeAdapter( const std::wstring name, int delay, int x, int y, int harvest, std::shared_ptr<CBasketAdapter> b, int seed) : CDrawable(name)
{ 
	CTreeFactory factory;
	mTree = factory.CreateTree(); 
	mDelay = delay;
	mTree->SetRootLocation(x, y);
	if (seed > -1)
	{
		mTree->SetSeed(seed);
	}
	mHarvestFrame = harvest;
	mBasket = b;
}
void CTreeAdapter::Draw(Gdiplus::Graphics* graphics)
{ 
	int frame = GetAngleChannel()->GetTimeline()->GetCurrentFrame();
	if (frame > (30+mDelay))
	{
		if (frame < (mDelay + 250))
		{
			mTree->SetTreeFrame(frame - (30 + mDelay));
		}
		if (frame > mHarvestFrame)
		{
			auto harvest = mTree->Harvest();
			mBasket->AddToBasket(harvest);
		}
		mTree->DrawTree(graphics);
	}

}

void CTreeAdapter::ShowDialogBox()
{
	CTreeSeedDlg dlg(mTree);
	if (dlg.DoModal() == IDOK)
	{
		auto frame = GetAngleChannel()->GetTimeline()->GetCurrentFrame();
		mTree->SetTreeFrame(frame);
	}
}