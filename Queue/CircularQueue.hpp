#pragma once
#include <iostream>
#include <cassert>

const int MAX_CAPACITY = 4;

template<typename T>
class CQueue
{
private:
	T* data;
	int size;
	int capacity;
	int getIndex;
	int putIndex;

	void resize();
	void copyFrom(const CQueue&);
	void free();

public:
	CQueue();
	CQueue(const CQueue&);
	CQueue(CQueue&&);
	CQueue& operator=(const CQueue&);
	CQueue& operator=(CQueue&&);
	~CQueue();

	bool isEmpty() const;
	void enqueue(const T&);
	void dequeue();
	const T& toDequeue();
	const T& peek() const;
};

template<typename T>
void CQueue<T>::resize()
{
	int newCapacity = capacity * 2;
	T* tempData = new T[newCapacity];
	for (int i = 0; i < capacity; i++)
	{
		tempData[i] = peek();
		dequeue();
	}
	size = capacity;
	capacity = newCapacity;
	getIndex = 0;
	putIndex = size;
	delete[] data;
	data = tempData;
}

template<typename T>
void CQueue<T>::copyFrom(const CQueue<T>& other)
{
	data = new T[other.capacity];
	for (int i = other.getIndex; i != other.putIndex; (++i) %= other.capacity)
	{
		data[i] = other.data[i];
	}
	size = other.size;
	capacity = other.capacity;
	getIndex = other.getIndex;
	putIndex = other.putIndex;
}

template<typename T>
void CQueue<T>::free()
{
	delete[] data;
	size = 0;
	capacity = 0;
}

template<typename T>
CQueue<T>::CQueue()
{
	size = 0;
	capacity = MAX_CAPACITY;
	data = new T[capacity];
	getIndex = 0;
	putIndex = 0;
}

template<typename T>
CQueue<T>::CQueue(const CQueue<T>& other)
{
	copyFrom(other);
}

template<typename T>
CQueue<T>::CQueue(CQueue<T>&& other)
{
	size = other.size;
	capacity = other.capacity;
	getIndex = other.getIndex;
	putIndex = other.putIndex;
	data = other.data;
	other.data = nullptr;
}

template<typename T>
CQueue<T>& CQueue<T>::operator=(const CQueue<T>& other)
{
	if (&other != this)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
CQueue<T>& CQueue<T>::operator=(CQueue<T>&& other)
{
	if (&other != this)
	{
		free();
		size = other.size;
		capacity = other.capacity;
		getIndex = other.getIndex;
		putIndex = other.putIndex;
		data = other.data;
		other.data = nullptr;
	}
	return *this;
}

template<typename T>
CQueue<T>::~CQueue()
{
	free();
}

template<typename T>
bool CQueue<T>::isEmpty() const
{
	return size == 0;
}

template<typename T>
void CQueue<T>::enqueue(const T& obj)
{
	if (size == capacity)
		resize();

	data[putIndex] = obj;
	(++putIndex) %= capacity;
	size++;
}

template<typename T>
void CQueue<T>::dequeue()
{
	if (isEmpty())
	{
		std::cerr << "The queue is empty" << std::endl;
	}
	(++getIndex) %= capacity;
	size--;
}

template<typename T>
const T& CQueue<T>::toDequeue()
{
	if (isEmpty())
	{
		std::cerr << "The queue is empty" << std::endl;
	}
	T toDequeue = peek();;
	(++getIndex) %= capacity;
	size--;
	return toDequeue;
}

template<typename T>
const T& CQueue<T>::peek() const
{
	assert(!isEmpty());
	return data[getIndex];
}
