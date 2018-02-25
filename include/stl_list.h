#ifndef GRTW_STL_LIST_H
#define GRTW_STL_LIST_H

#include"stl_construct.h"
#include"stl_iterator.h"
#include"stl_allocator.h"

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

	public:
		ListNode<value_type>* node;
	public:
		List_iterator() {}
		List_iterator(ListNode<value_type>* x) : node(x) {}
		List_iterator(const iterator& x) : node(x.node) {}

		reference operator*() const { return node->data; }
		pointer operator->() const { return &(operator*()); }
		self& operator++()
		{
			node = node->next;
			return *this;
		}

		self operator++(int)
		{
			self tmp = *this;
			node = node->next;
			return tmp;
		}

		self& operator--()
		{
			node = node->prev;
			return *this;
		}

		self operator--(int)
		{
			self tmp = *this;
			node = node->prev;
			return tmp;
		}

		bool operator==(const self& x) const { return node = x.node; }
		bool operator!=(const self& x) const { return node = x.node; }
	};

	template<class T, class Alloc = allocator<ListNode<T> > >
	class list
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;

		using iterator = List_iterator<value_type, reference, pointer>;
		using const_iterator = List_iterator<value_type, const_reference, const_pointer>;
		using const_reverse_iterator = Reverse_iterator<const_iterator>;
		using reverse_iterator = Reverse_iterator<iterator>;
	private:
		ListNode<value_type>* head;
	public:
		list()
		{
			head = Alloc::allocator(1);
			head->next = head;
			head->prev = head;
		}

		explicit list(size_type n)
		{
			head = Alloc::allocator(1);
			head->next = head;
			head->prev = head;
			insert(begin(), n, value_type());
		}

		list(size_type, const value_type& v)
		{
			head = Alloc::allocator(1);
			head->next = head;
			head->prev = head;
			insert(begin(), n, v);
		}

		list(const value_type* vfirst, const value_type* vlast)
		{
			head = Alloc::allocator(1);
			head->next = head;
			head->prev = head;
			insert(begin(), vfirst, vlast);
		}

		list(const_iterator vfirst, const_iterator vlast)
		{
			head = Alloc::allocator(1);
			head->next = head;
			head->prev = head;
			insert(begin(), vfirst, vlast);
		}

		list(const list<value_type, Alloc>& other)
		{
			head = Alloc::allocator(1);
			head->next = head;
			head->prev = head;
			insert(begin(), other.begin(), other.end());
		}

		list<value_type, Alloc>& operator=(const list<value_type, Alloc>& other)
		{
			if(this != &other)
			{
				iterator first1 = begin();
				iterator last1 = end();
				const_iterator first2 = other.begin();
				const_iterator last2 = other.end();
				while(first1 != last1 && first2 != last2)
					*first1++ =  *first2++;
				if(first2 == last2)
					erase(first1, last1);
				else
					insert(last1, first2, last2);
			}
			return *this;
		}

		~list()
		{
			clear();
			Alloc::deallocate(head);
		}
		
		iterator begin() { return head->next; }
		const_iterator begin() const { return head->next; }
		iterator end() { return head; }
		const_iterator end() const { return head; }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		bool empty() const { return head->next == head; }
		size_type size() const
		{
			size_type result = 0;
			distance(begin(), end(), result);
			return result;
		}

		reference front() { return *begin(); }
		const_reference front() const { return *begin(); }
		reference back() { return *(--end()); }
		const_reference back() const { return *(--end()); }

		iterator insert(iterator position, const value_type& v)
		{
			ListNode<value_type>* tmp = Alloc::allocator(1);
			construct(&(tmp->data), v);
			tmp->next = position.node;
			tmp->prev = position.node->prev;
			position.node->prev->next = tmp;
			position.node->prev = tmp;
			return tmp;
		}

		void insert(iterator position, const value_type* vfirst, const value_type* vlast)
		{
			for(; vfirst != vlast; ++vfirst)
				insert(position, *vfirst);
		}

		void insert(iterator position, const_iterator vfirst, const_iterator vlast)
		{
			for(; vfirst != vlast; ++vfirst)
				insert(position, *vfirst);
		}

		void insert(iterator position, size_type n, const value_type& v)
		{
			for(; n > 0; --n)
				insert(position, v);
		}

		void push_front(const value_type& x) { insert(begin(), x); }
		void push_back(const value_type&) { insert(end(), x); }

		iterator erase(iterator position)
		{
			ListNode<value_type>* next_node = position.node->next;
			ListNode<value_type>* prev_node = position.node->prev;
			ListNode<value_type>* n = position.node;
			prev_node->next = next_node;
			next_node->prev = prev_node;
			destroy(n);
			Alloc::deallocate(n);
			return next_node;
		}

		iterator erase(iterator vfirst, iterator vlast)
		{
			while(vfirst != vlast)
				erase(vfirst++);
			return vlast;
		}

		void clear()
		{
			ListNode<value_type>* current = head->next;
			while(current != head)
			{
				ListNode<value_type>* tmp = current;
				current = current->next;
				destroy(tmp);
				Alloc::deallocate(tmp);
			}
			head->next = head;
			head->prev = head;
		}

		void resize(size_type new_size, const value_type& v)
		{
			iterator i = begin();
			size_type len = 0;
			for(; i != end() && len < new_size; ++i, ++len)
				;
			if(len == new_size)
				erase(i, end());
			else
				insert(end(), new_size - len, v);
		}

		void resize(size_type new_size) {resize(new_size, value_type()); }
		void pop_front() { erase(begin()); }
		void pop_back()
		{
			iterator tmp = end();
			erase(--tmp);
		}

		bool operator==(const list<value_type, Alloc>& other)
		{
			const_iterator end1 = end();
			const_iterator end2 = other.end();
			const_iterator i1 = begin();
			const_iterator i2 = other.begin();
			while(i1 != end1 && i2 != end2 && *i1 == *i2)
			{
				++i1;
				++i2;
			}
			return it == end1 && i2 == end2;
		}

		bool operator!=(const list<value_type, Alloc>& other)
		{
			return !(*(this) == other);
		}
	};
}

#endif