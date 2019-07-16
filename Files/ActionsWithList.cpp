#include "List.h"
#include <iostream>
using namespace std;

template <typename T>
class Task
{
	int ans;
	List<T> list;
	bool checking;
public:
	Task()
	{
		checking = true;
	}
	void Menu();
	void AddElem();
	void DeleteElem();
	void PrintAll();
};

template <typename T>
void Task<T>::Menu()
{
	while (checking)
	{
		while (true)
		{
			cout << "\n------------------Menu------------------\n"
				<< "0. Quit\n"
				<< "1. Add element\n"
				<< "2. Delete element\n"
				<< "3. Print list\n"
				<< "----------------------------------------\n";
			cout << "Enter number 0-3: ";
			cin >> ans;
			cin.clear();
			while (cin.get() != '\n');
			if ((ans == 0) || (ans == 1) || (ans == 2) || (ans == 3))
				break;
			else
			{
				cout << endl << "Enter a number 0-3!" << endl;
				continue;
			}
		}
		checking = false;
		switch (ans)
		{
		case 1:
			AddElem();
			checking = true;
			break;
		case 2:
			DeleteElem();
			checking = true;
			break;
		case 3:
			PrintAll();
			checking = true;
			break;
		}

	}
}

template<typename T>
void Task<T>::AddElem()
{
	T elem;
	cout << "Enter new element: ";
	cin >> elem;
	cin.clear();
	while (cin.get() != '\n');
	int i;
	for (i = 0; (i < list.GetSize()) && (elem >= list[i]); i++);
	list.insert(elem, i);
}

template<typename T>
void Task<T>::DeleteElem()
{
	T elem;
	cout << "Enter element to delete: ";
	cin >> elem;
	cin.clear();
	while (cin.get() != '\n');
	int i;
	for (i = 0; (i < list.GetSize()) && (list[i] < elem); i++);
	if ((i < list.GetSize()) && (list[i] == elem))
		list.removeAt(i);
	else
		cout << "\nElement " << elem << " is not found!\n";
}

template<typename T>
void Task<T>::PrintAll()
{
	if (list.GetSize())
	{
		cout << endl;
		for (int i = 0; i < list.GetSize(); i++)
			cout << list[i] << " ";
		cout << endl;
	}
	else
		cout << "The list is empty!\n";
}

int main()
{
	Task<int> test;
	test.Menu();

	system("pause");
	return 0;
}