#ifndef MGO_SET_HPP_
#define MGO_SET_HPP_

#include "rb_tree.hpp"
#include "utils.hpp"
#include "algorithm.hpp"
#include "pair.hpp"
#include <memory>

namespace ft
{

// set

template <class _Key, class _Compare = ft::less<_Key>,
          class _Alloc = std::allocator<_Key> >
class set {
public:
  // typedefs:

  typedef _Key key_type;
  typedef _Key value_type;
  typedef _Compare key_compare;
  typedef _Compare value_compare;
  typedef _Alloc                                    allocator_type;
private:
  typedef rb_tree<key_type, value_type, 
                  ft::identity<value_type>, key_compare, _Alloc> __base;
  __base __tree_;  // red-black tree representing set
public: 
  typedef typename __base::const_pointer pointer;
  typedef typename __base::const_pointer const_pointer;
  typedef typename __base::const_reference reference;
  typedef typename __base::const_reference const_reference;
  typedef typename __base::const_iterator iterator;
  typedef typename __base::const_iterator const_iterator;
  typedef typename __base::const_reverse_iterator reverse_iterator;
  typedef typename __base::const_reverse_iterator const_reverse_iterator;
  typedef typename __base::size_type size_type;
  typedef typename __base::difference_type difference_type;

public:
// (Constructor)
  // empty (1)
  explicit set(const key_compare& _comp = key_compare()
             , const allocator_type& _alloc = allocator_type())
    : __tree_(_comp, _alloc) {}
  // range (2)
  template <class InputIterator>
  set (InputIterator _first, InputIterator _last,
       const key_compare& _comp = key_compare(),
       const allocator_type& _alloc = allocator_type())
    : __tree_(_comp, _alloc) { __tree_.insert_unique(_first, _last); }
  // copy (3)
  set (const set<_Key, _Compare, _Alloc>& _x) : __tree_(_x.__tree_) {}

// operator=
  set<_Key, _Compare, _Alloc>&
  operator=(const set<_Key, _Compare, _Alloc>& _x) {
    __tree_ = _x.__tree_;
    return *this;
  }

// Iterators:
  // begin
  iterator begin() { return __tree_.begin(); }
  const_iterator begin() const { return __tree_.begin(); }
  // end
  iterator end() { return __tree_.end(); }
  const_iterator end() const { return __tree_.end(); }
  // rbegin
  reverse_iterator rbegin() { return __tree_.rbegin(); }
  const_reverse_iterator rbegin() const { return __tree_.rbegin(); }
  // rend
  reverse_iterator rend() { return __tree_.rend(); }
  const_reverse_iterator rend() const { return __tree_.rend(); }

// Capacity:
  // empty
  bool empty() const { return __tree_.empty(); }
  // size
  size_type size() const { return __tree_.size(); }
  // max_size
  size_type max_size() const { return __tree_.max_size(); }

// Modifiers:
  // insert
    // single element (1)
  pair<iterator, bool>
    insert(const value_type& _v) {return (__tree_.insert_unique(_v));}
    // with hint (2)
  iterator insert(iterator _position, const value_type& _v) {
    return (__tree_.insert_unique(_position, _v));
  }
    // range (3)
  template <class InputIterator>
  void insert(InputIterator _first, InputIterator _last) {
    __tree_.insert_unique(_first, _last);
  }
  // erase
  void erase(iterator _position) { __tree_.erase(_position); }
  size_type erase(const key_type& _k) { return __tree_.erase(_k); }
  void erase(iterator _first, iterator _last) { __tree_.erase(_first, _last); }
  // swap
  void swap(set<_Key, _Compare, _Alloc>& _s) { __tree_.swap(_s.__tree_); }
  // clear
  void clear() { __tree_.clear(); }

// Observers:
  // key_comp
  key_compare key_comp() const { return __tree_.key_comp(); }
  // value_comp
  value_compare value_comp() const { return value_compare(__tree_.key_comp()); }

// Operations:
  // find
  iterator find(const key_type& _k)             {return __tree_.find(_k);}
  const_iterator find(const key_type& _k) const {return __tree_.find(_k);}
  // count
  size_type count(const key_type& _k) const { return __tree_.count(_k); }
  // lower_bound
  iterator lower_bound(const key_type& _k) { return __tree_.lower_bound(_k); }
  const_iterator lower_bound(const key_type& _k) const {
    return __tree_.lower_bound(_k);
  }
  // upper_bound
  iterator upper_bound(const key_type& _k) { return __tree_.upper_bound(_k); }
  const_iterator upper_bound(const key_type& _k) const {
    return __tree_.upper_bound(_k);
  }
  // equal_range
  ft::pair<iterator,iterator> equal_range(const key_type& _k) {
    return __tree_.equal_range(_k);
  }
  ft::pair<const_iterator,const_iterator> equal_range(const key_type& _k) const {
    return __tree_.equal_range(_k);
  }

// Allocator:
  // get_allocator
  allocator_type get_allocator() { return allocator_type(__tree_.alloc()); } // NOTE


}; // class set

// Non-member functions for map
template <class _Key, class _Compare, class _Alloc>
inline
bool
operator==(const set<_Key, _Compare, _Alloc>& _lhs,
           const set<_Key, _Compare, _Alloc>& _rhs) {
	return (_lhs.size() == _rhs.size() && ft::equal(_lhs.begin(), _lhs.end(), _rhs.begin()));
}

template <class _Key, class _Compare, class _Alloc>
inline
bool
operator< (const set<_Key, _Compare, _Alloc>& _lhs,
           const set<_Key, _Compare, _Alloc>& _rhs) {
	return ft::lexicographical_compare(_lhs.begin(), _lhs.end(), _rhs.begin(), _rhs.end());
}

template <class _Key, class _Compare, class _Alloc>
inline
bool
operator!=(const set<_Key, _Compare, _Alloc>& _lhs,
           const set<_Key, _Compare, _Alloc>& _rhs) {
	return !(_lhs == _rhs);
}

template <class _Key, class _Compare, class _Alloc>
inline
bool
operator> (const set<_Key, _Compare, _Alloc>& _lhs,
           const set<_Key, _Compare, _Alloc>& _rhs) {
	return _rhs < _lhs;
}

template <class _Key, class _Compare, class _Alloc>
inline
bool
operator>=(const set<_Key, _Compare, _Alloc>& _lhs,
           const set<_Key, _Compare, _Alloc>& _rhs) {
	return !(_lhs < _rhs);
}

template <class _Key, class _Compare, class _Alloc>
inline
bool
operator<=(const set<_Key, _Compare, _Alloc>& _lhs,
           const set<_Key, _Compare, _Alloc>& _rhs) {
	return !(_rhs < _lhs);
}

template <class _Key, class _Compare, class _Alloc>
inline
void
swap(set<_Key, _Compare, _Alloc>& _x,
     set<_Key, _Compare, _Alloc>& _y) {
  _x.swap(_y);
}

} // namespace ft

#endif /* MGO_SET_HPP_ */