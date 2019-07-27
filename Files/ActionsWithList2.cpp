#include <iostream>
#include "List.h"
#include <ctime>
using namespace std;

class Menu
{
	int ans;
	List<int> list;
public:
	Menu()
	{
		ans = 0;
		ShowMenu();
	}
	void ShowMenu()
	{
		bool checking = true;
		while (checking)
		{
			while (true)
			{
				cout << "-------------Menu------------\n"
					<< "0. Quit\n"
					<< "1. Fill in the list with random values (first number - size, second - diapason)\n"
					<< "2. Reverse list\n"
					<< "3. Print list\n"
					<< "------------------------------\n";
				cout << "Enter a number 0-3: ";
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
				checking = true;
				int size, diap;
				cin >> size >> diap;
				SetRandom(size, diap);
				break;
			case 2:
				checking = true;
				MakeReverse();
				break;
			case 3:
				checking = true;
				PrintAll();
				break;
			}
		}
	}

	void SetRandom(int size, int diap)
	{
		srand(time(NULL));
		list.reserve(size);
		for (int i = 0; i < size; i++)
			list[i] = rand() % diap;
	}

	void MakeReverse()
	{
		List<int> newList;
		newList.reserve(list.GetSize());
		for (int i = list.GetSize() - 1; i >= 0; i--)
			newList[list.GetSize() - i - 1] = list[i];
		list = newList;
	}

	void PrintAll()
	{
		for (int i = 0; i < list.GetSize(); i++)
			cout << list[i] << " ";
		cout << endl;
	}
};

int main()
{
	Menu main;
	system("pause");
	return 0;
}