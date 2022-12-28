#include <iostream>
#include "Tree.hpp"
#include <vector>
#include<string>
#include "ListNode.hpp"

// Задача първа
// Да се напише функция, която проверява дали дадено дърво е двоично наредено дърво.

bool isBSTrec(const Node<int>* root, int min, int max)
{
    if (root == nullptr)
        return true;

    if (root->data < min || root->data > max)
        return false;

    return isBSTrec(root->left, min, root->data) && isBSTrec(root->right, root->data, max);
}

bool isBST(const Node<int>* root)
{
    return isBSTrec(root, INT_MIN, INT_MAX);
}

// Задача втора
// Да се напише функция, която от сортиран вектор построява двоично наредено дърво.

Node<int>* buildBSTrec(int start, int end, std::vector<int> v)
{
    if (end < start)
        return nullptr;

    int mid = (end - start)/2 + start;
    std::cout<<mid<<std::endl;
    return new Node<int>(v[mid], buildBSTrec(start, mid - 1, v), buildBSTrec(mid + 1, end, v));
}

Node<int>* buildBST(std::vector<int> v)
{
    return buildBSTrec(0, v.size() - 1, v);
}

// Задача трета
// Да се напише функция, която премахва възел от двоично наредено дърво.

bool removeElem(Node<int>*& root, const int& elem)
{
    if (root == nullptr)
    {
        return false;
    }

    if (root->data == elem)
    {
        // ако е листо
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            root = nullptr;
            return true;
        }
        else if (root->left == nullptr && root->right != nullptr) // има само дясно поддърво
        {
            Node<int>* toDelete = root;
            root = root->right;
            delete toDelete;
            return true;
        }
        else if (root->left != nullptr && root->right == nullptr) // има само ляво поддърво
        {
            Node<int>* toDelete = root;
            root = root->left;
            delete toDelete;
            return true;
        }
        else // има ляво и дясно поддърво
        {
            Node<int>* temp = root -> right;
            while (temp->left != nullptr && temp->right != nullptr) {
                if (temp->left != nullptr)
                {
                    temp = temp->left;
                }
                else
                {
                    temp = temp->right;
                }
            }
            root->data = temp->data;
            removeElem(root->right, root->data); // трием листо
            return true;
        }
    }
    
    if (root->data < elem)
    {
        return removeElem(root->right, elem);
    }
    else if (root->data > elem)
    {
        return removeElem(root->left, elem);
    }
}

// Задача четвърта
// Да се напише функция, която проверява дали две дървета са еднакви.

bool sameTrees(const Node<int>* fst, const Node<int>* snd)
{
    if (fst == nullptr && snd == nullptr)
    {
        return true;
    }
    else if (fst == nullptr && snd != nullptr || fst != nullptr && snd == nullptr)
    {
        return false;
    }

    if (fst->data != snd->data)
    {
        return false;
    }

    return sameTrees(fst->left, snd->left) && sameTrees(fst->right, snd->right);
}

// Задача пета
// По даден корен на двоично наредено дърво и цяло число k, върнете k-тият най-малък елемент (броим от 1) от всички върхове на дървото.

void elementsInBST(const Node<int>* root, std::vector<int>& v)
{
    if (root == nullptr)
        return;

    elementsInBST(root->left, v);
    v.push_back(root->data);
    elementsInBST(root->right, v);
}

int KthSmallestElementBST(const Node<int>* root, int k)
{
    std::vector<int> v;
    elementsInBST(root, v);
    return v[k - 1];
}

// Задача шеста
// Нашата цел е да направим алгоритъм, който сериализира двоично дърво за търсене като го превърне в символен низ. 
// Трябва също да можем да десериализираме дърво - по подадения низ да построим дърво.

void serializeBSTrec(const Node<int>* root, std::string& str)
{
    if (root == nullptr)
        return;

    serializeBSTrec(root->left, str);
    str += std::to_string(root->data);
    serializeBSTrec(root->right, str);
}

std::string serializeBST(const Node<int>* root)
{
    std::string str = "";
    serializeBSTrec(root, str);
    return str;
}

Node<int>* deserializeBSTrec(int start, int end, std::string str)
{
    if (start > end)
    {
        return nullptr;
    }

    int mid = (end - start) / 2 + start;

    return new Node<int>(str[mid] - '0', deserializeBSTrec(start, mid - 1, str), deserializeBSTrec(mid + 1, end, str));
}

