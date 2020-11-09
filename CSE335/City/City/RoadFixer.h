/**
*
* \file RoadFixer.h 
*
* \author Spencer D Cassetta
*
*/

#pragma once
#include "TileVisitor.h"
#include "Tile.h"
#include "TileRoad.h"
#include "RoadVisitor.h"

/**
*
* class CRoadFixer
*
* visitor class to fix the roads
*
*/

class CRoadFixer : public CTileVisitor
{
public:
	/** Get the number of buildings
	 * \param road is the road we are visiting
	 * \returns Number of buildings */
	void VisitRoad(CTileRoad* road);

};