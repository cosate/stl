#ifndef GRTW_STL_HASH_FUNCTION_H
#define GRTW_STL_HASH_FUNCTION_H

#include<stddef.h>

namespace grtw
{
	template<class Key>
	struct hash { };

	inline size_t stl_hash_string(const char* s)
	{
		unsigned long h = 0;
		for(; *s; ++s)
			h = 5 * h + *s;
		return size_t(h);
	}

	template<>
	struct hash<char*>
	{
		size_t operator()(const char* s) const
		{
			return stl_hash_string(s);
		}
	};

	template<>
	struct hash<const char*>
	{
		size_t operator()(const char* s) const
		{
			return stl_hash_string(s);
		}
	};

	template<>
	struct hash<char>
	{
		size_t operator()(char c) const
		{
			return c;
		}
	};

	template<>
	struct hash<unsigned char>
	{
		size_t operator()(unsigned char c) const
		{
			return c;
		}
	};

	template<>
	struct hash<signed char>
	{
		size_t operator()(signed char c) const
		{
			return c;
		}
	};

	template<>
	struct hash<short>
	{
		size_t operator()(short c) const
		{
			return c;
		}
	};

	template<>
	struct hash<unsigned short>
	{
		size_t operator()(unsigned short c) const
		{
			return c;
		}
	};

	template<>
	struct hash<int>
	{
		size_t operator()(int c) const
		{
			return c;
		}
	};

	template<>
	struct hash<unsigned int>
	{
		size_t operator()(unsigned int c) const
		{
			return c;
		}
	};

	template<>
	struct hash<long>
	{
		size_t operator()(long c) const
		{
			return c;
		}
	};

	template<>
	struct hash<unsigned long>
	{
		size_t operator()(unsigned long c) const
		{
			return c;
		}
	};
}

#endif