#ifndef MGO_RB_TREE__
#define MGO_RB_TREE__

#include "__utils.hpp"
#include "algorithm.hpp"
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

// __rb_tree_rotate

inline void
__rb_tree_rotate_left(__rb_tree_node_base* _target, __rb_tree_node_base*& _root) {
  __rb_tree_node_base* substitute = _target->right;
  _target->right = substitute->left;
  if (substitute->left != NULL)
    substitute->left->parent = _target;
  substitute->parent = _target->parent;

  if (_target == _root)
    _root = substitute;
  else if (_target == _target->parent->left)
    _target->parent->left = substitute;
  else
    _target->parent->right = substitute;
  substitute->left = _target;
  _target->parent = substitute;
}

inline void
__rb_tree_rotate_right(__rb_tree_node_base* _target, __rb_tree_node_base*& _root) {
  __rb_tree_node_base* substitute = _target->left;
  _target->left = substitute->right;
  if (substitute->right != NULL)
    substitute->right->parent = _target;
  substitute->parent = _target->parent;

  if (_target == _root)
    _root = substitute;
  else if (_target == _target->parent->right)
    _target->parent->right = substitute;
  else
    _target->parent->left = substitute;
  substitute->right = _target;
  _target->parent = substitute;
}

// __rb_tree_rebalance

inline void
__rb_tree_rebalance_when_insertion(__rb_tree_node_base* _inserted, 
                                    __rb_tree_node_base*& _root) {
  _inserted->color = __rb_tree_red;
  while ((_inserted != _root) && (_inserted->parent->color == __rb_tree_red)) {
    if (_inserted->parent == _inserted->parent->parent->left) {
      // left
      __rb_tree_node_base* uncle = _inserted->parent->parent->right;
      if (uncle && uncle->color == __rb_tree_red) {
        // case 1
          // trick: switching colors
        _inserted->parent->color = __rb_tree_black;
        uncle->color = __rb_tree_black;
        _inserted->parent->parent->color = __rb_tree_red;
        _inserted = _inserted->parent->parent;
      }
      else {
        if (_inserted == _inserted->parent->right) {
          // case 2
          _inserted = _inserted->parent;
          __rb_tree_rotate_left(_inserted, _root);
        }
        // case 3
        _inserted->parent->color = __rb_tree_black;
        _inserted->parent->parent->color = __rb_tree_red;
        __rb_tree_rotate_right(_inserted->parent->parent, _root);
      }
    }
    else {
      // right
      __rb_tree_node_base* uncle = _inserted->parent->parent->left;
      if (uncle && uncle->color == __rb_tree_red) {
        // case 1
          // trick: switching colors
        _inserted->parent->color = __rb_tree_black;
        uncle->color = __rb_tree_black;
        _inserted->parent->parent->color = __rb_tree_red;
        _inserted = _inserted->parent->parent;
      }
      else {
        if (_inserted == _inserted->parent->left) {
          // case 2
          _inserted = _inserted->parent;
          __rb_tree_rotate_right(_inserted, _root);
        }
        // case 3
        _inserted->parent->color = __rb_tree_black;
        _inserted->parent->parent->color = __rb_tree_red;
        __rb_tree_rotate_left(_inserted->parent->parent, _root);
      }
    }
  }
  _root->color = __rb_tree_black;
}

