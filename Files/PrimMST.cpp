#include <iostream>
#include <fstream>
#include "List.h"
using namespace std;

template <typename T>
class PrimMST
{
	int vertices; //Vertices amount all vertices are from 0 to N-1 (N amount of vertices)
	int edges; //Edges amount
	T **matrix; //Adjacency matrix
	T **MSTmatrix; //Resulting matrix
	void GetMatrix(); //Copies adjacency matrix from a file
	void Unused(List<int> &temp, int from); //Only at the start puts all unused vertices in a list
public:
	PrimMST(); //Constructor
	~PrimMST(); //Destructor (frees memory)
	void GetMST(int from = 0); //Building MST (by default from the first vertice)
	void Results(); //Prints MST adjacency matrix 
};

template<typename T>
PrimMST<T>::PrimMST()
{
	vertices = 0;
	edges = 0;
	matrix = nullptr;
	GetMatrix();
	GetMST();
	Results();
}

template<typename T>
PrimMST<T>::~PrimMST()
{
	for (int i = vertices - 1; i >= 0; i--)
	{
		delete[] matrix[i];
		delete[] MSTmatrix[i];
	}
	delete[] matrix;
	delete[] MSTmatrix;
}

template<typename T>
void PrimMST<T>::GetMST(int from)
{
	MSTmatrix = new T*[vertices]; //Giving memory for 2D matrix
	for (int i = 0; i < vertices; i++)
		MSTmatrix[i] = new T[vertices];
	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++)
			MSTmatrix[i][j] = 0; //initializing with zeros

	List<int> unused, used;
	used.push_front(from);
	Unused(unused, from);
	while (!unused.isEmpty())
	{
		T min = INT32_MAX;
		int ind1, ind2;
		for (int i = 0; i < used.GetSize(); i++)
			for (int j = 0; j < vertices; j++)
				if (matrix[used[i]][j] != 0 && matrix[used[i]][j] < min && unused.isInList(j))
				{
					min = matrix[used[i]][j];
					ind1 = used[i];
					ind2 = j;
				}

		used.push_front(ind2);
		int ind = 0;
		while (unused[ind] != ind2)
			ind++;
		unused.removeAt(ind);
		MSTmatrix[ind1][ind2] = min;
		MSTmatrix[ind2][ind1] = min;
	}
}

template<typename T>
void PrimMST<T>::Results()
{
	for (int i = 0; i < vertices; i++)
		for (int j = i; j < vertices; j++)
			if (MSTmatrix[i][j] != 0)
				cout << i + 1 << " " << j + 1 << " " << MSTmatrix[i][j] << endl;
}


template<typename T>
void PrimMST<T>::GetMatrix()
{
	ifstream input;
	input.open("C:\\Maxim\\Visual Studio\\Projects\\HwProj\\input(PrimMST).txt");
	input >> vertices >> edges;
	matrix = new T*[vertices]; //Giving memory for 2D matrix
	for (int i = 0; i < vertices; i++)
		matrix[i] = new T[vertices];
	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++)
			matrix[i][j] = 0; //initializing with zeros
	for (int i = 0; i < edges; i++)
	{
		int j, k;
		T temp;
		input >> j >> k >> temp;
		j--;
		k--;
		matrix[j][k] = temp;
		matrix[k][j] = temp;
	}
	input.close();
}

template<typename T>
void PrimMST<T>::Unused(List<int> &temp, int from)
{
	for (int i = 0; i < vertices; i++)
		if (temp[from] != i)
			temp.push_front(i);
}

int main()
{
	PrimMST<int> graph;

	system("pause");
	return 0;
}

