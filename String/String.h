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
	//Ĭ�ϳ�Ա����
	String(const char* str = "");

	String(const String& s);
	//������ʹ�ø�ֵ���ŵ�ֻ������ֵ����ֵ������������������������
	String& operator=(const String& s);
	~String();
	void swap(String& s)
	{
		std::swap(s._ptr, _ptr);
		std::swap(s._capacity, _capacity);
		std::swap(s._size, _size);
	}
	//������
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
	//��
	void push_back(const char c);
	void push_back(const char* str);
	void push_back(const String& s);

	String& operator+=(const char c);
	String& operator+=(const char* str);
	String& operator+=(const String& s);

	String& insert(size_t pos, const char* str); 

	String& insert(size_t pos, const String& s);

	//ɾ
	void clear();
	String& erase(size_t pos, size_t len = npos);

	//��
	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	size_t find(const char c, size_t pos = 0) const;
	size_t find(const char* str, size_t pos = 0) const;
	//����size\capacity
	void reserve(size_t capacity);
	void resize(size_t sz, char c = '\0');

	//��ȡ��Ϣ
	const char* c_str() const;

	bool empty() const;
	size_t size() const;
	size_t capacity() const;
	//��ϵ�����
	bool operator<=(const String s);
	bool operator==(const String s);
	bool operator>(const String s);
	bool operator<(const String s);
	bool operator>=(const String s);
	bool operator!=(const String s);
	//const��һģһ�� ֻ��Ҫ�Ӹ�const�Ϳ����ˣ�const����ֻ�ܵ���const����
private:
	char* _ptr;
	size_t _size;
	size_t _capacity;
};