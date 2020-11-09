#include "pch.h"
#include "AnimChannelPosition.h"


/**
* Set a keyframe
*
* This function allocates a new keyframe and sends it to
* CAnimChannel, which will insert it into the collection of keyframes.
*/
void CAnimChannelPosition::SetKeyFrame(double posX, double posY)
{
	// Create a keyframe of the appropriate type
	// Telling it this channel and the angle
	std::shared_ptr<KeyframePosition> keyframe =
		std::make_shared<KeyframePosition>(this, posX, posY);

	// Insert it into the collection
	InsertKeyframe(keyframe);
}

/**
 * Compute an angle that is an interpolation between two keyframes
 *
 * This function is called after Use1 and Use2, so we have pointers to
 * to valid keyframes of the type KeyframeAngle. This function does the
 * tweening.
 * \param t A t value. t=0 means keyframe1, t=1 means keyframe2. Other values
 * interpolate between.
 */
void CAnimChannelPosition::Tween(double t)
{
	mPosX = int(mKeyframe1->GetPosX() + t * (mKeyframe2->GetPosX() - mKeyframe1->GetPosX()));
	mPosY = int(mKeyframe1->GetPosY() + t * (mKeyframe2->GetPosY() - mKeyframe1->GetPosY()));
}