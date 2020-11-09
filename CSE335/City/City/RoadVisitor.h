/**
*
* \file RoadVisitor.h
*
* \author Spencer D Cassetta
*
*/

#pragma once
#include "TileVisitor.h"
#include "Tile.h"
#include "TileRoad.h"

/**
*
* class CRoadVisitor
*
* visitor class to tell if tile is a tileRoad
*
*/

class CRoadVisitor : public CTileVisitor
{
public:
	/** Get the number of buildings
	 * \returns Number of buildings */
	int GetNumRoads() { return mNumRoads; }

	/// visitor to visit the road
	/// \param road is the road we are visiting
	void VisitRoad(CTileRoad* road) { mNumRoads++; }

private:
	/// Roads counter
	int mNumRoads = 0;
};