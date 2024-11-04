#pragma once
#include <vector>
#include <utility>
#include <string>




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

	template<class K>
	struct HashFunc {
		size_t operator()(const K& key)
		{
			return (size_t)key;
		}
	};
	template<>
	struct HashFunc<std::string> {
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
	template<class T>
	struct HashNode {
		HashNode* _next;
		T _data;
		HashNode(const T& data = T(), HashNode* next = nullptr)
			:_data(data),
			_next(next)
		{}
	};

	template<class K, class T, class Hash, class KeyOfT>
	class HashTable;

	template<class K, class T, class Hash, class KeyOfT>
	struct __HashIterator {
		typedef HashNode<T> Node;
		typedef HashTable<K, T, Hash, KeyOfT> HT;
		typedef __HashIterator<K, T, Hash, KeyOfT> Self;
		__HashIterator(Node* node, HT* pht)
			:_node(node),
			_pht(pht)
		{}
		Self operator++()
		{
			if (_node->_next == nullptr)
			{
				Hash hash;
				KeyOfT kot;
				size_t i = hash(kot(_node->_data)) % _pht->_table.size();
				for (i = i + 1; i < _pht->_table.size(); i++)
				{
					if (_pht->_table[i] == nullptr) continue;
					_node = _pht->_table[i];
					break;
				}
				if(i == _pht->_tables.size())
					_node = nullptr;
			}
			else
			{
				_node = _node->_next;
			}
			return *this;
		}
		bool operator==(const Self& other)
		{
			return _node == other._node;
		}
		bool operator!=(const Self& other)
		{
			return _node != other._node;
		}
		T* operator->()
		{
			return &_node->_data;
		}
		T& operator*()
		{
			return _node->_data;
		}
		HT* _pht;
		Node* _node;
	};
	template<class K,class T,class Hash,class KeyOfT>
	class HashTable {
		template<class K, class T, class Hash, class KeyOfT>
		friend struct __HashIterator;
		typedef HashNode<T> Node;
	public:
		typedef __HashIterator<K, T, Hash, KeyOfT> iterator;

		iterator begin()
		{
			if (_size == 0) return iterator(nullptr, this);
			for (size_t i = 0; i < _table.size(); i++)
			{
				if (_table[i] == nullptr) continue;
				return iterator(_table[i], this);
			}
			return end();
		}
		iterator end()
		{
			return iterator(nullptr, this);
		}
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
		std::pair<iterator,bool> Insert(const T& data)
		{
			KeyOfT kot;
			iterator it = Find(kot(data));
			if (it != end())
			{
				return std::make_pair(it,false);
			}
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
						new_hash.Insert(cur->_data);
						cur = cur->_next;
					}
				}
				_table.swap(new_hash._table);
			}
			Hash hash;
			size_t pos = hash(kot(data)) % _table.size();
			Node* new_node = new Node(data);
			new_node->_next = _table[pos];
			_table[pos] = new_node;
			_size++;
			return std::make_pair(iterator(new_node, this), true);
		}
		iterator Find(const K& key)
		{
			Hash hash;
			if (_size == 0) return end();
			size_t pos = hash(key) % _table.size();
			Node* cur = _table[pos];
			while (cur)
			{
				if (cur->_data.first == key) return iterator(cur, this) ;
				cur = cur->_next;
			}
			return end();
		}
		bool Erase(const K& key)
		{
			Hash hash;
			if (_size == 0) return false;
			size_t pos = hash(key) % _table.size();
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
}