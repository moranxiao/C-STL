#pragma once
#pragma warning(disable:4996)
#include <utility>


namespace moran {
	template <class T>
	struct ListNode {
		typedef ListNode<T> Node;
		List_Node(const T& value, Node* prev = nullptr, Node* next = nullptr)
			:_value(value),
			_prev(prev),
			_next(next)
		{}
		T _value;
		Node* _prev;
		Node* _next;
	};
	
	template <class T>
	class list {
		typedef ListNode<T> Node;
	public:
			
	private:
		Node* create_node(const T& value)
		{
			Node* new_node = new Node(value);
			return new_node;
		}
	public:
		list()
		{
			_head = create_node(0);
		}
		list(size_t n, const T& value = T())
		{
			while (n--)
			{
				Node* new_node = create_node(value);
				
			}
			
		}
		list(int n, const T& value = T())
		{

		}
	private:
		Node* _head;
	};
}