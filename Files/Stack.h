#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Stack
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
	Node<T> *top;
	int size;
public:
	Stack();
	~Stack();
	inline int GetSize();
	void push(T data);
	void pop();
	inline T onTop();
};

template<typename T>
Stack<T>::Stack()
{
	size = 0;
	top = nullptr;
}

template<typename T>
Stack<T>::~Stack()
{
	while (size)
		pop();
}

template<typename T>
inline int Stack<T>::GetSize()
{
	return size;
}

template<typename T>
void Stack<T>::push(T data)
{
	top = new Node<T>(data, top);
	size++;
}

template<typename T>
void Stack<T>::pop()
{
	Node<T> *temp = top;
	top = temp->next;
	delete temp;
	size--;
}

template <typename T>
inline T Stack<T>::onTop()
{
	return top->data;
}

