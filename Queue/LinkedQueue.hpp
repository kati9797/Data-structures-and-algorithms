#pragma once
#include<iostream>
#include<cassert>

template<typename T>
struct QueueElement
{
	T data;
	QueueElement<T>* next;
};

template<typename T>
class LinkedQueue
{
private:
	QueueElement<T>* head;
	QueueElement<T>* tail;

	void copyFrom(const LinkedQueue&);
	void free();

public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue&);
	LinkedQueue(LinkedQueue&&);
	LinkedQueue& operator=(const LinkedQueue&);
	LinkedQueue& operator=(LinkedQueue&&);
	~LinkedQueue();

	bool isEmpty() const;
	void enqueue(const T&);
	void dequeue();
	const T& toDequeue();
	const T& peek() const;
};

template<typename T>
void LinkedQueue<T>::free()
{
	while (!isEmpty())
	{
		dequeue();
	}
}

template<typename T>
void LinkedQueue<T>::copyFrom(const LinkedQueue<T>& other)
{
	head = nullptr;
	tail = nullptr;

	QueueElement<T>* ptr = other.head;
	while (ptr != nullptr)
	{
		enqueue(ptr->data);
		ptr = ptr->next;
	}
}

template<typename T>
LinkedQueue<T>::LinkedQueue()
{
	head = nullptr;
	tail = nullptr;
}

template<typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other)
{
	copyFrom(other);
}

template<typename T>
LinkedQueue<T>:: LinkedQueue(LinkedQueue<T>&& other)
{
	head = other.head;
	tail = other.tail;
	other.head = nullptr;
	other.tail = nullptr;
}

template<typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& other)
{
	if (&other != this)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(LinkedQueue<T>&& other)
{
	if (&other != this)
	{
		free();
		head = other.head;
		tail = other.tail;
		other.head = nullptr;
		other.tail = nullptr;
	}
	return *this;
}

template<typename T>
LinkedQueue<T>::~LinkedQueue()
{
	free();
}

template<typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return head == nullptr && tail == nullptr;
}

template<typename T>
void LinkedQueue<T>::enqueue(const T& obj)
{
	QueueElement<T>* newElemPtr = new QueueElement<T>();
	if (isEmpty()) 
	{
		newElemPtr->data = obj;
		head = newElemPtr;
		tail = newElemPtr;
	}
	else
	{
		newElemPtr->data = obj;
		tail->next = newElemPtr;
		tail = newElemPtr;
	}
}

template<typename T>
void LinkedQueue<T>::dequeue()
{
	if (isEmpty())
	{
		std::cerr << "The queue is empty!" << std::endl;
	}
	else if (head == tail)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		QueueElement<T>* tempPtr = head;
		head = head->next;
		delete tempPtr;
	}
}

template<typename T>
const T& LinkedQueue<T>::toDequeue()
{
	if (isEmpty())
	{
		std::cerr << "The queue is empty!" << std::endl;
	}
	else if (head == tail)
	{
		T result = head->data;
		delete head;
		head = nullptr;
		tail = nullptr;
		return result;
	}
	else
	{
		QueueElement<T>* tempPtr = head;
		T result = head->data;
		head = head->next;
		delete tempPtr;
		return result;
	}
}

template<typename T>
const T& LinkedQueue<T>::peek() const
{
	assert(!isEmpty());
	return head->data;
}