inline __rb_tree_node_base*
__rb_tree_rebalance_when_deletion(__rb_tree_node_base* _to_delete,
                                    __rb_tree_node_base*& _root,
                                    __rb_tree_node_base*& _leftmost,
                                    __rb_tree_node_base*& _rightmost) {
  __rb_tree_node_base* del_node =_to_delete;
  __rb_tree_node_base* next = NULL;
  __rb_tree_node_base* next_parent = NULL;

  // Finding the real node to delete
  if (del_node->left == NULL) {
    // When no both children are 
      // or only one right child is.
    next = del_node->right; // null or node
  }
  else {
    if (del_node->right == NULL) {
      // When only one left child is.
      next = del_node->left; // node
    }
    else {
      // When both children are.
      // Finding successor. -> del_node
      del_node = del_node->right;
      while (del_node->left != NULL)
        del_node = del_node->left;
      next = del_node->right;
    }
  }

  // 링크관계 변경 작업: Modifying node linking
  if (del_node != _to_delete) {
    // When del_node is _to_delete's successor
      // _to_delete에 대한 링크관계를 del_node로 대체하는 작업
    _to_delete->left->parent = del_node;
    del_node->left = _to_delete->left;
    if (del_node != _to_delete->right) {
      // When del_node is not direct right child.
      next_parent = del_node->parent;
      if (next) next->parent = del_node->parent;
      del_node->parent->left = next;
      del_node->right = _to_delete->right;
      _to_delete->right->parent = del_node;
    }
    else {
      next_parent = del_node;
    }
    if (_root == _to_delete)
      _root = del_node;
    else if (_to_delete->parent->left == _to_delete)
      _to_delete->parent->left = del_node;
    else
      _to_delete->parent->right = del_node;
    del_node->parent = _to_delete->parent;
    ft::swap(del_node->color, _to_delete->color);
    del_node = _to_delete; // del_node now points to node to be actually deleted
  }
  else {
    // When del_node is _to_delete
    next_parent = del_node->parent;
    if (next) next->parent = del_node->parent;
    if (_root == _to_delete) {
      _root = next;
    }
    else { // parent 간의 링크관계 작업
      if (_to_delete->parent->left == _to_delete)
        _to_delete->parent->left = next;
      else
        _to_delete->parent->right = next;
    }
    if (_leftmost == _to_delete) { // leftmost 변경 작업
      if (_to_delete->right == NULL)
        _leftmost = _to_delete->parent;
      else
        _leftmost = __rb_tree_node_base::minimum(next);
    }
    if (_rightmost == _to_delete) { // rightmost 변경 작업
      if (_to_delete->left == NULL)
        _rightmost = _to_delete->parent;
      else
        _rightmost = __rb_tree_node_base::maximum(next);
    }
  }

  // rebalancing
  if (del_node->color != __rb_tree_red) { // Getting Extra-Black
    while (next != _root && (next == NULL || next->color == __rb_tree_black)) {
      // When Doubly-Black
      if (next == next_parent->left) {
        // left
        __rb_tree_node_base* sibling = next_parent->right;
        if (sibling->color == __rb_tree_red) {
          // case 1
          sibling->color = __rb_tree_black;
          next_parent->color = __rb_tree_red;
          __rb_tree_rotate_left(next_parent, _root);
          sibling = next_parent->right;
        }
        if ((sibling->left == NULL || sibling->left->color == __rb_tree_black) &&
            (sibling->right == NULL || sibling->right->color == __rb_tree_black)) {
          // case 2
            // trick: switching color to bubble up extra-black
          sibling->color = __rb_tree_red;
          next = next_parent;
          next_parent = next_parent->parent;
        }
        else {
          if (sibling->right == NULL || sibling->right->color == __rb_tree_black) {
            // case 3
            if (sibling->left) sibling->left->color = __rb_tree_black; // NOTE: if문이 있을 이유가 있나? red node가 없는 경우도 있는건가?
            sibling->color = __rb_tree_red;
            __rb_tree_rotate_right(sibling, _root);
            sibling = next_parent->right;
          }
          // case 4
          sibling->color = next_parent->color;
          next_parent->color = __rb_tree_black;
          if (sibling->right) sibling->right->color = __rb_tree_black; // NOTE: if문이 있을 이유가 있나? red node가 없는 경우도 있는건가?
          __rb_tree_rotate_left(next_parent, _root);
          break;
        }
      }
      else {
        // right
        __rb_tree_node_base* sibling = next_parent->left;
        if (sibling->color == __rb_tree_red) {
          // case 1
          sibling->color = __rb_tree_black;
          next_parent->color = __rb_tree_red;
          __rb_tree_rotate_right(next_parent, _root);
          sibling = next_parent->left;
        }
        if ((sibling->right == NULL || sibling->right->color == __rb_tree_black) &&
            (sibling->left == NULL || sibling->left->color == __rb_tree_black)) {
          // case 2
            // trick: switching color to bubble up extra-black
          sibling->color = __rb_tree_red;
          next = next_parent;
          next_parent = next_parent->parent;
        }
        else {
          if (sibling->left == NULL || sibling->left->color == __rb_tree_black) {
            // case 3
            if (sibling->right) sibling->right->color = __rb_tree_black; // NOTE: if문이 있을 이유가 있나? red node가 없는 경우도 있는건가?
            sibling->color = __rb_tree_red;
            __rb_tree_rotate_left(sibling, _root);
            sibling = next_parent->left;
          }
          // case 4
          sibling->color = next_parent->color;
          next_parent->color = __rb_tree_black;
          if (sibling->left) sibling->left->color = __rb_tree_black; // NOTE: if문이 있을 이유가 있나? red node가 없는 경우도 있는건가?
          __rb_tree_rotate_right(next_parent, _root);
          break;
        }
      }
    }
    if (next) next->color = __rb_tree_black;
  }
  return del_node;
}

