#include <iostream>
#include<stack>
#include<queue>

using sLinkedList = LinkedListNode<std::stack<int>>;
using qLinkedList = LinkedListNode<std::queue<int>>;

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
void freeList(LinkedListNode<T>* ll)
{
    while (ll)
    {
        LinkedListNode<T>* toDelete = ll;
        ll = ll->next;
        delete toDelete;
    }
}

void printStack(std::stack<int> st)
{
    std::cout << '[';
    while (!st.empty())
    {
        std::cout << st.top() << ' ';
        st.pop();
    }
    std::cout << ']'<<std::endl;
}

void printSList(const sLinkedList* ll)
{
    const sLinkedList* iter = ll;
    while (iter)
    {
        printStack(iter->data);
        iter = iter->next;
    }
}

void freeSList(sLinkedList* ll)
{
    while (ll != nullptr)
    {
        sLinkedList* toDelete = ll;
        ll = ll->next;
        delete toDelete;
    }
}

void printQueue(std::queue<int> q)
{
    std::cout << '[';
    while (!q.empty())
    {
        std::cout << q.front() << ' ';
        q.pop();
    }
    std::cout << ']' << std::endl;
}

void printSList(const qLinkedList* ll)
{
    const qLinkedList* iter = ll;
    while (iter)
    {
        printQueue(iter->data);
        iter = iter->next;
    }
}

void freeqList(qLinkedList* ll)
{
    while (ll != nullptr)
    {
        qLinkedList* toDelete = ll;
        ll = ll->next;
        delete toDelete;
    }
}

//---------------------------------------------------------

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

// Task 1

void equalize(sLinkedList* head)
{
    sLinkedList* iter = head;
    
    std::stack<int> st;

    while (iter)
    {
        while(!((iter->data).empty()))
        {
            st.push((iter->data).top());
            (iter->data).pop();
        }
        iter = iter->next;
    }

    iter = head;
    while (!st.empty())
    {
        if (iter == nullptr)
        {
            iter = head;
        }

        (iter->data).push(st.top());
        st.pop();
        iter = iter->next;
    }
}

// Task 2

bool isEven(int n)
{
    if (n % 2 == 0)
        return true;
    return false;
}


bool all(std::queue<int> q, bool (*pred) (int))
{
    while (!q.empty())
    {
        if (!pred(q.front()))
            return false;
        q.pop();
    }
    return true;
}

void concat(std::queue<int>& q1, std::queue<int>& q2)
{
    while (!q2.empty())
    {
        q1.push(q2.front());
        q2.pop();
    }
}

void concatSimilarQueues(qLinkedList* head, bool (*pred) (int))
{
    qLinkedList* iter = head;
    if (iter == nullptr || iter->next == nullptr)
    {
        return;
    }

    while (iter && iter->next)
    {
        if(all(iter->data, pred))
        {
            while (iter->next && all(iter->next->data, pred))
            {
                concat(iter->data, iter->next->data);
                qLinkedList* toDelete = iter->next;
                iter->next = toDelete->next;
                delete toDelete;
            }
        }
        iter = iter->next;
    }
}

// Task 3

template<typename T>
LinkedListNode<T>* partition(LinkedListNode<T>* head, T x)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    LinkedListNode<T>* startSmaller = nullptr;
    LinkedListNode<T>* endSmaller = nullptr;

    LinkedListNode<T>* startBigger = nullptr;
    LinkedListNode<T>* endBigger = nullptr;

    LinkedListNode<T>* iter = head;
    while (iter)
    {
        if (iter->data < x)
        {
            if (startSmaller == nullptr)
            {
                startSmaller = iter;
                endSmaller = iter;
            }
            else
            {
                endSmaller->next = iter;
                endSmaller = endSmaller->next;
            }
        }
        else
        {
            if (startBigger == nullptr)
            {
                startBigger = iter;
                endBigger = iter;
            }
            else
            {
                endBigger->next = iter;
                endBigger = endBigger->next;
            }
        }

        iter = iter->next;
    }

    if (startSmaller == nullptr)
    {
        return head;
    }
    else if (startBigger == nullptr)
    {
        return head;
    }
    else
    {
        endSmaller->next = startBigger;
        endBigger->next = nullptr;
        printList(startBigger);
        return startSmaller;
    }
}

