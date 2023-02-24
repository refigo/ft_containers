#ifndef MGO_STACK_HPP_
#define MGO_STACK_HPP_

#include "vector.hpp"

namespace ft
{

// stack

template <class _Tp, class _Container = ft::vector<_Tp> >
class stack {
public:
	typedef _Container																container_type;
	typedef typename container_type::value_type				value_type;
	typedef typename container_type::reference				reference;
	typedef typename container_type::const_reference	const_reference;
	typedef typename container_type::size_type				size_type;

protected:
	container_type c;

public:
// (constructor)
	explicit stack (const container_type& _ctnr = container_type())
		: c(_ctnr) {}

// operator=
	stack& operator=(const stack& _other) {
		if (this != &_other)
			c = _other.c;
		return *this;
	}

// Element access:
	// top
	reference top()							      { return c.back(); }
	const_reference top() const		    { return c.back(); }

// Capacity:
	// empty
	bool empty() const						    { return c.empty(); }
	// size
	size_type size() const				    { return c.size(); }

// Modifiers:
	// push
	void push(const value_type& _v) 	{ c.push_back(_v); }
	// pop
	void pop() 						        		{ c.pop_back(); }

// Relational operators
	bool operator==(const stack<_Tp, _Container>& _other) const { 
		return (c == _other.c); }
	bool operator< (const stack<_Tp, _Container>& _other) const {
		return (c < _other.c); }
	bool operator!=(const stack<_Tp, _Container>& _other) const {
		return !(*this == _other); }
	bool operator> (const stack<_Tp, _Container>& _other) const {
		return (_other < *this); }
	bool operator>=(const stack<_Tp, _Container>& _other) const {
		return !(*this < _other); }
	bool operator<=(const stack<_Tp, _Container>& _other) const {
		return !(_other < *this); }

}; // class stack

} // namespace ft

#endif /* MGO_STACK_HPP_ */