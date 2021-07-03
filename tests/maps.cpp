/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:23:13 by gboucett          #+#    #+#             */
/*   Updated: 2021/03/14 11:41:02 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void maps()
{
	//srand(time(0));
	ft::Map<int, int> m;
	std::vector<ft::pair<int, int> > v;
	typedef ft::Map<int, int>::iterator iterator;

	for (int i = 0; i < 10; i++)
		v.push_back(ft::make_pair(rand(), rand()));

	m.insert(v.begin(), v.end());

#if defined(DEBUG) && DEBUG == 1
	m.dump_tree("map1.dot");
#endif

	size_t i = 0;
	for (iterator it = m.begin(); i < v.size() && it != m.end(); it++, i++)
		std::cout << it->first << " -> " << it->second << "\n";
}
