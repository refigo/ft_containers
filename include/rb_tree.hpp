#ifndef MGO_RB_TREE__
#define MGO_RB_TREE__

#include "iterator.hpp"
#include <memory>

namespace ft
{

// __rb_tree_node

typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;

struct __rb_tree_node_base
{
  typedef __rb_tree_color_type color_type;
  typedef __rb_tree_node_base* base_ptr;

  color_type color;
  base_ptr parent;
  base_ptr left;
  base_ptr right;

  static base_ptr minimum(base_ptr x)
  {
    while (x->left != 0) x = x->left;
    return x;
  }

  static base_ptr maximum(base_ptr x)
  {
    while (x->right != 0) x = x->right;
    return x;
  }
};

template <class Value>
struct __rb_tree_node : public __rb_tree_node_base
{
  typedef __rb_tree_node<Value>* link_type;
  Value value_field;
};

// __rb_tree_iterator

struct __rb_tree_base_iterator
{
  typedef __rb_tree_node_base::base_ptr base_ptr;
  typedef bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;
  base_ptr node;

  void increment()
  {
    if (node->right != 0) {
      node = node->right;
      while (node->left != 0)
        node = node->left;
    }
    else {
      base_ptr y = node->parent;
      while (node == y->right) {
        node = y;
        y = y->parent;
      }
      if (node->right != y)
        node = y;
    }
  }

  void decrement()
  {
    if (node->color == __rb_tree_red &&
        node->parent->parent == node)
      node = node->right;
    else if (node->left != 0) {
      base_ptr y = node->left;
      while (y->right != 0)
        y = y->right;
      node = y;
    }
    else {
      base_ptr y = node->parent;
      while (node == y->left) {
        node = y;
        y = y->parent;
      }
      node = y;
    }
  }
};

template <class Value, class Ref, class Ptr>
struct __rb_tree_iterator : public __rb_tree_base_iterator
{
  typedef Value value_type;
  typedef Ref reference;
  typedef Ptr pointer;
  typedef __rb_tree_iterator<Value, Value&, Value*>             iterator;
  typedef __rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
  typedef __rb_tree_iterator<Value, Ref, Ptr>                   self;
  typedef __rb_tree_node<Value>* link_type;

  __rb_tree_iterator() {}
  __rb_tree_iterator(link_type x) { node = x; }
  __rb_tree_iterator(const iterator& it) { node = it.node; }

  reference operator*() const { return link_type(node)->value_field; }
  pointer operator->() const { return &(operator*()); }

  self& operator++() { increment(); return *this; }
  self operator++(int) {
    self tmp = *this;
    increment();
    return tmp;
  }
    
  self& operator--() { decrement(); return *this; }
  self operator--(int) {
    self tmp = *this;
    decrement();
    return tmp;
  }
};

inline bool operator==(const __rb_tree_base_iterator& x,
                       const __rb_tree_base_iterator& y) {
  return x.node == y.node;
}

inline bool operator!=(const __rb_tree_base_iterator& x,
                       const __rb_tree_base_iterator& y) {
  return x.node != y.node;
}


template <class Key, class Value, class KeyOfValue, class Compare,
          class Allocator = std::allocator<Value> >
class rb_tree {
public:
  typedef Key                                           key_type;
	typedef Value                                      		value_type;
  typedef Compare                                 			value_compare;
  typedef Allocator                               			allocator_type;
  typedef typename allocator_type::pointer         			pointer;
  typedef typename allocator_type::const_pointer   			const_pointer;
  typedef typename allocator_type::size_type       			size_type;
  typedef typename allocator_type::difference_type 			difference_type;
	typedef	typename allocator_type::reference            reference;
	typedef	typename allocator_type::const_reference      const_reference;
  // typedef value_type* pointer;
  // typedef const value_type* const_pointer;
  // typedef value_type& reference;
  // typedef const value_type& const_reference;
  // typedef size_t size_type;
  // typedef ptrdiff_t difference_type;
  typedef __rb_tree_iterator<value_type, reference, pointer>              iterator;
  typedef __rb_tree_iterator<value_type, const_reference, const_pointer>  const_iterator;
  typedef reverse_iterator<const_iterator>                                const_reverse_iterator;
  typedef reverse_iterator<iterator>                                      reverse_iterator;
protected:
  typedef void*                                                           void_pointer;
  typedef __rb_tree_node_base*                                            base_ptr;
  typedef __rb_tree_node<Value>                                           rb_tree_node;
  typedef __rb_tree_color_type                                            color_type;
  typedef	typename allocator_type::template rebind<rb_tree_node>::other   node_allocator;
// public:
  typedef rb_tree_node*                                                   link_type; // NOTE: to public?

protected:
  size_type       node_count_; // keeps track of size of tree
  link_type       header_;
  Compare         value_compare_;
  allocator_type  value_alloc_;
  node_allocator  node_alloc_;

