#ifndef MGO_ITERATOR_
#define MGO_ITERATOR_

#include "type_traits.hpp"
#include <iterator>
#include <stddef.h>

namespace ft {

// iterator tag
typedef std::input_iterator_tag         input_iterator_tag;
typedef std::output_iterator_tag        output_iterator_tag;
typedef std::forward_iterator_tag       forward_iterator_tag;
typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
typedef std::random_access_iterator_tag random_access_iterator_tag;

// is_iterator_category_convertible
template <class FromIterCat, class ToIterCat>
struct __is_iterator_category_convertible                                                           : public false_type {};

template <class SameIterCat>
struct __is_iterator_category_convertible<SameIterCat, SameIterCat>                                 : public true_type {};

template <>
struct __is_iterator_category_convertible<forward_iterator_tag, input_iterator_tag>                 : public true_type {};

template <>
struct __is_iterator_category_convertible<bidirectional_iterator_tag, input_iterator_tag>           : public true_type {};
template <>
struct __is_iterator_category_convertible<bidirectional_iterator_tag, forward_iterator_tag>         : public true_type {};

template <>
struct __is_iterator_category_convertible<random_access_iterator_tag, input_iterator_tag>           : public true_type {};
template <>
struct __is_iterator_category_convertible<random_access_iterator_tag, forward_iterator_tag>         : public true_type {};
template <>
struct __is_iterator_category_convertible<random_access_iterator_tag, bidirectional_iterator_tag>   : public true_type {};

template <class From, class To>
struct is_iterator_category_convertible: public __is_iterator_category_convertible<From, To> {};

// has_iterator_category
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

// iterator_traits
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
    typedef ptrdiff_t difference_type;
    typedef typename remove_const<_Tp>::type value_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
    typedef random_access_iterator_tag iterator_category;
};

// For checking iterator tag
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

// iterator
template<class _Category, class _Tp, class _Distance = ptrdiff_t,
         class _Pointer = _Tp*, class _Reference = _Tp&>
struct iterator
{
    typedef _Tp        value_type;
    typedef _Distance  difference_type;
    typedef _Pointer   pointer;
    typedef _Reference reference;
    typedef _Category  iterator_category;
};


// reverse_iterator

template <class _Iter>
class reverse_iterator
    : public iterator<typename iterator_traits<_Iter>::iterator_category,
                      typename iterator_traits<_Iter>::value_type,
                      typename iterator_traits<_Iter>::difference_type,
                      typename iterator_traits<_Iter>::pointer,
                      typename iterator_traits<_Iter>::reference>
{
private:
    mutable _Iter __t; // TODO: consider...
protected:
    _Iter current;
public:
    typedef _Iter                                            iterator_type;
    typedef typename iterator_traits<_Iter>::difference_type difference_type;
    typedef typename iterator_traits<_Iter>::reference       reference;
    typedef typename iterator_traits<_Iter>::pointer         pointer;
    
    reverse_iterator() : current() {}
    explicit reverse_iterator(_Iter __x) : __t(__x), current(__x) {}
    template <class _Up> reverse_iterator(const reverse_iterator<_Up>& __u)
        : __t(__u.base()), current(__u.base()) {}
    _Iter base() const {return current;}
    reference operator*() const {__t = current; return *--__t;} // TODO: consider that __t is mutable.
    pointer  operator->() const {return &(operator*());}
    reverse_iterator& operator++() {--current; return *this;}
    reverse_iterator  operator++(int)
        {reverse_iterator __tmp(*this); --current; return __tmp;}
    reverse_iterator& operator--() {++current; return *this;}
    reverse_iterator  operator--(int)
        {reverse_iterator __tmp(*this); ++current; return __tmp;}
    reverse_iterator  operator+ (difference_type __n) const
        {return reverse_iterator(current - __n);}
    reverse_iterator& operator+=(difference_type __n)
        {current -= __n; return *this;}
    reverse_iterator  operator- (difference_type __n) const
        {return reverse_iterator(current + __n);}
    reverse_iterator& operator-=(difference_type __n)
        {current += __n; return *this;}
    reference         operator[](difference_type __n) const
        {return current[-__n-1];}
};

template <class _Iter1, class _Iter2>
bool
operator==(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
bool
operator<(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() > __y.base();
}

template <class _Iter1, class _Iter2>
bool
operator!=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() != __y.base();
}

template <class _Iter1, class _Iter2>
bool
operator>(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
bool
operator>=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() <= __y.base();
}

template <class _Iter1, class _Iter2>
bool
operator<=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() >= __y.base();
}

template <class _Iter1, class _Iter2>
typename reverse_iterator<_Iter1>::difference_type
operator-(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __y.base() - __x.base();
}

template <class _Iter>
reverse_iterator<_Iter>
operator+(typename reverse_iterator<_Iter>::difference_type __n, const reverse_iterator<_Iter>& __x)
{
    return reverse_iterator<_Iter>(__x.base() - __n);
}


// __wrap_iter

// template <class _Iter> class __wrap_iter;

// template <class _Iter1, class _Iter2>
// bool
// operator==(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&);

// template <class _Iter1, class _Iter2>
// bool
// operator<(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&);

// template <class _Iter1, class _Iter2>
// bool
// operator!=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&);

// template <class _Iter1, class _Iter2>
// bool
// operator>(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&);

// template <class _Iter1, class _Iter2>
// bool
// operator>=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&);

