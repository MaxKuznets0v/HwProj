#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename T>
class BinTree
{
	template <typename T>
	class Node
	{
	public:
		T data;
		Node<T> *leftChild;
		Node<T> *rightChild;
		Node(T data = T(), Node<T> *leftChild = nullptr, Node<T> *rightChild = nullptr)
		{
			this->data = data;
			this->leftChild = leftChild;
			this->rightChild = rightChild;
		}
	};
	Node<T> *root; // the head element
	T str; // string - arithmetic expression
	int res; // the result of the str
	void GetStr(); // takes data from the file
	T FindTemp(int &from); // finds current element for GrowTree()
	void GrowTree(Node<T> *&node, T elem, int &from); // builds tree
	void CountNumber(Node<T>* node); // counts a node with two leaves and frees memory
public:
	BinTree(); // constructor
	inline void AddOperator(Node<T> *&node, T elem); // adds operator into the tree
	void AddNumber(Node<T> *node, T elem); // adds number into the tree
	void GrowTree(T elem); // builds tree taking the string
	inline T label(Node<T> *node); // returns node data
	void PreOrderTraversal(); // prints the tree from the root
	void PreOrderTraversal(Node<T> *node); // prints the tree from a specific node
	inline bool isOperator(Node<T> *node); // checks whether element in node is an operator
	inline bool isNumber(Node<T> *node); // checks whether element in node is a number 
	inline bool isNumber(char temp); // checks whether char element is a number 
	inline int GetRes(); // returns result
};

template <typename T>
BinTree<T>::BinTree()
{
	root = nullptr;
	res = int();
	GetStr();
	GrowTree(str);
}

template <typename T>
inline void BinTree<T>::AddOperator(Node<T> *&node, T elem)
{
	if (root == nullptr)
	{
		root = new Node<T>(elem);
		node = root;
	}
	else
		node = new Node<T>(elem);
}

template <typename T>
void BinTree<T>::AddNumber(Node<T> *node, T elem)
{
	if (node->leftChild == nullptr)
		node->leftChild = new Node<T>(elem);
	else
		node->rightChild = new Node<T>(elem);
}

template <typename T>
void BinTree<T>::GrowTree(T elem)
{
	int index = 0;
	while (elem.at(index) != '(')
		index++;
	index++;
	GrowTree(root, elem, index);
}

template<typename T>
inline T BinTree<T>::label(Node<T>* node)
{
	return node->data;
}

template<typename T>
void BinTree<T>::GetStr()
{
	ifstream inp;
	inp.open("C:\\Maxim\\Visual Studio\\Projects\\HwProj\\input(TreeExpression).txt");
	getline(inp, str);
	inp.close();
}

template <typename T>
void BinTree<T>::GrowTree(Node<T> *&node, T elem, int &from)
{
	string temp;
	for (from; from < elem.length(); from++)
	{
		temp = FindTemp(from);
		if (temp == "(")
		{
			if (node->leftChild == nullptr)
				GrowTree(node->leftChild, elem, ++from);
			else
				GrowTree(node->rightChild, elem, ++from);
		}
		else if (temp == ")")
			break;
		else if ((temp == "*") || (temp == "/") || (temp == "+") || (temp == "-"))
			AddOperator(node, temp);
		else if (temp != " ")
			AddNumber(node, temp);
	}
}

template<typename T>
void BinTree<T>::PreOrderTraversal()
{
	Node<T> *node = root;
	if (node != nullptr)
	{
		cout << "( ";
		cout << label(node) << " ";
		PreOrderTraversal(node->leftChild);
		PreOrderTraversal(node->rightChild);
		cout << ")";
		CountNumber(node);
		res = stoi(node->data);
		delete node;
	}
}

template<typename T>
void BinTree<T>::PreOrderTraversal(Node<T> *node)
{
	if (node != nullptr)
	{
		if (isOperator(node))
			cout << "( ";
		cout << label(node) << " ";
		PreOrderTraversal(node->leftChild);
		PreOrderTraversal(node->rightChild);
		int count = 0;
		if (!isNumber(node))
		{
			if (isNumber(node->leftChild))
				count++;
			if (isNumber(node->rightChild))
				count++;
		}
		if (count == 2)
		{
			cout << ") ";
			CountNumber(node);
		}
	}
}

template<typename T>
inline bool BinTree<T>::isOperator(Node<T>* node)
{
	T temp = label(node);
	if (temp == "*" || temp == "/" || temp == "+" || temp == "-")
		return true;
	else
		return false;
}

template<typename T>
inline bool BinTree<T>::isNumber(Node<T>* node)
{
	T temp = label(node);
	if (temp != "*" && temp != "/" && temp != "+" && temp != "-")
		return true;
	else
		return false;
}

template<typename T>
inline bool BinTree<T>::isNumber(char temp)
{
	if (temp != '*' && temp != '/' && temp != '+' && temp != '-' && temp != ' ' && temp != '(' && temp != ')')
		return true;
	else
		return false;
}

template<typename T>
T BinTree<T>::FindTemp(int & from)
{
	string temp;
	temp = str.at(from);
	for (from; from < str.length() - 1; from++)
	{
		if (isNumber(str.at(from)) && isNumber(str.at(from + 1)))
		{
			temp += str.at(from + 1);
		}
		else
			break;
	}
	return temp;
}

template<typename T>
void BinTree<T>::CountNumber(Node<T>* node)
{
	int cur;
	string temp = label(node);

	if (temp == "+")
		cur = stoi(node->leftChild->data) + stoi(node->rightChild->data);
	else if (temp == "-") 
		cur = stoi(node->leftChild->data) - stoi(node->rightChild->data);
	else if (temp == "*")
		cur = stoi(node->leftChild->data) * stoi(node->rightChild->data);
	else
		cur = stoi(node->leftChild->data) / stoi(node->rightChild->data);
	delete node->leftChild;
	delete node->rightChild;
	node->data = to_string(cur);
}

template<typename T>
inline int BinTree<T>::GetRes()
{
	return res;
}


int main()
{
	BinTree<string> counter;
	counter.PreOrderTraversal();
	cout << " = " << counter.GetRes() << endl;
	system("pause");
	return 0;
}