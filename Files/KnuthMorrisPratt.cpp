#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class KMPSearch
{
	string text; // Current text
	int *pi; // Array for prefix function
	void SetText(); // Gets text from a file
	void PrefixFunction(string sample); //Setting up pi array
public:
	KMPSearch(); // Constructor
	~KMPSearch(); // Destructor (frees memory)
	string GetText(); //Getting text data
	int FindSample(string sample); // Searches sample and returns index of the first sample element
};

KMPSearch::KMPSearch()
{
	text = string();
	SetText();
}

KMPSearch::~KMPSearch()
{
	delete[] pi;
}

inline string KMPSearch::GetText()
{
	return text;
}

int KMPSearch::FindSample(string sample)
{
	pi = new int[sample.size()];
	PrefixFunction(sample);
	int j = 0; // pi index
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == sample[j])
		{
			j++;
			if (j == sample.size())
				return i - j + 1;
		}
		else if (j > 0)
		{
			j = pi[j - 1];
			if (text[i] == sample[j])
			{
				j++;
				if (j == sample.size())
					return i - j + 1;
			}
		}
	}
	return -1;
}

void KMPSearch::SetText()
{
	ifstream input;
	input.open("C:\\Maxim\\Visual Studio\\Projects\\HwProj\\input(KnuthMorrisPratt).txt");
	while (!input.eof())
	{
		string temp;
		getline(input, temp);
		text += temp;
	}
	input.close();
}

void KMPSearch::PrefixFunction(string sample)
{
	pi[0] = 0; //zero index is 0 by default
	for (int i = 1; i < sample.size(); i++)
	{
		int j = pi[i - 1];
		while (j > 0 && sample[i] != sample[j])
			j = pi[j - 1];
		if (sample[i] == sample[j])
			j++;
		pi[i] = j;
	}
}

int main()
{
	KMPSearch novel;
	string sample;
	cout << "Enter a word to find: ";
	getline(cin, sample);
	string text = novel.GetText();
	int index = novel.FindSample(sample);
	if (index < 0)
		cout << "Not found!\n";
	else
	{
		for (int i = 0; i < sample.size(); i++, index++)
				cout << text[index];
		cout << endl;
	}
	
	system("pause");
	return 0;
}

