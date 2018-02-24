#ifndef GRTW_STL_LIST_H
#define GRTW_STL_LIST_H

#include"stl_construct.h"
#include"stl_iterator.h"

namespace grtw
{
	template<class T>
	struct ListNode
	{
		T data;
		ListNode* prev;
		ListNode* next;
		ListNode() : data(T()), prev(nullptr), next(nullptr) {}
		~ListNode() { destroy(&data); }
	};

	template<class T, class Reference, class Pointer>
	class List_iterator
	{
	public:
		using iterator_category = bidirectional_iterator_tag;
		using difference_type = ptrdiff_t;
		using value_type = T;
		using pointer = Pointer;
		using reference = Reference;

		using iterator = List_iterator<T, T&, T*>;
		using const_iterator = List_iterator<T, const T&, const T*>;
		using self = List_iterator<T, Reference, Pointer>;

	private:
		ListNode<value_type>* node;
	public:
		List_iterator() {}
		List_iterator(ListNode<value_type>* x) : node(x) {}
		List_iterator(const iterator& x) : node(x.getNative()) {}

		ListNode<value_type>* getNative() const { return node; }
		reference operator*() const { return node->data; }
		pointer operator->() const { return &(operator*()); }
		self& operator++()
		{

		}

		self operator++(int)
		{

		}

		self& operator--()
		{

		}

		self operator--(int)
		{

		}

		bool operator==(const self& x) const
		{

		}

		bool operator!=(const self& x) const
		{

		}
	};

	template<class T>
	class list
	{
	public:
		list();
		~list();
		
	};
}

#endif