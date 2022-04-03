#ifndef CONTAINERS_STACK_HPP
#define CONTAINERS_STACK_HPP

#include "vector.hpp"
#include <iostream>
namespace ft {
	template <class T, class Container = ft::vector<T> >
	class stack {
	protected:
		Container c;

	public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference 		reference;
		typedef typename Container::const_reference const_reference;

		explicit stack(const container_type& cont = container_type()): c(cont){}
		stack(const stack& other): c(other.c) {}
		stack &operator=(const stack& other) {
			if (this == &other) return *this;
			c = other.c;
		}
		~stack(){}

		bool empty() const
		{
			return (c.empty());
		}

		size_type size() const
		{
			return (c.size());
		}

		value_type & top()
		{
			return (c.back());
		}
		const value_type& top() const
		{
			return  (c.back());
		}
		void push (const value_type& val)
		{
			c.push_back(val);
		}
		void pop()
		{
			c.pop_back();
		}
		template <typename T1, typename Cont>
			friend bool operator==(const stack<T1, Cont>& lhs, const stack<T1, Cont>& rhs);
		template <typename T1, typename Cont>
			friend bool operator<(const stack<T1, Cont>& lhs, const stack<T1, Cont>& rhs);

	};
	template <typename T, typename Container>
		bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}
	template <typename T, typename Container>
		bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <typename T, typename Container>
		bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}
	template <typename T, typename Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (rhs < lhs);
	}
	template <typename T, typename Container>
		bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <typename T, typename Container>
		bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!(lhs < rhs));
	}
}
#endif //CONTAINERS_STACK_HPP
