#ifndef GRTW_STL_VECTOR_H
#define GRTW_STL_VECTOR_H

#include"stl_iterator.h"
#include"stl_allocator.h"
#include"stl_uninitialized.h"
#include"stl_algorithms.h"
#include"type_traits.h"

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
		using const_reverse_iterator = Reverse_iterator<const_iterator>;
		using reverse_iterator = Reverse_iterator<iterator>;
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

		vector(size_type n, const T& v)
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

		vector(const T* first, const T* last)
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

		iterator insert(iterator it, const T& v)
		{
			size_type n = it - start;
			if(finish != end_of_storage)
			{
				if(it == finish)
				{
					construct(finish, v);
					++finish;
				}
				else
				{
					construct(finish, *(finish - 1));
					++finish;
					copy_backward(it, finish - 2, finish - 1);
					*it = v;
				}
			}
			else
			{
				size_type old_size = size();
				size_type new_size = old_size == 0 ? 1 : old_size * 2;
				iterator new_start = Alloc::allocate(new_size);
				iterator new_finish = new_start;
				new_finish = uninitialized_copy(start, it, new_start);
				construct(new_finish, v);
				++new_finish;
				new_finish = uninitialized_copy(it, finish, new_finish);
				destroy(start, finish);
				Alloc::deallocate(start, end_of_storage - start);
				start = new_start;
				finish = new_finish;
				end_of_storage = start + new_size;
			}
			return start + n;
		}

		void insert(iterator it, size_type n, const T& v)
		{
			if(n != 0)
			{
				size_type remain = end_of_storage - finish;
				if(n <= remain)
				{
					size_type elems_after = finish - it;
					iterator old_finish = finish;
					if(elems_after > n)
					{
						uninitialized_copy(finish - n, finish, finish);
						finish += n;
						copy_backward(it, old_finish - n, finish);
						fill(it, it + n, v);
					}
					else
					{
						uninitialized_fill_n(it, n - elems_after, v);
						finish += n - elems_after;
						uninitialized_copy(it, old_finish, finish);
						finish += elems_after;
						fill(it, old_finish, v);
					}
				}
				else
				{
					size_type old_size = size();
					size_type new_size = old_size + max(old_size, n);
					iterator new_start = Alloc::allocate(new_size);
					iterator new_finish = new_start;
					new_finish = uninitialized_copy(start, it, new_start);
					new_finish = uninitialized_fill_n(new_finish, n, v);
					new_finish = uninitialized_copy(it, finish, new_finish);
					destroy(start, finish);
					Alloc::deallocate(start, end_of_storage - start);
					start = new_start;
					finish = new_finish;
					end_of_storage = start + new_size;
				}
			}
		}

		void insert(iterator it, const_iterator first, const_iterator last)
		{
			if(first != last)
			{
				size_type n = distance(first, last);
				size_type remain = end_of_storage - finish;
				if(remain >= n)
				{
					size_type elems_after = finish - it;
					iterator old_finish = finish;
					if(elems_after >= n)
					{
						uninitialized_copy(old_finish - n, old_finish, old_finish);
						finish += n;
						copy_backward(it, old_finish - n, old_finish);
						copy(first, last, it);
					}
					else
					{
						uninitialized_copy(first + elems_after, last, finish);
						finish = finish + n - elems_after;
						uninitialized_copy(it, old_finish, finish);
						finish += elems_after;
						copy(first, first + elems_after, it);
					}
				}
				else
				{
					size_type old_size = size();
					size_type new_size = old_size + max(old_size, n);
					iterator new_start = Alloc::allocate(new_size);
					iterator new_finish = new_start;
					new_finish = uninitialized_copy(start, it, new_start);
					new_finish = uninitialized_copy(first, last, new_finish);
					new_finish = uninitialized_copy(it, finish, new_finish);
					destroy(start, finish);
					Alloc::deallocate(start);
					start = new_start;
					finish = new_finish;
					end_of_storage = start + new_size;
				}
			}
		}

		void pop_back()
		{
			--finish;
			destroy(finish);
		}

		iterator erase(iterator it)
		{
			if(it + 1 != finish)
				copy(it + 1, finish, it);
			--finish;
			destroy(finish);
			return it;
		}

		iterator erase(iterator first, iterator last)
		{
			copy(last, finish, first);
			iterator new_finish = first + (finish - last);
			destroy(new_finish, finish);
			finish = new_finish;
			return first;
		}

		void clear()
		{
			erase(start, finish);
		}

		template<class T1, class Alloc1>
		bool operator==(const vector<T1, Alloc1>& other)
		{
			return size() == other.size() && equal(start, finish, other.begin());
		}

		template<class T1, class Alloc1>
		bool operator!=(const vector<T1, Alloc1>& other)
		{
			return !(this->operator==(other));
		}
	};
}

#endif