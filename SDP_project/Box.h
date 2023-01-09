#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <list>

struct BoxData {
	std::string name;
	std::vector<std::string> souvenirs;

	BoxData(const std::string& n) : name{ n } {}
	BoxData(const std::string& n, std::vector<std::string> s) : name{ n }, souvenirs{ s } {}
};

struct BoxNode
{
private:
	void copy(const BoxNode& other)
	{
		BoxData d = *(other.dataPtr);
		dataPtr = new BoxData(d.name, d.souvenirs);
	}
	
	void free()
	{
		delete dataPtr;
	}
	
public:

	BoxData* dataPtr;
    std::vector<BoxNode*> boxes;

	BoxNode(BoxData* ptr = nullptr) : dataPtr{ptr} {}

	BoxNode(const BoxNode& other)
	{
		copy(other);
	}

	BoxNode& operator=(const BoxNode& other)
	{
		if (this != &other)
		{
			free();
			copy(other);
		}
		return *this;
	}

	~BoxNode()
	{
		free();
	}
	
	std::string getName() const
	{
		return dataPtr->name;
	}

	void printBoxNode() const
	{
		if (dataPtr != nullptr)
		{	std::cout << "Name: ";
			std::cout << dataPtr->name << std::endl;
		}
		
		if (dataPtr != nullptr)
		{
			std::cout << "Souvenirs: " << std::endl;
			for (int i = 0; i < dataPtr->souvenirs.size(); i++)
			{
				std::cout << dataPtr->souvenirs[i] << " ";
			}
		
			std::cout << std::endl;
		}

		if (boxes.size() != 0)
		{
			for (int i = 0; i < boxes.size(); i++)
			{
				std::cout << "********************" << std::endl;
				boxes[i]->printBoxNode();
			}
		}
	}

	void findBoxNode(const std::string& n, BoxNode*& node)
	{
		if (this == nullptr)
		{
			return;
		}

		if (dataPtr->name == n)
		{
			node = this;
			return;
		}

		for (int i = 0; i < boxes.size(); i++)
		{
			boxes[i]->findBoxNode(n, node);
		}
	}

	void addSouvenirs(const std::string& s)
	{
		dataPtr->souvenirs.push_back(s);
	}

	void addBoxNode(BoxNode* n)
	{
		boxes.push_back(n);
	}

	bool empty() const
	{
		if (boxes.size() == 0 && dataPtr->souvenirs.size() == 0)
		{
			return true;
		}
		else if (dataPtr->souvenirs.size() != 0)
		{
			return false;
		}

		for (int i = 0; i < boxes.size(); i++)
		{
			if (boxes[i]->dataPtr != nullptr)
			{
				return false;
			}
		}

		return true;
	}

	bool hasOneBox() const
	{
		if (boxes.size() == 1 && dataPtr->souvenirs.size() == 0)
		{
			return true;
		}
		else if (dataPtr->souvenirs.size() != 0)
		{
			return false;
		}

		int cnt = 0;
		for (int i = 0; i < boxes.size(); i++)
		{
			if (boxes[i]->dataPtr != nullptr)
			{
				cnt++;
			}
		}

		return cnt == 1;
	}
	
	void reduceEmptyBoxNodes_rec()
	{
		if (dataPtr == nullptr)
		{
			return;
		}

		if (dataPtr->souvenirs.size() == 0 && boxes.size() == 0) 
		{
			delete dataPtr;
			dataPtr = nullptr;
		}

		for (int i = 0; i < boxes.size(); i++)
		{
			boxes[i]->reduceEmptyBoxNodes_rec();
		}
	}
	
	void reduceBoxesWithOneBox_rec()
	{
		if(dataPtr == nullptr)
		{
			return;
		}

		if (hasOneBox() || empty()) 
		{
			delete dataPtr;
			dataPtr = nullptr;
		}

		for (int i = 0; i < boxes.size(); i++)
		{
			boxes[i]->reduceBoxesWithOneBox_rec();
		}
	}
};

class Box{
private:
	BoxNode* head = nullptr;
	
	void free_rec(BoxNode*);
	void free();
public:
	Box();
	Box(BoxNode*);
	Box(const Box&) = default;
	Box& operator=(const Box&) = default;
	~Box();

	void printBox() const;
	void initFromFile(std::string, int&);
	void addBox(BoxNode*);
	BoxNode* findBox(const std::string&);
	bool isEmpty() const;
	bool hasOneBox() const;
	void reduceBoxes();
};
