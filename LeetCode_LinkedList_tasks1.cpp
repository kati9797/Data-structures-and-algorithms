template<typename T>
struct LinkedListNode
{
    T data;
    LinkedListNode<T>* next;

    LinkedListNode(const T& newData, LinkedListNode<T>* newNext = nullptr) : data{ newData }, next{ newNext } {}
};

template<typename T>
void printList(const LinkedListNode<T>* ll)
{
    const LinkedListNode<T>* iter = ll;
    while (iter)
    {
        std::cout << iter->data << "->";
        iter = iter->next;
    }
    std::cout << "/" << std::endl;
}

template<typename T>
void printCyclicList(const LinkedListNode<T>* ll)
{
    std::cout << ll->data << " ";
    const LinkedListNode<T>* iter = ll->next;
    while (iter != ll)
    {
        std::cout << iter->data << " ";
        iter = iter->next;
    }
}

template<typename T>
void freeList(LinkedListNode<T>* ll)
{
    while (ll)
    {
        LinkedListNode<T>* toDelete = ll;
        ll = ll->next;
        delete toDelete;
    }
}

//------------------------------------------------------

template<typename T>
LinkedListNode<T>* reverse(LinkedListNode<T>* ll)
{
    LinkedListNode<T>* prev = nullptr;
    LinkedListNode<T>* curr = ll;

    while (curr)
    {
        LinkedListNode<T>* temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }

    return prev;
}

template<typename T>
LinkedListNode<T>* reverseKElements(LinkedListNode<T>* ll, int k)
{
    LinkedListNode<T>* prev = nullptr;
    LinkedListNode<T>* curr = ll;
    LinkedListNode<T>* start = ll;

    if (k == 0)
    {
        return curr;
    }

    while (curr)
    {
        --k;
        LinkedListNode<T>* temp = curr->next;
        curr->next = prev;
        prev = curr;
        if (k != 0) 
        {
            curr = temp;
        }
        else
        {
            ll->next = temp;
            return curr;
        }
    }

    return prev;
}

template<typename T>
LinkedListNode<T>* findMiddle(LinkedListNode<T>* ll)
{
    LinkedListNode<T>* slow = ll;
    LinkedListNode<T>* fast = ll;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = (fast->next)->next;
    }

    return slow;
}

template <typename T>
bool isPalindrome(LinkedListNode<T>* ll)
{
    std::stack<T> s;
    LinkedListNode<T>* iter = findMiddle(ll);

    while (iter)
    {
        s.push(iter->data);
        iter = iter->next;
    }

    iter = ll;
    while (!s.empty())
    {
        if (s.top() != iter->data)
            return false;
        s.pop();
        iter = iter->next;
    }

    return true;
}

template<typename T>
LinkedListNode<T>* shuffle(LinkedListNode<T>* ll)
{
    LinkedListNode<T>* middle = findMiddle(ll);
    LinkedListNode<T>* head = reverse(middle);
    LinkedListNode<T>* reversedIter = head;

    LinkedListNode<T>* iter = ll;
    while (iter->next != middle)
    {
        iter = iter->next;
    }
    iter->next = nullptr;
    
    while (reversedIter->next)
    {
        reversedIter = reversedIter->next;
    }
    reversedIter->next = ll;
   
    return head;
}

template<typename T>
bool hasCycle(LinkedListNode<T>* ll)
{
    LinkedListNode<T>* slow = ll;
    LinkedListNode<T>* fast = ll;

    while (fast && fast->next && slow)
    {
        slow = slow->next;
        fast = (fast->next)->next;

        if (fast == slow)
            return true;
    }
    return false;
}

template<typename T>
LinkedListNode<T>* oddEvenLinkedList(LinkedListNode<T>* ll)
{
    LinkedListNode<T>* odd = ll;
    LinkedListNode<T>* even = ll->next;
    LinkedListNode<T>* evenStart = ll->next;

    while(odd->next && even->next)
    {
        odd->next = even->next;
        even->next = (odd->next)->next;
        odd = odd->next;
        even = even->next;
    }
    odd->next = evenStart;

    return ll;
}

template<typename T>
LinkedListNode<T>* insertIntoCyclicSortedList(LinkedListNode<T>* ll, const int& value)
{
    LinkedListNode<T>* iter = ll;

    while (iter->next)
    {
        if (value >= iter->data && value <= (iter->next)->data)
        {
            LinkedListNode<T>* node = new LinkedListNode<int>(value, iter->next);
            iter->next = node;
            return ll;
            break;
        }
        iter = iter->next;
    }

    LinkedListNode<T>* node = new LinkedListNode<int>(value, iter->next);
    iter->next = node;
    return ll;
}

template<typename T>
LinkedListNode<T>* reorder(LinkedListNode<T>* ll)
{
    LinkedListNode<T>* mid = findMiddle(ll);
    LinkedListNode<T>* rev = reverse(mid);
    LinkedListNode<T>* iter = ll;
    if (iter == mid)
    {
        return ll;
    }

    while (iter->next != mid)
    {
        iter = iter->next;
    }
    iter->next = nullptr;

    iter = ll;
    LinkedListNode<T>* back = nullptr;
    while (rev)
    {
        if (iter == nullptr)
        {
            back->next = rev;
            back = rev;
            rev = rev->next;
        }
        else
        {
            if (back != nullptr)
            {
                back->next = iter;
            }
            LinkedListNode<T>* temp = iter->next;
            iter->next = rev;
            iter = temp;
            back = rev;
            rev = rev->next;
        }
    }

    return ll;
}
