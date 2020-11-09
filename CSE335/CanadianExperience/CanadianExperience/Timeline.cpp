#include "pch.h"
#include "Timeline.h"

/** Sets the current time
*
* Ensures all of the channels are
* valid for that point in time.
*/
void CTimeline::SetCurrentTime(double currentTime)
{
	// Set the time
	mCurrentTime = currentTime;

	for (auto channel : mChannels)
	{
		channel->SetFrame(GetCurrentFrame());
	}
}