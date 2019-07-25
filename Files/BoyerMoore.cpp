#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class BMSearch
{
	string text; //Current text
	int badCharacterTable[256]; //Array for bad character shift 256 since we use only alphabet
	int *goodSuffixTable; //Array for good suffix shift
	void SetText(); //Gets text from a file
public:
	BMSearch(); //Constructor
	~BMSearch(); //Destructor (frees memory)
	string GetText(); //Getting text data
	int FindSample(string sample); //Searches sample and returns index of the first sample element
	void badCharacter(string sample); //Setting up badCharacter array
	void goodSuffix(string sample); //Setting up goodSuffix array
};

void BMSearch::SetText()
{
	ifstream input;
	input.open("C:\\Maxim\\Visual Studio\\Projects\\HwProj\\input(BoyerMoore).txt");
	while (!input.eof())
	{
		string temp;
		getline(input, temp);
		text += temp;
	}
	input.close(); 
}

BMSearch::BMSearch()
{
	text = string();
	SetText();
}

BMSearch::~BMSearch()
{
	delete[] goodSuffixTable;
}

inline string BMSearch::GetText()
{
	return text;
}

int BMSearch::FindSample(string sample)
{
	badCharacter(sample);
	goodSuffix(sample);

	int i = sample.size() - 1;
	for (i; i < text.size(); )
	{
		int j = sample.size() - 1;
		int letter = text[i];
		if (letter < 0)
			letter = -letter;
		while (text[i] == sample[j])
		{
			if (j == 0)
				return i;
			j--;
			i--;
		}
		if (j == sample.size() - 1)
			i += j - badCharacterTable[letter];
		else
		{
			if (j - badCharacterTable[letter] > goodSuffixTable[j] - 1)
				i += j - badCharacterTable[letter];
			else
				i += goodSuffixTable[j] - 1;
		}
	}
	return -1;
}

void BMSearch::badCharacter(string sample)
{
	for (int i = 0; i < 256; i++)
		badCharacterTable[i] = -1;

	for (int i = 0; i < sample.size() - 1; i++)
	{
		int letter = sample[i];
		if (letter < 0)
			letter = -letter;
		badCharacterTable[letter] = i;
	}
}

void BMSearch::goodSuffix(string sample)
{
	int m = sample.size();
	goodSuffixTable = new int[m + 1];
	int *z = new int[m];
	for (int i = 0; i < m; i++)
	{
		goodSuffixTable[i] = m;
		z[i] = 0;
	}

	for (int j = 1, maxZidx = 0, maxZ = 0; j < m; ++j) // Z function
	{
		if (j <= maxZ)
		{
			if (maxZ - j + 1 < z[j - maxZidx])
				z[j] = maxZ - j + 1;
			else
				z[j] = z[j - maxZidx];
		}
		while (j + z[j] < m && sample[m - 1 - z[j]] == sample[m - 1 - (j + z[j])]) 
			z[j]++;
		if (j + z[j] - 1 > maxZ) 
		{
			maxZidx = j;
			maxZ = j + z[j] - 1;
		}
	}
	for (int j = m - 1; j > 0; j--) 
		goodSuffixTable[m - z[j]] = j; //цикл №1
	for (int j = 1, r = 0; j <= m - 1; j++) //цикл №2
		if (j + z[j] == m)
			for (; r <= j; r++)
				if (goodSuffixTable[r] == m) 
					goodSuffixTable[r] = j;
	delete[] z;
}

int main()
{
	BMSearch sample;
	cout << sample.FindSample("abcabd") << endl;
	system("pause");
	return 0;
}

