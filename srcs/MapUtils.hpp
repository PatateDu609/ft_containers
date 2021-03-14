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
}

template <typename T1, typename T2>
struct ft::pair
{
	T1 first;
	T2 second;

	pair()
	{}

	template <typename U, typename V>
	pair(const pair<U, V>& pr) : first(pr.first), second(pr.second)
	{}

	template <typename U, typename V>
	pair(const std::pair<U, V>& pr) : first(pr.first), second(pr.second)
	{}

	template <typename U, typename V>
	operator std::pair<U, V>() const
	{
		return std::make_pair(first, second);
	}

	pair& operator=(const pair& other)
	{
		first = other.first;
		second = other.second;
		return *this;
	}
};

#endif
