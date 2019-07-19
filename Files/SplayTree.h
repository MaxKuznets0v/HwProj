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
	inline Node<T1, T2> *Min(Node<T1, T2> *node) // finds minimum element from a specific node
	{
		while (node->leftChild != nullptr)
			node = node->leftChild;
		return node;
	}
	inline Node<T1, T2> *Max(Node<T1, T2> *node) // finds maximum element from a specific node
	{
		while (node->rightChild != nullptr)
			node = node->rightChild;
		return node;
	}
	void Add(T1 key, T2 elem);
	void Add(Node<T1, T2> *&node, Node<T1, T2> *parent, T1 key, T2 elem);
	void RotateRight(Node<T1, T2> *&node);
	void RotateLeft(Node<T1, T2> *&node);
	void Splay(Node<T1, T2> *node);
	T2 Search(T1 key);
	bool IsKeyInArray(T1 key);
	void Remove(T1 key);
	void Remove(Node<T1, T2>*& node, T1 key);
};

template<typename T1, typename T2>
SplayTree<T1, T2>::SplayTree()
{
	root = nullptr;
}

template<typename T1, typename T2>
SplayTree<T1, T2>::~SplayTree()
{
	while (root != nullptr)
		Remove(root, root->key);
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

template<typename T1, typename T2>
T2 SplayTree<T1, T2>::Search(T1 key)
{
	Node<T1, T2> *current = root;
	while (current != nullptr)
	{
		if (key < current->key)
			current = current->leftChild;
		else if (key > current->key)
			current = current->rightChild;
		else
		{
			Splay(current);
			return current->data;
		}
	}
	return "";
}

template<typename T1, typename T2>
bool SplayTree<T1, T2>::IsKeyInArray(T1 key)
{
	Node<T1, T2> *current = root;
	while (current != nullptr)
	{
		if (key < current->key)
			current = current->leftChild;
		else if (key > current->key)
			current = current->rightChild;
		else
		{
			Splay(current);
			return true;
		}
	}
	return false;
}

template<typename T1, typename T2>
void SplayTree<T1, T2>::Remove(T1 key)
{
	if (root == nullptr)
		return;
	else
	{
		Remove(root, key);
		Node<T1, T2>* current = root;
		while (true) // loop finds deleted element's parent and splays it
		{
			if (current->key > key)
			{
				if (current->leftChild != nullptr)
					current = current->leftChild;
				else
					break;
			}
			else
			{
				if (current->rightChild != nullptr)
					current = current->rightChild;
				else
					break;
			}
		}
		Splay(current);
	}
}

template<typename T1, typename T2>
void SplayTree<T1, T2>::Remove(Node<T1, T2>*& node, T1 key)
{
	if (node == nullptr)
		return;
	if (key < node->key)
		Remove(node->leftChild, key);
	else if (key > node->key)
		Remove(node->rightChild, key);
	else
	{
		if (node->leftChild == nullptr && node->rightChild == nullptr)
		{
			delete node;
			node = nullptr;
		}
		else if (!(node->leftChild != nullptr) || !(node->rightChild != nullptr))
		{
			if (node->leftChild != nullptr)
			{
				Node<T1, T2> *temp = node->leftChild;
				temp->parent = node->parent;
				delete node;
				node = temp;
			}
			else
			{
				Node<T1, T2> *temp = node->rightChild;
				temp->parent = node->parent;
				delete node;
				node = temp;
			}
		}
		else
		{
			Node<T1, T2> *temp = Min(node->rightChild);
			Node<T1, T2> *parent = Parent(temp);
			node->data = temp->data;
			node->key = temp->key;
			if (parent->leftChild == temp)
				Remove(parent->leftChild, parent->leftChild->key);
			else
				Remove(parent->rightChild, parent->rightChild->key);
		}
	}
}