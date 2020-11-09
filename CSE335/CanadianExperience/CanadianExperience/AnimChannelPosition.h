/**
* \file AnimChannelAngle.h
* \author Spencer Cassetta
*

* 
*/
#include "AnimChannel.h"
/**
 * Animation channel for angles.
 */
class CAnimChannelPosition : public CAnimChannel
{
public:
	///default constructor
	CAnimChannelPosition() { }
	/** Copy constructor disabled */
	CAnimChannelPosition(const CAnimChannelPosition&) = delete;
	/** Assignment operator disabled */
	void operator=(const CAnimChannelPosition&) = delete;

	///setter for the X
	///\param PosX
	void SetPosX(double PosX) { mPosX = PosX; }

	///getter for the x position
	///\return a double
	double GetPosX() { return mPosX; }


	///setter for the Y position
	///\param PosY
	void SetPosY(double PosY) { mPosY = PosY; }

	///getter for the y position
	///\returns a double
	double GetPosY() { return mPosY; }

	///setter for the keyframe
	///\param posX
	///\param posY
	void SetKeyFrame(double posX, double posY);

	///class for the keyframe
	class KeyframePosition : public Keyframe
	{
	public:

		///delete default constructor
		KeyframePosition() = delete;
		/** Copy constructor disabled */
		KeyframePosition(const KeyframePosition&) = delete;
		/** Assignment operator disabled */
		void operator=(const KeyframePosition&) = delete;

		///getter for the x position
		///\return a double
		double GetPosX() { return mFrmPosX; }

		///getter for the Y position
		///\return a double
		double GetPosY() { return mFrmPosY; }
		/** Constructor
		 * \param channel The channel we are for
		 * \param mPosX
		 * \param mPosY*/
		KeyframePosition(CAnimChannelPosition* channel, double mPosX, double mPosY) :
			Keyframe(channel), mChannel(channel), mFrmPosX(mPosX), mFrmPosY(mPosY) {}
		/** Use this keyframe as keyframe 1 */
		virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

		/** Use this keyframe as keyfraem 2 */
		virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

		/** Use this keyframe as the angle */
		virtual void UseOnly() override { mChannel->mPosX = mFrmPosX; mChannel->mPosY = mFrmPosY;}
	private:
		/// The channel this keyframe is associated with
		CAnimChannelPosition* mChannel;

		///member variable for x pos
		double mFrmPosX;

		///member variable for y pos
		double mFrmPosY;
	};

protected:

	///tween function
	///\param t
	virtual void Tween(double t);

private:
	///member variable for the x position
	double mPosX = 0;

	///member variable for the y position
	double mPosY = 0;

	/// The first angle keyframe
	KeyframePosition* mKeyframe1;

	/// The second angle keyframe
	KeyframePosition* mKeyframe2;
};