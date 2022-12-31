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
			return iter != nullptr;
		}

		// *it
		T& operator*() {
			return iter->data;
		}

		// &it
		Iterator operator&()
		{
			return Iterator(iter->skip);
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
void searchBetterSkip(bool& foundNext, bool& foundSkip, typename SkipList<T>::Iterator& skipIter, T nextInList)
{
	typename SkipList<T>::Iterator skip = &skipIter; // скип поле на текуща гара
	typename SkipList<T>::Iterator iter = skipIter; // итератор, чрез който ще обхождаме
	iter++;

	while (*iter != *skip) // обхождаме междинните гари
	{

		if (*iter == nextInList) // сред междинните гари е намерена следващата в нашия списък (ако направим скип, ще я пропуснем)
		{
			foundNext = true;
			break;
		}

		typename SkipList<T>::Iterator skipFieldIter = &iter;

		if (!skipFieldIter && *skipFieldIter == nextInList) // намерена е гара, чието скип поле води директно до следващата желана гара (този път може да е по-оптимален, но може и да не е)
		{
			foundSkip = true;
			typename SkipList<T>::Iterator copySkipIter = skipIter;
			typename SkipList<T>::Iterator copyIter = iter;

			// броячи за това колко гари се пропускат чрез скип полетата
			int cntSkipIter = 0;
			int cntIter = 0;

			while (copySkipIter != skip)
			{
				copySkipIter++;
				++cntSkipIter;
			}

			while (*copyIter != nextInList)
			{
				copyIter++;
				++cntIter;
			}

			// предвижваме се чрез итератора, който пропуска повече гари
			if (cntSkipIter >= cntIter)
			{
				skipIter = skip;
			}
			else
			{
				skipIter++;
			}
			break;
		}
		iter++;
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
		// гарата, на която се намираме, е гара, която трябва да бъде посетена
		if (*skipIter == *it)
		{
			toReturn.push_back(*skipIter);
			it++;
		} // гара, която не е в списъка, но задължително минаваме през нея
		else
		{
			toReturn.push_back(*skipIter);
		}

		typename SkipList<T>::Iterator skip = &skipIter; // скип поле на текуща гара
		if (!skip && *skip == *it) // ако скип полето сочи към следващата гара, която трябва да посетим -> се предвижваме чрез него
		{
			skipIter = skip;
		}
		else if (!skip && *skip != *it) // ако има скип поле (различно от nullptr), но води до друга гара, която не е следваща в списъка ни 
		{
			bool foundNext = false; // сред междинните гари е намерена е следващата в списъка за посещение
			bool foundSkip = false; // сред междинните гари е намерена такава, от която можем да стигнем до следващата в списъка, чрез скип полето й
			searchBetterSkip(foundNext, foundSkip, skipIter, *it);

			if (foundNext == true)
				skipIter++;
			else if (foundSkip == false)
				skipIter = skip;
		}
		else // няма скип поле
		{
			skipIter++;
		}
	}

	typename SkipList<T>::Iterator end = skipIter;
	typename SkipList<T>::Iterator last = end;
	end++;
	while (end != sl.end())
	{
		last = end;
		end++;
	}

	
	while (skipIter != sl.end())
	{
		typename SkipList<T>::Iterator skip = &skipIter;

		if (!skip && *skip == *last) // намираме стойността на последния елемент от списъка
		{
			toReturn.push_back(*skipIter);
			skipIter = skip;
			break;
		}
		else if (!skip && *skip != *last)
		{
			bool foundNext = false;
			bool foundSkip = false; // сред междинните гари е намерена такава, от която можем да стигнем до следващата в списъка, чрез скип полето й
			searchBetterSkip(foundNext, foundSkip, skipIter, *last);

			if (foundSkip == false)
				skipIter = skip;
		}
		else
		{
			toReturn.push_back(*skipIter);
			skipIter++;
		}
	}

	return toReturn;
}
