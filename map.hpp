#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>
#include <memory>
#include "./utils/utils.hpp"
#include "iterators/reverse_iterator.hpp"
#include "./utils/BinTree.hpp"

namespace ft {
template < class Key, class T, class Compare = ft::less<Key>,
	 class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
 public:
	typedef Key					key_type;
	typedef T					mapped_type;
	typedef size_t				size_type;
	typedef ptrdiff_t			difference_type;
	typedef Compare				key_compare;
	typedef Allocator			allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference 	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef ft::pair<const Key, T>						value_type;
private:
	typedef typename ft::Node<value_type>				node;
	typedef typename Allocator::template rebind<typename  ft::Node<value_type> >::other allocator_node;
	typedef typename ft::BinTree<value_type, key_compare, node, allocator_type, allocator_node> binTree;
public:
	typedef typename binTree::iterator iterator;
	typedef typename binTree::const_iterator const_iterator;
	typedef ft::reverse_iterator<iterator>		reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

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

private:
	binTree tree;

public:
//========================================================================================================
// constructor/destructor
//========================================================================================================
	explicit map(const key_compare& comp = key_compare(), const allocator_node alloc = allocator_node()):
	tree(comp, alloc) {	}

	template<class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare comp = key_compare(),
		 const allocator_node alloc = allocator_node()): tree(comp, alloc) {
		while (first != last) {
			this->insert(*first);
			first++;
		}
	}
	map(const map& other): tree(other.getCmp(), other.getAlloc()) {	}

	map &operator=(const map& other) {
		if (this == &other) return *this;

		tree = other.tree;
	}

	~map() {}
//========================================================================================================
// iterators
//========================================================================================================
	iterator begin() {
		return (iterator(tree.tree_min(), tree.root));
	}

	const_iterator begin() const {
		return (iterator(tree.tree_min(), tree.root));
	}

	iterator end() {
		return (iterator(NULL, tree.root));
	}

	const_iterator end() const {
		return (iterator(NULL, tree.root));
	}

	reverse_iterator rbegin() {
		return (reverse_iterator(end()));
	}

	const_reverse_iterator rbegin() const {
		return (const_reverse_iterator(end()));
	}

	reverse_iterator rend() {
		return (reverse_iterator(begin()));
	}

	const_reverse_iterator rend() const {
		return (const_reverse_iterator(begin()));
	}

//========================================================================================================
// capacity
//========================================================================================================
//========================================================================================================
// element access
//========================================================================================================
//========================================================================================================
// modifiers
//========================================================================================================
	ft::pair<iterator, bool> insert(const value_type &val) {
		return (tree.insert(val));
	}

//========================================================================================================
// observers
//========================================================================================================
//========================================================================================================
// operations
//========================================================================================================
	void print_tree(void) {
		tree.print();
	}
}; // class map
} // namespace ft

#endif // MAP_HPP_
