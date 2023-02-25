#ifndef MGO_MY_TESTER_
#define MGO_MY_TESTER_

#include <sys/time.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define RESET "\033[0m"
#define GRAY "\033[1;30m"
#define BOLD "\033[1m"

typedef long long ll;

#define SECONDS 1000000LL

#define VEC_SIZE 1000
#define STACK_SIZE 1000
#define MAP_SIZE 100
#define SET_SIZE 100

ll get_time(timeval start, timeval end);

void test_vector();
void test_stack();
void test_map();
void test_set();

#endif