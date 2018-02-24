#include<iostream>
#include"include/stl_vector.h"
#include"include/stl_map.h"

int main()
{
	grtw::vector<int> vec(3);
	vec.push_back(9);
	vec.push_back(8);
	vec.push_back(7);
	for(int i = 0; i < vec.size(); i++)
		std::cout<<vec[i]<<"   "<<std::endl;

	std::cout<<std::endl<<std::endl;
	
	grtw::map<int, char> m;
	m[4] = 'f';
	m[6] = 's';
	m[1] = 't';
	for(grtw::map<int, char>::iterator it = m.begin(); it != m.end(); it++)
		std::cout<<it->first<<"   "<<it->second<<"   "<<std::endl;
	return 0;
}