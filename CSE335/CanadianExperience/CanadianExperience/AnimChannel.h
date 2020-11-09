/**
*\file AnimChannel.h
*\author Spencer Cassetta
*
*/
#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
class CTimeline;
/**
 * Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
class CAnimChannel
{
public:
	///default constructor
	CAnimChannel() {}
	/** Copy constructor disabled */
	CAnimChannel(const CAnimChannel&) = delete;
	/** Assignment operator disabled */
	void operator=(const CAnimChannel&) = delete;

	///sets the name
	///\param name is the name
	void SetName(std::wstring name) { mName = name; }

	///getter for the name
	///\return the name
	std::wstring GetName() { return mName; }

	///isvalid
	///\returns a boolean
	bool IsValid();

	///Delete the current frame
	void DeleteCurrentFrame();

	///sets the current frame
	///\param currFrame
	void SetFrame(int currFrame);

	///sets the timeline
	///\param timeline is timeline
	void SetTimeline(CTimeline* timeline) { mTimeline = timeline; }

	///Gets the timeline
	///\return timeline
	CTimeline* GetTimeline() { return mTimeline; }

	///reassigns the frames
	void ReassignFrames();

	/** Class that represents a keyframe */
	class Keyframe
	{
	public:
		///default constructor
		Keyframe() = delete;
		/** Copy constructor disabled */
		Keyframe(const Keyframe&) = delete;
		/** Assignment operator disabled */
		void operator=(const Keyframe&);

		///setter for the frame
		///\param currFrame is the frame to set
		void SetFrame(int currFrame) { mFrame = currFrame; }

		///getter for the frame
		///\return mFrame
		int GetFrame() { return mFrame; }

		///defualt constructor
		///\param channel
		Keyframe(CAnimChannel channel);
		/** Use this keyframe as keyframe 1 */
		virtual void UseAs1() {}

		/** Use this keyframe as keyfraem 2 */
		virtual void UseAs2() {}

		/** Use this keyframe as the angle */
		virtual void UseOnly() {}

	private:
		/// The channel this keyframe is associated with
		CAnimChannel* mChannel;

	protected:
		/** Constructor
		 * \param channel Channel we are associated with */
		Keyframe(CAnimChannel* channel) : mChannel(channel) {}

		///member variable for the frame
		int mFrame = -1;
	};

protected:

	///function for tweening
	///\param t
	virtual void Tween(double t) {}

	///insert key frame
	///\param keyframe
	void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);

private:
	///mName
	std::wstring mName;

	///first key frame index
	int mKeyframe1 = -1;

	///second keyframe index
	int mKeyframe2 = -1;

	/// The collection of keyframes for this channel
	std::vector<std::shared_ptr<Keyframe>> mKeyframes;

	/// The timeline object
	CTimeline* mTimeline = nullptr;
};

