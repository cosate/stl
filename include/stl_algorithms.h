#ifndef GRTW_STL_ALGORITHMS_H
#define GRTW_STL_ALGORITHMS_H

#include"stl_iterator_base.h"
#include"stl_construct.h"

namespace grtw
{
	template<class InputIterator, class ForwardIterator>
	ForwardIterator copy_aux(InputIterator first, InputIterator last, ForwardIterator dest, true_type)
	{
		memcpy(result, first, sizeof(last - first));
		return result;
	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator copy_aux(InputIterator first, InputIterator last, ForwardIterator dest, false_type)
	{

	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator copy(InputIterator first, InputIterator last, ForwardIterator dest)
	{
		
	}
}

#endif