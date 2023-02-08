#ifndef MGO_TYPE_TRAITS_
#define MGO_TYPE_TRAITS_

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

template <class _Tp> struct __is_integral_mgo                     : public false_type {};
template <>          struct __is_integral_mgo<bool>               : public true_type {};
template <>          struct __is_integral_mgo<char>               : public true_type {};
template <>          struct __is_integral_mgo<signed char>        : public true_type {};
template <>          struct __is_integral_mgo<unsigned char>      : public true_type {};
template <>          struct __is_integral_mgo<wchar_t>            : public true_type {};
// #ifndef _LIBCPP_HAS_NO_UNICODE_CHARS // TODO: search
template <>          struct __is_integral_mgo<char16_t>           : public true_type {};
template <>          struct __is_integral_mgo<char32_t>           : public true_type {};
// #endif
template <>          struct __is_integral_mgo<short>              : public true_type {};
template <>          struct __is_integral_mgo<unsigned short>     : public true_type {};
template <>          struct __is_integral_mgo<int>                : public true_type {};
template <>          struct __is_integral_mgo<unsigned int>       : public true_type {};
template <>          struct __is_integral_mgo<long>               : public true_type {};
template <>          struct __is_integral_mgo<unsigned long>      : public true_type {};
template <>          struct __is_integral_mgo<long long>          : public true_type {};
template <>          struct __is_integral_mgo<unsigned long long> : public true_type {};

template <class _Tp> struct is_integral : public __is_integral_mgo<typename remove_cv<_Tp>::type> {};

};

#endif /* MGO_TYPE_TRAITS_ */
