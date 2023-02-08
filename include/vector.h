#ifndef MGO_VECTOR_H_
#define MGO_VECTOR_H_

#include <memory>
#include "type_traits.hpp"

namespace ft {

template <class _Tp, class _Allocator>
class __vector_base
{
protected:
    typedef _Tp                                      value_type; 
    typedef _Allocator                               allocator_type;
    // typedef allocator_traits<allocator_type>         __alloc_traits;
    typedef value_type&                              reference;
    typedef const value_type&                        const_reference;
    // typedef typename __alloc_traits::size_type       size_type;
    // typedef typename __alloc_traits::difference_type difference_type;
    // typedef typename __alloc_traits::pointer         pointer;
    // typedef typename __alloc_traits::const_pointer   const_pointer;
	typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef pointer                                  iterator;
    typedef const_pointer                            const_iterator;

    pointer                                         __begin_;
    pointer                                         __end_;
	pointer											__end_cap_;
	allocator_type									__alloc_;

	// __vector_base()
	// 	: __begin_(0),
	// 	__end_(0),
	// 	__end_cap_(0),
	// 	__alloc_(allocator_type()) {}
    __vector_base(const allocator_type& __a)
		: __begin_(0),
		__end_(0),
		__end_cap_(0),
		__alloc_(__a) {}
    ~__vector_base()
	{
		if (__begin_ != 0)
		{
			// clear();
			// __alloc_traits::deallocate(__alloc(), __begin_, capacity());
		}
	}

	//clear()
	//capacity()
};

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
    // typedef typename __base::__alloc_traits          __alloc_traits;
    typedef typename __base::reference               reference;
    typedef typename __base::const_reference         const_reference;
    typedef typename __base::size_type               size_type;
    typedef typename __base::difference_type         difference_type;
    typedef typename __base::pointer                 pointer;
    typedef typename __base::const_pointer           const_pointer;

    // typedef ft::__wrap_iter<pointer>                     iterator;
    // typedef ft::__wrap_iter<const_pointer>               const_iterator;
    // typedef ft::reverse_iterator<iterator>         reverse_iterator;
    // typedef ft::reverse_iterator<const_iterator>   const_reverse_iterator;

	/*	(1) empty container constructor (default constructor)
		Constructs an empty container, with no elements. */
	// vector() {}
	explicit vector(const allocator_type& __a = allocator_type()) : __base(__a) {}

	/*	(2) fill constructor
		Constructs a container with n elements. Each element is a copy of val. */
	// explicit vector(size_type __n)
	// {
	// 	if (__n > 0)
	// 	{
	// 		allocate(__n);
	// 		__construct_at_end(__n);
	// 	}
	// }
    // vector(size_type __n, const_reference __x)
	// {
	// 	if (__n > 0)
	// 	{
	// 		allocate(__n);
	// 		__construct_at_end(__n, __x);
	// 	}
	// }
    // vector(size_type __n, const_reference __x, const allocator_type& __a)
	//     : __base(__a)
	// {
	// 	if (__n > 0)
	// 	{
	// 		allocate(__n);
	// 		__construct_at_end(__n, __x);
	// 	}
	// }

	/*	(3) range constructor
		Constructs a container with as many elements as the range [first,last), 
		with each element constructed from its corresponding element in that range, 
		in the same order. */
	// template <class _InputIterator>
    //     vector(_InputIterator __first, _InputIterator __last,
    //            typename enable_if<__is_input_iterator  <_InputIterator>::value &&
    //                              !__is_forward_iterator<_InputIterator>::value>::type* = 0)
	// {
    // 	for (; __first != __last; ++__first)
    //     	push_back(*__first);
	// }
    // template <class _InputIterator>
    //     vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a,
    //            typename enable_if<__is_input_iterator  <_InputIterator>::value &&
    //                              !__is_forward_iterator<_InputIterator>::value>::type* = 0)
	//     : __base(__a)
	// {
	// 	for (; __first != __last; ++__first)
	// 		push_back(*__first);
	// }

	/*	(4) copy constructor
		Constructs a container with a copy of each of the elements in x, 
		in the same order. */
	// vector(const vector& __x)
	// 	: __base(__alloc_traits::select_on_container_copy_construction(__x.__alloc()))
	// {
	// 	size_type __n = __x.size();
	// 	if (__n > 0)
	// 	{
	// 		allocate(__n);
	// 		__construct_at_end(__x.__begin_, __x.__end_);
	// 	}
	// }
    // vector(const vector& __x, const allocator_type& __a)
	// 	: __base(__a)
	// {
	// 	size_type __n = __x.size();
	// 	if (__n > 0)
	// 	{
	// 		allocate(__n);
	// 		__construct_at_end(__x.__begin_, __x.__end_);
	// 	}
	// }

    // vector& operator=(const vector& __x);

	~vector() {}

};

};

#endif /* MGO_VECTOR_H_ */
