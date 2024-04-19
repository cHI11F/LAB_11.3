#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_11.3/LAB_11.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestBinarySearch)
		{
			
			vector<Student> students;
			Student student1 = { "Smith", 1, "Computer Science", 85.0, 90.0, 88.0 };
			Student student2 = { "Johnson", 2, "Electrical Engineering", 75.0, 80.0, 82.0 };
			students.push_back(student1);
			students.push_back(student2);

		
			Assert::IsTrue(binarySearch(students, "Smith", 1, "Computer Science")); 
			Assert::IsFalse(binarySearch(students, "Brown", 3, "Physics")); 
		}
	};
}
