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

	template<class T>
	struct less : public binary_function<T, T, bool>
	{
		bool operator()(const T& t1, const T& t2) const
		{
			return t1 < t2;
		}
	};
}

#endif