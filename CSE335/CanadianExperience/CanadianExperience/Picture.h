/**
 * \file Picture.h
 *
 * \author Spencer D Cassetta
 *
 * Picture class
 */

#include<iostream>
#include<vector>
#include "Actor.h"
#include "Timeline.h"
#pragma once

class CPictureObserver;
/**
 * The picture we are drawing.
 *
 * There will be one picture object that contains all of
 * our actors, which then contains the drawables.
 */
class CPicture
{

public:
	///default constructor
	CPicture() {}

	/// Copy Constructor (Disabled)
	CPicture(const CPicture&) = delete;
	/// Assignment Operator (Disabled)
	void operator=(const CPicture&) = delete;

	/** The picture size
	* \returns Size */
	Gdiplus::Size GetSize() { return mSize; }

	/** The picture size
	* \param size The new picture size */
	void SetSize(Gdiplus::Size size) { mSize = size; }

	///adds observer
	///\param observer
	void AddObserver(CPictureObserver* observer);

	///removes observer
	///\param observer
	void RemoveObserver(CPictureObserver* observer);

	///updates observer
	void UpdateObservers();

	///draws
	///\param graphics
	void Draw(Gdiplus::Graphics* graphics);


	/**Adds an actor
	*\param actor is the actor add*/
	void AddActor(std::shared_ptr<CActor> actor);

	///sets animation
	///\param time
	void SetAnimationTime(double time);

	/** Iterator that iterates over some collection */
	class Iter
	{
	public:
		/** Constructor
		 * \param pic The collection we are iterating over
		 *\param pos is the position*/
		Iter(CPicture* pic, int pos) : mPic(pic), mPos(pos) {}

		/**Test for end of the iterator
		*\param other
		 *\returns True if we this position equals not equal to the other position */
		bool operator!=(const Iter& other) const
		{
			return mPos != other.mPos;
		}

		/** Get value at current position
		 * \returns Value at mPos in the collection */
		std::shared_ptr<CActor> operator *() const { return mPic->mActors[mPos]; }

		/** Increment the iterator
		 * \returns Reference to this iterator */
		const Iter& operator++()
		{
			mPos++;
			return *this;
		}


	private:
		CPicture* mPic;   ///< Collection we are iterating over
		int mPos;       ///< Position in the collection
	};

	/** Get an iterator for the beginning of the collection
 * \returns Iter object at position 0 */
	Iter begin() { return Iter(this, 0); }

	/** Get an iterator for the end of the collection
	 * \returns Iter object at position past the end */
	Iter end() { return Iter(this, mActors.size()); }

	/** Get a pointer to the Timeline object
	 * \returns Pointer to the Timeline object
	 */
	CTimeline* GetTimeline() { return &mTimeline; }

private:
	/// The picture size
	Gdiplus::Size mSize = Gdiplus::Size(800, 600);

	/// The observers of this picture
	std::vector<CPictureObserver*> mObservers;

	///vector of actors the picture belongs to
	std::vector<std::shared_ptr<CActor>> mActors;

	/// The animation timeline
	CTimeline mTimeline;
};

