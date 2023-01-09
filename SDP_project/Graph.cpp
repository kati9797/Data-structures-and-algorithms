#include "Graph.h"

int Graph::findVertex(std::string& str) const
{
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].first == str)
			return i;
	}
	return -1;
}

Graph::Graph(int vertexCount)
{
	data.assign(vertexCount, std::pair<std::string, std::list<Edge>>());
}

void Graph::addVertex(std::string& n)
{

	data.push_back(std::make_pair(n, std::list<Edge>()));
}

bool Graph::isValidVertex(std::string& vertex) const
{
	return findVertex(vertex) != -1;
}

void Graph::addEdge(std::string& start, std::string& end, int w)
{
	if (!isValidVertex(start) || !isValidVertex(end))
	{
		throw std::runtime_error("Invalid vertex");
	}

	int startInd = findVertex(start);
	int endInd = findVertex(end);
	data[startInd].second.push_back({ end, w });
	data[endInd].second.push_back({ start, w });
}

int Graph::getWeight(std::string& from, std::string& to) const
{
	if (!isValidVertex(from) || !isValidVertex(to))
	{
		throw std::runtime_error("Invalid vertex");
	}

	int startInd = findVertex(from);

	for (const Edge& e : data[startInd].second)
	{
		if (e.end == to)
			return e.weight;
	}
	return 0;
}

bool Graph::hasEdge(std::string& from, std::string& to) const
{
	if (!isValidVertex(from) || !isValidVertex(to))
	{
		return false;
	}

	int startInd = findVertex(from);

	for (const Edge& e : data[startInd].second)
	{
		if (e.end == to)
			return true;
	}
	return false;
}

void Graph::getSuccessors(std::string& vertex, std::vector<std::pair<std::string, int>>& v)
{
	if (!isValidVertex(vertex))
	{
		throw std::runtime_error("Invalid vertex!");
	}

	int startInd = findVertex(vertex);

	for (const Edge& e : data[startInd].second)
	{
		v.push_back(std::make_pair(e.end, e.weight));
	}
}

void Graph::getPredeccessors(std::string& vertex, std::vector<std::pair<std::string, int>>& v)
{
	if (!isValidVertex(vertex))
	{
		throw std::runtime_error("Invalid vertex!");
	}

	int startInd = findVertex(vertex);

	for (unsigned int i = 0; i < data.size(); i++)
	{
		for (const Edge& e : data[i].second)
		{
			if (e.end == vertex)
				v.push_back(std::make_pair(data[i].first, e.weight));
		}
	}
}

void Graph::print() const
{
	int len = data.size();

	for (int i = 0; i < len; i++)
	{
		for (const Edge& e : data[i].second)
		{
			std::cout << data[i].first << "->" << e.end << " - " << e.weight << std::endl;
		}
	}
}

// Четене от файл

void Graph::inputFromFile(std::string source, int& k, int& r, int& time)
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
				int i = 0;

				// к на брой върха

				while (myline[i] != ' ')
				{
					char c = myline[i];
					int digit = c - '0';
					k *= 10;
					k += digit;
					i++;
				}

				i++;

				// r връзки

				while (myline[i] != '\0')
				{
					char c = myline[i];
					int digit = c - '0';
					r *= 10;
					r += digit;
					i++;
				}
			}
			else if (cnt <= r + 1)
			{
				int i = 0;

				// от:

				std::string curr;
				while (myline[i] != ' ')
				{
					curr += myline[i];
					i++;
				}

				int ind = findVertex(curr);
				if (ind == -1)
				{
					addVertex(curr);
				}

				i++;

				// до:

				std::string curr2;
				while (myline[i] != ' ')
				{
					curr2 += myline[i];
					i++;
				}

				int ind2 = findVertex(curr2);
				if (ind2 == -1)
				{
					addVertex(curr2);;
				}

				i++;

				// за време:

				int weight = 0;
				while (myline[i] != '\0')
				{
					char c = myline[i];
					int digit = c - '0';
					weight *= 10;
					weight += digit;
					i++;
				}
				addEdge(curr, curr2, weight);
			}
			else
			{
				int i = 0;

				// време, с което разполагаме

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

		myfile.close();
	}
	else {
		std::cout << "Couldn't open file\n";
	}

}

bool isVisitedBefore(std::vector<std::string> v, std::string vertex)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == vertex)
			return true;
	}
	return false;
}

// проверяваме дали намерения път е по-оптимален 

void Graph::check(std::vector<std::string> currPath, std::vector<std::string>& bestPath, int& maxVisited)
{
	std::vector<std::string> visited;
	for (int i = 0; i < currPath.size(); i++)
	{
		if (!isVisitedBefore(visited, currPath[i]))
		{
			visited.push_back(currPath[i]);
		}
	}

	int currVisited = visited.size();
	if (currVisited > maxVisited)
	{
		maxVisited = currVisited;
		bestPath.clear();
		bestPath = currPath;
	}
}

void Graph::findBestRoute_rec(std::vector<std::string> currPath, std::vector<std::string>& bestPath, int currTime, const int& maxTime, int& maxVisited, const std::string& start, std::string currPos)
{
	if (currTime > maxTime)
	{
		return;
	}

	if (currPos == start)
	{
		// достигнали сме началната позиция
		check(currPath, bestPath, maxVisited);
	}

	std::vector<std::pair<std::string, int>> succ;
	getSuccessors(currPos, succ);
	for (int i = 0; i < succ.size(); i++)
	{
		currPath.push_back(succ[i].first);
		findBestRoute_rec(currPath, bestPath, currTime + succ[i].second, maxTime, maxVisited, start, succ[i].first);
		currPath.pop_back();
	}
}

void Graph::findBestRoute(const int& maxTime)
{
	std::vector<std::string> currPath;
	std::vector<std::string> bestPath;
	int currTime = 0;
	int maxVisited = 0;
	std::string start = data[0].first;
	std::string currPos = start;
	currPath.push_back(start);
	findBestRoute_rec(currPath, bestPath, currTime, maxTime, maxVisited, start, currPos);

	for (int i = 0; i < bestPath.size(); i++)
	{
		std::cout << bestPath[i] << " ";
	}
}
