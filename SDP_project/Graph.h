#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <string>

struct Edge
{
	std::string end;
	int weight;

	Edge() = default;
	Edge(const std::string& e, const int& w) : end{ e }, weight{ w } {}
};

class Graph {

private:
	std::vector<std::pair<std::string,std::list<Edge>>> data;

	int findVertex(std::string&) const;
	void findBestRoute_rec(std::vector<std::string>, std::vector<std::string>&, int, const int&, int&, const std::string&, std::string);
	void check(std::vector<std::string>, std::vector<std::string>&, int&);
public:
	Graph() = default;
	Graph(int);
	void addVertex(std::string&);
	bool isValidVertex(std::string&) const;
	void addEdge(std::string&, std::string&, int);
	int getWeight(std::string&, std::string&) const;
	bool hasEdge(std::string&, std::string&) const;
	void getSuccessors(std::string&, std::vector<std::pair<std::string, int>>&);
	void getPredeccessors(std::string&, std::vector<std::pair<std::string, int>>&);
	void print() const;

	void inputFromFile(std::string, int&, int&, int&);
	void findBestRoute(const int&);
};
