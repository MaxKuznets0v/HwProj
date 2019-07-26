#include <iostream>
#include <string>
using namespace std;

class NumberLexer
{
	//enum States
	//{
	//	digit = 0, // from 0 to 9
	//	sign, // "+" or "-"
	//	bigE, // "E" for "10 in power of"
	//	comma, // "."
	//	other // another characters 
	//};

	bool isDigit(char letter);
public:
	NumberLexer();
	~NumberLexer();
	bool isNumber(string str);
};

inline bool NumberLexer::isDigit(char letter)
{
	if (letter >= '0' && letter <= '9')
		return true;
	else
		return false;
}

NumberLexer::NumberLexer()
{
}

NumberLexer::~NumberLexer()
{
}

bool NumberLexer::isNumber(string str)
{
	string ans = "";
	for (int i = 0; i < str.size(); i++) // getting new string without spaces
		if (str[i] != ' ')
			ans += str[i];
	if (!ans.size() || !isDigit(ans[0]) || !isDigit(ans[ans.size() - 1])) // if it's an empty string or first or second is not a digit
		return false;

	for (int i = 1; i < ans.size(); i++)
	{
		char token = ans[i];
		
		switch (token)
		{
		case '.':
			if (!isDigit(ans[i - 1]))
				return false;
			break;
		case 'E':
			if (!isDigit(ans[i - 1]))
				return false;
			break;
		case '+':
			if (ans[i - 1] != 'E')
				return false;
			break;
		case '-':
			if (ans[i - 1] != 'E')
				return false;
			break;
		default:
			if (!isDigit(token))
				return false;
			break;
		}
	}
	cout << ans << " is a real number!\n";
	return true;
}


int main()
{
	NumberLexer text;
	string x = "12E22";
	text.isNumber(x);
	system("pause");
	return 0;
}

