/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:04:28 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/13 23:38:06 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

#include <cmath>

void vectors()
{
	ft::Vector<int> a(10, 0);
	ft::Vector<int> b(10, 1);

	std::cout << "a == b\t-> " << (a == b) << std::endl;
	std::cout << "a != b\t-> " << (a != b) << std::endl;
	std::cout << "a < b\t-> " << (a < b) << std::endl;
	std::cout << "a > b\t-> " << (a > b) << std::endl;
	std::cout << "a <= b\t-> " << (a <= b) << std::endl;
	std::cout << "a >= b\t-> " << (a >= b) << std::endl;
}
