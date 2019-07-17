#include <iostream>
using namespace std;

template <typename T1, typename T2>
class SplayTree
{
	template <typename T1, typename T2>
	class Node
	{
	public:
		T1 key;
		T2 data;
		Node<T1, T2> *leftChild;
		Node<T1, T2> *rightChild;
		Node(T1 key = T1(), T2 data = T2(), Node<T1, T2> *leftChild = nullptr, Node<T1, T2> *rightChild = nullptr)
		{
			this->key = key;
			this->data = data;
			this->leftChild = leftChild;
			this->rightChild = rightChild;
		}
	};
	Node<T1, T2> *root;
public:
	SplayTree();
	~SplayTree();
	void Add(T2 elem);
	void Add(Node<T1, T2> *&node, T2 elem);
	void RotateLeft(Node<T1, T2> *node);
	void RotateRight(Node<T1, T2> *node);
};

template<typename T1, typename T2>
SplayTree<T1, T2>::SplayTree()
{
	root = nullptr;
}

template<typename T1, typename T2>
SplayTree<T1, T2>::~SplayTree()
{
	//TODO: free memory
}

template<typename T1, typename T2>
void SplayTree<T1, T2>::Add(T2 elem)
{
	if (root == nullptr)
		root = new Node<T>(elem);
	else
		Add(root, elem);
}

template <typename T1, typename T2>
void SplayTree<T1, T2>::Add(Node<T1, T2> *&node, T2 elem)
{
	if (node == nullptr)
		node = new Node<T>(elem);
	else if (elem < label(node))
		Add(node->leftChild, elem);
	else
		Add(node->rightChild, elem);
}

template<typename T1, typename T2>
void SplayTree<T1, T2>::RotateLeft(Node<T1, T2>* node)
{
	Node<T1, T2> *temp = node->rightChild;
	node->rightChild = temp->leftChild;
	temp->leftChild = node;
}

template<typename T1, typename T2>
void SplayTree<T1, T2>::RotateRight(Node<T1, T2>* node)
{
	Node<T1, T2> *temp = node->leftChild;
	node->leftChild = temp->rightChild;
	temp->rightChild = node;
}


