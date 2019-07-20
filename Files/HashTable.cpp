#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "List.h"
using namespace std;

template<typename T>
class Hash
{
	int hashSize;
	int param;
	List<List <T>> hashTable;
public:
	Hash(int size = 256, int param = 3); // 256 by default
	~Hash();
	int HashFunc(T elem);
	void Add(T elem);
	void GetFile();
	void Results();
};

template <typename T>
Hash<T>::Hash(int size, int param)
{
	hashSize = size;
	this->param = param;
	hashTable.reserve(size);
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
		hash = (hash * param - str[i]) % hashSize;
	return hash;
}

template<typename T>
void Hash<T>::Add(T elem)
{
	int index = HashFunc(elem); 
	hashTable[index].push_front(elem);
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
		Add(temp);
	}
	input.close();
}

int main()
{
	SetConsoleCP(1251);
	Hash<string> text;
	text.GetFile();
	system("pause");
	return 0;
}