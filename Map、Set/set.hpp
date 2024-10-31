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
		
	private:
		RBTree<K, K,SetKeyOfT,Compare> _tree;
	};
}