#include "Box.h"
#include <fstream>

void Box::free_rec(BoxNode* head)
{
	if (!head)
		return;

	for (int i = 0; i < head->boxes.size(); i++)
	{
		free_rec(head->boxes[i]);
	}
	delete head;
}

void Box::free()
{
	free_rec(head);
}

Box::Box() : head{ nullptr } {}

Box::Box(BoxNode* node = nullptr) : head{ node } {}

Box::~Box()
{
	free();
}

void Box::printBox() const
{
	if (head != nullptr)
	{
		std::cout << "-----------------------" << std::endl;
		for (int i = 0; i < head->boxes.size(); i++)
		{
			head->boxes[i]->printBoxNode();
			std::cout << "-----------------------" << std::endl;
		}
	}
}

BoxNode* Box::findBox(const std::string& boxName)
{
	if (head == nullptr)
	{
		return head;
	}

	if (head->dataPtr->name == boxName)
	{
		return head;
	}

	BoxNode* toReturn = nullptr;
	for (int i = 0; i < head->boxes.size(); i++)
	{
		head->boxes[i]->findBoxNode(boxName, toReturn);
	}
	return toReturn;
}

bool Box::isEmpty() const
{
	if (head->boxes.size() == 0 && head->dataPtr->souvenirs.size() == 0)
	{
		return true;
	}
	else if (head->dataPtr->souvenirs.size() != 0)
	{
		return false;
	}

	for (int i = 0; i < head->boxes.size(); i++)
	{
		if (head->boxes[i]->dataPtr != nullptr)
		{
			return false;
		}
	}
	return true;
}

bool Box::hasOneBox() const
{
	if (head->boxes.size() == 1 && head->dataPtr->souvenirs.size() == 0)
	{
		return true;
	}
	else if (head->dataPtr->souvenirs.size() != 0)
	{
		return false;
	}

	int cnt = 0;
	for (int i = 0; i < head->boxes.size(); i++)
	{
		if (head->boxes[i]->dataPtr != nullptr)
		{
			cnt++;
		}
	}
	return cnt == 1;
}

void Box::reduceBoxes()
{
	if (head == nullptr)
		return;

	if (isEmpty())
	{
		return;
	}

	if (hasOneBox() && head->boxes[0]->empty()) 
	{
		BoxData* toDelete = head->boxes[0]->dataPtr;
		delete toDelete;
		head->boxes[0]->dataPtr = nullptr;
		return;
	}

	// първо премахваме всички празни кутии
	for (int i = 0; i < head->boxes.size(); i++)
	{
		head->boxes[i]->reduceEmptyBoxNodes_rec();
	}

	// премахваме кутиите, в които има само една кутия
	for (int i = 0; i < head->boxes.size(); i++)
	{
		head->boxes[i]->reduceBoxesWithOneBox_rec();
	}
}

void Box::addBox(BoxNode* n)
{
	head->boxes.push_back(n);
}

// четене от файл

void Box::initFromFile(std::string source, int& numberOfAllBoxes)
{
	std::ifstream myfile;
	myfile.open(source);
	std::string myline;
	
	// създаваме нова главна кутия
	if (head == nullptr)
	{
		BoxData* mainBoxData = new BoxData("Main box");
		BoxNode* mainNode = new BoxNode(mainBoxData);
		head = mainNode;
	}
	
	int cnt = 0; // номер на ред
	
	if (myfile.is_open()) {
		while (!myfile.eof()) {
			std::getline(myfile, myline);
			
			if (myline.size() == 0)
			{
				return;
			}
			
			cnt++;
			if (cnt == 1) // ред 1
			{
				int i = 0;
				while (myline[i] != '\0')
				{
					numberOfAllBoxes *= 10;
					numberOfAllBoxes += myline[i++] - '0';
				}
			}
			else 
			{
				std::string currBox; // кутия, която ще обработваме
				int i = 0; // символ на текущия ред
				while (myline[i] != ' ')
				{
					currBox += myline[i++];
				}
				
				BoxNode* newBox = findBox(currBox);
				if (!newBox) // ако не е създадена досега, я създаваме
				{
					BoxData* newData = new BoxData(currBox);
					newBox = new BoxNode(newData);
					addBox(newBox);
				}
				
				i++;

				int numberSouvenirs = 0; // брой сувенири в кутия
				while (myline[i] != ' ')
				{
					numberSouvenirs *= 10;
					numberSouvenirs += myline[i++] - '0';
				}
				i++;

				int j = 0;
				while (numberSouvenirs != 0 && j < numberSouvenirs)
				{
					std::string currSouvenir = "";
					while (myline[i] != ' ')
					{
						currSouvenir += myline[i++];
					}
					i++;
					newBox->addSouvenirs(currSouvenir); // добавяме сувенири
					j++;
				}
				
				int countBoxes = 0; // брой кутии в текущата кутия
				while (myline[i] != ' ' && myline[i] != '\0')
				{
					countBoxes *= 10;
					countBoxes += myline[i++] - '0';
				}

				i++;

				j = 0;
				while (countBoxes != 0 && j < countBoxes)
				{
					std::string currBox = "";
					while (myline[i] != ' ' && myline[i] != '\0')
					{
						currBox += myline[i++];
					}
					
					BoxNode* box = findBox(currBox);
					if (!box) // създаваме нова кутия (приемаме, че във файла кутиите се задават от най-външна към най-вътрешна)
					{
						BoxData* newData = new BoxData(currBox);
						box = new BoxNode(newData);
						newBox->addBoxNode(box);
					}
					
					i++;
					j++;
				}
			}
		}
		myfile.close();
	}
	else {
		std::cout << "Couldn't open file\n";
	}
	
}

