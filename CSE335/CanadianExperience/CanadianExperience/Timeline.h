#include "AnimChannel.h"
#include <vector>
#pragma once

/** class for timeline*/
class CTimeline
{

public:
	/** Get the number of frames in the animation
	* \returns Number of frames in the animation
	*/
	int GetNumFrames() const { return mNumFrames; }

	/** Set the number of frames in the animation
	 * \param numFrames Number of frames in the animation
	 */
	void SetNumFrames(int numFrames) { mNumFrames = numFrames; }

	/** Get the frame rate
	 * \returns Animation frame rate in frames per second
	 */
	int GetFrameRate() const { return mFrameRate; }

	/** Set the frame rate
	 * \param frameRate Animation frame rate in frames per second
	 */
	void SetFrameRate(int frameRate) { mFrameRate = frameRate; }

	/** Get the current time
	 * \returns Current animation time in seconds
	 */
	double GetCurrentTime() const { return mCurrentTime; }

	/** Set the current time
	 * \param currentTime new current animation time in seconds
	 */
	void SetCurrentTime(double currentTime);

	/** Get the current frame.
	 *
	 * This is the frame associated with the current time
	 * \returns Current frame
	 */
	int GetCurrentFrame() const { return (int)(GetFrameRate() * GetCurrentTime()); }

	/** Get the animation duration
	 * \returns Animation duration in seconds
	 */
	double GetDuration() const { return (double)GetNumFrames() / (double)GetFrameRate(); }

	///add a channel
	///\param channel
	void AddChannel(CAnimChannel* channel) { mChannels.push_back(channel); channel->SetTimeline(this); }

private:

	///frame variable
	int mNumFrames = 300;

	///rate variable 
	int mFrameRate = 30;

	///current time
	double mCurrentTime = 0.0;

	/// List of all animation channels
	std::vector<CAnimChannel*> mChannels;
};

