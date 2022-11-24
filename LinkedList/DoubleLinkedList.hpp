#include <iostream>
#pragma once

template<typename T>
struct Node
{
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(const T& d, Node<T>* n = nullptr, Node<T>* p = nullptr) : data{ d }, next{ n }, prev{ p } {}
};

template<typename T>
class DoubleLinkedList
{
private:
  
    Node<T>* head;
    Node<T>* tail;

    void copyFrom(const DoubleLinkedList<T>&);
    void free();

    class Iterator 
    {
    private:
      
        Node<T>* iter;
        Iterator(Node<T>* it = nullptr) : iter{ it } {}

    public:
      
        friend class DoubleLinkedList<T>;

        Iterator& operator++()
        {
            if (iter == nullptr)
                return *this;
            iter = iter->next;
            return *this;
        }

        Iterator operator++(int)
        {
            if (iter == nullptr)
                return *this;
            Node<T>* toReturn = iter;
            iter = iter->next;
            return toReturn;
        }

        Iterator& operator--()
        {
            if (iter == nullptr)
                return *this;
            iter = iter->prev;
            return iter;
        }

        Iterator operator--(int)
        {
            if (iter == nullptr)
                return *this;
            Node<T>* toReturn = iter;
            iter = iter->prev;
            return toReturn;
        }

        const T& operator*()
        {
            if (iter == nullptr)
            {
                throw std::exception();
            }
            return iter->data;
        }

        bool operator==(const Iterator& other) const
        {
            return (*this == other.iter);
        }

        bool operator!=(const Iterator& other) const
        {
            return !(&this == other);
        }
    };

public:

    DoubleLinkedList();
    DoubleLinkedList(const DoubleLinkedList<T>&);
    DoubleLinkedList<T>& operator= (const DoubleLinkedList<T>&);
    ~DoubleLinkedList();

    void pushFront(const T& data);
    void pushBack(const T& data);

    void popFront();
    void popBack();

    const T& front() const;
    const T& back() const;

    Iterator begin();
    Iterator end();

    bool empty() const;
};

template<typename T>
void DoubleLinkedList<T>::copyFrom(const DoubleLinkedList<T>& other)
{
    Node<T>* iter = other.head;

    while (iter)
    {
        pushBack(iter->data);
        iter = iter->next;
    }
}

template<typename T>
void DoubleLinkedList<T>::free()
{
    while (!empty())
    {
        popFront();
    }
}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList()
{
    head = nullptr;
    tail = nullptr;
}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& other)
{
    copyFrom(other);
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList<T>& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    free();
}

template<typename T>
void DoubleLinkedList<T>::pushFront(const T& data)
{
    Node<T>* elem = new Node<T>(data);
    if (empty())
    {
        head = tail = elem;
    }
    else
    {
        head->prev = elem;
        elem->next = head;
        head = elem;
    }
}

template<typename T>
void DoubleLinkedList<T>::pushBack(const T& data)
{
    Node<T>* elem = new Node<T>(data);
    if (empty())
    {
        head = tail = elem;
    }
    else
    {
        tail->next = elem;
        elem->prev = tail;
        tail = elem;
    }
}

template<typename T>
void DoubleLinkedList<T>::popFront()
{
    if (empty())
    {
        std::cerr << "Empty List!" << std::endl;
    }
    else if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        Node<T>* toDelete = head;
        head = head->next;
        head->prev = nullptr;
        delete toDelete;
    }
}

template<typename T>
void DoubleLinkedList<T>::popBack()
{
    if (empty())
    {
        std::cerr << "Empty List!" << std::endl;
    }
    else if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        Node<T>* toDelete = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete toDelete;
    }
}

template<typename T>
const T& DoubleLinkedList<T>::front() const
{
    return head->data;
}

template<typename T>
const T& DoubleLinkedList<T>::back() const
{
    return tail->data;
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::begin()
{
    return Iterator(head);
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::end()
{
    return Iterator(nullptr);
}

template<typename T>
bool DoubleLinkedList<T>::empty() const
{
    return (head == nullptr && tail == nullptr);
}