// rb_tree
template <class _Key, class _Value, class _KeyOfValue, class _Compare,
          class _Alloc = std::allocator<_Value> >
class rb_tree {
public:
  typedef _Key                                          key_type;
	typedef _Value                                      	value_type;
  typedef _Compare                                 			key_compare;
  typedef _Alloc                               			    allocator_type;
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
  typedef __rb_tree_node<_Value>                                          rb_tree_node;
  typedef __rb_tree_color_type                                            color_type;
  typedef	typename allocator_type::template rebind<rb_tree_node>::other   node_allocator;
// public:
  typedef rb_tree_node*                                                   link_type; // NOTE: to public?

protected:
  size_type       node_count_; // keeps track of size of tree
  link_type       header_;
  _Compare        key_compare_;
  allocator_type  value_alloc_;
  node_allocator  node_alloc_;

  link_type& root() const { return (link_type&) header_->parent; }
  link_type& leftmost() const { return (link_type&) header_->left; }
  link_type& rightmost() const { return (link_type&) header_->right; }

  static link_type& left(link_type _x) { return (link_type&)(_x->left); }
  static link_type& right(link_type _x) { return (link_type&)(_x->right); }
  static link_type& parent(link_type _x) { return (link_type&)(_x->parent); }
  static reference value(link_type _x) { return _x->value_field; }
  static const _Key& key(link_type _x) { return _KeyOfValue()(value(_x)); }
  static color_type& color(link_type _x) { return (color_type&)(_x->color); }

  static link_type& left(base_ptr _x) { return (link_type&)(_x->left); }
  static link_type& right(base_ptr _x) { return (link_type&)(_x->right); }
  static link_type& parent(base_ptr _x) { return (link_type&)(_x->parent); }
  static reference value(base_ptr _x) { return ((link_type)_x)->value_field; }
  static const _Key& key(base_ptr _x) { return _KeyOfValue()(value(link_type(_x)));} 
  static color_type& color(base_ptr _x) { return (color_type&)(link_type(_x)->color); }

  static link_type minimum(link_type _x) { 
    return (link_type)  __rb_tree_node_base::minimum(_x);
  }
  static link_type maximum(link_type _x) {
    return (link_type) __rb_tree_node_base::maximum(_x);
  }
protected:
  link_type alloc_node() {
    return (node_alloc_.allocate(1));
  }
  void dealloc_node(link_type _p) {
    node_alloc_.deallocate(_p, 1);
  }

  link_type create_node(const value_type& _v) {
    link_type ret = alloc_node();
    try {
      value_alloc_.construct(&(ret->value_field), _v);
    }
    catch(...) { dealloc_node(ret); throw; }
    return ret;
  }

