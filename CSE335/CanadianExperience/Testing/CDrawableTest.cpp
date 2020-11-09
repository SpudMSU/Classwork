#include "pch.h"
#include "CppUnitTest.h"
#include "Drawable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	class CDrawableMock : public CDrawable
	{
	public:
		//make constructor public for testing
		CDrawableMock(const std::wstring& name) : CDrawable(name) {}
		virtual void Draw(Gdiplus::Graphics* graphics) override {}
		virtual bool HitTest(Gdiplus::Point pos) override { return false; }
	};
	TEST_CLASS(CDrawableTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestNothing)
		{
			// This is an empty test just to ensure the system is working
		}
		TEST_METHOD(TestDrawableConstructor)
		{
			std::wstring myName = L"fred";
			CDrawableMock drawable(myName);
			Assert::AreEqual(drawable.GetName(), myName);
		}
		TEST_METHOD(TestPosition)
		{
			CDrawableMock drawable(L"ted");
			Assert::IsTrue(drawable.GetPosition().X == 0);
			Assert::IsTrue(drawable.GetPosition().Y == 0);
			drawable.SetPosition(Gdiplus::Point(10, 15));
			Assert::IsTrue(drawable.GetPosition().X == 10);
			Assert::IsTrue(drawable.GetPosition().Y == 15);
		}
		TEST_METHOD(TestRotation)
		{
			CDrawableMock drawable(L"ted");
			Assert::IsTrue(drawable.GetRotation() == 0);
			drawable.SetRotation(99);
			Assert::IsTrue(drawable.GetRotation() == 99);
		}
		TEST_METHOD(TestCDrawableAssociation)
		{
			CDrawableMock body(L"Body");
			auto arm = std::make_shared<CDrawableMock>(L"Arm");
			auto leg = std::make_shared<CDrawableMock>(L"Leg");

			Assert::IsNull(arm->GetParent());
			Assert::IsNull(leg->GetParent());

			body.AddChild(arm);
			body.AddChild(leg);

			Assert::IsTrue(arm->GetParent() == &body);
			Assert::IsTrue(leg->GetParent() == &body);
		}
	};
}