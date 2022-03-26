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
	explicit BinTree(const node_alloc& al = node_alloc()): _n_allocator(al) {
		*_head = NULL;
	}

	~BinTree() {rec_delete(*_head); }

//========================================================
// insert/remove
//========================================================
	ft::pair<node_pointer, bool> insert(const value_type &val) {
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
			return ft::make_pair(y, false);
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
		return (ft::make_pair(new_node, true));
	}

	void	remove(const value_type &val) {
		node_pointer tmp = search_by_key(val);

		if (tmp->left == NULL) {
			transplant(tmp, tmp->right);
		} else if (tmp->right == NULL) {
			transplant(tmp, tmp->left);
		} else {
			node_pointer y = tree_min(tmp->right);
			if (y->parent != tmp) {
				transplant(y, y->right);
				y->right = tmp->right;
				y->right->parent = y;
			}
			transplant(tmp, y);
			y->left = tmp->left;
			y->left->parent = y;
		}
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
//========================================================
// print
//========================================================
	void	print() {

		node_pointer x = *_head;
		rec_print(x);
	}

	void	print_inc() {
		node_pointer x = tree_min();

		while (x != NULL) {
			std::cout << "key: " << x->data.first << " |valude: " << x->data.second << std::endl;
			x = successor(x);
		}
	}

	void	print_dec() {
		node_pointer x = tree_max();

		while (x != NULL) {
			std::cout << "key: " << x->data.first << " |valude: " << x->data.second << std::endl;
			x = predecessor(x);
		}
	}

	node_pointer successor(node_pointer x) {
		if (x->right != NULL)
			return tree_min(x->right);
		node_pointer y = x->parent;
		while (y != NULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	node_pointer predecessor(node_pointer x) {
		if (x->left != NULL)
			return tree_max(x->left);
		node_pointer y = x->parent;
		while (y != NULL && x == y->left) {
			x = y;
			y = y->parent;
		}
		return (y);
	}

//========================================================
// min/max
//========================================================

	node_pointer tree_min() {
		node_pointer x = *_head;

		while (x->left != NULL)
			x = x->left;
		return (x);
	}

	node_pointer tree_min(node_pointer x) {
		while (x->left != NULL)
			x = x->left;
		return (x);
	}

	node_pointer tree_max() {
		node_pointer x = *_head;

		while (x->right != NULL)
			x = x->right;
		return (x);
	}

	node_pointer tree_max(node_pointer x) {

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

void	transplant(node_pointer a, node_pointer b) {
		if (a->parent == NULL)
			*_head = b;
		else if (a == a->parent->left)
			a->parent->left = b;
		else
			a->parent->right = b;

		if (b != NULL)
			b->parent = a->parent;
	}

};

} // namespace ft

#endif // UTILS_BINTREE_HPP_
