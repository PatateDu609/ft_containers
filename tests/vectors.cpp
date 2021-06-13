/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:04:28 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/18 16:24:58 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

bool print = true;

template <typename T>
static std::ostream &operator<<(std::ostream &os, const ft::Vector<T> &x)
{
	if (x.empty() && print)
		return os << "is empty";
	else if (x.empty())
		return os;
	for (typename ft::Vector<T>::const_iterator it = x.begin(), it1 = ++x.begin(); it != x.end(); ++it)
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

static void test_vector_constructors()
{
	title("TEST VECTOR CONSTRUCTORS");

	{
		title("Default constructor", 1);
		ft::Vector<int> v;
		std::cout << "The vector : " << v << std::endl;
	}
	{
		title("Fill constructor (with default value)", 1);
		ft::Vector<int>::size_type size = 5;
		ft::Vector<int> v(size);
		std::cout << "The vector (should contain " << size << " element(s)) : " << v << std::endl;
	}
	{
		title("Fill constructor (with given value)", 1);
		ft::Vector<int>::size_type size = 5;
		int value = 55;
		ft::Vector<int> v(size, value);
		std::cout << "The vector (should contain " << size << " " << value << ") : " << v << std::endl;
	}
	{
		title("Range constructor", 1);
		ft::Vector<int>::size_type size = 10;
		ft::Vector<int> v(size, 25);
		ft::Vector<int> vt(v.begin(), v.end());

		std::cout << "The vector constructed by fill constructor  : " << v << std::endl;
		std::cout << "The vector constructed by range constructor : " << vt << std::endl;
	}
}

static void test_vector_copy()
{
	title("TEST VECTOR ASSIGNATION OPERATOR");

	ft::Vector<std::string> v(5, "bonjour");
	ft::Vector<std::string> v1;
	v1 = v;
	std::cout << "The vector constructed by fill constructor : " << v << std::endl;
	std::cout << "The vector after the copy                  : " << v1 << std::endl;
}

static void test_vector_capacity()
{
	title("TEST VECTOR CAPACITY");

	print = false;

	{
		title("Is the vector empty ?", 1);
		ft::Vector<int> v;
		std::cout << "The vector (" << v << ") is " << (v.empty() ? "empty" : "not empty") << std::endl;
		ft::Vector<int> v1(5, 10);
		std::cout << "The vector (" << v1 << ") is " << (v1.empty() ? "empty" : "not empty") << std::endl;
	}
	{
		title("The size of the vector", 1);
		ft::Vector<int> l;
		std::cout << "The vector (" << l << ") has " << l.size() << " element(s)" << std::endl;
		ft::Vector<int> l1(5, 10);
		std::cout << "The vector (" << l1 << ") has " << l1.size() << " element(s)" << std::endl;
		ft::Vector<int> l2(1, 100);
		std::cout << "The vector (" << l2 << ") has " << l2.size() << " element(s)" << std::endl;
	}
	{
		title("The capacity of the vector", 1);
		ft::Vector<int> v;
		ft::Vector<int>::size_type oldCapacity = -1;
		for (int i = 0; i < 1000; i++)
		{
			if (oldCapacity != v.capacity())
				std::cout << "Size : " << v.size() << ", "
						<< "Capacity : " << (oldCapacity = v.capacity()) << std::endl;
			v.push_back(i);
		}
	}
	{
		title("The maximum size of a vector is :", 1);
		std::cout << "My vector  : " << ft::Vector<int>().max_size() << std::endl;
		std::cout << "STL vector : " << std::vector<int>().max_size() << std::endl;
	}

	print = true;
}

static void test_vector_relational()
{
	title("TEST VECTOR RELATIONAL OPERATIONS");

	ft::Vector<int> a;
	ft::Vector<int> b;
	ft::Vector<int> c;

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

static void test_vector_swap_non_member()
{
	title("TEST VECTOR SWAP (NON MEMBER FUNCTION)");
	ft::Vector<int> foo(3, 100); // three ints with a value of 100
	ft::Vector<int> bar(5, 200); // five ints with a value of 200

	title("Before swapping :", 1);
	std::cout << "foo contains: " << foo << std::endl;
	std::cout << "bar contains: " << bar << std::endl;

	ft::swap(foo, bar);

	title("After swapping :", 1);
	std::cout << "foo contains: " << foo << std::endl;
	std::cout << "bar contains: " << bar << std::endl;
}

static void test_vector_swap_member()
{
	title("TEST VECTOR SWAP (MEMBER FUNCTION)");
	ft::Vector<int> foo(3, 100); // three ints with a value of 100
	ft::Vector<int> bar(5, 200); // five ints with a value of 200

	title("Before swapping :", 1);
	std::cout << "foo contains: " << foo << std::endl;
	std::cout << "bar contains: " << bar << std::endl;

	foo.swap(bar);

	title("After swapping :", 1);
	std::cout << "foo contains: " << foo << std::endl;
	std::cout << "bar contains: " << bar << std::endl;
}

static void test_vector_modifiers_insertions()
{
	title("TEST VECTOR INSERTION");

	{
		title("Testing push_back", 1);
		ft::Vector<int> v;
		for (int i = 0; i <= 5; i++)
		{
			std::cout << "The vector :\t\t" << v << std::endl;
			v.push_back(i);
		}
		std::cout << "The final vector :\t" << v << std::endl;
	}
	{
		title("Testing insert", 1);
		{
			title("Inserting a single element", 2);
			ft::Vector<int> v(5, 10);
			std::cout << "The vector before the insertion : " << v << std::endl;
			ft::Vector<int>::iterator it = v.begin() + (v.end() - v.begin() - 1);
			ft::Vector<int>::iterator res = v.insert(it, 111);
			std::cout << "The vector after the insertion : " << v << std::endl;
			std::cout << "iterator returned : " << *res << std::endl;
			res = v.insert(v.begin(), 222);
			std::cout << "The vector after the insertion : " << v << std::endl;
			std::cout << "iterator returned = " << *res << std::endl;
			res = v.insert(v.end(), 5784);
			std::cout << "The vector after the insertion : " << v << std::endl;
			std::cout << "iterator returned = " << *res << std::endl;
		}
		{
			title("Inserting new elements", 2);
			ft::Vector<int> v(5, 10);
			std::cout << "The vector before the insertion : " << v << std::endl;
			ft::Vector<int>::iterator it = v.begin();
			for (ft::Vector<int>::size_type i = 0; i < v.size() - 1; i++)
				it++;
			ft::Vector<int>::iterator res = v.insert(it, 5, -11);
			std::cout << "The vector after the insertion : " << v << std::endl;
			std::cout << "iterator returned : " << *res << std::endl;
			res = v.insert(v.begin(), 3, 100);
			std::cout << "The vector after the insertion : " << v << std::endl;
			std::cout << "iterator returned = " << *res << std::endl;
			res = v.insert(v.end(), 7, 189);
			std::cout << "The vector after the insertion : " << v << std::endl;
			std::cout << "iterator returned = " << *res << std::endl;
		}
		{
			title("Inserting a range of new elements", 2);
			ft::Vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);
			ft::Vector<int> v1(5, 10);
			std::cout << "The vector before the insertion : " << v1 << std::endl;
			v1.insert(v1.end(), v.rbegin(), v.rend());
			std::cout << "The vector after the insertion : " << v1 << std::endl;
		}
	}
}

static void test_vector_accessers()
{
	title("TEST VECTOR ACCESSERS");
	ft::Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	const ft::Vector<int> v1 = v;
	std::cout << "The vector of the test : " << v << std::endl;

	{
		title("Testing front and back", 1);

		{
			title("Accessing the front element", 2);
			std::cout << "Front element : " << v.front() << std::endl;
		}
		{
			title("Accessing the back element", 2);
			std::cout << "Back element : " << v.back() << std::endl;
		}
		{
			title("Modifying the front element", 2);
			v.front() = 3;
			std::cout << "Front element : " << v.front() << std::endl;
		}
		{
			title("Modifying the back element", 2);
			v.back() = 1;
			std::cout << "Back element : " << v.back() << std::endl;
		}
		{
			title("Accessing the front element for const Vector", 2);
			std::cout << "Front element : " << v1.front() << std::endl;
		}
		{
			title("Accessing the back element for const Vector", 2);
			std::cout << "Back element : " << v1.back() << std::endl;
		}
	}
	std::cout << "The vector after the front/back tests : " << v << std::endl;
	{
		title("Testing operator[] and at", 1);
		{
			title("Testing operator[] with non const Vector", 2);
			for (ft::Vector<int>::size_type i = 0; i < v.size(); i++)
				std::cout << "element " << i << " : " << v[i] << std::endl;
		}
		{
			title("Testing operator[] with const Vector", 2);
			for (ft::Vector<int>::size_type i = 0; i < v1.size(); i++)
				std::cout << "element " << i << " : " << v1[i] << std::endl;
		}
		{
			title("Testing at with non const Vector", 2);
			for (ft::Vector<int>::size_type i = 0; i < v.size(); i++)
				std::cout << "element " << i << " : " << v.at(i) << std::endl;
		}
		{
			title("Testing at with const Vector", 2);
			for (ft::Vector<int>::size_type i = 0; i < v1.size(); i++)
				std::cout << "element " << i << " : " << v1.at(i) << std::endl;
		}
		{
			title("Testing at with wrong pos", 2);
			try {
				v.at(4);
			}
			catch (const std::out_of_range& e) {
				std::cout << e.what() << std::endl;
			}
			try {
				v.at(-1);
			}
			catch (const std::out_of_range& e) {
				std::cout << e.what() << std::endl;
			}
		}
	}
	std::cout << "The vector after the operator[]/at tests : " << v << std::endl;
}

static void test_vector_reverse_iterators()
{
	title("TEST LIST ITERATORS (AS LVALUE AND RVALUE)");

	ft::Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	std::cout << "The vector (displayed with the standard iterator)\t: " << v << std::endl;

	std::cout << "The vector (displayed with the reverse iterator)\t:";
	for (ft::Vector<int>::reverse_iterator revit = v.rbegin(); revit != v.rend(); revit++)
		std::cout << " " << *revit;
	std::cout << std::endl;
	const ft::Vector<int> v1(v);
	std::cout << "The vector (displayed with the const iterator)\t\t:";
	for (ft::Vector<int>::const_iterator it = v1.begin(); it != v1.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;
	std::cout << "The vector (displayed with the const reverse iterator)\t:";
	for (ft::Vector<int>::const_reverse_iterator revit = v1.rbegin(); revit != v1.rend(); revit++)
		std::cout << " " << *revit;
	std::cout << std::endl;
}

static void test_vector_resize()
{
	title("TEST VECTOR RESIZING");

	{
		title("Shrinking vector", 1);
		ft::Vector<int> l(10, 22);
		std::cout << "Vector before calling resize : " << l << std::endl;
		l.resize(5);
		std::cout << "Vector after calling resize :  " << l << std::endl;
	}
	{
		title("Extending vector", 1);
		{
			title("With default value", 2);
			ft::Vector<int> l(2, 22);
			std::cout << "Vector before calling resize : " << l << std::endl;
			l.resize(5);
			std::cout << "Vector after calling resize :  " << l << std::endl;
		}
		{
			title("With given value", 2);
			ft::Vector<int> l(2, 22);
			std::cout << "Vector before calling resize : " << l << std::endl;
			l.resize(5, 11);
			std::cout << "Vector after calling resize :  " << l << std::endl;
		}
	}
}

static void test_vector_reserve()
{
	title("TEST VECTOR RESERVE");

	ft::Vector<int> v;
	std::cout << "Capacity before reserve : " << v.capacity() << std::endl;
	std::cout << "Size before reserve : " << v.size() << std::endl;
	v.reserve(10);
	std::cout << "Capacity after reserve : " << v.capacity() << std::endl;
	std::cout << "Size after reserve : " << v.size() << std::endl;

	v.assign(102, 98);

	std::cout << "Capacity before reserve : " << v.capacity() << std::endl;
	std::cout << "Size before reserve : " << v.size() << std::endl;
	v.reserve(98);
	std::cout << "Capacity after reserve : " << v.capacity() << std::endl;
	std::cout << "Size after reserve : " << v.size() << std::endl;
}

static void test_vector_deleting_elements()
{
	title("TEST LIST DELETING ELEMENTS");

	{
		title("Test of pop_back", 1);
		ft::Vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		std::cout << "The vector before popping everything : " << v << std::endl;
		v.pop_back();
		v.pop_back();
		v.pop_back();
		std::cout << "The vector after popping everything : " << v << std::endl;
		std::cout << "Checking that everything went well by adding new elements to the vector" << std::endl;
		v.push_back(4);
		v.push_back(5);
		v.push_back(6);
		std::cout << "The vector before popping everything : " << v << std::endl;
		v.pop_back();
		std::cout << "The vector after popping one element : " << v << std::endl;
	}
	{
		title("Test of clear", 1);
		ft::Vector<int> v(10, 5);
		std::cout << "The vector before clearing it : " << v << std::endl;
		v.clear();
		std::cout << "The vector after clearing it : " << v << std::endl;
	}
	{
		title("Tests of erase", 1);
		{
			title("Erasing a single element", 2);
			ft::Vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);
			v.push_back(4);
			v.push_back(5);
			v.push_back(6);
			v.push_back(7);
			v.push_back(8);
			v.push_back(9);
			v.push_back(10);
			std::cout << "The vector before erasing anything : " << v << std::endl;

			while (!v.empty())
			{
				ft::Vector<int>::iterator res = v.erase(v.begin());
				std::cout << "The vector now (element following the erased one : ";
				if (!v.empty())
					std::cout << *res;
				std::cout << ") : " << v << std::endl;
			}
		}
		{
			title("Erasing a range of elements", 2);
			ft::Vector<int> v;
			v.push_back(1);
			v.push_back(2);
			v.push_back(3);
			v.push_back(4);
			v.push_back(5);
			v.push_back(6);
			v.push_back(7);
			v.push_back(8);
			v.push_back(9);
			v.push_back(10);
			std::cout << "The list before erasing anything : " << v << std::endl;

			ft::Vector<int>::iterator it = v.begin();
			for (int i = 0; i < 3; i++)
				it++;
			ft::Vector<int>::iterator it1 = it;
			for (int i = 0; i < 3; i++)
				it1++;
			std::cout << "Range to erase :";
			for (ft::Vector<int>::iterator i = it; i != it1; i++)
				std::cout << " " << *i;
			std::cout << std::endl;
			v.erase(it, it1);
			std::cout << "The list after erasing : " << v << std::endl;
		}
	}
}

void vectors()
{
	title("TESTS ABOUT FT::VECTOR", -1);
	test_vector_constructors();
	test_vector_copy();
	test_vector_capacity();
	test_vector_relational();
	test_vector_swap_non_member();
	test_vector_swap_member();
	test_vector_modifiers_insertions();
	test_vector_accessers();
	test_vector_reverse_iterators();
	test_vector_resize();
	test_vector_reserve();
	test_vector_deleting_elements();
}
