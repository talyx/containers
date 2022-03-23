#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>
#include <memory>
#include "./utils/utils.hpp"
#include "iterators/reverse_iterator.hpp"

namespace ft {
template < class Key, class T, class Compare = ft::less<Key>,
	 class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
 public:
	typedef Key					key_type;
	typedef T					mapped_type;
	typedef ft::pair<const Key, T>			value_type;
	typedef size_t					size_type;
	typedef ptrdiff_t				difference_type;
	typedef Compare					key_compare;
	typedef Allocator				allocator_type;
	typedef value_type&				reference;
	typedef const value_type&			const_reference;
	typedef typename Allocator::pointer		pointer;
	typedef typename Allocator::const_pointer	const_pointer;

	class value_compare :
	public ft::binary_function < value_type, value_type, bool> {
	 protected:
		Compare comp;
		value_compare (Compare c): comp(c) { }
	 public:
		bool operator() (const value_type &a, const value_type &b) const {
			return (comp(a.first, b.first));
		}
	};

//========================================================================================================
// constructor/destructor
//========================================================================================================



}; // class map
} // namespace ft

#endif // MAP_HPP_
