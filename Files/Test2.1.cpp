#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream input;
	input.open("C:\\Maxim\\Visual Studio\\Projects\\HwProj\\input(Test2.1).txt");
	ofstream output;
	output.open("C:\\Maxim\\Visual Studio\\Projects\\HwProj\\output(Test2.1).txt", iostream::trunc);
	int a, b;
	cin >> a >> b;

	while (!input.eof())
	{
		int temp;
		input >> temp;
		if (temp < a)
			output << temp << " ";
	}
	input.seekg(ios::beg);
	while (!input.eof())
	{
		int temp;
		input >> temp;
		if (temp >= a && temp <= b)
			output << temp << " ";
	}
	input.seekg(ios::beg);
	while (!input.eof())
	{
		int temp;
		input >> temp;
		if (temp > b)
			output << temp << " ";
	}

	input.close();
	output.close();
	system("pause");
	return 0;
}