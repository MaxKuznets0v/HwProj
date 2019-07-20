#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "List.h"
using namespace std;

template <typename T>
class OurList
{
	template <typename T>
	class Node
	{
	public:
		T data;
		Node *next;
		int count = 0;
		Node(T data = T(), Node *next = nullptr)
		{
			this->data = data;
			this->next = next;
		}
	};
	Node<T> *head;
	int size;
public:
	OurList()
	{
		head = nullptr;
		size = 0;
	}
	~OurList()
	{
		while (size)
			pop_front();
	}
	void push_front(T data)
	{
		if (!isInList(data))
		{
			head = new Node<T>(data, head);
			size++;
			head->count++;
		}
		else
		{
			Node<T> *current = head;
			while (current->data != data)
				current = current->next;
			current->count++;
		}
	}
	void pop_front()
	{
		Node<T> *temp = head;
		head = head->next;
		delete temp;
		size--;
	}
	bool isInList(T elem)
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
	inline bool isEmpty()
	{
		if (head != nullptr)
			return false;
		else
			return true;
	}
	inline int GetSize()
	{
		return size;
	}
	T & operator[](int index)
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
	inline int Count(T elem)
	{
		Node<T> *current = head;
		while (current->data != elem)
			current = current->next;
		return current->count;
	}
};



template<typename T>
class Hash
{
	int hashSize;
	int param;
	List<OurList <T>> hashTable;
	int totalWords;
public:
	Hash(int size = 256, int param = 3); // 256 by default
	~Hash();
	int HashFunc(T elem);
	void Add(T elem);
	T MakeWord(T elem);
	void GetFile();
	void Results();
};

template <typename T>
Hash<T>::Hash(int size, int param)
{
	hashSize = size;
	this->param = param;
	hashTable.reserve(size);
	totalWords = 0;
}

template <typename T>
Hash<T>::~Hash()
{

}

template <typename T>
int Hash<T>::HashFunc(T str) // be sure that param and hashSize are relative prime 
{                                        // (otherwise doesn't work!!!)
	int hash = 0;
	for (int i = 0; str[i] != '\0'; i++)
		hash = (hash * param + (unsigned char)str[i]) % hashSize;
	return hash;
}

template<typename T>
void Hash<T>::Add(T elem)
{
	int index = HashFunc(elem);
	hashTable[index].push_front(elem);
	totalWords++;
}

template<typename T>
T Hash<T>::MakeWord(T temp)
{
	while (temp != "" && !((temp.at(temp.size() - 1) >= 'à' && temp.at(temp.size() - 1) <= 'ÿ') || (temp.at(temp.size() - 1) >= 'À' && temp.at(temp.size() - 1) <= 'ß') || (temp.at(temp.size() - 1) >= '0' && temp.at(temp.size() - 1) <= '9')))
		temp.pop_back();
	while (temp != "" && !((temp.at(0) >= 'à' && temp.at(0) <= 'ÿ') || (temp.at(0) >= 'À' && temp.at(0) <= 'ß') || (temp.at(0) >= '0' && temp.at(0) <= '9')) && temp != "")
		temp.erase(temp.begin());
	return temp;
}

template<typename T>
void Hash<T>::GetFile()
{
	fstream input;
	input.open("C:\\Maxim\\Repositories\\HwProj\\inputs\\input(HashTable).txt");
	while (!input.eof())
	{
		string temp;
		input >> temp;
		if (temp != "")
			temp = MakeWord(temp);
		if (temp != "")
			Add(temp);
	}
	input.close();
}

template<typename T>
void Hash<T>::Results()
{
	for (int i = 0; i < hashSize; i++)
	{
		if (!hashTable[i].isEmpty())
			for (int j = 0; j < hashTable[i].GetSize(); j++)
			{
				T temp = hashTable[i][j];
				cout << temp << ": " << hashTable[i].Count(temp) << endl;
			}
	}
	cout << "Words in total: " << totalWords << endl;
}

int main()
{
	SetConsoleOutputCP(1251);
	Hash<string> text;
	text.GetFile();
	text.Results();
	system("pause");
	return 0;
}