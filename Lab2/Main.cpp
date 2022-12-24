#include <iostream>
#include "DynamicArray.h"

int main()
{
	DynamicArray<int> a;

	std::cout << "Array A\n";
	for (int i = 0; i < 32; i++)
	{
		a.insert(i + 1);
		std::cout << a[i] << "\n";
	}
	std::cout << "Size: " << a.size() << "\n";
	std::cout << "Capacity: " << a.getCapacity() << "\n\n";

	a.insert(4, 50);
	std::cout << "Insert 50 at 4\n";
	std::cout << "New Size: " << a.size() << "\n";
	std::cout << "New Capacity: " << a.getCapacity() << "\n\n";


	std::cout << "Create ArrayB, which is set as copy of ArrayA on initialization\n";
	std::cout << "Double ArrayA\n";
	std::cout << "ArrayA\tArrayB\n";
	DynamicArray<int> b = a;
	for (int i = 0; i < a.size(); i++)
	{
		a[i] *= 2;
		std::cout << a[i] << "\t" << b[i] << "\n";
	}

	std::cout << "\nShow ArrayA in reverse\n";
	for (auto i = a.reverseIterator(); i.hasNext(); i.next())
		std::cout << i.get() << std::endl;
}
