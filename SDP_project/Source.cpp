#include <iostream>
#include <string>
#include "Skiplist.hpp"
#include <list>

int main()
{
	/*
	SkipList<std::string> s;
	s.pushBack("Sofia");
	s.pushBack("Pazrdzhik");
	s.pushBack("Plovdiv");
	s.pushBack("Dimitrovgrad");
	s.pushBack("StaraZagora");
	s.pushBack("NovaZagora");

	s.skip("Sofia", "Plovdiv");
	s.skip("Plovdiv", "Dimitrovgrad");
	s.skip("Dimitrovgrad", "NovaZagora");

	//s.popFront();
	//s.printDirect();
	//s.printSkip();
	*/

	
	// Градове, през които минава влака
	std::cout << "Number of towns: ";
	int n;
	std::cin >> n;
	SkipList<std::string> towns;
	std::string str;
	for (int i = 0; i < n; i++)
	{
		
		std::cin >> str;
		towns.pushBack(str);
	}

	// Директни връзки
	std::cout << "Number of direct links: ";
	int n2;
	std::cin >> n2;
	for (int i = 0; i < n2; i++)
	{
		std::string from;
		std::string to;
		std::cout << "From: ";
		std::cin >> from;
		std::cout << "To: ";
		std::cin >> to;
		towns.skip(from, to);
	}

	//towns.printDirect();
	//towns.printSkip();
	
	// Градове, които трябва да бъдат посетени
	std::list<std::string> toVisit;
	int n3;
	std::cout << "Number of towns to visit: ";
	std::cin >> n3;
	std::cout << "Towns to visit: ";
	for (int i = 0; i < n3; i++)
	{
		std::cin >> str;
		toVisit.push_back(str);
	}
	
	std::list<std::string> res = findBestWay(towns, toVisit);
	std::list<std::string>::iterator it = res.begin();
	while (it != res.end())
	{
		std::cout << *it << " ";
		it++;
	}
}

/*
Sofia
Pazardzhik
Plovdiv
Dimitrovgrad
StaraZagora
NovaZagora
Yambol
Karnobat
Burgas
*/
