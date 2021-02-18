/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 00:01:43 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/18 16:58:00 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "algorithm.hpp"
#include "List.hpp"

namespace ft
{
	template <typename T, typename Container = List<T> >
	class Queue;
}

template <typename T, typename Container>
class ft::Queue
{
public:
	typedef T value_type;
	typedef Container container_type;
	typedef typename container_type::size_type size_type;

	explicit Queue(const container_type &ctnr = container_type()) : _c(ctnr)
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

	value_type& front()
	{
		return _c.front();
	}

	const value_type& front() const
	{
		return _c.front();
	}

	value_type& back()
	{
		return _c.back();
	}

	const value_type& back() const
	{
		return _c.back();
	}

	void push(const value_type& val)
	{
		_c.push_back(val);
	}

	void pop()
	{
		_c.pop_front();
	}

	friend bool operator==(const ft::Queue<T, Container>& lhs, const ft::Queue<T, Container>& rhs)
	{
		return lhs._c == rhs._c;
	}

	friend bool operator!=(const ft::Queue<T, Container>& lhs, const ft::Queue<T, Container>& rhs)
	{
		return lhs._c != rhs._c;
	}

	friend bool operator<(const ft::Queue<T, Container>& lhs, const ft::Queue<T, Container>& rhs)
	{
		return lhs._c < rhs._c;
	}

	friend bool operator>(const ft::Queue<T, Container>& lhs, const ft::Queue<T, Container>& rhs)
	{
		return lhs._c > rhs._c;
	}

	friend bool operator<=(const ft::Queue<T, Container>& lhs, const ft::Queue<T, Container>& rhs)
	{
		return lhs._c <= rhs._c;
	}

	friend bool operator>=(const ft::Queue<T, Container>& lhs, const ft::Queue<T, Container>& rhs)
	{
		return lhs._c >= rhs._c;
	}

protected:
	container_type _c;
};

#endif
