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
	std::vector<std::pair<int, int> > v;
	//std::string s[] = {"false", "true"};

	typedef ft::Map<int, int>::iterator iterator;

	for (int i = 0; i < 10; i++)
		v.push_back(std::make_pair(i % 10, i));

	m.insert(v.begin(), v.end());

	std::cout << "before erase\n";
	for (iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " -> " << it->second << "\n";

	iterator it = m.find(5);
	m.erase(it);
	std::cout << "after erase\n";
	for (iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " -> " << it->second << "\n";
}
