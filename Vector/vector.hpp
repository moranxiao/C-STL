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
		//������
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

		//���ɣ�rbeginӦ��ָ��_finish����_finish��ǰһ��
		// rendӦ��ָ��_start����_start��ǰһ��
		///////////////////
		// ָ��_finish��_start��ǰһ��
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
		//ΪʲôҪ�������int���͵��أ���Ϊ��vector<int>(10,3)����ʱ��10��3�ᱻ��Ϊ��int���ͣ�
		// ����size_t��ƥ�䣬��������������汾�Ĺ���
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
		//�ϰ�˼ά
		vector(const vector& v)
		{
			//��Ϊ�β�v��const���ͣ���ȻҪ����const��������
			vector tmp(v.cbegin(), v.cend());
			std::swap(_start, tmp._start);
			std::swap(_finish, tmp._finish);
			std::swap(_end_of_storage, tmp._end_of_storage);
			std::cout << "���" << std::endl;
		}
		vector(vector&& v)
		{
			swap(v);
			std::cout << "�ƶ�����" << std::endl;
		}
		//����ֱ��ѡ��ֵ���ݣ���������ÿ������캯����ֱ�ӿ�������һ����ʱ����swap��Դת�ƹ�������
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

		//��
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
		//ɾ
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
		//��
		T& operator[](size_t index)
		{
			assert(size() - 1 >= index);
			return _start[index];
		}
		//��
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
		//��������ָ����ά��vector
		iterator _start = nullptr;
		iterator _finish = nullptr; //ָ�����һ��Ԫ�ص���һ��λ��
		iterator _end_of_storage = nullptr; //ָ�����һ���ռ����һ��λ��
	};
}