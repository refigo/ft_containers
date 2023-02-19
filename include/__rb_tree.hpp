#ifndef __MGO_RB_TREE_
#define __MGO_RB_TREE_

namespace ft {

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

private:
	// node
	typedef	ft::__rb_tree_node<T>								__node;
	typedef	ft::__rb_tree_node<T>*								__node_pointer;
	typedef	typename allocator_type::template rebind<__node>	__node_allocator; // NOTE



// public:
// 	typedef __tree_node<value_type, typename allocator_type::void_pointer> __node;
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