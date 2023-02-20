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

enum e_color
{
	RED,
	BLACK,
	D_BLACK
};

template <class _Tp>
class __rb_tree_node
{
public:
    typedef _Tp 			value_type;
	typedef __rb_tree_node*	pointer;
	typedef e_color			color;

    value_type	__value_;
    // bool		__is_black_;
	color		__color_;
    pointer		__parent_;
    pointer		__left_;
    pointer		__right_;

	__rb_tree_node()
		: __value_()
		// , __is_black_(false)
		, __color_(RED)
		, __parent_(NULL)
		, __left_(NULL)
		, __right_(NULL) {}

    explicit __rb_tree_node(const value_type& __v)
		: __value_(__v)
		// , __is_black_(false)
		, __color_(RED)
		, __left_()
		, __right_()
		, __parent_() {}
};

// __rb_tree_iterator

template <class _Tp>
class __rb_tree_iterator
{
public:
	typedef	bidirectional_iterator_tag			iterator_category;
	typedef	_Tp									value_type;
	typedef	value_type&							reference;
	typedef	ptrdiff_t							difference_type;
	typedef	_Tp*								pointer;
private:
	typedef	ft::__rb_tree_node<_Tp>				__node;
	typedef	ft::__rb_tree_node<_Tp>*			__node_pointer;

private:
	__node_pointer	__node_ptr_;

public:
	__rb_tree_iterator()
		: __node_ptr_() {}
	__rb_tree_iterator(const __rb_tree_iterator &__ref)
		: __node_ptr_(__ref.__node_ptr_) {}
	__rb_tree_iterator(__node_pointer __node_ptr)
		: __node_ptr_(__node_ptr) {}
	
	~__rb_tree_iterator() {}

	__rb_tree_iterator&		operator=(const __rb_tree_iterator& __ref)
	{
		if (this != &__ref)
			this->__node_ptr_ = __ref.__node_ptr;
		return (*this);
	}

	__node_pointer		base() const { return (this->__node_ptr_); }

	__rb_tree_iterator&		operator++()
	{
		if (__node_ptr_->right != NULL) {
			__node_ptr_ = getLeftMostNodePtrFrom(__node_ptr_->right);
			return (*this);
		}
		while (__node_ptr_->parent && __node_ptr_->parent->right == __node_ptr_)
			__node_ptr_ = __node_ptr_->parent;
		if (__node_ptr_->parent)
			__node_ptr_ = __node_ptr_->parent;
		// TODO: check end() using else to null?
		return (*this);
	}
	__rb_tree_iterator&		operator--()
	{
		if (__node_ptr_->left != NULL) {
			__node_ptr_ = getRightMostNodePtrFrom(__node_ptr_->left);
			return (*this);
		}
		while (__node_ptr_->parent && __node_ptr_->parent->left == __node_ptr_)
			__node_ptr_ = __node_ptr_->parent;
		if (__node_ptr_->parent)
			__node_ptr_ = __node_ptr_->parent;
		else
			__node_ptr_ = NULL;
		return (*this);
	}
	__rb_tree_iterator	operator++(int)		{ __rb_tree_iterator	__ret = *this; ++(*this); return (__ret); }
	__rb_tree_iterator	operator--(int)		{ __rb_tree_iterator	__ret = *this; --(*this); return (__ret); }

	reference			operator*()	const	{ return (__node_ptr_->value); }
	pointer				operator->() const	{ return (&(__node_ptr_->value)); }