// template <class _Iter1, class _Iter2>
// bool
// operator<=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&);

// template <class _Iter1, class _Iter2>
// typename __wrap_iter<_Iter1>::difference_type
// operator-(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&);

// template <class _Iter>
// __wrap_iter<_Iter>
// operator+(typename __wrap_iter<_Iter>::difference_type, const __wrap_iter<_Iter>&);

// template <class _I, class _O> _O copy(_I, _I, _O);
// template <class _B1, class _B2> _B2 copy_backward(_B1, _B1, _B2);
// template <class _I, class _O> _O move(_I, _I, _O);
// template <class _B1, class _B2> _B2 move_backward(_B1, _B1, _B2);

// template <class _Tp>
// typename enable_if
// <
//     has_trivial_copy_assign<_Tp>::value,
//     _Tp*
// >::type
// __unwrap_iter(__wrap_iter<_Tp*>);

template <class _Iter>
class __wrap_iter
{
public:
    typedef _Iter                                                      iterator_type;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
    typedef typename iterator_traits<iterator_type>::value_type        value_type;
    typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
    typedef typename iterator_traits<iterator_type>::pointer           pointer;
    typedef typename iterator_traits<iterator_type>::reference         reference;
private:
    iterator_type __i;
public:
    __wrap_iter(iterator_type __x) : __i(__x) {}
    __wrap_iter() {}
    template <class _Up> __wrap_iter(const __wrap_iter<_Up>& __u,
        //typename enable_if<__has_iterator_category_convertible_to<_Up, iterator_category>::value>::type* = 0
        typename enable_if<__is_random_access_iterator<_Up>::value>::type* = 0)
        : __i(__u.base()) {}
    reference operator*() const {return *__i;}
    pointer  operator->() const {return &(operator*());}
    __wrap_iter& operator++() {++__i; return *this;}
    __wrap_iter  operator++(int)
        {__wrap_iter __tmp(*this); ++__i; return __tmp;}
    __wrap_iter& operator--() {--__i; return *this;}
    __wrap_iter  operator--(int)
        {__wrap_iter __tmp(*this); --__i; return __tmp;}
    __wrap_iter  operator+ (difference_type __n) const
        {return __wrap_iter(__i + __n);}
    __wrap_iter& operator+=(difference_type __n)
        {__i += __n; return *this;}
    __wrap_iter  operator- (difference_type __n) const
        {return __wrap_iter(__i - __n);}
    __wrap_iter& operator-=(difference_type __n)
        {__i -= __n; return *this;}
    reference        operator[](difference_type __n) const
        {return __i[__n];}

    iterator_type base() const {return __i;}

private:
    // __wrap_iter(iterator_type __x) : __i(__x) {}

    // template <class _Up> friend class __wrap_iter;
    // template <class _CharT, class _Traits, class _Alloc> friend class basic_string;
    // template <class _Tp, class _Alloc> friend class vector;

    // template <class _Iter1, class _Iter2>
    // friend
    // bool
    // operator==(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&);
    
    // template <class _Iter1, class _Iter2>
    // friend
    // bool
    // operator<(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&);
    
    // template <class _Iter1, class _Iter2>
    // friend
    // bool
    // operator!=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&);
    
    // template <class _Iter1, class _Iter2>
    // friend
    // bool
    // operator>(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&);
    
    // template <class _Iter1, class _Iter2>
    // friend
    // bool
    // operator>=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&);
    
    // template <class _Iter1, class _Iter2>
    // friend
    // bool
    // operator<=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&);
    
    // template <class _Iter1, class _Iter2>
    // friend
    // typename __wrap_iter<_Iter1>::difference_type
    // operator-(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&);
    
    // template <class _Iter1>
    // friend
    // __wrap_iter<_Iter1>
    // operator+(typename __wrap_iter<_Iter1>::difference_type, const __wrap_iter<_Iter1>&);

    // template <class _I, class _O> friend _O copy(_I, _I, _O);
    // template <class _B1, class _B2> friend _B2 copy_backward(_B1, _B1, _B2);
    // template <class _I, class _O> friend _O move(_I, _I, _O);
    // template <class _B1, class _B2> friend _B2 move_backward(_B1, _B1, _B2);

    // template <class _Tp>
    // friend
    // typename enable_if
    // <
    //     has_trivial_copy_assign<_Tp>::value,
    //     _Tp*
    // >::type
    // __unwrap_iter(__wrap_iter<_Tp*>);
};

template <class _Iter1, class _Iter2>
bool
operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
{
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
bool
operator<(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
{
    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
bool
operator!=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
{
    return __x.base() != __y.base();
}

template <class _Iter1, class _Iter2>
bool
operator>(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
{
    return __x.base() > __y.base();
}

template <class _Iter1, class _Iter2>
bool
operator>=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
{
    return __x.base() >= __y.base();
}

template <class _Iter1, class _Iter2>
bool
operator<=(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
{
    return __x.base() <= __y.base();
}

template <class _Iter1, class _Iter2>
typename __wrap_iter<_Iter1>::difference_type
operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
{
    return __x.base() - __y.base();
}

template <class _Iter>
__wrap_iter<_Iter>
operator+(typename __wrap_iter<_Iter>::difference_type __n,
          const __wrap_iter<_Iter>& __x)
{
    return __wrap_iter<_Iter>(__x.base() + __n);
}

} // namespace ft

#endif /* MGO_ITERATOR_ */
