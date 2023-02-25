#include "my_tester.hpp"
#include "vector.hpp"
#include <vector>

void test_vector() {
	timeval ft_start;
	timeval ft_end;
	timeval std_start;
	timeval std_end;
	ll ft_time;
	ll std_time;

	// vector
	std::cout << CYAN << BOLD << "\n\n------------- vector -------------\n\n" << RESET << std::endl;

// vector push_back
	std::cout << YELLOW << BOLD << "------------- vector push_back -------------" << RESET << std::endl;
	/* ft::vector push_back */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int;
		for (int i = 0; i < VEC_SIZE; i++)
			vector_int.push_back(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	/* std::vector push_back */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int;
		for (int i = 0; i < VEC_SIZE; i++)
			std_vector_int.push_back(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::vector - push_back is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - push_back is OK" << RESET << std::endl;

// vector pop_back
	std::cout << YELLOW << BOLD << "------------- vector pop_back -------------" << RESET << std::endl;
	/* ft::vector pop_back */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int(VEC_SIZE, 0);
		for (int i = 0; i < VEC_SIZE; i++)
			vector_int.pop_back();
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	/* std::vector pop_back */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int(VEC_SIZE, 0);
		for (int i = 0; i < VEC_SIZE; i++)
			std_vector_int.pop_back();
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::vector - pop_back is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - pop_back is OK" << RESET << std::endl;

// vector insert
	std::cout << YELLOW << BOLD << "------------- vector insert -------------" << RESET << std::endl;
	/* ft::vector insert */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int;
		for (int i = 0; i < VEC_SIZE; i++)
			vector_int.insert(vector_int.begin(), i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	/* std::vector insert */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int;
		for (int i = 0; i < VEC_SIZE; i++)
			std_vector_int.insert(std_vector_int.begin(), i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);

	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::vector - insert is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - insert is OK" << RESET << std::endl;

// vector erase
	std::cout << YELLOW << BOLD << "------------- vector erase -------------" << RESET << std::endl;
	/* ft::vector erase */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int(VEC_SIZE, 0);
		for (int i = 0; i < VEC_SIZE; i++)
			vector_int.erase(vector_int.begin());
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	/* std::vector erase */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int(VEC_SIZE, 0);
		for (int i = 0; i < VEC_SIZE; i++)
			std_vector_int.erase(std_vector_int.begin());
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::vector - erase is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - erase is OK" << RESET << std::endl;

// vector swap
	std::cout << YELLOW << BOLD << "------------- vector swap -------------" << RESET << std::endl;
	/* ft::vector swap */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int(VEC_SIZE, 0);
		ft::vector<int> vector_int2(VEC_SIZE, 0);
		for (int i = 0; i < VEC_SIZE; i++)
			vector_int.swap(vector_int2);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	/* std::vector swap */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int(VEC_SIZE, 0);
		std::vector<int> std_vector_int2(VEC_SIZE, 0);
		for (int i = 0; i < VEC_SIZE; i++)
			std_vector_int.swap(std_vector_int2);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::vector - swap is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - swap is OK" << RESET << std::endl;

// vector clear
	std::cout << YELLOW << BOLD << "------------- vector clear -------------" << RESET << std::endl;
	/* ft::vector clear */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int(VEC_SIZE, 0);
		for (int i = 0; i < VEC_SIZE; i++)
			vector_int.clear();
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	/* std::vector clear */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int(VEC_SIZE, 0);
		for (int i = 0; i < VEC_SIZE; i++)
			std_vector_int.clear();
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::vector - clear is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - clear is OK" << RESET << std::endl;

// vector relational operators
	std::cout << YELLOW << BOLD << "------------- vector relational operators -------------" << RESET << std::endl;
	/* ft::vector relational operators */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int(VEC_SIZE, 0);
		ft::vector<int> vector_int2(VEC_SIZE, 0);
		for (int i = 0; i < VEC_SIZE; i++)
			if (vector_int != vector_int2)
			{
				std::cout << RED << BOLD <<  "ft::vector - relational operators is wrong" << RESET << std::endl;
				exit(1);
			}
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	/* std::vector relational operators */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int(VEC_SIZE, 0);
		std::vector<int> std_vector_int2(VEC_SIZE, 0);
		for (int i = 0; i < VEC_SIZE; i++)
		{
			if (std_vector_int != std_vector_int2)
			{
				std::cout << RED << BOLD << "std::vector - relational operators is wrong" << RESET << std::endl;
				exit(1);
			}
		}
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::vector - relational operators is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - relational operators is OK" << RESET << std::endl;

// vector iterator
	std::cout << YELLOW << BOLD << "------------- vector iterator -------------" << RESET << std::endl;
	/* ft::vector iterator */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int(VEC_SIZE, 0);
		ft::vector<int>::iterator it = vector_int.begin();
		ft::vector<int>::iterator ite = vector_int.end();
		for (; it != ite; it++)
			*it = 0;
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	/* std::vector iterator */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int(VEC_SIZE, 0);
		std::vector<int>::iterator it = std_vector_int.begin();
		std::vector<int>::iterator ite = std_vector_int.end();
		for (; it != ite; it++)
			*it = 0;
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::vector - iterator is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - iterator is OK" << RESET << std::endl;

// vector reverse iterator
	std::cout << YELLOW << BOLD << "------------- vector reverse iterator -------------" << RESET << std::endl;
	/* ft::vector reverse iterator */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int(VEC_SIZE, 0);
		ft::vector<int>::reverse_iterator it = vector_int.rbegin();
		ft::vector<int>::reverse_iterator ite = vector_int.rend();
		for (; it != ite; it++)
			*it = 0;
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	/* std::vector reverse iterator */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int(VEC_SIZE, 0);
		std::vector<int>::reverse_iterator it = std_vector_int.rbegin();
		std::vector<int>::reverse_iterator ite = std_vector_int.rend();
		for (; it != ite; it++)
			*it = 0;
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::vector - reverse iterator is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - reverse iterator is OK" << RESET << std::endl;

// vector capacity
	std::cout << YELLOW << BOLD << "------------- vector capacity -------------" << RESET << std::endl;
	/* ft::vector capacity */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int;
		for (int i = 0; i < VEC_SIZE; i++)
			vector_int.push_back(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	/* std::vector capacity */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int;
		for (int i = 0; i < VEC_SIZE; i++)
			std_vector_int.push_back(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::vector - capacity is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - capacity is OK" << RESET << std::endl;

// vector element access
	std::cout << YELLOW << BOLD << "------------- vector element access -------------" << RESET << std::endl;
	/* ft::vector element access */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int(VEC_SIZE, 0);
		for (int i = 0; i < VEC_SIZE; i++)
			vector_int[i] = i;
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	/* std::vector element access */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int(VEC_SIZE, 0);
		for (int i = 0; i < VEC_SIZE; i++)
			std_vector_int[i] = i;
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);

	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::vector - element access is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - element access is OK" << RESET << std::endl;

// vector modifiers
	std::cout << YELLOW << BOLD << "------------- vector modifiers -------------" << RESET << std::endl;
	/* ft::vector modifiers */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int;
		for (int i = 0; i < VEC_SIZE; i++)
			vector_int.push_back(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	/* std::vector modifiers */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int;
		for (int i = 0; i < VEC_SIZE; i++)
			std_vector_int.push_back(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::vector - modifiers is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - modifiers is OK" << RESET << std::endl;
}