  link_type clone_node(link_type _x) {
    link_type ret = create_node(_x->value_field);
    ret->color = _x->color;
    ret->left = NULL;
    ret->right = NULL;
    return ret;
  }

  void delete_node(link_type _p) {
    value_alloc_.destroy(&(_p->value_field));
    dealloc_node(_p);
  }

private:
  iterator __insert(base_ptr _x, base_ptr _y, const value_type& _v) {
  link_type to_right_if_null = (link_type) _x;
  link_type to_parent = (link_type) _y;
  link_type new_node;

  if (to_parent == header_ || 
      to_right_if_null != NULL || 
      key_compare_(_KeyOfValue()(_v), key(to_parent))) {
    // 아무 노드도 없을 때
    // 첫번째 인자로 주소가 들어왔을 때,
    // 새로 들어온 인자의 key가 두번째 인자보다 작을 때

    // 두번째 인자의 left에 배치
    new_node = create_node(_v);
    left(to_parent) = new_node;
    if (to_parent == header_) {
      // 아무 노드도 없었을 때
      root() = new_node;
      rightmost() = new_node;
    }
    else if (to_parent == leftmost()) {
      leftmost() = new_node;
    }
  }
  else {
    // 두번째 인자의 right에 배치
    new_node = create_node(_v);
    right(to_parent) = new_node;
    if (to_parent == rightmost())
      rightmost() = new_node;
  }
  parent(new_node) = to_parent;
  left(new_node) = NULL;
  right(new_node) = NULL;
  __rb_tree_rebalance_when_insertion(new_node, header_->parent); // NOTE: 여기서 root() 쓰면 컴파일 에러 남;
  ++node_count_;
  return iterator(new_node);
}

  link_type __copy(link_type _x, link_type _p) {
    link_type top = clone_node(_x);
    top->parent = _p;

    try {
      // 오른쪽부터 차례대로 채워감
      if (_x->right)
        top->right = __copy(right(_x), top);
      _p = top;
      _x = left(_x);

      while (_x != NULL) {
        link_type tmp = clone_node(_x);
        _p->left = tmp;
        tmp->parent = _p;
        if (_x->right)
          tmp->right = __copy(right(_x), tmp);
        _p = tmp;
        _x = left(_x);
      }
    }
    catch(...) { __erase(top); throw; }
    return top;
  }

  // erase all
  // erase without rebalancing
  void __erase(link_type _x) {
    while (_x != NULL) {
      __erase(right(_x));
      link_type tmp = left(_x);
      delete_node(_x);
      _x = tmp;
    }
  }

  void __init() {
    // header_ = get_node();
    header_ = alloc_node();
    color(header_) = __rb_tree_red;
    root() = NULL;
    leftmost() = header_;
    rightmost() = header_;
  }
public:
// (Constructor)
  rb_tree(const _Compare& _comp = _Compare()
        , const allocator_type _alloc = _Alloc()
        , const node_allocator _node_alloc = node_allocator() )
      : node_count_(0)
      , header_(NULL)
      , key_compare_(_comp)
      , value_alloc_(_alloc)
      , node_alloc_(_node_alloc)
  { __init(); }
  
  rb_tree(const rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& _x)
    : node_count_(0), key_compare_(_x.key_compare_) {
      header_ = alloc_node();
      color(header_) = __rb_tree_red;
      if (_x.root() == NULL) {
        root() = NULL;
        leftmost() = header_;
        rightmost() = header_;
      }
      else {
        try {
          root() = __copy(_x.root(), header_);
        }
        catch (...) { dealloc_node(header_); throw; }
        leftmost() = minimum(root());
        rightmost() = maximum(root());
      }
      node_count_ = _x.node_count_;
    }

    ~rb_tree() {
      clear();
      dealloc_node(header_);
    }

    rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>&
    operator=(const rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& _x) {
      if (this != &_x) {
        clear();
        node_count_ = 0;
        key_compare_ = _x.key_compare_;
        if (_x.root() == NULL) {
          root() = NULL;
          leftmost() = header_;
          rightmost() = header_;
        }
        else {
          root() = __copy(_x.root(), header_);
          leftmost() = minimum(root());
          rightmost() = maximum(root());
          node_count_ = _x.node_count_;
        }
      }
      return *this;
    }

public:
  _Compare key_comp() const { return key_compare_; }
  iterator begin() { return leftmost(); }
  const_iterator begin() const { return leftmost(); }
  iterator end() { return header_; }
  const_iterator end() const { return header_; }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }
  bool empty() const { return node_count_ == 0; }
  size_type size() const { return node_count_; }
  size_type max_size() const { return size_type(-1); } // NOTE

public:
// For Modifiers
  pair<iterator,bool> insert_unique(const value_type& _v)
  {
    link_type to_parent = header_;
    link_type to_insert = root();
    bool comp = true;
    while (to_insert != NULL)
    {
      to_parent = to_insert;
      comp = key_compare_(_KeyOfValue()(_v), key(to_insert));
      to_insert = comp ? left(to_insert) : right(to_insert);
    }
    iterator to_check = iterator(to_parent);
    if (comp) {
      // value가 to_parent 보다 작은 경우
      if (to_check == begin()) {
        return (pair<iterator,bool>(__insert(to_insert, to_parent, _v), true));
      }
      else {
        --to_check;
      }
    }
    if (key_compare_(key(to_check.node), _KeyOfValue()(_v))) {
      return (pair<iterator,bool>(__insert(to_insert, to_parent, _v), true));
    }
    // 이미 같은 key가 있는 경우
    return (pair<iterator,bool>(to_check, false));
  }
  iterator insert_unique(iterator _position, const value_type& _v) {
    if (_position.node == header_->left) {
      // begin()
      if (size() > 0 && key_compare_(_KeyOfValue()(_v), key(_position.node)))
        return __insert(_position.node, _position.node, _v);
      else
        return (insert_unique(_v).first);
    }
    else if (_position.node == header_) {
      // end()
      if (key_compare_(key(rightmost()), _KeyOfValue()(_v)))
        return __insert(NULL, rightmost(), _v);
      else
        return (insert_unique(_v).first);
    }
    else {
      iterator before = _position;
      --before;
      if (key_compare_(key(before.node), _KeyOfValue()(_v))
          && key_compare_(_KeyOfValue()(_v), key(_position.node))) {
        if (right(before.node) == NULL)
          return __insert(NULL, before.node, _v);
        else
          return __insert(_position.node, _position.node, _v);
      }
    }
  }
  template <class InputIterator>
  void insert_unique(InputIterator _first, InputIterator _last) {
    for ( ; _first != _last; ++_first)
      insert_unique(*_first);
  }

  void erase(iterator _position) {
    link_type to_delete = (link_type) __rb_tree_rebalance_when_deletion(_position.node,
                                                                        header_->parent,
                                                                        header_->left,
                                                                        header_->right);
    delete_node(to_delete);
    --node_count_;
  }
  size_type erase(const key_type& _k) {
    pair<iterator,iterator> p = equal_range(_k);
    size_type n = 0;
    distance(p.first, p.second, n);
    erase(p.first, p.second);
    return n;
  }
  void erase(iterator _first, iterator _last) {
    while (_first != _last) erase(*(_first++));
  }

  void clear() {
    if (node_count_ != 0) {
      __erase(root());
      leftmost() = header_;
      root() = NULL;
      rightmost() = header_;
      node_count_ = 0;
    }
  }

  void swap(rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>& _t) {
    ft::swap(header_, _t.header_);
    ft::swap(node_count_, _t.node_count_);
    ft::swap(key_compare_, _t.key_compare_);
    ft::swap(value_alloc_, _t.value_alloc_); // NOTE
    ft::swap(node_alloc_, _t.node_alloc_); // NOTE
  }

