/**
 * \file CFishBeta Test
 *
 * \author Spencer Cassetta
 *
 */

#include "pch.h"
#include "CppUnitTest.h"
#include "FishBeta.h"
#include "Aquarium.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//class for testing CFishBeta
namespace Testing
{
	TEST_CLASS(CFishBetaTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		TEST_METHOD(TestCAquariumHitTest)
		{
			CAquarium aquarium;

			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr,
				L"Testing empty aquarium");

			std::shared_ptr<CFishBeta> fish1 = std::make_shared<CFishBeta>(&aquarium);
			fish1->SetLocation(100, 200);
			aquarium.Add(fish1);

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish1,
				L"Testing fish at 100, 200");
		}

		/*
		tests that:

		If two images are on top of each other, it finds the image on top.
		
		It returns nullptr if you test where there is no image.

		*/
		TEST_METHOD(TestCAquariumTaskTest)
		{
			CAquarium aquarium;
			std::shared_ptr<CFishBeta> fish1 = std::make_shared<CFishBeta>(&aquarium);
			fish1->SetLocation(80, 100);
			aquarium.Add(fish1);

			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr,
				L"Testing empty space");

			std::shared_ptr<CFishBeta> fish2 = std::make_shared<CFishBeta>(&aquarium);
			fish2->SetLocation(100, 200);
			aquarium.Add(fish2);
			std::shared_ptr<CFishBeta> fish3 = std::make_shared<CFishBeta>(&aquarium);
			fish3->SetLocation(100, 200);
			aquarium.Add(fish3);

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish3,
				L"Testing fish on top");
		}
		TEST_METHOD(basicTest) 
		{
			CAquarium aq;
			CFishBeta fish(&aq);
		}
	};
}