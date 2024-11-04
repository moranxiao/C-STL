#include <iostream>


#include "unordered_map.h"
#include "unordered_set.h"

using namespace moran;
using std::cout;
using std::cin;
using std::endl;

int main()
{
	unordered_map<std::string, int> mp;
	unordered_set<int> st;
	std::string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };

	for (auto& str : arr)
	{
		mp[str]++;
	}
	return 0;
}