	bool				operator ==	(const __rb_tree_iterator& rhs) { return (this->_node == rhs._node); }
	bool				operator !=	(const __rb_tree_iterator& rhs) { return (this->_node != rhs._node); }
	// bool				operator ==	(const __rb_tree_const_iterator<T>& rhs) { return (this->base() == rhs.base()); }
	// bool				operator !=	(const __rb_tree_const_iterator<T>& rhs) { return (this->base() != rhs.base()); }

private:
	__node_pointer	getLeftMostNodePtrFrom(__node_pointer __node_ptr)
	{
		if (__node_ptr == NULL) // check nil
			return (__node_ptr);
		while (__node_ptr->left != NULL)
			__node_ptr = __node_ptr->left;
		return (__node_ptr);
	}
	__node_pointer	getRightMostNodePtrFrom(__node_pointer __node_ptr)
	{
		if (__node_ptr == NULL)
			return (__node_ptr);
		while (__node_ptr->right != NULL)
			__node_ptr = __node_ptr->right;
		return (__node_ptr);
	}
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
	// typedef	ft::__rb_tree_iterator<value_type>					const_iterator; // TODO
	typedef	ft::reverse_iterator<iterator>						reverse_iterator;
	// typedef	ft::reverse_iterator<const_iterator>				const_reverse_iterator; // TODO

private:
	// node
	typedef	ft::__rb_tree_node<value_type>							__node;
	typedef	ft::__rb_tree_node<value_type>*							__node_pointer;
	typedef	typename allocator_type::template rebind<__node>::other	__node_allocator; // NOTE: __node에 대한 allocator 타입

	value_compare		__val_comp_;
	allocator_type		__alloc_;
	__node_allocator	__node_alloc_;
	// __node_pointer		__nil_;
	__node_pointer		__meta_node_;
	size_type			__size_;

public:
	__rb_tree(value_compare const& __vc, 
		allocator_type const& __alloc = allocator_type(), 
		__node_allocator const& __node_alloc = __node_allocator())
		: __val_comp_(__vc)
		, __alloc_(__alloc)
		, __node_alloc_(__node_alloc)
		// , __nil_(NULL)
		, __meta_node_(NULL)
		, __size_(0)
		{
			__meta_node_ = __node_alloc_.allocate(1);
			__node_alloc_.construct(__meta_node_, __node());
		}
	

	// pair<typename __tree<_Tp, _Compare, _Allocator>::iterator, bool>
	// __insert_unique(const value_type& __v)
	// {
	// 	// 이미 같은게 있는지 찾기
	// 	// getRoot
	// 	// 기존에 같은게 없으면 insert
	// 	node_pointer	node = _node_alloc.allocate(1);
	// 	_node_alloc.construct(node, node_type(val));
	// 	pair<iterator,bool> ret = insertNode(node);
	// 	if (ret.second == false) {
	// 		_node_alloc.destroy(node);
	// 		_node_alloc.deallocate(node, 1);
	// 	} else {
	// 		this->_size++;
	// 		fixAfterInsert(node);
	// 	}
	// 	return (ret);


	// 	__node_base_pointer __parent;
	// 	__node_base_pointer& __child = __find_equal(__parent, __v);
	// 	__node_pointer __r = static_cast<__node_pointer>(__child);
	// 	bool __inserted = false;
		
	// 	if (__child == nullptr)
	// 	{
	// 		__node_holder __h = __construct_node(__v);
	// 		__insert_node_at(__parent, __child, __h.get());
	// 		__r = __h.release();
	// 		__inserted = true;
	// 	}
	// 	return pair<iterator, bool>(iterator(__r), __inserted);
	// }

	// find
	iterator	find(const value_type& __k) const
	{
		__node_pointer	__node_ptr = __get_root();
		while (__node_ptr != NULL) {
			if (!__val_comp_(__node_ptr->value, __k) && !__val_comp_(__k, __node_ptr->value))
				break;
			else if (__val_comp_(__node_ptr->value, __k))
				__node_ptr = __node_ptr->right;
			else
				__node_ptr = __node_ptr->left;
		}
		if (__node_ptr == NULL)
			return (iterator(this->__meta_node_));
		return (iterator(__node_ptr));
	}

private:
	__node_pointer	__get_root(void) const { return (__meta_node_->left); }

};

} // namespace ft

#endif /* __MGO_RB_TREE_ */