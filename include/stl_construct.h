#ifndef GRTW_STL_CONSTRUCT_H
#define GRTW_STL_CONSTRUCT_H

#include<new>
#include"type_traits.h"

namespace grtw
{
	//construct : placement new
	template<class T1, class T2>
	inline void construct(T1* p, T2& value)
	{
		new ((void*)p) (T1)value;
	}

	template<class T>
	inline void construct(T* p)
	{
		new ((void*)p) T();
	}


	//destroy
	template<class T>
	void destroy(T* p)
	{
		p->~T();
	}

	template<class Iterator>
	void destroy(Iterator first, Iterator last)
	{
		_destroy(first, last, value_type(first));
	}

	template<class Iterator, class T>
	void _destroy(Iterator first, Iterator last, T*)
	{
		using trivial_destructor = type_traits<T>::has_trivial_destructor;
		__destroy(first, last, trivial_destructor());
	}

	template<class Iterator>
	void __destroy(Iterator first, Iterator last, false_type)
	{
		for(; first != last; first++)
			destroy(&*first);
	}

	template<class Iterator>
	void __destroy(Iterator first, Iterator last, true_type)
	{}
}

#endif