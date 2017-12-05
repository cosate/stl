#ifndef GRTW_STL_ALLOCATOR_H
#define GRTW_STL_ALLOCATOR_H

#include"stl_alloc.h"

namespace grtw
{
	template<class T>
	class allocator
	{
	public:
		using value_type = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;

		static T* allocate();
		static T* allocate(size_t);
		static void deallocate(T*);
		static void deallocate(T*, size_t);
		static void construct(T*);
		static void construct(T*, const T&);
		static void destroy(T*);
		static void destroy(T*, T*);
	};

	template<class T>
	T* allocator<T>::allocate()
	{
		return static_cast<T*>(default_alloc::allocate(sizeof(T)));
	}

	template<class T>
	T* allocator<T>::allocate(size_t n)
	{
		if(n == 0)
			return nullptr;
		return static_cast<T*>(default_alloc::allocate(sizeof(T) * n));
	}

	template<class T>
	void allocator<T>::deallocate(T* p)
	{
		default_alloc::deallocate(static_cast<void*>p, sizeof(T));
	}

	template<class T>
	void allocator<T>::deallocate(T* p, size_t n)
	{
		if(n == 0)
			return;
		default_alloc::deallocate(static_cast<void*>p, sizeof(T) * n);
	}

	template<class T>
	void allocator<T>::construct(T* p)
	{
		new p T();
	}

	template<class T>
	void allocator<T>::construct(T* p, const T& v)
	{
		new p T(v);
	}

	template<class T>
	void allocator<T>::destroy(T* p)
	{
		p->~T();
	}

	template<class T>
	void allocator<T>::destroy(T* first, T* last)
	{
		while(first != last)
		{
			first->~T();
			++first;
		}
	}
}

#endif