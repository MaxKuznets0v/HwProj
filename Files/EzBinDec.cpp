#include <iostream>
#include <string>
using namespace std;

string decToBin(int a)
{
	string res;
	while (a)
	{
		if (a % 2)
			res = "1" + res;
		else
			res = "0" + res;
		a /= 2;
	}
	return res;
}

int binToDec(string s)
{
	int res = 0;
	for (int i = s.length() - 1; i >= 0; --i)
	{
		int digit = s.at(i) - '0';
		if (i == s.length() - 1)
			res += digit * 1;
		else
		{
			for (int j = 0; j < s.length() - i - 1; ++j)
				digit *= 2;
			res += digit;
		}
	}
	return res;
}

string pBlus(string s1, string s2)
{
	int len1 = s1.size();
	int len2 = s2.size();

	string ls1 = len1 < len2 ? s1 : s2;
	string ls2 = len1 < len2 ? s2 : s1;
	for (int i = ls1.size(); i < ls2.size(); ++i)
		ls1 = '0' + ls1;

	string result;
	int carry = 0;
	for (int i = ls2.size() - 1; i >= 0; --i)
	{
		int bit1 = ls1.at(i) - '0'; // '0' => 0, '1' => 1
		int bit2 = ls2.at(i) - '0';
		char sum = (bit1 ^ bit2 ^ carry) + '0';
		result = sum + result;
		carry = (bit1 & carry) | (bit2 & carry) | (bit1 & bit2);
	}
	if (carry)
		result = '1' + result;
	return result;
}

int main()
{
	setlocale(LC_ALL, "rus");
	int first, second;
	cout << "Введите два целых числа: \n";
	cin >> first >> second;
	string fres = decToBin(first);
	cout << "Число " << first << " в двоичной системе счисления: " << fres;
	cout << endl;
	string sres = decToBin(second);
	cout << "Число " << second << " в двоичной системе счисления: " << sres;
	cout << endl;
	string sum = pBlus(fres, sres);
	cout << "Сумма в двоичной системе: " << fres << " + " << sres << " = " << sum << endl;
	cout << "Сумма в десятичной системе: " << binToDec(sum) << endl;
	system("pause");
	return 0;
}