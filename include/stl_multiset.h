#ifndef GRTW_STL_MULTISET_H
#define GRTW_STL_MULTISET_H

namespace grtw
{
	template<class Key, class Compare = less<Key>, class Alloc = allocator<Key>>
	class multiset
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
		multiset() : repository(Compare()) {}
		explicit multiset(const Compare& comp) : repository(comp) {}
		multiset(const value_type* vfirst, const value_type* vlast) : repository(Compare()) { repository.insert_equal(vfirst, vlast); }
		multiset(const value_type* vfirst, const value_type* vlast, const Compare& comp) : repository(comp) { repository.insert_equal(vfirst, vlast); }
		multiset(const_iterator vfirst, const_iterator vlast) : repository(Compare()) { repository.insert_equal(vfirst, vlast); }
		multiset(const_iterator vfirst, const_iterator vlast, const Compare& comp) : repository(comp) { repository.insert_equal(vfirst, vlast); }
		multiset(const multiset<Key, Compare, Alloc>& other) : repository(other.repository) {}
		multiset<Key, Compare, Alloc>& operator=(const multiset<Key, Compare, Alloc>& other)
		{
			repository = other.repository;
			return *this;
		}

		iterator begin() const { return repository.begin(); }
		iterator end() const { return repository.end(); }
		reverse_iterator rbegin() const { return repository.rbegin(); }
		reverse_iterator rend() const { return repository.rend(); }
		bool empty() const { return repository.empty(); }
		size_type size() const { return repository.size(); }

		iterator insert(const value_type& x) { return repository.insert_equal(x); }
		void insert(const_iterator vfirst, const_iterator vlast) { repository.insert_equal(vfirst, vlast); }
		void insert(const value_type* vfirst, const value_type* vlast) { repository.insert_equal(vfirst, vlast); }

		void erase(iterator it)
		{
			using repo_iterator = repo_type::iterator;
			repository.erase((repo_iterator&)it);
		}

		size_type erase(const Key& k)
		{
			return repository.erase(k);
		}

		void erase(iterator vfirst, iterator vlast)
		{
			using repo_iterator = repo_type::iterator;
			repository.erase((repo_iterator&)vfirst, (repo_iterator&)vlast);
		}

		void clear() { repository.clear(); }

		iterator find(const Key& k) const { return repository.find(k); }
		size_type count(const Key& k) const { return repository.find(k) == repository.end() ? 0 : 1; }
		iterator lower_bound(const Key& k) const { return repository.lower_bound(k); }
		iterator upper_bound(const Key& k) const { return repository.upper_bound(k); }
		pair<iterator, iterator> equal_range(const Key& k) const { return repository.equal_range(k); }

		bool operator==(const multiset<Key, Compare, Alloc>& other) { return repository == other.repository; }
		bool operator!=(const multiset<Key, Compare, Alloc>& other) { return !(*(this) == other); }
	};
}

#endif