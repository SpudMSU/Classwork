#include "pch.h"
#include <iostream>
#include <memory>
#include "CppUnitTest.h"
#include "Picture.h"
#include "PictureObserver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	class CPictureObserverMock : public CPictureObserver
	{
	public:
		bool mUpdated = false;
		virtual void UpdateObserver() override { mUpdated = true; }
		CPictureObserverMock() : CPictureObserver() {}

	};
	TEST_CLASS(CPictureObserverTest)
	{
	public:
		
		TEST_METHOD(TestNothing)
		{
			// This is an empty test just to ensure the system is working
		}
		TEST_METHOD(TestCPictureObserverConstruct)
		{
			CPictureObserverMock observer;
		}
		TEST_METHOD(TestCPictureObserverOneObserver)
		{
			// Allocate a CPicture object
			std::shared_ptr<CPicture> picture = std::make_shared<CPicture>();

			// Create a mock observer object
			CPictureObserverMock observer;

			// And set it for the observer:
			observer.SetPicture(picture);

			picture->UpdateObservers();

			Assert::IsTrue(observer.mUpdated);

		}
		TEST_METHOD(GetPicture)
		{
			// Allocate a CPicture object
			std::shared_ptr<CPicture> picture = std::make_shared<CPicture>();

			//test getPicture by giving picture a unique size
			Gdiplus::Size uniqueSize(10, 10);

			CPictureObserverMock observer;
			picture->SetSize(uniqueSize);

			//giving the pic to the observer
			observer.SetPicture(picture);

			//getting it back
			std::shared_ptr<CPicture> retrieved = observer.GetPicture();

			//then testing it for the unique size
			Assert::AreEqual(retrieved->GetSize().Height, uniqueSize.Height);
			Assert::AreEqual(retrieved->GetSize().Width, uniqueSize.Width);
		}
		TEST_METHOD(UpdateObservers)
		{
			std::shared_ptr<CPicture> picture = std::make_shared<CPicture>();

			//make the observers
			CPictureObserverMock observer1;
			CPictureObserverMock observer2;

			observer1.SetPicture(picture);
			observer2.SetPicture(picture);

			//put in picture
			picture->AddObserver(&observer1);
			picture->AddObserver(&observer2);

			//call update observer
			picture->UpdateObservers();

			//test to see if observer bools were set to true
			Assert::IsTrue(observer1.mUpdated);
			Assert::IsTrue(observer2.mUpdated);
		}
		TEST_METHOD(DestroyObserver)
		{
			std::shared_ptr<CPicture> picture = std::make_shared<CPicture>();

			//make the observers
			CPictureObserverMock *observer1 = new CPictureObserverMock;
			CPictureObserverMock *observer2 = new CPictureObserverMock;

			//put in picture
			picture->AddObserver(observer1);
			picture->AddObserver(observer2);

			observer1->SetPicture(picture);
			observer2->SetPicture(picture);

			delete observer1;
			picture->RemoveObserver(observer1);

			picture->UpdateObservers();
			//test that other observer still functions
			Assert::IsTrue(observer2->mUpdated);
		}

	};
}