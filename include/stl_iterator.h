#ifndef GRTW_STL_ITERATOR_H
#define GRTW_STL_ITERATOR_H

#include"stl_iterator_base.h"

namespace grtw
{
	template<class Iterator>
	class reverse_iterator
	{
	protected:
		Iterator current;
	public:
		using iterator_category = typename iterator_traits<Iterator>::iterator_category;
		using value_type = typename iterator_traits<Iterator>::value_type;
		using difference_type = typename iterator_traits<Iterator>::difference_type;
		using pointer = typename iterator_traits<Iterator>::pointer;
		using reference = typename iterator_traits<Iterator>::reference;

		using _self = reverse_iterator<Iterator>;
	public:
		reverse_iterator() {}
		explicit reverse_iterator(Iterator it) : current(it) {}
		reverse_iterator(const _self& another) : current(another.current) {}

		Iterator base() const
		{
			return current;
		}

		reference operator*() const
		{
			Iterator tmp = current;
			return *--tmp;
		}

		
	};
}

#endif