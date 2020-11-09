/**
 * \file Drawable.h
 *
 * \author Spencer D Cassetta
 *
 * 
 */
#pragma once

#include <memory>
#include <string>
#include <vector>

class CActor;
class CTimeline;
#include "AnimChannelAngle.h"
#include "AnimChannelPosition.h"
#include "DrawableVisitor.h"
/**
 * Abstract base class for drawable elements of our picture
 */
class CDrawable
{
public:

	///destructor
	virtual ~CDrawable();

	/** Default constructor disabled */
	CDrawable() = delete;
	/** Copy constructor disabled */
	CDrawable(const CDrawable&) = delete;
	/** Assignment operator disabled */
	void operator=(const CDrawable&) = delete;

	/** Set the drawable position
 * \param pos The new drawable position*/
	void SetPosition(Gdiplus::Point pos) { mPosition = pos; }

	/** Get the drawable position
	 * \returns The drawable position*/
	Gdiplus::Point GetPosition() const { return mPosition; }

	/** Set the rotation angle in radians
	* \param r The new rotation angle in radians*/
	void SetRotation(double r) { mRotation = r; }

	/** Get the rotation angle in radians
	* \returns The rotation angle in radians*/
	double GetRotation() const { return mRotation; }

	/** Get the drawable name
	* \returns The drawable name */
	std::wstring GetName() const { return mName; }

	/**tells if object is movable
	*\returns true if it is movable*/
	virtual bool IsMovable() { return false; }

	/**Sets the actor
	*\param actor is the actor to set it to*/
	void SetActor(CActor* actor);

	/** draws the drawable
	*\param graphics to use to draw */
	virtual void Draw(Gdiplus::Graphics* graphics) = 0;

	/**Places the drawable
	*\param offset is an offset
	*\param rotate is degree to rotate object by*/
	void Place(Gdiplus::Point offset, double rotate);

	/**Adds a child node
	*\param child is the child node*/
	void AddChild(std::shared_ptr<CDrawable> child);

	/** test if you hit the actor
	*\param pos is the point to hittest
	*\return the drawable that you hit*/
	virtual bool HitTest(Gdiplus::Point pos) = 0;

	/**Move the drawable
	*\param delta is point to move object too*/
	void Move(Gdiplus::Point delta);

	/**Gets the parent node
	*\return the parent node*/
	CDrawable* GetParent() { return mParent; }

	/**Sets the parent node
	*\param parent is the node to set the parent too*/
	void SetParent(CDrawable* parent) { mParent = parent; }

	void SetTimeline(CTimeline* timeline);

	/** The angle animation channel
	 * \returns Pointer to animation channel */
	CAnimChannelAngle* GetAngleChannel() { return &mChannelAngle; }

	/** The Position animation channel
	 * \returns Pointer to animation channel */
	CAnimChannelPosition* GetPositionChannel() { return &mChannelPosition; }

	/** Set the keyframe based on the current status.
*/
	virtual void SetKeyframe();

	/** Get the current channel from the animation system.
	*/
	virtual void GetKeyframe();


	///function to delete the keyframe
	virtual void DeleteKeyframe();

protected:

	/**constructor
	*\param name is the name of the drawable*/
	CDrawable(const std::wstring& name);

	/**Rotates the point
	*\param point is the point to rotate around
	*\param angle is the angle to rotate everything by*/
	Gdiplus::Point RotatePoint(Gdiplus::Point point, double angle);


	/// The actual postion in the drawing
	Gdiplus::Point mPlacedPosition = Gdiplus::Point(0, 0);

	/// The actual rotation in the drawing
	double mPlacedR = 0;

private:
	/// The drawable name
	std::wstring mName;

	/// The position of this drawable relative to its parent
	Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

	/// The rotation of this drawable relative to its parent
	double mRotation = 0;

	/// The actor using this drawable
	CActor* mActor = nullptr;

	///Parent
	CDrawable* mParent = nullptr;

	///vector for it's children/
	std::vector<std::shared_ptr<CDrawable>> mChildren;

	/// The animation channel for animating the angle of this drawable
	CAnimChannelAngle mChannelAngle;

	///member variable for the position channel
	CAnimChannelPosition mChannelPosition;
};



