/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rich.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 19:08:50 by gboucett          #+#    #+#             */
/*   Updated: 2020/08/02 20:03:05 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

std::string color(bool reset, int r, int g, int b, bool fg)
{
	if (reset)
		return ("\033[0m");
	std::stringstream oss;
	oss << "\033[";
	if (fg)
		oss << "38;2";
	else
		oss << "48;2";
	oss << ";" << r << ";" << g << ";" << b << "m";
	return oss.str();
}

std::string construct(int number)
{
	std::stringstream oss;
	oss << "\033[" << number << "m";
	return oss.str();
}

std::string rich(Rich mode)
{
	switch (mode)
	{
	case RESET:
		return color(true);
	default:
		return construct(mode);
	}
}

void title(std::string str, int level)
{
	switch (level)
	{
	case -1:
		std::cout << color(false, 168, 50, 70, false) << color(false, 51, 194, 255) << rich(BOLD) << rich(ITALIC);
		break;
	case 0:
		std::cout << color(false, 92, 154, 255, false) << color(false, 222, 202, 186) << rich(BOLD) << rich(ITALIC);
		break;
	case 1:
		std::cout << color(false, 9, 217, 106) << rich(ITALIC) << rich(UNDERLINE);
		break;
	case 2:
		std::cout << color(false, 132, 73, 224) << rich(ITALIC);
	}
	std::cout << str;
	std::cout << rich(RESET) << std::endl;
}
