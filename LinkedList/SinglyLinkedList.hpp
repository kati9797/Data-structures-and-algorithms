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

	class Iterator
	{
	private:
		SinglyLinkedListElement<T>* iter;
		Iterator(SinglyLinkedListElement<T>* arg) : iter{ arg } {}

	public:

		friend class SinglyLinkedList;

		Iterator& operator++()
		{
			if (iter == nullptr)
				return *this;
			iter = iter.next;
			return (*this);
		}

		Iterator operator++(int)
		{
			Iterator toReturn = *this;
			(*this).operator++;
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

		T& operator*() 
		{
			return iter->data;
		}
	};

	class ConstIterator
	{
	private:
		const SinglyLinkedListElement<T>* constIter;
		ConstIterator(SinglyLinkedListElement<T>* arg) : constIter{ arg } {}

	private:

		friend class SinglyLinkedList;

		ConstIterator& operator++()
		{
			if (constIter == nullptr)
				return *this;
			constIter = constIter = constIter->next;
			return *this;
		}

		ConstIterator operator++(int)
		{
			ConstIterator toReturn = *this;
			++(*this);
			return toReturn;
		}

		bool operator==(const ConstIterator& other) const
		{
			return other.constIter = constIter;
		}

		bool operator!=(const ConstIterator& other) const
		{
			return !(*this == other);
		}

		const T& operator*() const
		{
			return constIter->data;
		}
	};

	Iterator begin()
	{
		return Iterator(head);
	}

	Iterator end()
	{
		return Iterator(nullptr);
	}

	ConstIterator begin() const
	{
		return Iterator(head);
	}

	ConstIterator end() const
	{
		return Iterator(nullptr);
	}

	ConstIterator cbegin()
	{
		return ConstIterator(head);
	}

	ConstIterator cend()
	{
		return ConstIterator(nullptr);
	}

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
