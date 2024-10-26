#include <iostream>

#include "AVLTree.hpp"

using namespace std;
using namespace moran;

int main()
{
	//int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int arr[] = {
	47, 83, 24, 36, 15, 98, 62, 3, 77, 56,
	11, 29, 73, 1, 59, 92, 5, 18, 79, 65,
	14, 88, 22, 34, 70, 45, 95, 40, 81, 32,
	68, 4, 53, 78, 60, 20, 39, 30, 74, 97,
	86, 9, 17, 63, 87, 12, 33, 50, 19, 71,
	2, 23, 69, 48, 55, 10, 75, 27, 99, 13,
	35, 44, 76, 67, 16, 41, 25, 8, 49, 72,
	66, 52, 7, 26, 100, 57, 42, 84, 54, 64,
	46, 38, 80, 37, 90, 72, 61, 82, 93, 91
	};
	AVLTree<int, int> avl;
	for (auto e : arr)
	{
		avl.Insert(make_pair(e, e));
	}
	cout << avl.IsLegal();
	return 0;
}