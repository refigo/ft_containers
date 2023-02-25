#include "my_tester.hpp"
#include "stack.hpp"
#include <stack>

void test_stack() {
	timeval ft_start;
	timeval ft_end;
	timeval std_start;
	timeval std_end;
	ll ft_time;
	ll std_time;

	// STACK TEST

	std::cout << CYAN << BOLD << "\n\n------------- stack -------------\n\n" << RESET << std::endl;

// stack push
	std::cout << YELLOW << BOLD << "------------- stack push -------------" << RESET << std::endl;
	gettimeofday(&ft_start, NULL);
	{
		ft::stack<int> stack_int;
		for (int i = 0; i < STACK_SIZE; i++)
			stack_int.push(i);
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::stack<int> std_stack_int;
		for (int i = 0; i < STACK_SIZE; i++)
			std_stack_int.push(i);
	}
	gettimeofday(&std_end, NULL);
	std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::stack - push is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::stack - push is OK" << RESET << std::endl;

// stack pop
	std::cout << YELLOW << BOLD << "------------- stack pop -------------" << RESET << std::endl;

	gettimeofday(&ft_start, NULL);
	{
		ft::stack<int> stack_int;
		for (int i = 0; i < STACK_SIZE; i++)
			stack_int.push(i);
		for (int i = 0; i < STACK_SIZE; i++)
			stack_int.pop();
	}

	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);
	gettimeofday(&std_start, NULL);
	{
		std::stack<int> std_stack_int;
		for (int i = 0; i < STACK_SIZE; i++)
			std_stack_int.push(i);
		for (int i = 0; i < STACK_SIZE; i++)
			std_stack_int.pop();
	}
	gettimeofday(&std_end, NULL);
    std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::stack - pop is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::stack - pop is OK" << RESET << std::endl;

// stack top
	std::cout << YELLOW << BOLD << "------------- stack top -------------" << RESET << std::endl;

	gettimeofday(&ft_start, NULL);
	{
		ft::stack<int> stack_int;
		for (int i = 0; i < STACK_SIZE; i++)
			stack_int.push(i);
		for (int i = 0; i < STACK_SIZE; i++)
			stack_int.top();
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);
	gettimeofday(&std_start, NULL);
	{
		std::stack<int> std_stack_int;
		for (int i = 0; i < STACK_SIZE; i++)
			std_stack_int.push(i);
		for (int i = 0; i < STACK_SIZE; i++)
			std_stack_int.top();
	}
	gettimeofday(&std_end, NULL);
    std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::stack - top is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::stack - top is OK" << RESET << std::endl;

// stack empty
	std::cout << YELLOW << BOLD << "------------- stack empty -------------" << RESET << std::endl;

	gettimeofday(&ft_start, NULL);
	{
		ft::stack<int> stack_int;
		for (int i = 0; i < STACK_SIZE; i++)
			stack_int.push(i);
		for (int i = 0; i < STACK_SIZE; i++)
			stack_int.pop();
		if (!stack_int.empty())
			std::cout << RED << BOLD << "ft::stack - empty is not OK" << RESET << std::endl;
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::stack<int> std_stack_int;
		for (int i = 0; i < STACK_SIZE; i++)
			std_stack_int.push(i);
		for (int i = 0; i < STACK_SIZE; i++)
			std_stack_int.pop();
		if (!std_stack_int.empty())
			std::cout << RED << BOLD << "std::stack - empty is not OK" << RESET << std::endl;
	}
	gettimeofday(&std_end, NULL);
    std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;

	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::stack - empty is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::stack - empty is OK" << RESET << std::endl;

// stack relational operators
	std::cout << YELLOW << BOLD << "------------- stack relational operators -------------" << RESET << std::endl;

	gettimeofday(&ft_start, NULL);
	{
		ft::stack<int> stack_int;
		ft::stack<int> stack_int2;
		for (int i = 0; i < STACK_SIZE; i++)
			stack_int.push(i);
		for (int i = 0; i < STACK_SIZE; i++)
			stack_int2.push(i);
		if (stack_int != stack_int2)
			std::cout << RED << BOLD << "ft::stack - relational operators is not OK" << RESET << std::endl;
	}
	gettimeofday(&ft_end, NULL);
	ft_time = get_time(ft_start, ft_end);

	gettimeofday(&std_start, NULL);
	{
		std::stack<int> std_stack_int;
		std::stack<int> std_stack_int2;
		for (int i = 0; i < STACK_SIZE; i++)
			std_stack_int.push(i);
		for (int i = 0; i < STACK_SIZE; i++)
			std_stack_int2.push(i);
		if (std_stack_int != std_stack_int2)
			std::cout << RED << BOLD << "std::stack - relational operators is not OK" << RESET << std::endl;
	}
	gettimeofday(&std_end, NULL);
    std_time = get_time(std_start, std_end);
	std::cout << BLUE << BOLD << "ft  :\t" << ft_time << " us" << RESET << std::endl;
	std::cout << MAGENTA << BOLD << "std :\t" << std_time << " us" << RESET << std::endl;
	if (std_time && ft_time > 20 * std_time)
	{
		std::cout << RED << BOLD << "ft::stack - relational operators is " << (double)ft_time / std_time << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::stack - relational operators is OK" << RESET << std::endl;
}