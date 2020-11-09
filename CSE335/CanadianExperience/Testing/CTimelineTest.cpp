#include "pch.h"
#include "CppUnitTest.h"
#include "Timeline.h"
#include "AnimChannelAngle.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CTimelineTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		TEST_METHOD(TestNumFrames)
		{
			CTimeline timeline;

			//default value
			Assert::AreEqual(300, timeline.GetNumFrames());

			//test getter & setter
			timeline.SetNumFrames(2);
			Assert::AreEqual(2, timeline.GetNumFrames());
		}
		TEST_METHOD(TestFrameRate)
		{
			CTimeline timeline;

			//default value
			Assert::AreEqual(30, timeline.GetFrameRate());

			//test getter & setter
			timeline.SetFrameRate(22);
			Assert::AreEqual(22, timeline.GetFrameRate());
		}
		TEST_METHOD(TestCurrentTime)
		{
			CTimeline timeline;

			//default value
			Assert::AreEqual(0.0, timeline.GetCurrentTime());

			//test getter & setter
			timeline.SetCurrentTime(43.3);
			Assert::AreEqual(43.3, timeline.GetCurrentTime());
		}
		TEST_METHOD(TestCTimelineGetDuration)
		{
			CTimeline timeline;

			// Default value
			Assert::AreEqual(10, timeline.GetDuration(), 0.0001);

			// Changed duration
			timeline.SetFrameRate(375);
			Assert::AreEqual(300.0 / 375.0, timeline.GetDuration(), 0.0001);

			timeline.SetNumFrames(789);
			Assert::AreEqual(789.0 / 375.0, timeline.GetDuration(), 0.0001);
		}

		TEST_METHOD(TestCTimelineGetCurrentFrame)
		{
			CTimeline timeline;

			// Default value
			Assert::AreEqual(0, timeline.GetCurrentFrame());

			// Changed time
			timeline.SetCurrentTime(9.27);
			Assert::AreEqual(278, timeline.GetCurrentFrame());
		}
		TEST_METHOD(TestCTimelineAdd)
		{
			CTimeline timeline;
			CAnimChannelAngle channel;

			timeline.AddChannel(&channel);
			Assert::IsTrue(&timeline == channel.GetTimeline());
		}
	};
}