#ifndef ITERATORS_RANDOM_ACCESS_ITERATOR_HPP_
#define ITERATORS_RANDOM_ACCESS_ITERATOR_HPP_

#include "./iterator.hpp"

namespace ft {

template <typename T, typename  Distance, typename  Pointer, typename Reference, bool _const = false>
class random_access_iterator : public iterator<random_access_iterator_tag, T, Distance, Pointer, Reference> {
 private:
	T* ptr;

 public:
	typedef Distance							difference_type;
	typedef random_access_iterator_tag					iterator_category;
	typedef typename conditional<_const, const T, T>::type			value_type;
	typedef typename conditional<_const, const Pointer, Pointer>::type	pointer;
	typedef typename conditional<_const, const Reference, Reference>::type	reference;

//========================================================================================================
// constructor/destructor
//========================================================================================================

	random_access_iterator(): ptr(0) {}

	random_access_iterator(T *p): ptr(p) {}

	random_access_iterator(const random_access_iterator & other): ptr(other.ptr) {}

// copy-assignable?

	~random_access_iterator() {}

//========================================================================================================
// opertor overloading (class member)
//========================================================================================================

	reference operator*() const {
		return *(this->ptr);
	}

	random_access_iterator &operator++() {
		++ptr;
		return (*this);
	}

	random_access_iterator operator++(int) {
		random_access_iterator tmp(*this);
		++ptr;
		return (tmp);
	}

	random_access_iterator &operator--() {
		--ptr;
		return (*this);
	}

	random_access_iterator operator--(int) {
		random_access_iterator tmp(*this);
		--ptr;
		return (tmp);
	}

	reference	operator[](int i) {
		return *(ptr + i);
	}

	pointer	operator->() const {
		return (ptr);
	}

	random_access_iterator &operator+=(difference_type n) {
		ptr += n;
		return  (*this);
	}

	random_access_iterator &operator-=(difference_type n) {
		ptr -= n;
		return (*this);
	}

	random_access_iterator operator+(difference_type n) {
		return random_access_iterator(ptr + n);
	}

	random_access_iterator operator-(difference_type n) {
		return random_access_iterator(ptr - n);
	}

//========================================================================================================
// opertor overloading ( friend methods )
//========================================================================================================

	template <typename t, typename distance, typename pointer, typename reference, bool _Const>
		friend bool operator==(const random_access_iterator<t, distance, pointer, reference, _Const> &lft, \
				const random_access_iterator<t, distance, pointer, reference, _Const> &rht);

	template <typename t, typename distance, typename pointer, typename reference, bool _Const>
		friend bool operator<(const random_access_iterator<t, distance, pointer, reference, _Const> &lft, \
				const random_access_iterator<t, distance, pointer, reference, _Const> &rht);

	template <typename t, typename distance, typename pointer, typename reference, bool _Const>
		friend typename random_access_iterator<t, distance, pointer, reference, _Const>::difference_type
		operator-(const random_access_iterator<t, distance, pointer, reference, _Const> &lft, \
				const random_access_iterator<t, distance, pointer, reference, _Const> &rht);


}; // class random_access_iterator

//========================================================================================================
// opertor overloading ( not class members  )
//========================================================================================================

template <typename t, typename distance, typename pointer, typename reference, bool _Const>
		bool operator==(const random_access_iterator<t, distance, pointer, reference, _Const> &lft, \
				const random_access_iterator<t, distance, pointer, reference, _Const> &rht) {
			return (lft.ptr == rht.ptr);
		}

	template <typename t, typename distance, typename pointer, typename reference, bool _Const>
		bool operator<(const random_access_iterator<t, distance, pointer, reference, _Const> &lft, \
				const random_access_iterator<t, distance, pointer, reference, _Const> &rht) {
			return (lft.ptr < rht.ptr);
		}

	template <typename t, typename distance, typename pointer, typename reference, bool _const>
			bool operator!=(const random_access_iterator<t, distance, pointer, reference, _const> &lft, \
							const random_access_iterator<t, distance, pointer, reference, _const> &rht) {
				return (!(lft == rht));
			}
	template <typename t, typename distance, typename pointer, typename reference, bool _const>
			bool operator>(const random_access_iterator<t, distance, pointer, reference, _const> &lft, \
							const random_access_iterator<t, distance, pointer, reference, _const> &rht) {
				return (rht < lft);
			}
	template <typename t, typename distance, typename pointer, typename reference, bool _const>
			bool operator<=(const random_access_iterator<t, distance, pointer, reference, _const> &lft, \
							const random_access_iterator<t, distance, pointer, reference, _const> &rht) {
				return (!(rht < lft));
			}

	template <typename t, typename distance, typename pointer, typename reference, bool _const>
			bool operator>=(const random_access_iterator<t, distance, pointer, reference, _const> &lft, \
							const random_access_iterator<t, distance, pointer, reference, _const> &rht) {
				return (!(lft < rht));
			}
	template <typename t, typename distance, typename pointer, typename reference, bool _Const>
		typename  random_access_iterator<t, distance, pointer, reference, _Const>::difference_type
		operator-(const random_access_iterator<t, distance, pointer, reference, _Const> &lft, \
				const random_access_iterator<t, distance, pointer, reference, _Const> &rht) {
			return (lft.ptr - rht.ptr);
		}

} // namespace ft

#endif // ITERATORS_RANDOM_ACCESS_ITERATOR_HPP_
