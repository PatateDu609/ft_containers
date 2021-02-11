/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 19:03:54 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/11 14:51:48 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_HPP
#define TESTS_HPP

#include "List.hpp"

#include <iostream>
#include <list>
#include <typeinfo>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

enum Rich
{
	RESET = 0,
	BOLD = 1,
	UNDERLINE = 4,
	ITALIC = 3,
	INVERSE = 7
};

std::string color(bool reset, int r = 0, int g = 0, int b = 0, bool fg = true);
std::string construct(int number);
std::string rich(Rich mode);
void title(std::string str, int level = 0);
void lists();

#endif
