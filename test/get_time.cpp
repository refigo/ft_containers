#include "my_tester.hpp"

ll get_time(timeval start, timeval end) {
	return ((end.tv_sec - start.tv_sec) * SECONDS + (end.tv_usec - start.tv_usec));
}
