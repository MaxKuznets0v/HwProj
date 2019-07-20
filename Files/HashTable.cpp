#include <iostream>
#include <fstream>
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
		hash = (hash * param + str[i]) % hashSize;
	return hash;
}

template<typename T>
void Hash<T>::Add(T elem)
{
	int index = HashFunc(elem, param); 
	hashTable[index].push_front(elem);
}

int main()
{
	Hash<char*> text;

	system("pause");
	return 0;
}