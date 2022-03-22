#ifndef ITERATORS_REVERSE_ITERATOR_HPP_
#define ITERATORS_REVERSE_ITERATOR_HPP_

#include "./iterator.hpp"
#include "./random_access_iterator.hpp"

namespace ft {

template <class Iterator>
class reverse_iterator : public iterator<typename ft::iterator_traits<Iterator>::iterator_category,
	typename ft::iterator_traits<Iterator>::value_type, typename ft::iterator_traits<Iterator>::difference_type,
	typename ft::iterator_traits<Iterator>, typename ft::iterator_traits<Iterator>::reference> {

 private:
	Iterator base_it;

 public:
	typedef Iterator				iterator_type;
	typedef typename Iterator::iterator_category	iterator_category;
	typedef typename Iterator::value_type		value_type;
	typedef typename Iterator::difference_type	difference_type;
	typedef typename Iterator::pointer		pointer;
	typedef typename Iterator::reference		reference;

//========================================================================================================
// constructor/destructor
//========================================================================================================

	reverse_iterator() {}

	explicit reverse_iterator(iterator_type it): base_it(it) { }

	template <class Iter>
	reverse_iterator(const reverse_iterator<Iter>& rev_it):
		base_it(rev_it.base_it) { }
	~reverse_iterator() { }

//========================================================================================================
// Member funcition
//========================================================================================================

	iterator_type base() const { return base_it; }

	reference operator*() const {
		iterator_type i_t = base_it;
		return *(--i_t);
	}

	reverse_iterator operator+(difference_type n) const {
		return (reverse_iterator(base_it - n));
	}

	reverse_iterator& operator++() {
		base_it--;
		return (*this);
	}

	reverse_iterator operator++(int n) {
		reverse_iterator r_i(*this);

		base_it--;
		return (r_i);
	}

	reverse_iterator& operator+=(difference_type n) {
		base_it -= n;

		return (*this);
	}

	reverse_iterator operator-(difference_type n ) const {

		return (reverse_iterator(base_it + n));
	}

	reverse_iterator& operator--() {
		base_it++;
		return (*this);
	}

	reverse_iterator operator--(int) {
		reverse_iterator r_i(*this);

		base_it++;
		return (r_i);
	}

	reverse_iterator& operator-=(difference_type n) {
		base_it += n;

		return (*this);
	}

	pointer operator->() const { return &(operator*()); }

	reference operator[](difference_type n) const {
		return *(base_it[-n - 1]);
	}
}; // class reverse_iterator

//========================================================================================================
// Non-member funcition
//========================================================================================================

template <class Iterator>
bool operator== (const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
	return (lhs.base() == rhs.base());
}

template <class Iterator>
bool operator!= (const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
	return (lhs.base() != rhs.base());
}

template <class Iterator>
bool operator<  (const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
	return (lhs.base() < rhs.base());
}

template <class Iterator>
bool operator<= (const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
bool operator> (const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
	return (lhs.base() > rhs.base());
}

template <class Iterator>
bool operator>= (const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
	return (lhs.base() >= rhs.base());
}

template <class Iterator>
reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it) {
	return (rev_it + n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator- (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
	return (lhs.base() - rhs.base());
}

} // namespace ft

#endif // ITERATORS_REVERSE_ITERATOR_HPP_
