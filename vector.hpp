#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include "./iterators/random_access_iterator.hpp"
#include "./utils/utils.hpp"
#include "./iterators/reverse_iterator.hpp"

namespace ft {
template < class T, class Alloc = std::allocator<T> >
class vector {
 private:
	T	*arr;
	size_t	_size;
	size_t	_cap;
	Alloc	_alloc;

 public:
	typedef T										value_type;
	typedef Alloc										allocator_type;
	typedef size_t										size_type;
	typedef typename ft::iterator_traits<ft::iterator< ft::random_access_iterator_tag, T> >::difference_type
												difference_type;
	typedef typename allocator_type::reference 						reference;
	typedef typename allocator_type::const_reference					const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef random_access_iterator< value_type, difference_type, pointer, reference>	iterator;
	typedef random_access_iterator< value_type, difference_type, pointer, reference, true>	const_iterator;
	typedef ft::reverse_iterator<iterator>							reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

//========================================================================================================
// constructor/destructor
//========================================================================================================

	explicit vector(const allocator_type& alloc = allocator_type()):
		arr(0), _size(0), _cap(0), _alloc(alloc) {}

	explicit vector(size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type()):
		_size(n), _cap(n), _alloc(alloc) {

		if (n == 0) { arr = 0; return;}

		if (_size > max_size())
			throw std::runtime_error("cannot create ft::vector larger than max_size()");
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
	vector(InputIterator first, InputIterator last,
		const allocator_type& alloc = allocator_type(),
		typename enable_if<!is_integral<InputIterator>::value, void**>::type = NULL):
		_alloc(alloc) {
		_size = ft::iterator_dist(first, last);
		if (_size > max_size())
			throw std::runtime_error("cannot create ft::vector larger than max_size()");
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
		return *this;
	}

//========================================================================================================
// Element access
//========================================================================================================

	reference operator[] (size_type n) { return (*(arr + n)); }

	const_reference operator[](size_type n) const { return (*(arr + n)); }

	reference at(size_type n) {
		if (n >= _size)
			throw std::out_of_range("vector::_M_range_check: __n (which is " + to_str(n)
				+ ") >= this->size() (which is " + to_str(_size ) + ")");
		return (*(arr + n));
	}

	const_reference at(size_type n) const {
		if (n >= _size)
			throw std::out_of_range("vector::_M_range_check: __n (which is " + to_str(n)
				+ ") >= this->size() (which is " + to_str(_size ) + ")");
		return (*(arr + n));
	}

	reference front() { return (*arr); }

	const_reference front () const { return (*arr); }

	reference back() { return  (*(arr + _size - 1)); }

	const_reference back() const { return (*(arr + _size - 1)); }


//========================================================================================================
// Iterators
//========================================================================================================

	iterator begin() { iterator b(arr); return (b); }

	const_iterator begin() const { iterator b(arr); return (b); }

	iterator end() { iterator b(arr + _size); return (b); }

	const_iterator end() const { iterator e(arr + _size); return (e); }

	reverse_iterator rbegin() { reverse_iterator rev_it(--(this->end())); return (rev_it); }

	const_reverse_iterator rbegin() const { reverse_iterator rev_it(--(this->end())); return (rev_it);}

	reverse_iterator rend() { reverse_iterator rev_it (--(this->begin())); return (rev_it); }

	const_reverse_iterator rend() const { reverse_iterator rev_it (--(this->begin())); return (rev_it); }

//========================================================================================================
// Capacity
//========================================================================================================

	size_t size() const {
		return (this->_size);
	}

	size_type max_size() const {
		return (_alloc.max_size());
	}

	void resize(size_type n, value_type val = value_type()) {
		if (n < _size) {
			for (; _size != n; _size--)
				_alloc.destroy(&arr[_size]);
		} else if (n > _size) {
			if (n > _cap)
				reserve(n);
			size_type i = _size;
			try {
				for (; i < n; i++)
					_alloc.construct(&arr[i], val);
				_size = i;
			} catch (...) {
				for (size_type j = _size; j < i; ++j)
					_alloc.destroy(&arr[j]);
				throw;
			}
		}
	}

	size_type capacity() const { return _cap; }

	bool empty() const { return (_size == 0); }

	void reserve(size_type n) {
		if (n > max_size())
			throw std::runtime_error("vector::reserve");
		if (n <= _cap) return;

		pointer new_arr = _alloc.allocate(n);
		size_type i = 0;

		try {
			for (; i < _size; i++)
				_alloc.construct(&new_arr[i], arr[i]);
			for (size_type j = 0; j < _size; j++)
				_alloc.destroy(&arr[j]);
			_alloc.deallocate(arr, _cap);
			_cap = n;
			arr = new_arr;
		} catch (...) {
			for (size_type j = 0; j < i; j++)
				_alloc.destroy(&new_arr[j]);
			_alloc.deallocate(new_arr, n);
			throw;
		}
	}

//========================================================================================================
// Modifiers
//========================================================================================================

	void assign(size_type n, const value_type& val) {
		if (n > _cap)
			reserve(n);

		this->clear();
		size_type i = 0;
		try {
			for (; i < n; i++) {
				_alloc.construct(arr + i, val);
			}
			_size = n;
		}catch (...){
			for (size_type j = 0; j < i; j++)
				_alloc.destroy(arr + j);
			throw;
		}
	}

	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last,
		typename ft::enable_if<!is_integral<InputIterator>::value, void**>::type = NULL) {
		size_type  dist = ft::iterator_dist(first, last);
		if (dist > _cap)
			reserve(dist);
		this->clear();
		size_type i = 0;
		try {
			for (; i < dist; i++, first++) {
				_alloc.construct(arr + i, *first);
			}
			_size = dist;
		}catch (...) {
			for (size_type j = 0; j < i; j++)
				_alloc.destroy(arr + j);
			throw;
		}
	}

