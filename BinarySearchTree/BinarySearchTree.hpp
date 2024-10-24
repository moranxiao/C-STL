#pragma once 
#include <iostream>
#include <utility>


namespace moran {

	template<class K>
	struct BSTreeNode {
		BSTreeNode* _left;
		BSTreeNode* _right;
		K _value;
		BSTreeNode(const K& value = K(), BSTreeNode* left = nullptr, BSTreeNode* right = nullptr)
			:_value(value),
			_left(left),
			_right(right)
		{}
	};

	template<class K>
	class BSTree {
		typedef BSTreeNode<K> Node;
	public:
		BSTree() = default;
		BSTree(const BSTree& tree)
		{
			_root = _Copy(tree._root);
		}
		BSTree& operator=(BSTree tree)
		{
			std::swap(tree._root, _root);
			return *this;
		}
		~BSTree()
		{
			_Destructor(_root);
		}


		bool Insert(const K& value)
		{
			Node* new_node = new Node(value);
			if (_root == nullptr)
			{
				_root = new_node;
				return true;
			}
			Node* cur = _root;
			while (cur)
			{
				if (value > cur->_value)
				{
					if (nullptr == cur->_right)
					{
						cur->_right = new_node;
						return true;
					}
					cur = cur->_right;
				}
				else if (value < cur->_value)
				{
					if (nullptr == cur->_left)
					{
						cur->_left = new_node;
						return true;
					}
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}
			return false;
		}
		bool Find(const K& value)
		{
			Node* cur = _root;
			while (cur)
			{
				if (value == cur->_value) return true;
				else if (cur->_value < value) cur = cur->_right;
				else cur = cur->_left;
			}
			return false;
		}
		bool Erase(const K& value)
		{
			Node* prev = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_value < value)
				{
					prev = cur;
					cur = cur->_right;
				}
				else if (cur->_value > value)
				{
					prev = cur;
					cur = cur->_left;
				}
				else
				{
					if (nullptr == cur->_left)
					{
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else
						{
							if (prev->_left == cur)
							{
								prev->_left = cur->_right;
							}
							else
							{
								prev->_right = cur->_right;
							}
						}
						delete cur;
					}
					else if (nullptr == cur->_right)
					{
						if (cur == _root)
						{
							_root = cur->_left;
						}
						else
						{
							if (prev->_left == cur)
							{
								prev->_left = cur->_left;
							}
							else
							{
								prev->_right = cur->_left;
							}
						}
						delete cur;
					}
					else
					{
						Node* del_node = cur;
						prev = cur;
						cur = cur->_right;
						while (cur->_left)
						{
							prev = cur;
							cur = cur->_left;
						}
						std::swap(del_node->_value, cur->_value);
						if (cur == prev->_left)
							prev->_left = cur->_right;
						else
							prev->_right = cur->_right;
						delete cur;
					}
					return true;
				}
			}
			return false;
		}
		bool FindR(const K& value)
		{
			return _FindR(_root,value);
		}
		bool InsertR(const K& value)
		{
			return _InsertR(_root,value);
		}
		bool EraseR(const K& value)
		{
			return _EraseR(_root,value);
		}
		void InOrder()
		{
			_InOrderR(_root);
			std::cout << std::endl;
		}
	private:
		Node* _Copy(Node* root)
		{
			if (root == nullptr) return nullptr;
			Node* new_node = new Node(root->_value);
			new_node->_left = _Copy(root->_left);
			new_node->_right = _Copy(root->_right);
			return new_node;
		}
		void _Destructor(Node*& root)
		{
			if (root == nullptr) return;
			_Destructor(root->_left);
			_Destructor(root->_right);
			delete root;
			root = nullptr;
		}
		bool _FindR(Node* root,const K& value)
		{
			if (nullptr == root) return false;
			if (root->_value == value) return true;
			return _FindR(root->_left, value) || _FindR(root->_right, value);
		}
		bool _InsertR(Node*& root, const K& value)
		{
			if (nullptr == root)
			{
				root = new Node(value);
				return true;
			}
			if (root->_value == value) return false;
			else if (root->_value > value)
			{
				return _InsertR(root->_left, value);
			}
			else
			{
				return _InsertR(root->_right, value);
			}
		}
		bool _EraseR(Node*& root, const K& value)
		{
			if (root == nullptr) return false;
			if (root->_value == value)
			{
				Node* del_node = root;
				if (root->_left == nullptr)
				{
					root = root->_right;
				}
				else if (root->_right == nullptr)
				{
					root = root->_left;
				}
				else
				{
					Node* prev = root;
					Node* cur = root->_right;
					while (cur->_left)
					{
						prev = cur;
						cur = cur->_left;
					}
					std::swap(del_node->_value, cur->_value);
					if (prev->_left == cur)
						prev->_left = cur->_right;
					else prev->_right = cur->_right;
					delete cur;
				}
				return true;
			}
			else if (root->_value < value) return _EraseR(root->_right, value);
			else return _EraseR(root->_left, value);
		}
		void _InOrderR(Node* root)
		{
			if (nullptr == root) return;
			_InOrderR(root->_left);
			std::cout << root->_value << ' ';
			_InOrderR(root->_right);
		}
	private:
		Node* _root = nullptr;
	};
}


namespace KeyValue {
	template <class K,class V>
	struct BSTNode {
		BSTNode(const K& key = K(), const V& value = V(), BSTNode* left = nullptr,BSTNode* right = nullptr)
			:_key(key),
			_value(value),
			_left(left),
			_right(right)
		{}
		BSTNode* _left;
		BSTNode* _right;
		K _key;
		V _value;
	};

	template <class K,class V>
	class BSTree {
		typedef BSTNode<K,V> Node;
	public:

	private:
		Node* _root = nullptr;
	};
}