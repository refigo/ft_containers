#ifndef __MGO__FUNCTIONAL_BASE_
#define __MGO__FUNCTIONAL_BASE_

namespace ft {

template <class _Arg1, class _Arg2, class _Result>
struct binary_function
{
	typedef _Arg1	first_argument_type;
	typedef _Arg2	second_argument_type;
	typedef _Result	result_type;
};

} // namespace ft

#endif /* __MGO__FUNCTIONAL_BASE_ */