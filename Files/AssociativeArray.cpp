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
};

int main()
{

	system("pause");
	return 0;
}