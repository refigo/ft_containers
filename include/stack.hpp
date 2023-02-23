#ifndef MGO_STACK_HPP
#define MGO_STACK_HPP

#include "vector.hpp"

namespace ft
{

// stack

template <class _Tp, class _Container = ft::vector<_Tp> >
class stack {
public:
	typedef _Container									container_type;
	typedef typename container_type::value_type			value_type;
	typedef typename container_type::reference			reference;
	typedef typename container_type::const_reference	const_reference;
	typedef typename container_type::size_type			size_type;

protected:
	container_type ctnr_;

public:
	explicit stack (const container_type& _ctnr = container_type())
		: ctnr_(_ctnr) {}


}; // class stack
	
} // namespace ft



#endif