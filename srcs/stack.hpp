/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 23:44:16 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/14 03:02:43 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "algorithm.hpp"
#include "vector.hpp"

namespace ft
{
	template <typename T, typename Container = vector<T> >
	class stack;

	template <typename T, typename Container>
	bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return !(lhs < rhs) && !(rhs < lhs);
	}

	template <typename T, typename Container>
	bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Container>
	bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Container>
	bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return !(lhs < rhs && lhs == rhs);
	}

	template <typename T, typename Container>
	bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return !(lhs < rhs);
	}
}

template <typename T, typename Container>
class ft::stack
{
public:
	typedef T value_type;
	typedef Container container_type;
	typedef typename container_type::size_type size_type;

	explicit stack(const container_type &ctnr = container_type()) : c(ctnr)
	{
	}

	bool empty() const
	{
		return c.empty();
	}

	size_type size() const
	{
		return c.size();
	}

	value_type &top()
	{
		return c.back();
	}

	const value_type &top() const
	{
		return c.back();
	}

	void push(const value_type &val)
	{
		c.push_back(val);
	}

	void pop()
	{
		c.pop_back();
	}

	friend bool operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.c < rhs.c;
	}

protected:
	container_type c;
};

#endif
