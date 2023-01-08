#pragma once
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
	void popBack();

	const T& front() const;
	const T& back() const;

	template<typename U>
	friend SinglyLinkedList<U> concat(SinglyLinkedList<U>&, SinglyLinkedList<U>&);

	void print() const;

	class Iterator
	{
	private:

		SinglyLinkedListElement<T>* iter;

		friend class SinglyLinkedList;

	public:

		Iterator(SinglyLinkedListElement<T>* arg = nullptr) : iter{ arg } {}

		Iterator& operator++()
		{
			if (iter == nullptr)
				return *this;
			iter = iter->next;
			return (*this);
		}

		Iterator operator++(int)
		{
			Iterator toReturn = *this;
			++(*this);
			return toReturn;
		}

		// сравняват се адреси
		bool operator==(const Iterator& other) const
		{
			return other.iter == iter;
		}

		bool operator!=(const Iterator& other) const
		{
			return !(*this == other);
		}

		T& operator*() const
		{
			return iter->data;
		}
	};

	Iterator begin() const
	{
		return Iterator(head);
	}

	Iterator end() const
	{
		return Iterator();
	}

	Iterator insertAfter(const Iterator&, const T&);
	Iterator remove(const Iterator&);
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
	return (head == nullptr && tail == nullptr);
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

template<typename T>
void SinglyLinkedList<T>::popBack()
{
	if (isEmpty())
	{
		std::cerr << "Empty list!" << std::endl;
	}
	else if (head == tail)
	{
		delete tail;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		SinglyLinkedListElement<T>* iter = head;
		while (iter->next != tail)
		{
			iter = iter->next;
		}
		delete tail;
		tail = iter;
		tail->next = nullptr;
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
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::insertAfter(const Iterator& it, const T& d)
{
	if (!it.iter || !it.iter->next)
	{
		pushBack(d);
		return end();
	}

	SinglyLinkedListElement<T>* newElem = new SinglyLinkedListElement<T>(d);
	newElem->next = it.iter->next;
	it.iter->next = newElem;
	return typename SinglyLinkedList<T>::Iterator(newElem);
}

template<typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::remove(const Iterator& it)
{
	if (!it.iter || !it.iter->next)
	{
		popBack();
		return end();
	}
	else if (it.iter == head)
	{
		popFront();
		return begin();
	}

	SinglyLinkedListElement<T>* toDelete = it.iter;
	SinglyLinkedListElement<T>* temp = head;
	while (temp && temp->next != toDelete)
	{
		temp = temp->next;
	}
	SinglyLinkedListElement<T>* next = toDelete->next;
	temp->next = next;
	delete toDelete;
	return typename SinglyLinkedList<T>::Iterator(next);
}

template<typename T>
SinglyLinkedList<T> concat(SinglyLinkedList<T>& lhs, SinglyLinkedList<T>& rhs)
{
	if (rhs.isEmpty())
	{
		return lhs;
	}
	else if (lhs.isEmpty())
	{
		return rhs;
	}

	SinglyLinkedListElement<T>* temp = lhs.head;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = rhs.head;
	return lhs;
}