// Task 4

template<typename T>
LinkedListNode<T>* endOfKGroup(LinkedListNode<T>* head, int k)
{
    LinkedListNode<T>* iter = head;
    while (iter && k != 0)
    {
        iter = iter->next;
        --k;
    }
    return iter;
}

template<typename T>
LinkedListNode<T>* reverseKGroups(LinkedListNode<T>* head, int k)
{
    // указател към новия head
    LinkedListNode<T>* end = endOfKGroup(head, k - 1);

    // ако няма толкова елементи за обръщане
    if (end == nullptr)
    {
        return head;
    }

    LinkedListNode<T>* next = end->next; //всичко след първите к-елемента
    // обръщаме първите к-елемента
    end->next = nullptr;
    end = head; // началото става край след обръщане

    head = reverse(head); // края става начало
    end->next = (reverseKGroups(next, k)); //с рекурсия обръщаме всички к-групи

    return head;
}

// Task 5

LinkedListNode<int>* rerange(LinkedListNode<int>* head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    LinkedListNode<int>* startEven = nullptr;
    LinkedListNode<int>* endEven = nullptr;

    LinkedListNode<int>* startOdd = nullptr;
    LinkedListNode<int>* endOdd = nullptr;

    while (head)
    {
        if (isEven(head->data))
        {
            if (startEven == nullptr)
            {
                startEven = head;
                endEven = head;
            }
            else
            {
                endEven->next = head;
                endEven = endEven->next;
            }
        }
        else
        {
            if (startOdd == nullptr)
            {
                startOdd = head;
                endOdd = head;
            }
            else
            {
                endOdd->next = head;
                endOdd = endOdd->next;
            }
        }
        head = head->next;
    }

    if (startEven == nullptr)
    {
        endOdd->next = nullptr;
        return startOdd;
    }
    else if (startOdd == nullptr)
    {
        endEven->next = nullptr;
        return startEven;
    }
    else
    {
        endEven->next = startOdd;
        endOdd->next = nullptr;
        return startEven;
    }
}

int main()
{
    /*
    std::stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);

    std::stack<int> s2;
    s2.push(6);
    s2.push(7);

    std::stack<int> s3;
    s3.push(8);
    s3.push(9);
    s3.push(10);
    s3.push(11);

    std::stack<int> s4;
    s4.push(12);

    sLinkedList* list = new LinkedListNode<std::stack<int>>(s1,
                        new LinkedListNode<std::stack<int>>(s2,
                        new LinkedListNode<std::stack<int>>(s3,
                        new LinkedListNode<std::stack<int>>(s4))));
    */


    /*
    std::queue<int> q1;
    q1.push(1);
    q1.push(3);
    q1.push(5);
    q1.push(7);
    q1.push(11);

    std::queue<int> q2;
    q2.push(4);
    q2.push(8);

    std::queue<int> q3;
    q3.push(8);
    q3.push(4);
    q3.push(2);
    q3.push(12);

    std::queue<int> q4;
    q4.push(16);

    qLinkedList* list = new LinkedListNode<std::queue<int>>(q1,
        new LinkedListNode<std::queue<int>>(q2,
            new LinkedListNode<std::queue<int>>(q3,
                new LinkedListNode<std::queue<int>>(q4))));

    concatSimilarQueues(list, isEven);
    printSList(list);
    freeqList(list);
    */

    /*
    LinkedListNode<int>* list =new LinkedListNode<int>(9,
        new LinkedListNode<int>(6,
            new LinkedListNode<int>(7,
                new LinkedListNode<int>(3,
                    new LinkedListNode<int>(5)))));

    LinkedListNode<int>* res = partition(list, 2);
    printList(res);
    free(res);
    */

    LinkedListNode<int>* list = new LinkedListNode<int>(9,
        new LinkedListNode<int>(17,
            new LinkedListNode<int>(6,
                new LinkedListNode<int>(12,
                    new LinkedListNode<int>(5,
                        new LinkedListNode<int>(23))))));

    LinkedListNode<int>* res = rerange(list);
    printList(res);
    free(res);

}
