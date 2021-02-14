/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queues.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 02:55:50 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/14 03:04:59 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void queues()
{
	ft::Queue<int> s;

	for (int i = 0; i < 10; i++)
		s.push(i);

	std::cout << "Size : " << s.size() << std::endl;

	while (!s.empty())
	{
		std::cout << s.front() << std::endl;
		s.pop();
	}

	std::queue<int> ss;

	for (int i = 0; i < 10; i++)
		ss.push(i);

	std::cout << "Size : " << ss.size() << std::endl;

	while (!ss.empty())
	{
		std::cout << ss.front() << std::endl;
		ss.pop();
	}
}
