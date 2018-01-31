#ifndef GRTW_STL_FUNCTION_H
#define GRTW_STL_FUNCTION_H

namespace grtw
{
	template<class Arg1, class Arg2, class Res>
	struct binary_function
	{
		using first_argument_type = Arg1;
		using second_argument_type = Arg2;
		using result_type = Res;
	};

	template<class Arg, class Res>
	struct unary_function
	{
		using argument_type = Arg;
		using result_type = Res;
	};

	template<class T>
	struct less : public binary_function<T, T, bool>
	{
		bool operator()(const T& t1, const T& t2) const
		{
			return t1 < t2;
		}
	};

	template<class T>
	struct greater : public binary_function<T, T, bool>
	{
		bool operator()(const T& t1, const T& t2) const
		{
			return t1 > t2;
		}
	};

	template<class T>
	struct less_equal : public binary_function<T, T, bool>
	{
		bool operator()(const T& t1, const T& t2) const
		{
			return t1 <= t2;
		}
	};

	template<class T>
	struct greater_equal : public binary_function<T, T, bool>
	{
		bool operator()(const T& t1, const T& t2) const
		{
			return t1 >= t2;
		}
	};

	template<class T>
	struct equal_to : public binary_function<T, T, bool>
	{
		bool operator()(const T& t1, const T& t2) const
		{
			return t1 == t2;
		}
	};

	template<class T>
	struct not_equal_to : public binary_function<T, T, bool>
	{
		bool operator()(const T& t1, const T& t2) const
		{
			return t1 != t2;
		}
	};

	template<class Pair>
	struct select1st : public unary_function<Pair, typename Pair::first_type>
	{
		const typename Pair::first_type& operator()(const Pair& x) const
		{
			return x.first;
		}
	};

	template<class Pair>
	struct select2nd : public unary_function<Pair, typename Pair::second_type>
	{
		const typename Pair::second_type& operator()(const Pair& x) const
		{
			return x.second;
		}
	};
}

#endif