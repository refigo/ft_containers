#include "my_tester.hpp"
#include "set.hpp"
#include <set>

void test_set() {
	timeval ft_start;
	timeval ft_end;
	timeval std_start;
	timeval std_end;
	ll ft_time;
	ll std_time;

	// SET TEST

	std::cout << CYAN << BOLD << "\n\n------------- set -------------\n\n" << RESET << std::endl;
// set insert
	std::cout << YELLOW << BOLD << "------------- set insert -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
		ft::set<int> set_int;
		for (int i = 0; i < SET_SIZE; i++)
			set_int.insert(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::set<int> std_set_int;
		for (int i = 0; i < SET_SIZE; i++)
			std_set_int.insert(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::set - insert is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::set - insert is OK" << RESET << std::endl;

// set find
	std::cout << YELLOW << BOLD << "------------- set find -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
		ft::set<int> set_int;
		for (int i = 0; i < SET_SIZE; i++)
			set_int.insert(i);
		for (int i = 0; i < SET_SIZE; i++)
			set_int.find(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::set<int> std_set_int;
		for (int i = 0; i < SET_SIZE; i++)
			std_set_int.insert(i);
		for (int i = 0; i < SET_SIZE; i++)
			std_set_int.find(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::set - find is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::set - find is OK" << RESET << std::endl;

// set erase
	std::cout << YELLOW << BOLD << "------------- set erase -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
		ft::set<int> set_int;
		for (int i = 0; i < SET_SIZE; i++)
			set_int.insert(i);
		for (int i = 0; i < SET_SIZE; i++)
			set_int.erase(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::set<int> std_set_int;
		for (int i = 0; i < SET_SIZE; i++)
			std_set_int.insert(i);
		for (int i = 0; i < SET_SIZE; i++)
			std_set_int.erase(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::set - erase is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::set - erase is OK" << RESET << std::endl;

// set relational operators
	std::cout << YELLOW << BOLD << "------------- set relational operators -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
		ft::set<int> set_int;
		ft::set<int> set_int2;
		ft::set<int> set_int3;
		for (int i = 0; i < SET_SIZE; i++)
		{
			set_int.insert(i);
			set_int2.insert(i);
			set_int3.insert(i + 1);
		}
		if (set_int != set_int2)
		{
			std::cout << RED << BOLD << "ft::set - relational operators(==) is not OK" << RESET << std::endl;
			exit(1);
		}
		if (set_int > set_int3)
		{
			std::cout << RED << BOLD << "ft::set - relational operators(>) is not OK" << RESET << std::endl;
			exit(1);
		}
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::set<int> std_set_int;
		std::set<int> std_set_int2;
		std::set<int> std_set_int3;
		for (int i = 0; i < SET_SIZE; i++)
		{
			std_set_int.insert(i);
			std_set_int2.insert(i);
			std_set_int3.insert(i + 1);
		}
		if (std_set_int != std_set_int2)
		{
			std::cout << RED << BOLD << "std::set - relational operators(==) is not OK" << RESET << std::endl;
			exit(1);
		}
		if (std_set_int > std_set_int3)
		{
			std::cout << RED << BOLD << "std::set - relational operators(>) is not OK" << RESET << std::endl;
			exit(1);
		}
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::set - relational operators is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::set - relational operators is OK" << RESET << std::endl;

// set swap
	std::cout << YELLOW << BOLD << "------------- set swap -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
		ft::set<int> set_int;
		ft::set<int> set_int2;
		for (int i = 0; i < SET_SIZE; i++)
		{
			set_int.insert(i);
			set_int2.insert(i + 1);
		}
		set_int.swap(set_int2);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::set<int> std_set_int;
		std::set<int> std_set_int2;
		for (int i = 0; i < SET_SIZE; i++)
		{
			std_set_int.insert(i);
			std_set_int2.insert(i + 1);
		}
		std_set_int.swap(std_set_int2);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::set - swap is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::set - swap is OK" << RESET << std::endl;

// set clear
	std::cout << YELLOW << BOLD << "------------- set clear -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
		ft::set<int> set_int;
		for (int i = 0; i < SET_SIZE; i++)
			set_int.insert(i);
		set_int.clear();
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::set<int> std_set_int;
		for (int i = 0; i < SET_SIZE; i++)
			std_set_int.insert(i);
		std_set_int.clear();
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::set - clear is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::set - clear is OK" << RESET << std::endl;
    
// set lower_bound
	std::cout << YELLOW << BOLD << "------------- set lower_bound -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
        ft::set<int> set_int;
        for (int i = 0; i < SET_SIZE; i++)
            set_int.insert(i);
        for (int i = 0; i < SET_SIZE; i++)
            set_int.lower_bound(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::set<int> std_set_int;
		for (int i = 0; i < SET_SIZE; i++)
			std_set_int.insert(i);
        for (int i = 0; i < SET_SIZE; i++)
            std_set_int.lower_bound(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::set - lower_bound is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::set - lower_bound is OK" << RESET << std::endl;

// set upper_bound
    std::cout << YELLOW << BOLD << "------------- set upper_bound -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
        ft::set<int> set_int;
        for (int i = 0; i < SET_SIZE; i++)
            set_int.insert(i);
        for (int i = 0; i < SET_SIZE; i++)
            set_int.upper_bound(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::set<int> std_set_int;
		for (int i = 0; i < SET_SIZE; i++)
			std_set_int.insert(i);
        for (int i = 0; i < SET_SIZE; i++)
            std_set_int.upper_bound(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::set - upper_bound is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::set - upper_bound is OK" << RESET << std::endl;

// set equal_range
    std::cout << YELLOW << BOLD << "------------- set equal_range -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
        ft::set<int> set_int;
        for (int i = 0; i < SET_SIZE; i++)
            set_int.insert(i);
        for (int i = 0; i < SET_SIZE; i++)
            set_int.equal_range(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::set<int> std_set_int;
		for (int i = 0; i < SET_SIZE; i++)
			std_set_int.insert(i);
        for (int i = 0; i < SET_SIZE; i++)
            std_set_int.equal_range(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::set - equal_range is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::set - equal_range is OK" << RESET << std::endl;
}