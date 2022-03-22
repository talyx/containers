#ifndef UTILS_UTILS_HPP_
#define UTILS_UTILS_HPP_
#include <stddef.h>

#define HEADER  "\033[95m"
#define PINK    "\033[35m"

#define BLUE	"\033[34m"
#define OKBLUE  "\033[94m"

#define FAIL    "\033[91m"
#define RED		"\033[31m"

#define GREEN	"\033[32m"
#define OKGREEN "\033[92m"

#define YELLOW	"\033[33m"
#define YELLO	"\033[33m"
#define WARNING "\033[93m"

#define TURGUOISE   "\033[36m"
#define OKCYAN  "\033[96m"

#define TURQ	"\033[36m"

#define BOLD	"\033[1m"

#define ENDC	"\033[0m"
#define ZERO_C  "\033[0m"
#define RESET   "\033[0m"

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

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2) {
  while (first1 != last1) {
    if (first2 == last2 || *first2 < *first1) return false;
    else if (*first1 < *first2) return true;
    ++first1; ++first2;
  }
  return (first2 != last2);
}

// template <typename Iterator>
// bool is_iterator( Iterator first, Iterator second) {

} // namespace ft
#endif // UTILS_UTILS_HPP_
