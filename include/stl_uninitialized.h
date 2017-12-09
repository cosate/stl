#ifndef GRTW_STL_UNINITIALIZED_H
#define GRTW_STL_UNINITIALIZED_H

#include"stl_algorithm.h"
#include"type_traits.h"
#include"stl_iterator.h"
#include"stl_construct.h"

namespace grtw
{
	template<class InputIterator, class ForwardItertor>
	ForwardItertor uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardItertor dest, true_type)
	{
		return copy(first, last, dest);
	}

	template<class InputIterator, class ForwardItertor>
	ForwardItertor uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardItertor dest, false_type)
	{
		for(; first != last; first++)
			;
	}

	template<class InputIterator, class ForwardItertor>
	ForwardItertor uninitialized_copy(InputIterator first, InputIterator last, ForwardItertor dest)
	{
		using is_POD_type = type_traits<first>::is_POD_type;
		return uninitialized_copy_aux(first, last, dest, is_POD_type())
	}
}

#endif