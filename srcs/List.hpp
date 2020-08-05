/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 19:04:03 by gboucett          #+#    #+#             */
/*   Updated: 2020/08/05 15:23:52 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <limits>
#include "algorithm.hpp"

namespace ft
{
	template <typename T>
	class List;
	template <typename T, typename Node>
	class ListIterator;
	template <typename T, typename Node>
	class ListReverseIterator;
	template <typename T>
	struct ListNode
	{
		ListNode *prev;
		T data;
		ListNode *next;
	};

	template <typename T>
	bool operator==(const List<T> &lhs, const List<T> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (typename List<T>::const_iterator lit = lhs.begin(), rit = rhs.begin(); lit != lhs.end(); lit++, rit++)
			if (*rit != *lit)
				return false;
		return true;
	}

	template <typename T>
	bool operator<(const List<T> &lhs, const List<T> &rhs)
	{
		if (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
			return true;
		return false;
	}

	template <typename T>
	bool operator!=(const List<T> &lhs, const List<T> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator>(const List<T> &lhs, const List<T> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T>
	bool operator<=(const List<T> &lhs, const List<T> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T>
	bool operator>=(const List<T> &lhs, const List<T> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T>
	void swap(List<T> &x, List<T> &y)
	{
		x.swap(y);
	}
} // namespace ft

template <typename T, typename Node>
class ft::ListIterator
{
public:
	typedef T value_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;

	ListIterator() : _node(NULL)
	{
	}

	ListIterator(const ListIterator &other)
	{
		*this = other;
	}

	ListIterator(Node *node)
	{
		_node = node;
	}

	~ListIterator()
	{
	}

	ListIterator &operator=(const ListIterator &other)
	{
		_node = other._node;
		return (*this);
	}

	bool operator==(const ListIterator &b) const
	{
		return b._node == _node;
	}

	bool operator!=(const ListIterator &b) const
	{
		return !(b == *this);
	}

	reference operator*()
	{
		return _node->data;
	}

	reference operator->()
	{
		return _node->data;
	}

	ListIterator &operator++()
	{
		_node = this->_node->next;
		return (*this);
	}

	ListIterator operator++(int)
	{
		ListIterator it(*this);
		_node = _node->next;
		return (it);
	}

	ListIterator &operator--()
	{
		_node = _node->prev;
		return (*this);
	}

	ListIterator operator--(int)
	{
		ListIterator &it(*this);
		_node = _node->prev;
		return (it);
	}

	Node *getNode()
	{
		return _node;
	}

private:
	Node *_node;
}; // class ft::ListIterator

template <typename T, typename Node>
class ft::ListReverseIterator
{
public:
	typedef T value_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;

	ListReverseIterator() : _node(NULL)
	{
	}

	ListReverseIterator(const ListReverseIterator &other)
	{
		*this = other;
	}

	ListReverseIterator(Node *node)
	{
		_node = node;
	}

	~ListReverseIterator()
	{
	}

	ListReverseIterator &operator=(const ListReverseIterator &other)
	{
		_node = other._node;
		return (*this);
	}

	bool operator==(const ListReverseIterator &b) const
	{
		return b._node == _node;
	}

	bool operator!=(const ListReverseIterator &b) const
	{
		return !(b == *this);
	}

	reference operator*()
	{
		return _node->data;
	}

	reference operator->()
	{
		return _node->data;
	}

	ListReverseIterator &operator++()
	{
		_node = _node->prev;
		return (*this);
	}

	ListReverseIterator operator++(int)
	{
		ListReverseIterator &it(*this);
		_node = _node->prev;
		return (it);
	}

	ListReverseIterator &operator--()
	{
		_node = _node->next;
		return (*this);
	}

	ListReverseIterator operator--(int)
	{
		ListReverseIterator &it(*this);
		_node = _node->next;
		return (it);
	}

private:
	Node *_node;
}; // class ft::ListReverseIterator

template <typename T>
class ft::List
{
public:
	typedef T value_type;
	typedef ft::ListNode<value_type> Node;
	typedef ft::ListIterator<value_type &, Node> iterator;
	typedef ft::ListReverseIterator<value_type &, Node> reverse_iterator;
	typedef ft::ListIterator<const value_type &, const Node> const_iterator;
	typedef ft::ListReverseIterator<const value_type&, const Node> const_reverse_iterator;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef size_t size_type;
	typedef std::ptrdiff_t difference_type;

	List()
	{
		reset(true);
	}

	List(size_type size, const_reference val = value_type())
	{
		reset(true);
		assign(size, val);
	}

	List(const List<value_type> &other)
	{
		reset(true);
		*this = other;
	}

	List(iterator first, iterator last)
	{
		reset(true);
		assign(first, last);
	}

	~List()
	{
		_destructor = true;
		clear();
	}

	List &operator=(const List<value_type> &other)
	{
		reset();
		assign(other.begin(), other.end());
		return *this;
	}

	reference front()
	{
		return _begin->data;
	}

	const_reference front() const
	{
		return _begin->data;
	}

	reference back()
	{
		return _end->data;
	}

	const_reference back() const
	{
		return _end->data;
	}

	void push_front(const_reference v)
	{
		Node *node = new Node({.prev = NULL, .data = v, .next = _begin});
		if (_begin)
			_begin->prev = node;
		_begin = node;
		if (!_end)
			_end = _begin;
		_size++;
		if (_size)
		{
			if (!_ritend)
				_ritend = new Node({.prev = NULL, .data = value_type(), .next = _begin});
			else
				_ritend->next = _begin;
			_begin->prev = _ritend;
			if (_size == 1)
			{
				delete _itend;
				_itend = new Node({.prev = _end, .data = value_type(), .next = NULL});
				_end->next = _itend;
			}
		}
	}

	void push_back(const_reference v)
	{
		Node *node = new Node({.prev = _end, .data = v, .next = NULL});
		if (_end)
			_end->next = node;
		_end = node;
		if (!_begin)
			_begin = _end;
		_size++;

		if (_size)
		{
			if (!_itend)
				_itend = new Node({.prev = _end, .data = value_type(), .next = NULL});
			else
				_itend->prev = _end;
			_end->next = _itend;
			if (_size == 1)
			{
				delete _ritend;
				_ritend = new Node({.prev = NULL, .data = value_type(), .next = _begin});
				_begin->prev = _ritend;
			}
		}
	}

	void pop_front()
	{
		if (_begin)
		{
			Node *temp = _begin;
			_size--;
			_begin = _begin->next;
			if (_begin)
			{
				_begin->prev = _ritend;
				_ritend->next = _begin;
			}
			delete temp;
			if (!_size)
				reset();
		}
	}

	void pop_back()
	{
		if (_end)
		{
			Node *temp = _end;
			_size--;
			_end = _end->prev;
			_end->next = _itend;
			_itend->prev = _end;
			delete temp;
			if (!_size)
				reset();
		}
	}

	const_iterator begin() const
	{
		return const_iterator(_begin);
	}

	const_iterator end() const
	{
		return const_iterator(_itend);
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(_end);
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(_ritend);
	}

	iterator begin()
	{
		return iterator(_begin);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(_end);
	}

	iterator end()
	{
		return iterator(_itend);
	}

	reverse_iterator rend()
	{
		return reverse_iterator(_ritend);
	}

	bool empty() const
	{
		return _size == 0;
	}

	size_type size() const
	{
		return _size;
	}

	size_type max_size() const
	{
		return (std::numeric_limits<size_type>::max() / sizeof(Node));
	}

	void assign(const_iterator first, const_iterator last)
	{
		clear();
		while (first != last)
			push_back(*first++);
	}

	void assign(iterator first, iterator last)
	{
		clear();
		while (first != last)
			push_back(*first++);
	}

	void assign(size_type n, const value_type &val)
	{
		clear();
		for (size_type i = 0; i < n; i++)
			push_back(val);
	}

	void clear()
	{
		while (_ritend)
		{
			Node *temp = _ritend;
			_ritend = _ritend->next;
			delete temp;
		}
		_ritend = NULL;
		_itend = NULL;
		reset();
	}

	iterator insert(iterator position, const value_type &val)
	{
		if (position == begin())
		{
			push_front(val);
			return begin();
		}
		else if (position == end())
		{
			push_back(val);
			return --end();
		}

		Node *newNode = new Node({.prev = NULL, .data = val, .next = NULL});
		Node *node = position.getNode();
		newNode->prev = node->prev;
		newNode->next = node;
		node->prev->next = newNode;
		node->prev = newNode;
		_size++;
		return iterator(newNode);
	}

	void insert(iterator position, size_type n, const value_type &val)
	{
		for (size_type i = 0; i < n; i++)
			insert(position, val);
	}

	void insert(iterator position, iterator first, iterator last)
	{
		while (first != last)
			insert(position, *first++);
	}

	iterator erase(iterator position)
	{
		if (position == begin())
		{
			pop_front();
			return begin();
		}
		else if (position == end())
		{
			pop_back();
			return end();
		}
		Node *node = position.getNode();
		Node *before = node->prev;
		Node *after = node->next;
		before->next = after;
		if (after)
			after->prev = before;
		delete node;
		_size--;
		return iterator(after);
	}

	iterator erase(iterator first, iterator last)
	{
		while (first != last)
			erase(first++);
		return first;
	}

	void swap(List &x)
	{
		ft::swap(x._begin, _begin);
		ft::swap(x._end, _end);
		ft::swap(x._itend, _itend);
		ft::swap(x._size, _size);
	}

	void resize(size_type n, value_type val = value_type())
	{
		size_type i = 0;
		iterator it = begin();

		if (n < _size)
		{
			for (i = 0; i < n; i++)
				it++;
			erase(it, end());
		}
		else if (n > _size)
			insert(end(), n - _size, val);
	}

	void remove(const value_type &val)
	{
		for (iterator it = begin(); it != end(); it++)
			if (*it == val)
				erase(it);
	}

	template <typename Predicate>
	void remove_if(Predicate pred)
	{
		for (iterator it = begin(); it != end(); it++)
			if (pred(*it))
				erase(it);
	}

	void unique()
	{
		for (iterator it = ++begin(), it1 = begin(); it != end(); it++, it1++)
			if (*it == *it1)
				erase(it1);
	}

	template <typename BinaryPredicate>
	void unique(BinaryPredicate binary_pred)
	{
		for (iterator it = ++begin(), it1 = begin(); it != end(); it++, it1++)
			if (binary_pred(*it, *it1))
				erase(it1);
	}

	void reverse()
	{
		List temp(begin(), end());
		clear();
		for (reverse_iterator it = temp.rbegin(); it != temp.rend(); it++)
		{
			push_back(*it);
		}
	}

	void sort()
	{
		sort(ft::less<value_type>());
	}

	template <typename Compare>
	void sort(Compare comp)
	{
		if (_size <= 1)
			return;
		_end->next = NULL;
		int swapped;
		Node *ptr1;
		Node *lptr = NULL;

		do
		{
			swapped = 0;
			ptr1 = _begin;
			while (ptr1->next != lptr)
			{
				if (comp(ptr1->next->data, ptr1->data))
				{
					ft::swap(ptr1->data, ptr1->next->data);
					swapped = 1;
				}
				ptr1 = ptr1->next;
			}
			lptr = ptr1;
		} while (swapped);
		_end->next = _itend;
	}

	void splice(iterator position, List &x)
	{
		splice(position, x, x.begin(), x.end());
	}

	void splice(iterator position, List &x, iterator i)
	{
		iterator it = i;
		splice(position, x, i, ++it);
	}

	void splice(iterator position, List &x, iterator first, iterator last)
	{
		Node *tmp, *tmp1;

		while (first != last)
		{
			tmp = first++.getNode();
			if (tmp == x._begin)
			{
				x._begin = tmp->next;
				x._begin->prev = x._ritend;
				x._ritend->next = x._begin;
			}
			if (tmp == x._itend)
				tmp = tmp->prev;

			tmp->next->prev = tmp->prev;
			tmp->prev->next = tmp->next;

			tmp1 = position.getNode();
			tmp1->prev->next = tmp;
			tmp->prev = tmp1->prev;
			tmp1->prev = tmp;
			tmp->next = tmp1;

			if (tmp1 == _begin)
			{
				_begin = tmp;
				_ritend->next = _begin;
				_begin->prev = _ritend;
			}

			_size++;
			x._size--;
		}
		if (x._size == 0)
			x.reset();
	}

	void merge(List &x)
	{
		merge(x, ft::less<value_type>());
	}

	template <typename Compare>
	void merge(List &x, Compare comp)
	{
		if (x._begin == _begin)
			return;
		iterator f1 = begin();
		iterator l1 = end();
		iterator f2 = x.begin();
		iterator l2 = x.end();

		while (f1 != l1 && f2 != l2 && f1.getNode() && f2.getNode())
		{
			if (comp(*f2, *f1))
			{
				splice(f1, x, f2);
				if (f1 == begin())
				{
					_begin = _begin->prev;
					_ritend->next = _begin;
					_begin->prev = _ritend;
				}
				f2 = x.begin();
			}
			else
				f1++;
		}
		splice(l1, x);
	}

private:
	void reset(bool constructor = false)
	{
		if (!constructor && !_destructor)
		{
			delete _itend;
			delete _ritend;
		}
		_itend = NULL;
		_ritend = NULL;
		_destructor = false;
		_begin = NULL;
		_end = NULL;
		_size = 0;
	}

	Node *_begin;
	Node *_end;
	size_type _size;
	Node *_itend;
	Node *_ritend;
	bool _destructor;
}; //class ft::List

#endif
