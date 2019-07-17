#include <iostream>
#include "SplayTree.h"
using namespace std;

int main()
{
	SplayTree<string, string> arr;
	arr.Add("ba","first");
	arr.Add("ab", "second");
	arr.Add("cc", "third");
	system("pause");
	return 0;
}
