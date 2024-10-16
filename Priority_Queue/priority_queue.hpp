#pragma warning(disable:4996)
#pragma once

#include <utility>
#include <cstdio>


namespace moran {
	struct Date {
		Date(int year, int month, int day)
			:_year(year),
			_month(month),
			_day(day)
		{}

		void print()
		{
			printf("Äê/ÔÂ/ÈÕ£º%4d/%02d/%02d\n", _year, _month, _day);
		}
		int _year;
		int _month;
		int _day;
	};
	bool operator<(const Date& d1, const Date& d2)
	{
		if (d1._year < d2._year ||
			(d1._year == d2._year && d1._month < d2._month) ||
			(d1._year == d2._year && d1._month == d2._month && d1._day < d2._day))
			return true;
		return false;
	}
	bool operator==(const Date& d1, const Date& d2)
	{
		return d1._year == d2._year && d1._month == d2._month && d1._day == d2._day;
	}
	bool operator>(const Date& d1, const Date& d2)
	{
		return !(d1<d2 || d1 == d2);
	}
	
	template<class T>
	struct less {
		bool operator()(const T& x, const T& y)
		{
			return x < y;
		}
	};
	template<class T>
	struct less<T*>
	{
		bool operator()(T* x, const T* y)
		{
			return *x < *y;
		}
	};
	template<>
	struct less<Date*>{
		bool operator()(const Date* x,const Date*  y)
		{
			return *x < *y;
		}
	};

	template<class T>
	struct greater {
		bool operator()(const T& x, const T& y)
		{
			return x > y;
		}
	};

	template<class T, class Container, class Compare = less<T>>
	class priority_queue {
	private:
		void down(size_t u)
		{
			Compare com;
			size_t child = u * 2+1;
			while (child < _ctnr.size())
			{
				if (child + 1 < _ctnr.size() && com(_ctnr[child] , _ctnr[child + 1]))
					child = child + 1;
				if (com(_ctnr[u], _ctnr[child]))
				{
					std::swap(_ctnr[u], _ctnr[child]);
					u = child;
					child = u * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
		void up(size_t u)
		{
			Compare com;
			size_t parent = (u-1) / 2;
			while (u)
			{
				if (com(_ctnr[parent] ,_ctnr[u]))
				{
					std::swap(_ctnr[parent], _ctnr[u]);
					u = parent;
					parent = (u - 1) / 2;
				}
				else break;
			}
		}
		void make_stack()
		{
			for (int i = (_ctnr.size() - 2) / 2; i >= 0; i--)
			{
				down(i);
			}
		}
	public:
		priority_queue(const Container& ctnr = Container())
		{
			for (auto& e : ctnr)
			{
				_ctnr.push_back(e);
			}
			make_stack();
		}
		T& top()
		{
			return _ctnr.front();
		}
		const T& top() const
		{
			return _ctnr.front();
		}
		void push(const T& value)
		{
			_ctnr.push_back(value);
			up(_ctnr.size() - 1);
		}
		void pop()
		{
			std::swap(_ctnr[0], _ctnr[_ctnr.size() - 1]);
			_ctnr.pop_back();
			down(0);
		}
		bool empty() const
		{
			return _ctnr.empty();
		}
		size_t size() const
		{
			return  _ctnr.size();
		}
	private:
		Container _ctnr;
	};
}
