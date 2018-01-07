#ifndef GRTW_STL_DEQUE_H
#define GRTW_STL_DEQUE_H

#include"stl_iterator.h"
#include"stl_construct.h"
#include"stl_allocator.h"
#include"stl_algorithms.h"

namespace grtw
{
	template<class T, class Reference, class Pointer, size_t Nodesize>
	struct deque_iterator
	{
		using iterator_category = random_access_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using reference = Reference;
		using pointer = Pointer;

		using Self = deque_iterator<T, Reference, Pointer, Nodesize>;
		using iterator = deque_iterator<T, T&, T*, Nodesize>;
		using const_iterator = deque_iterator<T, const T&, const T*, Nodesize>;

		T* first;
		T* last;
		T* current;
		T** node;
		deque_iterator() : first(nullptr), last(nullptr), current(nullptr), node(nullptr) {}
		deque_iterator(T* x, T** y) : first(*y), last(*y + Nodesize), current(x), node(y) {}
		deque_iterator(const iterator& x) : first(x.first), last(x.last), current(x.current), node(x.node) {}

		reference operator*() const { return *current; }
		pointer operator->() const { return current; }

		difference_type operator-(const Self& x) const { return difference_type(Nodesize) * (node - x.node - 1) + (current - first) + (x.last - x.current); }
		void set_node(T** new_node)
		{
			node = new_node;
			first = *new_node;
			last = first + difference_type(Nodesize);
		}

		Self& operator++()
		{
			++current;
			if(current == last)
			{
				set_node(node + 1);
				current = first;
			}
			return *this;
		}

		Self operator++(int)
		{
			Self tmp = *this;
			++*this;
			return tmp;
		}

		Self& operator--()
		{
			if(current == first)
			{
				set_node(node - 1);
				current = last;
			}
			--current;
			return *this;
		}

		Self operator--(int)
		{
			Self tmp = *this;
			--*this;
			return tmp;
		}

		Self& operator+=(difference_type n)
		{
			difference_type offset = n + current - first;
			if(offset >= 0 && offset < difference_type(Nodesize))
				current += n;
			else
			{
				difference_type node_offset = offset > 0 ? offset / difference_type(Nodesize) : -difference_type((-offset - 1) / Nodesize) - 1;
				set_node(node + node_offset);
				current = first + (offset - node_offset * difference_type(Nodesize));				
			}
			return *this;
		}

		Self operator+(difference_type n) const
		{
			Self tmp = *this;
			return tmp += n;
		}

		Self& operator-=(difference_type n)
		{
			return *this += -n;
		}

		Self operator-(difference_type n) const
		{
			Self tmp = *this;
			return tmp -= n;
		}

		reference operator[](difference_type n)
		{
			return *(*this + n);
		}

		bool operator==(const Self& other) const { return current == other.current; }
		bool operator!=(const Self& other) const { return !(*this == other); }
		bool operator<(const Self& other) const { return (node == other.node) ? current < other.current : node < other.node; }
		bool operator>(const Self& other) const { return other < *this; }
		bool operator<=(const Self& other) const { return !(*this > other); }
		bool operator>=(const Self& other) const { return !(*this < other); }
	};

	template<class T, class Reference, class Pointer, size_t BufferSize>
	inline deque_iterator<T, Reference, Pointer, BufferSize> operator+(ptrdiff_t n, const deque_iterator<T>& it)
	{
		return it + n;
	}

	template<class T, class Node_Alloc = allocator<T>, class Map_Alloc = allocator<T*>>
	class deque
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using difference_type = ptrdiff_t;
		using size_type = size_t;

		using iterator = deque_iterator<T, reference, pointer, BufferSize()>;
		using const_iterator = deque_iterator<T, const_reference, const_pointer, BufferSize()>;
		using reverse_iterator = reverse_iterator<iterator>;
		using const_reverse_iterator = reverse_iterator<const_iterator>;

	private:
		T** node_map;
		size_t map_size;
		iterator start;
		iterator finish;

	private:
		static size_t BufferSize() { return (sizeof(T) < 512) ? (512/(sizeof(T))) : size_t(1); }

		void initialize_map(size_type);
		void create_nodes(T**, T**);
		void destroy_nodes(T**, T**);

	public:
		deque();
		deque(const deque&);
		explicit deque(size_type);
		deque(size_type, const value_type&);
		deque(const value_type*, const value_type*);
		deque(const_iterator, const_iterator);
		~deque();

		iterator begin() { return start; }
		iterator end() { return finish; }
		const_iterator begin() const { return start; }
		const_iterator end() const { return finish; }
		reverse_iterator rbegin() { return reverse_iterator(finish); }
		reverse_iterator rend() { return reverse_iterator(start); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(finish); }
		const_reverse_iterator rend() const { return const_reverse_iterator(start); }

		reference operator[](size_type n) { return start[difference_type(n)]; }
		const_reference operator[](size_type n) const { return start[difference_type(n)]; }

		reference front() { return *start; }
		const_reference front() const { return *start; }
		reference back()
		{
			iterator tmp = finish;
			return *(--tmp);
		}
		const_reference back() const
		{
			const_iterator tmp = finish;
			return *(--tmp);
		}

		size_type size() const { return finish - start; }
		bool empty() const { return finish == start; }

		void push_back(const value_type&);
		void push_front(const value_type&);
		void pop_back();
		void pop_front();

		iterator insert(iterator, const value_type&);
		void resize(size_type);
		iterator erase(iterator);
		void clear();
	};

	template<class T, class Node_Alloc, class Map_Alloc>
	void deque<T, Node_Alloc, Map_Alloc>::initialize_map(size_t nelements)
	{
		size_t nnodes = nelements/BufferSize() + 1;
		map_size = max(8, nnodes + 2);
		node_map = Map_Alloc::allocate(map_size);
		T** nstart = node_map + (map_size - nnodes)/2;
		T** nfinish = nstart + nnodes;
		create_nodes(nstart, nfinish);
		start.set_node(nstart);
		finish.set_node(nfinish);
		start.current = start.first;
		finish.current = finish.first + nelements % BufferSize();
	}

	template<class T, class Node_Alloc, class Map_Alloc>
	void deque<T, Node_Alloc, Map_Alloc>::create_nodes(T** start, T** finish)
	{
		for(T** curr = start; curr < finish; ++curr)
			*curr = Node_Alloc::allocate(BufferSize());
	}

	template<class T, class Node_Alloc, class Map_Alloc>
	void deque<T, Node_Alloc, Map_Alloc>::destroy_nodes(T** start, T** finish)
	{
		for(T** curr = start; curr < finish; ++curr)
			Node_Alloc::deallocate(*curr, BufferSize());
	}

	template<class T, class Node_Alloc, class Map_Alloc>
	deque<T, Node_Alloc, Map_Alloc>::~deque()
	{
		destroy(start, finish);
		destroy_nodes(start.node, finish.node + 1);
		Map_Alloc::deallocate(node_map, map_size);
	}

	
}

#endif