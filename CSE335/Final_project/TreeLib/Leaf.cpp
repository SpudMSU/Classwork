#include "pch.h"
#include "Leaf.h"
#include "Limb.h"

void CLeaf::AdjustLocation() {
	//adjust the positions based upon the parents
	double x = 0;
	double y = 0;
	y = this->GetParent()->GetEndY();
	x = GetParent()->GetEndX();
	SetLocation((int)x, (int)y);

}