#include "RBTree.hpp"


namespace moran {
	template<class K,class V,class Compare = std::less<K>>
	class map {
		struct MapKeyOfT {
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		
	private:
		RBTree<K, std::pair<K, V>, MapKeyOfT, Compare> _tree;
	};
}