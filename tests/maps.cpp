/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teyber <teyber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:23:13 by gboucett          #+#    #+#             */
/*   Updated: 2021/03/01 03:20:14 by teyber           ###   ########.fr       */
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
	rbt.insert(5);
	rbt.insert(5);
	rbt.insert(5);
	rbt.insert(5);
	rbt.insert(5);
	rbt.insert(1);
	rbt.insert(1);
	rbt.insert(1);
	rbt.insert(1);
	rbt.insert(1);
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
	rbt.insert(3);
	rbt.insert(3);
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
	rbt.insert(6);
	rbt.insert(6);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.erase(5);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(65);
	rbt.insert(98);
	rbt.insert(98);
	rbt.insert(98);
	rbt.insert(98);
	rbt.insert(98);
	rbt.insert(98);
	rbt.insert(8);
	rbt.erase(65);
	rbt.erase(1);
	rbt.insert(8);
	rbt.insert(8);


	dumpRBT(rbt, "rbt.dot");
}
