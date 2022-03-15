#ifndef ITERATORS_RANDOM_ACCESS_ITERATOR_HPP_
#define ITERATORS_RANDOM_ACCESS_ITERATOR_HPP_

#include "./iterator.hpp"

namespace ft {

template <typename T, typename  Distance, typename  Pointer, typename Reference, bool _const = false>
class random_acces_iterator : public iterator<random_acces_iterator_tag, T, Distance, Pointer, Reference> {
 private:
	T* ptr;

 public:
	typedef Distance														difference_type;
	typedef random_acces_iterator_tag										iterator_category;
	typedef typename conditional<_const, const T, T>::type					value_type;
	typedef typename conditional<_const, const Pointer, Pointer>::type		pointer;
	typedef typename conditional<_const, const Reference, Reference>::type	reference;

//========================================================================================================
// constructor/destructor
//========================================================================================================

	random_acces_iterator(): ptr(0) {}

	random_acces_iterator(T *p): ptr(p) {}

	random_acces_iterator(const random_acces_iterator & other): ptr(other.ptr) {}

// copy-assignable?

	~random_acces_iterator() {}

//========================================================================================================
// opertor overloading (class member)
//========================================================================================================

	reference operator*() const {
		return *(this->ptr);
	}

	random_acces_iterator &operator++() {
		++ptr;
		return (*this);
	}

	random_acces_iterator operator++(int) {
		random_acces_iterator tmp(*this);
		++ptr;
		return (tmp);
	}

	random_acces_iterator &operator--() {
		--ptr;
		return (*this);
	}

	random_acces_iterator operator--(int) {
		random_acces_iterator tmp(*this);
		--ptr;
		return (tmp);
	}

	reference	operator[](int i) {
		return *(ptr + i);
	}

	pointer	operator->() const {
		return (ptr);
	}

	random_acces_iterator &operator+=(difference_type n) {
		ptr += n;
		return  (*this);
	}

	random_acces_iterator &operator-=(difference_type n) {
		ptr -= n;
		return (*this);
	}

	random_acces_iterator operator+(difference_type n) {
		return random_acces_iterator(ptr + n);
	}

	random_acces_iterator operator-(difference_type n) {
		return random_acces_iterator(ptr - n);
	}

//========================================================================================================
// opertor overloading ( friend methods )
//========================================================================================================

	template <typename t, typename distance, typename pointer, typename reference, bool _Const>
		friend bool operator==(const random_acces_iterator<t, distance, pointer, reference, _Const> &lft, \
				const random_acces_iterator<t, distance, pointer, reference, _Const> &rht) {
			return (lft.ptr == rht.ptr);
		}

	template <typename t, typename distance, typename pointer, typename reference, bool _Const>
		friend bool operator<(const random_acces_iterator<t, distance, pointer, reference, _Const> &lft, \
				const random_acces_iterator<t, distance, pointer, reference, _Const> &rht) {
			return (lft.ptr < rht.ptr);
		}
}; // class random_acces_iterator

//========================================================================================================
// opertor overloading ( not class members  )
//========================================================================================================

	template <typename t, typename distance, typename pointer, typename reference, bool _const>
			bool operator!=(const random_acces_iterator<t, distance, pointer, reference, _const> &lft, \
							const random_acces_iterator<t, distance, pointer, reference, _const> &rht) {
				return (!(lft == rht));
			}
	template <typename t, typename distance, typename pointer, typename reference, bool _const>
			bool operator>(const random_acces_iterator<t, distance, pointer, reference, _const> &lft, \
							const random_acces_iterator<t, distance, pointer, reference, _const> &rht) {
				return (rht < lft);
			}
	template <typename t, typename distance, typename pointer, typename reference, bool _const>
			bool operator<=(const random_acces_iterator<t, distance, pointer, reference, _const> &lft, \
							const random_acces_iterator<t, distance, pointer, reference, _const> &rht) {
				return (!(rht < lft));
			}

	template <typename t, typename distance, typename pointer, typename reference, bool _const>
			bool operator>=(const random_acces_iterator<t, distance, pointer, reference, _const> &lft, \
							const random_acces_iterator<t, distance, pointer, reference, _const> &rht) {
				return (!(lft < rht));
			}
} // namespace ft

#endif // ITERATORS_RANDOM_ACCESS_ITERATOR_HPP_
