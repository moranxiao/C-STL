#include "RBTree.hpp"


namespace moran {
	template<class K,class V,class Compare = std::less<K>>
	class map {
		struct MapKeyOfT {
			const K& operator()(const std::pair<K,V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename RBTree<K, std::pair<K, V>, MapKeyOfT, Compare>::iterator iterator;
	
		iterator begin()
		{
			return _tree.begin();
		}
		iterator end()
		{
			return _tree.end();
		}
	public:
		std::pair<iterator, bool> insert(const std::pair<K, V>& kv)
		{
			return _tree.Insert(kv);
		}
		V& operator[](const K& key)
		{
			iterator it = insert(std::make_pair(key, V())).first;
			return it->second;
		}
	private:
		RBTree<K, std::pair<K, V>, MapKeyOfT, Compare> _tree;
	};
}