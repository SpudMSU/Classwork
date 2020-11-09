/**
 * \file CAquarium Test
 *
 * \author Spencer Cassetta
 *
 */
#include "pch.h"
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include "CppUnitTest.h"
#include "Aquarium.h"
#include "XmLNode.h"
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
const unsigned int RandomSeed = 1238197374;
#include "Item.h"
#include "FishBeta.h"
#include "FishAngel.h"
#include "FishStinky.h"
#include "FishBubbles.h"
#include "DecorCastle.h"
/*
*class for testing Aquarium
*/
namespace Testing
{
	TEST_CLASS(CAquariumTest)
	{
	public:
			/**
			* Create a path to a place to put temporary files
			*/
			/**
		   * Test to ensure an aquarium .aqua file is empty
		   */
		   /**
	*  Populate an aquarium with three Beta fish
	*/
		void PopulateAllTypes(CAquarium * aquarium)
		{
			srand(RandomSeed); //seed the rand
			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(aquarium);
			fish1->SetLocation(100, 200);
			aquarium->Add(fish1);

			srand(RandomSeed);
			shared_ptr<CFishAngel> fish2 = make_shared<CFishAngel>(aquarium);
			fish2->SetLocation(400, 400);
			aquarium->Add(fish2);

			srand(RandomSeed);
			shared_ptr<CFishStinky> fish3 = make_shared<CFishStinky>(aquarium);
			fish3->SetLocation(600, 100);
			aquarium->Add(fish3);

			srand(RandomSeed);
			shared_ptr<CFishBubbles> fish4 = make_shared<CFishBubbles>(aquarium);
			fish4->SetLocation(550, 150);
			aquarium->Add(fish4);

			shared_ptr<CDecorCastle> castle1 = make_shared<CDecorCastle>(aquarium);
			castle1->SetLocation(500, 200);
			aquarium->Add(castle1);
		}
		void TestAllTypes(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Ensure three items
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

			// Ensure the positions are correct
			
			//only testing for x speed due to inablility 
			//to calculate y with a parrallel seed on rand

			srand(RandomSeed);
			//test for beta speed
			size_t speed = (size_t)rand() / (size_t)(RAND_MAX * 20.0);
			Assert::IsTrue(regex_search(xml, wregex(L"<item speedX=", speed)));

			//test angel
			srand(RandomSeed);
			speed = (size_t)rand() / (size_t)(RAND_MAX * 50.0) + 5;
			Assert::IsTrue(regex_search(xml, wregex(L"<item speedX=", speed)));

			//test stinky
			srand(RandomSeed);
			speed = (size_t)rand() / (size_t)(RAND_MAX * 30.0);
			Assert::IsTrue(regex_search(xml, wregex(L"<item speedX=", speed)));

			//test bubbles
			srand(RandomSeed);
			speed = (size_t)rand() / (size_t)(RAND_MAX * 50.0);
			Assert::IsTrue(regex_search(xml, wregex(L"<item speedX=", speed)));

			

			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"550\" y=\"150\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"500\" y=\"200\"")));

			// Ensure the types are correct
			Assert::IsTrue(regex_search(xml,
				wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"angel\"/><item.* type=\"stinky\"/><item.* type=\"bubbles\"/><item.* type=\"castle\"/></aqua>")));
		}


		void PopulateThreeBetas(CAquarium * aquarium)
		{
			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(aquarium);
			fish1->SetLocation(100, 200);
			aquarium->Add(fish1);

			shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(aquarium);
			fish2->SetLocation(400, 400);
			aquarium->Add(fish2);

			shared_ptr<CFishBeta> fish3 = make_shared<CFishBeta>(aquarium);
			fish3->SetLocation(600, 100);
			aquarium->Add(fish3);
		}


		void TestEmpty(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());
			Assert::IsTrue(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua/>")));

		}
		void TestThreeBetas(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Ensure three items
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

			// Ensure the positions are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));

			// Ensure the types are correct
			Assert::IsTrue(regex_search(xml,
				wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));
		}
		wstring TempPath()
		{
			// Create a path to temporary files
			wchar_t path_nts[MAX_PATH];
			GetTempPath(MAX_PATH, path_nts);

			// Convert null terminated string to wstring
			return wstring(path_nts);
		}

		/**
		* Read a file into a wstring and return it.
		* \param filename Name of the file to read
		* \return File contents
		*/
		wstring ReadFile(const wstring & filename)
		{
			ifstream t(filename);
			wstring str((istreambuf_iterator<char>(t)),
				istreambuf_iterator<char>());

			return str;
		}
		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestCAquariumConstruct)
		{
			CAquarium aquarium;
		}
		TEST_METHOD(TestCAquariumHitTest)
		{
			CAquarium aquarium;

			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr,
				L"Testing empty aquarium");

			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(&aquarium);
			fish1->SetLocation(100, 200);
			aquarium.Add(fish1);

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish1,
				L"Testing fish at 100, 200");
		}
		TEST_METHOD(TestCAquariumSave)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create an aquarium
			CAquarium aquarium;

			//
			// First test, saving an empty aquarium
			//
			wstring file1 = path + L"test1.aqua";
			aquarium.Save(file1);

			TestEmpty(file1);
			//
		   // Now populate the aquarium
		   //

			PopulateThreeBetas(&aquarium);

			wstring file2 = path + L"test2.aqua";
			aquarium.Save(file2);

			TestThreeBetas(file2);

			CAquarium aquarium3;
			PopulateAllTypes(&aquarium3);

			wstring file3 = path + L"test3.aqua";
			aquarium3.Save(file3);

			TestAllTypes(file3);

		}
		TEST_METHOD(TestCAquariumClear)
		{
			CAquarium aquarium;
			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(&aquarium);
			fish1->SetLocation(140, 200);
			aquarium.Add(fish1);

			shared_ptr<CFishAngel> fish2 = make_shared<CFishAngel>(&aquarium);
			fish2->SetLocation(130, 200);
			aquarium.Add(fish2);

			shared_ptr<CFishBubbles> fish3 = make_shared<CFishBubbles>(&aquarium);
			fish3->SetLocation(120, 200);
			aquarium.Add(fish3);

			shared_ptr<CDecorCastle> castle1 = make_shared<CDecorCastle>(&aquarium);
			castle1->SetLocation(110, 200);
			aquarium.Add(castle1);

			aquarium.Clear();

			Assert::IsTrue(aquarium.HitTest(140, 200) == nullptr,
					L"Testing empty aquarium");
			Assert::IsTrue(aquarium.HitTest(130, 200) == nullptr,
				L"Testing empty aquarium");
			Assert::IsTrue(aquarium.HitTest(120, 200) == nullptr,
				L"Testing empty aquarium");
			Assert::IsTrue(aquarium.HitTest(110, 200) == nullptr,
				L"Testing empty aquarium");
			

		}
		TEST_METHOD(TestCAquariumLoad)
		{
			// Create a path to temporary files
			wstring path = TempPath();

			// Create two aquariums
			CAquarium aquarium, aquarium2;

			//
			// First test, saving an empty aquarium
			//
			wstring file1 = path + L"test1.aqua";

			aquarium.Save(file1);
			TestEmpty(file1);

			aquarium2.Load(file1);
			aquarium2.Save(file1);
			TestEmpty(file1);

			//
			// Now populate the aquarium
			//

			PopulateThreeBetas(&aquarium);

			wstring file2 = path + L"test2.aqua";
			aquarium.Save(file2);
			TestThreeBetas(file2);

			aquarium2.Load(file2);
			aquarium2.Save(file2);
			TestThreeBetas(file2);

			//
			// Test all types
			//
			CAquarium aquarium3;
			PopulateAllTypes(&aquarium3);

			wstring file3 = path + L"test3.aqua";
			aquarium3.Save(file3);
			TestAllTypes(file3);

			aquarium2.Load(file3);
			aquarium2.Save(file3);
			TestAllTypes(file3);
		}
	};
}