//Да се напише функция, която обръща едносвързан списък.
template<typename T>
SinglyLinkedList<T> reverse(const SinglyLinkedList<T>& list)
{
    SinglyLinkedListElement<T>* ptr = list.getHead();
    SinglyLinkedList<T> reverse;

    if (ptr == nullptr)
    {
        std::cerr << "Empty list!" << std::endl;
    }
    else
    {
        while (ptr != nullptr)
        {
            reverse.pushFront(ptr->data);
            ptr = ptr->next;
        }

    }
    return reverse;
}

//Да се напише функция, която открива средата на свързан списък.
template<typename T>
const T& findMiddle(const SinglyLinkedList<T>& list)
{
    SinglyLinkedListElement<T>* slowPtr = list.getHead();

    if (slowPtr == nullptr)
    {
        std::cerr << "Empty list!" << std::endl;
    }
    else
    {
        SinglyLinkedListElement<T>* fastPtr = slowPtr;

        while (fastPtr != nullptr && fastPtr->next != nullptr)
        {
            slowPtr = slowPtr->next;
            fastPtr = (fastPtr->next)->next;
        }
    }

    return slowPtr->data;
}
