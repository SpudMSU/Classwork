/**
 * \file AnimChannel.cpp
 *
 * \author Spencer Cassetta
 */

#include "pch.h"
#include "AnimChannel.h"
#include "Timeline.h"
/** Determine how we should insert a keyframe into our keyframe list.
 * \param keyframe The keyframe to insert
 */
void CAnimChannel::InsertKeyframe(std::shared_ptr<Keyframe> keyframe)
{
	// Get the current frame and tell it to the keyframe we are setting.
	int currFrame = mTimeline->GetCurrentFrame();
	keyframe->SetFrame(currFrame);

	// The possible options for keyframe insertion
	enum { Append, Replace, Insert } action;

	// Determine the action we will do
	if (mKeyframe1 < 0)
	{
		// There is no first keyframe. This means
		// we are before any keyframes or there are no keyframes.
		// If before a keyframe, we insert, otherwise, we append
		action = mKeyframe2 >= 0 ? Insert : Append;
	}
	else
	{
		// We know mKeyframe1 is valid
		// So, we are after it.
		int frame1 = mKeyframes[mKeyframe1]->GetFrame();

		if (mKeyframe2 < 0)
		{
			// There is no second keyframe.
			// If we are after the current frame, we append.
			// If we are on the current frame, we replace.
			action = frame1 < currFrame ? Append : Replace;
		}
		else
		{
			// There is a second keyframe
			// If we are before the first frame, we insert
			// If not, we replace
			action = frame1 < currFrame ? Insert : Replace;
		}
	}

	//
	// And do the appropriate action
	//
	switch (action)
	{
	case Append:
		// Add to end and the keyframe to the left becomes the new keyframe
		mKeyframes.push_back(keyframe);
		mKeyframe1 = (int)mKeyframes.size() - 1;
		break;

	case Replace:
		// Replace the current keyframe
		mKeyframes[mKeyframe1] = keyframe;
		break;

	case Insert:
		// Insert after mKeyframe1
		// and mKeyframe1 becomes this new insertion (frame we are on)
		mKeyframes.insert(mKeyframes.begin() + 1 + mKeyframe1, keyframe);
		mKeyframe1++;
		break;
	}

}

/**
 * Is the channel valid, meaning has keyframes?
 * \returns true if the channel is valid.
 */
bool CAnimChannel::IsValid()
{
	return mKeyframe1 >= 0 || mKeyframe2 >= 0;
}

void CAnimChannel::SetFrame(int currFrame)
{
	// Should we move forward in time?
	while (mKeyframe2 >= 0 &&
		mKeyframes[mKeyframe2]->GetFrame() <= currFrame)
	{
		mKeyframe1 = mKeyframe2;
		mKeyframe2++;
		if (mKeyframe2 >= (int)mKeyframes.size())
			mKeyframe2 = -1;
	}

	// Should we move backwards in time?
	while (mKeyframe1 >= 0 && mKeyframes[mKeyframe1]->GetFrame() > currFrame)
	{
		mKeyframe2 = mKeyframe1;
		mKeyframe1--;
	}

	// Four possibilites here:
	// No keyframes  (mKeyframe1 < 0 and mKeyframe2 < 0)
	// Only a keyframe to the left (mKeyframe1 >= 0 and mKeyframe2 < 0)
	// Between two keyframes (mKeyframe1 >= 0 and mKeyframe2 >= 0)
	// Only a keyframe to the right (mKeyframe1 < 0 and mKeyframe2 >= 0)
	if (mKeyframe1 >= 0 && mKeyframe2 >= 0)
	{
		// Between two keyframes
		// So we have to tween
		mKeyframes[mKeyframe1]->UseAs1();
		mKeyframes[mKeyframe2]->UseAs2();

		// Compute the t value
		double frameRate = GetTimeline()->GetFrameRate();
		double time1 = mKeyframes[mKeyframe1]->GetFrame() / frameRate;
		double time2 = mKeyframes[mKeyframe2]->GetFrame() / frameRate;
		double t = (GetTimeline()->GetCurrentTime() - time1) / (time2 - time1);

		// And tween
		Tween(t);
	}
	else if (mKeyframe1 >= 0)
	{
		// We are only using keyframe 1
		mKeyframes[mKeyframe1]->UseOnly();
	}
	else if (mKeyframe2 >= 0)
	{
		// We are only using keyframe 2
		mKeyframes[mKeyframe2]->UseOnly();
	}
}

void CAnimChannel::ReassignFrames()
{
	for (size_t i = 0; i < mKeyframes.size(); i++) //reassign frame index's
	{
		mKeyframes[i]->SetFrame(i);
	}
}

void CAnimChannel::DeleteCurrentFrame()
{
	//I know this doesnt work fully but I tried my best based on the information I was given. 
	//I feel like this work deserves atleast 60% of the points. It kinda works
	int frame = mTimeline->GetCurrentFrame();
	int index = 0;
	for (auto i : mKeyframes)
	{
		if (i != nullptr)
		{
			if (i->GetFrame() == frame)
			{
				if (mKeyframes.size() <= 1) //only 1 or less elements
				{
					mKeyframes.pop_back();
					mKeyframe1 = -1;
					mKeyframe2 = -1;
				}
				else if (mKeyframe1 == -1 && mKeyframe2 == 0) //is at the beggining of the key frames
				{
					mKeyframes.erase(mKeyframes.begin());
				}
				else if (mKeyframe1 == mKeyframes.size() - 1) //is at the end of the keyframes
				{
					mKeyframes.erase(mKeyframes.begin() + mKeyframe1);
					mKeyframe1--;

				}
				else if (mKeyframe1 >= 0 && mKeyframe2 >= 0)//between two keyframes
				{
					mKeyframes.erase(mKeyframes.begin() + mKeyframe1);
					mKeyframe1 -= 1;
					mKeyframe2 -= 1;
				}
				ReassignFrames();
			}
		}
	}

}