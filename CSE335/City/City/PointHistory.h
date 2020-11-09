/**
* \file PointHistory.cpp
*
* \author Charles Owen
*
* Class that maintains a collection of Point objects in order.
*/

#pragma once
#include <memory>
#include <random>


/**
 * Class that maintains a collection of Point objects in order.
 */
class CPointHistory
{
public:
    CPointHistory();
    virtual ~CPointHistory();

    void Add(Gdiplus::Point p);


protected:
    /**
    * Nested class that stores up to five points in a bin.
    */
    class PointBin
    {
    public:
        PointBin(int max);
        virtual ~PointBin();

        /// Get the current count of items in this bin
        /// \return Count (zero to MaxPoints)
        int GetCnt() { return mCnt; }

        /// Get the maximum points we allow in this bin
        /// \return Maximum integer value
        int GetMax() { return mMax; }

        bool Add(Gdiplus::Point point);

        /// Get a stored point
        /// \param i Index to the point (0 to mCnt-1)
        /// \return Stored point value
        Gdiplus::Point Get(int i) { return mPoints[i]; }

        /// Get the next bin in the list
        /// \return Pointer to next bin or null if none
        std::shared_ptr<PointBin> GetNext() { return mNext; }

        /// Set the next bin in the list
        /// \param next Next pointer to set
        void SetNext(std::shared_ptr<PointBin> next) { mNext = next; }
		/** Iterator that iterates over some collection */

    private:
        PointBin() = delete;

        /// Array to store the points
        Gdiplus::Point *mPoints;

        /// Maximum number of elements we can store in the array
        int mMax;

        /// Number of elements currently stored in array
        int mCnt = 0;

        /// Next bin
        std::shared_ptr<PointBin> mNext;
    };


    /// Pointer to the head of the linked list of bins
    std::shared_ptr<PointBin> mHead;

private:
    int MakeSize();


    /// Random number generator
    std::mt19937 mGen;

    /// Pointer to the tail of the linked list of bins (last node)
    std::shared_ptr<PointBin> mTail;
public:

	/** Iterator that iterates over the Point History */
	class Iter
	{
	public:
		/** Constructor
		 * \param point The collection we are iterating over 
		 *\param bin is the bin we are on
		 *\param posBin is the position in the bin we are on
		 */
		Iter(CPointHistory* point, std::shared_ptr<PointBin> bin, int posBin) : mPointer(point), mBin(bin), mPos(posBin) {}

		/** Test for end of the iterator
		 * \param other is other iter we are comparing
		 * \returns True if we this position equals not equal to the other position */
		bool operator!=(const Iter& other) const
		{
			if (mBin == other.mBin && mPos == other.mPos)
				return false;
			return true;
		}

		/** Get value at current position
		 * \returns Value at mPos in the collection */
		Gdiplus::Point operator *() const
		{
			return mBin->Get(mPos);
		}

		/** Increment the iterator
		 * \returns Reference to this iterator */
		const Iter& operator++()
		{
			mPos++;
			if (mBin->GetCnt() <= mPos)
			{
				mPos = 0;
				mBin = mBin->GetNext();
			}
			return *this;
		}


	private:
		CPointHistory* mPointer;   ///< Collection we are iterating over
		std::shared_ptr<PointBin> mBin;       ///< Bin in the collection
		int mPos; ///< position in the bin
	};

	/** Get an iterator for the beggining of the collection
	 * \returns Iter to first object in linked list */
	Iter begin() { return Iter(this, mHead, 0); }

	/** Get an iterator for the end of the collection
	 * \returns Iter object at position past the end */
	Iter end() { return Iter(this, nullptr, 0); }

};

