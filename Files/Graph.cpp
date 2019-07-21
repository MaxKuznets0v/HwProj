#include <iostream>
#include <fstream>
#include "List.h"
using namespace std;

template<typename T>
class Graph // A full graph
{
	int vertices; // vertices amount
	int edges; // edges amount
	T **adjacencyMatrix; // full graph adjancency matrix
	class Country // A subgraph (country)
	{
	public:
		int capital; // country capital
		List<int> countryCities; // cities in country
		Country(int capital)
		{
			this->capital = capital;
			countryCities.push_front(capital);
		}
	};
	List<Country*> countries; //List of all countries
public:
	Graph(); //Constructor
	void GetGraph(); //Gets full graph from a file
	void GrowCountry();
	void Unused(List<int> &temp); //Puts unused vertices into a list (called at the start)
};

template<typename T>
Graph<T>::Graph()
{
	vertices = 0;
	edges = 0;
	adjacencyMatrix = nullptr;
	GetGraph();
}

template<typename T> 
void Graph<T>::GetGraph()
{
	fstream input;
	input.open("C:\\Maxim\\Repositories\\HwProj\\inputs\\input(Graph).txt");
	input >> vertices >> edges; // first is vertix number second is edge number
	adjacencyMatrix = new T*[vertices]; // making square matrix
	for (int i = 0; i < vertices; i++)
		adjacencyMatrix[i] = new T[vertices];
	for (int i = 0; i < vertices; i++) //initializing matrix with zeros
		for (int j = 0; j < vertices; j++)
			adjacencyMatrix[i][j] = 0;
	for (int i = 0; i < edges; i++) //pasting file data
	{
		int j, k;
		T temp;
		input >> j >> k >> temp;
		j--; // since 0 is the first element
		k--;
		adjacencyMatrix[j][k] = temp; //since graph is unoriented
		adjacencyMatrix[k][j] = temp;
	}
	int countryCount;
	input >> countryCount;
	for (int i = 0; i < countryCount; i++)
	{
		int cap; //current capital
		input >> cap;
		cap--;
		Country *temp = new Country(cap);
		countries.push_front(temp);
	}
	input.close();
}

template<typename T>
void Graph<T>::GrowCountry()
{
	List<int> temp;
	Unused(temp);
	while (!temp.isEmpty())
	{
		for (int i = 0; i < countries.GetSize(); i++)
		{
			if (temp.isEmpty())
				break;
			int min = INT32_MAX, ind1, curCity;

			for (int j = 0; j < countries[i]->countryCities.GetSize(); j++)
			{
				for (int k = 0; k < vertices; k++)
					if (adjacencyMatrix[countries[i]->countryCities[j]][k] != 0 && adjacencyMatrix[countries[i]->countryCities[j]][k] < min && temp.isInList(k))
					{
						min = adjacencyMatrix[countries[i]->countryCities[j]][k];
						ind1 = countries[i]->countryCities[j];
						curCity = k;
					}
			}
			if (min == INT32_MAX)
				continue;
			countries[i]->countryCities.push_front(curCity);
			adjacencyMatrix[ind1][curCity] = 0;
			adjacencyMatrix[curCity][ind1] = 0;
			int ind = 0;
			while (temp[ind] != curCity)
				ind++;
			temp.removeAt(ind);
		}
	}
}

template<typename T>
void Graph<T>::Unused(List<int> &temp)
{
	for (int i = 0; i < vertices; i++)
		temp.push_front(i);
	for (int i = 0; i < countries.GetSize(); i++)
	{
		if (temp.isInList(countries[i]->capital))
		{
			int j = 0;
			while (temp[j] != countries[i]->capital)
				j++;
			temp.removeAt(j);
		}
	}
}

int main()
{
	Graph<int> city;
	city.GrowCountry();
	system("pause");
	return 0;
}

