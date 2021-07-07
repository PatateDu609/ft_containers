/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:44:44 by gboucett          #+#    #+#             */
/*   Updated: 2021/07/07 21:22:03 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include <vector> // Used to separate tests of map and tests of vector...

static bool print = true;

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const ft::pair<T1, T2> &p)
{
	os << "(" << p.first << ", " << p.second << ")";
	return os;
}

template <typename Key, typename T, typename Compare, typename Alloc>
static std::ostream &operator<<(std::ostream &os, const ft::map<Key, T, Compare, Alloc> &x)
{
	if (x.empty() && print)
		return os << "is empty";
	else if (x.empty())
		return os;

	for (typename ft::map<Key, T, Compare, Alloc>::const_iterator it = x.begin(), it1 = ++x.begin(); it != x.end(); it++)
	{
		os << *it;
		if (it1 != x.end())
		{
			os << " ";
			it1++;
		}
	}
	return os;
}

static std::vector<ft::pair<int, int> > generate_data(int n = 20, bool use_i = true)
{
	std::vector<ft::pair<int, int> > v;

	std::cout << "Initial data :";
	for (int i = 0; i < n; i++)
	{
		v.push_back(ft::make_pair(use_i ? i : rand() % 100, rand() % 100));
		std::cout << " " << v.back();
	}
	std::cout << std::endl;
	return v;
}

static void test_map_constructors()
{
	title("TEST MAP CONSTRUCTORS");

	{
		title("Default constructor", 1);
		ft::map<int, int> m;
		std::cout << "The map : " << m << std::endl;
	}
	{
		title("Range constructor", 1);
		std::vector<ft::pair<int, int> > v = generate_data();

		ft::map<int, int> m(v.begin(), v.end());

		std::cout << "The map : " << m << std::endl;
	}
}

static void test_map_comparators()
{
	title("TEST MAP COMPARATORS");

	std::vector<ft::pair<int, int> > v = generate_data(10, false);

	ft::map<int, int, ft::greater<int> > m(v.begin(), v.end()); // should sort in reverse order
	ft::map<int, int> m1(v.begin(), v.end());					// should sort in reverse order

	std::cout << "m (comparator = greater): " << m << std::endl;
	std::cout << "m1 (comparator = less): " << m1 << std::endl;
}

static void test_map_copy()
{
	title("TEST MAP COPY");

	{
		title("Test copy constructor", 1);
		std::vector<ft::pair<int, int> > v = generate_data(10, false);
		ft::map<int, int> m(v.begin(), v.end());
		ft::map<int, int> m1(m);

		std::cout << "ininitial m : " << m << std::endl;
		std::cout << "copied m1 : " << m1 << std::endl;
	}
	{
		title("Test operator=", 1);
		std::vector<ft::pair<int, int> > v = generate_data(10);
		std::vector<ft::pair<int, int> > v1 = generate_data(10, false);

		std::cout << std::endl;
		ft::map<int, int> m(v.begin(), v.end());
		ft::map<int, int> m1(v1.begin(), v1.end());

		std::cout << "m with v : " << m << std::endl;
		std::cout << "m1 with v1 : " << m1 << std::endl
				  << std::endl;
		m1 = m;
		std::cout << "m with v : " << m << std::endl;
		std::cout << "m1 copied (should be same as m): " << m1 << std::endl;
	}
}

void maps()
{
	title("TESTS ABOUT FT::MAP", -1);
	test_map_constructors();
	test_map_comparators();
	test_map_copy();
}
