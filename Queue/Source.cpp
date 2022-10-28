#include <iostream>
#include "CircularQueue.hpp"
#include "LinkedQueue.hpp"

int main()
{
	/*
	CQueue<int> q;

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();

	std::cout << q.isEmpty() << std::endl;

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	CQueue<int> q2(q);
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	*/

	LinkedQueue<int> l;
	l.enqueue(1);
	l.enqueue(2);
	l.enqueue(3);
	l.enqueue(4);
	l.enqueue(5);

	std::cout << l.peek() << std::endl;
	l.dequeue();
	std::cout << l.peek() << std::endl;
	l.dequeue();
	std::cout << l.peek() << std::endl;
	l.dequeue();
	std::cout << l.peek() << std::endl;
	l.dequeue();
	std::cout << l.peek() << std::endl;
	l.dequeue();

	std::cout << "Empty? " << l.isEmpty() << std::endl;

	l.enqueue(1);
	l.enqueue(2);
	l.enqueue(3);
	l.enqueue(4);
	l.enqueue(5);

	LinkedQueue<int> l2(l);
	std::cout << l2.toDequeue() << std::endl;
	std::cout << l2.toDequeue() << std::endl;
	std::cout << l2.toDequeue() << std::endl;
	std::cout << l2.toDequeue() << std::endl;
	std::cout << l2.toDequeue() << std::endl;

	std::cout << "Empty? " << l2.isEmpty() << std::endl;

}
