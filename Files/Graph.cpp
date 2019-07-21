#include <iostream>
#include <fstream>
#include "List.h"
using namespace std;

template<typename T>
class Graph // A full graph
{
	class Country // A subgraph (country)
	{
	public:
		int capital; // country capital
		List< List<T> > countryMatrix; // subgraph adjancency matrix
		Country(int capital)
		{
			this->capital = capital;
		}
	};
	int vertices; // vertices amount
	int edges; // edges amount
	T **adjacencyMatrix; // full graph adjancency matrix
	List<Country*> countries;
public:
	Graph(); //Constructor
	void GetGraph(); //Gets full graph from a file
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
		Country *temp = new Country(cap);
		countries.push_front(temp);
	}
	input.close();
}

int main()
{
	Graph<int> city;
	system("pause");
	return 0;
}

