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
	typedef	ft::__rb_tree_iterator<const value_type>			const_iterator; // TODO
	typedef	ft::reverse_iterator<iterator>						reverse_iterator;
	typedef	ft::reverse_iterator<const_iterator>				const_reverse_iterator; // TODO

private:
	// node
	typedef	ft::__rb_tree_node<value_type>							__node;
	typedef	ft::__rb_tree_node<value_type>*							__node_pointer;
	typedef	typename allocator_type::template rebind<__node>::other	__node_allocator; // NOTE: __node에 대한 allocator 타입

	value_compare		__val_comp_;
	allocator_type		__alloc_;
	__node_allocator	__node_alloc_;
	// __node_pointer		__nil_;
	__node_pointer		__header_;
	size_type			__size_;

public:
	__rb_tree(value_compare const& _vc, 
		allocator_type const& _alloc = allocator_type(), 
		__node_allocator const& _node_alloc = __node_allocator())
		: __val_comp_(_vc)
		, __alloc_(_alloc)
		, __node_alloc_(_node_alloc)
		// , __nil_(NULL)
		, __header_(NULL)
		, __size_(0)
		{
			__header_ = __node_alloc_.allocate(1);
			__node_alloc_.construct(__header_, __node());
		}
	__rb_tree(const red_black_tree &ref)
  : __val_comp_(ref._comp)
		, __alloc_(ref._alloc)
		, __node_alloc_(ref._node_alloc)
		// , __nil_(NULL)
		, __header_(NULL)
		, __size_(0)
	{
		_meta_node = _node_alloc.allocate(1);
		_node_alloc.construct(_meta_node, node_type());
		if (ref.getRoot() != my_nullptr) {
			copyTree(ref.getRoot());
		}
	}
	void	copyTree(node_pointer node)
	{
		if(node != my_nullptr) {
			insertValue(node->value);
			copyTree(node->left);
			copyTree(node->right);
		}
	}
	virtual ~red_black_tree()
	{
		this->clear();
		_node_alloc.destroy(_meta_node);
		_node_alloc.deallocate(_meta_node, 1);
	}
	red_black_tree& operator=(const red_black_tree &ref)
	{
		if (this == &ref)
			return (*this);
		this->clear();
		this->_comp = ref._comp;
		this->_alloc = ref._alloc;
		this->_node_alloc = ref._node_alloc;
		copyTree(ref.getRoot());
		this->_size = ref._size;
		return (*this);
	}
// Iterators:
	iterator				begin(){ return (iterator(minValueNode(_meta_node))); }
	const_iterator			begin() const  { return (const_iterator(minValueNode(_meta_node))); }
	iterator				end() { return (iterator(_meta_node)); }
	const_iterator			end() const { return (const_iterator(_meta_node)); }
	reverse_iterator		rbegin() { return (reverse_iterator(end())); }
	const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }
	reverse_iterator		rend() { return (reverse_iterator(begin())); }
	const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }
// Capacity:
	bool					empty() const { return (this->_size == 0); }
	size_type				size() const { return (this->_size); }
	size_type				max_size() const { return (_node_alloc.max_size()); }
// Modifiers:
	pair<iterator,bool>		insert (const value_type& val)
	{ return (insertValue(val)); }
	iterator				insert (iterator position, const value_type& val)
	{
		(void)position;
		return (insertValue(val).first);
	}
