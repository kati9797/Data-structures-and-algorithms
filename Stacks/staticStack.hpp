#pragma once
#include <iostream>
#include <cassert>

const int MAX_SIZE = 24;

template<typename T>
class Stack{
private:
	T arr[MAX_SIZE];
	int topIndex;

	bool isFull() const;

public:
	Stack();
  
	void push(const T&);
	T pop();
	T top() const;
	bool empty() const;
};

template <typename T>
bool Stack<T>::isFull() const
{
	return topIndex == MAX_SIZE - 1;
}

template <typename T>
Stack<T>::Stack() : topIndex(-1) {}

template <typename T>
void Stack<T>::push(const T& obj)
{
	if (isFull())
	{
		std::cerr << "The stack is full" << std::endl;
	}
	else
	{
		arr[++topIndex] = obj;
	}
}

template <typename T>
T Stack<T>::top() const
{
	if (empty())
	{
		std::cerr << "The stack is empty!" << std::endl;
		return T();
	}
	else
	{
		return arr[topIndex];
	}
}


template <typename T>
T Stack<T>::pop()
{
	if (empty())
	{
		std::cerr << "The stack is empty!" << std::endl;
		return T();
	}
	else
	{
		return arr[topIndex--];
	}
}

template <typename T>
bool Stack<T>::empty() const
{
	return topIndex == -1;
}
