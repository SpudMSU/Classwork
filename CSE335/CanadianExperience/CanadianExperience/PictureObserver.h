/**
 * \file PictureObserver.h
 *
 * \author Spencer D Cassetta
 *
 * Picture class observer
 */

#include <iostream>
#include <memory>
#pragma once


class CPicture;

/**
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */

class CPictureObserver
{

private:
	/// Picture we are observing
	std::shared_ptr<CPicture> mPicture;
protected:

	///default constructor
	CPictureObserver() {}
	virtual ~CPictureObserver();
	/// Copy Constructor (Disabled)
	CPictureObserver(const CPictureObserver&) = delete;
	/// Assignment Operator (Disabled)
	void operator=(const CPictureObserver&) = delete;

public:
	/// This function is called to update any observers
	virtual void UpdateObserver() = 0;

	/**Getter for the picture
	*\return the picture of the observer*/
	std::shared_ptr<CPicture> GetPicture() { return mPicture; }

	/**Setter for the picture
	*\param picture is the picture to set*/
	void SetPicture(std::shared_ptr<CPicture> picture);
};

