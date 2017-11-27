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
}

#endif