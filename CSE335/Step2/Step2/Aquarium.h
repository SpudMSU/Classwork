/**
 * \file Aquarium.h
 *
 * \author Spencer D Cassetta
 *
 * Class that manages all the fish life within the aquarium
 *
 */

#pragma once
#include <iostream>
#include <vector>
#include "Item.h"
#include "FishBeta.h"
#include "FishAngel.h"
#include "FishStinky.h"
#include "FishBubbles.h"
#include "DecorCastle.h"

 /**
  * Class that manages all the fish life within the aquarium
  */
class CAquarium
{
public:
	///Clears all objects from the aquarium
	void Clear();

	/// Get the width of the aquarium
	/// \returns Aquarium width
	int GetWidth() const { return mBackground->GetWidth(); }

	/// Get the height of the aquarium
	/// \returns Aquarium height
	int GetHeight() const { return mBackground->GetHeight(); }

	/** 
	* Handle updates for animation
	* \param elapsed The time since the last update
	*/
	void Update(double elapsed);

	/**
	* Creates a node for the item in XML
	* \param node -> node which contains info about the item
	* \returns none
	*/
	void XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node);


	/**
	* Loads a file coded in xml
	* \param filename - aqua file containing info
	* \returns none
	*/
	void Load(const std::wstring& filename);
	
	/** 
	 * Save the aquarium as a .aqua XML file.
	 *
	 * Open an XML file and stream the aquarium data to it.
	 *
	 * \param filename The filename of the file to save the aquarium to
	*/
	void Save(const std::wstring& filename);

	/**
	* sizes and puts fish image on the canvas
	* \param graphics system uses this to draw
	* \returns void
	*/
	void OnDraw(Gdiplus::Graphics* graphics);

	///default constructor
	CAquarium();

	/**
	* Adds fish to mItems
	* \param item Fish obj to add to the class vector
	* \returns void
	*/
	void Add(std::shared_ptr<CItem> item);

	/**
	* Tests if the mouse hits target when it clicks
	* \param x, x location of where to hit test
	* \param y, y location of where to hit test
	* \returns fish object it hit
	*/
	std::shared_ptr<CItem> HitTest(int x, int y);

	/**
	* takes item out of mItems and puts it on top
	* \param item, item to take out of vector and put back in
	* \returns void
	*/
	void replaceItem(std::shared_ptr<CItem> item);

private:

	std::unique_ptr<Gdiplus::Bitmap> mBackground; ///< Background image

	/// All of the items to populate our aquarium
	std::vector<std::shared_ptr<CItem> > mItems;
};


