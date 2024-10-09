#pragma warning(disable:4996)
#include "String.h"

//默认成员函数
String::String(const char* str) //默认参数只在声明中，定义时不需要写明，即只写一次
	:_capacity(0),_size(0),_ptr(nullptr)
{
	if (str == nullptr)
	{
		assert(false);
		return;
	}
	_size = strlen(str);
	_capacity = _size + 1;
	_ptr = new char[_capacity];
	strncpy(_ptr, str, _size);
	_ptr[_size] = '\0';
}

String::String(const String& s)
{
	_capacity = s._capacity;
	_size = s._size;
	_ptr = new char[_capacity];
	strncpy(_ptr, s._ptr, s._size + 1);
}

String& String::operator=(const String& s)
{
	String tmp(s);
	std::swap(tmp._ptr, _ptr);
	std::swap(tmp._capacity, _capacity);
	std::swap(tmp._size, _size);
	return *this;
}

String::~String()
{
	delete[] _ptr;
}
//增
void String::push_back(const char c)
{
	if (_size + 1 >= _capacity)
	{
		reserve(_capacity == 0 ? 4 : 2*_capacity);
	}
	_ptr[_size] = c;
	_ptr[++_size] = '\0';
}
void String::push_back(const char* str)
{
	size_t len = strlen(str);
	while (len + _size >= _capacity)
	{
		reserve(2 * _capacity);
	}
	strncpy(_ptr + _size, str, len);
	_size += len;
	_ptr[_size] = '\0';
}
void String::push_back(const String& s)
{
	push_back(s._ptr);
}

String& String::operator+=(const char c)
{
	push_back(c);
	return *this;
}
String& String::operator+=(const char* str)
{
	push_back(str);
	return *this;
}
String& String::operator+=(const String& s)
{
	push_back(s);
	return *this;
}

String& String::insert(size_t pos, const char* str) //pos前插入
{
	size_t len = strlen(str);
	while (_size + len >= _capacity)
		reserve(2 * _capacity);
	if (pos >= _size)
	{
		*this += str;
	}
	else
	{
		for (int i = _size-1; i >= pos; i--)
		{
			_ptr[i + len] = _ptr[i];
		}
		strncpy(_ptr + pos, str, len);
	}
	_size += len;
	_ptr[_size] = '\0';
	return *this;
}
String& String::insert(size_t pos, const String& s)
{
	return insert(pos, s._ptr);
}



//删
void String::clear()
{
	_size = 0;
}
String& String::erase(size_t pos, size_t len)
{
	if (len == npos)
	{
		_size = pos;
		_ptr[pos] = '\0';
		return *this;
	}
	if (pos + len >= _size)
		_size = std::min(pos - 1, (size_t)0);
	else
	{
		for (int i = pos + len; i < _size; i++)
		{
			_ptr[i - len] = _ptr[i];
		}
		_size -= len;
		_ptr[_size] = '\0';
	}
	return *this;
}

//查
char& String::operator[](size_t index)
{
	return _ptr[index];
}
const char& String::operator[](size_t index) const
{
	return _ptr[index];
}
size_t String::find(const char c, size_t pos) const
{
	assert(pos < _size);
	char str[] = { c,'\0' };
	const char* ptr = strstr(_ptr + pos, str);
	if (ptr == nullptr)
		return npos;
	return (size_t)(ptr - _ptr);
}
size_t String::find(const char* str, size_t pos) const
{
	assert(pos < _size);
	const char* ptr = strstr(_ptr + pos, str);
	if (ptr == nullptr)
		return npos;
	return (size_t)(ptr - _ptr);
}


//调整size\capacity
void String::reserve(size_t capacity)
{
	if (capacity <= _capacity)
		return;
	_capacity = capacity;
	char* tmp = new char[_capacity];
	strncpy(tmp, _ptr, _size + 1);
	delete[] _ptr;
	_ptr = tmp;
}
void String::resize(size_t sz, char c)
{
	while (sz >= _capacity)
	{
		reserve(2*_capacity);
	}
	if (sz > _size)
	{
		for (int i = _size; i < sz; i++)
		{
			_ptr[i] = c;
		}
		_size = sz;
	}
	else
	{
		_size = sz;
	}
	_ptr[_size] = '\0';
}


//获取信息
const char* String::c_str() const
{
	return _ptr;
}

bool String::empty() const
{
	return _size == 0;
}
size_t String::size() const
{
	return _size;
}
size_t String::capacity() const
{
	return _capacity;
}



//关系运算符重载
bool String::operator<=(const String s)
{
	return (*this < s) || (*this == s);
}

bool String::operator>(const String s)
{
	return !(*this <= s);
}

bool String::operator==(const String s)
{
	return strcmp(s._ptr, _ptr) == 0;
}

bool String::operator<(const String s)
{
	return strcmp(_ptr, s._ptr) < 0;
}
bool String::operator>=(const String s)
{
	return !(*this < s);
}
bool String::operator!=(const String s)
{
	return !(*this == s);
}


std::ostream& operator<<(std::ostream& out, const String& s)
{
	out << s._ptr;
	return out;
}
std::istream& operator>>(std::istream& in, String& s) //一个字符一个字符的读
{
	s.clear();
	const int N = 256;
	char buffer[N];
	int idx = 0;
	char c = in.get();
	while (c != ' ' && c != '\n')
	{
		if (idx == N-1)
		{
			buffer[N - 1] = '\0';
			s += buffer;
			idx = 0;
		}
		buffer[idx++] = c;
		c = in.get();
	}
	buffer[idx] = '\0';
	s += buffer;
	return in;
}

