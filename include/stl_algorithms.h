#ifndef GRTW_STL_ALGORITHMS_H
#define GRTW_STL_ALGORITHMS_H

#include"stl_iterator_base.h"
#include"stl_construct.h"

namespace grtw
{
	template<class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator dest)
	{
		return copy_aux(first, last, dest, value_type(first));
	}

	template<class T>
	T* copy(T*, T*)
	{
		
	}

	template<class InputIterator, OutputIterator>
	OutputIterator copy_aux()
}

#endif