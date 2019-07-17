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
	void Add(T1 key, T2 elem);
	void Add(Node<T1, T2> *&node, T1 key, T2 elem);
	void RotateLeft(Node<T1, T2> *node);
	void RotateRight(Node<T1, T2> *node);
	void Splay(Node<T1, T2> *node, Node<T1, T2> *parent);
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
void SplayTree<T1, T2>::Add(T1 key, T2 elem)
{
	if (root == nullptr)
		root = new Node<T1, T2>(key, elem);
	else
		Add(root, key, elem);
}

template <typename T1, typename T2>
void SplayTree<T1, T2>::Add(Node<T1, T2> *&node, T1 key, T2 elem)
{
	if (node == nullptr)
		node = new Node<T1, T2>(key, elem);
	else if (key < node->key)
		Add(node->leftChild, key, elem);
	else
		Add(node->rightChild, key, elem);
	Splay(node, root);
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

template<typename T1, typename T2>
void SplayTree<T1, T2>::Splay(Node<T1, T2>* node, Node<T1, T2>* parent)
{
	if (node == root)
		return;
	else
	{
		if (parent->leftChild == node)
			RotateRight(parent);
		else if (parent->rightChild == node)
			RotateLeft(parent);
		Splay(node, root);
	}
}