Node<int>* deserializeBST(std::string str)
{
    return deserializeBSTrec(0, str.size() - 1, str);
}

// Задача седма
// По подадено начало на свързан списък, чиито елементи са възходящо подредени, постройте балансирано наредено двоично дърво за търсене. 

Node<int>* buildFromList(ListNode<int>* head)
{
    if (head == nullptr)
    {
        return nullptr;
    } 
    ListNode<int>* slow = head;
    ListNode<int>* fast = head;
    ListNode<int>* prev = head;
    while (fast != nullptr && fast->next != nullptr)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    
    Node<int>* res = new Node<int>(slow->data);

    if (prev != slow)
    {
        prev->next = nullptr;    
        res->left = buildFromList(head); 
    }
    res->right = buildFromList(slow->next);
    return res;
}

// Задача осма
// Search in a Binary Search Tree
// По даден корен на двоично дърво за търсене и стойност на елемен от дървото, проверете дали елемента се съдържа в дървото.
// Измислете подходящо решение ако елементът не се съдържа в дървото.

Node<int>* findElem(Node<int>* root, const int& elem)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->data == elem)
        return root;

    Node<int>* left = findElem(root->left, elem);
    Node<int>* right = findElem(root->right, elem);

    if (left != nullptr)
    {
        return left;
    }
    if (right != nullptr)
    {
        return right;
    }
    return nullptr;
}

// Задача девета
// Insert into a Binary Search Tree
// По даден корен на наредено двоично дърво за търсене и число, поставете числото в дървото. 
// Върнете корена на дървото след успешно поставяне.
// Предварително знаем, че даденото число не се съдържа вече в дървото.

Node<int>* insertIntoBST(Node<int>*& root, const int& elem)
{
    if (root == nullptr)
    {
        return new Node<int>(elem);
    }

    if (root->data < elem)
    {
        root->right = insertIntoBST(root->right, elem);
    }
    else if (root->data > elem)
    {
        root -> left = insertIntoBST(root->left, elem);
    }

    return root;
}

int main()
{
    using Tree = Node<int>;
    using List = ListNode<int>;

    /*
    // Task 1
    Tree* t = new Tree(5, new Tree(3, new Tree(1), new Tree(4)), new Tree(6, nullptr, new Tree(7)));
    std::cout << isBST(t);
    freeTree(t);
    */

    /*
    // Task 2
    std::vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    Tree* t = buildBST(v);
    printTree(t);
    freeTree(t);
    */

    /*
    // Task 3
    Tree* t = new Tree(5, new Tree(3, new Tree(1), new Tree(4)), new Tree(6, nullptr, new Tree(7)));
    std::cout << removeElem(t, 3);
    printTree(t);
    freeTree(t);
    */

    /*
    // Task 4
    Tree* t1 = new Tree(5, new Tree(3, new Tree(1), new Tree(4)), new Tree(6, nullptr, new Tree(7)));
    Tree* t2 = new Tree(5, new Tree(3, new Tree(1), new Tree(4)), new Tree(6, nullptr, new Tree(7)));
    std::cout << sameTrees(t1, t2);
    freeTree(t1);
    freeTree(t2);
    */

    /*
    // Task 5
    Tree* t = new Tree(5, new Tree(3, new Tree(1), new Tree(4)), new Tree(6, nullptr, new Tree(7)));
    std::cout << KthSmallestElementBST(t, 3);
    freeTree(t);
    */

    /*
    // Task 6
    Tree* t = new Tree(5, new Tree(3, new Tree(1), new Tree(4)), new Tree(6, nullptr, new Tree(7)));
    Tree* t2 = deserializeBST( serializeBST(t) );
    printTree(t2);
    freeTree(t);
    free(t2);
    */

    /*
    // Task 7
    List* l = new List(1, new List(2, new List(3, new List(4, new List(5)))));
    Tree* t = buildFromList(l);
    printTree(t);
    freeTree(t);
    freeList(l);
    */

    /*
    // Task 8
    Tree* t = new Tree(5, new Tree(3, new Tree(1), new Tree(4)), new Tree(6, nullptr, new Tree(7)));
    Tree* t2 = findElem(t, 3);
    printTree(t2);
    freeTree(t);
    */

    /*
    // Task 9
    Tree* t1 = new Tree(5, new Tree(3, new Tree(1), new Tree(4)), new Tree(6, nullptr, new Tree(7)));
    Tree* t2 = insertIntoBST(t1, 2);
    printTree(t2);
    freeTree(t1);
    */
}
