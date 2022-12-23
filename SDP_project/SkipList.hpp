#include <iostream>
#include <list>

template<typename T>
struct SkipListNode
{
	T data;
	SkipListNode<T>* next;
	SkipListNode<T>* skip;

	SkipListNode(const T& d, SkipListNode<T>* n = nullptr, SkipListNode<T>* s = nullptr) : data{ d }, next{ n }, skip{ s } {}
};

template<typename T>
class SkipList
{
private:

	using SLN = SkipListNode<T>;

	SLN* head;
	SLN* tail;

	void copyFrom(const SkipList<T>&);
	void free();

public:

	class Iterator {
	private:
		SLN* iter;

		Iterator(SLN* node) : iter{ node } {}
	public:

		// ++it
		Iterator& operator++() {
			if (iter == nullptr)
				return *this;
			iter = iter->next;
			return *this;
		}

		// it++
		Iterator operator++(int) {
			Iterator temp = *this;
			++(*this);
			return temp;
		}

		// !it
		bool operator!() const
		{
			return iter->skip != nullptr;
		}

		// *it
		T& operator*() {
			return iter->data;
		}

		// &it
		T& operator&()
		{
			return (iter->skip->data);
		}
		
		// == 
		bool operator==(const Iterator& other) const {
			return other.iter == iter;
		}

		// !=
		bool operator!=(const Iterator& other) const {
			return !(*this == other);
		}

		friend class SkipList;
	};

	SkipList();
	SkipList(const SkipList<T>&);
	SkipList<T>& operator=(const SkipList<T>&);
	~SkipList();

	Iterator begin()
	{
		return Iterator(head);
	}

	Iterator end()
	{
		return Iterator(nullptr);
	}

	bool isEmpty() const;
	void pushBack(const T&); // създава едносвързан списък
	void popFront();
	void skip(const T&, const T&); // skip from - to
	
	void printDirect() const;
	void printSkip() const;
};

template<typename T>
void SkipList<T>::copyFrom(const SkipList<T>& other)
{
	head = nullptr;
	tail = nullptr;

	SLN* iter = other.head;
	while (iter != nullptr)
	{
		pushBack(iter->data);
		iter = iter->next;
	}

	iter = other.head;
	SLN* iterCopySkipList = head;
	while (iter != nullptr)
	{
		if (iter->skip != nullptr)
		{
			iterCopySkipList->skip = iter->skip;
		}
		iter = iter->next;
		iterCopySkipList = iter->next;
	}
}

template<typename T>
void SkipList<T>::free()
{
	while (head != nullptr)
	{
		popFront();
	}

	head = tail = nullptr;
}

template<typename T>
SkipList<T>::SkipList()
{
	head = nullptr;
	tail = nullptr;
}

template<typename T>
SkipList<T>::SkipList(const SkipList<T>& other) 
{
	copyFrom(other);
}

template<typename T>
SkipList<T>& SkipList<T>::operator=(const SkipList<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
SkipList<T>::~SkipList()
{
	free();
}

template<typename T>
bool SkipList<T>::isEmpty() const
{
	return head == nullptr && tail == nullptr;
}

template<typename T>
void SkipList<T>::pushBack(const T& d)
{
	SLN* temp = new SkipListNode<T>(d);
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
inline void SkipList<T>::popFront()
{
	if (isEmpty())
	{
		std::cerr << "Empty list!" << std::endl;
	}
	else if (head == tail)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		SLN* toDelete = head;
		head = head->next;
		delete toDelete;
	}
}

template<typename T>
void SkipList<T>::skip(const T& from, const T& to)
{
	SLN* fromIter = head;
	while (fromIter->data != from)
	{
		fromIter = fromIter->next;
	}

	SLN* toIter = fromIter;
	while (toIter->data != to)
	{
		toIter = toIter->next;
	}

	fromIter->skip = toIter;
}

template<typename T>
void SkipList<T>::printDirect() const
{
	SLN* iter = head;
	while (iter != nullptr)
	{
		std::cout << iter->data << "->";
		iter = iter->next;
	}
	std::cout << "/" << std::endl;
}

template<typename T>
void SkipList<T>::printSkip() const
{
	SLN* iter = head;
	while (iter != nullptr)
	{
		if (iter->skip != nullptr)
		{
			std::cout << iter->data << "->" << iter->skip->data << std::endl;
			iter = iter->next;
		}
		else
		{
			iter = iter->next;
		}
	}
}

template<typename T>
std::list<T> findBestWay(SkipList<T>& sl, std::list<T>& list)
{
	typename SkipList<T>::Iterator skipIter = sl.begin();
	typename std::list<T>::iterator it = list.begin();

	std::list<T> toReturn;

	while (it != list.end())
	{
		if (*skipIter == *it)
		{
			toReturn.push_back(*skipIter);
			it++;

			if (!skipIter && &skipIter == *it)
			{
				while (*skipIter != *it)
				{
					skipIter++;
				}
			}
			else if (!skipIter && &skipIter != *it)
			{
				bool foundNext = false;
				typename SkipList<T>::Iterator skip = skipIter;
				while (*skip != &skipIter)
				{
					if (*skip == *it)
						foundNext = true;
					skip++;
				}

				if (foundNext == true)
					skipIter++;
				else
					skipIter = skip;
			}
			else
			{
				skipIter++;
			}
		}
		else
		{
			toReturn.push_back(*skipIter);
			if (!skipIter && &skipIter == *it)
			{
				while (*skipIter != *it)
				{
					skipIter++;
				}
			}
			else if (!skipIter && &skipIter != *it)
			{
				bool foundNext = false;
				typename SkipList<T>::Iterator skip = skipIter;
				while (*skip != &skipIter)
				{
					if (*skip == *it)
						foundNext = true;
					skip++;
				}

				if (foundNext == true)
					skipIter++;
				else
					skipIter = skip;
			}
			else
			{
				skipIter++;
			}
		}
	}

	while (skipIter != sl.end())
	{
		if (!skipIter)
		{
			toReturn.push_back(*skipIter);
			while (*skipIter != &skipIter)
			{
				skipIter++;
			}
		}
		else
		{
			toReturn.push_back(*skipIter);
			skipIter++;
		}
	}

	return toReturn;
}
