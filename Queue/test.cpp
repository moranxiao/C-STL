#include <iostream>
#include <vector>
#include <deque>
#include <list>

#include "queue.hpp"


using std::cout;
using std::cin;
using std::endl;
using namespace moran;

int main()
{
	queue<int, std::deque<int>> q;
	for (int i = 1; i <= 15; i += 3)
	{
		q.push(i);
	}
	while (!q.empty())
	{
		cout << q.front() << " | " << q.back() << endl;
		q.pop();
	}
	
	return 0;
}