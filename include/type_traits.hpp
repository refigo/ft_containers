#ifndef MGO_TYPE_TRAITS_
#define MGO_TYPE_TRAITS_

#include <cwchar>
#include <type_traits>

namespace ft {

// enable_if

template <bool, class Tp_ = void>
struct enable_if {};

template <class Tp_>
struct enable_if<true, Tp_> {
    typedef Tp_ type;
};

// integral_constant

template <class _Tp, _Tp __v>
struct integral_constant
{
    static const _Tp          value = __v;
    typedef _Tp               value_type;
    typedef integral_constant type;
};

template <class _Tp, _Tp __v>
const _Tp integral_constant<_Tp, __v>::value;

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

// remove_const

template <class _Tp> struct remove_const            {typedef _Tp type;};
template <class _Tp> struct remove_const<const _Tp> {typedef _Tp type;};

// remove_volatile

template <class _Tp> struct remove_volatile               {typedef _Tp type;};
template <class _Tp> struct remove_volatile<volatile _Tp> {typedef _Tp type;};

// remove_cv

template <class _Tp> struct remove_cv
{typedef typename remove_volatile<typename remove_const<_Tp>::type>::type type;};

// is_integral

template <class _Tp> struct __is_integral_                     : public false_type {};
template <>          struct __is_integral_<bool>               : public true_type {};
template <>          struct __is_integral_<char>               : public true_type {};
template <>          struct __is_integral_<signed char>        : public true_type {};
template <>          struct __is_integral_<unsigned char>      : public true_type {};
template <>          struct __is_integral_<wchar_t>            : public true_type {};
template <>          struct __is_integral_<char16_t>           : public true_type {};
template <>          struct __is_integral_<char32_t>           : public true_type {};
template <>          struct __is_integral_<short>              : public true_type {};
template <>          struct __is_integral_<unsigned short>     : public true_type {};
template <>          struct __is_integral_<int>                : public true_type {};
template <>          struct __is_integral_<unsigned int>       : public true_type {};
template <>          struct __is_integral_<long>               : public true_type {};
template <>          struct __is_integral_<unsigned long>      : public true_type {};
template <>          struct __is_integral_<long long>          : public true_type {};
template <>          struct __is_integral_<unsigned long long> : public true_type {};

template <class _Tp> struct is_integral : public __is_integral_<typename remove_cv<_Tp>::type> {};

template <typename _Tp>
bool
operator==(ft::is_integral<_Tp> _lhs, std::is_integral<_Tp> _rhs) {return _lhs.value == _rhs.value;}

template <typename _Tp>
bool
operator==(std::is_integral<_Tp> _lhs, ft::is_integral<_Tp> _rhs) {return _lhs.value == _rhs.value;}

// add_lvalue_reference

template <class _Tp> struct add_lvalue_reference                      {typedef _Tp& type;};
template <class _Tp> struct add_lvalue_reference<_Tp&>                {typedef _Tp& type;};  // for older compiler
template <>          struct add_lvalue_reference<void>                {typedef void type;};
template <>          struct add_lvalue_reference<const void>          {typedef const void type;};
template <>          struct add_lvalue_reference<volatile void>       {typedef volatile void type;};
template <>          struct add_lvalue_reference<const volatile void> {typedef const volatile void type;};

} // namespace ft

#endif /* MGO_TYPE_TRAITS_ */
