#include <iostream>
#include <vector>
#include <deque>
#include <list>

#include "stack.hpp"


using std::cout;
using std::cin;
using std::endl;
using namespace moran;

int main()
{
	stack<int, std::vector<int>> st(std::vector<int>({1,3,5,7,9}));
	while (!st.empty())
	{
		cout << st.top() << ' ';
		st.pop();
	}
	return 0;
}