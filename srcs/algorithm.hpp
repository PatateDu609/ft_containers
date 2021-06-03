/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 01:18:17 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/18 02:57:23 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <typeinfo>

namespace ft
{
	template <typename T>
	void swap(T &a, T &b)
	{
		T temp = a;

		a = b;
		b = temp;
	}

	template <typename T>
	struct less
	{
		bool operator()(const T &a, const T &b) const
		{
			return (a < b);
		}
	};

	template <typename T>
	struct great
	{
		bool operator()(const T &a, const T &b) const
		{
			return (a > b);
		}
	};

	template <typename iterator1, typename iterator2>
	bool lexicographical_compare(iterator1 first1, iterator1 last1, iterator2 first2, iterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first1 > *first2)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template <typename iterator1, typename iterator2, typename Compare>
	bool lexicographical_compare(iterator1 first1, iterator1 last1, iterator2 first2, iterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || !comp(*first1, *first2))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
}; // namespace ft

#endif
