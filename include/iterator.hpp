#ifndef MGO_ITERATOR_
#define MGO_ITERATOR_

#include "type_traits.hpp"

namespace ft {

// reference from stddef.h
#define __MGO_PTRDIFF_TYPE__ long int
typedef __MGO_PTRDIFF_TYPE__ mgo_ptrdiff_t;

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class _Tp>
struct __has_iterator_category
{
private:
    struct __two {char _; char __;};
    template <class _Up> static __two __test(...);
    template <class _Up> static char __test(typename _Up::iterator_category* = 0);
public:
    static const bool value = sizeof(__test<_Tp>(0)) == 1;
};

template <class _Iter, bool> struct ____iterator_traits {};

template <class _Iter>
struct ____iterator_traits<_Iter, true>
{
    typedef typename _Iter::difference_type   difference_type;
    typedef typename _Iter::value_type        value_type;
    typedef typename _Iter::pointer           pointer;
    typedef typename _Iter::reference         reference;
    typedef typename _Iter::iterator_category iterator_category;
};

template <class _Iter, bool> struct __iterator_traits {};

template <class _Iter>
struct __iterator_traits<_Iter, true>
    :  ____iterator_traits
      <
        _Iter,
        is_iterator_category_convertible<typename _Iter::iterator_category, input_iterator_tag>::value ||
        is_iterator_category_convertible<typename _Iter::iterator_category, output_iterator_tag>::value
      >
{};

// iterator_traits<Iterator> will only have the nested types if Iterator::iterator_category
//    exists.  Else iterator_traits<Iterator> will be an empty class.  This is a
//    conforming extension which allows some programs to compile and behave as
//    the client expects instead of failing at compile time.

template <class _Iter>
struct iterator_traits
    : __iterator_traits<_Iter, __has_iterator_category<_Iter>::value> {};

template<class _Tp>
struct iterator_traits<_Tp*>
{
    typedef mgo_ptrdiff_t difference_type;
    typedef typename remove_const<_Tp>::type value_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
    typedef random_access_iterator_tag iterator_category;
};

template <class FromIterCat, class ToIterCat>
struct __is_iterator_category_convertible                                                           : public false_type {};

template <class SameIterCat>
struct __is_iterator_category_convertible<SameIterCat, SameIterCat>                                 : public true_type {};

struct __is_iterator_category_convertible<forward_iterator_tag, input_iterator_tag>                 : public true_type {};

struct __is_iterator_category_convertible<bidirectional_iterator_tag, input_iterator_tag>           : public true_type {};
struct __is_iterator_category_convertible<bidirectional_iterator_tag, forward_iterator_tag>         : public true_type {};

struct __is_iterator_category_convertible<random_access_iterator_tag, input_iterator_tag>           : public true_type {};
struct __is_iterator_category_convertible<random_access_iterator_tag, forward_iterator_tag>         : public true_type {};
struct __is_iterator_category_convertible<random_access_iterator_tag, bidirectional_iterator_tag>   : public true_type {};

template <class From, class To>
struct is_iterator_category_convertible: public __is_iterator_category_convertible<From, To> {};

template <class _Tp, class _Up, bool = __has_iterator_category<iterator_traits<_Tp> >::value> // TODO: bool에서 iterator인지 체크하는건 알겠음. 근데 이게 false이면 SFINAE에 걸리나?
struct __has_iterator_category_convertible_to
    : public integral_constant<bool, is_iterator_category_convertible<typename iterator_traits<_Tp>::iterator_category, _Up>::value>
{};

template <class _Tp, class _Up>
struct __has_iterator_category_convertible_to<_Tp, _Up, false> : public false_type {};

template <class _Tp>
struct __is_input_iterator : public __has_iterator_category_convertible_to<_Tp, input_iterator_tag> {};

template <class _Tp>
struct __is_forward_iterator : public __has_iterator_category_convertible_to<_Tp, forward_iterator_tag> {};

template <class _Tp>
struct __is_bidirectional_iterator : public __has_iterator_category_convertible_to<_Tp, bidirectional_iterator_tag> {};

template <class _Tp>
struct __is_random_access_iterator : public __has_iterator_category_convertible_to<_Tp, random_access_iterator_tag> {};

template<class _Category, class _Tp, class _Distance = mgo_ptrdiff_t,
         class _Pointer = _Tp*, class _Reference = _Tp&>
struct iterator
{
    typedef _Tp        value_type;
    typedef _Distance  difference_type;
    typedef _Pointer   pointer;
    typedef _Reference reference;
    typedef _Category  iterator_category;
};

};

#endif /* MGO_ITERATOR_ */
