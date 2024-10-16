#pragma warning(disable:4996)
#pragma once


namespace moran {
	template<class T,class Container>
	class queue {
	public:
		queue(const Container& ctnr = Container())
		{
			for (auto& e : ctnr)
				_ctnr.push_back(e);
		}
		
		void push(const T& value)
		{
			_ctnr.push_back(value);
		}
		void pop()
		{
			_ctnr.pop_front();
		}
		T& back()
		{
			return _ctnr.back();
		}
		T& front()
		{
			return _ctnr.front();
		}
		const T& back() const
		{
			return _ctnr.back();
		}
		const T& front() const
		{
			return _ctnr.front();
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