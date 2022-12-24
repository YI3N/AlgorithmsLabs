#include "Sort.h"
#include <random>
#include <string>

TEST(QuickSortTest, SortTestInt)
{
	std::srand(time(NULL));
	int* array = new int[10000];
	for (int i = 0; i < 10000; ++i)
	{
		array[i] = std::rand() % 200001 - 100000;
	}

	Quick(array, array + 10000 - 1, [](int a, int b) { return a < b; }, false);

	for (int i = 1; i < 10000; ++i)
	{
		EXPECT_TRUE(array[i - 1] <= array[i]);
	}
}

TEST(InsertSortTest, SortTestInt)
{
	std::srand(time(NULL));
	int* array = new int[10000];
	for (int i = 0; i < 10000; ++i)
	{
		array[i] = array[i] = std::rand() % 200001 - 100000;
	}

	Insertions(array, array + 10000 - 1, [](int a, int b) { return a < b; });

	for (int i = 1; i < 10000; ++i)
	{
		EXPECT_TRUE(array[i - 1] <= array[i]);
	}
}

TEST(QuickSortTest, SortTestString)
{
	std::srand(time(NULL));
	std::string* array = new std::string[10000];
	for (int i = 0; i < 10000; ++i)
	{
		array[i] = std::to_string(std::rand() % 200001 - 100000);
	}

	Quick(array, array + 10000 - 1, [](std::string a, std::string b) { return a < b; }, false);

	for (int i = 1; i < 10000; ++i)
	{
		EXPECT_TRUE(array[i - 1] <= array[i]);
	}
}

TEST(InsertSortTest, SortTestString)
{
	std::srand(time(NULL));
	std::string* array = new std::string[10000];
	for (int i = 0; i < 10000; ++i)
	{
		array[i] = std::to_string(std::rand() % 200001 - 100000);
	}

	Insertions(array, array + 10000 - 1, [](std::string a, std::string b) { return a < b; });

	for (int i = 1; i < 10000; ++i)
	{
		EXPECT_TRUE(array[i - 1] <= array[i]);
	}
}