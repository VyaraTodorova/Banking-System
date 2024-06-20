#pragma once
#include <iostream>
constexpr size_t DEFAULT_SIZE = 8;

template<typename T>
class Collection {
public:
	Collection();
	Collection(const Collection<T>& other);
	Collection(Collection<T>&& other);
	Collection<T>operator=(const Collection<T>& other);
	Collection<T>operator=(Collection<T>&& other);

	void add(const T& element);
	void add(T& element);
	void edit(const T& element, size_t index);
	void remove(unsigned index);

	T& operator[](size_t index);
	T operator[](size_t index)const;
	size_t getCount()const;
	/*size_t getIndex(const T& object)const;*/

	~Collection();
private:
	T* collection;
	size_t size;
	size_t capacity;
	void copyFrom(const Collection& other);
	void moveFrom(Collection&& other);
	void free();
	void resize();
};

template<typename T>
void Collection<T>::free()
{
	delete[] collection;
	size = 0;
	capacity = DEFAULT_SIZE;
}

template<typename T>
void Collection<T>::copyFrom(const Collection& other)
{
	collection = new T[other.capacity];
	for (size_t i = 0; i < other.size; i++)
	{
		collection[i] = other.collection[i];
	}
	size = other.size;
	capacity = other.capacity;
}

template<typename T>
void Collection<T>::moveFrom(Collection&& other)
{
	collection = other.collection;
	other.collection = nullptr;
	size = other.size;
	other.size = 0;
	capacity = other.capacity;
	other.capacity = 0;
}

template<typename T>
void Collection<T>::resize()
{
	capacity *= 2;
	T* newCollection = new T[capacity];

	for (size_t i = 0; i < size; i++)
	{
		newCollection[i] = collection[i];
	}

	delete[] collection;
	collection = newCollection;
}

template<typename T>
Collection<T>::Collection()
{
	collection = new T[DEFAULT_SIZE];
	size = 0;
	capacity = DEFAULT_SIZE;
}

template<typename T>
Collection<T>::Collection(const Collection<T>& other)
{
	copyFrom(other);
}

template<typename T>
Collection<T>::Collection(Collection<T>&& other)
{
	moveFrom(std::move(other));
}

template<typename T>
Collection<T>Collection<T>::operator=(const Collection<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
Collection<T>Collection<T>::operator=(Collection<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
Collection<T>::~Collection()
{
	free();
}

template<typename T>
void Collection<T>::add(const T& element)
{
	if (size >= capacity)
	{
		resize();
	}

	collection[size++] = element;
}

template<typename T>
void Collection<T>::add(T& element)
{
	if (size >= capacity)
	{
		resize();
	}
	
	collection[size++] = std::move(element);
}

template<typename T>
void Collection<T>::edit(const T& element, size_t index)
{
	if (index < 0 || index > size)
	{
		throw std::invalid_argument("Invalid index.");
	}

	collection[index] = element;
}

template<typename T>
void Collection<T>::remove(unsigned index)
{
	if (size == 0)
	{
		throw std::invalid_argument("The collection is empty.");
	}

	if (index >= size)
	{
		throw std::invalid_argument("Invalid index");
	}

	if (index != size - 1)
	{
		collection[index] = collection[size - 1];
	}
	size--;
}

template<typename T>
size_t Collection<T>::getCount()const
{
	return size;
}

template<typename T>
T& Collection<T>::operator[](size_t index)
{
	if (index > size)
	{
		throw std::invalid_argument("Invalid index");
	}
	return collection[index];
}

template<typename T>
T Collection<T>::operator[](size_t index)const
{
	if (index > size)
	{
		throw std::invalid_argument("Invalid index");
	}
	return collection[index];
}
//template<typename T>
//size_t Collection<T>::getIndex(const T& object)const
//{
//	for (int i = 0; i < size; i++)
//	{
//		if (collection[i] == object)
//		{
//			return i;
//		}
//	}
//
//	throw std::invalid_argument("The object is nit found.");
//}