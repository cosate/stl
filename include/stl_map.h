#ifndef GRTW_STL_MAP_H
#define GRTW_STL_MAP_H

#include"stl_function.h"
#include"stl_allocator.h"
#include"stl_rbtree.h"
#include"stl_pair.h"

namespace grtw
{
	template<class Key, class T, class Compare = less<Key>, class Alloc = allocator<pair<const Key, T>>>
	class map
	{
	private:
		using value_type = pair<const Key, T>;
		using repo_type = RBTree<Key, value_type, select1st<value_type>, Compare, Alloc>;

	public:
		using pointer = typename repo_type::pointer;
		using const_pointer = typename repo_type::const_pointer;
		using reference = typename repo_type::reference;
		using const_reference = typename repo_type::reference;
		using iterator = typename repo_type::iterator;
		using const_iterator = typename repo_type::const_iterator;
		using reverse_iterator = typename repo_type::reverse_iterator;
		using const_reverse_iterator = typename repo_type::const_reverse_iterator;
		using size_type = typename repo_type::size_type;
		using difference_type = typename repo_type::difference_type;

	private:
		repo_type repository;

	public:
		map();
		~map();

		iterator begin() { return repository.begin(); }
		const_iterator begin() { return repository.begin(); }
		iterator end() { return repository.end(); }
		const_iterator end() { return repository.end(); }
		reverse_iterator rbegin() { return repository.rbegin(); }
		const_reverse_iterator rbegin() { return repository.rbegin(); }
		reverse_iterator rend() { return repository.rend(); }
		const_reverse_iterator rend() { return repository.rend(); }
		bool empty() { return repository.empty(); }
		size_type size() { return size(); }
		T& operator[](const Key& k)
		{
			iterator i = lower_bound(k);
			if(i == end() || key_comp()(k, (*i).first))
				i = insert(value_type(k, T()));
			return (*i).second;
		}

		pair<iterator, bool> insert(const value_type& x)
		{
			
		}
	};
}

#endif