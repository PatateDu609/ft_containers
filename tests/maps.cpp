/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 20:44:44 by gboucett          #+#    #+#             */
/*   Updated: 2021/07/14 21:12:06 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include <vector> // Used to separate tests of map and tests of vector...

static bool print = true;

template<typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const ft::pair<T1, T2> &p)
{
	os << "(" << p.first << ", " << p.second << ")";
	return os;
}

template<typename Key, typename T, typename Compare, typename Alloc>
static std::ostream &operator<<(std::ostream &os, const ft::map<Key, T, Compare, Alloc> &x)
{
	if (x.empty() && print)
		return os << "is empty";
	else if (x.empty())
		return os;

	for (typename ft::map<Key, T, Compare, Alloc>::const_iterator it = x.begin(), it1 = ++x.begin();
	     it != x.end(); it++)
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
	ft::map<int, int> m1(v.begin(), v.end());                    // should sort in reverse order

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

		std::cout << "initial m : " << m << std::endl;
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

static void test_map_reverse_iterators()
{
	title("TEST MAP ITERATORS");

	typedef ft::map<int, int>::reverse_iterator reverse_iterator;
	typedef ft::map<int, int>::const_reverse_iterator const_reverse_iterator;
	typedef ft::map<int, int>::const_iterator const_iterator;

	std::vector<ft::pair<int, int> > v = generate_data(10);
	ft::map<int, int> m(v.begin(), v.end());
	const ft::map<int, int> m1(m);

	{
		title("Testing with non-const map", 1);
		std::cout << "The map (displayed with reverse_iterator):";
		for (reverse_iterator rit = m.rbegin(); rit != m.rend(); rit++)
			std::cout << " " << *rit;
		std::cout << std::endl;
		std::cout << "The map (displayed with const_iterator):";
		for (const_iterator it = m.begin(); it != m.end(); it++)
			std::cout << " " << *it;
		std::cout << std::endl;
		std::cout << "The map (displayed with const_reverse_iterator):";
		for (const_reverse_iterator rit = m.rbegin(); rit != m.rend(); rit++)
			std::cout << " " << *rit;
		std::cout << std::endl;
	}
	{
		title("Testing with const map", 1);

		std::cout << "The map (displayed with const_iterator):";
		for (const_iterator it = m1.begin(); it != m1.end(); it++)
			std::cout << " " << *it;
		std::cout << std::endl;
		std::cout << "The map (displayed with const_reverse_iterator):";
		for (const_reverse_iterator rit = m1.rbegin(); rit != m1.rend(); rit++)
			std::cout << " " << *rit;
		std::cout << std::endl;
	}
}

static void test_map_insertion()
{
	title("TESTS ABOUT INSERTION IN MAP", -1);

	{
		title("Test of operator[]", 1);

		ft::map<int, std::string> m;
		int random_key = rand() % 10 + 100;

		{
			title("Adding elements", 2);
			m[0] = "bonjour";
			m[1] = "yo mec";
			m[20000] = "bye mec";
			m[-213213] = "roi";
			m[random_key] = "oie"; // should be inserted between 1 and 20000

			std::cout << "The map after adding elements : " << m << std::endl;
		}
		{
			title("Editing some elements", 2);
			m[20000] = "hey mec";
			m[-213213] = "king";
			m[random_key] = "goose";

			std::cout << "The map after editing some elements : " << m << std::endl;
		}
	}
	{
		title("Tests of insert", 1);

		{
			title("Tests of insert with a value (inserting pairs of int)", 2);
			std::vector<ft::pair<int, int> > data = generate_data(3, false);
			ft::map<int, int> m;

			data.push_back(data.back());
			data.push_back(data.front());
			data.push_back(ft::make_pair(-12, 1212));

			for (size_t i = 0; i < data.size(); i++)
			{
				ft::pair<ft::map<int, int>::iterator, bool> p = m.insert(data[i]);
				std::string res = std::string(" ") + (p.second ? "was" : "was not");

				std::cout << *p.first << res << " inserted" << std::endl;
			}
			std::cout << "Final map : " << m << std::endl;
		}
		{
			title("Tests of insert with hint", 2);

			std::vector<ft::pair<int, int> > data = generate_data(10, false);
			ft::map<int, int> m;

			for (size_t i = 0; i < data.size(); i++)
			{
				ft::map<int, int>::iterator it = m.insert(m.end(), data[i]);

				std::cout << "Returned iterator : " << *it << std::endl;
			}
			std::cout << "Final map : " << m << std::endl;
		}
		{
			title("Tests of insert with range", 2);

			std::vector<ft::pair<int, int> > data = generate_data(10, false);
			ft::map<int, int> m;

			m.insert(data.begin(), data.end());
			std::cout << "Final map : " << m << std::endl;
		}
	}
}

static void test_map_erase()
{
	title("TESTS ABOUT ERASE");

	{
		title("Clearing a map", 1);

		std::vector<ft::pair<int, int> > data = generate_data(15);
		ft::map<int, int> m(data.begin(), data.end());

		std::cout << "The map before clear : " << m << std::endl;
		m.clear();
		std::cout << "The map after clear : " << m << std::endl;

		std::cout << "\n\nTrying to reinsert new elements..." << std::endl;

		data = generate_data(10, false);
		m.insert(data.begin(), data.end());

		std::cout << "The map before clear : " << m << std::endl;
		m.clear();
		std::cout << "The map after clear : " << m << std::endl;
	}
	{
		title("Tests of erase", 1);
		std::vector<ft::pair<int, int> > data = generate_data(15);

		{
			title("Trying to erase a specific iterator", 2);

			ft::map<int, int> m(data.begin(), data.end());

			std::cout << "Initial map : " << m << std::endl;
			std::cout << "Erasing " << *m.begin() << std::endl;
			m.erase(m.begin());
			std::cout << "The map after one erase : " << m << std::endl;
			std::cout << "Erasing " << *++m.begin() << std::endl;
			m.erase(++m.begin());
			std::cout << "The map after two erases : " << m << std::endl;
		}
		{
			title("Trying to erase specific value", 2);

			ft::map<int, int> m(data.begin(), data.end()); // Keys are from 0 to 14 inclusive

			std::cout << "Initial map : " << m << std::endl;
			std::cout << "Erasing " << 12 << std::endl;
			std::cout << "RESULT : " << m.erase(12) << std::endl;
			std::cout << "The map after one erase : " << m << std::endl;
			std::cout << "Erasing " << 23 << std::endl; // Nonexistent key...
			std::cout << "RESULT : " << m.erase(23) << std::endl;
			std::cout << "The map after two erases : " << m << std::endl; // should be same as before
		}
		{
			title("Trying to remove multiple elements at once", 2);

			ft::map<int, int> m(data.begin(), data.end());

			std::cout << "Initial map : " << m << std::endl;
			m.erase(++m.begin(), m.end()); // To keep erase from calling clear (already tested)
			std::cout << "The map after erasing : " << m << std::endl;
		}
	}
}

static void test_map_capacity()
{
	title("TESTS ABOUT MAP CAPACITY");

	ft::map<int, int> m;

	std::cout << "max_size : " << m.max_size() << std::endl;
	std::cout << "empty : " << std::boolalpha << m.empty() << std::noboolalpha << std::endl;
	std::cout << "size : " << m.size() << std::endl;

	m[0] = 123124;
	std::cout << "empty : " << std::boolalpha << m.empty() << std::noboolalpha << std::endl;
	std::cout << "size : " << m.size() << std::endl;

	m[0] = 232;
	std::cout << "empty : " << std::boolalpha << m.empty() << std::noboolalpha << std::endl;
	std::cout << "size : " << m.size() << std::endl;

	m[12] = 232;
	std::cout << "empty : " << std::boolalpha << m.empty() << std::noboolalpha << std::endl;
	std::cout << "size : " << m.size() << std::endl;
}

static void test_map_swap()
{
	title("TESTS ABOUT MAP SWAPPING");

	ft::map<int, std::string>::iterator it, it1;

	ft::map<int, std::string> m;

	m[0] = "bonjour";
	m[1] = "yo mec";
	m[20000] = "bye mec";
	m[-213213] = "roi";
	m[212] = "oie";

	ft::map<int, std::string> m1;
	m1[1243] = "oppo";
	m1[1324] = "samsung";

	it = m.begin();
	it1 = m1.begin();

	std::cout << "Iterators : it -> " << *it << ", it1 -> " << *it1 << std::endl;

	std::cout << "The first map : " << m << std::endl;
	std::cout << "The second map : " << m1 << std::endl;
	m.swap(m1);
	std::cout << "The first map : " << m << std::endl;
	std::cout << "The second map : " << m1 << std::endl;

	std::cout << "Iterators : it -> " << *it << ", it1 -> " << *it1 << std::endl; // should not segfault nor swap

	swap(m, m1);
	std::cout << "The first map : " << m << std::endl;
	std::cout << "The second map : " << m1 << std::endl;

	std::cout << "Iterators : it -> " << *it << ", it1 -> " << *it1 << std::endl; // same as before
}

void test_map_operation()
{
	title("TESTS OF MAP OPERATIONS");

	typedef ft::map<int, int>::iterator iterator;

	std::vector<ft::pair<int, int> > data = generate_data(20);
	ft::map<int, int> m(data.begin(), data.end());

	{
		title("Testing find", 1);

		std::cout << "Trying to find an existing element" << std::endl;
		iterator it = m.find(12); //existing element
		if (it == m.end())
			std::cout << "Element not found" << std::endl;
		else
			std::cout << "Element found : " << *it << std::endl;

		std::cout << "Trying to find a nonexistent element" << std::endl;
		it = m.find(112); //nonexistent element
		if (it == m.end())
			std::cout << "Element not found" << std::endl;
		else
			std::cout << "Element found : " << *it << std::endl;
	}
	{
		title("Testing count", 1);

		std::cout << "There is " << m.count(12) << " elements with 12 as their key."
		          << std::endl; //existing element
		std::cout << "There is " << m.count(1212) << " elements with 1212 as their key."
		          << std::endl; //nonexistent element
	}
	{
		title("Testing upper_bound and lower_bound", 1);

		iterator u, l;

		std::cout << "Upper and lower bound of existing element :" << std::endl;
		u = m.upper_bound(10);
		l = m.lower_bound(10);
		std::cout << "Upper bound : " << *u << ", lower bound : " << *l << std::endl;

		std::cout << "Upper and lower bound of nonexistent element :" << std::endl;
		u = m.upper_bound(-10);
		l = m.lower_bound(-10);
		std::cout << "Upper bound : " << *u << ", lower bound : " << *l << std::endl;

		std::cout << "Upper and lower bound of erased element :" << std::endl;
		m.erase(10);
		u = m.upper_bound(10);
		l = m.lower_bound(10);
		std::cout << "Upper bound : " << *u << ", lower bound : " << *l << std::endl;
	}{
		title("Testing equal_range", 1);

		ft::pair<iterator, iterator> ul;

		std::cout << "Upper and lower bound of existing element :" << std::endl;
		ul = m.equal_range(11);
		std::cout << "Upper bound : " << *ul.first << ", lower bound : " << *ul.second << std::endl;

		std::cout << "Upper and lower bound of nonexistent element :" << std::endl;
		ul = m.equal_range(-10);
		std::cout << "Upper bound : " << *ul.first << ", lower bound : " << *ul.second << std::endl;

		std::cout << "Upper and lower bound of erased element :" << std::endl;
		m.erase(11);
		ul = m.equal_range(11);
		std::cout << "Upper bound : " << *ul.first << ", lower bound : " << *ul.second << std::endl;
	}
}

static void test_map_relational()
{
	title("TESTING RELATIONAL OPERATORS");

	ft::map<int, int> m, m1, m2;

	m[0] = 121;
	m[-12] = 1;
	m[20] = 0;

	m1[1] = 121;
	m1[-12] = 2;
	m1[12] = 0;

	m2 = m;

	std::cout << "Displaying m : " << m << std::endl;
	std::cout << "Displaying m1 : " << m1 << std::endl;
	std::cout << "Displaying m2 : " << m2 << std::endl;

	std::cout << std::boolalpha;
	std::cout << "m == m1 = " << (m == m1) << std::endl;
	std::cout << "m != m1 = " << (m != m1) << std::endl;
	std::cout << "m < m1 = " << (m < m1) << std::endl;
	std::cout << "m <= m1 = " << (m <= m1) << std::endl;
	std::cout << "m > m1 = " << (m > m1) << std::endl;
	std::cout << "m >= m1 = " << (m >= m1) << std::endl << std::endl;

	std::cout << "m == m2 = " << (m == m2) << std::endl;
	std::cout << "m != m2 = " << (m != m2) << std::endl;
	std::cout << "m < m2 = " << (m < m2) << std::endl;
	std::cout << "m <= m2 = " << (m <= m2) << std::endl;
	std::cout << "m > m2 = " << (m > m2) << std::endl;
	std::cout << "m >= m2 = " << (m >= m2) << std::endl;
	std::cout << std::noboolalpha;
}

void maps()
{
	title("TESTS ABOUT FT::MAP", -1);
	test_map_constructors();
	test_map_comparators();
	test_map_copy();
	test_map_reverse_iterators();
	test_map_insertion();
	test_map_erase();
	test_map_capacity();
	test_map_swap();
	test_map_operation();
	test_map_relational();
}
