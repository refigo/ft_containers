#ifndef __MGO_RB_TREE_
#define __MGO_RB_TREE_

#include "iterator.hpp"

#include <memory>

namespace ft {

// __rb_tree_node

// template <class _Pointer>
// class __rb_tree_end_node
// {
// public:
//     typedef _Pointer pointer;


//     __rb_tree_end_node() : __left_() {}
// };

// template <class _VoidPtr>
// class __rb_tree_node_base
//     : public __rb_tree_end_node<_VoidPtr>
// {
//     __rb_tree_node_base(const __rb_tree_node_base&);
//     __rb_tree_node_base& operator=(const __rb_tree_node_base&);
// public:
//     typedef _VoidPtr					pointer;
//     typedef const _VoidPtr				const_pointer;
//     typedef __rb_tree_end_node<pointer> base;


//     __rb_tree_node_base() : __right_(), __parent_(), __is_black_(false) {}
// };

template <class _Tp>
class __rb_tree_node
{
public:
    typedef _Tp 			value_type;
	typedef __rb_tree_node*	pointer;

    value_type	__value_;
    bool		__is_black_;
    pointer		__parent_;
    pointer		__left_;
    pointer		__right_;

	__rb_tree_node()
		: __value_()
		, __is_black_(false)
		, __parent_(NULL)
		, __left_(NULL)
		, __right_(NULL) {}

    explicit __rb_tree_node(const value_type& __v)
            : __value_(__v), __is_black_(false), __left_(), __right_(), __parent_() {}
};

// __rb_tree_iterator

template <class _Tp, class _NodePtr, class _DiffType>
class __rb_tree_iterator
{
    typedef _NodePtr                                              	__node_pointer;
    typedef __node_pointer*											__node;
    typedef typename __node::base                                 	__node_base;
    typedef typename __node_base::pointer                         	__node_base_pointer;

    __node_pointer __ptr_;

    // typedef pointer_traits<__node_pointer> __pointer_traits;
public:
    typedef bidirectional_iterator_tag 	iterator_category;
    typedef _Tp                        	value_type;
    typedef _DiffType                  	difference_type;
    typedef value_type&                	reference;
    typedef value_type*					pointer;

    __rb_tree_iterator() {}

    reference operator*() const {return __ptr_->__value_;}
    pointer operator->() const {return &__ptr_->__value_;}

    __rb_tree_iterator& operator++()
        {__ptr_ = static_cast<__node_pointer>(__tree_next(static_cast<__node_base_pointer>(__ptr_)));
         return *this;}
    __rb_tree_iterator operator++(int)
        {__rb_tree_iterator __t(*this); ++(*this); return __t;}

    __rb_tree_iterator& operator--()
        {__ptr_ = static_cast<__node_pointer>(__tree_prev(static_cast<__node_base_pointer>(__ptr_)));
         return *this;}
    __rb_tree_iterator operator--(int)
        {__rb_tree_iterator __t(*this); --(*this); return __t;}

    friend bool operator==(const __rb_tree_iterator& __x, const __rb_tree_iterator& __y)
        {return __x.__ptr_ == __y.__ptr_;}
    friend bool operator!=(const __rb_tree_iterator& __x, const __rb_tree_iterator& __y)
        {return !(__x == __y);}

private:
    explicit __rb_tree_iterator(__node_pointer __p) : __ptr_(__p) {}
    // template <class, class, class> friend class __tree;
    // template <class, class, class> friend class __tree_const_iterator;
    // template <class> friend class __map_iterator;
    // template <class, class, class, class> friend class map;
    // template <class, class, class, class> friend class multimap;
    // template <class, class, class> friend class set;
    // template <class, class, class> friend class multiset;
};

// __rb_tree

template <class _Tp, class _Compare, class _Allocator>
class __rb_tree
{
public:
	typedef _Tp                                      			value_type;
    typedef _Compare                                 			value_compare;
    typedef _Allocator                               			allocator_type;
    typedef typename allocator_type::pointer         			pointer;
    typedef typename allocator_type::const_pointer   			const_pointer;
    typedef typename allocator_type::size_type       			size_type;
    typedef typename allocator_type::difference_type 			difference_type;
	
	// node
	typedef	ft::__rb_tree_node<value_type>							__node;
	typedef	ft::__rb_tree_node<value_type>*							__node_pointer;
	typedef	typename allocator_type::template rebind<__node>::other	__node_allocator; // NOTE

	// iterator
	typedef	ft::__rb_tree_iterator<value_type, 
			__node_pointer, difference_type>					iterator;
	typedef	ft::reverse_iterator<iterator>						reverse_iterator;

private:
	value_compare		__comp_;
	allocator_type		__alloc_;
	__node_allocator	__node_alloc_;
	__node_pointer		__nil_;
	size_type			__size_;

public:
	__rb_tree(value_compare const& __comp, 
		allocator_type const& __alloc = allocator_type(), 
		__node_allocator const& __node_alloc = __node_allocator())
		:	__comp_(__comp),
			__alloc_(__alloc),
			__node_alloc_(__node_alloc),
			__nil_(NULL),
			__size_(0)
		{
			__nil_ = __node_alloc_.allocate(1);
			__node_alloc_.construct(__nil_, __node());
		}

};

} // namespace ft

#endif /* __MGO_RB_TREE_ */