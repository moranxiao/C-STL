#pragma warning(disable:4996)
#pragma once
#include <utility>


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
			return _finish-1;
		}
		reverse_iterator rend()
		{
			return _start-1;
		}
		const_reverse_iterator begin() const
		{
			return _finish-1;
		}
		const_reverse_iterator end() const
		{
			return _start-1;
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
			//因为v是const类型，自然要调用const迭代器咯
			vector tmp(v.cbegin(), v.cend());
			std::swap(_start, tmp._start);
			std::swap(_finish, tmp._finish);
			std::swap(_end_of_storage, tmp._end_of_storage);
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
		//删
		void pop_back()
		{
			if (!empty())
			{
				_finish--;
			}
		}
		//改
		
		//查



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
		void resize(size_t n,const T& value = T())
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