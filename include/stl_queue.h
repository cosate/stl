#ifndef GRTW_STL_QUEUE_H
#define GRTW_STL_QUEUE_H

#include"stl_deque.h"
#include"stl_vector.h"
#include"stl_function.h"
#include"stl_heap.h"

namespace grtw
{
	template<class T, class Sequence = deque<T>>
	class queue
	{
	public:
		using value_type = typename Sequence::value_type;
		using size_type = typename Sequence::size_type;
		using container_type = Sequence;
		using reference = typename Sequence::reference;
		using const_reference = typename Sequence::const_reference;

	private:
		Sequence c;

	public:
		queue() : c() {}
		explicit queue(const Sequence& s) : c(s) {}
		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }
		reference front() { return c.front(); }
		const_reference front() const { return c.front(); }
		reference back() { return c.back(); }
		const_reference back() const { return c.back(); }
		void push(const value_type& x) { c.push(x); }
		void pop() { c.pop(); }
	};

	template<class T, class Sequence = vector<T>, class Compare = less<typename Sequence::value_type>>
	class priority_queue
	{
	public:
		using value_type = typename Sequence::value_type;
		using size_type = typename Sequence::size_type;
		using container_type = Sequence;
		using reference = typename Sequence::reference;
		using const_reference = typename Sequence::const_reference;

	private:
		Sequence c;
		Compare comp;

	public:
		priority_queue() : c() {}
		explicit priority_queue(const Compare& x) : c(), comp(x) {}
		priority_queue(const Compare& x, const Sequence& s) : c(s), comp(x) { make_heap(c.begin(), c.end(), comp); }

		priority_queue(const value_type* vfirst, const value_type* vlast) : c(vfirst, vlast) { make_heap(c.begin(), c.end()); }
		priority_queue(const value_type* vfirst, const value_type* vlast, const Compare& x) : c(vfirst, vlast), comp(x) { make_heap(c.begin(), c.end()); }

		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }
		const_reference top() const { return c.front(); }
		void push(const value_type& x)
		{
			c.push_back(x);
			push_heap(c.begin(), c.end(), comp);
		}

		void pop()
		{
			pop_heap(c.begin(), c.end(), comp);
			c.pop_back();
		}
	};
}

#endif