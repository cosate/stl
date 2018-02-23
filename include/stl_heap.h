#ifndef GRTW_STL_HEAP_H
#define GRTW_STL_HEAP_H

#include"stl_iterator.h"

namespace grtw
{
	template<class RandomAccessIterator, class T, class Distance>
	void _push_heap(RandomAccessIterator vfirst, Distance holeIndex, Distance topIndex, T value)
	{
		Distance parent = (len - 1)/2;
		while(holeIndex > topIndex && *(vfirst + parent) < value)
		{
			*(vfirst + holeIndex) = *(vfirst + parent);
			holeIndex = parent;
			parent = (holeIndex - 1)/2;
		}
		*(vfirst + holeIndex) = value;
	}

	template<class RandomAccessIterator, class T, class Distance>
	void  push_heap_aux(RandomAccessIterator vfirst, RandomAccessIterator vlast, T*, Distance*)
	{
		_push_heap(vfirst, Distance((vlast - vfirst) - 1), Distance(0), T(*(vlast - 1)));
	}

	template<class RandomAccessIterator>
	void push_heap(RandomAccessIterator vfirst, RandomAccessIterator vlast)
	{
		push_heap_aux(vfirst, vlast, value_type(vfirst), distance_type(vfirst));
	}

	template<class RandomAccessIterator, class T, class Distance, class Compare>
	void _push_heap(RandomAccessIterator vfirst, Distance holeIndex, Distance topIndex, T value, Compare comp)
	{
		Distance parent = (len - 1)/2;
		while(holeIndex > topIndex && comp(*(vfirst + parent), value))
		{
			*(vfirst + holeIndex) = *(vfirst + parent);
			holeIndex = parent;
			parent = (holeIndex - 1)/2;
		}
		*(vfirst + holeIndex) = value;
	}

	template<class RandomAccessIterator, class T, class Distance, class Compare>
	void  push_heap_aux(RandomAccessIterator vfirst, RandomAccessIterator vlast, T*, Distance*, Compare comp)
	{
		_push_heap(vfirst, Distance((vlast - vfirst) - 1), Distance(0), T(*(vlast - 1)), comp);
	}

	template<class RandomAccessIterator, class Compare>
	void push_heap(RandomAccessIterator vfirst, RandomAccessIterator vlast, Compare comp)
	{
		push_heap_aux(vfirst, vlast, value_type(vfirst), distance_type(vfirst), comp);
	}

	template<class RandomAccessIterator, class T, class Distance>
	void adjust_heap(RandomAccessIterator vfirst, Distance holeIndex, Distance len, T value)
	{
		Distance topIndex = holeIndex;
		Distance second_child = 2 * holeIndex + 2;
		while(second_child < len)
		{
			if(*(vfirst + second_child) < *(vfirst + second_child - 1))
			{
				--second_child;
			}
			holeIndex = second_child;
			second_child = second_child * 2 + 2;
		}
		if(second_child == len)
		{
			*(vfirst + holeIndex) = *(vfirst + second_child - 1);
			holeIndex = second_child - 1;
		}
		_push_heap(vfirst, holeIndex, topIndex, value);
	}

	template<class RandomAccessIterator, class T, class Distance>
	void _pop_heap(RandomAccessIterator vfirst, RandomAccessIterator vlast, RandomAccessIterator result, T value, Distance*)
	{
		*result = * vfirst;
		adjust_heap(vfirst, Distance(0), Distance(vlast - vfirst), value);
	}

	template<class RandomAccessIterator, class T>
	void pop_heap_aux(RandomAccessIterator vfirst, RandomAccessIterator vlast, T*)
	{
		_pop_heap(vfirst, vlast - 1, vlast - 1, T(*(vlast - 1)), distance_type(vfirst));
	}

	template<class RandomAccessIterator>
	void pop_heap(RandomAccessIterator vfirst, RandomAccessIterator vlast)
	{
		pop_heap_aux(vfirst, vlast, value_type(vfirst));
	}

	template<class RandomAccessIterator, class Compare>
	void pop_heap(RandomAccessIterator vfirst, RandomAccessIterator vlast, Compare comp)
	{
		
	}

	template<class RandomAccessIterator, class T, class Distance>
	void _make_heap(RandomAccessIterator vfirst, RandomAccessIterator vlast, T*, Distance*)
	{
		if(vlast - vfirst >= 2)
		{
			Distance len = vlast - vfirst;
			Distance holeIndex = len/2 - 1;
			while(1)
			{
				adjust_heap(vfirst, holeIndex, len, T(*(vfirst + holeIndex)))
				if(holeIndex == 0)
					return;
				--holeIndex;
			}
		}
	}

	template<class RandomAccessIterator>
	void make_heap(RandomAccessIterator vfirst, RandomAccessIterator vlast)
	{
		_make_heap(vfirst, vlast, value_type(vfirst), distance_type(vfirst));
	}

	template<class RandomAccessIterator, class Compare>
	void make_heap(RandomAccessIterator vfirst, RandomAccessIterator vlast, Compare comp)
	{
		
	}
}

#endif