template <class InputIterator>
	void					insert (InputIterator first, InputIterator last)
	{
		while (first != last) {
			this->insert(*first);
			++first;
		}
	}
	void					erase (const_iterator position) { deleteValue(*position); }
	size_type				erase (const value_type& k) { return (deleteValue(k)); }
	void					erase (const_iterator first, const_iterator last)
	{
		for (const_iterator it = first; it != last; ) {
			erase(it++);
		}
	}
	void swap (rbtree& x)
	{
		if (this == &x)
			return;
		value_compare	tmp_comp = x._comp;
		node_alloc_type	tmp_node_alloc = x._node_alloc;
		node_pointer	tmp_meta_node = x._meta_node;
		size_type		tmp_size = x._size;

		x._comp = this->_comp;
		x._node_alloc = this->_node_alloc;
		x._meta_node = this->_meta_node;
		x._size = this->_size;

		this->_comp = tmp_comp;
		this->_node_alloc = tmp_node_alloc;
		this->_meta_node = tmp_meta_node;
		this->_size = tmp_size;
	}
	void clear()
	{
		deleteTree(getRoot());
		setRoot(my_nullptr);
		this->_size = 0;
	}
	iterator	find (const value_type& k) const
	{
		node_pointer	tmp = getRoot();
		while (tmp != my_nullptr) {
			if (!_comp(tmp->value, k) && !_comp(k, tmp->value))
				break;
			else if (_comp(tmp->value, k))
				tmp = tmp->right;
			else
				tmp = tmp->left;
		}
		if (tmp == my_nullptr)
			return (iterator(this->_meta_node));
		return (iterator(tmp));
	}
	size_type	count (const value_type& k) const
	{
		iterator	tmp = find(k);
		if (tmp == end())
			return (0);
		size_type	count = 0;
		for (iterator it = tmp; it != end(); ++it) {
			if (!_comp(*it, k) && !_comp(k, *it))
				++count;
		}
		return (count);
	}
	
	// insert_unique_node
	ft::pair<iterator,bool>	insert_unique_node(__node_pointer node)
	{
		__node_pointer tmp = __get_root();
		__node_pointer parent;
		if (tmp == NULL) {
			__set_root(node);
			return (ft::make_pair(iterator(node), true));
		}
		while (tmp) {
			if (__val_comp_(tmp->value, node->value)) {
				parent = tmp;
				tmp = tmp->right;
			}
			else if (__val_comp_(node->value, tmp->value)) {
				parent = tmp;
				tmp = tmp->left;
			}
			else
				return (ft::make_pair(iterator(tmp), false));
		}
		if (__val_comp_(parent->value, node->value)) {
			parent->right = node;
			node->parent = parent;
		}
		else {
			parent->left = node;
			node->parent = parent;
		}
		return (ft::make_pair(iterator(node), true));
	}

	//insert_unique_value
	ft::pair<iterator, bool> insert_unique_value(const value_type& _val)
	{
		__node_pointer	__new = __node_alloc_.allocate(1);
		__node_alloc_.construct(__new, node_type(_val));
		pair<iterator,bool> __ret = insert_unique_node(__new);
		if (__ret.second == false) {
			__node_alloc_.destroy(__new);
			__node_alloc_.deallocate(__new, 1);
		} else {
			this->_size++;
			fix_after_insert(__new);
		}
		return (__ret);
	}

	void	fix_after_insert(__node_pointer _node)
	{
		__node_pointer	parent;
    __node_pointer  grandparent;

		while (_node != __get_root() && get_color(_node) == RED && get_color(getParent(_node)) == RED)
		{
			parent = get_parent(_node);
			grandparent = get_grandparent(_node);
			if (grandparent == NULL)
				break;
			__node_pointer	uncle = get_uncle(_node);
			if (get_color(uncle) == RED) {
				insert_case_1(_node);
			} else if (parent == grandparent->left) {
				if (_node == parent->right)
					insert_case_2(_node, parent);
				insert_case_3(_node, parent, grandparent);
			} else if (parent == grandparent->right) {
				if (_node == parent->left)
					insert_case_2(_node, parent);
				insert_case_3(_node, parent, grandparent);
			}
		}
		set_color(__get_root(), BLACK);
	}

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
			return (iterator(this->__header_));
		return (iterator(__node_ptr));
	}

private:
	__node_pointer	__get_root(void) const {
		return (__header_->left);
	}
	void			__set_root(__node_pointer _node) {
		__header_->left = _node;
		__header_->right = _node;
		if (_node != NULL)
			_node->parent = __header_;
	}
	void	delete_tree(__node_pointer node) {
		if (node == NULL)
			return;
		delete_tree(node->left);
		delete_tree(node->right);
		__node_alloc_.destroy(node);
		__node_alloc_.deallocate(node, 1);
	}
	void	rotateLeft(__node_pointer node) {
		__node_pointer	rightChild = node->right;
		if (rightChild == NULL)
			return;
		node->right = rightChild->left;
		if (node->right != NULL)
			node->right->parent = node;
		rightChild->parent = node->parent;
		if (get_parent(node) == NULL)
			__set_root(rightChild);
		else if (node == node->parent->left)
			node->parent->left = rightChild;
		else
			node->parent->right = rightChild;
		rightChild->left = node;
		node->parent = rightChild;
	}
	void	rotate_right(__node_pointer node)
	{
		__node_pointer	leftChild = node->left;
		if (leftChild == NULL)
			return;
		node->left = leftChild->right;
		if (node->left != NULL)
			node->left->parent = node;
		leftChild->parent = node->parent;
		if (get_parent(node) == NULL)
			set_root(leftChild);
		else if (node == node->parent->left)
			node->parent->left = leftChild;
		else
			node->parent->right = leftChild;
		leftChild->right = node;
		node->parent = leftChild;
	}
	__node_pointer	min_value_node(__node_pointer node) const
	{
		if (node == NULL)
			return (node);
		while (node->left != NULL)
			node = node->left;
		return (node);
	}
	__node_pointer	max_value_node(__node_pointer node) const
	{
		if (node == NULL)
			return (node);
		while (node->right != NULL)
			node = node->right;
		return (node);
	}
	__node_pointer	get_parent(__node_pointer node) const
	{
		if (node == NULL)
			return node;
		if (node->parent == this->_meta_node)
			return (NULL);
		return (node->parent);
	}
	__node_pointer	get_grandparent(__node_pointer node)
	{
		__node_pointer pr = get_parent(node);
		if (pr == NULL)
			return (NULL);
		return (get_parent(pr));
	}
	__node_pointer	get_sibling(__node_pointer node)
	{
		__node_pointer	pr = get_parent(node);
		if (pr == NULL)
			return (NULL);
		if (node == pr->left)
			return (pr->right);
		return (pr->left);
	}
	__node_pointer	get_uncle(__node_pointer node)
	{
		__node_pointer	pr = get_parent(node);
		if (pr == NULL)
			return (NULL);
		return (get_sibling(pr));
	}
	e_color	get_color(__node_pointer node)
	{
		if (node == NULL)
			return (BLACK);
		return (node->__color_);
	}
	void	setColor(__node_pointer node, e_color color)
	{
		if (node == NULL)
			return;
		node->__color_ = color;
	}

};

} // namespace ft

#endif /* __MGO_RB_TREE_ */