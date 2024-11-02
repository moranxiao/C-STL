#pragma once
#include <vector>

namespace ClosedHash {
	
	enum State {
		DELETE,
		EMPTY,
		EXIST
	};

	template<class T>
	struct HashData{
		HashData(const T& data = T(), State st = EMPTY)
			:_data(data),
			_st(st)
		{}
		T _data;
		State _st;
	};

	template <class K,class T,class KeyOfT>
	class HashTable {
	public:
		
		bool Insert(const )s
		{

		}
	private:
		std::vector<T> _table;
	};
}

namespace Bucket {

}