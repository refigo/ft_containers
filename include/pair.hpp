#ifndef MGO_PAIR_HPP_
#define MGO_PAIR_HPP_

namespace ft {

// pair

template <class _T1, class _T2>
struct pair
{
	typedef _T1 first_type;
	typedef _T2 second_type;

	_T1	first;
	_T2	second;

// (Construct)
	// default (1)
	pair() : first(), second() {}
	// copy (2)
	pair(const _T1& __x, const _T2& __y)
		: first(__x), second(__y) {}
	// initialization (3)
	template<class _U1, class _U2>
	pair(const pair<_U1, _U2>& __p)
		: first(__p.first), second(__p.second) {}
};

// relational operators (pair)
template <class _T1, class _T2>
inline
bool
operator==(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y) {
  return (__x.first == __y.first && __x.second == __y.second);
}

template <class _T1, class _T2>
inline
bool
operator!=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y) {
  return !(__x == __y);
}

template <class _T1, class _T2>
inline
bool
operator< (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y) {
  return (__x.first < __y.first || (!(__y.first < __x.first) && __x.second < __y.second));
}

template <class _T1, class _T2>
inline
bool
operator> (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y) {
  return (__y < __x);
}

template <class _T1, class _T2>
inline
bool
operator>=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y) {
  return !(__x < __y);
}

template <class _T1, class _T2>
inline
bool
operator<=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y) {
  return !(__y < __x);
}

// make_pair

template <class _T1, class _T2>
inline
pair<_T1,_T2>
make_pair(_T1 __x, _T2 __y) {
  return (ft::pair<_T1, _T2>(__x, __y));
}

} // namespace ft

#endif /* MGO_PAIR_HPP_ */