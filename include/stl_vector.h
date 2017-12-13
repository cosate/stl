#ifndef GRTW_STL_VECTOR_H
#define GRTW_STL_VECTOR_H

#include"stl_iterator.h"
#include"stl_allocator.h"
#include"stl_uninitialized.h"

namespace grtw
{
	template<class T, class Alloc = allocator<T>>
	class vector
	{
	public:
		using value_type = T;
		using pointer = T*;
		using iterator = T*;
		using const_iterator = const T*;
		using reverse_iterator = reverse_iterator<iterator>;
		using const_reverse_iterator = reverse_iterator<const_iterator>;
		using reference = T&;
		using const_reference = const T&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;

	private:
		iterator start;
		iterator finish;
		iterator end_of_storage;

	private:
		void allocate_copy();
		void allocate_fill(size_t n, )
		{
			start = Alloc::allocate(n);
			uninitialized_fill_n(start, n, )
		}

	public:
		vector() : start(nullptr), finish(nullptr), end_of_storage(nullptr) {}
		explicit vector(size_type n)
		{
			allocate_fill()
		}
		vector(size_type, const T&);
		vector(int, const T&);
		vector(long, const T&);

		vector(const vector<T, Alloc>&);
		vector& operator=(const vector<T, Alloc>&);

		template<class Iterator>
		vector(Iterator, Iterator);

		~vector();

	public:
		bool empty() const { return start == finish; }

		iterator begin() { return start; }
		iterator end() { return finish; }
		const_iterator begin() const { return start; }
		const_iterator end() const { return finish; }
		const_iterator cbegin() const {return start; }
		const_iterator cend() const { return finish; }
		reverse_iterator rbegin() { return reverse_iterator(finish); }
		reverse_iterator rend() { return reverse_iterator(start); }
		const_reverse_iterator crbegin() const { return reverse_iterator(finish); }
		const_reverse_iterator crend() const { return reverse_iterator(start); }

		size_type size() { return finish - start; }
		size_type capacity() { return end_of_storage - start; }
		
		reference operator[](size_type n) { return *(begin() + n); }
		reference front() { return *begin(); }
		reference back() { return *(end() - 1); }
		const_reference front() const { return *cbegin(); }
		const_reference back() const { return *(cend() - 1); }

		void resize(size_type);
		void reserve(size_type);
		void push_back();
		iterator insert(iterator, const T&);
		iterator insert(iterator, size_type, const T&);
		void pop_back();
		iterator erase(iterator);
		iterator erase(iterator, iterator);
		void clear();
	};
}

#endif