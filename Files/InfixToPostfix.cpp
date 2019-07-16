#include <iostream>
#include "Stack.h"
#include <string>
using namespace std;

int makePostfix (string inp, string &outp)
{
	Stack<char> stack;
	for (size_t i = 0; i < inp.length(); i++)
	{
		char token = inp.at(i);
		if (token >= '0' && token <= '9')
			outp += token;
		else if (token == ' ' && outp.at(outp.length() - 1) != ' ')
			outp += token;
		else if (token == '*' || token == '/' || token == '+' || token == '-')
		{
			if (!stack.GetSize())
				stack.push(token);
			else
			{
				while (stack.GetSize() && ((stack.onTop() == '*' || stack.onTop() == '/') || ((stack.onTop() == '+' || stack.onTop() == '-') && (token == '+' || token == '-'))))
				{
					outp += stack.onTop();
					stack.pop();
				}
				if (!stack.GetSize() || stack.onTop() == '(' || token == '*' || token == '/')
					stack.push(token);
			}
		}
		else if (token == '(')
			stack.push(token);
		else if (token == ')')
		{
			while (stack.onTop() != '(')
			{
				if (stack.GetSize())
				{
					outp += stack.onTop();
					stack.pop();
				}
				else
				{
					cout << "Invalid parentheses!\n";
					return 1;
				}
			}
			stack.pop(); // Removes token '('
		}

	}
	while (stack.GetSize())
	{
		if (stack.onTop() == '(')
		{
			cout << "Invalid parentheses!)\n";
			return 1;
		}
		else
		{
			outp += stack.onTop();
			stack.pop();
		}
	}
	return 0;
}
int PostfixCounter(string input)
{
	Stack<int> stack;
	int temp;
	for (int i = 0; i < input.length(); i++)
		if (input.at(i) != ' ')
		{
			char current = input.at(i);
			switch (current)
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
				stack.push(atoi(&current));
			}
		}
	return stack.onTop();
}
int main()
{
	string input, output;
	cout << "Enter your infix expression: ";
	getline(cin, input);
	if (!makePostfix(input, output))
		cout << output << endl;
	cout << PostfixCounter(output) << endl;
	system("pause");
	return 0;
}











