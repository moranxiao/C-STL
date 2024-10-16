#pragma warning(disable:4996)
#pragma once

namespace moran {
	template<class T, class Container>
	class stack {
	public:
		stack(const Container& ctnr = Container())
		{
			for (auto e : ctnr)
			{
				_ctnr.push_back(e);
			}
		}
		void push(const T& value)
		{
			_ctnr.push_back(value);
		}
		void pop()
		{
			_ctnr.pop_back();
		}
		T& top()
		{
			return _ctnr.back();
		}
		T& top() const
		{
			return _ctnr.back();
		}
		bool empty() const 
		{
			return _ctnr.empty();
		}
		size_t size() const 
		{
			return _ctnr.size();
		}
	private:
		Container _ctnr;
	};
}
