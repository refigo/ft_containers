#ifndef MGO_MAP_HPP_
#define MGO_MAP_HPP_

#include "__functional_base.hpp"
#include "pair.hpp"
#include "iterator.hpp"
#include "__rb_tree.hpp"

#include <memory>

#include <algorithm> // TODO: remove

namespace ft
{

// is_emptys는 C++11 이다.

// template <class _Key, class _Tp, class _Compare, bool = std::is_empty<_Compare>::value>
// class __map_value_compare
//     : private _Compare
// {
//     typedef pair<_Key, _Tp> _P;
//     typedef pair<const _Key, _Tp> _CP;
// public:
//     __map_value_compare() : _Compare() {}
//     __map_value_compare(_Compare c) : _Compare(c) {}
//     const _Compare& key_comp() const {return *this;}
//     bool operator()(const _CP& __x, const _CP& __y) const
//         {return static_cast<const _Compare&>(*this)(__x.first, __y.first);}
//     bool operator()(const _CP& __x, const _P& __y) const
//         {return static_cast<const _Compare&>(*this)(__x.first, __y.first);}
//     bool operator()(const _CP& __x, const _Key& __y) const
//         {return static_cast<const _Compare&>(*this)(__x.first, __y);}
//     bool operator()(const _P& __x, const _CP& __y) const
//         {return static_cast<const _Compare&>(*this)(__x.first, __y.first);}
//     bool operator()(const _P& __x, const _P& __y) const
//         {return static_cast<const _Compare&>(*this)(__x.first, __y.first);}
//     bool operator()(const _P& __x, const _Key& __y) const
//         {return static_cast<const _Compare&>(*this)(__x.first, __y);}
//     bool operator()(const _Key& __x, const _CP& __y) const
//         {return static_cast<const _Compare&>(*this)(__x, __y.first);}
//     bool operator()(const _Key& __x, const _P& __y) const
//         {return static_cast<const _Compare&>(*this)(__x, __y.first);}
//     bool operator()(const _Key& __x, const _Key& __y) const
//         {return static_cast<const _Compare&>(*this)(__x, __y);}



// //     bool operator()(const _Tp& __x, const _Tp& __y) const
// //         {return static_cast<const _Compare&>(*this)(__x.first, __y.first);}
// //     bool operator()(const typename _Tp::first_type& __x, const _Tp& __y) const
// //         {return static_cast<const _Compare&>(*this)(__x, __y.first);}
// //     bool operator()(const _Tp& __x, const typename _Tp::first_type& __y) const
// //         {return static_cast<const _Compare&>(*this)(__x.first, __y);}
// //     bool operator()(const typename _Tp::first_type& __x,
// //                     const typename _Tp::first_type& __y) const
// //         {return static_cast<const _Compare&>(*this)(__x, __y);}
// };

// map_iterator

// template <class _TreeIterator>
// class __map_iterator
// {
//     _TreeIterator __i_;

//     typedef typename _TreeIterator::__pointer_traits             __pointer_traits;
//     typedef const typename _TreeIterator::value_type::first_type key_type;
//     typedef typename _TreeIterator::value_type::second_type      mapped_type;
// public:
//     typedef bidirectional_iterator_tag                           iterator_category;
//     typedef pair<key_type, mapped_type>                          value_type;
//     typedef typename _TreeIterator::difference_type              difference_type;
//     typedef value_type&                                          reference;
//     typedef typename __pointer_traits::template
// #ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
//             rebind<value_type>
// #else
//             rebind<value_type>::other
// #endif
//                                                                  pointer;

//     __map_iterator() {}

//     __map_iterator(_TreeIterator __i) : __i_(__i) {}

//     reference operator*() const {return *operator->();}
//     pointer operator->() const {return (pointer)__i_.operator->();}

//     __map_iterator& operator++() {++__i_; return *this;}
//     __map_iterator operator++(int)
//     {
//         __map_iterator __t(*this);
//         ++(*this);
//         return __t;
//     }

//     __map_iterator& operator--() {--__i_; return *this;}
//     __map_iterator operator--(int)
//     {
//         __map_iterator __t(*this);
//         --(*this);
//         return __t;
//     }

//     friend bool operator==(const __map_iterator& __x, const __map_iterator& __y)
//         {return __x.__i_ == __y.__i_;}
//     friend bool operator!=(const __map_iterator& __x, const __map_iterator& __y)
//         {return __x.__i_ != __y.__i_;}

//     template <class, class, class, class> friend class map;
//     template <class, class, class, class> friend class multimap;
//     template <class> friend class __map_const_iterator;
// };

// template <class _TreeIterator>
// class __map_const_iterator
// {
//     _TreeIterator __i_;

//     typedef typename _TreeIterator::__pointer_traits             __pointer_traits;
//     typedef const typename _TreeIterator::value_type::first_type key_type;
//     typedef typename _TreeIterator::value_type::second_type      mapped_type;
// public:
//     typedef bidirectional_iterator_tag                           iterator_category;
//     typedef pair<key_type, mapped_type>                          value_type;
//     typedef typename _TreeIterator::difference_type              difference_type;
//     typedef const value_type&                                    reference;
//     typedef typename __pointer_traits::template
// #ifndef _LIBCPP_HAS_NO_TEMPLATE_ALIASES
//             rebind<value_type>
// #else
//             rebind<value_type>::other
// #endif
//                                                                  pointer;

//     __map_const_iterator() {}

//     __map_const_iterator(_TreeIterator __i) : __i_(__i) {}
//     __map_const_iterator(
//             __map_iterator<typename _TreeIterator::__non_const_iterator> __i)
//                 : __i_(__i.__i_) {}

//     reference operator*() const {return *operator->();}
//     pointer operator->() const {return (pointer)__i_.operator->();}

//     __map_const_iterator& operator++() {++__i_; return *this;}
//     __map_const_iterator operator++(int)
//     {
//         __map_const_iterator __t(*this);
//         ++(*this);
//         return __t;
//     }

//     __map_const_iterator& operator--() {--__i_; return *this;}
//     __map_const_iterator operator--(int)
//     {
//         __map_const_iterator __t(*this);
//         --(*this);
//         return __t;
//     }

//     friend bool operator==(const __map_const_iterator& __x, const __map_const_iterator& __y)
//         {return __x.__i_ == __y.__i_;}
//     friend bool operator!=(const __map_const_iterator& __x, const __map_const_iterator& __y)
//         {return __x.__i_ != __y.__i_;}

//     template <class, class, class, class> friend class map;
//     template <class, class, class, class> friend class multimap;
//     template <class, class, class> friend class __tree_const_iterator;
// };


template <class _Key, class _Tp, class _Compare = ft::less<_Key>,
          class _Allocator = std::allocator<ft::pair<const _Key, _Tp> > >
class map
{
public:
    // types:
    typedef _Key                                     	key_type;
    typedef _Tp                                      	mapped_type;
    typedef ft::pair<const key_type, mapped_type>		value_type;
    typedef _Compare                                 	key_compare;
    typedef _Allocator                               	allocator_type;
    typedef value_type&                                 reference;
    typedef const value_type&                           const_reference;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef typename allocator_type::size_type          size_type;
    typedef typename allocator_type::difference_type    difference_type;

