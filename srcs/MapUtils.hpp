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

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
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

#endif
