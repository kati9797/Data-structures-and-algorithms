#include "Graph.h"

Graph::Graph(unsigned int vertexCount)
{
	data = std::vector<std::list<Edge>>(vertexCount , std::list<Edge>());
}

void Graph::addVertex()
{
	data.push_back(std::list<Edge>());
}

bool Graph::isValidVertex(const unsigned int& vertex) const
{
	return vertex < data.size();
}

void Graph::addEdge(const unsigned int& start, const unsigned int& end, unsigned int w)
{
	if(!isValidVertex(start) || !isValidVertex(end))
	{
		throw std::runtime_error("Invalid vertex");
	}

	data[start].push_back({ end, w });
	data[end].push_back({ start, w });
}

unsigned int Graph::getWeight(const unsigned& from, const unsigned int& to) const
{
	if (!isValidVertex(from) || !isValidVertex(to))
	{
		throw std::runtime_error("Invalid vertex");
	}

	for (const Edge& e : data[from])
	{
		if (e.end == to)
			return e.weight;
	}
	return 0;
}

bool Graph::hasEdge(const unsigned int& from, const unsigned int& to) const
{
	if (!isValidVertex(from) || !isValidVertex(to))
	{
		return false;
	}

	for (const Edge& e : data[from])
	{
		if (e.end == to)
			return true;
	}
	return false;
}

void Graph::getSuccessors(const unsigned int& vertex, std::vector<std::pair<unsigned int, unsigned int>>& v)
{
	if (!isValidVertex(vertex))
	{
		throw std::runtime_error("Invalid vertex!");
	}
	
	for (const Edge& e : data[vertex])
	{
		v.push_back(std::make_pair(e.end, e.weight));
	}
}

void Graph::getPredeccessors(const unsigned int& vertex, std::vector<std::pair<unsigned int, unsigned int>>& v)
{
	if (!isValidVertex(vertex))
	{
		throw std::runtime_error("Invalid vertex!");
	}

	for (unsigned int i = 0; i < data.size(); i++)
	{
		for (const Edge& e : data[i])
		{
			if (e.end == vertex)
				v.push_back(std::make_pair(i, e.weight
				));
		}
	}
}

void Graph::print(std::vector<std::string>& v) const
{
	int len = data.size();

	for (int i = 0; i < len; i++)
	{
		for (const Edge& e : data[i])
		{
			std::cout << v[i] << "->" << v[e.end] << " - " << e.weight << std::endl;
		}
	}
}

void readFirstRow(std::string source, int& k, int& r)
{
	std::ifstream myfile;
	myfile.open(source);
	std::string myline;
	if (myfile.is_open()) {
		while (!myfile.eof()) {
			std::getline(myfile, myline);

			int i = 0;
			while (myline[i] != ' ')
			{
				char c = myline[i];
				int digit = c - '0';
				k *= 10;
				k += digit;
				i++;
			}

			i++;

			while (myline[i] != '\0')
			{
				char c = myline[i];
				int digit = c - '0';
				r *= 10;
				r += digit;
				i++;
			}

			break;
		}
	}
	else {
		std::cout << "Couldn't open file\n";
	}
}

int findWord(std::vector<std::string> v, std::string str)
{
	int len = v.size();
	for (int i = 0; i < len; i++)
	{
		if (str == v[i])
		{
			return i;
		}
	}
	return -1;
}

void readRRows(std::string source, int r, std::vector<std::string>& v, Graph& g)
{
	std::ifstream myfile;
	myfile.open(source);
	std::string myline;
	int cnt = 0;
	if (myfile.is_open()) {
		while (!myfile.eof()) {
			std::getline(myfile, myline);
			cnt++;
			if (cnt == 1)
			{
				continue;
			}
			else if (cnt > r + 1)
			{
				break;
			}
			else {

				int i = 0;

				std::string curr;
				while (myline[i] != ' ')
				{
					curr += myline[i];
					i++;
				}

				int ind = findWord(v, curr);
				if (ind == -1)
				{
					v.push_back(curr);
					ind = v.size() - 1;
				}

				i++;
				std::string curr2;
				while (myline[i] != ' ')
				{
					curr2 += myline[i];
					i++;
				}

				int ind2 = findWord(v, curr2);
				if (ind2 == -1)
				{
					v.push_back(curr2);
					ind2 = v.size() - 1;
				}

				i++;
				int weight = 0;
				while (myline[i] != '\0')
				{
					char c = myline[i];
					int digit = c - '0';
					weight *= 10;
					weight += digit;
					i++;
				}
				g.addEdge(ind, ind2, weight);
			}
		}
	}
	else {
		std::cout << "Couldn't open file\n";
	}
}

void readLastRow(std::string source, int r, int& time)
{
	std::ifstream myfile;
	myfile.open(source);
	std::string myline;
	int cnt = 0;
	if (myfile.is_open()) {
		while (!myfile.eof()) {
			std::getline(myfile, myline);
			cnt++;
			if (cnt > r + 1)
			{
				int i = 0;
				while (myline[i] != '\0')
				{
					char c = myline[i];
					int digit = c - '0';
					time *= 10;
					time += digit;
					i++;
				}
			}
		}
	}
}
