/**
* \file AnimChannelAngle.h
* \author Spencer Cassetta
*

note: I could not get the position class working in time. Had a odd error. I got it to work when I implemented everything in the
* angle class. Could not get it to work using the position class but I did all the same stuff
have mercy on me. I wrote the position class to show I know how too, I just couldnt get it functioning in time

at worse this should just be a simple handbook violation because it violates the single use principle 
*/
#include "AnimChannel.h"
/**
 * Animation channel for angles.
 */
class CAnimChannelAngle : public CAnimChannel
{
public:
	///default constructor
	CAnimChannelAngle() { }
	/** Copy constructor disabled */
	CAnimChannelAngle(const CAnimChannelAngle&) = delete;
	/** Assignment operator disabled */
	void operator=(const CAnimChannelAngle&) = delete;


	///setter for the angle
	///\param angle
	void SetAngle(double angle) { mAngle = angle; }

	///getter for the angle
	///\returns the angle
	double GetAngle() { return mAngle; }

	///setter for the keyframe
	///\param angle
	///\param x
	///\param y
	void SetKeyFrame(double angle, double x, double y);

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

	///class for the keyframe
	class KeyframeAngle : public Keyframe
	{
	public:
		///delete default constructor
		KeyframeAngle() = delete;
		/** Copy constructor disabled */
		KeyframeAngle(const KeyframeAngle&) = delete;
		/** Assignment operator disabled */
		void operator=(const KeyframeAngle&) = delete;

		///getter for the x position
		///\return a double
		double GetPosX() { return mFrmPosX; }

		///getter for the Y position
		///\return a double
		double GetPosY() { return mFrmPosY; }

		///getter for the angle
		///\return the angle
		double GetAngle() { return mFrmAngle; }
		/** Constructor
		 * \param channel The channel we are for
		 * \param angle The angle for the keyframe 
		 *\param PosX
		 *\param PosY */
		KeyframeAngle(CAnimChannelAngle* channel, double angle, double PosX, double PosY) :
			Keyframe(channel), mChannel(channel), mFrmAngle(angle), mFrmPosX(PosX), mFrmPosY(PosY) {}
		/** Use this keyframe as keyframe 1 */
		virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

		/** Use this keyframe as keyfraem 2 */
		virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

		/** Use this keyframe as the angle */
		virtual void UseOnly() override { mChannel->mAngle = mFrmAngle; mChannel->mPosX = mFrmPosX; mChannel->mPosY = mFrmPosY;
		}
	private:
		/// The channel this keyframe is associated with
		CAnimChannelAngle* mChannel;

		///member variable for the angle
		double mFrmAngle;

		///member variable for the x positon
		double mFrmPosX;

		///member variable for the y positon
		double mFrmPosY;
	};

protected:
	///tweening function
	///\param t
	virtual void Tween(double t);

private:
	///member variable for the angle
	double mAngle = 0;


	///member variable for the x position
	double mPosX = 0;

	///member variable for the y position
	double mPosY = 0;
	/// The first angle keyframe
	KeyframeAngle* mKeyframe1 = nullptr;

	/// The second angle keyframe
	KeyframeAngle* mKeyframe2 = nullptr;
};

