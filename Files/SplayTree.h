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
		Node<T1, T2> *parent;
		Node(T1 key = T1(), T2 data = T2(), Node<T1, T2> *parent = nullptr, Node<T1, T2> *leftChild = nullptr, Node<T1, T2> *rightChild = nullptr)
		{
			this->key = key;
			this->data = data;
			this->leftChild = leftChild;
			this->rightChild = rightChild;
			this->parent = parent;
		}
	};
	Node<T1, T2> *root;
public:
	SplayTree();
	~SplayTree();
	inline Node<T1, T2> *Parent(Node<T1, T2> *node)
	{
		if (node != root && node != nullptr)
			return node->parent;
		else
			return nullptr;
	}
	void Add(T1 key, T2 elem);
	void Add(Node<T1, T2> *&node, Node<T1, T2> *parent, T1 key, T2 elem);
	void RotateRight(Node<T1, T2> *&node);
	void RotateLeft(Node<T1, T2> *&node);
	void Splay(Node<T1, T2> *node);
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
		Add(root, nullptr, key, elem);
}

template <typename T1, typename T2>
void SplayTree<T1, T2>::Add(Node<T1, T2> *&node, Node<T1, T2> *parent,T1 key, T2 elem)
{
	if (node == nullptr)
	{
		node = new Node<T1, T2>(key, elem, parent);
		Splay(node); //bring new node to the root
	}
	else if (key < node->key)
		Add(node->leftChild, node, key, elem);
	else if (key > node->key)
		Add(node->rightChild, node, key, elem);
	else
	{
		node->data = elem;
		Splay(node);
		return;
	}
}

template<typename T1, typename T2>
void SplayTree<T1, T2>::RotateRight(Node<T1, T2>* &node)
{
	if (node->leftChild == nullptr)
		return;
	Node<T1, T2> *temp = node->leftChild; // changing pointers
	node->leftChild = temp->rightChild;
	temp->rightChild = node;
	if (node->parent == nullptr)// -------------------changing parents
	{
		node->parent = temp;
		temp->parent = nullptr;
	}
	else
	{
		temp->parent = node->parent;
		node->parent = temp;
	}
	if (node != root) 
	{
		if (node->leftChild != nullptr)
			node->leftChild->parent = node;
		node = temp; // now node its child
		if (node->key > root->key) // depends on in which part (left or right relatively to the root) is node
			node->parent->rightChild = node;
		else
			node->parent->leftChild = node;
	}
	else
	{
		if (temp->rightChild->leftChild != nullptr)
			temp->rightChild->leftChild->parent = temp->rightChild;
		root = temp; //now node its child
	}
	// -------------------changing parents
}

template<typename T1, typename T2>
void SplayTree<T1, T2>::RotateLeft(Node<T1, T2>*& node)
{
	if (node->rightChild == nullptr)
		return;
	Node<T1, T2> *temp = node->rightChild; //changing pointers
	node->rightChild = temp->leftChild;
	temp->leftChild = node;
	if (node->parent == nullptr) // -------------------changing parents
	{
		node->parent = temp;
		temp->parent = nullptr;
	}
	else
	{
		temp->parent = node->parent;
		node->parent = temp;
	}
	if (node != root) 
	{
		if (node->rightChild != nullptr)
			node->rightChild->parent = node;
		node = temp; //now node its child
		if (node->key < root->key) // depends on in which part (left or right relatively to the root) is node
			node->parent->leftChild = node;
		else
			node->parent->rightChild = node;
	}
	else
	{
		if (temp->leftChild->rightChild != nullptr)
			temp->leftChild->rightChild->parent = temp->leftChild;
		root = temp; //now node its child
	}
	// -------------------changing parents
}

template<typename T1, typename T2>
void SplayTree<T1, T2>::Splay(Node<T1, T2>* node)
{
	while (Parent(node) != nullptr)
	{
		Node<T1, T2>* parent = Parent(node);
		Node<T1, T2>* gparent = Parent(parent);
		if (node == parent->leftChild)
		{
			if (gparent == nullptr)
				RotateRight(parent); //Zig
			else if (parent == gparent->leftChild)
			{
				RotateRight(gparent); //Zig-Zig
				RotateRight(parent);
			}
			else
			{
				RotateRight(parent); //Zig-Zag
				RotateLeft(gparent);
			}
		}
		else
		{
			if (gparent == nullptr)
				RotateLeft(parent); //Zig
			else if (parent == gparent->rightChild)
			{
				RotateLeft(gparent); //Zig-Zig
				RotateLeft(parent);
			}
			else
			{
				RotateLeft(parent); //Zig-Zag
				RotateRight(gparent);
			}
		}
	}
}




