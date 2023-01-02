#include <iostream>
#include "Tree.hpp"
#include <vector>
#include<string>
#include "ListNode.hpp"
#include <cassert>

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

// Задача десета
// Лава и дяна ротация на дърво

void rotateLeft(Node<int>*& root)
{
    assert(root->right != nullptr);

    Node<int>* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;

    root = newRoot;
}

void rotateRight(Node<int>*& root)
{
    assert(root->left != nullptr);

    Node<int>* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;

    root = newRoot;
}

// Задача (За домашно)
// Нека имаме двоично наредено дърво T от цели числа.

// pred(x) = max{ y | y е ключ на възел в Т и y < x } // Предшественик
// succ(x) = min{ y | y е ключ на възел в T и y > x } // Наследник
// Да се реализира pred(t, x) и succ(t, x).Бележка: Не е нужно х да се съдържа в дървото.

void predRec(Node<int>* root, int x, int& max)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->data == x)
    {
        return;
    }

    if (root->data > x)
    {
        if (root->data > max)
            max = root->data;

        // std::cout << root->data << " " << max << std::endl;
        predRec(root->left, x, max);
    }

    if (root->data < x)
    {
        if (root->data > max)
            max = root->data;

        // std::cout << root->data << " " << max << std::endl;
        predRec(root->right, x, max);
    }
}

int pred(Node<int>* root, int x)
{
    int max = INT_MIN;
    predRec(root, x, max);
    if (max == INT_MIN)
    {
        std::cout << "No predecessors!" << std::endl;
        return int();
    }
    return max;
}

void findMinRec(Node<int>* root, int& min)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->data < min)
    {
        min = root->data;
    }

    findMinRec(root->left, min);
}

void succRec(Node<int>* root, int x, int& min)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->data == x)
    {
        min = root->data;
        succRec(root->right, x, min);
    }

    if (root->data > x)
    {
        if (root->data > min)
        {
            min = root->data;
            findMinRec(root->left, min);
            return;
        }
            
        // std::cout << root->data << " " << min << std::endl;
        succRec(root->left, x, min);
    }

    if (root->data < x)
    {
        if (root->data > min)
        {
            min = root->data;
            findMinRec(root->left, min);
            return;
        }
         
        // std::cout << root->data << " " << min << std::endl;
        succRec(root->right, x, min);
    }
}

int succ(Node<int>* root, int x)
{
    int min = INT_MAX;
    succRec(root, x, min);
    if (min == INT_MAX || min == x)
    {
        std::cout << "No successors!" << std::endl;
        return int();
    }
    return min;
}

// Задача (Контролно)
// Да се напише функция, която намира сумата на всички елементи на двоично наредено дърво от цели числа, 
// които имат нечетен брой наследници в интервала[x, y](т.е.сумата на броя елементи в лявото поддърво 
// и броя елементи в дясното поддърво в интервала[x, y] е нечетно число).Нека x и y са параметри на функцията.

void sumPrimeSuccRec(Node<int>* root, int x, int y, int& cnt)
{
    if (root == nullptr)
        return;

    // std::cout<<root->data<<std::endl;
    if (root->data >= x && root->data <= y)
    {
        //std::cout << root->data << std::endl;
        cnt++;
    }

    if (root->data <= y)
    {
        sumPrimeSuccRec(root->left, x, y, cnt);
    }
    if (root->data >= x)
    {
        sumPrimeSuccRec(root->right, x, y, cnt);
    }
}

bool isPrime(int n)
{
    if (n <= 1)
        return false;
    else if (n == 2)
        return true;

    double temp = sqrt(n);
    for (int i = 2; i <= temp; i++)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}

void rec(Node<int>* root, int x, int y, int& sum)
{
    if (root == nullptr)
    {
        return;
    }

    int cnt = 0;
    sumPrimeSuccRec(root, x, y, cnt);
    if (root->data >= x && root->data <= y)
        cnt--;

    if (isPrime(cnt))
    {
        sum += root->data; 
        std::cout << root->data << " " << cnt << " " << sum << std::endl;
    }
    rec(root->left, x, y, sum);
    rec(root->right, x, y, sum);
}

int sumPrimeSucc(Node<int>* root, int x, int y)
{
    int sum = 0;
    rec(root, x, y, sum);
    return sum;
}

