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
	ft::Map<int, int> m;
	std::vector<ft::pair<int, int> > v;
	typedef ft::Map<int, int>::iterator iterator;

	for (int i = 0; i < 10; i++)
		v.push_back(ft::make_pair(i % 10, i));

	m.insert(v.begin(), v.end());

	std::cout << "before erase\n";
	for (iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " -> " << it->second << "\n";

#if defined(DEBUG) && DEBUG == 1
	m.dump_tree("map_before_erase.dot");
#endif

	m.erase(m.find(6), ++(++m.find(6)));

#if defined(DEBUG) && DEBUG == 1
	m.dump_tree("map_after_erase.dot");
#endif

	std::cout << "after erase, size : " << m.size() << "\n";
	for (iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " -> " << it->second << "\n";
}
