/**
 * \file Actor.h
 *
 * \author Spencer D Cassetta
 *
 *
 */

#pragma once


#include <string>
#include <memory>
#include "Drawable.h"
#include <vector>
class CPicture;
 /**
 * Class for actors in our drawings.
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */
class CActor
{
public:
	///constructor
	///\param name
	CActor(const std::wstring& name);

	/** Default constructor disabled */
	CActor() = delete;
	/** Copy constructor disabled */
	CActor(const CActor&) = delete;
	/** Assignment operator disabled */
	void operator=(const CActor&) = delete;
	virtual ~CActor();

	/** Get the actor name
	 * \returns Actor name */
	std::wstring GetName() const { return mName; }

	/** The actor position
	* \returns The actor position as a point */
	Gdiplus::Point GetPosition() const { return mPosition; }

	/** The actor position
	* \param pos The new actor position */
	void SetPosition(Gdiplus::Point pos) { mPosition = pos; }


	/** The Position animation channel
 * \returns Pointer to animation channel */
	CAnimChannelAngle* GetPositionChannel() { return &mChannelPosition; }

	/** Actor is enabled
	* \returns enabled status */
	bool IsEnabled() const { return mEnabled; }

	/** Set Actor Enabled
	* \param enabled New enabled status */
	void SetEnabled(bool enabled) { mEnabled = enabled; }

	/** Actor is clickable
	* \returns true if actor is clickable */
	bool IsClickable() const { return mClickable; }

	/** Actor clickable
	* \param clickable New clickable status */
	void SetClickable(bool clickable) { mClickable = clickable; }

	/** sets the root of the actor
	*\param root is root to set */
	void SetRoot(std::shared_ptr<CDrawable> root);

	/** draws the actor
	*\param graphics to use to draw */
	void Draw(Gdiplus::Graphics* graphics);

	/** test if you hit the actor
	*\param pos is the point to hittest
	*\return the drawable that you hit*/
	std::shared_ptr<CDrawable> HitTest(Gdiplus::Point pos);

	/**Adds a drawable to the actor
	*\param drawable is the object to add to the actor*/
	void AddDrawable(std::shared_ptr<CDrawable> drawable);

	/** Get the actors picture
	*\return the actors picture */
	CPicture* GetPicture() { return mPicture; }

	void SetTimeline(CTimeline* timeline);

	/**Sets the actors picture
	*\param picture is the picture to set as the actors picture*/
	void SetPicture(CPicture* picture);

	///sets keyframe
	void SetKeyframe();

	///deletes keyframe
	void DeleteKeyframe();
	/** brief Get a keyframe for an actor.
	*/
	void GetKeyframe();

private:

	///name
	std::wstring mName;

	///enabled
	bool mEnabled = true;

	///position
	Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

	///clickable
	bool mClickable = true;

	/// The root drawable
	std::shared_ptr<CDrawable> mRoot;

	/// The drawables in drawing order
	std::vector<std::shared_ptr<CDrawable>> mDrawablesInOrder;

	///the picture of the actor
	CPicture* mPicture = nullptr;

	///member variable for channel position
	CAnimChannelAngle mChannelPosition;
};

