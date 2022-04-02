#ifndef UTILS_BINTREE_HPP_
#define UTILS_BINTREE_HPP_

#include <iostream>
#include <memory>
#include "./Node.hpp"
#include "./utils.hpp"
#include "../iterators/iterator.hpp"

namespace ft {
template < class Type, class Compare = ft::less<Type>, class _Node = ft::Node<Type>,
class  Allocator = std::allocator<Type>, class Node_allocator = std::allocator<_Node> >
class BinTree {
public:
//========================================================================================================
// Class BST_iterator
//========================================================================================================
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
					node * root;

				public:
				//========================================================================================================
				// constructor/destructor
				//========================================================================================================
					BST_iterator() { _node_ptr = NULL; root = NULL; }

					BST_iterator(node* const p, node* const root) { _node_ptr = p; this->root = root;}

					BST_iterator(const BST_iterator& other): _node_ptr(other._node_ptr), root(other.root) { }
					~BST_iterator() {}
				//========================================================================================================
				// operator overloading
				//========================================================================================================
					BST_iterator &operator=(const BST_iterator& other) {
						if (this == &other) return *this;

						_node_ptr = other._node_ptr;
						root = other.root;
						return (*this);
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
				// function
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
	typedef Type 			value_type;
	typedef Compare 		comp;
	typedef _Node 			node;
	typedef Allocator 		allocator_type;
	typedef Node_allocator 	allocator_node;
	typedef node* 			node_pointer;
	typedef BST_iterator<value_type, ptrdiff_t, typename allocator_type::pointer,
	typename allocator_type::reference> 		iterator;
	typedef BST_iterator<value_type, ptrdiff_t, typename  allocator_type::pointer,
	typename allocator_type::reference, true> 	const_iterator;

////========================================================
//// constructor/destructor
////========================================================
//	explicit BinTree(const node_alloc& al = node_alloc()): _n_allocator(al) {
//		*_head = NULL;
//	}
//
//	BinTree &operator=(const BinTree &other) {
//		if (this == &other) return *this;
//
//		rec_delete(*_head);
//		node_pointer tmp_head = other.get_head();
//		while (tmp_head != NULL) {
//			this->insert(tmp_head->data);
//			tmp_head = successor(tmp_head);
//		}
//	}
//
//	~BinTree() {rec_delete(*_head); }
//
////========================================================
//// insert/remove
////========================================================
//	ft::pair<node_pointer, bool> insert(const value_type &val) {
//		node_pointer y = NULL;
//		node_pointer x = *_head;
//
//		while (x != NULL) {
//			y = x;
//			if (val < x->data)
//				x = x->left;
//			else
//				x = x->right;
//		}
//		if (y != NULL && y->data.first == val.first) {
//			std::cout << "Value with this key(" << val.first << ") already exists\n";
//			return ft::make_pair(y, false);
//		}
//
//		node_pointer new_node = _n_allocator.allocate(1);
//		try {
//			_n_allocator.construct(new_node, node(val));
//			if (y == NULL) {
//				*_head = new_node;
//			} else {
//				new_node->parent = y;
//				if (new_node->data < y->data)
//					y->left = new_node;
//				else
//					y->right = new_node;
//		}
//		} catch(...) {
//			return (ft::make_pair(new_node, false));
//		}
//		return (ft::make_pair(new_node, true));
//	}
//
//	void	remove(const value_type &val) {
//		node_pointer tmp = search_by_key(val);
//
//		if (tmp->left == NULL) {
//			transplant(tmp, tmp->right);
//		} else if (tmp->right == NULL) {
//			transplant(tmp, tmp->left);
//		} else {
//			node_pointer y = tree_min(tmp->right);
//			if (y->parent != tmp) {
//				transplant(y, y->right);
//				y->right = tmp->right;
//				y->right->parent = y;
//			}
//			transplant(tmp, y);
//			y->left = tmp->left;
//			y->left->parent = y;
//		}
//	}
//
//	node_pointer search_by_key(const value_type &val) {
//		node_pointer x = *_head;
//
//		while (x != NULL && val.first != x->data.first) {
//			if (val < x->data)
//				x = x->left;
//			else
//				x = x->right;
//		}
//		return (x);
//	}
////========================================================
//// print
////========================================================
//	void	print() {
//
//		node_pointer x = *_head;
//		rec_print(x);
//	}
//
//	void	print_inc() {
//		node_pointer x = tree_min();
//
//		while (x != NULL) {
//			std::cout << "key: " << x->data.first << " |valude: " << x->data.second << std::endl;
//			x = successor(x);
//		}
//	}
//
//	void	print_dec() {
//		node_pointer x = tree_max();
//
//		while (x != NULL) {
//			std::cout << "key: " << x->data.first << " |valude: " << x->data.second << std::endl;
//			x = predecessor(x);
//		}
//	}
//
//	static node_pointer successor(node_pointer x) {
//		if (x->right != NULL)
//			return tree_min(x->right);
//		node_pointer y = x->parent;
//		while (y != NULL && x == y->right) {
//			x = y;
//			y = y->parent;
//		}
//		return y;
//	}
//
//	static node_pointer predecessor(node_pointer x) {
//		if (x->left != NULL)
//			return tree_max(x->left);
//		node_pointer y = x->parent;
//		while (y != NULL && x == y->left) {
//			x = y;
//			y = y->parent;
//		}
//		return (y);
//	}
//
////========================================================
//// min/max
////========================================================
//
//	node_pointer tree_min() {
//		node_pointer x = *_head;
//
//		while (x->left != NULL)
//			x = x->left;
//		return (x);
//	}
//
//	static node_pointer tree_min(node_pointer x) {
//		while (x->left != NULL)
//			x = x->left;
//		return (x);
//	}
//
//	node_pointer tree_max() {
//		node_pointer x = *_head;
//
//		while (x->right != NULL)
//			x = x->right;
//		return (x);
//	}
//
//	static node_pointer tree_max(node_pointer x) {
//
//		while (x->right != NULL)
//			x = x->right;
//		return (x);
//	}
//
//	node_pointer get_head() { return (*_head); }
//
// private:
//	void rec_print(node_pointer n) {
//		if (n != NULL) {
//			rec_print(n->left);
//			std::cout << n->data.first << " " << n->data.second << std::endl;
//			rec_print(n->right);
//		}
//	}
//
//	void rec_delete(node_pointer n) {
//		if (n != NULL) {
//			rec_delete(n->left);
//			rec_delete(n->right);
//			_n_allocator.destroy(n);
//			_n_allocator.deallocate(n, 1);
//		}
//	}
//
//	void transplant(node_pointer a, node_pointer b) {
//		if (a->parent == NULL)
//			*_head = b;
//		else if (a == a->parent->left)
//			a->parent->left = b;
//		else
//			a->parent->right = b;
//
//		if (b != NULL)
//			b->parent = a->parent;
//	}
}; // class BinTree

} // namespace ft

#endif // UTILS_BINTREE_HPP_
