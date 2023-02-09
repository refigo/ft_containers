#ifndef MGO_VECTOR_HPP_
#define MGO_VECTOR_HPP_

#include "type_traits.hpp"
#include "iterator.hpp"

#include <limits> // numeric_limits
#include <memory> // allocator
#include <stdexcept> // for throwing error in __vector_base_common
#include <algorithm> // min(), max()

namespace ft {

template <bool>
class __vector_base_common
{
protected:
    __vector_base_common() {}
    void __throw_length_error() const
    {
        throw std::length_error("vector");
    }
    void __throw_out_of_range() const
    {
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

    // (constructor)
    // __vector_base()
    // 	: __begin_(0),
    // 	__end_(0),
    // 	__end_cap_(0),
    // 	__alloc_(allocator_type()) {}
    __vector_base(const allocator_type& __a)
        : __begin_(NULL),
        __end_(NULL),
        __end_cap_(NULL),
        __alloc_(__a) {}
    // (destructor)
    ~__vector_base()
    {
        if (__begin_ != NULL)
        {
            this->clear();
            this->__alloc_.deallocate(__begin_, this->capacity());
        }
    }

    //clear()
    void clear()
    {
        __destruct_at_end(__begin_);
    }
    //capacity()
    size_type capacity() const
    {
        return (static_cast<size_type>(this->__end_cap_ - this->__begin_));
    }

    // __destruct_at_end()
    void __destruct_at_end(const_pointer __new_last)
    {
        while (__new_last < __end_)
            this->__alloc_.destroy(const_cast<pointer>(--__end_));
    }

    // __copy_assign_alloc()
    void __copy_assign_alloc(const __vector_base& __c)
    {
        if (__alloc_ != __c.__alloc_)
        {
            this->clear();
            __alloc_.deallocate(__begin_, this->capacity());
            __begin_ = __end_ = __end_cap_ = NULL;
        }
        __alloc_ = __c.__alloc_;
    }

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


    // (constructor)
    /*	(1) empty container constructor (default constructor)
        Constructs an empty container, with no elements. */
    explicit vector(const allocator_type& __a = allocator_type()) : __base(__a) {}
    // vector() {}
    // explicit vector(const allocator_type& __a) : __base(__a) {}

    /*	(2) fill constructor
        Constructs a container with n elements. Each element is a copy of val. */
    explicit vector(size_type __n, const value_type& __x = value_type(), 
                    const allocator_type& __a = allocator_type())
        : __base(__a)
    {
        if (__n > 0)
        {
            __allocate(__n);
            __construct_at_end(__n, __x);
        }
    }
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
    template <class _InputIterator>
        vector(_InputIterator __first, _InputIterator __last, 
               const allocator_type& __a = allocator_type(),
               typename enable_if<__is_input_iterator<_InputIterator>::value>::type* = 0)
        : __base(__a)
    {
        for (; __first != __last; ++__first)
            push_back(*__first);
    }
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
    vector(const vector& __x, const allocator_type& __a = allocator_type())
    	: __base(__a)
    {
    	size_type __n = __x.size();
    	if (__n > 0)
    	{
    		__allocate(__n);
    		__construct_at_end(__x.__begin_, __x.__end_);
    	}
    }
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

    
    // (destructor)
    ~vector() {}


    // operator=
    vector& operator=(const vector& __x)
    {
        if (this != &__x)
        {
            __base::__copy_assign_alloc(__x);
            assign(__x.__begin_, __x.__end_);
        }
        return *this;
    }


    // Iterators


    // Capacity
    // size()
    size_type size() const
    {
        return (static_cast<size_type>(this->__end_ - this->__begin_));
    }
    // max_size()
    size_type max_size() const
    {
        return (std::min(this->__alloc_.max_size(), std::numeric_limits<size_type>::max() / 2));  // end() >= begin(), always
    }
    // resize()
    // void resize(size_type __sz)
    // {
    //     size_type __cs = size();
    //     if (__cs < __sz)
    //         this->__append(__sz - __cs);
    //     else if (__cs > __sz)
    //         this->__destruct_at_end(this->__begin_ + __sz);
    // }
    void resize(size_type __sz, value_type __x = value_type())
    {
        size_type __cs = size();
        if (__cs < __sz)
            __append(__sz - __cs, __x);
        else if (__cs > __sz)
            __destruct_at_end(this->__begin_ + __sz);
    }
    // capacity()
    size_type capacity() const {return (__base::capacity());}
    // empty()
    bool empty() const {return (this->__begin_ == this->__end_);}
    // reserve()
    void reserve(size_type __n)
    {
        if (__n > this->max_size())
            this->__throw_length_error();
        if (__n > this->capacity())
        {
            // allocator_type& __a = this->__alloc();
            // __split_buffer<value_type, allocator_type&> __v(__n, 0, __a);
            // __v.__construct_at_end(move_iterator<pointer>(this->__begin_),
            //                     move_iterator<pointer>(this->__end_));
            // this->clear();
            // __swap_out_circular_buffer(__v);
            pointer __tmp_begin = this->__alloc_.allocate(__n);
            std::uninitialized_copy(this->__begin_, this->__end_, __tmp_begin); // TODO: consider...
            this->__end_ = __tmp_begin + this->size();
            this->__alloc_.deallocate(this->__begin_, this->capacity());
            this->__begin_ = __tmp_begin;
            this->__end_cap_ = this->__begin_ + __n;
        }
    }


    // Element access
    // operator[]
    reference       operator[](size_type __n) {return (this->__begin_[__n]);}
    const_reference operator[](size_type __n) const {return (this->__begin_[__n]);}
    // at()
    reference       at(size_type __n)
    {
        if (__n >= size())
            this->__throw_out_of_range();
        return (this->__begin_[__n]);
    }
    const_reference at(size_type __n) const
    {
        if (__n >= size())
            this->__throw_out_of_range();
        return (this->__begin_[__n]);
    }
    // front()
    // back()

    // Modifiers
    // assign()
    template <class _InputIterator>
        typename enable_if
        <
             __is_input_iterator  <_InputIterator>::value,
            void
        >::type
        assign(_InputIterator __first, _InputIterator __last)
    {
        this->clear();
        for (; __first != __last; ++__first)
            this->push_back(*__first);
    }
    void assign(size_type __n, const_reference __u)
    {
        if (__n <= this->capacity())
        {
            size_type __s = this->size();
            std::fill_n(this->__begin_, std::min(__n, __s), __u);
            if (__n > __s)
                __construct_at_end(__n - __s, __u);
            else
                __destruct_at_end(this->__begin_ + __n);
        }
        else
        {
            __deallocate();
            __allocate(__recommend(static_cast<size_type>(__n)));
            __construct_at_end(__n, __u);
        }
    }
    // push_back()
    void push_back(const_reference __x)
    {
        if (this->__end_ >= this->__end_cap_)
        {
            size_type size_recommended = __recommend(this->size() + 1);
            this->reserve(size_recommended);
        }
        this->__alloc_.construct(this->__end_, __x);
        ++(this->__end_);
    }
    // pop_back()
    // insert()
    // erase()
    // swap()
    // clear()
    void clear() {__base::clear();}

    // Allocator
    // get_allocator()


private:
    // __allocate()
    void __allocate(size_type __n)
    {
        if (__n > this->max_size())
            this->__throw_length_error();
        this->__begin_ = this->__end_ = this->__alloc_.allocate(__n);
        this->__end_cap_ = this->__begin_ + __n;
    }

    // __deallocate()
    void __deallocate()
    {
        if (this->__begin_ != NULL)
        {
            this->clear();
            this->__alloc_.deallocate(this->__begin_, this->capacity());
            this->__begin_ = this->__end_ = this->__end_cap_ = NULL;
        }
    }

    // __recommend()
    size_type __recommend(size_type __new_size) const
    {
        const size_type __ms = this->max_size();
        if (__new_size > __ms)
            this->__throw_length_error();
        const size_type __cap = this->capacity();
        if (__cap >= __ms / 2)
            return __ms;
        return (std::max(2*__cap, __new_size));
    }

    // __construct_at_end()
    void __construct_at_end(size_type __n)
    {
        do
        {
            this->__alloc_.construct(this->__end_);
            ++(this->__end_);
            --__n;
        } while (__n > 0);
    }
    void __construct_at_end(size_type __n, const_reference __x)
    {
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
        __construct_at_end(_ForwardIterator __first, _ForwardIterator __last)
    {
        // allocator_type& __a = this->__alloc();
        for (; __first != __last; ++__first)
        {
            // __alloc_traits::construct(__a, _STD::__to_raw_pointer(this->__end_), *__first);
            this->__alloc_.construct(this->__end_, *__first);
            ++this->__end_;
        }
    }

    //  Default constructs __n objects starting at __end_
    //  throws if construction throws
    //  Postcondition:  size() == size() + __n
    //  Exception safety: strong but assumes move ctor doesn't throw (copy ctor can)
    // void __append(size_type __n)
    // {
    //     if (static_cast<size_type>(this->__end_cap() - this->__end_) >= __n)
    //         this->__construct_at_end(__n);
    //     else
    //     {
    //         allocator_type& __a = this->__alloc();
    //         __split_buffer<value_type, allocator_type&> __v(__recommend(size() + __n), size(), __a);
    //         __v.__construct_at_end(__n);
    //         __swap_out_circular_buffer(__v);
    //     }
    // }

    //  Default constructs __n objects starting at __end_
    //  throws if construction throws
    //  Postcondition:  size() == size() + __n
    //  Exception safety: strong but assumes move ctor doesn't throw (copy ctor can)
    void __append(size_type __n, const_reference __x)
    {
        if (static_cast<size_type>(this->__end_cap_ - this->__end_) >= __n)
            __construct_at_end(__n, __x);
        else
        {
            this->reserve(__recommend(this->size() + __n));
            __construct_at_end(__n, __x); // recommend에서 반환한 값 만큼으로 제한?
        }
    }


};


// Non-member function overloads
// relational operators()
// swap()


};

#endif /* MGO_VECTOR_HPP_ */
