#ifndef GRTW_STL_ITERATOR_H
#define GRTW_STL_ITERATOR_H

#include"stl_iterator_base.h"

namespace grtw
{
	template<class Iterator>
	class Reverse_iterator
	{
	protected:
		Iterator current;
	public:
		using iterator_category = typename iterator_traits<Iterator>::iterator_category;
		using value_type = typename iterator_traits<Iterator>::value_type;
		using difference_type = typename iterator_traits<Iterator>::difference_type;
		using pointer = typename iterator_traits<Iterator>::pointer;
		using reference = typename iterator_traits<Iterator>::reference;

		using _self = Reverse_iterator<Iterator>;
	public:
		Reverse_iterator() {}
		explicit Reverse_iterator(Iterator it) : current(it) {}
		Reverse_iterator(const _self& another) : current(another.current) {}

		Iterator base() const
		{
			return current;
		}

		reference operator*() const
		{
			Iterator tmp = current;
			return *--tmp;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		_self& operator++()
		{
			--current;
			return *this;
		}

		_self operator++(int)
		{
			_self tmp = *this;
			--current;
			return tmp;
		}

		_self& operator--()
		{
			++current;
			return *this;
		}

		_self operator--(int)
		{
			_self tmp = *this;
			++current;
			return tmp;
		}

		_self operator+(difference_type n)
		{
			return _self(current - n);
		}

		_self& operator+=(difference_type n)
		{
			current -= n;
			return *this;
		}

		_self operator-(difference_type n)
		{
			return _self(current + n);
		}

		_self operator-=(difference_type n)
		{
			current += n;
			return *this;
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}
	};

	template<class Iterator>
	inline bool operator==(const Reverse_iterator<Iterator>& x, const Reverse_iterator<Iterator>& y)
	{
		return x.base() == y.base();
	}

	template<class Iterator>
	inline bool operator!=(const Reverse_iterator<Iterator>& x, const Reverse_iterator<Iterator>& y)
	{
		return !(x == y);
	}

	template<class Iterator>
	inline bool operator<(const Reverse_iterator<Iterator>& x, const Reverse_iterator<Iterator>& y)
	{
		return y.base() < x.base();
	}

	template<class Iterator>
	inline bool operator>(const Reverse_iterator<Iterator>& x, const Reverse_iterator<Iterator>& y)
	{
		return y < x;
	}

	template<class Iterator>
	inline bool operator<=(const Reverse_iterator<Iterator>& x, const Reverse_iterator<Iterator>& y)
	{
		return !(y < x);
	}

	template<class Iterator>
	inline bool operator>=(const Reverse_iterator<Iterator>& x, const Reverse_iterator<Iterator>& y)
	{
		return !(x < y);
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
	operator-(const Reverse_iterator<Iterator>& x, const Reverse_iterator<Iterator>& y)
	{
		return y.base() - x.base();
	}

	template<class Iterator>
	inline Reverse_iterator<Iterator>
	operator+(typename Reverse_iterator<Iterator>::difference_type n, const Reverse_iterator<Iterator>& x)
	{
		return Reverse_iterator<Iterator>(x.base() - n);
	}
}

#endif