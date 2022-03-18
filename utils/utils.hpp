#ifndef UTILS_UTILS_HPP_
#define UTILS_UTILS_HPP_

#include <iostream>
#include <sstream>
#include <string>

namespace ft {

template <typename InputIterator>
ptrdiff_t	iterator_dist(InputIterator first, InputIterator second) {
	ptrdiff_t	i;
	for (i = 0; first != second; i++)
		first++;
	return (i);
}

std::string	to_str(size_t n) {
	std::stringstream str;

	str << n;
	return (str.str());
}

// template <typename Iterator>
// bool is_iterator( Iterator first, Iterator second) {

} // namespace ft
#endif // UTILS_UTILS_HPP_
