#pragma once
#pragma warning(disable:4996)
#include <utility>
#include <iostream>

namespace moran {
	template <class T>
	struct list_node {
		typedef list_node<T> Node;
		list_node(const T& value = T(), Node* prev = nullptr, Node* next = nullptr)
			:_value(value),
			_prev(prev),
			_next(next)
		{}
		T _value;
		Node* _prev;
		Node* _next;
	};
	
	template<class T,class Ref,class Ptr>
	struct list_iterator {
		typedef list_iterator<T,Ref,Ptr> Self;
		typedef list_node<T> Node;

		list_iterator(Node* node)
			:_node(node)
		{}
		Self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		//不能用引用，tmp是临时变量
		Self operator++(int)
		{
			Self tmp(_node);  
			_node = _node->_next;
			return tmp;
		}
		Self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		Self operator--(int)
		{
			Self tmp(_node);
			_node = _node->_prev;
			return tmp;
		}
		bool operator!=(const Self& it) const
		{
			return it._node != _node;
		}
		bool operator==(const Self& it) const
		{
			return it._node == _node;

		}
		Ref operator*() const 
		{
			return _node->_value;
		}
		Ptr operator->() const
		{
			return &(operator*());
		}

		Node* _node;
	};

	template <class T>
	class list {
		typedef list_node<T> Node;
	//共有成员类型
	public:
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;

		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		const_iterator cbegin() const
		{
			return const_iterator(_head->_next);
		}
		const_iterator cend() const
		{
			return const_iterator(_head);
		}
		void print()
		{
			for (auto& e : *this)
			{
				std::cout << e << " ";
			}
			std::cout << std::endl;
		}
	//私有成员方法
	private:
		void init()
		{
			_head = new Node();
			_head->_next = _head->_prev = _head;
		}
	public:
		list()
		{
			init();
		}

		list(size_t n, const T& value = T())
		{
			//选择头插尾插一样的，我选择尾插
			init();
			_size = n;
			while (n--)
			{
				Node* new_node = new Node(value, _head->_prev, _head);
				_head->_prev->_next = new_node;
				_head->_prev = new_node;
			}
		}
		list(int n, const T& value = T())
		{
			init();
			_size = n;
			while (n--)
			{
				Node* new_node = new Node(value, _head->_prev, _head);
				_head->_prev->_next = new_node;
				_head->_prev = new_node;
			}
		}

		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			init();
			while (first != last)
			{
				Node* new_node = new Node(*first,_head->_prev,_head);
				_head->_prev->_next = new_node;
				_head->_prev = new_node;
				first++;
				_size++;
			}
		}
		//列表初始化，非常的方便！
		list(std::initializer_list<T> initializer)
		{
			init();
			for (auto& e : initializer)
			{
				Node* new_node = new Node(e, _head->_prev, _head);
				_head->_prev->_next = new_node;
				_head->_prev = new_node;
				_size++;
			}
		}

		void swap(list& lt)
		{
			std::swap(lt._head, _head);
			std::swap(lt._size, _size);
		}
		list(const list& lt)
		{
			init();
			for (auto& e : lt)
			{
				push_back(e);
			}
		}
		list& operator=(const list lt)
		{
			swap(lt, *this);
			return *this;
		}
		//增
		void push_back(const T& value)
		{
			Node* new_node = new Node(value, _head->_prev, _head);
			_head->_prev->_next = new_node;
			_head->_prev = new_node;
			_size++;
		}
		void push_front(const T& value)
		{
			Node* new_node = new Node(value, _head, _head->_next);
			_head->_next = new_node;
			new_node->_next->_prev = new_node;
			_size++;

		}

		//在it之后插入
		iterator insert(iterator it,const T& value)
		{
			Node* new_node = new Node(value, it._node, it._node->_next);
			it._node->_next = new_node;
			new_node->_next->_prev = new_node;
			_size++;
			return it;
		}
		//删
		void pop_front()
		{
			if (_size == 0)
				return;
			_head->_next = _head->_next->_next;
			delete _head->_next->_prev;
			_head->_next->_prev = _head;
			_size--;
		}
		void pop_back()
		{
			if (_size == 0)
				return;
			_head->_prev = _head->_prev->_prev;
			delete _head->_prev->_next;
			_head->_prev->_next = _head;
			_size--;
		}
		iterator erase(iterator it)
		{
			Node* tmp = it._node->_next;
			it._node->_prev->_next = tmp;
			tmp->_prev = it._node->_prev;
			delete it._node;
			return iterator(tmp);
		}

		~list()
		{
			Node* cur = _head->_next;
			while (cur != _head)
			{
				Node* tmp = cur->_next;
				delete cur;
				cur = tmp;
			}
			delete _head;
		}
		size_t size()
		{
			return _size;
		}

		bool empty()
		{
			return _size == 0;
		}


	private:
		Node* _head = nullptr;
		size_t _size = 0;
	};
}