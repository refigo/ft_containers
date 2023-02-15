#include "../include/vector.hpp"

#include <vector>
#include <iostream>

#include <list>
#include <string>

template <class Vec>
void	print_vector(Vec v1) {
	for (unsigned long i(0); i < v1.size(); ++i) {
		std::cout << v1[i] << ' ';
	}
	std::cout << '\n';
}

void real_std_stl(void)
{
	std::cout << "[std vector constructor]\n";

	std::vector<int>	real_vector;
	std::vector<int>	real_vector_fill(10, 5);
	std::vector<int>::iterator	it_begin_rv(real_vector_fill.begin());
	std::vector<int>::iterator	it_end_rv(real_vector_fill.end());
	std::vector<int>	real_vector_range(it_begin_rv, it_end_rv);
	print_vector(real_vector_range);

	std::list<int>		real_list_fill(4, 42);
	std::vector<int>	real_vector_bidirect(real_list_fill.begin(), real_list_fill.end());
	// std::cout << "real_vector_bidirect.end(): " << *real_vector_bidirect.end() << std::endl;
	// std::cout << "real_vector_fill.end(): " << *real_vector_fill.end() << std::endl;
	// std::vector<int>::iterator	real_it_begin_before = real_vector_bidirect.begin();
	real_vector_bidirect.insert(real_vector_bidirect.begin(), 200);
	// std::cout << "real_it_begin_before: " << *real_it_begin_before << std::endl; // stl에서도 터진다.
	print_vector(real_vector_bidirect);
	real_vector_bidirect.insert(real_vector_bidirect.begin() + 2, 3, 400);
	print_vector(real_vector_bidirect);

	// for test leaks
	// std::list<std::string>		real_list_fill_str(4, "test");
	// std::vector<std::string>	real_vector_bidirect_str(real_list_fill_str.begin(), real_list_fill_str.end());
	// real_vector_bidirect_str.insert(real_vector_bidirect_str.begin() + 1, "test2");
	// print_vector(real_vector_bidirect_str);
}

void test_ft_stl(void)
{
	std::cout << "[ft vector constructor]\n";

	ft::vector<int>		test_ft_vector;
	ft::vector<int>		test_ft_vector_fill(10, 5);
	// std::cout << "test_ft_vector_fill.size(): " << test_ft_vector_fill.size() << std::endl;
	ft::vector<int>		test_ft_vector_copy(test_ft_vector_fill);
	print_vector(test_ft_vector_copy);
	// test_ft_vector.assign(test_ft_vector_fill.begin(), test_ft_vector_fill.end());
	// print_vector(test_ft_vector);
	// test_ft_vector_copy.assign(2, 42);
	// std::cout << "test_ft_vector_copy.size(): " << test_ft_vector_copy.size() << std::endl;
	// print_vector(test_ft_vector_copy);

	std::list<int>		real_list_fill(4, 42);
	ft::vector<int>	test_vector_bidirect(real_list_fill.begin(), real_list_fill.end());
	// ft::vector<int>::iterator	test_it_begin_before = test_vector_bidirect.begin();
	test_vector_bidirect.insert(test_vector_bidirect.begin(), 200);
	// std::cout << "test_it_begin_before: " << *test_it_begin_before << std::endl;
	print_vector(test_vector_bidirect);
	test_vector_bidirect.insert(test_vector_bidirect.begin() + 2, 3, 400);
	print_vector(test_vector_bidirect);

	// test for leaks
	// std::list<std::string>		test_list_fill_str(4, "test");
	// ft::vector<std::string>		test_vector_bidirect_str(test_list_fill_str.begin(), test_list_fill_str.end());
	// test_vector_bidirect_str.insert(test_vector_bidirect_str.begin() + 1, "test2");
	// print_vector(test_vector_bidirect_str);
}

int	main(void) {
	real_std_stl();
	test_ft_stl();

	{
		std::list<int> lst;
		for (int i = 1; i < 5; ++i)
			lst.push_back(i * 3);
		std::list<int>::reverse_iterator it_rbegin(lst.rbegin());
		std::list<int>::reverse_iterator it_rend(lst.rend());
		for (int __i(0); it_rbegin != it_rend; ++it_rbegin, ++__i)
		{
			// std::cout << it_rbegin << '\n';
			std::cout << __i << '\n';
		}
	}

	// system("leaks a.out");
	return 0;
}
