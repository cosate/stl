#ifndef GRTW_STL_MAP_H
#define GRTW_STL_MAP_H

#include"stl_function.h"
#include"stl_allocator.h"
#include"stl_rbtree.h"
#include"stl_pair.h"

namespace grtw
{
	template<class Key, class Value, class Compare = less<Key>, class Alloc = allocator<pair<const Key, Value>>>
	class map
	{
	private:
		using value_type = pair<const Key, Value>;
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
		map() : repository(Compare()) {}
		explicit map(const Compare& comp) : repository(comp) {}
		map(const value_type* vfirst, const value_type* vlast) : repository(Compare()) { repository.insert_unique(vfirst, vlast); }
		map(const_iterator vfirst, const_iterator vlast) : repository(Compare()) { repository.insert_unique(vfirst, vlast); }
		map(const map<Key, Value, Compare, Alloc>& other) : repository(other.repository) {}
		map<Key, Value, Compare, Alloc>& operator=(const map<Key, Value, Compare, Alloc>& other)
		{
			repository = other.repository;
			return *this;
		}

		iterator begin() { return repository.begin(); }
		const_iterator begin() { return repository.begin(); }
		iterator end() { return repository.end(); }
		const_iterator end() { return repository.end(); }
		reverse_iterator rbegin() { return repository.rbegin(); }
		const_reverse_iterator rbegin() { return repository.rbegin(); }
		reverse_iterator rend() { return repository.rend(); }
		const_reverse_iterator rend() { return repository.rend(); }
		bool empty() { return repository.empty(); }
		size_type size() { return repository.size(); }

		Value& operator[](const Key& k)
		{
			iterator i = lower_bound(k);
			if(i == end() || repository.key_comp()(k, (*i).first))
				i = insert(value_type(k, Value()));
			return (*i).second;
		}

		pair<iterator, bool> insert(const value_type& x) { return repository.insert_unique(x); }

		void insert(const value_type* vfirst, const value_type* vlast) { repository.insert_unique(vfirst, vlast); }
		void insert(const_iterator vfirst, const_iterator vlast) { repository.insert_unique(vfirst, vlast); }

		void erase(iterator it) { repository.erase(it); }
		size_type erase(const Key& k) { return repository.erase(k); }
		void erase(iterator vfirst, iterator vlast) { repository.erase(vfirst, vlast); }

		void clear() { repository.clear(); }

		iterator find(const Key& k) { return repository.find(); }
		const_iterator find(const Key& k) const { return repository.find(k); }
		size_type count(const Key& k) { return repository.find(k) == repository.end() ? 0 : 1; }
		iterator lower_bound(const Key& k) { return repository.lower_bound(k); }
		const_iterator lower_bound(const Key& k) const { return repository.lower_bound(k); }
		iterator upper_bound(const Key& k) { return repository.upper_bound(k); }
		const_iterator upper_bound(const Key& k) const { return repository.upper_bound(k); }
		pair<iterator, iterator> equal_range(const Key& k) { return repository.equal_range(k); }
		pair<const_iterator, const_iterator> equal_range(const Key& k) const { return repository.equal_range(k); }

		bool operator==(const map<Key, Value, Compare, Alloc>& other) { return repository == other.repository; }
		bool operator!=(const map<Key, Value, Compare, Alloc>& other) { return !(*(this) == other); }
	};
}

#endif