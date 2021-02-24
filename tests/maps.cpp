/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teyber <teyber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:23:13 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/23 20:39:51 by teyber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void maps()
{
	// title("TESTS ABOUT FT::MAP", -1);

	ft::RBTree<int, std::less<int> > rbt;

	dumpRBT(rbt, "rbtstart.dot");
	std::cout << "Start size : " << rbt.size() << std::endl;

	rbt.printInOrder();
	rbt.printInReverseOrder();

	rbt.insert(2);
	rbt.insert(5);
	rbt.insert(1);
	rbt.insert(4);
	rbt.insert(7);

	rbt.printInOrder();
	rbt.printInReverseOrder();
	//rbt.insert(3);
	//rbt.insert(6);
	//rbt.insert(65);
	//rbt.insert(98);
	//rbt.insert(8);

	dumpRBT(rbt, "rbtfinal.dot");
}
