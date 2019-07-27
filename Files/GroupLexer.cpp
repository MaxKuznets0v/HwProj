#include <iostream>
#include <string>
using namespace std;

class GroupChecker
{
	enum States
	{
		year,
		num,
		mm
	};
public:
	inline bool isDigit(char ch)
	{
		if (ch >= '0' && ch <= '9')
			return true;
		else 
			return false;
	}

	bool isGroupValid(string str)
	{
		States state = year;
		string temp = "";
		char prev, symbol;
		for (int i = 0; i < str.size(); i++)
		{
			symbol = str[i];
			switch (state)
			{
			case year:
				if (isDigit(symbol))
				{
					if (temp.size() == 2)
						return false;
					else
						temp += symbol;
				}
				else
				{
					if (temp.size() == 2 && (symbol == 'B' || symbol == 'M' || symbol == 'S'))
					{
						temp = "";
						state = num;
					}
					else
						return false;
				}
				break;
			case num:
				if (isDigit(symbol))
				{
					if (temp.size() == 2)
						return false;
					else
						temp += symbol;
				}
				else
				{
					if (temp.size() > 0 && symbol == '-')
					{
						temp = "";
						state = mm;
					}
					else
						return false;
				}
				break;
			case mm:
				if (symbol == 'm')
				{
					temp += symbol;
					if (temp.size() > 2)
						return false;
				}
				else
					return false;
				if (temp == "mm")
					return true;
				break;
			}
		}
	}

};

int main()
{
	GroupChecker check;
	string a = "19S5-mm";
	if (check.isGroupValid(a))
		cout << "Y\n";
	else
		cout << "N\n";
	system("pause");
	return 0;
}