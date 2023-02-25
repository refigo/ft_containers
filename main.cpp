#include "my_tester.hpp"

int main(void)
{
	test_vector();
	test_stack();
	test_map();
	test_set();

	std::cout << CYAN << BOLD << "\n\n------------- LEAKS -------------\n\n" << RESET << std::endl;
	std::cout << "check leaks in another shell" << std::endl;
	while(1){}

	std::cout << GREEN << BOLD << "------------- TEST is OK -------------" << RESET << std::endl;
	return (0);
}
