include <iostream>

template<typename T>
struct ListNode
{
    T data;
    ListNode<T>* next;

    ListNode(const T& d, ListNode<T>* n = nullptr) : data{ d }, next { n } {}
};

template<typename T>
void freeList(ListNode<T>* list)
{
    while (list)
    {
        ListNode<T>* toDelete = list;
        list = list->next;
        delete toDelete;
    }
}

template<typename T>
void printList(const ListNode<T>* list)
{
    const ListNode<T>* iter = list;
    while (iter)
    {
        std::cout << iter->data << "->";
        iter = iter->next;
    }
    std::cout << "/" << std::endl;
}

template<typename T>
ListNode<T>* removeElements(ListNode<T>* head, int val)
{
    ListNode<T>* iter = head;

    if (iter == nullptr || (iter->next == nullptr && iter->data != val))
    {
        return head;
    }
    else if (iter->next == nullptr && iter->data == val)
    {
        return nullptr;
    }
    else
    {
        if (head->data == val)
        {
            while (iter->data == val)
            {
                iter = iter->next;
            }
            head = iter;
        }

        while (iter && iter->next)
        {
            if ((iter->next)->data != val)
            {
                iter = iter->next;
            }
            else
            {
                ListNode<T>* curr = iter;
                while (iter->next && (iter->next)->data == val)
                {
                    iter = iter->next;
                }
                iter = iter->next;
                curr->next = iter;
            }
        }
    }
    return head;
}

template<typename T>
ListNode<T>* findMiddle(ListNode<T>* ll)
{
    ListNode<T>* slow = ll;
    ListNode<T>* fast = ll;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = (fast->next)->next;
    }

    return slow;
}

template<typename T>
int pairSum(ListNode<T>* head)
{
    ListNode<T>* mid = findMiddle(head);
    ListNode<T>* prev = mid;
    ListNode<T>* back = prev->next;
    mid->next = nullptr;

    while (back)
    {
        ListNode<T>* temp = back->next;
        back->next = prev;
        prev = back;
        back = temp;
    }

    int maxSum = 0;
    back = prev;
    while (back)
    {
        int currSum = head->data + back->data;
        if (currSum > maxSum)
        {
            maxSum = currSum;
        }
        head = head->next;
        back = back->next;
    }

    return maxSum;
}

int main()
{
    using Node = ListNode<int>;

    Node* list = new Node(1, new Node(2, new Node(10, new Node(6, new Node(60, new Node(42))))));
   // Node* list2 = new Node(1);
    //printList(removeElements(list, 8));
    //printList(removeElements(list2, 1));
    std::cout << pairSum(list);
    freeList(list);
    //freeList(list2);
}
