#include <iostream>
#include "String.h"
#include <string>

using std::cout;
using std::cin;
using std::endl;





int main()
{
	//std::string s("hello,world");
	//String s("hello wolrd");
	//cout << s << endl;
	//String s1(s);
	//cout << s1 << endl;
	//s1 = "hello String";
	//cout << s1 << endl;
	//cout << (s1 == s) << endl;
	//cout << (s1 >= s) << endl;
	//String s("hello world");
	//s += '\n';

	//s.push_back("I'm YYX");
	//cout << s << endl;
	//cout << s.c_str() << endl;
	//cout << s.find('Y') << endl;
	//for (auto e : s)
	//{
	//	cout << e;
	//}
	//cout << endl;
	String s("hello world");
	s.insert(100, "yyx");
	cout << s << endl;

	s.insert(5, "yyx");
	cout << s << endl;
	s.erase(5, 3);
	cout << s << endl;
	s.erase(5,-1);
	cout << s << endl;

	return 0;
}
