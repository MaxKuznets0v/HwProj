#include <iostream>
using namespace std;

template <typename T>
class CircleList
{
	template <typename T>
	class Node
	{
	public:
		Node(T data = T(), Node *next = nullptr)
		{
			this->data = data;
			this->next = next;
		}
		T data;
		Node<T> *next;
	};
	int size; //List size
	Node<T> *head; //The first list element
public:
	//Constructor
	CircleList();
	//Destructor (frees memory)
	~CircleList();
	//Places element at the start of the list
	void push_back(T data);
	//Deletes element at the start of the list
	void pop_front();
	//Deletes element at the user's index of the list
	void removeAt(int index);
	//Returns list size
	inline int GetSize();
	//Operator [] overloading
	T & operator[] (int index);
};

template <typename T>
CircleList<T>::CircleList()
{
	size = 0;
	head = nullptr;
}

template <typename T>
CircleList<T>::~CircleList()
{
	while (size)
		pop_front();
}

template<typename T>
void CircleList<T>::push_back(T data)
{
	if (head == nullptr)
	{
		Node<T> *temp = new Node<T>;
		head = temp;
		head->data = data;
		head->next = head;
	}
	else
	{
		Node<T> *current = head;
		while (current->next != head)
			current = current->next;
		current->next = new Node<T>(data, head);
	}
	size++;
}

template<typename T>
void CircleList<T>::pop_front()
{
	Node<T> *temp = head;
	if (size != 1)
		head = head->next;
	else
		head = nullptr;
	delete temp;
	size--;
}

template<typename T>
void CircleList<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
		size++;
	}
	else
	{
		Node<T> *another = head;
		for (int i = 0; i < index - 1; i++)
			another = another->next;
		Node<T> *temp = another->next;
		another->next = temp->next;
		delete temp;
	}
	size--;
}

template<typename T>
inline int CircleList<T>::GetSize()
{
	return size;
}

template<typename T>
T & CircleList<T>::operator[](int index)
{
	int count = 0;
	Node<T> *current = head;
	while (current->next != head)
	{
		if (count == index)
			break;
		else
			{
				current = current->next;
				count++;
			}
	}
	return current->data;
}

int safePosition(int n, int m)
{
	CircleList<int> list;
	for (int i = 0; i < n; i++)
		list.push_back(i + 1);
	int i = (m - 1) % list.GetSize(); //since list starts with 0 index
	while (list.GetSize() != 1)
	{
		list.removeAt(i);
		i = (i + m - 1) % list.GetSize(); // minus 1 since we deleted 1 person
	}
	return list[0];
}

int main()
{
	int n, m;
	cout << "Enter amount of people: ";
	cin >> n;
	cout << "Enter a step: ";
	cin >> m;
	cout << "Safe position is " << safePosition(n, m) << endl;
	system("pause");
	return 0;
}