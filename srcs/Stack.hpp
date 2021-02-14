/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
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
#include "List.hpp"

namespace ft
{
	template <typename T, typename Container = List<T> >
	class Stack;
}

template <typename T, typename Container>
class ft::Stack
{
public:
	typedef T value_type;
	typedef Container container_type;
	typedef typename container_type::size_type size_type;

	explicit Stack(const container_type &ctnr = container_type()) : _c(ctnr)
	{
	}

	bool empty() const
	{
		return _c.empty();
	}

	size_type size() const
	{
		return _c.size();
	}

	value_type &top()
	{
		return _c.back();
	}

	const value_type &top() const
	{
		return _c.back();
	}

	void push(const value_type &val)
	{
		_c.push_back(val);
	}

	void pop()
	{
		_c.pop_back();
	}

	friend bool operator==(const ft::Stack<T, Container> &lhs, const ft::Stack<T, Container> &rhs)
	{
		return lhs._c == rhs._c;
	}

	friend bool operator!=(const ft::Stack<T, Container> &lhs, const ft::Stack<T, Container> &rhs)
	{
		return lhs._c != rhs._c;
	}

	friend bool operator<(const ft::Stack<T, Container> &lhs, const ft::Stack<T, Container> &rhs)
	{
		return lhs._c < rhs._c;
	}

	friend bool operator>(const ft::Stack<T, Container> &lhs, const ft::Stack<T, Container> &rhs)
	{
		return lhs._c > rhs._c;
	}

	friend bool operator<=(const ft::Stack<T, Container> &lhs, const ft::Stack<T, Container> &rhs)
	{
		return lhs._c <= rhs._c;
	}

	friend bool operator>=(const ft::Stack<T, Container> &lhs, const ft::Stack<T, Container> &rhs)
	{
		return lhs._c >= rhs._c;
	}

protected:
	container_type _c;
};

#endif
