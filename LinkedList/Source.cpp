int main()
{
    SinglyLinkedList<int> list;
    list.pushFront(1);
    list.pushFront(2);
    list.pushFront(3);
    list.pushBack(8);
    list.pushBack(9);
  
    list.print();
  
    list.popFront();
    list.popFront();
    list.popFront();
    list.popFront();
    list.popFront();

    std::cout << "Empty? " << list.isEmpty() << std::endl;

    list.pushFront(1);
    list.pushFront(2);
    list.pushFront(3);
    list.pushBack(8);
    list.pushBack(9);

    SinglyLinkedList<int> l2(list);
    l2.print();
}
