#include <iostream>
using namespace std;

template <typename T>
class BinarySearchTree
{
	template <typename T>
	class Node
	{
	public:
		Node(T data = T(), Node<T> *leftChild = nullptr, Node<T> *rightChild = nullptr)
		{
			this->data = data;
			this->leftChild = leftChild;
			this->rightChild = rightChild;
		}
		T data;
		Node<T> *leftChild; // less than node value
		Node<T> *rightChild; // more than node value
	};
	Node<T> *root; // the head element
public:
	BinarySearchTree(); //constructor
	~BinarySearchTree(); //destructor (frees memory)
	inline T label(Node<T> *node); // shows node's data
	inline Node<T> *Min(Node<T> *node) // finds minimum element from a specific node
	{
		while (node->leftChild != nullptr)
			node = node->leftChild;
		return node;
	}
	inline Node<T> *Max(Node<T> *node) // finds maximum element from a specific node
	{
		while (node->rightChild != nullptr)
			node = node->rightChild;
		return node;
	}
	Node<T> *Parent(Node<T> *&node, T elem) //finds a parent to an element
	{
		if (node == root)
			return root;
		Node<T> *current = root;
		while (true)
		{
			if (elem < label(current))
			{
				if (current->leftChild == node)
					return current;
				if (current->leftChild != nullptr)
					current = current->leftChild;
				else
					return nullptr;
			}
			else if (elem > label(current))
			{
				if (current->rightChild == node)
					return current;
				if (current->rightChild != nullptr)
					current = current->rightChild;
				else
					return nullptr;
			}
			else
			{
				if (current->rightChild == node)
					return current;
				if (current->leftChild == node)
					return current;
				if (current->rightChild != nullptr)
					current = current->rightChild;
				else
					return nullptr;
			}
		}
	}
	inline bool IsChild(Node<T> *parent, Node<T> *child);
	void Add(T elem); // adds an element from the root
	void Add(Node<T> *&node, T elem); // adds an element from a specific node
	bool IsInSet(T elem); // checks whether element is in set from the root
	bool IsInSet(Node<T> *node, T elem); // checks whether element is in set from a specific node
	void Remove(T elem); // removes element from the root
	void Remove(Node<T> *&node, T elem); // removes element from a specific node
	void InOrderTraversal(Node<T> *node); // left tree, root, right tree from a specific node
	void PostOrderTraversal(Node<T> *node); // left tree, right tree, root from a specific node
	void PreOrderTraversal(Node<T> *node); // root, left tree, right tree from a specific node
	void InReverseOrderTraversal(Node<T> *node); // from the biggest to the lowest from a specific node
	void InOrderTraversal(); // left tree, root, right tree from the root
	void PostOrderTraversal(); // left tree, right tree, root from the root
	void PreOrderTraversal(); // root, left tree, right tree from the root
	void InReverseOrderTraversal(); // from the biggest to the lowest from the root
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	root = nullptr;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	while (root != nullptr)
		Remove(root, label(root));
}

template<typename T>
inline T BinarySearchTree<T>::label(Node<T>* node)
{
	return node->data;
}

template<typename T>
inline bool BinarySearchTree<T>::IsChild(Node<T>* parent, Node<T>* child)
{
	if (label(child) == label(parent))
		return true;
	else
		return false;
}

template<typename T>
void BinarySearchTree<T>::Add(T elem)
{
	if (root == nullptr)
		root = new Node<T>(elem);
	else
		Add(root, elem);
		//Non-recursive realisation
		/*
		Node<T> *current = root;
		while (true)  
		{
			if (elem < current->data)
			{
				if (current->leftChild != nullptr)
					current = current->leftChild;
				else
				{
					current->leftChild = new Node<T>(elem);
					break;
				}
			}
			else
			{
				if (current->rightChild != nullptr)
					current = current->rightChild;
				else
				{
					current->rightChild = new Node<T>(elem);
					break;
				}
			}
		}*/
}

template <typename T>
void BinarySearchTree<T>::Add(Node<T> *&node, T elem)
{
	if (node == nullptr)
		node = new Node<T>(elem);
	else if (elem < label(node))
		Add(node->leftChild, elem);
	else
		Add(node->rightChild, elem);
}

