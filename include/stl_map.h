#ifndef GRTW_STL_MAP_H
#define GRTW_STL_MAP_H

#include"stl_function.h"
#include"stl_allocator.h"
#include"stl_rbtree.h"
#include"stl_pair.h"

namespace grtw
{
	template<class Key, class T, class Compare = less<Key>, class Alloc = allocator<T>>
	class map
	{
	public:
		using value_type = pair<const Key, T>;

	private:
		RBTree<Key, value_type, >
	public:
		map();
		~map();
		
	};
}

#endif