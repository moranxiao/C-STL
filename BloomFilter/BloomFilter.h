#pragma once

#include <bitset>
#include <string>


namespace moran {

	struct HashBKDR
	{
		// BKDR
		size_t operator()(const std::string& key)
		{
			size_t val = 0;
			for (auto ch : key)
			{
				val *= 131;
				val += ch;
			}

			return val;
		}
	};

	struct HashAP
	{
		// BKDR
		size_t operator()(const std::string& key)
		{
			size_t hash = 0;
			for (size_t i = 0; i < key.size(); i++)
			{
				if ((i & 1) == 0)
				{
					hash ^= ((hash << 7) ^ key[i] ^ (hash >> 3));
				}
				else
				{
					hash ^= (~((hash << 11) ^ key[i] ^ (hash >> 5)));
				}
			}
			return hash;
		}
	};

	struct HashDJB
	{
		// BKDR
		size_t operator()(const std::string& key)
		{
			size_t hash = 5381;
			for (auto ch : key)
			{
				hash += (hash << 5) + ch;
			}

			return hash;
		}
	};

	template<size_t N, class K = std::string, class Hash1 = HashBKDR,class Hash2 = HashAP,class Hash3 = HashDJB>
	class BloomFilter {
	public:
		void Set(const K& key)
		{
			size_t hash1 = Hash1()(key) % (N*_ratio);
			_bits->set(hash1);

			size_t hash2 = Hash2()(key) % (N * _ratio);
			_bits->set(hash2);

			size_t hash3 = Hash3()(key) % (N * _ratio);
			_bits->set(hash3);
		}
		bool Test(const K& key)
		{
			size_t hash1 = Hash1()(key) % (N * _ratio);
			if (!_bits->test(hash1))
				return false;

			size_t hash2 = Hash2()(key) % (N * _ratio);
			if (!_bits->test(hash2))
				return false;

			size_t hash3 = Hash3()(key) % (N * _ratio);
			if (!_bits->test(hash3))
				return false;
			return true;
		}

		void Reset(const K& key);
		//不能直接删除标志位，会对其他数据有影响
		//勉强可以对每位增加引用计数，每次删除时，对引用计数--，但是增加了内存的使用，降低了布隆过滤器的优势，得不偿失
	private:
		static const size_t _ratio = 5; //负载因子
		std::bitset<N * _ratio>* _bits = new std::bitset<N * _ratio>;//标准库的位图是静态数组
	};
	using namespace std;
	void TestBloomFilter2()
	{
		srand(time(0));
		const size_t N = 100000;
		BloomFilter<N> bf;
		cout << sizeof(bf) << endl;

		std::vector<std::string> v1;
		std::string url = "https://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html";

		for (size_t i = 0; i < N; ++i)
		{
			v1.push_back(url + std::to_string(1234 + i));
		}

		for (auto& str : v1)
		{
			bf.Set(str);
		}

		// 相似
		std::vector<std::string> v2;
		for (size_t i = 0; i < N; ++i)
		{
			std::string url = "http://www.cnblogs.com/-clq/archive/2021/05/31/2528153.html";
			url += std::to_string(rand() + i);
			v2.push_back(url);
		}

		size_t n2 = 0;
		for (auto& str : v2)
		{
			if (bf.Test(str))
			{
				++n2;
			}
		}
		cout << "相似字符串误判率:" << (double)n2 / (double)N << endl;

		std::vector<std::string> v3;
		for (size_t i = 0; i < N; ++i)
		{
			string url = "zhihu.com";
			url += std::to_string(rand() + i);
			v3.push_back(url);
		}

		size_t n3 = 0;
		for (auto& str : v3)
		{
			if (bf.Test(str))
			{
				++n3;
			}
		}
		cout << "不相似字符串误判率:" << (double)n3 / (double)N << endl;
	}

}