template <typename T>
bool BinarySearchTree<T>::IsInSet(T elem)
{
	if (root == nullptr)
		return false;
	else
		IsInSet(root, elem);
		//Non-recursive realisation
		/*Node<T> *current = root;
		while (true)
		{
			if (elem < current->data)
			{
				if (current->leftChild != nullptr)
					current = current->leftChild;
				else
					return false;
			}
			else if (elem > current->data)
			{
				if (current->rightChild != nullptr)
					current = current->rightChild;
				else
					return false;
			}
			else
				return true;
		}*/
}

template<typename T>
bool BinarySearchTree<T>::IsInSet(Node<T>* node, T elem)
{
	if (node == nullptr)
		return false;
	if (elem < label(node))
		IsInSet(node->leftChild, elem);
	else if (elem > label(node))
		IsInSet(node->rightChild, elem);
	else
		return true;
}

template <typename T>
void BinarySearchTree<T>::Remove(T elem)
{
	if (root == nullptr)
		return;
	else
		Remove(root, elem);
	// Not finished non-recursive realisation
	/*Node<T> *current = root;
	while (true)
	{
		if (elem < current->data)
		{
			if (current->leftChild != nullptr)
				current = current->leftChild;
			else
			{
				cout << "Element " << elem << " is not in set!\n";
				return;
			}
		}
		else if (elem > current->data)
		{
			if (current->rightChild != nullptr)
				current = current->rightChild;
			else
			{
				cout << "Element " << elem << " is not in set!\n";
				return;
			}
		}
		else
		{
			if (current->leftChild == nullptr && current->rightChild == nullptr)

			break;
		}
	}*/
}

template<typename T>
void BinarySearchTree<T>::Remove(Node<T>* &node, T elem)
{
	if (node == nullptr)
		return;
	if (elem < label(node))
		Remove(node->leftChild, elem);
	else if (elem > label(node))
		Remove(node->rightChild, elem);
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
				Node<T> *temp = node->leftChild;
				delete node;
				node = temp;
			}
			else
			{
				Node<T> *temp = node->rightChild;
				delete node;
				node = temp;
			}
		}
		else
		{
			Node<T> *temp = Min(node->rightChild);
			Node<T> *parent = Parent(temp, label(temp));
			node->data = label(temp);
			if (IsChild(parent->leftChild, temp))
				Remove(parent->leftChild, label(parent->leftChild));
			else
				Remove(parent->rightChild, label(parent->rightChild));
		}
	}
}

template<typename T>
void BinarySearchTree<T>::InOrderTraversal(Node<T> *node)
{
	if (node != nullptr)
	{
		InOrderTraversal(node->leftChild);
		cout << label(node) << " ";
		InOrderTraversal(node->rightChild);
	}
}

template<typename T>
void BinarySearchTree<T>::PostOrderTraversal(Node<T> *node)
{
	if (node != nullptr)
	{
		PostOrderTraversal(node->leftChild);
		PostOrderTraversal(node->rightChild);
		cout << label(node) << " ";
	}
}

template<typename T>
void BinarySearchTree<T>::PreOrderTraversal(Node<T> *node)
{
	if (node != nullptr)
	{
		cout << label(node) << " ";
		PreOrderTraversal(node->leftChild);
		PreOrderTraversal(node->rightChild);
	}
}

template<typename T>
void BinarySearchTree<T>::InReverseOrderTraversal(Node<T>* node)
{
	if (node != nullptr)
	{
		InReverseOrderTraversal(node->rightChild);
		cout << label(node) << " ";
		InReverseOrderTraversal(node->leftChild);
	}
}

template<typename T>
void BinarySearchTree<T>::InOrderTraversal()
{
	Node<T> *node = root;
	if (node != nullptr)
	{
		InOrderTraversal(node->leftChild);
		cout << label(node) << " ";
		InOrderTraversal(node->rightChild);
	}
}

template<typename T>
void BinarySearchTree<T>::PostOrderTraversal()
{
	Node<T> *node = root;
	if (node != nullptr)
	{
		PostOrderTraversal(node->leftChild);
		PostOrderTraversal(node->rightChild);
		cout << label(node) << " ";
	}
}

template<typename T>
void BinarySearchTree<T>::PreOrderTraversal()
{
	Node<T> *node = root;
	if (node != nullptr)
	{
		cout << label(node) << " ";
		PreOrderTraversal(node->leftChild);
		PreOrderTraversal(node->rightChild);
	}
}

template<typename T>
void BinarySearchTree<T>::InReverseOrderTraversal()
{
	Node<T> *node = root;
	if (node != nullptr)
	{
		InReverseOrderTraversal(node->rightChild);
		cout << label(node) << " ";
		InReverseOrderTraversal(node->leftChild);
	}
}
