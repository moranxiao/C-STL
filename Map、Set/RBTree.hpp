#pragma once

#include <utility>
#include <iostream>
#include <cassert>

namespace moran {
	enum Color {
		BLACK, 
		RED
	};
	template<class T>
	struct RBTreeNode {
		RBTreeNode<T>* _parent;
		RBTreeNode<T>* _left;
		RBTreeNode<T>* _right;
		T _data;
		Color _col;
		RBTreeNode(const T data = T(), Color col = RED, RBTreeNode<T>* left = nullptr,
			RBTreeNode<T>* right = nullptr, RBTreeNode<T>* parent = nullptr)
			:_data(data),
			_col(col),
			_left(left),
			_right(right),
			_parent(parent)
		{}
	};
	
	template<class K,class T,class KOfT,class Compare>
	class RBTree {
		typedef RBTreeNode<T> Node;
	public:
		RBTree() = default;
		
		bool Insert(const T& data)
		{
			KOfT kot;
			Compare cmp;
			if (_root == nullptr)
			{
				_root = new Node(data,BLACK);
				return true;
			}
			Node* cur = _root;
			while (cur)
			{
				if (cmp(kot(cur->_data), kot(data)))
				{
					if (cur->_right == nullptr)
					{
						Node* new_node = new Node(data);
						cur->_right = new_node;
						new_node->_parent = cur;
						cur = new_node;
						break;
					}
					else cur = cur->_right;
				}
				else if (cmp(kot(data),kot(cur->_data)))
				{
					if (cur->_left == nullptr)
					{
						Node* new_node = new Node(data);
						cur->_left = new_node;
						new_node->_parent = cur;
						cur = new_node;
						break;
					}
					else cur = cur->_left;
				}
				else return false;
			}
			Node* parent = cur->_parent;
			while (parent && parent->_col == RED)
			{
				assert(parent->_parent != nullptr);
				Node* grand = parent->_parent; //如果parent为红，说明不是根节点，则一定有父节点
				Node* uncle = grand->_left == parent ? grand->_right : grand->_left; //找到uncle节点
				if (uncle == nullptr || uncle->_col == BLACK) //uncle为空或者为黑则是情况二
				{
					if (parent == grand->_left)
					{
						if (cur == parent->_left)
						{
							_RotateR(grand);
						}
						else
						{
							_RotateLR(grand);
						}
					}
					else
					{
						if (cur == parent->_left)
						{
							_RotateRL(grand);
						}
						else
						{
							_RotateL(grand);
						}
					}
					break;
				}
				else//uncle为红节点
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					if (grand != _root)
					{
						grand->_col = RED;
						cur = grand;
						parent = cur->_parent;
					}
					else break;
				}
			}
			return true;
		}
		bool IsLegal()
		{
			if (_root && _root->_col == RED) return false;
			return _IsLegal(_root);
		}
		void InorderPrint()
		{
			_Inorder(_root);
			std::cout << std::endl;
		}
		~RBTree()
		{
			_Destructor(_root);
		}
	private:
		void _Destructor(Node* root)
		{
			if (root == nullptr) return;
			_Destructor(root->_left);
			_Destructor(root->_right);
			delete root;
			root = nullptr;
		}
		bool _IsLegal(Node* root)
		{
			if (root == nullptr) return true;
			if (root->_parent && root->_col == RED)
			{
				return root->_parent->_col != RED;
			}
			int lbcount = get_bcount(root->_left);
			int rbcount = get_bcount(root->_right);
			return lbcount == rbcount;
		}
		int get_bcount(Node* root)
		{
			if (root == nullptr) return 0;
			if (root->_col == BLACK)
			{
				return 1 + get_bcount(root->_left);
			}
			return get_bcount(root->_left);
		}
		void _Inorder(Node* root)
		{
			if (root == nullptr) return;
			_Inorder(root->_left);
			std::cout << root->_kv.first  << " ";
			_Inorder(root->_right);
		}

		void _RotateL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;
			Node* pparent = parent->_parent;

			subR->_parent = pparent;
			subR->_left = parent;
		
			if (pparent == nullptr)
			{
				_root = subR;
			}
			else
			{
				if (pparent->_left == parent)
					pparent->_left = subR;
				else
					pparent->_right = subR;
			}
			parent->_parent = subR;
			parent->_right = subRL;
			if (subRL)
			{
				subRL->_parent = parent;
			}
			subR->_col = BLACK;
			parent->_col = RED;
		}
		void _RotateR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subRL = subL->_right;
			Node* pparent = parent->_parent;

			subL->_parent = pparent;
			subL->_right = parent;

			if (pparent == nullptr)
			{
				_root = subL;
			}
			else
			{
				if (pparent->_left == parent)
					pparent->_left = subL;
				else
					pparent->_right = subL;
			}
			parent->_parent = subL;
			parent->_left = subRL;
			if (subRL)
			{
				subRL->_parent = parent;
			}
			subL->_col = BLACK;
			parent->_col = RED;
		}
		void _RotateRL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;
			_RotateR(subR);
			_RotateL(parent);
			parent->_col = RED;
			subR->_col = RED;
			subRL->_col = BLACK;
		}
		void _RotateLR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;
			_RotateL(subL);
			_RotateR(parent);
			parent->_col = RED;
			subL->_col = RED;
			subLR->_col = BLACK;
		}
		
	private:
		Node* _root = nullptr;
	};
}