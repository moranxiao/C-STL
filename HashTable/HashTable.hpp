#pragma once
#include <vector>
#include <utility>

namespace ClosedHash {
	
	template<class K>
	struct HashFunc {
		size_t operator()(const K& key)
		{
			return (size_t)key;
		}
	};
	template<>
	struct HashFunc<std::string>{
		size_t operator()(const std::string& s)
		{
			size_t val = 0;
			for (auto e : s)
			{
				val *= 131;
				val += e;
			}
			return val;
		}
	};
	enum State {
		DELETE,
		EMPTY,
		EXIST
	};

	template<class K,class V>
	struct HashData{
		HashData(const std::pair<K,V>& kv = std::pair<K,V>(), State st = EMPTY)
			:_kv(kv),
			_st(st)
		{}
		std::pair<K,V> _kv;
		State _st;
	};

	template <class K,class V,class Hash = HashFunc<K>>
	class HashTable {
	public:
		
		bool Insert(const std::pair<K,V>& kv)
		{
			if (_table.size() == 0)
			{
				_table.resize(10);
			}
			else if(_size*10 / _table.size() >= 7) //扩容
			{
				HashTable<K, V> new_hash;
				new_hash._table.resize(_table.size() * 2);
				for (size_t i = 0; i < _table.size(); i++)
				{
					if (_table[i]._st == EXIST)
					{
						new_hash.Insert(_table[i]._kv);
					}
				}
				std::swap(_table, new_hash._table);
				
			}
			size_t pos = Hash()(kv.first) % _table.size();
			size_t i = pos;
			while (_table[i]._st == EXIST)
			{
				if (_table[i]._kv.first == kv.first)
				{
					return false;
				}
				i = (i + 1) % _table.size();
			}
			_size++;
			_table[i]._kv = kv;
			_table[i]._st = EXIST;
			return true;
		}
		std::pair<K, V>* Find(const K& key)
		{
			if (_size == 0) return nullptr;
			size_t pos = Hash()(key) % _table.size();
			size_t i = pos;
			while (_table[i]._st != EMPTY)
			{
				if (_table[i]._kv.first == key && _table[i]._st == EXIST)
				{
					return &_table[i]._kv;
				}

				i = (i + 1) % _table.size();
				//有可能整个表没有空，只有存在和删除
				if (i == pos) return nullptr;
			}
			return nullptr;
		}
		bool Erase(const K& key)
		{
			//如果哈希表里没有值，则直接返回
			if (_size == 0)
				return false;
			//找到映射位置
			size_t pos = Hash()(key) % _table.size();
			//线性探测
			size_t i = pos;
			while(_table[i]._st != EMPTY)
			{
				if (_table[i]._kv.first == key)
				{
					if (_table[i]._st == DELETE) return false;
					else
					{
						_size--;
						_table[i]._st = DELETE;
					}
				}
				i = (i + 1) % _table.size();
				//如果遍历一遍都没找到，说明没有
				if (i == pos)
					return false;
			}
			return false;
		}
	private:
		std::vector<HashData<K,V>> _table;
		size_t _size = 0;
	};


	void TestHT2()
	{
		std::string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };

		//HashTable<string, int, HashFuncString> countHT;
		HashTable<std::string, int> countHT;
		for (auto& str : arr)
		{
			auto ptr = countHT.Find(str);
			if (ptr)
			{
				ptr->second++;
			}
			else
			{
				countHT.Insert(make_pair(str, 1));
			}
		}
	}

}

namespace Bucket {
	template<class K,class V>
	struct HashNode {
		HashNode* _next;
		std::pair<K,V> _kv;
		HashNode(const std::pair<K,V>& kv, HashNode* next = nullptr)
			:_kv(kv),
			_next(next)
		{}
	};
	template<class K,class V>
	class HashTable {
		typedef HashNode<K, V> Node;

	public:
		~HashTable()
		{
			for (size_t i = 0; i < _table.size(); i++)
			{
				if (_table[i] == nullptr) continue;
				Node* cur = _table[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_table[i] = nullptr;
			}
		}
		bool Insert(const std::pair<K, V>& kv)
		{
			if (Find(kv.first) != nullptr) return false;
			if (_table.size() == 0)
			{
				_table.resize(10,nullptr);
			}
			else if (_size == _table.size()) //节点数等于桶数时需要扩容
			{
				HashTable new_hash;
				new_hash._table.resize(_table.size() * 2);
				for (size_t i = 0; i < _table.size(); i++)
				{
					if (_table[i] == nullptr) continue;
					Node* cur = _table[i];
					while (cur)
					{
						new_hash.Insert(cur->_kv);
						cur = cur->_next;
					}
				}
				_table.swap(new_hash._table);
			}
			size_t pos = kv.first % _table.size();
			Node* new_node = new Node(kv);
			new_node->_next = _table[pos];
			_table[pos] = new_node;
			_size++;
			return true;
		}
		std::pair<K, V>* Find(const K& key)
		{
			if (_size == 0) return nullptr;
			size_t pos = key % _table.size();
			Node* cur = _table[pos];
			while (cur)
			{
				if (cur->_kv.first == key) return &cur->_kv;
				cur = cur->_next;
			}
			return nullptr;
		}
		bool Erase(const K& key)
		{
			if (_size == 0) return false;
			size_t pos = key % _table.size();
			Node* prev = nullptr;
			Node* cur = _table[pos];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (prev == nullptr)
					{
						_table[pos] = nullptr;
					}
					else
					{
						prev->_next = cur->_next;
					}

					delete cur;
					_size--;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}
	private:
		std::vector<Node*> _table;		
		size_t _size = 0;// 存储有效数据个数
	};

	void test1()
	{
		int a[] = { 1, 11, 4, 15, 26, 7, 44,55,99,81,43,29,130,29,40,40,1,23,77,19,88,39,100,28};
		HashTable<int, int> hash;
		for (auto e : a)
		{
			hash.Insert(std::make_pair(e, e));
		}
		hash.Erase(130);
		hash.Erase(44);
		hash.Erase(2);
		hash.Erase(1);
		hash.Erase(77);
		hash.Erase(-1);

	}
}