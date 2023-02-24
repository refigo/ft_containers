#ifndef MGO_VECTOR_HPP_
#define MGO_VECTOR_HPP_

#include "algorithm.hpp"
#include "type_traits.hpp"
#include "iterator.hpp"
#include <algorithm>
#include <limits>
#include <memory>
#include <stdexcept>
#include <cstring>

namespace ft {

// vector

template <bool>
class __vector_base_common
{
protected:
  __vector_base_common() {}
  void __throw_length_error() const {
    throw std::length_error("vector");
  }
  void __throw_out_of_range() const {
    throw std::out_of_range("vector");
  }
};

template <class _Tp, class _Allocator>
class __vector_base
  : protected __vector_base_common<true>
{
protected:
  typedef _Tp                                      value_type; 
  typedef _Allocator                               allocator_type;
  typedef value_type&                              reference;
  typedef const value_type&                        const_reference;
  typedef typename allocator_type::size_type       size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::pointer         pointer;
  typedef typename allocator_type::const_pointer   const_pointer;
  typedef pointer                                  iterator;
  typedef const_pointer                            const_iterator;

  pointer             __begin_;
  pointer             __end_;
  pointer             __end_cap_;
  allocator_type      __alloc_;

  __vector_base(const allocator_type& __a = allocator_type())
    : __begin_(NULL)
    , __end_(NULL)
    , __end_cap_(NULL)
    , __alloc_(__a) {}
  
  ~__vector_base() {
    if (__begin_ != NULL) {
      this->clear();
      this->__alloc_.deallocate(__begin_, this->capacity());
    }
  }

  void clear() {
    __destruct_at_end(__begin_);
  }
  size_type capacity() const {
    return (static_cast<size_type>(this->__end_cap_ - this->__begin_));
  }

  void __destruct_at_end(const_pointer __new_last) {
    while (__new_last < __end_)
        this->__alloc_.destroy(const_cast<pointer>(--__end_));
  }

  void __copy_assign_alloc(const __vector_base& __c) {
    if (__alloc_ != __c.__alloc_) {
      clear();
      __alloc_.deallocate(__begin_, this->capacity());
      __begin_ = __end_ = __end_cap_ = NULL;
    }
    __alloc_ = __c.__alloc_;
  }

  static void __swap_alloc(allocator_type& __x, allocator_type& __y) {
    allocator_type  __tmp(__x);
    __x = __y;
    __y = __tmp;
  }
}; // class __vector_base

template <class _Tp, class _Allocator = std::allocator<_Tp> >
class vector
    : protected __vector_base<_Tp, _Allocator>
{
private:
    typedef __vector_base<_Tp, _Allocator>           __base;
public: 
    typedef vector                                   __self;
    typedef _Tp                                      value_type; 
    typedef _Allocator                               allocator_type;
    typedef typename __base::reference               reference;
    typedef typename __base::const_reference         const_reference;
    typedef typename __base::size_type               size_type;
    typedef typename __base::difference_type         difference_type;
    typedef typename __base::pointer                 pointer;
    typedef typename __base::const_pointer           const_pointer;
    typedef ft::__wrap_iter<pointer>                 iterator;
    typedef ft::__wrap_iter<const_pointer>           const_iterator;
    typedef ft::reverse_iterator<iterator>           reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

// (constructor)
  // default (1)
  explicit vector(const allocator_type& _a = allocator_type()) : __base(_a) {}
  // fill (2)
  explicit vector(size_type _n, const value_type& _x = value_type(), 
                  const allocator_type& _a = allocator_type())
      : __base(_a) {
    if (_n > 0) {
      __allocate(_n);
      __construct_at_end(_n, _x);
    }
  }
  // range (3)
  template <class _InputIterator>
    vector(_InputIterator __first, _InputIterator __last, 
           const allocator_type& __a = allocator_type(),
           typename enable_if<!is_integral<_InputIterator>::value>::type* = 0)
      : __base(__a) {
    for (; __first != __last; ++__first)
      push_back(*__first);
  }
  // copy (4)
  vector(const vector& __x, const allocator_type& __a = allocator_type())
      : __base(__a) {
    size_type __n = __x.size();
    if (__n > 0) {
      __allocate(__n);
      __construct_at_end(__x.__begin_, __x.__end_);
    }
  }

// (destructor)
  ~vector() {}

// operator=
  vector& operator=(const vector& __x) {
    if (this != &__x) {
      __base::__copy_assign_alloc(__x);
      assign(__x.__begin_, __x.__end_);
    }
    return *this;
  }

// Iterators:
  // begin()
  iterator               begin()          {return (__make_iter(this->__begin_));}
  const_iterator         begin()   const  {return (__make_iter(this->__begin_));}
  // end()
  iterator               end()            {return (__make_iter(this->__end_));}
  const_iterator         end()     const  {return (__make_iter(this->__end_));}
  // rbegin()
  reverse_iterator       rbegin()         {return       reverse_iterator(end());}
  const_reverse_iterator rbegin()  const  {return const_reverse_iterator(end());}
  // rend()
  reverse_iterator       rend()           {return       reverse_iterator(begin());}
  const_reverse_iterator rend()    const  {return const_reverse_iterator(begin());}

// Capacity:
  // size()
  size_type size() const {
    return (static_cast<size_type>(this->__end_ - this->__begin_));
  }
  // max_size()
  size_type max_size() const {
    return (std::min(this->__alloc_.max_size(), std::numeric_limits<size_type>::max() / 2));
  }
  // resize()
  void resize(size_type __sz, value_type __x = value_type()) {
    size_type __cs = size();
    if (__cs < __sz)
      __append(__sz - __cs, __x);
    else if (__cs > __sz)
      this->__destruct_at_end(this->__begin_ + __sz);
  }
  // capacity()
  size_type capacity() const {return (__base::capacity());}
  // empty()
  bool empty() const {return (this->__begin_ == this->__end_);}
  // reserve()
  void reserve(size_type __n) {
    if (__n > this->max_size())
      this->__throw_length_error();
    if (__n > this->capacity()) {
      pointer __tmp_begin = this->__alloc_.allocate(__n);
      std::uninitialized_copy(this->__begin_, this->__end_, __tmp_begin);
      pointer __tmp_end = __tmp_begin + size();
      this->__alloc_.deallocate(this->__begin_, this->capacity());
      this->__begin_ = __tmp_begin;
      this->__end_ = __tmp_end;
      this->__end_cap_ = this->__begin_ + __n;
    }
  }

// Element access:
  // operator[]
  reference       operator[](size_type __n) {return (this->__begin_[__n]);}
  const_reference operator[](size_type __n) const {return (this->__begin_[__n]);}
  // at()
  reference       at(size_type __n) {
    if (__n >= size())
      this->__throw_out_of_range();
    return (this->__begin_[__n]);
  }
  const_reference at(size_type __n) const {
    if (__n >= size())
      this->__throw_out_of_range();
    return (this->__begin_[__n]);
  }
  // front()
  reference       front()       {return *(this->__begin_);}
  const_reference front() const {return *(this->__begin_);}
  // back()
  reference       back()        {return *(this->__end_ - 1);}
  const_reference back()  const {return *(this->__end_ - 1);}

// Modifiers:
  // assign()
  template <class _InputIterator>
    typename enable_if
    <
      __is_input_iterator  <_InputIterator>::value,
      void
    >::type
  assign(_InputIterator __first, _InputIterator __last) {
    this->clear();
    for (; __first != __last; ++__first)
        this->push_back(*__first);
  }
  void assign(size_type __n, const_reference __u) {
    if (__n <= this->capacity()) {
      size_type __s = this->size();
      std::fill_n(this->__begin_, std::min(__n, __s), __u);
      if (__n > __s)
        __construct_at_end(__n - __s, __u);
      else
        this->__destruct_at_end(this->__begin_ + __n);
    }
    else {
      __deallocate();
      __allocate(__recommend(static_cast<size_type>(__n)));
      __construct_at_end(__n, __u);
    }
  }
  // push_back()
  void push_back(const_reference __x) {
    if (this->__end_ >= this->__end_cap_) {
      size_type size_recommended = __recommend(this->size() + 1);
      this->reserve(size_recommended);
    }
    this->__alloc_.construct(this->__end_, __x);
    ++(this->__end_);
  }
  // pop_back()
  void pop_back() {
      this->__destruct_at_end(this->__end_ - 1);
  }
  // insert()
     // single element (1)
  iterator insert(const_iterator __position, const_reference __x) {
    difference_type __off = __position - begin();
    if (this->__end_ >= this->__end_cap_)
      reserve(__recommend(size() + 1));
    pointer __p = this->__begin_ + __off;
    pointer __moving_from_end = this->__end_;
    for (; __moving_from_end != __p; --__moving_from_end) {
      this->__alloc_.construct(__moving_from_end, *(__moving_from_end - 1));
      this->__alloc_.destroy(__moving_from_end - 1);
    }
    this->__alloc_.construct(__p, __x);
    ++(this->__end_);
    return (__make_iter(__p));
  }
    // fill (2)
  void insert(const_iterator __position, size_type __n, const_reference __x) {
    difference_type __off = __position - begin();
    if (this->__end_ + __n >= this->__end_cap_)
      reserve(__recommend(size() + __n));
    pointer __p = this->__begin_ + __off;
    pointer __moving_from_new_end = this->__end_ + __n - 1;
    for (; __moving_from_new_end != __p + __n - 1; --__moving_from_new_end) {
      this->__alloc_.construct(__moving_from_new_end, *(__moving_from_new_end - __n));
      this->__alloc_.destroy(__moving_from_new_end - __n);
    }
    for (size_type i(0); i < __n; ++i)
      this->__alloc_.construct(__p + i, __x);
    this->__end_ += __n;
  }
    // range (3)
  template <class _InputIterator>
  void insert(const_iterator __position, _InputIterator __first, 
    typename enable_if
    <
      __is_input_iterator  <_InputIterator>::value,
      _InputIterator
    >::type __last) {
    difference_type __off = __position - begin();
    size_type __n(0);
    for (_InputIterator __tmp_first(__first)
      ; __tmp_first != __last
      ; ++__tmp_first)
      ++__n;
    if (this->__end_ + __n >= this->__end_)
      reserve(__recommend(size() + __n));
    pointer __p = this->__begin_ + __off;
    pointer __moving_from_new_end = this->__end_ + __n - 1;
    for (; __moving_from_new_end != __p + __n - 1; --__moving_from_new_end) {
      this->__alloc_.construct(__moving_from_new_end, *(__moving_from_new_end - __n));
      this->__alloc_.destroy(__moving_from_new_end - __n);
    }
    for (; __first != __last; ++__first, ++__p)
      this->__alloc_.construct(__p, *__first);
    this->__end_ += __n;
  }

  // erase()
  iterator erase(iterator __position) {
    pointer __p = const_cast<pointer>(&*__position);
    iterator __r = __make_iter(__p);
    this->__alloc_.destroy(__p);
    std::memmove(__p, __p + 1, sizeof(value_type) * (this->__end_ - __p - 1));
    --(this->__end_);
    return __r;
  }
  iterator erase(iterator __first, iterator __last) {
    pointer __p = this->__begin_ + (__first - begin());
    iterator __r = __make_iter(__p);
    size_type __n = __last - __first;
    for (size_type __i(0); __i < __n; ++__i, ++__p)
        this->__alloc_.destroy(__p);
    std::uninitialized_copy(__last, end(), __first);
    this->__end_ -= __n;
    return __r;
  }
  // swap()
  void swap(vector& __x) {
    pointer __tmp_begin(this->__begin_);
    this->__begin_ = __x.__begin_;
    __x.__begin_ = __tmp_begin;
    pointer __tmp_end(this->__end_);
    this->__end_ = __x.__end_;
    __x.__end_ = __tmp_end;
    pointer __tmp_end_cap(this->__end_cap_);
    this->__end_cap_ = __x.__end_cap_;
    __x.__end_cap_ = __tmp_end_cap;
    __base::__swap_alloc(this->__alloc_, __x.__alloc_);
  }
  // clear()
  void clear() {__base::clear();}

// Allocator:
  // get_allocator()
  allocator_type get_allocator() const {return (this->__alloc_);}

private:
  void __allocate(size_type __n) {
    if (__n > this->max_size())
      this->__throw_length_error();
    this->__begin_ = this->__end_ = this->__alloc_.allocate(__n);
    this->__end_cap_ = this->__begin_ + __n;
  }

  void __deallocate() {
    if (this->__begin_ != NULL) {
      this->clear();
      this->__alloc_.deallocate(this->__begin_, this->capacity());
      this->__begin_ = this->__end_ = this->__end_cap_ = NULL;
    }
  }

  size_type __recommend(size_type __new_size) const {
    const size_type __ms = this->max_size();
    if (__new_size > __ms)
      this->__throw_length_error();
    const size_type __cap = this->capacity();
    if (__cap >= __ms / 2)
      return __ms;
    return (std::max(2*__cap, __new_size));
  }

  // __construct_at_end()
  void __construct_at_end(size_type __n) {
    do
    {
      this->__alloc_.construct(this->__end_);
      ++(this->__end_);
      --__n;
    } while (__n > 0);
  }
  void __construct_at_end(size_type __n, const_reference __x) {
    do
    {
      this->__alloc_.construct(this->__end_, __x);
      ++(this->__end_);
      --__n;
    } while (__n > 0);
  }
  template <class _ForwardIterator>
    typename enable_if
    <
      __is_forward_iterator<_ForwardIterator>::value,
      void
    >::type
  __construct_at_end(_ForwardIterator __first, _ForwardIterator __last) {
    for (; __first != __last; ++__first) {
      this->__alloc_.construct(this->__end_, *__first);
      ++this->__end_;
    }
  }

  void __append(size_type __n, const_reference __x) {
    if (static_cast<size_type>(this->__end_cap_ - this->__end_) >= __n) {
      __construct_at_end(__n, __x);
    }
    else {
      this->reserve(__recommend(this->size() + __n));
      __construct_at_end(__n, __x);
    }
  }

  // __make_iter()
  iterator       __make_iter(pointer __p)                 {return iterator(__p);}
  const_iterator __make_iter(const_pointer __p) const     {return const_iterator(__p);}

}; // class vector

// Non-member function overloads
  // relational operators()
template <class _Tp, class _Allocator>
inline
bool
operator==(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y) {
    const typename vector<_Tp, _Allocator>::size_type __sz = __x.size();
    return __sz == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Tp, class _Allocator>
inline
bool
operator!=(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y) {
    return !(__x == __y);
}

template <class _Tp, class _Allocator>
inline
bool
operator< (const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y) {
    return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class _Tp, class _Allocator>
inline
bool
operator> (const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y) {
    return __y < __x;
}

template <class _Tp, class _Allocator>
inline
bool
operator>=(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y) {
    return !(__x < __y);
}

template <class _Tp, class _Allocator>
inline
bool
operator<=(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y) {
    return !(__y < __x);
}

  // swap()
template <class _Tp, class _Allocator>
inline
void
swap(vector<_Tp, _Allocator>& __x, vector<_Tp, _Allocator>& __y) {
    __x.swap(__y);
}

} // namespace ft

#endif /* MGO_VECTOR_HPP_ */