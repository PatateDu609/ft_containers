/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 02:56:56 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/18 17:18:05 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
template <typename T, typename Container>
std::ostream& operator<<(std::ostream& os, ft::Stack<T, Container> stack)
{
	if (stack.empty())
		return os << "empty";
	os << stack.top();
	stack.pop();
	while (stack.size())
	{
		os << " " << stack.top();
		stack.pop();
	}
	return os;
}

static void test_stack_constructor()
{
	title("TEST QUEUE CONSTRUCTOR");

	{
		title("Constructor with no argument", 1);
		ft::Stack<int> q;
		std::cout << "The stack : " << q << std::endl;
	}
	{
		title("Constructor with container_type argument", 1);
		std::deque<int> d;
		for (int i = 0; i < 10; i++)
			d.push_back(i);
		std::cout << "Container :";
		for (int i = 0; i < 10; i++)
			std::cout << " " << d[i];
		std::cout << std::endl;
		ft::Stack<int, std::deque<int> > q(d);
		std::cout << "The stack : " << q << std::endl;
	}
}

static void test_stack_size_push()
{
	title("TEST QUEUE SIZE/EMPTY/PUSH");

	ft::Stack<int> q;
	title("Test of empty", 1);
	std::cout << "The stack : " << q << std::endl;
	title("Test of size and push", 1);
	std::cout << "Size : " << q.size() << std::endl;
	for (int i = 0; i < 3; i++)
	{
		q.push(i);
		std::cout << "The stack : " << q << std::endl;
		std::cout << "Size : " << q.size() << std::endl;
	}
}

static void test_stack_accessers()
{
	title("TEST QUEUE ACCESSERS");
	ft::Stack<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	const ft::Stack<int> q1 = q;

	std::cout << "The stack before the tests : " << q << std::endl;
	std::cout << "top element : " << q.top() << std::endl;
	q.top() = 44;
	std::cout << "top element : " << q.top() << std::endl;
	std::cout << "top element but stack is const : " << q1.top() << std::endl;
	std::cout << "The stack after the tests : " << q << std::endl;
}

void stacks()
{
	title("TESTS ABOUT FT::QUEUE", -1);
	test_stack_constructor();
	test_stack_size_push();
	test_stack_accessers();
}
