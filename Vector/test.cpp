#include "vector.hpp"
#include <iostream>


using std::cout;
using std::cin;
using std::endl;

using namespace moran;

int main()
{
	vector<int> v1;
	vector<int> v2(10);
	for (auto e : v2)
	{
		cout << e << ' ';
	}
	cout << endl;
	int arr[] = { 1,2,3,4,5,6,7,8 };
	vector<int> v3(arr,arr+sizeof(arr)/sizeof(int));
	for (auto e : v3)
	{
		cout << e << ' ';
	}
	cout << endl;
	v3.push_back(10);

	for (auto e : v3)
	{
		cout << e << ' ';
	}
	cout << endl;

	vector<int> v4(v3);

	for (auto e : v4)
	{
		cout << e << ' ';
	}
	cout << endl;
	return 0;
}