#ifndef GRTW_STL_ALGORITHMS_H
#define GRTW_STL_ALGORITHMS_H

#include"stl_iterator_base.h"
#include"type_traits.h"

namespace grtw
{
	//copy
	template<class InputIterator, class OutputIterator>
	inline OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator dest, input_iterator_tag)
	{
		for(; first != last; ++first, ++dest)
			*dest = *first;
		return dest;
	}

	template<class InputIterator, class OutputIterator>
	inline OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator dest, random_access_iterator_tag)
	{
		using Dist = typename iterator_traits<InputIterator>::difference_type;
		for(Dist n = last - first; n > 0; --n)
		{
			*dest = * first;
			++first;
			++dest;
		}
		return dest;
	}

	template<class T>
	inline T* __copy(T* first, T* last, T* dest)
	{
		memmove(dest, first, sizeof(T) * (last - first));
		return dest + (last - first);
	}

	template<class InputIterator, class OutputIterator, class Trivial>
	struct copy_dispatch
	{
		static OutputIterator copy(InputIterator first, InputIterator last, OutputIterator dest)
		{
			using Cat = iterator_traits<Iterator>::iterator_category;
			return __copy(fisrt, last, dest, iterator_category(first));
		}
	};

	template<class T>
	struct copy_dispatch<T*, T*, true_type>
	{
		static T* copy(T* first, T* last, T* dest)
		{
			return __copy(first, last, dest);
		}
	};

	template<class T>
	struct copy_dispatch<const T*, T*, true_type>
	{
		static T* copy(const T* first, const T* last, T* dest)
		{
			return __copy(first, last, dest);
		}
	};

	template<class InputIterator, class OutputIterator>
	inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator dest)
	{
		using Val = iterator_traits<InputIterator>::value_type;
		using Triv = type_traits<Val>::has_trivial_assignment_operator;
		return copy_dispatch<InputIterator, OutputIterator, Triv>::copy(first, last, dest);
	}

	//fill
	template<class ForwardIterator, class T>
	
}

#endif