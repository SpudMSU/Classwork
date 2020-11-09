#include "pch.h"
#include "Root.h"
#include "FruitTree.h"
using namespace Gdiplus;


CRoot::CRoot(CFruitTree* tree,  double angle) : CLimb(tree, angle)
{
	SetLocation(tree->GetLocation().X, tree->GetLocation().Y);
	SetAngle(0);
}
void CRoot::Draw(Gdiplus::Graphics* graphics, double pAngle)
{
	//draw the limb
	double len = GetLength();
	int x = GetX();
	int y = GetY();
	Pen pen(Color(139, 69, 19), (REAL)GetWidth());

	pen.SetEndCap(LineCapRound);
	graphics->DrawLine(&pen, (REAL)x, (REAL)y, (REAL)(x), (REAL)(y + (-len)));
	Pen pen2(Color(139, 69, 19), (REAL)2);
	graphics->DrawLine(&pen, (REAL)(x), (REAL)(y + (-len)), (REAL)(x + len / 2), (REAL)(y + ((-len) * 1.5)));
	graphics->DrawLine(&pen, (REAL)(x), (REAL)(y + (-len)), (REAL)((x) - GetLength() / 2), (REAL)(y + ((-len) * 1.5)));

	this->SetEndX(x);
	this->SetEndY(y + ((-len) * 1.5));
}

void CRoot::AdjustLocation()
{//set location to trees location
	auto tree = GetTree();
	SetLocation(tree->GetLocation().X, tree->GetLocation().Y);
}