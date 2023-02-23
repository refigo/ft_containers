#ifndef MGO_UTILS_HPP_
#define MGO_UTILS_HPP_

namespace ft
{

// unary_function

template <class Arg, class Result>
struct unary_function {
    typedef Arg argument_type;
    typedef Result result_type;
};

// binary_function

template <class Arg1, class Arg2, class Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

// identity

template <class T>
struct identity : public unary_function<T, T> {
  const T& operator()(const T& x) const { return x; }
};

// select1st

template <class Pair>
struct select1st : public unary_function<Pair, typename Pair::first_type> {
  const typename Pair::first_type& operator()(const Pair& x) const
  {
    return x.first;
  }
};

// select2nd

template <class Pair>
struct select2nd : public unary_function<Pair, typename Pair::second_type> {
  const typename Pair::second_type& operator()(const Pair& x) const
  {
    return x.second;
  }
};

// less

template <class _Tp>
struct less : binary_function<_Tp, _Tp, bool>
{
	bool operator()(const _Tp& __x, const _Tp& __y) const
		{return __x < __y;}
};

// swap

// template <class _Tp>
// inline void swap(_Tp& _a, _Tp& _b) {
//   _Tp tmp = _a;
//   _a = _b;
//   _b = tmp;
// }

} // namespace ft


#endif /* __MGO_UTILS_HPP_ */