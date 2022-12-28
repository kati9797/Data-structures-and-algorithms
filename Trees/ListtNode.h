#include <iostream>

template <typename T>
struct ListNode {
	T data;
	ListNode<T>* next;

	ListNode(const T& d, ListNode<T>* n = nullptr) : data{ d }, next{ n } {}
};

template <typename T>
void freeList(ListNode<T>* head)
{
	while (head != nullptr)
	{
		ListNode<T>* toDelete = head;
		head = head->next;
		delete toDelete;
	}
}
