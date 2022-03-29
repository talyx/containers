#ifndef ITERATORS_BST_ITERATOR_HPP_
#define ITERATORS_BST_ITERATOR_HPP_

#include <memory>
#include "../utils/Node.hpp"
#include "./iterator.hpp"

namespace ft {

template <typename T,typename Distance = ptrdiff_t, typename Pointer = T*,
typename Reference = T&, bool isConst = false>
class BST_iterator: public ft::iterator<ft::bidirectional_iterator_tag, T, Distance, Pointer, Reference> {
 public:
	typedef typename ft::conditional<isConst, const T, T>::type			value_type;
	typedef typename ft::conditional<isConst, const ft::Node<T>, Node<T> >::type	node;
	typedef typename ft::conditional<isConst, const Reference, Reference>::type	reference;
	typedef typename ft::conditional<isConst, const Pointer, Pointer>::type		pointer;
	typedef Distance	difference_type;
	typedef size_t		size_type;

 private:
	node * _node_ptr;

 public:
//========================================================================================================
// constructor/destructor
//========================================================================================================
	BST_iterator() { _node_ptr = NULL; }

	BST_iterator(node* const p) { _node_ptr = p; }

	BST_iterator(const BST_iterator& other): _node_ptr(other._node_ptr) {}

	~BST_iterator() {}
//========================================================================================================
// operator overloading
//========================================================================================================
	BST_iterator &operator=(const BST_iterator& other) {
		if (this == &other) return *this;

		_node_ptr = other._node_ptr;
	}

	template<typename t, typename distance, typename pointer,
	typename reference, bool _isConst>
	bool	operator==(const BST_iterator<t, distance, pointer, reference, _isConst> &other) {
		return (_node_ptr == other._node_ptr);
	}
	template<typename t, typename distance, typename pointer,
	typename reference, bool _isConst>
	bool	operator!=(const BST_iterator<t, distance, pointer, reference, _isConst> &other) {
		return (!(_node_ptr == other._node_ptr));
	}

	BST_iterator &operator++() {
		_node_ptr = successor(_node_ptr);
		return (*this);
	}

	BST_iterator operator++(int) {
		BST_iterator tmp(*this);
		++(*this);
		return (tmp);
	}

	BST_iterator &operator--() {
		_node_ptr = predecessor(_node_ptr);
		return (*this);
	}

	BST_iterator operator--(int) {
		BST_iterator tmp(*this);
		--(*this);
		return (tmp);
	}

	reference operator*() {return (_node_ptr->data); }

	pointer operator->() {return (&(_node_ptr->data));}
//========================================================================================================
// funcition
//========================================================================================================
	node* base() { return (_node_ptr); }

	static node* tree_min(node* x) {
		while (x->left != NULL)
			x = x->left;
		return (x);
	}

	static node* tree_max(node* x) {

		while (x->right != NULL)
			x = x->right;
		return (x);
	}

	node* successor(node* x) {
		if (x->right != NULL)
			return tree_min(x->right);
		node* y = x->parent;
		while (y != NULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	node* predecessor(node* x) {
		if (x->left != NULL)
			return tree_max(x->left);
		node* y = x->parent;
		while (y != NULL && x == y->left) {
			x = y;
			y = y->parent;
		}
		return (y);
	}
}; // class BST_iterator
} // namespace ft

#endif // ITERATORS_BST_ITERATOR_HPP_
