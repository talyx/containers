#ifndef ITERATORS_BST_ITERATOR_HPP_
#define ITERATORS_BST_ITERATOR_HPP_

#include <memory>
#include "../utils/BinTree.hpp"
#include "./iterator.hpp"

namespace ft {

template <typename T, typename Compare = ft::less<T>, typename _Node = ft::Node<T>,
typename Allocator = std::allocator<T>, typename _node_alloc = std::allocator<_Node>, bool isConst = false>
class BST_iterator: public ft::iterator< ft::bidirectional_iterator_tag, T> {

 public:
	typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type
									difference_type;
	typedef bidirectional_iterator_tag				iterator_category;
	typedef typename ft::conditional<isConst, const T, T>::type	value_type;
	typedef typename ft::conditional<isConst, const T&, T&>::type	reference;
	typedef typename ft::conditional<isConst, const T*, T*>::type	pointer;
	typedef _Node		node;
	typedef node*		node_pointer;
	typedef Allocator	alloc;
	typedef _node_alloc	node_alloc;
	typedef Compare		compare;
	typedef BST_iterator	self;
	typedef self&		self_r;
	typedef self*		self_p;
	typedef const BST_iterator	self_c;
	typedef const BST_iterator&	self_cr;
	typedef const BST_iterator*	sefl_cp;
 private:
	node_pointer	_node_ptr;
	node_pointer	_root;
	compare		cmp;

 public:
//========================================================================================================
// constructor/destructor
//========================================================================================================

	BST_iterator(node_pointer node_ptr, node_pointer root, compare cmp):
	    _node_ptr(node_ptr), _root(root), cmp(cmp) { }

	explicit BST_iterator(self_cr o): _node_ptr(o._node_ptr),
		_root(o._root), cmp(o.cmp) { }

	self_r operator=(self_cr o) {
		if (this == &o) return *this;

		_node_ptr = o._node_ptr;
		_root = o._root;
		cmp = o.cmp;
		return *this;
	}

	~BST_iterator() {}




}; // class BST_iterator

} // namespace ft

#endif // ITERATORS_BST_ITERATOR_HPP_
