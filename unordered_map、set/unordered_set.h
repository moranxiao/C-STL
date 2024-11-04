#pragma once


#include "HashTable.hpp"


namespace moran {
	using namespace Bucket;



	template<class K,class Hash = HashFunc<K>>
	class unordered_set {
		template<class K>
		struct SetKeyOfT {
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename HashTable<K, K, Hash, SetKeyOfT<K>>::iterator iterator;
		iterator begin()
		{
			return _ht.begin();
		}
		iterator end()
		{
			return _ht.end();
		}
		std::pair<iterator, bool> insert(const K& key)
		{
			return _ht.Insert(key);
		}
		iterator find(const K& key)
		{
			return _ht.Find(key);
		}
	private:
		HashTable<K, K, Hash, SetKeyOfT<K>> _ht;
	};
}