#include <iostream>
#include "Stack.h"
using namespace std;

void PrintAll(Stack<int> &stack)
{
	int size = stack.GetSize();
	while (size)
	{
		cout << stack.onTop() << " ";
		size--;
	}
	cout << endl;
}

int main()
{
	Stack<int> stack;
	bool checking = true;
	int ans;
	while (checking)
	{
		while (true)
		{
			cout << "\n------------------Menu------------------\n"
				<< "0. Quit\n"
				<< "1. Add element at the top of a stack\n"
				<< "2. Delete element from the top of a stack\n"
				<< "3. Copy element at the top of a stack\n"
				<< "4. Print all\n"
				<< "----------------------------------------\n";
			cout << "Enter number 0-4: ";
			cin >> ans;
			cin.clear();
			while (cin.get() != '\n');
			if ((ans == 0) || (ans == 1) || (ans == 2) || (ans == 3) || (ans == 4))
				break;
			else
			{
				cout << endl << "Enter a number 0-4!" << endl;
				continue;
			}
		}
		checking = false;
		int temp;
		switch (ans)
		{
		case 1:
			cout << "Enter a number to add: ";
			cin >> temp;
			stack.push(temp);
			checking = true;
			break;
		case 2:
			cout << "Deleting element " << stack.onTop() << endl;
			stack.pop();
			checking = true;
			break;
		case 3:
			if (stack.GetSize())
			{
				temp = stack.onTop();
				stack.push(temp);
			}
			checking = true;
			break;
		case 4:
			PrintAll(stack);
			checking = true;
			break;
		}
	}
	system("pause");
	return 0;
}