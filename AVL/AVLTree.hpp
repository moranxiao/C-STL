#pragma once

#include <cassert>
#include <algorithm>

namespace moran {
	template<class K,class V>
	struct AVLTreeNode {
		AVLTreeNode<K, V>* _left;
		AVLTreeNode<K, V>* _right;
		AVLTreeNode<K, V>* _parent;
		std::pair<K, V> _kv;
		int _bf;
		AVLTreeNode(const std::pair<K,V>& kv,int bf = 0, AVLTreeNode<K, V>* left = nullptr, 
			AVLTreeNode<K, V>* right = nullptr, AVLTreeNode<K, V>* parent = nullptr)
			:_kv(kv),
			_bf(bf),
			_left(left),
			_right(right),
			_parent(parent)
		{}
	};

	template <class K,class V>
	class AVLTree {
		typedef AVLTreeNode<K, V> Node;
	public:
		AVLTree() = default;

		template<class InputIterator>
		AVLTree(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
			}
		}
		bool Insert(const std::pair<K,V>& kv)
		{
			//���Ƿ�Ϊ��
			if (_root == nullptr)
			{
				_root = new Node(kv);
				return true;
			}
			Node* cur = _root;
			while (cur)
			{
				if (cur->_kv.first > kv.first)
				{
					if (cur->_left == nullptr)
					{
						Node* new_node = new Node(kv);
						cur->_left = new_node;
						new_node->_parent = cur;
						//����curƽ������
						cur->_bf--;
						break;
					}
					else
					{
						cur = cur->_left;
					}
				}
				else if (cur->_kv.first < kv.first)
				{
					if (cur->_right == nullptr)
					{
						Node* new_node = new Node(kv);
						cur->_right = new_node;
						new_node->_parent = cur;
						//����cur��ƽ������
						cur->_bf++;
						break;
					}
					else
					{
						cur = cur->_right;
					}
				}
				else
					return false;
			}
			Node* parent = cur->_parent;
			//���curƽ������Ϊ0����û�и��ڵ㣬�������������
			while (cur->_bf && parent)
			{
				if (cur->_bf == 1 || cur->_bf == -1)
				{
					if (cur == parent->_left)
					{
						parent->_bf--;
						//��Ҫ����
						if (parent->_bf == -2)
						{
							if (cur->_bf == 1)
							{
								_RotateLR(parent);//������
							}
							else
							{
								_RotateR(parent);//����
							}
							break;
						}
					}
					else
					{
						parent->_bf++;
						//��Ҫ����
						if (parent->_bf == 2)
						{
							if (cur->_bf == 1)
							{
								//����
								_RotateL(parent);
							}
							else
							{
								_RotateRL(parent);//������
							}
							break;
						}
					}
				}
				else
				{
					assert(false);
				}
				cur = parent;
				parent = parent->_parent;
			}
			return true;
		}
		bool IsLegal()
		{
			return _IsLegal(_root);
		}
	private:
		bool _IsLegal(Node* root)
		{
			if (root == nullptr) return true;
			if (root->_bf >= 2 || root->_bf <= -2) return false;
			if (!_IsLegal(root->_left) || !_IsLegal(root->_right)) return false;
			return root->_bf == (Height(root->_right) - Height(root->_left));
		}
		int Height(Node* root)
		{
			if (root == nullptr) return 0;
			return std::max(Height(root->_left), Height(root->_right)) + 1;
		}
		void _RotateR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;
			Node* pparent = parent->_parent;
			if (pparent)
			{
				if (pparent->_left == parent)
					pparent->_left = subL;
				else
					pparent->_right = subL;
			}
			else
			{
				_root = subL;
			}
			subL->_parent = parent->_parent;
			subL->_right = parent;

			parent->_parent = subL;
			parent->_left = subLR;
			if (subLR)
			{
				subLR->_parent = parent;
			}

			parent->_bf = subL->_bf = 0;
		}
		void _RotateL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;
			Node* pparent = parent->_parent;
			if (pparent)
			{
				if (pparent->_left == parent)
					pparent->_left = subR;
				else
					pparent->_right = subR;
			}
			else
			{
				_root = subR;
			}
			subR->_parent = parent->_parent;
			subR->_left = parent;

			parent->_parent = subR;
			parent->_right = subRL;
			if (subRL)
			{
				subRL->_parent = parent;
			}

			parent->_bf = subR->_bf = 0;
		}
		void _RotateRL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;
			int bf = subRL->_bf;
			_RotateR(subR);
			_RotateL(parent);
			subRL->_bf = 0;
			if (bf == 1)
			{
				subR->_bf = 0;
				parent->_bf = -1;
			}
			else if (bf == -1)
			{
				subR->_bf = 1;
				parent->_bf = 0;
			}
			else if (bf == 0)
			{
				subR->_bf = parent->_bf = 0;
			}
			else
				assert(false);
		}
		void _RotateLR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;
			int bf = subLR->_bf;
			_RotateL(subL);
			_RotateR(parent);
			subLR->_bf = 0;
			if (bf == 1)
			{
				parent->_bf = 0;
				subL->_bf = -1;
			}
			else if (bf == -1)
			{
				parent->_bf = 1;
				subL->_bf = 0;
			}
			else if (bf == 0)
			{
				parent->_bf = subL->_bf = 0;
			}
			else
			{
				assert(false);
			}
		}
	private:
		Node* _root = nullptr;
	};
}