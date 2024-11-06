#pragma warning(disable:4996)
#pragma once
#include <utility>
#include <cassert>

namespace moran {
	template <typename T>
	class vector {
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef T* reverse_iterator;
		typedef const T* const_reverse_iterator;
		//迭代器
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator cbegin() const
		{
			return _start;
		}
		const_iterator cend() const
		{
			return _finish;
		}

		//存疑？rbegin应该指向_finish还是_finish的前一个
		// rend应该指向_start还是_start的前一个
		///////////////////
		// 指向_finish和_start的前一个
		// 
		reverse_iterator rbegin()
		{
			return _finish - 1;
		}
		reverse_iterator rend()
		{
			return _start - 1;
		}
		const_reverse_iterator begin() const
		{
			return _finish - 1;
		}
		const_reverse_iterator end() const
		{
			return _start - 1;
		}
	public:

		vector() = default;
		~vector()
		{
			delete[] _start;
		}
		vector(size_t n, const T& value = T())
		{
			resize(n, value);
		}
		//为什么要重载这个int类型的呢？因为当vector<int>(10,3)构造时，10和3会被认为是int类型，
		// 觉得size_t不匹配，会走下面迭代器版本的构造
		vector(int n, const T& value = T())
		{
			resize(n, value);
		}
		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}
		//老板思维
		vector(const vector& v)
		{
			//因为形参v是const类型，自然要调用const迭代器咯
			vector tmp(v.cbegin(), v.cend());
			std::swap(_start, tmp._start);
			std::swap(_finish, tmp._finish);
			std::swap(_end_of_storage, tmp._end_of_storage);
			std::cout << "深拷贝" << std::endl;
		}
		vector(vector&& v)
		{
			swap(v);
			std::cout << "移动构造" << std::endl;
		}
		//参数直接选择值传递，这样会调用拷贝构造函数，直接拷贝出来一个临时对象，swap资源转移过来即可
		vector& operator=(vector v)
		{
			swap(v);
			return *this;
		}
		
		void swap(vector& v)
		{
			std::swap(v._start, _start);
			std::swap(v._finish, _finish);
			std::swap(v._end_of_storage, _end_of_storage);
		}

		//增
		void push_back(const T& value)
		{
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 4 : 2 * capacity());
			}
			*_finish = value;
			_finish++;
		}

		iterator insert(iterator pos, const T& value)
		{
			assert(pos >= _start && pos <= _finish);
			size_t index = pos - _start;
			if (capacity() == size())
			{
				reserve(capacity() * 2);
			}
			pos = index + _start;
			iterator it = _finish;
			while (it > pos)
			{
				*it = *(it-1);
				it--;
			}
			*it = value;
			_finish++;
			return pos;
		}
		iterator insert(iterator pos,T&& value)
		{
			assert(pos >= _start && pos <= _finish);
			size_t index = pos - _start;
			if (capacity() == size())
			{
				reserve(capacity() * 2);
			}
			pos = index + _start;
			iterator it = _finish;
			while (it > pos)
			{
				*it = *(it - 1);
				it--;
			}
			*it = std::forward(value);
			_finish++;
			return pos;
		}
		//删
		void pop_back()
		{
			if (!empty())
			{
				_finish--;
			}
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start && pos < _finish);
			iterator it = pos;
			while (it+1  < _finish)
			{
				*it = *(it + 1);
				it++;
			}
			_finish --;
			return pos;
		}
		iterator erase(iterator first, iterator last)
		{
			assert(first < last && first >= _start && last <= _finish);
			size_t len = last - first + 1;
			iterator it = first;
			while (it + len < _finish)
			{
				*it = *(it + len);
				it++;
			}
			_finish -= len;
			return first;
		}
		//改
		T& operator[](size_t index)
		{
			assert(size() - 1 >= index);
			return _start[index];
		}
		//查
		const T& operator[](size_t index) const
		{
			assert(size() - 1 >= index);
			return _start[index];
		}


		void reserve(size_t n)
		{
			if (n > capacity())
			{
				iterator ptr = new T[n];
				if (_start == nullptr)
				{
					_finish = _start = ptr;
					_end_of_storage = n + ptr;
				}
				else
				{
					for (size_t i = 0; i < size(); i++)
					{
						ptr[i] = _start[i];
					}
					_end_of_storage = ptr + n;
					_finish = ptr + size();
					delete[] _start;
					_start = ptr;
				}
			}
		}
		void resize(size_t n, const T& value = T())
		{
			if (n > capacity())
			{
				reserve(n);
			}
			if (n > size())
			{
				iterator it = _finish;
				_finish = _start + n;
				while (it != _finish)
				{
					*it = value;
					it++;
				}
			}
			else
			{
				_finish = _start + n;
			}
		}
		size_t size()
		{
			return _finish - _start;
		}
		size_t capacity()
		{
			return _end_of_storage - _start;
		}
		bool empty()
		{
			return _start == _finish;
		}
	private:
		//利用三个指针来维护vector
		iterator _start = nullptr;
		iterator _finish = nullptr; //指向最后一个元素的下一个位置
		iterator _end_of_storage = nullptr; //指向最后一个空间的下一个位置
	};
}