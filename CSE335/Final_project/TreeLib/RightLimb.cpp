#include "pch.h"
#include "RightLimb.h"
#include "Apple.h"
#include "Leaf.h"
using namespace std;
void CRightLimb::AdjustLocation() {
		//and adjust the positions based upon the parents
		double x = 0;
		double y = 0;
		y = GetParent()->GetEndY();
		x = GetParent()->GetEndX() + GetParent()->GetLength() / 2.0;

		SetLocation((int)x, (int)y);

}

void CRightLimb::Grow(double lenG, double angle, double angle2, double dev, std::vector<std::shared_ptr<CTreeItem>>* newlimbs)
{
	CLimb::Grow(lenG, angle, angle2, dev, newlimbs);
	auto i = this;
	auto tree = GetTree();
	if ((i->GetLength() > (lenG - 1) || i->GetDepth() > 2) && !i->HasLeaf())
	{
		//if its mature enough, give it leaves and fruit
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