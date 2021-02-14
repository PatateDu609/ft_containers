/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 02:56:56 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/14 03:03:55 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void stacks()
{
	ft::Stack<int> s;

	for (int i = 0; i < 10; i++)
		s.push(i);

	std::cout << "Size : " << s.size() << std::endl;

	while (!s.empty())
	{
		std::cout << s.top() << std::endl;
		s.pop();
	}

	std::stack<int> ss;

	for (int i = 0; i < 10; i++)
		ss.push(i);

	std::cout << "Size : " << ss.size() << std::endl;

	while (!ss.empty())
	{
		std::cout << ss.top() << std::endl;
		ss.pop();
	}
}
