#ifndef GRTW_STL_VECTOR_H
#define GRTW_STL_VECTOR_H

#include"stl_iterator.h"
#include"stl_allocator.h"

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

	public:
		vector();
		explicit vector(size_type);
		vector(size_type, const T&);
		vector(int, const T&);
		vector(long, const T&);

		vector(const vector<T, Alloc>&);
		vector& operator=(const vector<T, Alloc>&);

		template<class Iterator>
		vector(Iterator, Iterator);

		~vector();

	private:
		iterator start;
		iterator finish;
		iterator end_of_storage;

	public:
		bool empty();

		iterator begin();
		iterator end();

		size_type size();
		size_type capacity();
		void resize(size_type);
		void reserve(size_type);
		
		reference operator[](size_type);
		reference front();
		reference back();

		void push_back();
		iterator insert(iterator, const T&);
		iterator insert(iterator, size_type, const T&);
		void pop_back();
		iterator erase(iterator);
		iterator erase(iterator, iterator);
		void clear();

	}
}

#endif