#pragma once
#include <iostream>
#include <cassert>

template<typename T>
// елемент на стека (стойност - указател към следващия елемент от стека)
struct StackElement
{
	T data;
	StackElement<T>* next;
};

template<typename T>
class LinkedStack
{
private:
	StackElement<T>* topPtr;

	void copyFrom(const LinkedStack&);
	void free();

public:
	LinkedStack();
	LinkedStack(const LinkedStack&);
	LinkedStack& operator=(const LinkedStack&);
	~LinkedStack();

	bool empty() const;
	void push(const T&);
	T pop();
	// извличане на последно добавения елемент без възможност за неговата промяна
	T const& top() const;
	// извличане на последно добавения елемент с възможност за промяна
	T& top();
};

// копиране на стек
// използване на допълнителен стек
template<typename T>
void LinkedStack<T> ::copyFrom(const LinkedStack& other)
{
	topPtr = nullptr;

	StackElement<T>* ptr = other.topPtr;
	// допълнителен стек
	LinkedStack<T> tmp;

	// докато не стигнем последния елемент на стека,
	// добавяме елемента към допълнителния стек
	while (ptr != nullptr)
	{
		tmp.push(ptr->data);
		ptr = ptr->next;
	}

	// връщаме в стека и изпразваме допълнителния стек
	while (!tmp.empty())
	{
		push(tmp.pop());
	}
}

template<typename T>
void LinkedStack<T> ::free()
{
	while (!empty())
	{
		pop();
	}
}

template<typename T>
LinkedStack<T>::LinkedStack()
{
	topPtr = nullptr;
}

template<typename T>
LinkedStack<T> ::LinkedStack(const LinkedStack& other)
{
	copyFrom(other);
}

template<typename T>
LinkedStack<T>& LinkedStack<T> :: operator=(const LinkedStack& other)
{
	if (&other != this)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
LinkedStack<T> :: ~LinkedStack()
{
	free();
}

template<typename T>
bool LinkedStack<T> ::empty() const
{
	return topPtr == nullptr;
}

template<typename T>
void LinkedStack<T> ::push(const T& obj)
{
	// заделяне на памет за нов елемент
	StackElement<T>* newElPtr = new StackElement<T>();
	// даваме стойност на новия елемент
	newElPtr->data = obj;
	// създаваме връзка между новия елемент и предишния в стека
	newElPtr->next = topPtr;
	// пренасочваме върха на стека
	topPtr = newElPtr;
}

template<typename T>
T LinkedStack<T> ::pop()
{
	if (empty())
	{
		std::cerr << "The stack is empty!" << std::endl;
		return T();
	}

	// стойността на елемента, който ще изтрием
	T result = top();

	// насочваме временен указател към върха на стека, който ще бъде изтрит
	StackElement<T>* tempPtr = topPtr;

	// пренасочваме указателя към предходния елемент
	topPtr = topPtr->next;

	// изтриваме указателя, който сочи към стария връх на стека
	delete tempPtr;

	return result;
}

template<typename T>
T const& LinkedStack<T> :: top() const
{
	assert(!empty());
	return topPtr->data;
}

template<typename T>
T& LinkedStack<T> ::top()
{
	assert(!empty());
	return topPtr->data;
}
