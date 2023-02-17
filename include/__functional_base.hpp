#ifndef __MGO__FUNCTIONAL_BASE_HPP_
#define __MGO__FUNCTIONAL_BASE_HPP_

namespace ft {

// binary_function

template <class _Arg1, class _Arg2, class _Result>
struct binary_function
{
	typedef _Arg1	first_argument_type;
	typedef _Arg2	second_argument_type;
	typedef _Result	result_type;
};

// less

template <class _Tp>
struct less : binary_function<_Tp, _Tp, bool>
{
	bool operator()(const _Tp& __x, const _Tp& __y) const
		{return __x < __y;}
};

} // namespace ft

#endif /* __MGO__FUNCTIONAL_BASE_HPP_ */