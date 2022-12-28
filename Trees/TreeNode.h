#include <iostream>

template <typename T>
struct Node {
	T data;
	Node<T>* left;
	Node<T>* right;

	Node(const T& d, Node<T>* l = nullptr, Node<T>* r = nullptr) : data{ d }, left{ l }, right{ r } {}
};

template <typename T>
void freeTree(Node<T>* root)
{
	if (root == nullptr)
		return;

	freeTree(root->left);
	freeTree(root->right);

	delete root;
}

template<class T>
void printBT(const std::string& prefix, const Node<T>* node, bool isLeft) {
	if (node != nullptr) {
		std::cout << prefix;

		std::cout << (isLeft ? "|--" : "`--");

		std::cout << node->data << std::endl;

		printBT(prefix + (isLeft ? "|   " : "    "), node->left, true);
		printBT(prefix + (isLeft ? "|   " : "    "), node->right, false);
	}
}

template<class T>
void printTree(const Node<T>* node) {
	printBT("", node, false);
}
