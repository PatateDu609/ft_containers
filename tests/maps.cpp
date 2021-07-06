/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:23:13 by gboucett          #+#    #+#             */
/*   Updated: 2021/03/14 11:41:02 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include "RBTree.hpp"

typedef ft::RBTree<int>::iterator iterator;

void maps()
{
	ft::RBTree<int> rbt;

	rbt.insert(8);
	rbt.insert(3);
	rbt.insert(1);
	rbt.insert(6);
	rbt.insert(10);
	rbt.insert(14);
	rbt.insert(13);
	rbt.insert(7);
	rbt.insert(4);
	rbt.insert(55);
	rbt.insert(54);
	rbt.insert(407);
	rbt.insert(154);
	rbt.insert(100);
	rbt.insert(5252);

	std::cout << "lower bound : " << *rbt.lower_bound(55) << std::endl;
	std::cout << "upper bound : " << *rbt.upper_bound(55) << std::endl
			  << std::endl;
	std::cout << "lower bound : " << *rbt.lower_bound(9) << std::endl;
	std::cout << "upper bound : " << *rbt.upper_bound(9) << std::endl;

	rbt.dump("done.dot");
}
