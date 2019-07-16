#pragma once
//File contains 7 sorts and a binary search
//In every sort lo - lower index, hi - upper index + 1


//----------------------------Insertion sort---------------------------------
template <typename T>
void insSort(T *a, int lo, int hi)  
{
	for (int i = lo + 1; i < hi; i++)
		for (int j = i; (j > 0) && (a[j] < a[j - 1]); --j)
			std::swap(a[j], a[j - 1]);
}
//---------------------------------------------------------------------------

//----------------------------Quick sort-------------------------------------
//Array division into 2 parts: smaller and greater than a pivot value
template <typename T>
T partition(T *a, int low, int high) 
{
	T pivot = a[high - 1];
	int i = low;
	for (int j = low; (j < high - 1); j++)
		if (a[j] <= pivot)
		{
			std::swap(a[i], a[j]);
			++i;
		}
	std::swap(a[i], a[high - 1]);
	return i;
}

template <typename T>
void quickSort(T *a, int lo, int hi)
{
	if (lo + 10 < hi)
	{
		int p = partition(a, lo, hi);
		quickSort(a, lo, p);
		quickSort(a, p + 1, hi);
	}
	else if (lo < hi)
		insSort(a, lo, hi);
}
//---------------------------------------------------------------------------

//----------------------------Bubble sort------------------------------------
template <typename T>
void bubSort(T *a, int lo, int hi)
{
	for (int i = lo; i < hi; ++i)
		for (int j = hi - 1; j > i; --j)
			if (a[j] < a[j - 1])
				std::swap(a[j], a[j - 1]);
}
//---------------------------------------------------------------------------

//----------------------------Binary search----------------------------------
//Returns element index or -1 if there's no element
template <typename T>
int isInArr(T *a, int lo, int hi, T num)  
{
	while (lo < hi)
	{
		int mid = lo + (hi - lo) / 2;
		if (a[mid] == num)
			return mid;

		if (a[mid] > num)
			hi = mid;
		else
			lo = mid + 1;
	}
	return -1;
}
//---------------------------------------------------------------------------

//----------------------------Counting sort----------------------------------
//Useful when number diapason(excluding the highest) is much smaller than whole number amount
template <typename T>
void countSort(T *a, int lo, int hi, int diap)
{
	T *b = new T[diap]();
	for (int i = lo; i < hi; ++i)
		b[a[i]] += 1;

	int ind = lo;
	for (int i = lo; i < diap; ++i)
		for (int j = 0; j < b[i]; j++)
		{
			a[ind] = i;
			ind++;
		}
	delete[] b;
}
//---------------------------------------------------------------------------

//----------------------------Shell sort-------------------------------------
template <typename T>
void shellSort(T *a, int hi)
{
	for (int step = hi / 2; step > 0; step /= 2)
		for (int i = step; i < hi; ++i)
			for (int j = i; (j >= step) && (a[j] < a[j - step]); j -= step)
				std::swap(a[j - step], a[j]);
}
//---------------------------------------------------------------------------

//----------------------------Selection sort---------------------------------
template <typename T>
void selSort(T *a, int lo, int hi)
{
	int ind;
	T min;
	for (int i = lo; i < hi - 1; i++)
	{
		min = a[i];
		ind = i;
		for (int j = i + 1; (j < hi); j++)
			if (a[j] < min)
			{
				min = a[j];
				ind = j;
			}
		std::swap(a[i], a[ind]);
	}
}
//---------------------------------------------------------------------------

//--------------------------------Heap Sort----------------------------------
//Element insertion into the heap (cur - new element index)
//Each cur element goes to its position
template <typename T>
void downHeap(T *a, int cur, int n)
{
	while (cur < n / 2)
	{
		int child = 2 * cur + 1;
		if ((a[child] < a[child + 1]) && (child < n - 1))
			child++;

		if (a[cur] >= a[child])
			break;

		std::swap(a[child], a[cur]);
		cur = child;
	}
}

template <typename T>
void heapSort(T *a, int lo, int hi)
{
	//Building the heap
	for (int i = hi / 2 - 1; i >= lo; --i)
		downHeap(a, i, hi);
	//Sort
	for (int i = hi - 1; i > lo; --i)
	{
		std::swap(a[0], a[i]);
		downHeap(a, lo, i);
	}
}
//---------------------------------------------------------------------------

//--------------------------------Merge Sort---------------------------------
//hi is the highest index, size is an array size
template <typename T>
void merge(T *a, int lo, int mid, int hi)
{
	int index = 0, l = lo, h = mid + 1;
	T *temp = new T[hi - lo + 1];
	while (l <= mid && h <= hi)
	{
		if (a[l] < a[h])
			temp[index++] = a[l++];
		else
			temp[index++] = a[h++];
	}
	while (l <= mid)
		temp[index++] = a[l++];
	while (h <= hi)
		temp[index++] = a[h++];

	for (int i = 0; i < hi - lo + 1; i++)
		a[lo + i] = temp[i];
	delete[] temp;
}

template <typename T>
void mergeS(T *a, int lo, int hi) //We need this function to convert array size to its last index
{
	if (lo < hi)
	{
		int mid = lo + (hi - lo) / 2;
		mergeS(a, lo, mid);
		mergeS(a, mid + 1, hi);
		merge(a, lo, mid, hi);
	}
}

template <typename T>
void mergeSort(T *a, int lo, int size) //An actual sort
{
	int hi = size - 1;
	mergeS(a, lo, hi);
}
//---------------------------------------------------------------------------