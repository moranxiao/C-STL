#pragma once

#include <utility>

template <class K,class T,size_t N>
struct BTreeNode {
	BTreeNode()
	_data(T()), _parent(nullptr), _n(0)
	{
		for (int i = 0; i <= N; i++)
		{
			_keys[i] = K();
			_subs[i] = nullptr;
		}
		_subs[N + 1] = nullptr;
	}
	T _data;
	K _keys[N + 1];
	BTreeNode* _subs[N + 2];
	int _n;
	BTreeNode* _parent;
};

template<class K,class T,size_t N>
class BTree {
	typedef BTreeNode<K,T, N> Node;
public:
	std::pair<Node*, int> Find(const K& key)
	{
		
	}
	bool Insert(const K& key,const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node;
			_root->_keys[0] = key;
			_root->_data = data;
			_root->_n = 1;
			return true;
		}
		std::pair<Node*,int> p = Find(key);
		//如果关键字已存在，则不插入
		if (p.second != -1) return false;
		Node* parent = p.first;


		
	}
private:
	void InsertKey(const K& key,Node* node)
	{
		for (size_t i = node->_n; i > 0; i--)
		{
			if (node->_keys[i - 1] > key)
			{
				node->_keys[i] = node->_keys[i - 1];
				
			}
		}
	}
private:
	Node* _root = nullptr;
};