// Да се напише функция, която приема двоично/произволно дърво и връща височината му.

int heightTree(Node<int>* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    int heightLeft = 1 + heightTree(root->left);
    int heightRight = 1 + heightTree(root->right);
    return std::max(heightLeft, heightRight) - 1;
}

// Да се напише функция, която приема двоично / произволно дърво с n върха и проверява дали числата от 1 до n се срещат точно веднъж в дървото.

void findNElementsRec(Node<int>* root, int n, std::vector<int>& v)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->data >= 1 && root->data <= n)
        v[root->data - 1]++;

    findNElementsRec(root->left, n, v);
    findNElementsRec(root->right, n, v);
}

bool findNelements(Node<int>* root, int n)
{
    std::vector<int> v = std::vector<int>(n);;
    for (int i = 0; i < n; i++)
    {
        v[i] = 0;
    }
    findNElementsRec(root, n, v);
    for (int i = 0; i < n; i++)
    {
        if (v[i] != 1)
            return false;
    }
    return true;
}

// Да се напише функция, която приема двоично / произволно дърво и връща всички думи, които са получени от корена до някое листо.

void allWordsRec(Node<char>* root, std::string curr, std::vector<std::string>& v)
{
    if (root == nullptr)
    {
        return;
    }

    curr += root->data;
    if (root->left == nullptr && root->right == nullptr)
    {
        v.push_back(curr);
    }

    allWordsRec(root->left, curr, v);
    allWordsRec(root->right, curr, v);
}

std::vector<std::string> allWords(Node<char>* root)
{
    std::vector<std::string> v;
    allWordsRec(root, "", v);
    return v;
}

// Да се напише функция, която приема двоично/произволно дърво, чиито елементи са символи и цяло число к и отпечатва думата на к-тото ниво на дървото.

void wordKLevel(Node<char>* root, int k, std::string& str, int currLevel)
{
    if (root == nullptr)
        return;

    if (currLevel == k)
    {
        str += root->data;
        return;
    }

    wordKLevel(root->left, k, str, currLevel + 1);
    wordKLevel(root->right, k, str, currLevel + 1);
}

std::string wordKLevel(Node<char>* root, int k)
{
    std::string str = "";
    wordKLevel(root, k, str, 0);
    return str;
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

    // Task 10
    /*
    Tree* t = new Tree(5, new Tree(3, new Tree(1), new Tree(4)), new Tree(6, nullptr, new Tree(7)));
    rotateRight(t);
    printTree(t);
    freeTree(t);
    */

    // Task 11
    /*
    Tree* t = new Tree(5, new Tree(3, new Tree(1), new Tree(4)), new Tree(8, new Tree(6), new Tree(9, nullptr, new Tree(10))));
    std::cout << succ(t, 4);
    freeTree(t);
    */

    // Task 12 
    /*
    Tree* t = new Tree(5, new Tree(3, new Tree(1), new Tree(4)), new Tree(8, new Tree(6), new Tree(9, nullptr, new Tree(10))));
    std::cout << sumPrimeSucc(t,1,10);
    freeTree(t);
    */

    // Task 13
    /*
    Tree* t = new Tree(5, new Tree(3, new Tree(1), new Tree(4)), new Tree(8, new Tree(6), new Tree(9, nullptr, new Tree(10))));
    std::cout << heightTree(t);
    freeTree(t);
    */

    // Task 14
    /*
    Tree* t = new Tree(5, new Tree(3, new Tree(1, nullptr, nullptr), new Tree(4)), new Tree(7, new Tree(6), new Tree(8, nullptr, new Tree(9))));
    std::cout << findNelements(t, 9);
    freeTree(t);
    */

    // Task 15
    /*
    Node<char>* t = new Node<char>('a', new Node<char>('b', new Node<char>('b'), new Node<char>('c', new Node<char>('d'), new Node<char>('e'))), new Node<char>('f', new Node<char>('g')));
    std::vector<std::string> v = allWords(t);
    printTree(t);
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    freeTree(t);
    */

    // Task 16
    /*
    Node<char>* t = new Node<char>('a', new Node<char>('b', new Node<char>('b'), new Node<char>('c', new Node<char>('d'), new Node<char>('e'))), new Node<char>('f', new Node<char>('g')));
    printTree(t);
    std::cout << wordKLevel(t, 2);
    freeTree(t);
    */
}
