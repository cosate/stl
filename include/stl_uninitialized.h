#ifndef GRTW_STL_UNINITIALIZED_H
#define GRTW_STL_UNINITIALIZED_H

#include<cstring>
#include"stl_algorithm.h"
#include"type_traits.h"

namespace grtw
{
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
}

#endif