#pragma warning(disable:4996)
#pragma once
#include <assert.h>
#include <cstring>
#include <utility>
#include <iostream>
#include <algorithm>


class String {
	friend std::ostream& operator<<(std::ostream& out, const String& s);
	friend std::istream& operator>>(std::istream& in,String& s);
public:
	typedef char* iterator;
	typedef const char* const_iterator;

	static const size_t npos = -1;
public:
	//默认成员函数
	String(const char* str = "");

	String(const String& s);
	//由于能使用赋值符号的只能是左值，左值不会立马消亡，可以用引用
	String& operator=(const String& s);
	~String();
	void swap(String& s)
	{
		std::swap(s._ptr, _ptr);
		std::swap(s._capacity, _capacity);
		std::swap(s._size, _size);
	}
	//迭代器
	iterator begin()
	{
		return _ptr;
	}
	const_iterator begin() const
	{
		return _ptr;
	}
	iterator end()
	{
		return _ptr+_size;
	}
	const_iterator end() const
	{
		return _ptr+_size;
	}
	//增
	void push_back(const char c);
	void push_back(const char* str);
	void push_back(const String& s);

	String& operator+=(const char c);
	String& operator+=(const char* str);
	String& operator+=(const String& s);

	String& insert(size_t pos, const char* str); 

	String& insert(size_t pos, const String& s);

	//删
	void clear();
	String& erase(size_t pos, size_t len = npos);

	//查
	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	size_t find(const char c, size_t pos = 0) const;
	size_t find(const char* str, size_t pos = 0) const;
	//调整size\capacity
	void reserve(size_t capacity);
	void resize(size_t sz, char c = '\0');

	//获取信息
	const char* c_str() const;

	bool empty() const;
	size_t size() const;
	size_t capacity() const;
	//关系运算符
	bool operator<=(const String s);
	bool operator==(const String s);
	bool operator>(const String s);
	bool operator<(const String s);
	bool operator>=(const String s);
	bool operator!=(const String s);
	//const版一模一样 只需要加个const就可以了，const对象只能调用const方法
private:
	char* _ptr;
	size_t _size;
	size_t _capacity;
};