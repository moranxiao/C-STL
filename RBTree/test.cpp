#include <iostream>
#include "RBTree.hpp"

using namespace std;
using namespace moran;


int main()
{
	//int arr[] = { 34, 12, 56, 78, 3, 45, 67, 89, 23, 90,
	// 11, 15, 88, 67, 32, 54, 76, 85, 1, 4,
	// 29, 42, 61, 71, 99, 28, 38, 92, 10, 5,
	// 18, 79, 13, 36, 75, 20, 30, 99, 2, 25,
	// 50, 80, 73, 14, 48, 58, 44, 95, 8, 16,
	// 19, 22, 39, 64, 63, 100, 7, 41, 24, 49,
	// 70, 72, 91, 84, 33, 87, 35, 97, 60, 86,
	// 57, 77, 26, 65, 62, 37, 98, 83, 6, 40,
	// 27, 55, 82, 17, 74, 46, 69, 47, 66, 93,
	// 81, 94, 9, 14, 88, 1, 53, 59, 12, 72 };
	//int arr[] = { 34, 12, 56, 78, 3, 45, 67, 89, 23, 90 };
	int arr[] = { 234, 786, 123, 456, 789, 45, 678, 321, 987, 234,
	 567, 890, 12, 34, 567, 890, 123, 456, 789, 912,
	 101, 202, 303, 404, 505, 606, 707, 808, 909, 111,
	 222, 333, 444, 555, 666, 777, 888, 999, 100, 200,
	 300, 400, 500, 600, 700, 800, 900, 50, 150, 250,
	 350, 450, 550, 650, 750, 850, 950, 19, 39, 59,
	 79, 99, 199, 299, 399, 499, 599, 699, 799, 899,
	 100, 350, 150, 450, 750, 850, 990, 520, 430, 640,
	 870, 390, 920, 420, 230, 640, 770, 890, 50, 25 };
	RBTree<int, int> rbt;
	for (auto e : arr)
	{
		rbt.Insert(make_pair(e, e));
	}
	cout << rbt.IsLegal() << endl;
	rbt.InorderPrint();
	return 0;
}