#ifndef GRTW_STL_UNINITIALIZED_H
#define GRTW_STL_UNINITIALIZED_H

#include<cstring>
#include"stl_algorithms.h"
#include"stl_construct.h"

namespace grtw
{
	//uninitialized_copy
	template<class InputIterator, class ForwardIterator>
	inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator dest, true_type)
	{
		return copy(first, last, dest);
	}

	template<class InputIterator, class ForwardIterator>
	inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator dest, false_type)
	{
		ForwardIterator cur = dest;
		for(; first != last; ++first, ++cur)
			construct(&*cur, *first);
		return cur;
	}
	
	template<class InputIterator, class ForwardIterator, class T>
	inline ForwardIterator _uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator dest, T*)
	{
		using IS_POD = type_traits<T>::is_POD_type;
		return __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator dest, IS_POD());
	}

	template<class InputIterator, class ForwardIterator>
	inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator dest)
	{
		return _uninitialized_copy(first, last, dest, value_type(dest));
	}

	inline char* uninitialized_copy(const char* first, const char* last, char* dest)
	{
		memmove(dest, first, last - first);
		return dest + (last - first);
	}

	inline wchar_t* uninitialized_copy(const wchar_t* first, const wchar_t* last, wchar_t* dest)
	{
		memmove(dest, first, sizeof(wchar_t)*(last - first));
		return dest + (last - first);
	}

	//uninitialized_fill
	template <class ForwardIterator, class T>
	inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& x, true_type)
	{
		fill(first, last, x);
	}

	template <class ForwardIterator, class T>
	void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& x, false_type)
	{
		ForwardIterator cur = first;
	    for(; cur != last; ++cur)
	    	construct(&*cur, x);
	}

	template <class ForwardIterator, class T, class T1>
	inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x, T1*)
	{
		using IS_POD = typename __type_traits<T1>::is_POD_type;
		__uninitialized_fill_aux(first, last, x, IS_POD());               
	}

	template <class ForwardIterator, class T>
	inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x)
	{
		__uninitialized_fill(first, last, x, value_type(first));
	}

	//uninitialized_fiil_n
	template <class ForwardIterator, class _Size, class T>
	inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, _Size n, const T& x, true_type)
	{
		return fill_n(first, n, x);
	}

	template <class ForwardIterator, class _Size, class T>
	ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, _Size n, const T& x, false_type)
	{
		ForwardIterator cur = first;
		for(; n > 0; --n, ++cur)
			construct(&*cur, x);
	    return cur;
	}

	template <class ForwardIterator, class _Size, class T, class T1>
	inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, _Size n, const T& x, T1*)
	{
		using IS_POD = typename __type_traits<T1>::is_POD_type;
		return __uninitialized_fill_n_aux(first, n, x, IS_POD());
	}

	template <class ForwardIterator, class _Size, class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first, _Size n, const T& x)
	{
		return __uninitialized_fill_n(first, n, x, value_type(first));
	}
}

#endif