#include "RBTree.hpp"


namespace moran {

	template<class K,class Compare = std::less<K>>
	class set {	
		struct SetKeyOfT {
			const K& operator()(const K& data)
			{
				return data;
			}
		};
	public:
		using typename RBTree<K, K, SetKeyOfT, Compare>::iterator = iterator;
		iterator begin()
		{
			return _tree.begin;
		}
		iterator end()
		{
			return _tree.end();
		}
	public:
		std::pair<iterator, bool> insert(const K& key)
		{
			return _tree.Insert(key);
		}
	private:
		RBTree<K, K,SetKeyOfT,Compare> _tree;
	};
}