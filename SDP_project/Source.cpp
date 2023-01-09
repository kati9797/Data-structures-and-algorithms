#include <iostream>
#include <string>
#include "Skiplist.hpp"
#include <list>
#include <fstream>
#include <vector>
#include "Graph.h"
#include "Box.h"

int main()
{
	/*
	// А)
	
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

	// Градове, които трябва да бъдат посетени
	std::list<std::string> toVisit;
	int n3;
	std::cout << "Number of towns to visit: ";
	std::cin >> n3;
	std::cout << "Towns to visit: " << std::endl;
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
	*/
	
	/*
	// Б)

	int k = 0;
	int r = 0;
	int time = 0;
	Graph g;
	g.inputFromFile("town.txt", k, r, time);
	// 
	//g.print();
	std::cout << "Best route: " << std::endl;
	g.findBestRoute(time);
	*/

	/*
	// В)

	Box mainBox;
	int countBoxes = 0;
	mainBox.initFromFile("boxes.txt", countBoxes);
	mainBox.reduceBoxes();
	mainBox.printBox();
	*/
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
