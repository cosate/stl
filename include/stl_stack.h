#ifndef GRTW_STL_STACK_H
#define GRTW_STL_STACK_H

#include"stl_deque.h"

namespace grtw
{
	template<class T, class Sequence = deque<T>>
	class stack
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
		stack() : c() {}
		explicit stack(const Sequence& s) : c(s) {}
		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }
		reference top() ( return c.back(); )
		const_reference top() const { return c.back(); }
		void push(const value_type& v) { c.push_back(v); }
		void pop() { c.pop_back(); }
	};
}

#endif