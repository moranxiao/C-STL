#include <iostream>
#include <string>
#include "set.hpp"
#include "map.hpp"


using std::cout;
using std::cin;
using std::endl;
using namespace moran;

int main()
{
	std::string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
	map<std::string, int> mp;
	for (auto& e : arr)
	{
		mp[e]++;
	}
	for (auto& e : mp)
	{
		cout << e.first << ':' << e.second << endl;
	}
	return 0;
}