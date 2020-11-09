#include "pch.h"
#include "CppUnitTest.h"
#include "AnimChannelAngle.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CAnimChannelAngleTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestName)
		{
			CAnimChannelAngle x;
			x.SetName(L"fred");
			std::wstring test = L"fred";
			Assert::AreEqual(test, x.GetName());

		}

	};
}