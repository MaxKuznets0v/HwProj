#include <iostream>
using namespace std;

template <typename T>
class List
{
	template <typename T>
	class Node
	{
	public:
		T data; 
		Node *next;
		Node(T data = T(), Node *next = nullptr)
		{
			this->data = data;
			this->next = next;
		}
	};

	int size; //List size
	Node<T> *head; //The first list element
public:
	//Constructor
	List();
	//Destructor (frees the memory)
	~List();
	//Returns list size
	inline int GetSize();
	//Places element at the start of the list
	void push_back(T data);
	//Places element at the end of the list
	void push_front(T data);
	//Places element at the user's index of the list
	void insert(T data, int index);
	//Deletes element at the start of the list
	void pop_front();
	//Deletes element at the end of the list
	void pop_back();
	//Deletes element at the user's index of the list
	void removeAt(int index);
	//TODO: void sort();
	//Operator [] overloading
	T & operator[] (int index);
	//Reserves (size) cells, only if list is empty
	inline void reserve(int size);
	//Checks whether list is empty
	inline bool isEmpty();
	//Checks whether element is in list
	bool isInList(T elem);
};

template <typename T>
List<T>::List() //Default
{
	size = 0;
	head = nullptr;
}

template<typename T>
List<T>::~List()
{
	while (size)
		pop_front();
}

template <typename T>
inline int List<T>::GetSize()
{
	return size;
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
		head = new Node<T>(data);
	else
	{
		Node<T> *current = head;
		while (current->next != nullptr)
			current = current->next;
		current->next = new Node<T>(data);
	}
	size++;
}

template<typename T>
void List<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	size++;
}

template<typename T>
void List<T>::insert(T data, int index)
{
	if (head == nullptr)
		head = new Node<T>(data);
	else if (index == 0)
	{
		push_front(data);
		size--; //Decr since push_front already has incr
	}
	else
	{
		Node<T> *another = head;
		for (int i = 0; i < index - 1; i++)
			another = another->next;
		Node<T> *newN = new Node<T>(data, another->next);
		another->next = newN;
	}
	size++;
}

template<typename T>
void List<T>::pop_front()
{
	Node<T> *temp = head;
	head = head->next;
	delete temp;
	size--;
}

template<typename T>
void List<T>::pop_back()
{
	Node<T> *current = head;
	while (current->next != nullptr)
		current = current->next;
	delete current;
	size--;
}

template<typename T>
void List<T>::removeAt(int index)
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

template <typename T>
T & List<T>::operator[](int index)
{
	int count = 0;
	Node<T> *current = head;

	while (current != nullptr)
	{
		if (count == index)
			return current->data;
		else
		{
			current = current->next;
			count++;
		}
	}
}

template<typename T>
inline void List<T>::reserve(int size)
{
	if (head == nullptr)
		for (int i = 0; i < size; i++)
			push_front(T());
	else
		return;
}

template<typename T>
inline bool List<T>::isEmpty()
{
	if (head != nullptr)
		return false;
	else
		return true;
}

template<typename T>
bool List<T>::isInList(T elem)
{
	Node<T> *current = head;
	while (current != nullptr)
	{
		if (current->data == elem)
			return true;
		else
			current = current->next;
	}
	return false;
}
