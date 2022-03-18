#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

#include <iostream>
namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class vector {
	private:
		T	*arr;
		size_t	size;
		size_t	cap;
		Alloc	alloc;
	public:
		typedef T														value_type;
		typedef Alloc													allocator_type;
		typedef size_t													size_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;

//		vector(const allocator_type& alloc = allocator_type()) {
//
//		}
//
//		vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
//
//		}
//
//		template<class InputIterator>
//				vector(InputIterator first, InputIterator last,  const allocator_type& alloc = allocator_type())
//		{}
//		vector(const vector& x) {
//
//		}
//
//		~vector() {
//
//		}
//
//		vector &operator=(const vector & x) {
//			return <#initializer#>;
//		}
	};
}

#endif //CONTAINERS_VECTOR_HPP
//========================================================================================================
// constructor/destructor
//========================================================================================================

	explicit vector(const allocator_type& alloc = allocator_type()): arr(0), _size(0), _cap(0), _alloc(alloc) {}

	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _size(n), _cap(n), _alloc(alloc) {

		if (n == 0) { arr = 0; return;}

		this->arr = _alloc.allocate(n);
		size_type i = 0;
		try {
			for(; i < n; ++i) {
				_alloc.construct(&this->arr[i], val);
			}
		} catch(...) {
			for (size_t j = 0; j < i; ++j) {
				_alloc.destroy(&arr[j]);
			}
			_alloc.deallocate(arr, _cap);
			this->_size = 0;
			this->_cap = 0;
			throw;
		}
	}

	template<class InputIterator>
			vector(InputIterator first, InputIterator last,  const allocator_type& alloc = allocator_type()): _alloc(alloc) {
		// check iterator valid!!!
		_size = iterator_dist(first, last);
		_cap = _size;
		this->arr = _alloc.allocate(_size);
		size_type i = 0;
		try {
			for (; i < _size; ++i) {
				_alloc.construct(&arr[i], *first);
				first++;
			}
		} catch(...) {
			for (size_type j = 0; j < i; ++j) {
				_alloc.destroy(&arr[j]);
			}
			_alloc.deallocate(arr, _cap);
			this->_size = 0;
			this->_cap = 0;
			throw;
		}
	}

	vector(const vector &other): _size(other._size), _cap(other._cap), _alloc(other._alloc) {
		this->arr = _alloc.allocate(_cap);
		size_type i = 0;
		try {
			for (; i < _size; ++i) {
				_alloc.construct(&arr[i], other.arr[i]);
			}
		} catch (...) {
			for (size_type j = 0; j < i; ++j) {
				_alloc.destroy(&arr[j]);
			}
			_alloc.deallocate(arr, _cap);
			_size = 0;
			_cap = 0;
			throw;
		}
	}


	~vector() {
		for (size_type j = 0; j < _size; ++j) {
			_alloc.destroy(&arr[j]);
		}
		_alloc.deallocate(arr, _cap);
	}

	vector &operator=(const vector &other) {

		if (this == &other) { return *this; }

		for (size_type j = 0; j < _size; j++) {
			_alloc.destroy(&arr[j]);
		}
		_alloc.deallocate(arr, _cap);
		_size = 0;
		_cap = 0;
		if (other._size == 0)
			return *this;
		_size = other._size;
		_alloc = other._alloc;
		_cap = other._cap;
		arr = _alloc.allocate(_cap);
		size_type i = 0;
		try {
			for (; i < _size; i++) {
				_alloc.construct(&arr[i], other[i]);
			}
		} catch (...) {
			for (size_type j = 0; j < i; j++)
				_alloc.destroy(&arr[j]);
			_alloc.deallocate(arr, _cap);
			_size = 0;
			_cap = 0;
			throw;
		}
	}

//========================================================================================================
// Element access
//========================================================================================================

	reference operator[] (size_type n) { return (*(arr + n)); }

	const_reference operator[](size_type n) const { return (*(arr + n)); }

	reference at(size_type n) {
		if (n >= _size)
			throw std::out_of_range("out_of_range error: item number (" + to_str(n)
				+ ") is greater than available items (" + to_str(_size - 1) + ")");
		return (*(arr + n));
	}

	const_reference at(size_type n) const {
		if (n >= _size)
			throw std::out_of_range("out_of_range error: item number (" + to_str(n)
				+ ") is greater than available items (" + to_str(_size - 1) + ")");
		return (*(arr + n));
	}

	reference front() { return (*arr); }

	const_reference front () const { return (*arr); }

	reference back() { return  (*(arr + _size - 1)); }

	const_reference back() const { return (*(arr + _size - 1)); }


