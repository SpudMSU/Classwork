#include "pch.h"
#include "TreeItemImage.h"
using namespace Gdiplus;

CTreeItemImage::CTreeItemImage(CFruitTree* tree, double angle, Gdiplus::Bitmap* image)
	: CTreeItem(tree, angle) {
	mImage = image;
}
void CTreeItemImage::Draw(Gdiplus::Graphics* graphics, double pAngle)
{

	const double RtoD = 57.295779513;
	float wid = (float)(mImage->GetWidth()/3);
	float hit = (float)(mImage->GetHeight()/3);

	double Angle = pAngle;
	auto state = graphics->Save();
	int x = GetX();
	int y = GetY();
	//rotates image in radians, mAngle
	graphics->TranslateTransform((float)x, (float)y);
	graphics->RotateTransform((float)(-Angle * RtoD));
	//draw rotated image
	graphics->DrawImage(mImage, -wid / 2, -hit / 2,
		wid, hit);

	//then restore graphical state
	graphics->Restore(state);
}