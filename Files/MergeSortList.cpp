#include <iostream>
#include <fstream>
#include <string>
#include "List.h"
using namespace std;

class ListSort
{
	List<string> list;
	List<string> names;
	List<string> phones;
public:
	ListSort();
	void getFile(); //Gets data from a file
	void separate(); //Divides names from phones
	void sort(); //Menu and sort call
	void merge(List<string> &sorting, int lo, int mid, int hi); //Merging process
	void listSort(List<string> &sorting, int lo, int hi); //Actual sort
	void listSort(List<string> &sorting); //Sort with one arg
	void showList(); //Prints list
};

ListSort::ListSort()
{
	getFile();
	separate();
}

void ListSort::getFile()
{
	fstream file;
	string temp;
	file.open("C:\\Maxim\\Visual Studio\\Projects\\HwProj\\input(MergeSortList).txt", ifstream::in);
	while (!file.eof())
	{
		getline(file, temp);
		list.push_back(temp);
	}
	file.close();
}

void ListSort::separate()
{
	for (int i = 0; i < list.GetSize(); i++)
	{
		names.push_back("");
		phones.push_back("");
		int j = 0;
		string::iterator it = list[i].begin();
		while (*it != '-')
		{
			names[i] += *it;
			++it;
		}
		it++;
		while (it != list[i].end())
		{
			phones[i] += *it;
			++it;
		}
	}
}

void ListSort::merge(List<string> &sorting, int lo, int mid, int hi)
{
	int index = 0, l = lo, h = mid + 1;
	List<string> tempFull, tempPart;
	while (l <= mid && h <= hi)
	{
		if (sorting[l] < sorting[h])
		{
			tempFull.push_back(list[l]);
			tempPart.push_back(sorting[l]);
			l++;
		}
		else
		{
			tempFull.push_back(list[h]);
			tempPart.push_back(sorting[h]);
			h++;
		}
	}
	while (l <= mid)
	{
		tempFull.push_back(list[l]);
		tempPart.push_back(sorting[l]);
		l++;
	}
	while (h <= hi)
	{
		tempFull.push_back(list[h]);
		tempPart.push_back(sorting[h]);
		h++;
	}

	for (int i = 0; i < hi - lo + 1; i++)
	{
		list[lo + i] = tempFull[i];
		sorting[lo + i] = tempPart[i];
	}
}

void ListSort::listSort(List<string> &sorting, int lo, int hi)
{
	if (lo < hi)
	{
		int mid = lo + (hi - lo) / 2;
		listSort(sorting, lo, mid);
		listSort(sorting, mid + 1, hi);
		merge(sorting, lo, mid, hi);
	}
}

void ListSort::listSort(List<string> &sorting)
{
	int lo = 0, hi = sorting.GetSize() - 1;
	listSort(sorting, lo, hi);
}

void ListSort::showList()
{
	for (int i = 0; i < list.GetSize(); i++)
		cout << list[i] << endl;
	cout << endl;
}

void ListSort::sort()
{
	while (true)
	{
		int ans;
		cout << "How would you like to sort: by name or by phone number? (0 or 1)\n";
		cin >> ans;
		if (ans == 0)
		{
			listSort(names);
			break;
		}
		else if (ans == 1)
		{
			listSort(phones);
			break;
		}
		else
		{
			cout << "Enter 0 or 1!\n";
			cin.clear();
			while (cin.get() != '\n');
		}
	}
}


int main()
{
	ListSort cur;
	cur.showList();
	cur.sort();
	cur.showList();
	system("pause");
	return 0;
}