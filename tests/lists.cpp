/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 19:03:59 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/11 14:54:01 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

template <typename T>
static std::ostream &operator<<(std::ostream &os, const ft::List<T> &x)
{
	if (x.empty())
		return os;
	for (typename ft::List<T>::const_iterator it = x.begin(), it1 = ++x.begin(); it != x.end(); ++it)
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

static bool are_both_odd(const int &a, const int &b)
{
	return a % 2 && b % 2;
}

static bool is_odd(const int& a)
{
	return a % 2;
}

static void test_list_constructors()
{
	title("TEST LIST CONSTRUCTORS");

	{
		title("Default constructor", 1);
		ft::List<int> l;
		std::cout << "The list : " << l << std::endl;
	}
	{
		title("Fill constructor (with default value)", 1);
		ft::List<int>::size_type size = 5;
		ft::List<int> l(size);
		std::cout << "The list (should contain " << size << " element(s)) : " << l << std::endl;
	}
	{
		title("Fill constructor (with given value)", 1);
		ft::List<int>::size_type size = 5;
		int value = 100;
		ft::List<int> l(size, value);
		std::cout << "The list (should contain " << size << " element(s)) : " << l << std::endl;
	}
	{
		title("Range constructor", 1);
		ft::List<int> l(5, 100);
		ft::List<int> l1(l.begin(), ++(++l.begin()));
		std::cout << "The list constructed by fill constructor : " << l << std::endl;
		std::cout << "The list constructed by range constructor : " << l1 << std::endl;
	}
	{
		title("Copy constructor", 1);
		ft::List<int> l(5, 200);
		ft::List<int> l1(l);
		std::cout << "The list constructed by fill constructor : " << l << std::endl;
		std::cout << "The list constructed by copy constructor : " << l1 << std::endl;
	}
}

static void test_list_copy()
{
	title("TEST LIST COPY OPERATOR");
	ft::List<std::string> l(5, "bonjour");
	decltype(l) l1;
	l1 = l;
	std::cout << "The list constructed by fill constructor :\t" << l << std::endl;
	std::cout << "The list after the copy :\t\t\t" << l1 << std::endl;
}

static void test_list_capacity()
{
	title("TEST LIST CAPACITY");

	{
		title("Is the list empty ?", 1);
		ft::List<int> l;
		std::cout << "The list (" << l << ") is : " << (l.empty() ? "empty" : "not empty") << std::endl;
		ft::List<int> l1(5, 10);
		std::cout << "The list (" << l1 << ") is : " << (l1.empty() ? "empty" : "not empty") << std::endl;
	}
	{
		title("The size of the list", 1);
		ft::List<int> l;
		std::cout << "The list (" << l << ") has " << l.size() << " element(s)" << std::endl;
		ft::List<int> l1(5, 10);
		std::cout << "The list (" << l1 << ") has " << l1.size() << " element(s)" << std::endl;
		ft::List<int> l2(1, 100);
		std::cout << "The list (" << l2 << ") has " << l2.size() << " element(s)" << std::endl;
	}
	{
		title("The maximum size of a list is :", 1);
		ft::List<int> l;
		std::cout << l.max_size() << std::endl;
	}
}

static void test_list_relational()
{
	title("TEST LIST RELATIONAL OPERATIONS");

	ft::List<int> a;
	ft::List<int> b;
	ft::List<int> c;

	a.push_back(10);
	a.push_back(20);
	a.push_back(30);

	b.push_back(10);
	b.push_back(20);
	b.push_back(30);

	c.push_back(30);
	c.push_back(20);
	c.push_back(10);

	if (a == b)
		std::cout << "a and b are equal\n";
	if (b != c)
		std::cout << "b and c are not equal\n";
	if (b < c)
		std::cout << "b is less than c\n";
	if (c > b)
		std::cout << "c is greater than b\n";
	if (a <= b)
		std::cout << "a is less than or equal to b\n";
	if (a >= b)
		std::cout << "a is greater than or equal to b\n";
}

static void test_list_swap_non_member()
{
	title("TEST LIST SWAP (NON MEMBER FUNCTION)");
	ft::List<int> foo(3, 100); // three ints with a value of 100
	ft::List<int> bar(5, 200); // five ints with a value of 200

	title("Before swapping :", 1);
	std::cout << "foo contains: " << foo << std::endl;
	std::cout << "bar contains: " << bar << std::endl;

	ft::swap(foo, bar);

	title("After swapping :", 1);
	std::cout << "foo contains: " << foo << std::endl;
	std::cout << "bar contains: " << bar << std::endl;
}

static void test_list_swap_member()
{
	title("TEST LIST SWAP (MEMBER FUNCTION)");
	ft::List<int> foo(3, 200);	// three ints with a value of 100
	ft::List<int> bar(5, 1100); // five ints with a value of 200

	title("Before swapping :", 1);
	std::cout << "foo contains: " << foo << std::endl;
	std::cout << "bar contains: " << bar << std::endl;

	foo.swap(bar);

	title("After swapping :", 1);
	std::cout << "foo contains: " << foo << std::endl;
	std::cout << "bar contains: " << bar << std::endl;
}

static void test_list_modifiers_insertions()
{
	title("TEST LIST INSERTION METHODS");

	{
		title("Testing push_front", 1);
		ft::List<int> l;
		for (int i = 5; i >= 0; i--)
		{
			std::cout << "The list :\t\t" << l << std::endl;
			l.push_front(i);
		}
		std::cout << "The final list :\t" << l << std::endl;
	}
	{
		title("Testing push_back", 1);
		ft::List<int> l;
		for (int i = 0; i <= 5; i++)
		{
			std::cout << "The list :\t\t" << l << std::endl;
			l.push_back(i);
		}
		std::cout << "The final list :\t" << l << std::endl;
	}
	{
		title("Tesing insert", 1);
		{
			title("Inserting a single element", 2);
			ft::List<int> l(5, 10);
			std::cout << "The list before the insertion : " << l << std::endl;
			decltype(l)::iterator it = l.begin();
			for (decltype(l)::size_type i = 0; i < l.size() - 1; i++)
				it++;
			auto res = l.insert(it, 111);
			std::cout << "The list after the insertion : " << l << std::endl;
			std::cout << "iterator returned = " << *res << std::endl;
			res = l.insert(l.begin(), 222);
			std::cout << "The list after the insertion : " << l << std::endl;
			std::cout << "iterator returned = " << *res << std::endl;
			res = l.insert(l.end(), 5784);
			std::cout << "The list after the insertion : " << l << std::endl;
			std::cout << "iterator returned = " << *res << std::endl;
		}
		{
			title("Inserting new elements", 2);
			ft::List<int> l(5, 10);
			std::cout << "The list before the insertion : " << l << std::endl;
			decltype(l)::iterator it = l.begin();
			for (decltype(l)::size_type i = 0; i < l.size() - 1; i++)
				it++;
			l.insert(it, 5, -11);
			std::cout << "The list after the insertion : " << l << std::endl;
		}
		{
			title("Inserting a range of new elements", 2);
			ft::List<int> l;
			l.push_back(1);
			l.push_back(2);
			l.push_back(3);
			ft::List<int> l1(5, 10);
			std::cout << "The list before the insertion : " << l1 << std::endl;
			l1.insert(l1.end(), l.begin(), l.end());
			std::cout << "The list after the insertion : " << l1 << std::endl;
		}
	}
	{
		title("Assigning a list", 1);
		{
			title("Fill version", 2);
			ft::List<int> l(5);
			std::cout << "The list before assigning : " << l << std::endl;
			l.assign(5, 10);
			std::cout << "The list after assigning : " << l << std::endl;
		}
		{
			title("Range version", 2);
			ft::List<int> l(5);
			ft::List<int> l1;
			l1.push_back(1);
			l1.push_back(2);
			l1.push_back(3);
			std::cout << "The list before assigning : " << l << std::endl;
			l.assign(l1.begin(), l1.end());
			std::cout << "The list after assigning : " << l << std::endl;
		}
	}
}

static void test_list_accessers()
{
	title("TEST LIST ACCESSERS");
	ft::List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	std::cout << "The list of the test : " << l << std::endl;

	{
		title("Accessing the front element", 1);
		std::cout << "Front element : " << l.front() << std::endl;
	}
	{
		title("Accessing the back element", 1);
		std::cout << "Back element : " << l.back() << std::endl;
	}
	{
		title("Modifying the front element", 1);
		l.front() = 3;
		std::cout << "Front element : " << l.front() << std::endl;
	}
	{
		title("Modifying the back element", 1);
		l.back() = 1;
		std::cout << "Back element : " << l.back() << std::endl;
	}
	std::cout << "The list after the tests : " << l << std::endl;
}

static void test_list_reverse_iterators()
{
	title("TEST LIST ITERATORS (AS LVALUE AND RVALUE)");

	ft::List<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);

	std::cout << "The list (displayed with the standard iterator) : " << l << std::endl;

	std::cout << "The list (displayed with the reverse iterator) : ";
	for (decltype(l)::reverse_iterator revit = l.rbegin(); revit != l.rend(); revit++)
		std::cout << " " << *revit;
	std::cout << std::endl;
	const decltype(l) l1(l);
	std::cout << "The list (displayed with the const iterator) : ";
	for (decltype(l1)::const_iterator it = l1.begin(); it != l1.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;
	std::cout << "The list (displayed with the const reverse iterator) : ";
	for (decltype(l1)::const_reverse_iterator revit = l1.rbegin(); revit != l1.rend(); revit++)
		std::cout << " " << *revit;
	std::cout << std::endl;
}

static void test_list_resize()
{
	title("TEST LIST RESIZING");

	{
		title("Shrinking list", 1);
		ft::List<int> l(10, 22);
		std::cout << "List before calling resize : " << l << std::endl;
		l.resize(5);
		std::cout << "List after calling resize :  " << l << std::endl;
	}
	{
		title("Extending list", 1);
		{
			title("With default value", 2);
			ft::List<int> l(2, 22);
			std::cout << "List before calling resize : " << l << std::endl;
			l.resize(5);
			std::cout << "List after calling resize :  " << l << std::endl;
		}
		{
			title("With given value", 2);
			ft::List<int> l(2, 22);
			std::cout << "List before calling resize : " << l << std::endl;
			l.resize(5, 11);
			std::cout << "List after calling resize :  " << l << std::endl;
		}
	}
}

static void test_list_deleting_elements()
{
	title("TEST LIST DELETING ELEMENTS");

	{
		title("Test of pop_back", 1);
		ft::List<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		std::cout << "The list before popping everything : " << l << std::endl;
		l.pop_back();
		l.pop_back();
		l.pop_back();
		std::cout << "The list after popping everything : " << l << std::endl;
		std::cout << "Checking that everything went well by adding new elements to the list" << std::endl;
		l.push_back(4);
		l.push_back(5);
		l.push_back(6);
		std::cout << "The list before popping everything : " << l << std::endl;
		l.pop_back();
		std::cout << "The list after popping one element : " << l << std::endl;
	}
	{
		title("Test of pop_front", 1);
		ft::List<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		std::cout << "The list before popping everything : " << l << std::endl;
		l.pop_front();
		l.pop_front();
		l.pop_front();
		std::cout << "The list after popping everything : " << l << std::endl;
		std::cout << "Checking that everything went well by adding new elements to the list" << std::endl;
		l.push_back(4);
		l.push_back(5);
		l.push_back(6);
		std::cout << "The list before popping everything : " << l << std::endl;
		l.pop_front();
		std::cout << "The list after popping everything : " << l << std::endl;
	}
	{
		title("Test of clear", 1);
		ft::List<int> l(10, 5);
		std::cout << "The list before clearing it : " << l << std::endl;
		l.clear();
		std::cout << "The list after clearing it : " << l << std::endl;
	}
	{
		title("Tests of erase", 1);
		{
			title("Erasing a single element", 2);
			ft::List<int> l;
			l.push_back(1);
			l.push_back(2);
			l.push_back(3);
			l.push_back(4);
			l.push_back(5);
			l.push_back(6);
			l.push_back(7);
			l.push_back(8);
			l.push_back(9);
			l.push_back(10);
			std::cout << "The list before erasing anything : " << l << std::endl;

			for (decltype(l)::iterator it = l.begin(); !l.empty(); it++)
			{
				auto res = l.erase(it);
				std::cout << "The list now (element following the erased one : ";
				if (!l.empty())
					std::cout << *res;
				std::cout << ") : " << l << std::endl;
			}
		}
		{
			title("Erasing a range of elements", 2);
			ft::List<int> l;
			l.push_back(1);
			l.push_back(2);
			l.push_back(3);
			l.push_back(4);
			l.push_back(5);
			l.push_back(6);
			l.push_back(7);
			l.push_back(8);
			l.push_back(9);
			l.push_back(10);
			std::cout << "The list before erasing anything : " << l << std::endl;

			decltype(l)::iterator it = l.begin();
			for (int i = 0; i < 3; i++)
				it++;
			decltype(it) it1 = it;
			for (int i = 0; i < 3; i++)
				it1++;
			l.erase(it, it1);
			std::cout << "The list after erasing : " << l << std::endl;
		}
	}
}

static void test_list_unary_operations()
{
	title("TEST OPERATIONS UNARY OPERATIONS");
	srand(time(NULL));


	{
		title("Test of reverse", 1);
		ft::List<int> l;
		l.push_back(0);
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_back(5);
		l.push_back(6);
		l.push_back(7);
		l.push_back(8);
		l.push_back(9);
		std::cout << "The list before reversing it : " << l << std::endl;
		l.reverse();
		std::cout << "The list after the reverse :   " << l << std::endl;
	}
	{
		title("Test of sort", 1);
		ft::List<int> l;
		{
			title("With operator<", 2);
			for (int i = 0; i < 10; i++)
				l.push_back(rand() % 10);
			std::cout << "List before sorting : " << l << std::endl;
			l.sort();
			std::cout << "List after sorting : " << l << std::endl;
		}
		{
			title("With custom operator", 2);
			l.clear();
			for (int i = 0; i < 10; i++)
				l.push_back(rand() % 10);
			std::cout << "List before sorting : " << l << std::endl;
			l.sort(ft::great<int>());
			std::cout << "List after sorting : " << l << std::endl;
		}
	}
	{
		title("Tests for remove and remove_if", 1);
		{
			title("Test of remove", 2);
			ft::List<int> l;
			l.push_back(0);
			l.push_back(1);
			l.push_back(0);
			l.push_back(0);
			l.push_back(0);
			l.push_back(1);
			l.push_back(1);
			l.push_back(0);
			l.push_back(1);
			l.push_back(3);
			l.push_back(0);
			l.push_back(2);
			l.push_back(4);
			l.push_back(0);
			l.push_back(0);
			std::cout << "Test before removing anything : " << l << std::endl;
			l.remove(0);
			std::cout << "Test after removing all 0 : " << l << std::endl;
		}
		{
			title("Test of remove_if", 2);
			ft::List<int> l;
			for (int i = 0; i < 15; i++)
				l.push_back(rand() % 10);
			std::cout << "Test before removing anything : " << l << std::endl;
			l.remove_if(is_odd);
			std::cout << "Test after removing all odd numbers : " << l << std::endl;
		}
		{
			title("Test of unique", 1);
			ft::List<int> l;
			{
				title("Without predicate", 2);
				for (int i = 0; i < 15; i++)
					l.push_back(rand() % 10);
				l.sort();
				std::cout << "The list before calling unique : " << l << std::endl;
				l.unique();
				std::cout << "The list after calling unique : " << l << std::endl;
			}
			{
				title("With predicate", 2);
				for (int i = 0; i < 15; i++)
					l.push_back(rand() % 10);
				l.sort();
				std::cout << "The list before calling unique : " << l << std::endl;
				l.unique(are_both_odd);
				std::cout << "The list after calling unique (criteria : both odd) : " << l << std::endl;
			}
		}
	}
}

static void test_list_binary_operations()
{
	title("TEST LIST BINARY OPERATIONS");

	{
		title("Tests of splice", 1);
		{
			title("Transfer entire list", 2);
			ft::List<int> l;
			ft::List<int> l1;
			l.push_back(0);
			l.push_back(1);

			l1.push_back(5);
			l1.push_back(6);
			l1.push_back(7);
			std::cout << "The source list : " << l1 << std::endl;
			std::cout << "The target list before calling splice : " << l << std::endl;
			l.splice(l.end(), l1);
			std::cout << "The source list after splice : " << l1 << std::endl;
			std::cout << "The target list after calling splice : " << l << std::endl;

			l1.push_back(-3);
			l1.push_back(-2);
			l1.push_back(-1);
			std::cout << "The source list : " << l1 << std::endl;
			l.splice(l.begin(), l1);
			std::cout << "The source list after splice : " << l1 << std::endl;
			std::cout << "The target list after calling splice a second time : " << l << std::endl;

			l1.push_back(2);
			l1.push_back(3);
			l1.push_back(4);
			std::cout << "The source list : " << l1 << std::endl;
			auto it = l.begin();
			it++; it++; it++; it++; it++;
			l.splice(it, l1);
			std::cout << "The source list after splice : " << l1 << std::endl;
			std::cout << "The target list after calling splice a third time : " << l << std::endl;
		}
		{
			title("Transfer single element", 2);
			ft::List<int> l;
			ft::List<int> l1(5, 22);
			l.push_back(0);
			l.push_back(1);
			l.push_back(2);
			l.push_back(3);
			l.push_back(4);

			l1.front() = 5;
			l1.back() = -1;
			std::cout << "The source list : " << l1 << std::endl;
			std::cout << "The target list before calling splice : " << l << std::endl;
			l.splice(l.end(), l1, l1.begin());
			l.splice(l.begin(), l1, l1.end());
			std::cout << "The source list after splice : " << l1 << std::endl;
			std::cout << "The target list after calling splice : " << l << std::endl;
		}
		{
			title("Transfer a range of elements", 2);
			ft::List<int> l;
			ft::List<int> l1;
			l.push_back(0);
			l.push_back(1);
			l.push_back(2);

			l1.push_back(3);
			l1.push_back(3);
			l1.push_back(4);
			l1.push_back(5);
			l1.push_back(6);
			std::cout << "The target list before calling splice : " << l << std::endl;
			std::cout << "The source list : " << l1 << std::endl;
			l.splice(l.end(), l1, ++l1.begin(), --l1.end());
			std::cout << "The source list after splice : " << l1 << std::endl;
			std::cout << "The target list after calling splice : " << l << std::endl;
		}
	}
	{
		title("Tests of merge", 1);
		srand(time(NULL));
		{
			title("Without comparison function", 2);
			ft::List<int> l;
			ft::List<int> l1;
			for (int i = 0; i < 5; i++)
			{
				l.push_back(rand() % 100);
				l1.push_back(rand() % 100);
			}
			l.sort();
			l1.sort();

			std::cout << "The first list : " << l << std::endl;
			std::cout << "The second list : " << l1 << std::endl;
			l.merge(l1);
			std::cout << "The merged list : " << l << std::endl;
		}
		{
			title("With comparison function", 2);
			ft::List<int> l;
			ft::List<int> l1;
			for (int i = 0; i < 5; i++)
			{
				l.push_back(rand() % 100);
				l1.push_back(rand() % 100);
			}
			l.sort(ft::great<int>());
			l1.sort(ft::great<int>());

			std::cout << "The first list : " << l << std::endl;
			std::cout << "The second list : " << l1 << std::endl;
			l.merge(l1, ft::great<int>());
			std::cout << "The merged list : " << l << std::endl;
		}
	}
}

void test_list_algorithm()
{
	title("TEST LIST ALGORITHM FUNCTIONS");

	ft::List<int> l;

	l.push_back(0);
	l.push_back(3);
	l.push_back(4);
	l.push_back(1);
	l.push_back(1);

	std::cout << "List :";
	for (auto it = l.begin(); it != l.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;

	std::cout << "Count of 1 : " << std::count(l.begin(), l.end(), 1);
}

void lists()
{
	title("TESTS ABOUT FT::LISTS", -1);
	test_list_constructors();
	test_list_copy();
	test_list_capacity();
	test_list_modifiers_insertions();
	test_list_accessers();
	test_list_reverse_iterators();
	test_list_resize();
	test_list_deleting_elements();
	test_list_relational();
	test_list_swap_non_member();
	test_list_swap_member();
	test_list_unary_operations();
	test_list_binary_operations();
	test_list_algorithm();
}
