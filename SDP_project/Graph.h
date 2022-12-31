#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <string>

struct Edge
{
	unsigned int end;
	unsigned int weight;

	Edge(const unsigned int& e, const unsigned int& w) : end{ e }, weight{ w } {}
};

class Graph {

private:
	std::vector<std::list<Edge>> data;

public:
	Graph(unsigned int);
	void addVertex();
	bool isValidVertex(const unsigned int&) const;
	void addEdge(const unsigned int&, const unsigned int&, unsigned int);
	unsigned int getWeight(const unsigned&, const unsigned int&) const;
	bool hasEdge(const unsigned int&, const unsigned int&) const;
	void getSuccessors(const unsigned int&, std::vector<std::pair<unsigned int, unsigned int>>&);
	void getPredeccessors(const unsigned int&, std::vector<std::pair<unsigned int, unsigned int>>&);
	void print(std::vector<std::string>&) const;
};
