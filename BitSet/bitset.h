#pragma once

#include <vector>


namespace moran {
	template<size_t N>
	class bitset {
	public:
		bitset()
		{
			_bits.resize(N / 8 + 1);
		}
		
		bitset& set(size_t x)
		{
			if(x < N)
				_bits[x / 8] |= 1 << (x % 8);
			return *this;
		}
		bitset& reset(size_t x)
		{
			if(x < N)
				_bits[x / 8] &= ~(1 << (x % 8));
			return *this;
		}
		bool test(size_t x)
		{
			if (x >= N) return false;
			return _bits[x / 8] & (1 << (x % 8));
		}
	private:
		std::vector<char> _bits;
	};

	void test1()
	{
		bitset<100> bs;
		bs.set(10);
		bs.set(31);
		bs.set(74);
		bs.set(2);
		bs.set(99);
		std::cout << bs.test(10) << std::endl;
		std::cout << bs.test(11) << std::endl;
		std::cout << bs.test(31) << std::endl;
		std::cout << bs.test(2) << std::endl;
		std::cout << bs.test(99) << std::endl;
		std::cout << bs.test(74) << std::endl;
		std::cout << bs.test(100) << std::endl;
		bs.reset(10);
		bs.reset(31);
		bs.reset(74);
		bs.reset(2);
		bs.reset(99);
		std::cout << std::endl;
		std::cout << bs.test(10) << std::endl;
		std::cout << bs.test(11) << std::endl;
		std::cout << bs.test(31) << std::endl;
		std::cout << bs.test(2) << std::endl;
		std::cout << bs.test(99) << std::endl;
		std::cout << bs.test(74) << std::endl;
		std::cout << bs.test(100) << std::endl;

	}
}