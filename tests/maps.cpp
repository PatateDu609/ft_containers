/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:23:13 by gboucett          #+#    #+#             */
/*   Updated: 2021/03/04 20:32:19 by gboucett         ###   ########.fr       */
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

	ft::RBTree<int, std::less<int> > rbt1;

	rbt1.insert(5);
	rbt1.insert(4);
	rbt1.insert(3);
	rbt1.insert(2);
	rbt1.insert(1);

	rbt1.printInOrder();
	rbt.printInOrder();

	rbt.swap(rbt1);

	rbt1.printInOrder();
	rbt.printInOrder();

	dumpRBT(rbt, "rbt.dot");
}
