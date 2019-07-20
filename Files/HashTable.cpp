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
	class Node // typical list node but has a count field
	{
	public:
		T data;
		Node *next;
		int count = 0; // shows how word count
		Node(T data = T(), Node *next = nullptr)
		{
			this->data = data;
			this->next = next;
		}
	};
	Node<T> *head; // the head node
	int size; // list length 
public:
	OurList() // constructor
	{
		head = nullptr;
		size = 0;
	}
	~OurList() // destructor (frees memory)
	{
		while (size)
			pop_front();
	}
	void push_front(T data)
	{
		if (!isInList(data)) // if not on list - add
		{
			head = new Node<T>(data, head);
			size++;
			head->count++;
		}
		else // if in list increase count field
		{
			Node<T> *current = head;
			while (current->data != data)
				current = current->next;
			current->count++;
		}
	}
	void pop_front() // delete from the head
	{
		Node<T> *temp = head;
		head = head->next;
		delete temp;
		size--;
	}
	bool isInList(T elem) // checks whether element is in list
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
	inline bool isEmpty() // checks whether list is empty
	{
		if (head != nullptr)
			return false;
		else
			return true;
	}
	inline int GetSize() // returns list size
	{
		return size;
	}
	T & operator[](int index) // overloading [] operator
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
	inline int Count(T elem) // returns count field
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
	int hashSize; // size of array
	int param; // parameter that is used in HashFunc()
	List<OurList <T>> hashTable; // hash table
	int totalWords; // quantity of words in the text
public:
	Hash(int size = 256, int param = 3); // 256 by default
	int HashFunc(T elem); 
	void Add(T elem); // add an element to the hash table
	T MakeWord(T elem); // help function to GetFile()
	void GetFile(); // Source for the table
	void Results(); // Prints the results
	float LoadFactor(); // Returns load factor
	int MaxListLength(); // Returns longest list size (list for one hash value)
	float AverageListLength(); // Returns average list size of all hashes
};

template <typename T>
Hash<T>::Hash(int size, int param)
{
	hashSize = size;
	this->param = param;
	hashTable.reserve(size);
	totalWords = 0;
	GetFile();
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
	while (temp != "" && !((temp.at(temp.size() - 1) >= 'à' && temp.at(temp.size() - 1) <= 'ÿ') || (temp.at(temp.size() - 1) >= 'À' && temp.at(temp.size() - 1) <= 'ß') || (temp.at(temp.size() - 1) >= '0' && temp.at(temp.size() - 1) <= '9') || (temp.at(temp.size() - 1) >= 'a' && temp.at(temp.size() - 1) <= 'z') || (temp.at(temp.size() - 1) >= 'A' && temp.at(temp.size() - 1) <= 'Z')))
		temp.pop_back();
	while (temp != "" && !((temp.at(0) >= 'à' && temp.at(0) <= 'ÿ') || (temp.at(0) >= 'À' && temp.at(0) <= 'ß') || (temp.at(0) >= '0' && temp.at(0) <= '9') || (temp.at(0) >= 'a' && temp.at(0) <= 'z') || (temp.at(0) >= 'A' && temp.at(0) <= 'Z')))
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
	Results();
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
	cout << "Load factor: " << LoadFactor() << endl;
	cout << "Maximum list length: " << MaxListLength() << endl;
	cout << "Average list length: " << AverageListLength() << endl;
}

template<typename T>
float Hash<T>::LoadFactor()
{
	int count = 0;
	for (int i = 0; i < hashSize; i++)
		if (!hashTable[i].isEmpty())
			count++;
	return (float)count / (float)hashSize;
}

template<typename T>
int Hash<T>::MaxListLength()
{
	int count = 0;
	for (int i = 0; i < hashSize; i++)
		if (hashTable[i].GetSize() > count)
			count = hashTable[i].GetSize();
	return count;
}

template<typename T>
float Hash<T>::AverageListLength()
{
	int count = 0;
	int sum = 0;
	for (int i = 0; i < hashSize; i++)
		if (!hashTable[i].isEmpty())
		{
			count++;
			sum += hashTable[i].GetSize();
		}
	return (float)sum / (float)count;
}

int main()
{
	SetConsoleOutputCP(1251);
	Hash<string> text;
	system("pause");
	return 0;
}