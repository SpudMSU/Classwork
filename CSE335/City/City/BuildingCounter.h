/**
* 
* \file BuildingCounter.h
*
* \author Spencer D Cassetta
*
*/
#pragma once
#include "TileVisitor.h"


/**
*
* class BuildingCounter
*
* visitor class to count the number of buildings
*
*/
class CBuildingCounter : public CTileVisitor
{
public:
	/** Get the number of buildings
	 * \returns Number of buildings */
	int GetNumBuildings() const { return mNumBuildings; }

	///visitor function that visits the building
	///\param building is the building we are visiting
	void VisitBuilding(CTileBuilding* building);

private:
	/// Buildings counter
	int mNumBuildings = 0;
};

