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
	container_type ctnr_;

public:
// (constructor)
	explicit stack (const container_type& _ctnr = container_type())
		: ctnr_(_ctnr) {}

// operator=
	stack& operator=(const stack& _other) {
		if (this != &_other)
			ctnr_ = _other.ctnr_;
		return *this;
	}

// Element access:
	// top
	reference top()							{ return ctnr_.back(); }
	const_reference top() const	{ return ctnr_.back(); }

// Capacity:
	// empty
	bool empty() const					{ return ctnr_.empty(); }
	// size
	size_type size() const			{ return ctnr_.size(); }

// Modifiers:
	// push
	void push(const value_type& _v) { ctnr_.push_back(_v); }
	// pop
	void pop() { ctnr_.pop_back(); }

// Relational operators
	bool operator==(const stack<_Tp, _Container>& _other) const { 
		return (ctnr_ == _other.ctnr_); }
	bool operator< (const stack<_Tp, _Container>& _other) const {
		return (ctnr_ < _other.ctnr_); }
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