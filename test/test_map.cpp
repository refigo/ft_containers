#include "my_tester.hpp"
#include "map.hpp"
#include <map>

void test_map() {
	timeval ft_start;
	timeval ft_end;
	timeval std_start;
	timeval std_end;
	ll ft_time;
	ll std_time;

	// MAP TEST

	std::cout << CYAN << BOLD << "\n\n------------- map -------------\n\n" << RESET << std::endl;
// map insert
	std::cout << YELLOW << BOLD << "------------- map insert -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
		ft::map<int, int> map_int;
		for (int i = 0; i < MAP_SIZE; i++)
			map_int.insert(ft::make_pair(i, i));
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::map<int, int> std_map_int;
		for (int i = 0; i < MAP_SIZE; i++)
			std_map_int.insert(std::make_pair(i, i));
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::map - insert is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::map - insert is OK" << RESET << std::endl;

// map find
	std::cout << YELLOW << BOLD << "------------- map find -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
		ft::map<int, int> map_int;
		for (int i = 0; i < MAP_SIZE; i++)
			map_int.insert(ft::make_pair(i, i));
		for (int i = 0; i < MAP_SIZE; i++)
			map_int.find(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::map<int, int> std_map_int;
		for (int i = 0; i < MAP_SIZE; i++)
			std_map_int.insert(std::make_pair(i, i));
		for (int i = 0; i < MAP_SIZE; i++)
			std_map_int.find(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::map - find is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::map - find is OK" << RESET << std::endl;

// map erase
	std::cout << YELLOW << BOLD << "------------- map erase -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
		ft::map<int, int> map_int;
		for (int i = 0; i < MAP_SIZE; i++)
			map_int.insert(ft::make_pair(i, i));
		for (int i = 0; i < MAP_SIZE; i++)
			map_int.erase(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::map<int, int> std_map_int;
		for (int i = 0; i < MAP_SIZE; i++)
			std_map_int.insert(std::make_pair(i, i));
		for (int i = 0; i < MAP_SIZE; i++)
			std_map_int.erase(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::map - erase is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::map - erase is OK" << RESET << std::endl;

// map relational operators
	std::cout << YELLOW << BOLD << "------------- map relational operators -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
		ft::map<int, int> map_int;
		ft::map<int, int> map_int2;
		ft::map<int, int> map_int3;
		for (int i = 0; i < MAP_SIZE; i++)
		{
			map_int.insert(ft::make_pair(i, i));
			map_int2.insert(ft::make_pair(i, i));
			map_int3.insert(ft::make_pair(i + 1, i + 1));
		}
		if (map_int != map_int2)
		{
			std::cout << RED << BOLD << "ft::map - relational operators(==) is not OK" << RESET << std::endl;
			exit(1);
		}
		if (map_int > map_int3)
		{
			std::cout << RED << BOLD << "ft::map - relational operators(>) is not OK" << RESET << std::endl;
			exit(1);
		}
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::map<int, int> std_map_int;
		std::map<int, int> std_map_int2;
		std::map<int, int> std_map_int3;
		for (int i = 0; i < MAP_SIZE; i++)
		{
			std_map_int.insert(std::make_pair(i, i));
			std_map_int2.insert(std::make_pair(i, i));
			std_map_int3.insert(std::make_pair(i + 1, i + 1));
		}
		if (std_map_int != std_map_int2)
		{
			std::cout << RED << BOLD << "std::map - relational operators(==) is not OK" << RESET << std::endl;
			exit(1);
		}
		if (std_map_int > std_map_int3)
		{
			std::cout << RED << BOLD << "std::map - relational operators(>) is not OK" << RESET << std::endl;
			exit(1);
		}
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::map - relational operators is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::map - relational operators is OK" << RESET << std::endl;

// map swap
	std::cout << YELLOW << BOLD << "------------- map swap -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
		ft::map<int, int> map_int;
		ft::map<int, int> map_int2;
		for (int i = 0; i < MAP_SIZE; i++)
		{
			map_int.insert(ft::make_pair(i, i));
			map_int2.insert(ft::make_pair(i + 1, i + 1));
		}
		map_int.swap(map_int2);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::map<int, int> std_map_int;
		std::map<int, int> std_map_int2;
		for (int i = 0; i < MAP_SIZE; i++)
		{
			std_map_int.insert(std::make_pair(i, i));
			std_map_int2.insert(std::make_pair(i + 1, i + 1));
		}
		std_map_int.swap(std_map_int2);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::map - swap is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::map - swap is OK" << RESET << std::endl;

// map clear
	std::cout << YELLOW << BOLD << "------------- map clear -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
		ft::map<int, int> map_int;
		for (int i = 0; i < MAP_SIZE; i++)
			map_int.insert(ft::make_pair(i, i));
		map_int.clear();
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::map<int, int> std_map_int;
		for (int i = 0; i < MAP_SIZE; i++)
			std_map_int.insert(std::make_pair(i, i));
		std_map_int.clear();
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::map - clear is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::map - clear is OK" << RESET << std::endl;
    
// map lower_bound
	std::cout << YELLOW << BOLD << "------------- map lower_bound -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
        ft::map<int, int> map_int;
        for (int i = 0; i < MAP_SIZE; i++)
            map_int.insert(ft::make_pair(i, i));
        for (int i = 0; i < MAP_SIZE; i++)
            map_int.lower_bound(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::map<int, int> std_map_int;
		for (int i = 0; i < MAP_SIZE; i++)
			std_map_int.insert(std::make_pair(i, i));
        for (int i = 0; i < MAP_SIZE; i++)
            std_map_int.lower_bound(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::map - lower_bound is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::map - lower_bound is OK" << RESET << std::endl;

// map upper_bound
    std::cout << YELLOW << BOLD << "------------- map upper_bound -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
        ft::map<int, int> map_int;
        for (int i = 0; i < MAP_SIZE; i++)
            map_int.insert(ft::make_pair(i, i));
        for (int i = 0; i < MAP_SIZE; i++)
            map_int.upper_bound(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::map<int, int> std_map_int;
		for (int i = 0; i < MAP_SIZE; i++)
			std_map_int.insert(std::make_pair(i, i));
        for (int i = 0; i < MAP_SIZE; i++)
            std_map_int.upper_bound(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::map - upper_bound is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::map - upper_bound is OK" << RESET << std::endl;

// map equal_range
    std::cout << YELLOW << BOLD << "------------- map equal_range -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
        ft::map<int, int> map_int;
        for (int i = 0; i < MAP_SIZE; i++)
            map_int.insert(ft::make_pair(i, i));
        for (int i = 0; i < MAP_SIZE; i++)
            map_int.equal_range(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::map<int, int> std_map_int;
		for (int i = 0; i < MAP_SIZE; i++)
			std_map_int.insert(std::make_pair(i, i));
        for (int i = 0; i < MAP_SIZE; i++)
            std_map_int.equal_range(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::map - equal_range is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::map - equal_range is OK" << RESET << std::endl;
}