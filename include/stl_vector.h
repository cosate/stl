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
		void allocate_fill(size_t n, const T& v)
		{
			start = Alloc::allocate(n);
			uninitialized_fill_n(start, n, v);
			finish = start + n;
			end_of_storage = finish;
		}

	//construct and destruct	
	public:
		vector() : start(nullptr), finish(nullptr), end_of_storage(nullptr) {}

		explicit vector(size_type n)
		{
			allocate_fill(n, T());
		}

		vector(size_type, const T& v)
		{
			allocate_fill(n, v);
		}

		vector(int n, const T& v)
		{
			allocate_fill(n, v);
		}

		vector(long n, const T& v)
		{
			allocate_fill(n, v);
		}

		vector(const vector<T, Alloc>& v)
		{
			size_t n = v.size();
			start = Alloc::allocate(n);
			uninitialized_copy(v.begin(), v.end(), start);
			finish = start + n;
			end_of_storage = finish;
		}

		vector(iterator first, iterator last)
		{
			size_t n = last - first;
			start = Alloc::allocate(n);
			uninitialized_copy(first, last, start);
			finish = start + n;
			end_of_storage = finish;
		}

		vector& operator=(const vector<T, Alloc>& v)
		{
			if(this != v.begin())
			{
				Alloc::destroy(start, finish);
				size_t n = v.size();
				if(capacity() >= n)
					finish = uninitialized_copy(v.begin(), v.end(), start);
				else
				{
					Alloc::deallocate(start, end_of_storage - start);
					start = Alloc::allocate(n);
					uninitialized_copy(v.begin(), v.end(), start);
					finish = start + n;
					end_of_storage = finish;
				}
			}
			return *this;
		}

		~vector()
		{
			Alloc::destroy(start, finish);
			Alloc::deallocate(start, end_of_storage - start);
		}

	//interface
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

		void resize(size_type n, const T& v = T())
		{
			if(n < size())
				erase(start + n, finish);
			else
				insert(finish, n - size(), v);
		}

		void reserve(size_type n)
		{
			if(n > capacity())
			{
				size_type old_size = size();
				iterator tmp = Alloc::allocate(n);
				uninitialized_copy(start, finish, tmp);
				Alloc::destroy(start, finish);
				Alloc::deallocate(start, end_of_storage - start);
				start = tmp;
				finish = start + old_size;
				end_of_storage = start + n;
			}
		}

		void push_back(const T& v)
		{
			insert(end(), v);
		}

		iterator insert(iterator, const T&)
		{
			if(iterator < capacity())
		}

		iterator insert(iterator, size_type, const T&);
		void pop_back();
		iterator erase(iterator);
		iterator erase(iterator, iterator);
		void clear();
	};
}

#endif