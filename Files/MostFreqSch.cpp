#include <iostream>
#include <fstream>
#include "C:\Maxim\Visual Studio\Projects\HwProj\sort.h"
using namespace std;

//most frequent element search (from a file)
int mostFreq(ifstream &a)
{
	int size;
	a >> size;
	int *arr = new int[size];
	for (int i = 0; i < size; i++)
		a >> arr[i];

	quickSort(arr, 0, size);
	int ind, count = 0, temp = 1;
	for (int i = 1; i < size; ++i)
	{
		if (arr[i - 1] == arr[i])
			temp++;
		else
		{
			if (temp > count)
			{
				count = temp;
				ind = i - temp;
			}
			temp = 1;
		}
	}
	return arr[ind];
}

int main()
{
	ifstream input("C:\\Maxim\\Visual Studio\\Projects\\HwProj\\input(MostFreqSch)");
	if (!input)
		cout << "Can\'t open the file!\n";
	else
		cout << "The most frequent element is " << mostFreq(input) << endl;
	input.close();
	system("pause");
	return 0;
}