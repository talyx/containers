#ifndef UTILS_BINTREE_HPP_
#define UTILS_BINTREE_HPP_

#include <iostream>
#include <memory>
#include "./Node.hpp"
#include "./utils.hpp"

namespace ft {

template < class T, class Compare = ft::less<T>, class _Node = ft::Node<T>,
class Allocator = std::allocator<T>, class Node_allocator = std::allocator<_Node> >
struct BinTree {
 public:
	typedef T		value_type;
	typedef Compare		comp;
	typedef _Node		node;
	typedef Allocator	alloc;
	typedef Node_allocator	node_alloc;
	typedef node*		node_pointer;
	typedef node_pointer*	head;

 private:
	head _head;
	node_alloc	_n_allocator;
	alloc		_allocator;

 public:
//========================================================
// constructor/destructor
//========================================================
	BinTree(const node_alloc& al = node_alloc()): _n_allocator(al) {
		*_head = NULL;
	}

	~BinTree() {rec_delete(*_head); }

//========================================================
// funcition
//========================================================
	void	insert(const value_type &val) {
		node_pointer y = NULL;
		node_pointer x = *_head;

		while (x != NULL) {
			y = x;
			if (val < x->data)
				x = x->left;
			else
				x = x->right;
		}
		if (y != NULL && y->data.first == val.first) {
			std::cout << "Value with this key(" << val.first << ") already exists\n";
			return;
		}

		node_pointer new_node = _n_allocator.allocate(1);
		_n_allocator.construct(new_node, node(val));
		if (y == NULL) {
			*_head = new_node;
		} else {
			new_node->parent = y;
			if (new_node->data < y->data)
				y->left = new_node;
			else
				y->right = new_node;
		}
	}

	void	print() {
		node_pointer x = *_head;

		rec_print(x);
	}

	node_pointer search_by_key(const value_type &val) {
		node_pointer x = *_head;

		while (x != NULL && val.first != x->data.first) {
			if (val < x->data)
				x = x->left;
			else
				x = x->right;
		}
		return (x);
	}

	node_pointer min() {
		node_pointer x = *_head;

		while (x->left != NULL)
			x = x->left;
		return (x);
	}

	node_pointer max() {
		node_pointer x = *_head;

		while (x->right != NULL)
			x = x->right;
		return (x);
	}

 private:
	void rec_print(node_pointer n) {
		if (n != NULL) {
			rec_print(n->left);
			std::cout << n->data.first << " " << n->data.second << std::endl;
			rec_print(n->right);
		}
	}

	void rec_delete(node_pointer n) {
		if (n != NULL) {
			rec_delete(n->left);
			rec_delete(n->right);
			_n_allocator.destroy(n);
			_n_allocator.deallocate(n, 1);
		}
	}
};

} // namespace ft

#endif // UTILS_BINTREE_HPP_
