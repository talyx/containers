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
