#include <iostream>
#include <string>
#include "Stack.h"
using namespace std;

bool isBalanced(string user)
{
	Stack<char> stack;
	for (int i = 0; i < user.length(); i++)
		switch (user.at(i))
		{
		case '(':
			stack.push('(');
			break;
		case ')':
			if (stack.onTop() == '(')
				stack.pop();
			else
				return false;
			break;
		case '{':
			stack.push('{');
			break;
		case '}':
			if (stack.onTop() == '{')
				stack.pop();
			else
				return false;
			break;
		case '[':
			stack.push('[');
			break;
		case ']':
			if (stack.onTop() == '[')
				stack.pop();
			else
				return false;
			break;
		}
	if (stack.GetSize())
		return false;
	else
		return true;
}

int main()
{
	string input;
	cout << "Enter your line: ";
	getline(cin, input);
	if (isBalanced(input))
		cout << "Parentheses is balanced!\n";
	else
		cout << "Parentheses is not balanced!\n";
	system("pause");
	return 0;
}