  link_type& root() const { return (link_type&) header_->parent; }
  link_type& leftmost() const { return (link_type&) header_->left; }
  link_type& rightmost() const { return (link_type&) header_->right; }

  static link_type& left(link_type _x) { return (link_type&)(_x->left); }
  static link_type& right(link_type _x) { return (link_type&)(_x->right); }
  static link_type& parent(link_type _x) { return (link_type&)(_x->parent); }
  static reference value(link_type _x) { return _x->value_field; }
  static const Key& key(link_type _x) { return KeyOfValue()(value(_x)); }
  static color_type& color(link_type _x) { return (color_type&)(_x->color); }

  static link_type& left(base_ptr _x) { return (link_type&)(_x->left); }
  static link_type& right(base_ptr _x) { return (link_type&)(_x->right); }
  static link_type& parent(base_ptr _x) { return (link_type&)(_x->parent); }
  static reference value(base_ptr _x) { return ((link_type)_x)->value_field; }
  static const Key& key(base_ptr _x) { return KeyOfValue()(value(link_type(_x)));} 
  static color_type& color(base_ptr _x) { return (color_type&)(link_type(_x)->color); }

  static link_type minimum(link_type _x) { 
    return (link_type)  __rb_tree_node_base::minimum(_x);
  }
  static link_type maximum(link_type _x) {
    return (link_type) __rb_tree_node_base::maximum(_x);
  }
private:
  void __init() {
    // header_ = get_node();
    header_ = node_alloc_.allocate(1);
    color(header_) = __rb_tree_red;
    root() = 0;
    leftmost() = header_;
    rightmost() = header_;
  }
public:
// (Constructor)
  rb_tree(const Compare& _comp = Compare()
        , const allocator_type _alloc = Allocator()
        , const node_allocator _node_alloc = node_allocator() )
      : node_count_(0)
      , header_(NULL)
      , value_compare_(_comp)
      , value_alloc_(_alloc)
      , node_alloc_(_node_alloc)
  { __init(); }

public:
                                // accessors:
  iterator begin() { return leftmost(); }
  const_iterator begin() const { return leftmost(); }
  iterator end() { return header_; }
  const_iterator end() const { return header_; }

public:
                                // Debugging.
  bool __rb_verify() const;
};

inline int __black_count(__rb_tree_node_base* _node, __rb_tree_node_base* _root)
{
  if (_node == 0)
    return 0;
  else {
    int bc = _node->color == __rb_tree_black ? 1 : 0;
    if (_node == _root)
      return bc;
    else
      return bc + __black_count(_node->parent, _root);
  }
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
bool
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::__rb_verify() const
{
  if (node_count_ == 0 || begin() == end())
    return node_count_ == 0 && begin() == end() &&
      header_->left == header_ && header_->right == header_;

  int len = __black_count(leftmost(), root());
  for (const_iterator it = begin(); it != end(); ++it) {
    link_type x = (link_type) it.node;
    link_type L = left(x);
    link_type R = right(x);

    if (x->color == __rb_tree_red)
      if ((L && L->color == __rb_tree_red) ||
          (R && R->color == __rb_tree_red))
        return false;
    
    if (L && value_compare_(value(x), value(L)))
      return false;
    if (L && value_compare_(value(R), value(x)))
      return false;
    
    if (!L && !R && __black_count(x, root()) != len)
      return false;
  }

  if (leftmost() != __rb_tree_node_base::minimum(root()))
    return false;
  if (rightmost() != __rb_tree_node_base::maximum(root()))
    return false;
  
  return true;
}

} // namespace ft

#endif /* MGO_RB_TREE__ */