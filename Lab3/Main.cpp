#include "Sort.h"
#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <chrono>
#include <fstream>


void PerformanceTest()
{
	int maxSize = 100;
	int repeats = 10000;

	typedef std::chrono::nanoseconds ns;
	typedef std::chrono::high_resolution_clock clock;

	std::ofstream os("stats.txt");

	for (int i = 2; i <= maxSize; i++)
	{
		ns insertSortTime = std::chrono::nanoseconds(0);
		ns quickSortTime = std::chrono::nanoseconds(0);

		std::cout << i << " of " << maxSize << std::endl;
		for (int k = 0; k < repeats; ++k)
		{
			int* arrayA = new int[i];
			int* arrayB = new int[i];

			for (int j = 0; j < i; j++)
			{
				arrayA[j] = std::rand() % 200001 - 100000;
				arrayB[j] = arrayA[j];
			}

			auto startInsretTime = clock::now();
			Insertions(arrayA, arrayA + i - 1, [](int a, int b) { return a < b; });
			auto endInsretTime = clock::now();

			auto startQuickTime = clock::now();
			Quick(arrayB, arrayB + i - 1, [](int a, int b) { return a < b; }, false);
			auto endQuickTime = clock::now();

			insertSortTime += (endInsretTime - startInsretTime);
			quickSortTime += (endQuickTime - startQuickTime);

			delete[] arrayA;
			delete[] arrayB;
		}

		insertSortTime /= repeats;
		quickSortTime /= repeats;

		os << i << "\t";
		os << insertSortTime.count() << "\t";
		os << quickSortTime.count() << std::endl;
	}

	os.close();
}

void WorkTest()
{
	const size_t size = 10;
	int* quick = new int[size];
	int* insert = new int[size];
	int* standart = new int[size];

	std::cout << "Unsorted" << std::endl;
	std::cout << "Quick\tInset\tStandard" << std::endl;

	for (size_t i = 0; i < size; i++)
	{
		quick[i] = std::rand() % 2001 - 1000;
		insert[i] = quick[i];
		standart[i] = quick[i];
		std::cout << quick[i] << "\t" << insert[i] << "\t" << standart[i] << std::endl;
	}

	Insertions(insert, (insert + size - 1), [](int a, int b) { return a < b; });
	Quick(quick, (quick + size - 1), [](int a, int b) { return a < b; }, true);
	std::sort(standart, standart + size, [](int a, int b) { return a < b; });

	std::cout << "Sorted" << std::endl;
	std::cout << "Quick\tInset\tStandard" << std::endl;

	for (size_t i = 0; i < size; i++)
	{
		std::cout << quick[i] << "\t" << insert[i] << "\t" << standart[i] << std::endl;
	}

	delete[] quick;
	delete[] insert;
	delete[] standart;
}

int main()
{
	std::srand(time(NULL));

	//PerformanceTest();
	WorkTest();
}