#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Person
{
	string name;
	string phone;
public:
	//Returns name
	string Name();
	//Puts name
	void SetName(string a);
	//Puts phone
	void SetPhone(string a);
	//Returns phone number
	string Phone();
	friend ostream &operator << (ostream &stream, Person &ob);
	friend istream &operator >> (istream &stream, Person &ob);
};

string Person::Name()
{
	return name;
}
string Person::Phone()
{
	return phone;
}
void Person::SetName(string a)
{
	name = a;
}
void Person::SetPhone(string a)
{
	phone = a;
}
istream &operator >> (istream &stream, Person &ob)
{
	cout << "Enter a person\'s name: ";
	getline(stream, ob.name);
	stream.clear();
	cout << "Enter a person\'s phone number: ";
	stream >> ob.phone;
	//The next two lines protect from excess info in stream
	stream.clear();
	while (stream.get() != '\n');
	return stream;
}
ostream &operator << (ostream &stream, Person &ob)
{
	stream << "\n-----------------------------------";
	stream << "\nName: " << ob.name << endl;
	stream << "\nPhone number: " << ob.phone << endl;
	stream << "-----------------------------------\n";
	return stream;
}

class Base
{
	int length; //Notes amount
	Person *phoneBook; //PhoneBook
	fstream file; //Contains PhoneBook
public:
	Base() //Constructor loads the table from the file and show the menu
	{
		GetBook();
		ShowMenu();
	}
	~Base() //Destructor clears the memory
	{
		delete[] phoneBook;
	}
	//Shows menu
	void ShowMenu()
	{
		int ans; //user answer
		do
		{
			cout << "\n---------------Menu----------------\n"
				<< "0. Quit\n"
				<< "1. Add a note\n"
				<< "2. Print all the notes\n"
				<< "3. Find a phone number by name\n"
				<< "4. Find a name by number\n"
				<< "5. Save current notes into a file\n\n";
			cout << "Enter number 0-5: ";
			cin >> ans;
			cin.clear();
			while (cin.get() != '\n');
			if ((ans == 0) || (ans == 1) || (ans == 2) || (ans == 3) || (ans == 4) || (ans == 5))
				break;
			else
			{
				cout << endl << "Enter a number 0-5!" << endl;
				continue;
			}
		} while (true);

		if (ans)
		{
			switch (ans)
			{
			case 1:
			{
				AddNew();
				ShowMenu();
				break;
			}
			case 2:
			{
				PrintAll();
				ShowMenu();
				break;
			}
			case 3:
			{
				FindByName();
				ShowMenu();
				break;
			}
			case 4:
			{
				FindByPhone();
				ShowMenu();
				break;
			}
			case 5:
			{
				Save();
				ShowMenu();
				break;
			}
			}
		}
	}
	//Gets existing table
	void GetBook()
	{
		file.open("C:\\Maxim\\Visual Studio\\Projects\\HwProj\\PhoneBook.txt");
		file >> length;
		phoneBook = new Person[length];
		for (int i = 0; i < length; i++)
		{
			string fst, scd;
			file >> fst >> scd;
			fst = fst + " " + scd;
			phoneBook[i].SetName(fst);
			file >> scd;
			phoneBook[i].SetPhone(scd);
		}
		file.close();
	}
	//Prints all the table
	void PrintAll()
	{
		if (length)
			for (int i = 0; i < length; ++i)
				cout << phoneBook[i];
		else
			cout << "The table is empty!\n";
	}
	//Adds a new element
	void AddNew()
	{
		Person *temp = new Person[length + 1];
		for (int i = 0; i < length; i++)
			temp[i] = phoneBook[i];
		delete[] phoneBook;
		phoneBook = temp;
		cin >> phoneBook[length];
		length++;
	}
	//Finds a person by name
	void FindByName()
	{
		string curName; //user name
		cout << "Enter the name: ";
		getline(cin, curName);
		int count = 0; //amount of people
		vector<int> people;
		for (int i = 0; i < length; i++)
			if (curName == phoneBook[i].Name())
			{
				count++;
				people.push_back(i);
			}
		if (count)
		{
			cout << "We\'ve found " << count << " results by your request!\n";
			for (int i = 0; i < count; i++)
				cout << phoneBook[people[i]];
		}
		else
			cout << "No one found!\n";
	}
	//Find a person by phone number
	void FindByPhone()
	{
		string curPhone; //user name
		cout << "Enter the phone: ";
		getline(cin, curPhone);
		int count = 0; //amount of people
		vector<int> people;
		for (int i = 0; i < length; i++)
			if (curPhone == phoneBook[i].Phone())
			{
				count++;
				people.push_back(i);
			}
		if (count)
		{
			cout << "We\'ve found " << count << " results by your request!\n";
			for (int i = 0; i < count; i++)
				cout << phoneBook[people[i]];
		}
		else
			cout << "No one found!\n";
	}
	//Saves new data
	void Save()
	{
		//Opens file and destroys all data, then copys from phoneBook array
		file.open("C:\\Maxim\\Visual Studio\\Projects\\HwProj\\PhoneBook.txt", ios::trunc | ofstream::out);
		file << length << endl;
		for (int i = 0; i < length; ++i)
			file << phoneBook[i].Name() << " " << phoneBook[i].Phone() << endl;
		file.close();
	}
};

int main()
{
	Base menu;
	system("pause");
	return 0;
}