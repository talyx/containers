#ifndef CONTAINERS_STACK_HPP
#define CONTAINERS_STACK_HPP

#include <vector>
#include <iostream>
namespace ft {
	template <class T, class Container = std::vector<T> >
	class stack {
	protected:
		Container st;

	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

		stack(const container_type& ctnr = container_type()): st(ctnr){}

		~stack(){}
		bool empty() const
		{
			return (st.empty());
		}

		size_type size() const
		{
			return (st.size());
		}

		value_type & top()
		{
			return (st.back());
		}
		const value_type& top() const
		{
			return  (st.back());
		}
		void push (const value_type& val)
		{
			st.push_back(val);
		}
		void pop()
		{
			st.pop_back();
		}
		template <typename T1, typename Cont>
			friend bool operator==(const stack<T1, Cont>& lhs, const stack<T1, Cont>& rhs);
		template <typename T1, typename Cont>
			friend bool operator<(const stack<T1, Cont>& lhs, const stack<T1, Cont>& rhs);

	};
	template <typename T, typename Container>
		bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs.st == rhs.st);
	}
	template <typename T, typename Container>
		bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <typename T, typename Container>
		bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs.st < rhs.st);
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
