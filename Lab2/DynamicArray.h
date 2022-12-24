#pragma once
#include <iostream>

template <typename T>
class DynamicArray final
{
	public:
		class Iterator
		{
			public:
				Iterator(DynamicArray<T>* array, T* head, bool isReversed)
				{
					this->array = array;
					this->head = head;
					this->isReverced = isReversed;
					current = head;
				};

				const T& get() const
				{
					return *current;
				}

				void set(const T& value)
				{
					*current = value;
				}

				void next()
				{
					if (isReverced) 
						current -= 1;
					else			
						current += 1;
				}

				bool hasNext() const
				{
					if (isReverced)
					{
						if (current == head - array->size())	
							return false;
						return true;
					}
					else
					{
						if (current == array->size() + head)	
							return false;
						return true;
					}
				};

			protected:
				T* head;
				T* current;
				DynamicArray<T>* array;
				bool isReverced;
		};

		class ConstIterator : public Iterator
		{
			public:
				ConstIterator(DynamicArray<T>* array, T* head, bool isReversed) : Iterator(array, head, isReversed) {}
				void set(const T& value) = delete;
		};

		DynamicArray()
		{
			capacity = kDefaultSize;
			mSize = 0;
			data = (T*)malloc(capacity * sizeof(T));
		};

		DynamicArray(size_t capacity)
		{
			this->capacity = capacity;
			mSize = 0;
			data = (T*)malloc(this -> capacity * sizeof(T));
		};

		DynamicArray(DynamicArray& other)
		{
			mSize = other.mSize;
			capacity = other.capacity;
			data = (T*)malloc(mSize * sizeof(T));
			for (size_t i = 0; i < mSize; i++)
				new (data + i) T(other.data[i]);
		};

		~DynamicArray()
		{
			for (size_t i = 0; i < mSize; i++)
				data[i].~T();
			free(data);
		};

		int insert(const T& value)
		{
			if (mSize == capacity) 
				expand();

			new (data + mSize) T(value);
			mSize++;

			return mSize - 1;
		};

		int insert(int index, const T& value)
		{
			if (index < 0 || index >= mSize) 
				return -1;

			if (mSize == capacity) 
				expand();

			mSize++;

			for (size_t i = mSize - 1; i > index; --i)
			{
				new (data + i) T(std::move(data[i - 1]));
				data[i - 1].~T();
			}

			new(data + index) T(value);
			return index;
		};

		void remove(int index)
		{
			if (index < 0 || index >= mSize) 
				throw "Index out of bounds\n";

			data[index].~T();

			for (size_t i = index; i < mSize - 1; ++i)
			{
				data[i].~T();
				new (data + i) T(std::move(data[i + 1]));
			}

			mSize--;
		};

		int size() const
		{
			return mSize;
		}

		void swap(DynamicArray& other)
		{
			std::swap(data, other.data);
			std::swap(mSize, other.mSize);
			std::swap(capacity, other.capacity);
		};

		int getCapacity() const
		{ 
			return capacity;
		}

		Iterator iterator()
		{
			return Iterator(this, data, false);
		}

		Iterator cIterator()
		{
			return ConstIterator(this, data, false);
		}

		Iterator reverseIterator()
		{
			return Iterator(this, data + mSize - 1, true);
		}

		Iterator cReverseIterator()
		{
			return ConstIterator(this, data + mSize - 1, true);
		}

		T& operator[](int index)
		{
			if (index < 0 || index >= mSize)
				throw std::out_of_range("Index out of bounds");

			return *(data + index);
		};

		const T& operator[](int index) const
		{
			if (index < 0 || index >= mSize)
				throw std::out_of_range("Index out of bounds");

			return *(data + index);
		};

		DynamicArray<T>& operator = (DynamicArray other)
		{
			swap(other);
			return *this;
		};

	private:
		const size_t kDefaultSize = 8;
		const int kExpandFactor = 2;

		T* data;
		size_t mSize;
		size_t capacity;

		void expand()
		{
			capacity *= kExpandFactor;
			T* newData = (T*)malloc(capacity * sizeof(T));

			for (size_t i = 0; i < mSize; ++i)
				new (newData + i) T(std::move(data[i]));

			for (size_t i = 0; i < mSize; ++i)
				data[i].~T();

			free(data);
			data = newData;
			newData = nullptr;
		};
};