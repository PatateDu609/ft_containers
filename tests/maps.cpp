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
	ft::map<int, int> map;

	map[0] = 0;
	map[1] = 1;
	map[2] = 2;
	map[3] = 3;
	map[4] = 4;
	map[1] = 4564;

	//for (iterator it = map.begin(); it != map.end(); it++)
	//std::cout << it->first << " - " << it->second << "\n";
}
