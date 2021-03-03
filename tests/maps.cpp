/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teyber <teyber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:23:13 by gboucett          #+#    #+#             */
/*   Updated: 2021/03/03 11:08:29 by teyber           ###   ########.fr       */
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

	rbt.erase(1);
	rbt.printInOrder();
	rbt.printInReverseOrder();

	rbt.erase(2);
	rbt.printInOrder();
	rbt.printInReverseOrder();

	rbt.erase(3);
	rbt.printInOrder();
	rbt.printInReverseOrder();

	rbt.erase(8);
	rbt.printInOrder();
	rbt.printInReverseOrder();

	rbt.erase(65);
	rbt.printInOrder();
	rbt.printInReverseOrder();

	rbt.erase(4);
	rbt.printInOrder();
	rbt.printInReverseOrder();

	rbt.erase(98);

	dumpRBT(rbt, "rbt1.dot");
	rbt.insert(252);
	//rbt.insert(252);

	rbt.printInOrder();
	rbt.printInReverseOrder();

	std::cout << "new size = " << rbt.size() << std::endl;

	dumpRBT(rbt, "rbt.dot");
}
