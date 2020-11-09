#include "pch.h"
#include "LeftLimb.h"
#include "Leaf.h"
#include "Apple.h"
using namespace Gdiplus;
using namespace std;
void CLeftLimb::AdjustLocation() {
		//and adjust the positions based upon the parents
		double x = 0;
		double y = 0;
		double angle = 0;
		y = this->GetParent()->GetEndY();
		x = this->GetParent()->GetEndX() - this->GetParent()->GetLength() / 2.0;
		SetLocation((int)x, (int)y);
}

void CLeftLimb::Grow(double lenG, double angle, double angle2, double dev, std::vector<std::shared_ptr<CTreeItem>>* newlimbs)
{
	//upcall for the grow
	CLimb::Grow(lenG, angle, angle2, dev, newlimbs);
	auto i = this;
	auto tree = GetTree();

	//if its long enough, has a depth of 2, and doesnt have leaves
	if ((i->GetLength() > (lenG - 1) || i->GetDepth() > 2) && !i->HasLeaf())
	{
		//give it leaves and fruit
		auto leaf = make_shared<CLeaf>(tree, 0, tree->GetLeafImage());
		leaf->SetParent(i);
		newlimbs->push_back(leaf);

		auto apple = make_shared<CApple>(tree, 0, tree->GetFruitImage());
		apple->SetParent(i);
		newlimbs->push_back(apple);

		i->GiveLeaf();

		tree->AddFruit(apple);
	}
}