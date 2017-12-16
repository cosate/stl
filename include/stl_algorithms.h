#ifndef GRTW_STL_ALGORITHMS_H
#define GRTW_STL_ALGORITHMS_H

#include<cstring>
#include"stl_iterator.h"
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
			using Cat = typename iterator_traits<Iterator>::iterator_category;
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
		using Val = typename iterator_traits<InputIterator>::value_type;
		using Triv = typename type_traits<Val>::has_trivial_assignment_operator;
		return copy_dispatch<InputIterator, OutputIterator, Triv>::copy(first, last, dest);
	}

	//copy_backward
	template <class BidirectionalIter1, class BidirectionalIter2>
	inline BidirectionalIter2 __copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 dest, bidirectional_iterator_tag)
	{
		while (first != last)
			*--dest = *--last;
		return dest;
	}

	template <class RandomAccessIter, class BidirectionalIter>
	inline BidirectionalIter __copy_backward(RandomAccessIter first, RandomAccessIter last, BidirectionalIter dest, random_access_iterator_tag)
	{
		using Dist = typename iterator_traits<RandomAccessIter>::difference_type;
		for(Dist n = last - first; n > 0; --n)
			*--dest = *--last;
		return dest;
	}

	template <class BidirectionalIter1, class BidirectionalIter2, class BoolType>
	struct copy_backward_dispatch
	{
		using Cat = typename iterator_traits<BidirectionalIter1>::iterator_category;
		static BidirectionalIter2 copy(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 dest)
		{
			return __copy_backward(first, last, dest, Cat());
		}
	};

	template <class T>
	struct copy_backward_dispatch<T*, T*, true_type>
	{
		static T* copy(const T* first, const T* last, T* dest)
		{
			const ptrdiff_t num = last - first;
			memmove(dest - num, first, sizeof(T) * num);
			return dest - num;
		}
	};

	template <class T>
	struct copy_backward_dispatch<const T*, T*, true_type>
	{
		static T* copy(const T* first, const T* last, T* dest)
		{
			return  copy_backward_dispatch<T*, T*, true_type>::copy(first, last, dest);
		}
	};

	template <class BI1, class BI2>
	inline BI2 copy_backward(BI1 first, BI1 last, BI2 dest)
	{
		using Val = typename iterator_traits<BI2>::value_type;
		using Triv = typename type_traits<Val>::has_trivial_assignment_operator;
		return copy_backward_dispatch<BI1, BI2, Triv>::copy(first, last, dest);
	}

	//fill
	template<class ForwardIterator, class T>
	inline void fill(ForwardIterator first, ForwardIterator last, const T& v)
	{
		for(; first != last; ++first)
			*first = v;
	}

	inline void fill(unsigned char* first, unsigned char* last, const unsigned char& c)
	{
		unsigned char tmp = c;
		memset(first, tmp, last - first);
	}

	inline void fill(signed char* first, signed char* last, const signed char& c)
	{
  		signed char tmp = c;
  		memset(first, static_cast<unsigned char>(tmp), last - first);
  	}

	inline void fill(char* first, char* last, const char& c)
	{
  		char tmp = c;
  		memset(first, static_cast<unsigned char>(tmp), last - first);
  	}

  	//fill_n
	template<class OutputIterator, class _Size, class T>
	inline OutputIterator fill_n(OutputIterator first, _Size n, const T& v)
	{
		for(; n > 0; --n, ++first)
			*first = v;
		return first;
	}

	template <class _Size>
	inline unsigned char* fill_n(unsigned char* first, _Size n, const unsigned char& c)
	{
		fill(first, first + n, c);
		return first + n;
	}

	template <class _Size>
	inline signed char* fill_n(char* first, _Size n, const signed char& c)
	{
		fill(first, first + n, c);
		return first + n;
	}

	template <class _Size>
	inline char* fill_n(char* first, _Size n, const char& c)
	{
		fill(first, first + n, c);
		return first + n;
	}

	template<class Iterator1, class Iterator2>
	inline bool equal(Iterator1 start1, Iterator1 end1, Iterator2 start2)
	{
		while(start1 != end1)
		{
			if(*start1 != *start2)
				return false;
			++start1;
			++start2;
		}
		return true;
	}

	template<class Iterator1, class Iterator2, class Compare>
	inline bool equal(Iterator1 start1, Iterator1 end1, Iterator2 start2, Compare comp)
	{
		while(start1 != end1)
		{
			if(!comp(*start1, *start2))
				return false;
			++start1;
			++start2;
		}
		return true;
	}

	template<class T>
	void swap(T& t1, T& t2)
	{
		T tmp = t1;
		t1 = t2;
		t2 = tmp;
	}

	template<class T>
	const T& max(const T& t1, const T& t2)
	{
		return (t1 < t2) ? t2 : t1;
	}

	template<class T, class Compare>
	const T& max(const T& t1, const T& t2, Compare comp)
	{
		return (comp(t1, t2)) ? t2 : t1;
	}

	template<class T>
	const T& min(const T& t1, const T& t2)
	{
		return (t1 < t2) ? t1 : t2;
	}

	template<class T, class Compare>
	const T& min(const T& t1, const T& t2, Compare comp)
	{
		return (comp(t1, t2)) ? t1 : t2;
	}
}

#endif