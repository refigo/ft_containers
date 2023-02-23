#ifndef __MGO_MAP_HPP_
#define __MGO_MAP_HPP_

#include "pair.hpp"
#include "iterator.hpp"
#include "rb_tree.hpp"
#include "__utils.hpp"

#include <memory>

#include <algorithm> // TODO: remove

namespace ft
{

template <class _Key, class _Tp, class _Compare = ft::less<_Key>,
          class _Allocator = std::allocator<ft::pair<const _Key, _Tp> > >
class map
{
public:
    typedef _Key                                     	key_type;
    typedef _Tp                                      	mapped_type;
    typedef ft::pair<const key_type, mapped_type>		  value_type;
    typedef _Compare                                 	key_compare;

    class value_compare
        : public ft::binary_function<value_type, value_type, bool>
    {
        friend class map;
    protected:
        key_compare comp;

        value_compare(key_compare c) : comp(c) {}
    public:
        bool operator()(const value_type& __x, const value_type& __y) const
            {return comp(__x.first, __y.first);}
    };

private:
    typedef ft::pair<key_type, mapped_type>				__value_type;
    // typedef value_compare													__vc;
    typedef _Allocator														__allocator_type;
    typedef ft::rb_tree<key_type, value_type, 
            ft::select1st<value_type>, key_compare, __allocator_type>			__base;
    __base __tree_;

public:
    typedef _Allocator                              allocator_type;
  typedef typename __base::pointer					        pointer;
  typedef typename __base::const_pointer 				    const_pointer;
  typedef typename __base::reference					      reference;
  typedef typename __base::const_reference			    const_reference;
  typedef typename __base::iterator					        iterator;
  typedef typename __base::const_iterator				    const_iterator;
  typedef typename __base::reverse_iterator			    reverse_iterator;
  typedef typename __base::const_reverse_iterator		const_reverse_iterator;
  typedef typename __base::size_type					      size_type;
  typedef typename __base::difference_type			    difference_type;

public:
// (Constructor)
  // empty (1)
  explicit map(const key_compare& _comp = key_compare()
             , const allocator_type& _alloc = allocator_type())
    : __tree_(_comp, _alloc) {}
  // range (2)
  template <class InputIterator>
  map (InputIterator _first, InputIterator _last,
       const key_compare& _comp = key_compare(),
       const allocator_type& _alloc = allocator_type())
    : __tree_(_comp, _alloc) { __tree_.insert_unique(_first, _last); }
  // copy (3)
  map (const map<_Key, _Tp, _Compare, _Allocator>& _x) : __tree_(_x.__tree_) {}

// operator=
  map<_Key, _Tp, _Compare, _Allocator>&
  operator=(const map<_Key, _Tp, _Compare, _Allocator>& _x) {
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

// Element access:
  // operator[]
  _Tp& operator[](const key_type& _k) {
    return ((*((insert(value_type(_k, _Tp()))).first)).second);
  }

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
  size_type erase(const key_type& _x) { return __tree_.erase(_x); }
  void erase(iterator _first, iterator _last) { __tree_.erase(_first, _last); }
  // swap
  void swap(map<_Key, _Tp, _Compare, _Allocator>& _m) { __tree_.swap(_m.__tree_); }
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
  size_type count(const key_type& _k) { return __tree_.count(_k); }
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

// TODO: remove
public:
  bool test_rb_tree() {return (__tree_.__rb_verify()); }
};

} // namespace ft

#endif /* __MGO_MAP_HPP_ */