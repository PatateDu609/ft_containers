/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:49:51 by gboucett          #+#    #+#             */
/*   Updated: 2020/11/01 17:56:24 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include <map>

void maps()
{
	ft::Map<std::string, int> map;
	std::map<std::string, int> smap;

	std::cout << "Max size ft::Map<std::string, int> : " << map.max_size() << std::endl;
	std::cout << "Max size std::map<std::string, int> : " << smap.max_size() << std::endl;

	std::cout << "The map is " << (map.empty() ? "" : "not ") << "empty" << std::endl;
	map["test"] = 5;
	std::cout << "The map is " << (map.empty() ? "" : "not ") << "empty" << std::endl;
	std::cout << map["test"] << std::endl;
	map["test"] = 55;
	std::cout << map["test"] << std::endl;
}
