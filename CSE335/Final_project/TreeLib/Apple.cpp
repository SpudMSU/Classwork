#include "pch.h"
#include "Apple.h"
#include "Limb.h"
#include "FruitTree.h"
using namespace Gdiplus;
void CApple::AdjustLocation() {
	//adjust the positions based upon the parents ending postion
	double x = 0;
	double y = 0;
	y = this->GetParent()->GetEndY();
	x = GetParent()->GetEndX();

	///and set the position
	SetLocation((int)x, (int)y);

}

void CApple::Draw(Gdiplus::Graphics* graphics, double pAngle)
{
	//get the width and height
	const double RtoD = 57.295779513;
	double size = GetTree()->GetFruitSize();
	float wid = (float)(mImage->GetWidth() / size);
	float hit = (float)(mImage->GetHeight() / size);

	//angle of apples will always be towards the ground
	double Angle = 3.1415;

	///save the state
	auto state = graphics->Save();

	//rotates image in radians, mAngle
	graphics->TranslateTransform((float)GetX(), (float)GetY());
	graphics->RotateTransform((float)(-Angle * RtoD));
	//draw rotated image
	graphics->DrawImage(mImage, (REAL)(-wid / 2.0), (REAL)(-hit / 2.0),
		(REAL)wid, (REAL)hit);

	//then restore graphical state
	graphics->Restore(state);
}

void CApple::DrawInBasket(Gdiplus::Graphics* graphics, int x, int y) 
{
	const double RtoD = 57.295779513;
	double size = mSize;
	float wid = (float)(mImage->GetWidth() / size);
	float hit = (float)(mImage->GetHeight() / size);

	double Angle = 3.1415;
	auto state = graphics->Save();

	//rotates image in radians, mAngle
	graphics->TranslateTransform((float)x, (float)y);
	graphics->RotateTransform((float)(-Angle * RtoD));
	//draw rotated image
	graphics->DrawImage(mImage, (REAL)(-wid / 2.0), (REAL)(-hit / 2.0),
		(REAL)wid, (REAL)hit);

	//then restore graphical state
	graphics->Restore(state);
}

void CApple::Grow(double lenG, double angle, double angle2, double dev, std::vector<std::shared_ptr<CTreeItem>>* newlimbs)
{
	auto tree = GetTree();

	//if size is over 5 then decrease it
	if (tree->GetFruitSize() > 5)
	{
		//decrease the fruit size division factor which will grow it
		tree->DecreaseFruitSize();
	}
}