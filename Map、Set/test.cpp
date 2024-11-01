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
	std::string arr[] = { "ƻ��", "����", "ƻ��", "����", "ƻ��", "ƻ��", "����", "ƻ��", "�㽶", "ƻ��", "�㽶" };
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