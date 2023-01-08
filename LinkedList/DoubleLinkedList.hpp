#pragma once 
#include <iostream>

template<typename T>
class DLL
{
private:

	struct Node
	{
		T data;
		Node* next;
		Node* prev;

		Node(const T& d, Node* n = nullptr, Node* p = nullptr) : data{ d }, next{ n }, prev{ p } {}
	};

	Node* head;
	Node* tail;

	void copyFrom(const DLL<T>&);
	void free();

public:

	DLL();
	DLL(const DLL<T>&);
	DLL<T>& operator=(const DLL<T>&);
	~DLL();

	void pushFront(const T&);
	void pushBack(const T&);

	void popFront();
	void popBack();

	const T& front() const;
	const T& back() const;

	bool empty() const;

	void print() const;

	class Iterator;
	Iterator insertAfter(const Iterator&, const T&); // връщаме итератор към добавения елемент
	Iterator remove(const Iterator&); // връщаме итератор към елемента след изтрития 

	class Iterator
	{
	private:

		Node* iter;
		friend class DLL;

	public:
		Iterator(Node* it = nullptr) : iter{ it } {}

		bool isValid() const
		{
			return iter != nullptr;
		}

		// ++it
		Iterator& operator++()
		{
			if (!iter)
				return (*this);

			iter = iter->next;
			return (*this);
		}

		// it++
		Iterator operator++(int)
		{
			if (!iter)
				return (*this);

			Iterator toReturn = (*this);
			++(*this);
			return toReturn;
		}

		// --it
		Iterator& operator--()
		{
			if (!iter)
				return (*this);

			iter = iter->prev;
			return(*this);
		}

		// it--
		Iterator operator--(int)
		{
			if (!iter)
				return (*this);

			Iterator toReturn = (*this);
			--(*this);
			return toReturn;
		}

		T& operator*()
		{
			return iter->data;
		}

		bool operator==(const Iterator& it)
		{
			return iter = it.iter;
		}

		bool operator!=(const Iterator& it)
		{
			return !((*this) == it);
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
};

template<typename T>
void DLL<T>::copyFrom(const DLL<T>& other)
{
	head = nullptr;
	tail = nullptr;

	Node* iter = other.head;
	while (iter)
	{
		pushBack(iter->data);
		iter = iter->next;
	}
}

template<typename T>
void DLL<T>::free()
{
	while (!empty())
	{
		popBack();
	}
}

template<typename T>
DLL<T>::DLL()
{
	head = nullptr;
	tail = nullptr;
}

template<typename T>
DLL<T>::DLL(const DLL<T>& other)
{
	copyFrom(other);
}

template<typename T>
DLL<T>& DLL<T>::operator=(const DLL<T>& other)
{
	if (this != (&other))
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
DLL<T>::~DLL()
{
	free();
}

template<typename T>
void DLL<T>::pushFront(const T& d)
{
	Node* newElem = new Node(d);

	if (empty())
	{
		head = newElem;
		tail = newElem;
	}
	else
	{
		newElem->next = head;
		head->prev = newElem;
		head = newElem;
	}
}

template<typename T>
void DLL<T>::pushBack(const T& d)
{
	Node* newElem = new Node(d);

	if (empty())
	{
		head = newElem;
		tail = newElem;
	}
	else
	{
		newElem->prev = tail;
		tail->next = newElem;
		tail = newElem;
	}
}

template<typename T>
void DLL<T>::popFront()
{
	if (empty())
	{
		throw std::runtime_error("Empty list!");
	}

	if (head == tail)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else 
	{
		Node* toDelete = head;
		head = head->next;
		head->prev = nullptr;
		delete toDelete;
	}
}

template<typename T>
void DLL<T>::popBack()
{
	if (empty())
	{
		throw std::runtime_error("Empty list!");
	}

	if (head == tail)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		Node* toDelete = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete toDelete;
	}
}

template<typename T>
const T& DLL<T>::front() const
{
	return head->data;
}

template<typename T>
const T& DLL<T>::back() const
{
	return tail->data;
}

template<typename T>
bool DLL<T>::empty() const
{
	return head == nullptr && tail == nullptr;
}

template<typename T>
void DLL<T>::print() const
{
	Node* iter = head;
	while (iter)
	{
		std::cout << iter->data << " ";
		iter = iter->next;
	}
	std::cout<<std::endl;
}

template<typename T>
typename DLL<T>::Iterator DLL<T>::insertAfter(const Iterator& it, const T& d)
{
	if ( !it.iter || it.iter == tail)
	{
		pushBack(d);
		return end();
	}

	Node* newElem = new Node(d);
	newElem->next = it.iter->next;
	newElem->next = it.iter;
	it.iter->next = newElem;
	return typename DLL<T>::Iterator(newElem);
}

template<typename T>
typename DLL<T>::Iterator DLL<T>::remove(const Iterator& it)
{
	if (it.iter == head)
	{
		popFront();
		return begin();
	}
	else if (!it.iter || !it.iter->next)
	{
		popBack();
		return end();
	}

	Node* toDelete = it.iter;
	Node* next = toDelete->next;
	it.iter->prev->next = next;
	next->prev = it.iter->prev;
	delete toDelete;
	return typename DLL<T>::Iterator(next);
}
