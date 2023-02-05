#ifndef MGO_TYPE_TRAITS_
#define MGO_TYPE_TRAITS_

//#define MGO_BEGIN_NAMESPACE_FT_ namespace ft { inline namespace _LIBCPP_ABI_NAMESPACE {
//MGO_BEGIN_NAMESPACE_FT_

namespace ft {

// enable_if

template <bool, class Tp_ = void>
struct enable_if {};

template <class Tp_>
struct enable_if<true, Tp_> {
    typedef Tp_ type;
};

// helper class: integral_constant

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

template <class _Tp> struct __is_integral                     : public false_type {};
template <>          struct __is_integral<bool>               : public true_type {};
template <>          struct __is_integral<char>               : public true_type {};
template <>          struct __is_integral<signed char>        : public true_type {};
template <>          struct __is_integral<unsigned char>      : public true_type {};
template <>          struct __is_integral<wchar_t>            : public true_type {};
#ifndef _LIBCPP_HAS_NO_UNICODE_CHARS // TODO: search
template <>          struct __is_integral<char16_t>           : public true_type {};
template <>          struct __is_integral<char32_t>           : public true_type {};
#endif
template <>          struct __is_integral<short>              : public true_type {};
template <>          struct __is_integral<unsigned short>     : public true_type {};
template <>          struct __is_integral<int>                : public true_type {};
template <>          struct __is_integral<unsigned int>       : public true_type {};
template <>          struct __is_integral<long>               : public true_type {};
template <>          struct __is_integral<unsigned long>      : public true_type {};
template <>          struct __is_integral<long long>          : public true_type {};
template <>          struct __is_integral<unsigned long long> : public true_type {};

template <class _Tp> struct is_integral : public __is_integral<typename remove_cv<_Tp>::type> {};

};

#endif