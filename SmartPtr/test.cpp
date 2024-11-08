#include <iostream>
//#include <memory>

#include "unique_ptr.hpp"
#include "auto_ptr.hpp"
#include "shared_ptr.hpp"

using namespace std;

//void test1()
//{
//	auto_ptr<int> p1(new int(4));
//	auto_ptr<int> p2(p1);
//	cout << *p2;
//	cout << *p1;
//
//}

//void test2()
//{
//	unique_ptr<int> p1(new int(4));
//	unique_ptr<int> p2(p1);
//	p1 = p2;
//}

int main()
{
	//moran::TestAutoptr();
	//test1();

	moran::TestSharedptr();
	return 0;
}