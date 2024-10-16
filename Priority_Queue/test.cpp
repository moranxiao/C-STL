#include <iostream>
#include <vector>
#include <deque>
#include <list>

#include "priority_queue.hpp"


using std::cout;
using std::cin;
using std::endl;

using namespace moran;



int main()
{
	//priority_queue<int, std::vector<int>> heap(std::vector<int>({9,212,123,44,49,8,5,10,31}));
	//while (!heap.empty())
	//{
	//	cout << heap.top() << ' ';
	//	heap.pop();
	//}
	priority_queue<Date*, std::vector<Date*>> heap;
	//Date d1(2024, 10, 16);
	//Date d2(2023, 9, 16);
	//Date d3(2024, 11, 15);
	//Date d4(2022, 7, 3);
	//Date d5(2025, 3, 2);
	//Date d6(2025, 2, 2);
	//Date d7(2023, 12, 17);
	//heap.push(d1);
	//heap.push(d2);
	//heap.push(d3);
	//heap.push(d4);
	//heap.push(d5);
	//heap.push(d6);
	//heap.push(d7);
	//while (!heap.empty())
	//{
	//	heap.top().print();
	//	heap.pop();
	//}
	Date d1(2024, 10, 16);
	Date d2(2023, 9, 16);
	Date d3(2024, 11, 15);
	Date d4(2022, 7, 3);
	Date d5(2025, 3, 2);
	Date d6(2025, 2, 2);
	Date d7(2023, 12, 17);
	heap.push(&d1);
	heap.push(&d2);
	heap.push(&d3);
	heap.push(&d4);
	heap.push(&d5);
	heap.push(&d6);
	heap.push(&d7);
	while (!heap.empty())
	{
		heap.top()->print();
		heap.pop();
	}
	return 0;
}