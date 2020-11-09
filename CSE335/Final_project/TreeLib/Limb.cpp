#include "pch.h"
#include "Limb.h"
#include "FruitTree.h"
#include "TreeItemVisitor.h"
#include "Leaf.h"
#include "RightLimb.h"
#include "LeftLimb.h"
#include "TreeItem.h"
#include "Root.h"
using namespace Gdiplus;
using namespace std;


CLimb::CLimb(CFruitTree* tree, double angle)
	: CTreeItem(tree,  angle) {

}

void CLimb::GiveLeaf() 
{
	SetLeaf(true);
}

void CLimb::AddChild(std::shared_ptr<CTreeItem> item)
{//adds a child and sets the parent
	mChildren.push_back(item);
	item->SetRoot(GetRoot());
	item->SetParent(this);
}


void CLimb::Draw(Gdiplus::Graphics* graphics, double pAngle)
{
	//calculate the derivatives to properly draw limbs on an angle
	double useAngle = GetAngle()+ pAngle + 1.57;
	SetAngleSum(GetAngle() + pAngle);
	double dx = cos(useAngle) * mLength;
	double dy = -sin(useAngle) * mLength;


	//then draw them
	int x = GetX();
	int y = GetY();
	Pen pen(Color(139, 69, 19), (REAL)GetWidth());

	pen.SetEndCap(LineCapRound);
	graphics->DrawLine(&pen, (REAL)x, (REAL)y, (REAL)(x + dx), (REAL)(y + dy));
	Pen pen2(Color(139, 69, 19), (REAL)2);
	graphics->DrawLine(&pen, (REAL)(x + dx), (REAL)(y + dy), (REAL)(x + dx + GetLength() / 2), (REAL)(y + (dy * 1.5)));
	graphics->DrawLine(&pen, (REAL)(x + dx), (REAL)(y + dy), (REAL)((x + dx) - GetLength() / 2), (REAL)(y + (dy * 1.5)));

	this->SetEndX(x + dx);
	this->SetEndY(y + (dy * 1.5));

	mSpawned = true;
}


///function to spawn item
void CLimb::Spawn()
{

}

///function to grow limb
void CLimb::Grow(double lenG, double angle, double angle2, double dev, std::vector<std::shared_ptr<CTreeItem>> *newlimbs)
{
	auto i = this;
	//adjust width and length
	i->SetLength(i->GetLength() + (lenG / 100.0) + dev);//
	i->SetWidth(i->GetWidth() + (double)(.03));//

	auto tree = GetTree();
	if (i->GetChildCount() == 0 && i->GetLength() > lenG)//
	{
		//if mature enough, grow 2 limbs
		auto newlimb = make_shared<CRightLimb>(tree, (-angle + dev));//
		auto newlimb2 = make_shared<CLeftLimb>(tree, (angle2 + dev));//

		newlimb->SetDepth(i->GetDepth() + 1);
		newlimb2->SetDepth(i->GetDepth() + 1);
		i->AddChild(newlimb);
		i->AddChild(newlimb2);
		newlimbs->push_back(newlimb);
		newlimbs->push_back(newlimb2);
	}
}