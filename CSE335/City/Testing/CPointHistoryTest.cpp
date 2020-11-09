#include "pch.h"
#include <vector>
#include "CppUnitTest.h"
#include "PointHistory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Gdiplus;

namespace Testing
{
    /** Testing stub class, creates a vector from
    * the list. This is done so we can test this
    * before we create the iterator. DO NOT USE
    * THIS CODE to solve the iterator task */
    class CPointHistoryStub : public CPointHistory
    {
    public:
        std::vector<Point> GetPoints()
        {
            std::vector<Point> list;
            auto ptr = mHead;
            while (ptr != nullptr)
            {
                for (int i = 0; i < ptr->GetCnt(); i++)
                {
                    list.push_back(ptr->Get(i));
                }

                ptr = ptr->GetNext();
            }

            return list;
        }
    };
	//
		// The following two functions are used by the test.
		// They must be declared before the test.
		//

		/**
		 * Helper function to assert that two points are equal
		 * \param a First point
		 * \param c Second point
		 */
	void AssertEqual(Point a, Point b)
	{
		Assert::AreEqual(a.X, b.X);
		Assert::AreEqual(a.Y, b.Y);
	}

	/**
	 * Helper function to test that the iterator works
	 * for an arbitrary number of points.
	 * \param num Number of points to test (>= 0)
	 */
	void TestAtSize(int num)
	{
		CPointHistory history;
		vector<Point> points;

		// Create num random test values
		for (int i = 0; i < num; i++)
		{
			Point p(rand() % 100, rand() % 100);
			points.push_back(p);
			history.Add(p);
		}

		auto iter = history.begin();
		auto end = history.end();

		// Test that they are all correct
		for (int i = 0; i < num; i++)
		{
			Assert::IsTrue(iter != end);

			Point a = points[i];
			Point b = *iter;

			Assert::AreEqual(a.X, b.X);
			Assert::AreEqual(a.Y, b.Y);

			++iter;		// Next location
		}

		Assert::IsFalse(iter != end);
	}

    TEST_CLASS(CPointHistoryTest)
    {
    public:

        TEST_METHOD_INITIALIZE(methodName)
        {
            extern wchar_t g_dir[];
            ::SetCurrentDirectory(g_dir);
        }

		TEST_METHOD(TestCPointHistoryIterator)
		{
			CPointHistory history;

			//
			// Ensure the iterator indicates initially empty
			//
			auto iter = history.begin();
			auto end = history.end();
			Assert::IsFalse(iter != end);

			// 
			// Test with one item in the list
			//
			Point a(78, 22);
			history.Add(a);

			iter = history.begin();
			end = history.end();
			Assert::IsTrue(iter != end);
			AssertEqual(*iter, a);

			++iter;
			Assert::IsFalse(iter != end);

			// 
			// Test with two items in the list
			//
			Point b(66, -687);
			history.Add(b);

			iter = history.begin();
			end = history.end();
			Assert::IsTrue(iter != end);
			AssertEqual(*iter, a);

			++iter;
			Assert::IsTrue(iter != end);
			AssertEqual(*iter, b);

			++iter;
			Assert::IsFalse(iter != end);

			//
			// Test with varying numbers of items in the list
			//
			for (int num = 0; num < 21; num++)
			{
				wstringstream str;
				str << L"Testing " << num << " items in list." << endl;
				Logger::WriteMessage(str.str().c_str());
				TestAtSize(num);
			}
		}
        TEST_METHOD(TestCPointHistoryAdd)
        {
            CPointHistoryStub history;

            // Vector for test data
            vector<Point> testData;

            // Ensure initially empty
            TestEqual(testData, history.GetPoints());

            // Create some simple test data
            for (int i = 0; i < 3; i++)
            {
                Point p(187 - i, 23 + i);
                testData.push_back(p);
                history.Add(p);
            }

            // And test
            TestEqual(testData, history.GetPoints());

            // Create some simple test data
            for (int i = 0; i < 117; i++)
            {
                Point p(i, 87 - i);
                testData.push_back(p);
                history.Add(p);
            }

            // And test
            TestEqual(testData, history.GetPoints());
        }

        void TestEqual(vector<Point> a, vector<Point> b)
        {
            Assert::AreEqual(a.size(), b.size());
            for (size_t i = 0; i < a.size(); i++) 
            {
                Assert::AreEqual(a[i].X, b[i].X);
                Assert::AreEqual(a[i].Y, b[i].Y);
            }
        }

    };


}