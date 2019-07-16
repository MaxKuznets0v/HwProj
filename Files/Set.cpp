#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

void menu(BinarySearchTree<int> set)
{
	bool checking = true;
	int ans;
	while (checking)
	{
		while (true)
		{
			cout << "\n------------------Menu------------------\n"
				<< "0. Quit\n"
				<< "1. Add element\n"
				<< "2. Delete element\n"
				<< "3. Check if element is in set\n"
				<< "4. Print elements in order\n"
				<< "5. Print elements in reverse order\n"
				<< "----------------------------------------\n";
			cout << "Enter number 0-5: ";
			cin >> ans;
			cin.clear();
			while (cin.get() != '\n');
			if ((ans == 0) || (ans == 1) || (ans == 2) || (ans == 3) || (ans == 4) || (ans == 5))
				break;
			else
			{
				cout << endl << "Enter a number 0-5!" << endl;
				continue;
			}
		}
		checking = false;
		int temp;
		switch (ans)
		{
		case 1:
			cout << "Enter element to add: ";
			cin >> temp;
			set.Add(temp);
			checking = true;
			break;
		case 2:
			cout << "Enter element to remove: ";
			cin >> temp;
			set.Remove(temp);
			checking = true;
			break;
		case 3:
			cout << "Enter element to check: ";
			cin >> temp;
			if (set.IsInSet(temp))
				cout << "Element " << temp << " is in set!\n";
			else
				cout << "Element " << temp << " is not in set!\n";
			checking = true;
			break;
		case 4:
			cout << "Set in order: ";
			set.InOrderTraversal();
			cout << endl;
			checking = true;
			break;
		case 5:
			cout << "Set in reverse order: ";
			set.InReverseOrderTraversal();
			cout << endl;
			checking = true;
			break;
		}
	}
}

int main()
{
	BinarySearchTree<int> set;
	menu(set);
	system("pause");
	return 0;
}