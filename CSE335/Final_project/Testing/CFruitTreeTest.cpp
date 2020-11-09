#include "pch.h"
#include "CppUnitTest.h"
#include "FruitTree.h"
#include "Tree.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CFruitTreeTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(construct)
		{
			//CFruitTree tree;
			//tree->SetLocation(10, 10);
			//Assert::AreEqual(tree->GetLocation().X, 10);
			//Assert::AreEqual(tree->GetLocation().Y, 10);
			//tree->SetTreeFrame(30);
			//Assert::AreEqual(tree->GetTreeFrame(), 30);
		}

	};
}