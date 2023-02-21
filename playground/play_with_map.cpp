
// #include "../include/map.hpp"

#include <map>

#include <iostream>

// #include "../include/rb_tree.hpp"
#include "../include/__map.hpp"
#include "../include/pair.hpp"

int main(void)
{
	// std
	{
		std::map<char, int>		real_map; // constructor empty (1)
		// std::map<char, int>		real_map_par(); // constructor empty (1)

		// first insert function version (single parameter):
		std::pair<std::map<char,int>::iterator,bool> ret;

		real_map.insert ( std::pair<char,int>('a',100) );
		ret = real_map.insert ( std::pair<char,int>('z',200) );
		std::cout << " with a value of " << ret.first->second << '\n';

		
		ret = real_map.insert ( std::pair<char,int>('z',500) );
		if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';

		for (std::map<char,int>::iterator it = real_map.begin(); it != real_map.end(); ++it) {
			std::cout << "<" << it->first << ", " << it->second  << ">" << '\n';
			// std::cout << *it << std::endl;
		}
  }

	}

	// ft
	{
		ft::map<char, int>		my_map; // constructor empty (1)
		// ft::map<char, int>		my_map_par(); // constructor empty (1)

		bool check_test = my_map.test_rb_tree();
		std::cout << check_test << std::endl;

		char key = 'c';
		int value = 1;
		my_map.insert(ft::make_pair(key, value));
		my_map.insert(ft::make_pair('b', 2));

		for (ft::map<char,int>::iterator it = my_map.begin(); it != my_map.end(); ++it) {
			std::cout << "<" << it->first << ", " << it->second  << ">" << '\n';
		}
	}

	return 0;
}
