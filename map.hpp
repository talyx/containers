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
		friend class map;
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
	allocator_type _alloc;

public:
//========================================================================================================
// constructor/destructor
//========================================================================================================
	explicit map(const key_compare& comp = key_compare(), const allocator_type alloc = allocator_type()):
	tree(comp, alloc), _alloc(allocator_type()) {	}

	template<class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare comp = key_compare(),
		 const allocator_type alloc = allocator_type()): tree(comp, alloc), _alloc(allocator_type()) {
		insert(first, last);
	}
	map(const map& other): tree(other.tree), _alloc(allocator_type()){	}

	map &operator=(const map& other) {
		if (this == &other) return *this;

		tree = other.tree;
		return (*this);
	}

	~map() {}
//========================================================================================================
// iterators
//========================================================================================================
	iterator begin() {
		return (iterator(tree.tree_min(), tree.root));
	}

	const_iterator begin() const {
		return (const_iterator(tree.tree_min(), tree.root));
	}

	iterator end() {
		return (iterator(NULL, tree.root));
	}

	const_iterator end() const {
		return (const_iterator(NULL, tree.root));
	}

	reverse_iterator rbegin() {
		return (reverse_iterator(--end()));
	}

	const_reverse_iterator rbegin() const {
		return (const_reverse_iterator(--end()));
	}

	reverse_iterator rend() {
		return (reverse_iterator(--begin()));
	}

	const_reverse_iterator rend() const {
		return (const_reverse_iterator(--begin()));
	}

//========================================================================================================
// capacity
//========================================================================================================
	bool empty() const { return (tree.empty()); }
	size_type  size() const { return (tree.size()); }
	size_type  max_size() const {
		return (tree.max_size());
	}

//========================================================================================================
// element access
//========================================================================================================
	mapped_type &operator[](const key_type& k) {
		ft::pair<iterator, bool> ret;
		ret = tree.insert(ft::make_pair(k, mapped_type()));
		return (ret.first->second);
	}
//========================================================================================================
// modifiers
//========================================================================================================
	ft::pair<iterator, bool> insert(const value_type &val) {
		return (tree.insert(val));
	}

	iterator insert(iterator position, const value_type& val) {
		return (tree.insert(position, val));// does not work
	}

	template<class It>
	void insert (It first, It last){ tree.insert(first, last); }

	size_type  erase(const key_type& k) {
		node* tmp = tree.erase(ft::make_pair(k, mapped_type()));
		if (tmp == NULL)
			return (0);
		return (1);
	}

	void erase(iterator position) { tree.erase(position);}

	void erase(iterator first, iterator last) { tree.erase(first, last); }

	void swap (map &x) {
			tree.swap(x.tree);
	}

	void clear(){ tree.clear(); }

//========================================================================================================
// operations
//========================================================================================================

	iterator find(const key_type& k) {
		node* tmp = tree.search_by_key(ft::make_pair(k, mapped_type()));
		return (iterator(tmp, tree.root));
	}
	const_iterator find(const key_type& k) const {
		node* tmp = tree.search_by_key(ft::make_pair(k, mapped_type()));

		return (iterator(tmp, tree.root));
	}

	size_type count (const key_type& k) const {
		node* tmp = tree.search_by_key(ft::make_pair(k, mapped_type()));
		if (tmp == NULL)
			return (0);
		else
			return (1);
	}

	iterator lower_bound (const key_type& k){
		return (tree.lower_bound(ft::make_pair(k, mapped_type())));
	}

	const_iterator lower_bound (const key_type& k) const{
		return (tree.lower_bound(ft::make_pair(k, mapped_type())));
	}

	iterator upper_bound(const key_type& k) {
		return (tree.upper_bound(ft::make_pair(k, mapped_type())));
	}

	const_iterator upper_bound(const key_type& k) const {
		return (tree.upper_bound(ft::make_pair(k, mapped_type())));
	}

	pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
		return (ft::make_pair(lower_bound(k), upper_bound(k)));
	}

	pair<iterator, iterator> equal_range(const key_type& k) {
		return (ft::make_pair(lower_bound(k), upper_bound(k)));
	}

//========================================================================================================
// observers
//========================================================================================================

	key_compare key_comp() const {
		key_compare key;
		return (key);
	}

	value_compare value_comp() const {
		value_compare v_cmp(key_comp());
		return (v_cmp);
	}

	allocator_type  get_allocator() const {
		return (_alloc);
	}
}; // class map
//========================================================================================================
// Non-member functions
//========================================================================================================
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
					 const ft::map<Key,T,Compare,Alloc>& rhs ){
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
					 const ft::map<Key,T,Compare,Alloc>& rhs ){
		return (!(lhs == rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs ){
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
					 const ft::map<Key,T,Compare,Alloc>& rhs ){
		return (!(rhs < lhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs ){
		return (rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
					 const ft::map<Key,T,Compare,Alloc>& rhs ){
		return (!(lhs < rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs,
			   ft::map<Key,T,Compare,Alloc>& rhs ) {
		lhs.swap(rhs);
	}

} // namespace ft

#endif // MAP_HPP_
