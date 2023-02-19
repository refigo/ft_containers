#ifndef __MGO_RB_TREE_
#define __MGO_RB_TREE_

#include "iterator.hpp"

#include <memory>

namespace ft {

// __rb_tree_node

template <class _Pointer>
class __rb_tree_end_node
{
public:
    typedef _Pointer pointer;
    pointer __left_;

    __rb_tree_end_node() : __left_() {}
};

template <class _VoidPtr>
class __rb_tree_node_base
    : public __rb_tree_end_node<_VoidPtr>
{
    __rb_tree_node_base(const __rb_tree_node_base&);
    __rb_tree_node_base& operator=(const __rb_tree_node_base&);
public:
    typedef _VoidPtr					pointer;
    typedef const _VoidPtr				const_pointer;
    typedef __rb_tree_end_node<pointer> base;

    pointer __right_;
    pointer __parent_;
    bool __is_black_;

    __rb_tree_node_base() : __right_(), __parent_(), __is_black_(false) {}
};

template <class _Tp, class _VoidPtr>
class __rb_tree_node
    : public __rb_tree_node_base<_VoidPtr>
{
public:
    typedef __rb_tree_node_base<_VoidPtr> base;
    typedef _Tp value_type;

    value_type __value_;

    explicit __rb_tree_node(const value_type& __v)
            : __value_(__v) {}
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
	// iterator
	typedef	ft::__rb_tree_iterator<value_type>					iterator;
	typedef	ft::reverse_iterator<iterator>						reverse_iterator;
	// node
	typedef	ft::__rb_tree_node<value_type, 
						typename allocator_type::void_pointer>	__node;
	typedef	ft::__rb_tree_node<value_type, 
						typename allocator_type::void_pointer>*	__node_pointer;
	typedef	typename allocator_type::template rebind<__node>	__node_allocator; // NOTE



// public:
// 	typedef __rb_tree_node<value_type, typename allocator_type::void_pointer> __node;
// 	typedef typename allocator_type::template
//             rebind_alloc<__node>
//                                                      __node_allocator;
//     // typedef allocator_traits<__node_allocator>       __node_traits;
//     typedef typename __node_allocator::pointer          __node_pointer;
//     typedef typename __node_allocator::const_pointer    __node_const_pointer;
//     typedef typename __node::base::pointer           __node_base_pointer;
//     typedef typename __node::base::const_pointer     __node_base_const_pointer;
// private:
//     typedef typename __node::base::base __end_node_t;
//     typedef typename pointer_traits<__node_pointer>::template
//             rebind<__end_node_t>
//                                                      __end_node_ptr;
//     typedef typename pointer_traits<__node_pointer>::template
//             rebind<const __end_node_t>
//                                                      __end_node_const_ptr;
//     __node_pointer                                          __begin_node_;
//     __compressed_pair<__end_node_t, __node_allocator>  __pair1_;
//     __compressed_pair<size_type, value_compare>        __pair3_;



};

} // namespace ft

#endif /* __MGO_RB_TREE_ */