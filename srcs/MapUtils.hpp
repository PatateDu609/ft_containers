/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapUtils.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 10:36:02 by gboucett          #+#    #+#             */
/*   Updated: 2021/03/14 10:37:37 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPUTILS_HPP
#define MAPUTILS_HPP

namespace ft
{
	template <typename T1, typename T2>
	struct pair;

	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return pair<T1, T2>(t, u);
	}
}

template <typename T1, typename T2>
struct ft::pair
{
	T1 first;
	T2 second;

	pair()
	{
	}

	pair(const T1 &t, const T2 &u) : first(t), second(u)
	{
	}

	template <typename U, typename V>
	pair(const pair<U, V> &pr) : first(pr.first), second(pr.second)
	{
	}

	template <typename U, typename V>
	pair &operator=(const pair<U, V> &pr)
	{
		first = pr.first;
		second = pr.second;
		return *this;
	}
};

#if defined(DEBUG) && DEBUG == 1

#include <iostream>

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const ft::pair<T1, T2> &p)
{
	os << "(" << p.first << ", " << p.second << ")";
	return os;
}

#endif

#endif
