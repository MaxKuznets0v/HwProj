#include <iostream>
#include "Stack.h"
#include <string>
using namespace std;

int PostfixCounter(string input)
{
	Stack<int> stack;
	int temp;
	for (int i = 0; i < input.length(); i++)
		if (input.at(i) != ' ')
		{
			switch (input.at(i))
			{
			case '+':
				temp = stack.onTop();
				stack.pop();
				temp += stack.onTop();
				stack.pop();
				stack.push(temp);
				break;
			case '-':
				temp = -stack.onTop();
				stack.pop();
				temp += stack.onTop();
				stack.pop();
				stack.push(temp);
				break;
			case '*':
				temp = stack.onTop();
				stack.pop();
				temp *= stack.onTop();
				stack.pop();
				stack.push(temp);
				break;
			case '/':
				temp = stack.onTop();
				stack.pop();
				temp = stack.onTop() / temp;
				stack.pop();
				stack.push(temp);
				break;
			default:
				stack.push(atoi(&input.at(i)));
			}
		}
	return stack.onTop();
}

int main()
{
	string input;
	cout << "Enter your expression: ";
	getline(cin, input);
	cout << PostfixCounter(input);
	system("pause");
	return 0;
}