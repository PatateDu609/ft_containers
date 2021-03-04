/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:23:13 by gboucett          #+#    #+#             */
/*   Updated: 2021/03/04 22:14:50 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void maps()
{
	// title("TESTS ABOUT FT::MAP", -1);

	ft::RBTree<int, std::less<int> > rbt;

	rbt.insert(2);
	rbt.insert(2);
	rbt.insert(2);
	rbt.insert(2);
	rbt.insert(2);

	rbt.insert(5);
	rbt.insert(5);
	rbt.insert(5);
	rbt.insert(5);

	rbt.insert(1);
	rbt.insert(1);

	rbt.insert(4);
	rbt.insert(4);
	rbt.insert(4);
	rbt.insert(4);
	rbt.insert(4);
	rbt.insert(4);

	rbt.insert(7);
	rbt.insert(7);
	rbt.insert(7);
	rbt.insert(7);
	rbt.insert(7);
	rbt.insert(7);
	rbt.insert(7);
	rbt.insert(7);
	rbt.insert(7);

	rbt.insert(3);
	rbt.insert(3);
	rbt.insert(3);

	rbt.insert(6);
	rbt.insert(6);
	rbt.insert(6);
	rbt.insert(6);
	rbt.insert(6);
	rbt.insert(6);
	rbt.insert(6);
	rbt.insert(6);

	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);

	rbt.insert(98);
	rbt.insert(98);
	rbt.insert(98);
	rbt.insert(98);

	rbt.insert(8);
	rbt.insert(8);
	rbt.insert(8);

	std::cout << "max_size : " << rbt.max_size() << std::endl;

	typedef ft::RBTree<int, std::less<int> >::const_iterator iterator;

	const ft::RBTree<int, std::less<int> > rbt1 = rbt;

	std::pair<iterator, iterator> eq = rbt1.equal_range(98);

	std::cout << "Range :";
	for (; eq.first != eq.second; eq.first++)
		std::cout << " " << *eq.first;
	std::cout << std::endl;
	dumpRBT(rbt, "rbt.dot");
}
