/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teyber <teyber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:23:13 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/23 02:22:29 by teyber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void maps()
{
	// title("TESTS ABOUT FT::MAP", -1);

	ft::RBTree<int, std::less<int> > rbt;

	dumpRBT(rbt, "rbtstart.dot");
	std::cout << "Start size : " << rbt.size() << std::endl;

	rbt.insert(2);
	std::cout << "size : " << rbt.size() << std::endl;
	rbt.insert(5);
	std::cout << "size : " << rbt.size() << std::endl;
	rbt.insert(1);
	std::cout << "size : " << rbt.size() << std::endl;
	rbt.insert(4);
	std::cout << "size : " << rbt.size() << std::endl;
	rbt.insert(7);
	std::cout << "size : " << rbt.size() << std::endl;
	rbt.insert(3);
	std::cout << "size : " << rbt.size() << std::endl;
	rbt.insert(6);
	std::cout << "size : " << rbt.size() << std::endl;
	rbt.insert(65);
	std::cout << "size : " << rbt.size() << std::endl;
	rbt.insert(98);
	std::cout << "size : " << rbt.size() << std::endl;
	rbt.insert(8);

	std::cout << "Final size : " << rbt.size() << std::endl;

	dumpRBT(rbt, "rbtfinal.dot");
}
