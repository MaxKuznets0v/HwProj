#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class CommentLexer
{
	enum States
	{
		idle, // idle till doesn't get'/' 
		open, // after that becomes open and wait for '*'
		comment, // then text till '*'
		close, // until gets '/' 
		other // other symbols
	};
	int moveTable[4][3]; //Finite-state machine move table
	string code; // actual text
	void GetTable(); // Getting move table from a file
	void GetCode(); // Getting code from a file
public:
};

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

	input.close();
}

int main()
{
	CommentLexer text;

	system("pause");
	return 0;
}

