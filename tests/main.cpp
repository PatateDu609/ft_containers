/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 19:54:09 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/18 17:22:21 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

int main()
{
	srand(time(NULL));

	if (VECTOR)
		vectors();
	if (STACK)
		stacks();
	if (MAP)
		maps();
	if (SET)
		sets();
	return (0);
}
