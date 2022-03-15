#ifndef ITERATORS_ITERATOR_HPP_
#define ITERATORS_ITERATOR_HPP_

#include <stddef.h>
#include <iostream>

//========================================================
// main struct
//========================================================

template <typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
struct iterator {
	public:
		typedef Category		iterator_category;
		typedef T				value_type;
		typedef Distance		difference_type;
		typedef Pointer			pointer;
		typedef Reference		reference;
};

//=========================================================
// Iterator category
//=========================================================

struct input_iterator_tag {};
struct forward_iterator_tag: public input_iterator_tag {};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_acces_iterator_tag: public bidirectional_iterator_tag {};

//========================================================
// iterator_traits
//========================================================

template <class Iterator>
struct	iterator_traits {
 public:
	typedef typename Iterator::difference_type	difference_type;
	typedef typename Iterator::value_type		value_type;
	typedef typename Iterator::pointer			pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T* > {
 public:
	ptrdiff_t					difference_type;
	T							value_type;
	T*							pointer;
	T&							reference;
	random_acces_iterator_tag	iterator_category;
};

template <class T>
class iterator_traits<const T*> {
 public:
	ptrdiff_t					difference_type;
	T							value_type;
	const T*					pointer;
	const T&					reference;
	random_acces_iterator_tag	iterator_category;
};

//========================================================
// conditional
//========================================================

template <bool, typename A, typename B>
struct conditional {
	typedef B type;
};

template <typename A, typename B>
struct conditional<true, A, B> {
	typedef A type;
};


#endif // ITERATORS_ITERATOR_HPP_

