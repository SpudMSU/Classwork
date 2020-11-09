/**
 * \file Drawable.cpp
 *
 * \author Spencer D Cassetta
 *
 *
 */

#include "pch.h"
#include "Drawable.h"
#include "Actor.h"
#include "Timeline.h"

 /**
  * Constructor
  *\param name The drawable name
  */
CDrawable::CDrawable(const std::wstring& name) : mName(name)
{
	mName = name;
}

/** Destructor */
CDrawable::~CDrawable()
{
}

/**
 * Set the actor using this drawable
 * \param actor Actor using this drawable
 */
void CDrawable::SetActor(CActor* actor)
{
	mActor = actor;
	// Set the channel name
	mChannelAngle.SetName(actor->GetName() + L":" + mName);
}

/** Add the channels for this drawable to a timeline
 * \param timeline The timeline class.
 */
void CDrawable::SetTimeline(CTimeline* timeline)
{
	timeline->AddChannel(&mChannelAngle);
}

/** Set the keyframe based on the current status.
*/
void CDrawable::SetKeyframe()
{
	mChannelAngle.SetKeyFrame(mRotation, mPosition.X, mPosition.Y);
	//mChannelPosition.SetKeyFrame(mPosition.X, mPosition.Y);
}

void CDrawable::DeleteKeyframe()
{
	mChannelAngle.DeleteCurrentFrame();
}

/** Get the current channel from the animation system.
*/
void CDrawable::GetKeyframe()
{
	if (mChannelAngle.IsValid())
	{
		mRotation = mChannelAngle.GetAngle();
	}
	if (mChannelAngle.IsValid())
	{
		mPosition.X = (int)mChannelAngle.GetPosX();
		mPosition.Y = (int)mChannelAngle.GetPosY();
	}
}

/**
 * Add a child drawable to this drawable
 * \param child The child to add
 */
void CDrawable::AddChild(std::shared_ptr<CDrawable> child)
{
	child->SetParent(this);
	mChildren.push_back(child);
}

/** Rotate a point by a given angle.
* \param point The point to rotate
* \param angle An angle in radians
* \returns Rotated point
*/
Gdiplus::Point CDrawable::RotatePoint(Gdiplus::Point point, double angle)
{
	double cosA = cos(angle);
	double sinA = sin(angle);

	return Gdiplus::Point(int(cosA * point.X + sinA * point.Y),
		int(-sinA * point.X + cosA * point.Y));
}

/**
 * Place this drawable relative to its parent
 *
 * This works hierarchically from top item down.
 * \param offset Parent offset
 * \param rotate Parent rotation
 */
void CDrawable::Place(Gdiplus::Point offset, double rotate)
{
	// Combine the transformation we are given with the transformation
	// for this object.
	mPlacedPosition = offset + RotatePoint(mPosition, rotate);
	mPlacedR = mRotation + rotate;

	// Update our children
	for (auto drawable : mChildren)
	{
		drawable->Place(mPlacedPosition, mPlacedR);
	}
}

/**
 * Move this drawable some amount
 * \param delta The amount to move
 */
void CDrawable::Move(Gdiplus::Point delta)
{
	if (mParent != nullptr)
	{
		mPosition = mPosition + RotatePoint(delta, -mParent->mPlacedR);
	}
	else
	{
		mPosition = mPosition + delta;
	}
}