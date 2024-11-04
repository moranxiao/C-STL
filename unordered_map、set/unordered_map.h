#pragma once


#include "HashTable.hpp"



namespace moran {
	using namespace Bucket;


	template<class K, class V,class Hash = HashFunc<K>>
	class unordered_map {
		template<class K,class V>
		struct MapKeyOfT {
			const K& operator()(const std::pair<K,V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename HashTable<K, std::pair<K,V>, Hash, MapKeyOfT<K,V>>::iterator iterator;
		iterator begin()
		{
			return _ht.begin();
		}
		iterator end()
		{
			return _ht.end();
		}
		std::pair<iterator, bool> insert(const std::pair<K,V>& data)
		{
			return _ht.Insert(data);
		}
		iterator find(const K& key)
		{
			return _ht.Find(key);
		}
		V& operator[](const K& key)
		{
			std::pair<iterator,bool> p = insert(std::make_pair(key,V()));
			return p.first->second;
		}
	private:
		HashTable<K, std::pair<K, V>, Hash, MapKeyOfT<K,V>> _ht;
	};
}