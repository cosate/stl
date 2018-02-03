#ifndef GRTW_STL_SET_H
#define GRTW_STL_SET_H

#include"stl_allocator.h"
#include"stl_function.h"
#include"stl_rbtree.h"

namespace grtw
{
	template<class Key, class Compare = less<Key>, class Alloc = allocator<Key>>
	class set
	{
	private:
		using value_type = Key;
		using repo_type = RBTree<Key, value_type, identity<value_type>, Compare, Alloc>;

	public:
		using pointer = typename repo_type::const_pointer;
		using const_pointer = typename repo_type:: const_pointer;
		using reference = typename repo_type::const_reference;
		using const_reference = typename repo_type::const_reference;
		using iterator = typename repo_type::const_iterator;
		using const_iterator = typename repo_type::const_iterator;
		using reverse_iterator = typename repo_type::const_reverse_iterator;
		using const_reverse_iterator = typename repo_type::const_reverse_iterator;
		using size_type = typename repo_type::size_type;
		using difference_type = typename repo_type::difference_type;

	private:
		repo_type repository;

	public:
		set();
		~set();
		iterator begin() const { return repository.begin(); }
		iterator end() const { return repository.end(); }
		reverse_iterator rbegin() const { return repository.rbegin(); }
		reverse_iterator rend() const { return repository.rend(); }
		bool empty() const { return repository.empty(); }
		size_type size() const { return repository.size(); }
		pair<iterator, bool> insert(const value_type& x)
		{
			pair<typename repo_type::iterator, bool> 
		}
	};
}

#endif