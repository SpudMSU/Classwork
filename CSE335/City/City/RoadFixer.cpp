#include "pch.h"
#include "RoadFixer.h"


void CRoadFixer::VisitRoad(CTileRoad* road)
{
	CRoadVisitor visitor;
	int n = 0;
	bool ul = false;
	bool ur = false;
	bool ll = false;
	bool lr = false;
	auto ulTile = road->GetAdjacent(-1, -1);
	if (ulTile != nullptr)
	{
		n = visitor.GetNumRoads();
		ulTile->Accept(&visitor);
		if (n < visitor.GetNumRoads())
		{
			ul = true;
		}
	}
	auto urTile = road->GetAdjacent(1, -1);
	if (urTile != nullptr)
	{
		n = visitor.GetNumRoads();
		urTile->Accept(&visitor);
		if (n < visitor.GetNumRoads())
		{
			ur = true;
		}
	}
	auto llTile = road->GetAdjacent(-1, 1);
	if (llTile != nullptr)
	{
		n = visitor.GetNumRoads();
		llTile->Accept(&visitor);
		if (n < visitor.GetNumRoads())
		{
			ll = true;
		}
	}
	auto lrTile = road->GetAdjacent(1, 1);
	if (lrTile != nullptr)
	{
		n = visitor.GetNumRoads();
		lrTile->Accept(&visitor);
		if (n < visitor.GetNumRoads())
		{
			lr = true;
		}
	}
	road->SetAdjacencies(ul, ur, ll, lr);
}