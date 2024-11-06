#include <iostream>
#include <vector>
#include "vector.hpp"
using std::cout;
using std::cin;
using std::endl;

using namespace moran;


vector<int> getv()
{
	vector<int> v1(5, 10);
	return v1;
}

int main()
{
	//vector<int> v1;
	//vector<int> v2(10);
	//for (auto e : v2)
	//{
	//	cout << e << ' ';
	//}
	//cout << endl;
	//int arr[] = { 1,2,3,4,5,6,7,8 };
	//vector<int> v3(arr,arr+sizeof(arr)/sizeof(int));
	//for (auto e : v3)
	//{
	//	cout << e << ' ';
	//}
	//cout << endl;
	//v3.push_back(10);

	//for (auto e : v3)
	//{
	//	cout << e << ' ';
	//}
	//cout << endl;

	//vector<int> v4(v3);

	//for (auto e : v4)
	//{
	//	cout << e << ' ';
	//}
	////cout << endl;
	//std::vector<int> v = {1,2,3,4,5 };
	//std::vector<int>::const_iterator it = v.end();
	//it = v.insert(it-1, 1);
	//for (auto e : v)
	//{
	//	cout << e << ' ';
	//}
	//cout << *it << endl;
	//vector<int> v(3u, 1);
	//auto it = v.end();
	//for (int i = 0; i < 10; i++)
	//	it = v.insert(it, i);
	//for (auto e : v)
	//{
	//	cout << e << ' ';
	//}
	//	
	//int a[] = { 1,2,3,4,5,6,7,8,9,10 ,11};
	//vector<int> v(a, a + sizeof(a) / sizeof(int));
	//auto it = v.begin();
	//while(it < v.end())
	//{
	//	if (*it % 2 == 0)
	//		it = v.erase(it);
	//	else it++;
	//}
	//vector<int> v(10, 5);
	//for (auto e : v)
	//	cout << e << ' ';
	vector<int> v1(10, 5);
	vector<int> v2(std::move(v1));
	v1 = std::move(v2);
	return 0;
}