    typedef ft::__rb_tree_iterator<value_type>      	iterator;
    typedef ft::__rb_tree_iterator<const value_type>    const_iterator;

    // typedef ft::__map_iterator<typename __base::iterator>      			iterator;
    // typedef ft::__map_const_iterator<typename __base::const_iterator> 	const_iterator;
    // typedef ft::reverse_iterator<iterator>               				reverse_iterator;
    // typedef ft::reverse_iterator<const_iterator>         				const_reverse_iterator;
    

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
    typedef ft::pair<key_type, mapped_type>									__value_type;
    typedef value_compare													__vc;
    typedef _Allocator														__allocator_type;
    typedef ft::__rb_tree<__value_type, __vc, __allocator_type>				__base;
    // typedef typename __base::__node_traits                 __node_traits;
    // typedef allocator_traits<allocator_type>               __alloc_traits;

    __base __tree_;

public:
    // typedef typename allocator_type::pointer               				pointer;
    // typedef typename allocator_type::const_pointer         				const_pointer;
    // typedef typename allocator_type::size_type             				size_type;
    // typedef typename allocator_type::difference_type       				difference_type;

    // typedef ft::__map_iterator<typename __base::iterator>      			iterator;
    // typedef ft::__map_const_iterator<typename __base::const_iterator> 	const_iterator;
    // typedef ft::reverse_iterator<iterator>               				reverse_iterator;
    // typedef ft::reverse_iterator<const_iterator>         				const_reverse_iterator;
    
    // typedef ft::__rb_tree_iterator<__value_type>      			iterator;


    // empty (1)
    explicit map(const key_compare& __comp = key_compare(), 
                    const allocator_type& __a = allocator_type())
        : __tree_(__vc(__comp), __a) {}
    // explicit map(const key_compare& __comp = key_compare())
    //     : __tree_(__vc(__comp)) {}
    // explicit map(const key_compare& __comp, const allocator_type& __a)
    //     : __tree_(__vc(__comp), __a) {}

    // range (2)
    // template <class _InputIterator>
    //     map(_InputIterator __f, _InputIterator __l,
    //         const key_compare& __comp = key_compare())
    //     : __tree_(__vc(__comp))
    //     {
    //         insert(__f, __l);
    //     }

