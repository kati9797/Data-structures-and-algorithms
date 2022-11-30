#include <iostream>

template<typename T>
struct Tree {
    T data;
    Tree<T>* left;
    Tree<T>* right;

    Tree(const T& d, Tree<T>* l = nullptr, Tree<T>* r = nullptr) : data{ d }, left{ l }, right{ r } {}
};

template<typename T>
void freeTree(Tree<T>* root)
{
    if (root == nullptr)
        return;

    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

template<class T>
void printBT(const std::string& prefix, const Tree<T>* node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "`--");

        std::cout << node->data << std::endl;

        printBT(prefix + (isLeft ? "|   " : "    "), node->left, true);
        printBT(prefix + (isLeft ? "|   " : "    "), node->right, false);
    }
}

template<class T>
void printTree(const Tree<T>* node) {
    printBT("", node, false);
}

// Да се реализира функция, която добавя елемент в двоично наредено дърво.

template<typename T>
void addElemInTree(Tree<T>*& root, const T& elem)
{
    if (root == nullptr)
    {
        root = new Tree<T>(elem);
        return;
    }
    else if (elem > root->data)
    {
        addElemInTree(root->right, elem);
    }
    else
    {
        addElemInTree(root->left, elem);
    }
}

//Да се напише функция contains(Tree<T>* tree, const T& elem) която връща дали елемента се съдържа в двоично дърво.
//Да се реализира същата функция за двоично наредено дърво.

template<typename T>
bool containsInBT(Tree<T>* root, const T& elem)
{
    if (root == nullptr)
    {
        return false;
    }
    else if (root->data == elem)
    {
        return true;
    }
    else
    {
        return containsInBT(root->left, elem) || containsInBT(root->right, elem);
    }
}

template<typename T>
bool containsInBST(Tree<T>* root, const T& elem)
{
    if (root == nullptr)
    {
        return false;
    }
    else if (root->data == elem)
    {
        return true;
    }
    else if (elem > root->data)
    {
        containsInBST(root->right, elem);
    }
    else
    {
        containsInBST(root->left, elem);
    }
}

//Да се напише функция max((Tree<T>* tree) която връща най - големия елемент в двоично дърво. 
//Да се реализира същата функция за двоично наредено дърво. Да се реализира функция намираща най - малкия елемент.

template<typename T>
T maxElemBT(Tree<T>* root)
{
    if (root == nullptr)
    {
        return -1;
    }

    T maxElem = root->data;
    
    T maxElemLeft = maxElemBT(root->left);
    if (maxElemLeft > maxElem)
        maxElem = maxElemLeft;

    T maxElemRight = maxElemBT(root->right);
    if (maxElemRight > maxElem)
        maxElem = maxElemRight;

    return maxElem;
}

template<typename T>
T maxElemBST(Tree<T>* root)
{
    if (root == nullptr)
    {
        return -1;
    }
    
    T maxElem = root->data;
    T maxElemRight = maxElemBST(root->right);
    if (maxElemRight > maxElem)
        maxElem = maxElemRight;
    return maxElem;
}

template<typename T>
T minElemBT(Tree<T>* root)
{
    if (root == nullptr)
    {
        return 1024;
    }

    T minElem = root->data;

    T minElemLeft = minElemBT(root->left);
    if (minElemLeft < minElem)
        minElem = minElemLeft;

    T minElemRight = minElemBT(root->right);
    if (minElemRight < minElem)
        minElem = minElemRight;

    return minElem;
}

template<typename T>
T minElemBST(const Tree<T>* root)
{
    if (root == nullptr)
    {
        return 1024;
    }

    T minElem = root->data;
    T minElemLeft = minElemBST(root->left);
    if (minElemLeft < minElem)
        minElem = minElemLeft;
    return minElem;
}

//Да се реализира функция, която връща височината на двоично дърво.

template<typename T>
int hightOfBT(const Tree<T>* root)
{
    if (root == nullptr)
    {
        return -1;
    }

    int hightLeft = 1 + hightOfBT(root->left);
    int hightRight = 1 + hightOfBT(root->right);
    return std::max(hightLeft, hightRight);
}

//Да се напише функция, която обхожда елементите на двоично дърво по схемата ляво - корен - дясно. (още позната като inorder traversal).
//Извикайте функцията върху двоично наредено дърво.Какво забелязвате ?

template<typename T>
void leftRootRight(Tree<T>* root)
{
    if (root == nullptr)
    {
        return;
    }

    leftRootRight(root->left); 
    std::cout << root->data << " ";
    leftRootRight(root->right);
}

int main()
{
    Tree<int>* t = new Tree<int>(4, new Tree<int>(2, new Tree<int>(1), new Tree<int> (3)), new Tree<int>(9, new Tree<int>(8), new Tree<int>(12)));
    Tree<int>* t2 = new Tree<int>(4, new Tree<int>(10), new Tree<int>(1));
  
    //addElemInTree(t, 1);
    //printTree(t);
    //std::cout << containsInBT(t2, 10) << std::endl;
    ////std::cout << containsInBT(t2, 8) << std::endl;
    //std::cout << containsInBST(t, 10) << std::endl;
    //std::cout << containsInBST(t, 2) << std::endl;

    //std::cout << maxElemBT(t2) << std::endl;
    //std::cout << maxElemBST(t) << std::endl;
    //std::cout << minElemBT(t2) << std::endl;
    //std::cout << minElemBST(t) << std::endl;

    //std::cout << hightOfBT(t);
    //leftRootRight(t);
    //leftRootRight(t2);
  
    freeTree(t);
    freeTree(t2);
}
