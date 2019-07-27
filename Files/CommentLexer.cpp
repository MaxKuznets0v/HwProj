#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class CommentLexer
{
	enum Move
	{
		slash, // "/" = 0
		star, // "*" = 1
		otherSign // "other" = 2
	};
	int moveTable[4][3]; //Finite-state machine move table
	string code; // actual text
	void GetTable(); // Getting move table from a file
	void GetCode(); // Getting code from a file
public:
	CommentLexer(); //Constructor
	void FindComments(); //Lexer
};

CommentLexer::CommentLexer()
{
	code = "";
	GetTable();
	GetCode();
}

void CommentLexer::FindComments()
{
	int state = 0;
	Move sign;
	char prev;
	char symbol;
	for (int i = 0; i < code.size(); i++)
	{
		symbol = code[i];
		switch (state)
		{
		case 0:
			if (symbol == '/')
			{
				prev = symbol;
				sign = slash;
				state = moveTable[state][sign];
			}
			break;
		case 1:
			if (symbol == '*')
			{
				sign = star;
				cout << prev << symbol;
				state = moveTable[state][sign];
			}
			else if (symbol != '/')
			{
				sign = otherSign;
				state = moveTable[state][sign];
			}
			else
				prev = symbol;
			break;
		case 2:
			if (symbol == '*')
			{
				sign = star;
				prev = symbol;
				state = moveTable[state][sign];
			}
			else
				cout << symbol;
			break;
		case 3:
			if (symbol == '/')
			{
				sign = slash;
				cout << prev << symbol;
				state = moveTable[state][sign];
				cout << endl;
			}
			else if (symbol != '*')
			{
				sign = otherSign;
				state = moveTable[state][otherSign];
				cout << prev << symbol;
			}
			else
				cout << prev;
			break;
		}
	}
}

void CommentLexer::GetTable()
{
	ifstream input;
	input.open("C:\\Maxim\\Repositories\\HwProj\\inputs\\input(CommentLexer).txt");
	while (!input.eof())
	{
		string state1, op, state2; // first state operator, second state
		input >> state1 >> op >> state2;
		if (op == "/")
			moveTable[stoi(state1)][0] = stoi(state2);
		else if (op == "*")
			moveTable[stoi(state1)][1] = stoi(state2);
		else if (op == "other")
			moveTable[stoi(state1)][2] = stoi(state2);
	}
	input.close();
}

void CommentLexer::GetCode()
{
	ifstream input;
	input.open("C:\\Maxim\\Repositories\\HwProj\\inputs\\inputText(CommentLexer).txt");
	while (!input.eof())
	{
		string temp;
		getline(input, temp);
		code += temp;
	}
	input.close();
}



int main()
{
	CommentLexer text;
	text.FindComments();
	
	system("pause");
	return 0;
}

