#ifndef GRTW_STL_PAIR_H
#define GRTW_STL_PAIR_H

namespace grtw
{
	template<class T1, class T2>
	struct pair
	{
		using first_type = T1;
		using second_type = T2;
		T1 first;
		T2 second;
		pair() : first(T1()), second(T2()) {}
		pair(const T1& t1, const T2& t2) :  first(t1), second(t2) {}
		template<class U1, class U2>
		pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
	};

	template<class T1, class T2>
	inline bool operator==(const pair<T1, T2>& p1, const pair<T1, T2>& p2)
	{
		return p1.first == p2.first && p1.second == p2.second;
	}

	template<class T1, class T2>
	inline bool operator!=(const pair<T1, T2>& p1, const pair<T1, T2>& p2)
	{
		return !(p1.first == p2.first && p1.second == p2.second);
	}

	template<class T1, class T2>
	inline bool operator<(const pair<T1, T2>& p1, const pair<T1, T2>& p2)
	{
		return (p1.first < p2.first) || (!(p2.first < p1.first) && (p1.second < p2.second));
	}

	template<class T1, class T2>
	inline bool operator>=(const pair<T1, T2>& p1, const pair<T1, T2>& p2)
	{
		return !(p1 < p2);
	}

	template<class T1, class T2>
	inline bool operator>(const pair<T1, T2>& p1, const pair<T1, T2>& p2)
	{
		return p2 > p1;
	}

	template<class T1, class T2>
	inline bool operator<=(const pair<T1, T2>& p1, const pair<T1, T2>& p2)
	{
		return !(p1 > p2);
	}

	template<class T1, class T2>
	inline pair<T1, T2> make_pair(const T1& t1, const T2& t2)
	{
		return pair<T1, T2>(t1, t2);
	}
}

#endif