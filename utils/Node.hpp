#ifndef UTILS_NODE_HPP_
#define UTILS_NODE_HPP_

#include <iostream>
#include "./utils.hpp"
//========================================================================================================
// node
//========================================================================================================
namespace ft {
template <typename T>
struct Node {

 public:
	Node*		parent;
	Node*		left;
	Node*		right;
	bool		color;
	T			data;

//=========================================================
// constructor/destructor
//=========================================================

	Node(): data(T()) {}

	Node(const T &val): data(val) { }

	Node(const Node & o): parent(o.parent), left(o.left),
		right(o.right), data(o.data) { }
	~Node() {}

	Node &operator=(const Node &o) {
		if (this == &o) return *this;

		parent = o.parent;
		left = o._left;
		right = o.right;
		data = o.data;
		return (*this);
	}

	bool operator==(const Node &o) {
		return (data == o.data);
	}
};
} // namespace ft

#endif // UTILS_NODE_HPP_
