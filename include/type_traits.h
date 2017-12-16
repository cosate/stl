#ifndef GRTW_TYPE_TRAITS_H
#define GRTW_TYPE_TRAITS_H

namespace grtw
{
	struct true_type {};
	struct false_type {};
	
	template<class T>
	struct type_traits
	{
		using has_trivial_constructor = false_type;
		using has_trivial_copy_constructor = false_type;
		using has_assignment_operator = false_type;
		using has_trivial_destructor = false_type;
		using is_POD_type = false_type;
	};

	template<>
	struct type_traits<bool>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<char>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<signed char>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<unsigned char>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<wchar_t>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<short>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<unsigned short>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<int>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<unsigned int>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<long>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<unsigned long>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<long long>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<unsigned long long>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<float>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<double>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<>
	struct type_traits<long double>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};

	template<T>
	struct type_traits<T*>
	{
		using has_trivial_constructor = true_type;
		using has_trivial_copy_constructor = true_type;
		using has_assignment_operator = true_type;
		using has_trivial_destructor = true_type;
		using is_POD_type = true_type;
	};


	//Is_integer
	template <class T>
	struct Is_integer
	{
		using Integral = false_type;
	};

	template<>
	struct Is_integer<bool>
	{
		using Integral = true_type;
	};

	template<>
	struct Is_integer<char>
	{
		using Integral = true_type;
	};

	template<>
	struct Is_integer<signed char>
	{
		using Integral = true_type;
	}
	};

	template<>
	struct Is_integer<unsigned char>
	{
		using Integral = true_type;
	};

	template<>
	struct Is_integer<wchar_t>
	{
		using Integral = true_type;
	};

	template<>
	struct Is_integer<short>
	{
		using Integral = true_type;
	};

	template<>
	struct Is_integer<unsigned short>
	{
		using Integral = true_type;
	};

	template<>
	struct Is_integer<int>
	{
		using Integral = true_type;
	};

	template<>
	struct Is_integer<unsigned int>
	{
		using Integral = true_type;
	};

	template<>
	struct Is_integer<long>
	{
		using Integral = true_type;
	};

	template<>
	struct Is_integer<unsigned long>
	{
		using Integral = true_type;
	};

	template<>
	struct Is_integer<long long>
	{
		using Integral = true_type;
	};

	template<>
	struct Is_integer<unsigned long long>
	{
		using Integral = true_type;
	};
}

#endif