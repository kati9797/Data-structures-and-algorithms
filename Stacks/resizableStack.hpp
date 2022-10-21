#include <iostream>

template<typename T>
class RStack {
private:
	T* arr;
	int topIndex;
	int capacity;

	void resize();
	bool isFull() const;
	void copyFrom(const RStack&);
	void free();

public:
	RStack();
	RStack(const RStack&);
	RStack& operator=(const RStack&);
	~RStack();

	bool empty() const;
	void push(const T&);
	T pop();
	T top() const;
};

template<typename T>
void RStack<T> ::resize()
{
	T* resizedArr = new T[capacity *= 2];
	for (int i = 0; i <= topIndex; i++)
	{
		resizedArr[i] = arr[i];
	}
	free();
	arr = resizedArr;
}

template<typename T>
bool RStack<T> ::isFull() const
{
	return topIndex == capacity - 1;
}

template<typename T>
void RStack<T> ::copyFrom(const RStack& other)
{
	topIndex = other.topIndex;
	capacity = other.capacity;
	arr = new T[capacity];
	for (int i = 0; i < capacity; i++)
	{
		arr[i] = other.arr[i];
	}
}

template<typename T>
void RStack<T> ::free()
{
	delete[] arr;
}

template<typename T>
RStack<T>::RStack()
{
	topIndex = -1;
	capacity = 4;
	arr = new T[capacity];
}

template<typename T>
RStack<T> ::RStack(const RStack& other)
{
	copyFrom(other);
}

template<typename T>
RStack<T>& RStack<T> :: operator=(const RStack& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
RStack<T> :: ~RStack()
{
	free();
}

template<typename T>
bool RStack<T> :: empty() const
{
	return topIndex == -1;
}

template<typename T>
void RStack<T> ::push(const T& obj)
{
	if (isFull())
	{
		resize();
	}
	arr[++topIndex] = obj;
}

template<typename T>
T RStack<T> ::pop()
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

template<typename T>
T RStack<T> ::top() const
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