    // template <class _InputIterator>
    //     map(_InputIterator __f, _InputIterator __l,
    //         const key_compare& __comp, const allocator_type& __a)
    //     : __tree_(__vc(__comp), __a)
    //     {
    //         insert(__f, __l);
    //     }

    // copy (3)
    // map(const map& __m)
    //     : __tree_(__m.__tree_)
    //     {
    //         insert(__m.begin(), __m.end());
    //     }


    //       iterator begin()       {return __tree_.begin();}
    // const_iterator begin() const {return __tree_.begin();}
    //       iterator end()         {return __tree_.end();}
    // const_iterator end()   const {return __tree_.end();}

    //       reverse_iterator rbegin()       {return       reverse_iterator(end());}
    // const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
    //       reverse_iterator rend()         {return       reverse_iterator(begin());}
    // const_reverse_iterator rend()   const {return const_reverse_iterator(begin());}

    // const_iterator         cbegin()  const {return begin();}
    // const_iterator         cend()    const {return end();}
    // const_reverse_iterator crbegin() const {return rbegin();}
    // const_reverse_iterator crend()   const {return rend();}

    // bool      empty()    const {return __tree_.size() == 0;}
    // size_type size()     const {return __tree_.size();}
    // size_type max_size() const {return __tree_.max_size();}

    // mapped_type& operator[](const key_type& __k);

    //       mapped_type& at(const key_type& __k);
    // const mapped_type& at(const key_type& __k) const;

    // allocator_type get_allocator() const {return __tree_.__alloc();}
    // key_compare    key_comp()      const {return __tree_.value_comp().key_comp();}
    // value_compare  value_comp()    const {return value_compare(__tree_.value_comp().key_comp());}

// Modifiers:
    // insert
        // single element (1)
    pair<iterator, bool>
        insert(const value_type& __v) {return __tree_.__insert_unique(__v);}
    
        // with hint (2)
        // range (3)

// Operations:
    // find
    iterator find(const key_type& __k)             {return __tree_.find(__k);}
    const_iterator find(const key_type& __k) const {return __tree_.find(__k);}

// ref (clang)
    // pair<iterator, bool>
    //     insert(const value_type& __v) {return __tree_.__insert_unique(__v);}

    // iterator
    //     insert(const_iterator __p, const value_type& __v)
    //         {return __tree_.__insert_unique(__p.__i_, __v);}

    // template <class _InputIterator>
    //     void insert(_InputIterator __f, _InputIterator __l)
    //     {
    //         for (const_iterator __e = cend(); __f != __l; ++__f)
    //             insert(__e.__i_, *__f);
    //     }

    // void insert(initializer_list<value_type> __il)
    //     {insert(__il.begin(), __il.end());}

    // iterator erase(const_iterator __p) {return __tree_.erase(__p.__i_);}
    // size_type erase(const key_type& __k)
    //     {return __tree_.__erase_unique(__k);}
    // iterator  erase(const_iterator __f, const_iterator __l)
    //     {return __tree_.erase(__f.__i_, __l.__i_);}
    // void clear() {__tree_.clear();}

    // void swap(map& __m) {__tree_.swap(__m.__tree_);}

    // iterator find(const key_type& __k)             {return __tree_.find(__k);}
    // const_iterator find(const key_type& __k) const {return __tree_.find(__k);}
    // size_type      count(const key_type& __k) const
    //     {return __tree_.__count_unique(__k);}
    // iterator lower_bound(const key_type& __k)
    //     {return __tree_.lower_bound(__k);}
    // const_iterator lower_bound(const key_type& __k) const
    //     {return __tree_.lower_bound(__k);}
    // iterator upper_bound(const key_type& __k)
    //     {return __tree_.upper_bound(__k);}
    // const_iterator upper_bound(const key_type& __k) const
    //     {return __tree_.upper_bound(__k);}
    // pair<iterator,iterator> equal_range(const key_type& __k)
    //     {return __tree_.__equal_range_unique(__k);}
    // pair<const_iterator,const_iterator> equal_range(const key_type& __k) const
    //     {return __tree_.__equal_range_unique(__k);}

// private:
    // typedef typename __base::__node                    __node;
    // typedef typename __base::__node_allocator          __node_allocator;
    // typedef typename __base::__node_pointer            __node_pointer;
    // typedef typename __base::__node_const_pointer      __node_const_pointer;
    // typedef typename __base::__node_base_pointer       __node_base_pointer;
    // typedef typename __base::__node_base_const_pointer __node_base_const_pointer;
    // typedef __map_node_destructor<__node_allocator> _D;
    // typedef unique_ptr<__node, _D> __node_holder;
};

} // namespace ft

#endif /* MGO_MAP_HPP_ */