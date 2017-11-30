#ifndef GRTW_STL_ITERATOR_H
#define GRTW_STL_ITERATOR_H

namespace grtw
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<class T, class Distance>
	struct input_iterator
	{
		using iterator_category = input_iterator_tag;
		using value_type = T;
		using difference_type = Distance;
		using pointer = T*;
		using reference = T&;
	};

	struct output_iterator
	{
		using iterator_category = output_iterator_tag;
		using value_type = void;
		using difference_type = void;
		using pointer = void;
		using reference  = void;
	};

	template<class T, class Distance>
	struct forward_iterator
	{
		using iterator_category = forward_iterator_tag;
		using value_type = T;
		using difference_type = Distance;
		using pointer = T*;
		using reference = T&;
	};

	template<class T, class Distance>
	struct bidirectional_iterator
	{
		using iterator_category = bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = Distance;
		using pointer = T*;
		using reference = T&;
	};

	template<class T, class Distance>
	struct random_access_iterator
	{
		using iterator_category = random_access_iterator_tag;
		using value_type = T;
		using difference_type = Distance;
		using pointer = T*;
		using reference = T&;
	};

	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		using iterator_category = Category;
		using value_type = T;
		using difference_type = Distance;
		using pointer = Pointer;
		using reference = Reference;
	};

	template<class Iterator>
	struct iterator_traits
	{
		using iterator_category = Iterator::iterator_category;
		using value_type = Iterator::value_type;
		using difference_type = Iterator::difference_type;
		using pointer = Iterator::pointer;
		using reference = Iterator::reference;
	};

	template<class T>
	struct iterator_traits<T*>
	{
		using iterator_category = random_access_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T*;
		using reference = T&;
	};

	template<class T>
	struct iterator_traits<const T*>
	{
		using iterator_category = random_access_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;
	};

	template<class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
	iterator_category(const Iterator&)
	{
		using Cat = typename iterator_traits<Iterator>::iterator_category;
		return Cat();
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type*
	distance_type(const Iterator&)
	{
		using Diff = typename iterator_traits<Iterator>::difference_type*;
		return static_cast<Diff>(0);
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::value_type*
	value_type(const Iterator&)
	{
		using Val = typename iterator_traits<Iterator>::value_type*;
		return static_cast<Val>(0);
	}

	template<class Iterator, class Distance>
	inline void _distance(Iterator first, Iterator last, Distance& n, input_iterator_tag)
	{
		while(first != last)
		{
			++first;
			++n;
		}
	}

	template<class Iterator, class Distance>
	inline void _distance(Iterator first, Iterator last, Distance& n, random_access_iterator_tag)
	{
		n += (last - first);
	}

	template<class Iterator, class Distance>
	inline void distance(Iterator first, Iterator last, Distance& n)
	{
		_distance(first, last, n, iterator_category(first));
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
	_distance(Iterator first, Iterator last, input_iterator_tag)
	{
		typename iterator_traits<Iterator>::difference_type n = 0;
		while(first != last)
		{
			++first;
			++n;
		}
		return n;
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
	_distance(Iterator first, Iterator last, random_access_iterator_tag)
	{
		return last - first;
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last)
	{
		return _distance(first, last, iterator_category(first));
	}

	template<class Iterator, class Distance>
	inline void _advance(Iterator& it, Distance n, input_iterator_tag)
	{
		while(n--)
		{
			++it;
		}
	}

	template<class Iterator, class Distance>
	inline void _advance(Iterator& it, Distance n, bidirectional_iterator_tag)
	{
		if(n >= 0)
			while(n--)
				++it;
		else
			while(n++)
				--it;
	}

	template<class Iterator, class Distance>
	inline void _advance(Iterator& it, Distance n, random_access_iterator_tag)
	{
		it += n;
	}


	template<class Iterator, class Distance>
	inline void advance(Iterator& it, Distance n)
	{
		_advance(it, n, iterator_category(it));
	}
}

#endif