	void push_back(const value_type &val) {
		if (_size + 1 > _cap)
			(_cap > 0) ? reserve(_cap * 2) : reserve(1);
		try {
			_alloc.construct(&arr[_size], val);
			_size++;
		} catch (...) {
			throw;
		}
	}

	void pop_back() {
		if (_size == 0) return;
		_alloc.destroy(&arr[_size - 1]);
		_size--;
	}

	iterator insert(iterator position, const value_type& val) {
		if (position == end()) {
			push_back(val);
			return (end() - 1);
		}
		ft::vector<T, Alloc> tmp(begin(), position);
		tmp.reserve(_cap);
		size_type it_index = position - begin();
		tmp.push_back(val);
		for (size_type i = it_index; i < _size; i++)
			tmp.push_back(arr[i]);
		swap(tmp);
		return (iterator(&(arr[it_index])));
	}

	void insert(iterator position, size_type n, const value_type& val) {
		size_type count = n;
		size_type it_index = position - begin();
		if (_size + count > _cap * 2)
			reserve(_size + count);
		else if (_cap > 0)
			reserve(_cap * 2);
		else
			reserve(1);
		position = iterator(&arr[it_index]);
		if (position == end()) {
			for (size_type i = 0; i < n; i++)
				push_back(val);
			return;
		}
		ft::vector<T, Alloc> tmp(begin(), position);
		tmp.reserve(_cap);
		for (size_type i = 0; i < n; i++)
			tmp.push_back(val);
		for (size_type i = it_index; i < _size; i++)
			tmp.push_back(arr[i]);
		swap(tmp);
	}

	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if<!is_integral<InputIterator>::value, void**>::type = NULL) {
		size_type count = ft::iterator_dist(first, last);
		size_type it_index = position - begin();
		if (_size + count > _cap * 2)
			reserve(_size + count);
		else if (_cap > 0)
			 reserve(_cap * 2);
		 else
			 reserve(1);
		if (position == end()) {
			while(first != last) {
				push_back(*first);
				first++;
			}
			return;
		}
		ft::vector<T, Alloc> tmp(begin(), iterator(&arr[it_index]));
		tmp.reserve(_cap);
		while (first != last) {
			tmp.push_back(*first);
			first++;
		}
		for (size_type i = it_index; i < _size; i++)
			tmp.push_back(arr[i]);
		swap(tmp);
	}

	iterator erase(iterator position) {
		if (position == end())
			return (end());
		difference_type index_it = ft::iterator_dist(begin(), position);
		_alloc.destroy(&arr[index_it]);
		_size--;
		for (size_type i = index_it; i < _size; i++) {
			_alloc.construct(&arr[i], arr[i + 1]);
			_alloc.destroy(&arr[i +1]);
		}
		return  (iterator(&arr[index_it]));
	}

	iterator erase(iterator first, iterator last) {
		size_type index_first = ft::iterator_dist(begin(), first);
		size_type index_last = ft::iterator_dist(begin(), last);
		for (size_type i = index_first; i < index_last; i++)
			_alloc.destroy(&arr[i]);
		for (size_type i = 0, j = index_last; j < _size; j++, i++)
			_alloc.construct(&arr[index_first + i], arr[j]);
		_size -= index_last - index_first;
		return (iterator(&arr[index_first]));
	}

	void swap(vector& x) {
		if (this == &x) { return; }

		size_type	tmp_size = _size;
		size_type	tmp_cap = _cap;
		pointer		tmp_arr = arr;
		allocator_type	tmp_alloc = _alloc;

		_size = x._size;
		_cap = x._cap;
		_alloc = x._alloc;
		arr = x.arr;

		x._size = tmp_size;
		x._cap = tmp_cap;
		x._alloc = tmp_alloc;
		x.arr = tmp_arr;
	}

	void clear() {
		for (size_type i = 0; i < _size; i++)
			_alloc.destroy(&arr[i]);
		_size = 0;
	}

	allocator_type get_allocator() const {
		return (_alloc);
	}

}; // class vector
//========================================================================================================
// Non-member function
//========================================================================================================

template <class T, class Alloc>
  bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {

	if (lhs.size() != rhs.size()) return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
  bool operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
	return (!(lhs == rhs));
}

template <class T, class Alloc>
  bool operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
  bool operator<= (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
	return (!(rhs < lhs));
}

template <class T, class Alloc>
  bool operator>  (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
	return (rhs < lhs);
}

template <class T, class Alloc>
  bool operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
	return (!(lhs < rhs));
}

template< class T, class Alloc >
	void swap( ft::vector<T,Alloc>& lhs,
			   ft::vector<T,Alloc>& rhs ){
		lhs.swap(rhs);
	}

} // namespace ft

#endif // VECTOR_HPP_
