#pragma once

#include <utility>
#include <iostream>

template<class K,size_t N>
struct BTreeNode {
	BTreeNode()
	 :_parent(nullptr), _n(0)
	{
		for (int i = 0; i < N; i++)
		{
			_keys[i] = K();
			_subs[i] = nullptr;
		}
		_subs[N] = nullptr;
	}
	K _keys[N];
	BTreeNode* _subs[N+1];
	int _n;
	BTreeNode* _parent;
};

template<class K,size_t N>
class BTree {
	typedef BTreeNode<K, N> Node;
public:
	std::pair<Node*, int> Find(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (true)
		{
			if (cur == nullptr) break;
			int l = 0, r = cur->_n - 1;
			while (l < r)
			{
				int mid = (l + r + 1) / 2;
				if (cur->_keys[mid] > key) r = mid-1;
				else l = mid + 1;
			}
			if (cur->_keys[r] == key)
			{
				return { cur,r };
			}
			else if (cur->_keys[r] < key)
			{
				parent = cur;
				cur = cur->_subs[r + 1];
			}
			else {
				parent = cur;
				cur = cur->_subs[r];
			}
		}
		return { parent,-1 };
	}
	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node;
			_root->_keys[0] = key;
			_root->_n = 1;
			return true;
		}
		std::pair<Node*,int> p = Find(key);
		//如果关键字已存在，则不插入
		if (p.second != -1) return false;
		K midKey = key;
		Node* parent = p.first;
		Node* child = nullptr;
		while (true)
		{
			InsertKey(midKey, parent, child);
			if (parent->_n != N) //如果插入后容量没满，则插入完成
			{
				break;
			}
			//分裂
			Node* brother = new Node;
			int mid = parent->_n / 2;
			midKey = parent->_keys[mid];
			parent->_keys[mid] = K();

			int j = 0;
			for (size_t i = mid + 1; i < parent->_n; i++)
			{
				brother->_keys[j] = parent->_keys[i];
				brother->_subs[j] = parent->_subs[i];
				if(brother->_subs[j] != nullptr) brother->_subs[j]->_parent = brother;
				parent->_keys[i] = K();
				parent->_subs[i] = nullptr;
				j++;
			}
			brother->_n = j;
			brother->_subs[j] = parent->_subs[parent->_n];
			parent->_subs[parent->_n] = nullptr;

			if (brother->_subs[j] != nullptr) brother->_subs[j]->_parent = brother;

			parent->_n -= j + 1;

			if (parent->_parent == nullptr)
			{
				_root = new Node;
				_root->_keys[0] = midKey;
				_root->_subs[0] = parent;
				_root->_subs[1] = brother;
				brother->_parent = _root;
				parent->_parent = _root;
				_root->_n = 1;
				break;
			}
			else
			{
				brother->_parent = parent->_parent;
				parent = parent->_parent;
				child = brother;
			}
		}
		return true;
	}
	void Inorder()
	{
		_Inorder(_root);
	}
private:
	void _Inorder(Node* root)
	{
		if (root == nullptr) return;
		for (size_t i = 0; i < root->_n; ++i)
		{
			_Inorder(root->_subs[i]);
			std::cout << root->_keys[i] << ' ';
		}
		_Inorder(root->_subs[root->_n]);
	}
	void InsertKey(const K& key, Node* parent, Node* child)
	{
		int j = parent->_n - 1;
		while (j >= 0 && parent->_keys[j] > key)
		{
			parent->_keys[j + 1] = parent->_keys[j];
			parent->_subs[j + 2] = parent->_subs[j + 1];
			j--;
		}
		parent->_keys[j + 1] = key;
		parent->_subs[j + 2] = child;
		if (child != nullptr)
			child->_parent = parent;
		parent->_n++;
	}
private:
	Node* _root = nullptr;
};


void TestBTree()
{
	BTree<int, 3> bt;
	int arr[] = { 53, 139, 75, 49, 145, 36, 101 };
	for (auto e : arr)
	{
		bt.Insert(e);
	}
	bt.Inorder();
	return;
}