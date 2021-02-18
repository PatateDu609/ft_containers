/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queues.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 02:55:50 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/18 17:08:39 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

template <typename T, typename Container>
std::ostream& operator<<(std::ostream& os, ft::Queue<T, Container> queue)
{
	if (queue.empty())
		return os << "empty";
	os << queue.front();
	queue.pop();
	while (queue.size())
	{
		os << " " << queue.front();
		queue.pop();
	}
	return os;
}

static void test_queue_constructor()
{
	title("TEST QUEUE CONSTRUCTOR");

	{
		title("Constructor with no argument", 1);
		ft::Queue<int> q;
		std::cout << "The queue : " << q << std::endl;
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
		ft::Queue<int, std::deque<int> > q(d);
		std::cout << "The queue : " << q << std::endl;
	}
}

static void test_queue_size_push()
{
	title("TEST QUEUE SIZE/EMPTY/PUSH");

	ft::Queue<int> q;
	title("Test of empty", 1);
	std::cout << "The queue : " << q << std::endl;
	title("Test of size and push", 1);
	std::cout << "Size : " << q.size() << std::endl;
	for (int i = 0; i < 3; i++)
	{
		q.push(i);
		std::cout << "The queue : " << q << std::endl;
		std::cout << "Size : " << q.size() << std::endl;
	}
}

static void test_queue_accessers()
{
	title("TEST QUEUE ACCESSERS");
	ft::Queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	const ft::Queue<int> q1 = q;

	std::cout << "The queue of the test : " << q << std::endl;

	{
		title("Accessing the front element", 1);
		std::cout << "Front element : " << q.front() << std::endl;
	}
	{
		title("Accessing the back element", 1);
		std::cout << "Back element : " << q.back() << std::endl;
	}
	{
		title("Modifying the front element", 1);
		q.front() = 3;
		std::cout << "Front element : " << q.front() << std::endl;
	}
	{
		title("Modifying the back element", 1);
		q.back() = 1;
		std::cout << "Back element : " << q.back() << std::endl;
	}
	{
		title("Accessing the front element for const Queue", 1);
		std::cout << "Front element : " << q1.front() << std::endl;
	}
	{
		title("Accessing the back element for const Queue", 1);
		std::cout << "Back element : " << q1.back() << std::endl;
	}
	std::cout << "The queue after the front/back tests : " << q << std::endl;
}

void queues()
{
	title("TESTS ABOUT FT::QUEUE", -1);
	test_queue_constructor();
	test_queue_size_push();
	test_queue_accessers();
}
