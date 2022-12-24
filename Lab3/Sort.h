#pragma once
#include <utility>

template<typename T, typename Compare> 
T GetPivot(T* first, T* last, Compare comp)
{
	T* middle = first + (last-first) / 2;
	if (comp(*last, *first))
		std::swap(*first, *last);
	if (comp(*middle, *first))
		std::swap(*first, *middle);
	if (comp(*last, *middle))
		std::swap(*last, *middle);
	return *middle;
}

template<typename T, typename Compare>
T* Partition(T* first, T* last, Compare comp)
{
	T pivot = GetPivot(first, last, comp);
	T* f = first;
	T* l = last;
	while (true)
	{
		while (comp(*f, pivot))
			f++;
		while (comp(pivot, *l))
			l--;
		if (f >= l)
			break;

		std::swap(*f, *l);
		f++;
		l--;
	}
	return l;
}

template<typename T, typename Compare>
void Quick(T* first, T* last, Compare comp, bool useInsertions)
{
	while (last - first > 0)
	{
		if (useInsertions && last - first <= 60)
		{
			Insertions(first, last, comp);
			return;
		}

		T* p = Partition(first, last, comp);

		if (p - first < last - p - 1)
		{
			Quick(first, p, comp, useInsertions);
			first = p + 1;
		}
		else
		{
			Quick(p + 1, last, comp, useInsertions);
			last = p;
		}
	}
}

template<typename T, typename Compare> 
void Insertions(T* first, T* last, Compare comp)
{
	for (T* i = first; i <= last; i++)
	{
		T* j = i - 1;
		T temp = std::move(*i);

		while (j >= first && comp(temp, *j))
		{
			*(j + 1) = std::move(*j);
			j--;
		}
		*(j + 1) = std::move(temp);
	}
}