public:
// For Operations
  // find
  iterator find(const key_type& _k) {
    link_type keeping = header_;
    link_type leading = root();

    while (leading != NULL) {
      if (!key_compare_(key(leading), _k)) // 찾는 key가 leading과 같거나 혹은 보다 더 작을때
        keeping = leading, leading = left(leading); // NOTE
      else // 찾는 key가 더 클 때
        leading = right(leading);
    }
    iterator checking = iterator(keeping);
    return ((checking == end() || key_compare_(_k, key(checking.node))) 
            ? end() : checking); // 같은 key를 못 찾은 경우 end()를 반환
  }
  const_iterator find(const key_type& _k) const {
    link_type keeping = header_;
    link_type leading = root();

    while (leading != NULL) {
      if (!key_compare_(key(leading), _k)) // 찾는 key가 leading node와 같거나 혹은 보다 더 작을때
        keeping = leading, leading = left(leading); // NOTE
      else // 찾는 key가 더 클 때
        leading = right(leading);
    }
    iterator checking = iterator(keeping);
    return ((checking == end() || key_compare_(_k, key(checking.node))) 
            ? end() : checking); // 같은 key를 못 찾은 경우 end()를 반환
  }
  // count
  size_type count(const key_type& _k) const {
    ft::pair<const_iterator, const_iterator> p = equal_range(_k);
    size_type n = 0;
    distance(p.first, p.second, n);
    return n;
  }
  // lower_bound: 인자로 들어온 key와 같거나 key 보다 작은 것 중에 가장 큰 것을 반환
  iterator lower_bound(const key_type& _k) {
    link_type keeping = header_;
    link_type leading = root();

    while (leading != NULL) {
      if (!key_compare_(key(leading), _k)) // _k가 같거나 작을 때
        keeping = leading, leading = left(leading);
      else
        leading = right(leading);
    }
    return iterator(keeping);
  }
  const_iterator lower_bound(const key_type& _k) const {
    link_type keeping = header_;
    link_type leading = root();

    while (leading != NULL) {
      if (!key_compare_(key(leading), _k)) // _k가 같거나 작을 때
        keeping = leading, leading = left(leading);
      else
        leading = right(leading);
    }
    return const_iterator(keeping);
  }
  // upper_bound: 인자로 들어온 key 보다 큰 것 중에 가장 작은 것을 반환
  iterator upper_bound(const key_type& _k) {
    link_type keeping = header_;
    link_type leading = root();

    while (leading != NULL) {
      if (key_compare_(_k, key(leading))) // _k가 작을 때
        keeping = leading, leading = left(leading);
      else
        leading = right(leading);
    }
    return iterator(keeping);
  }
  const_iterator upper_bound(const key_type& _k) const {
    link_type keeping = header_;
    link_type leading = root();

    while (leading != NULL) {
      if (key_compare_(_k, key(leading))) // _k가 작을 때
        keeping = leading, leading = left(leading);
      else
        leading = right(leading);
    }
    return const_iterator(keeping);
  }
  // equal_range
  ft::pair<iterator,iterator> equal_range(const key_type& _k) {
    return ft::pair<iterator,iterator>(lower_bound(_k), upper_bound(_k));
  }
  ft::pair<const_iterator,const_iterator> equal_range(const key_type& _k) const {
    return ft::pair<const_iterator,const_iterator>(lower_bound(_k), upper_bound(_k));
  }

public:
// For alloc
  allocator_type alloc() const { return allocator_type(node_alloc_); }

public:
  // Debugging.
  bool __rb_verify() const;
}; // class rb_tree

inline int __black_count(__rb_tree_node_base* _node, __rb_tree_node_base* _root) {
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

template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
bool
rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::__rb_verify() const {
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
    
    if (L && key_compare_(key(x), key(L)))
      return false;
    if (L && key_compare_(key(R), key(x)))
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