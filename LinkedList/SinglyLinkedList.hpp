#include <iostream>

template<typename T>
struct SinglyLinkedListElement
{
	T data;
	SinglyLinkedListElement<T>* next;

	SinglyLinkedListElement(const T& newData)
	{
		data = newData;
		next = nullptr;
	}
};

template<typename T>
class SinglyLinkedList
{
private:
	using SLE = SinglyLinkedListElement<T>;

	SLE* head;
	SLE* tail;

	void copyFrom(const SinglyLinkedList<T>&);
	void free();

public:
	SinglyLinkedList();
	SinglyLinkedList(const SinglyLinkedList<T>&);
	SinglyLinkedList& operator=(const SinglyLinkedList<T>&);
	~SinglyLinkedList();

	bool isEmpty() const;
	void pushFront(const T&);
	void pushBack(const T&);
	void popFront();

	const T& front() const;
	const T& back() const;
	SLE* getHead() const;
	SLE* getTail() const;

	template<typename U>
	friend SinglyLinkedList<U> concat(SinglyLinkedList<U>&, SinglyLinkedList<U>&);

	void print() const;
};

template<typename T>
void SinglyLinkedList<T>::free()
{
	while (head != nullptr)
	{
		popFront();
	}
	head = tail = nullptr;
}

template<typename T>
void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList<T>& other)
{
	if (other.isEmpty())
	{
		head = nullptr;
		tail = nullptr;
	}

	SLE* tempPtr = other.head;
	while (tempPtr != nullptr)
	{
		pushBack(tempPtr->data);
		tempPtr = tempPtr->next;
	}
}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList()
{
	head = nullptr;
	tail = nullptr;
}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other)
{
	copyFrom(other);
}

template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other)
{
	if (&other != this)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
	free();
}

template<typename T>
bool SinglyLinkedList<T>::isEmpty() const
{
	return head == nullptr && tail == nullptr;
}

template<typename T>
void SinglyLinkedList<T>::pushFront(const T& obj)
{
	SLE* temp = new SinglyLinkedListElement<T>(obj);

	if (isEmpty())
	{
		head = tail = temp;
	}
	else
	{
		temp->next = head;
		head = temp;
	}
}

template<typename T>
void SinglyLinkedList<T>::pushBack(const T& obj)
{
	SLE* temp = new SinglyLinkedListElement<T>(obj);
	if (isEmpty())
	{
		head = tail = temp;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}
}

template<typename T>
void SinglyLinkedList<T>::popFront()
{
	if (isEmpty())
	{
		std::cerr << "Empty list!" << std::endl;
	}
	else if (head == tail)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		SLE* toDelete = head;
		head = head->next;
		delete toDelete;
	}
}

template <typename T>
const T& SinglyLinkedList<T>::front() const
{
	if (isEmpty())
	{
		throw std::length_error("Empty list!");
	}
	
	return head->data;
}

template <typename T>
const T& SinglyLinkedList<T>::back() const
{
	if (isEmpty())
	{
		throw std::length_error("Empty list!");
	}

	return tail->data;
}

template <typename T>
void SinglyLinkedList<T>::print() const
{
	SLE* ptr = head;
	while (ptr != nullptr)
	{
		std::cout << ptr->data << " -> ";
		ptr = ptr->next;
	}
	std::cout << "/" << std::endl;
}

template<typename T>
SinglyLinkedList<T> concat(SinglyLinkedList<T>& lhs, SinglyLinkedList<T>& rhs)
{
	SinglyLinkedList<T> result;

	if (lhs.head == nullptr)
	{
		result.head = rhs.head;
		result.tail = rhs.tail;
	}
	else if (rhs.head == nullptr)
	{
		result.head = lhs.head;
		result.tail = lhs.tail;
	}
	else
	{
		result.head = lhs.head;
		lhs.tail->next = rhs.head;
		result.tail = rhs.tail;
	}

	rhs.head = rhs.tail = lhs.head = lhs.tail = nullptr;
	return result;
}

template<typename T>
SinglyLinkedListElement<T>* SinglyLinkedList<T>::getHead() const
{
	return head;
}

template<typename T>
SinglyLinkedListElement<T>* SinglyLinkedList<T>::getTail() const
{
	return tail;
}
