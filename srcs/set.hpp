/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:02:15 by gboucett          #+#    #+#             */
/*   Updated: 2021/07/14 21:18:27 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef set_HPP
#define set_HPP

#include "RBTree.hpp"
#include <iostream>

namespace ft
{
	template <typename T, typename Compare = less<T>, typename Alloc = std::allocator<T> >
	class set;

	template <typename T, typename Compare, typename Alloc>
	bool operator>(const set<T, Compare, Alloc> &x, const set<T, Compare, Alloc> &y)
	{
		return y < x;
	}

	template <typename T, typename Compare, typename Alloc>
	bool operator==(const set<T, Compare, Alloc> &x, const set<T, Compare, Alloc> &y)
	{
		return !(y < x) && !(x < y);
	}

	template <typename T, typename Compare, typename Alloc>
	bool operator!=(const set<T, Compare, Alloc> &x, const set<T, Compare, Alloc> &y)
	{
		return !(x == y);
	}
	template <typename T, typename Compare, typename Alloc>
	bool operator<=(const set<T, Compare, Alloc> &x, const set<T, Compare, Alloc> &y)
	{
		return !(x > y);
	}

	template <typename T, typename Compare, typename Alloc>
	bool operator>=(const set<T, Compare, Alloc> &x, const set<T, Compare, Alloc> &y)
	{
		return !(x < y);
	}

	template <typename T, typename Compare, typename Alloc>
	void swap(set<T, Compare, Alloc> &x, set<T, Compare, Alloc> &y)
	{
		x.swap(y);
	}
}

template <typename T, typename Compare, typename Alloc>
class ft::set
{
public:
	typedef T key_type;
	typedef T value_type;
	typedef Compare key_compare;
	typedef Compare value_compare;
	typedef Alloc allocator_type;

private:
	typedef RBTree<value_type, value_compare, allocator_type> tree_type;

public:
	typedef typename tree_type::reference reference;
	typedef typename tree_type::const_reference const_reference;
	typedef typename tree_type::pointer pointer;
	typedef typename tree_type::const_pointer const_pointer;

	typedef typename tree_type::iterator iterator;
	typedef typename tree_type::const_iterator const_iterator;
	typedef typename tree_type::reverse_iterator reverse_iterator;
	typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

	typedef typename tree_type::difference_type difference_type;
	typedef typename tree_type::size_type size_type;

	explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(value_compare(comp), alloc), _comp(comp)
	{
	}

	template <class InputIterator>
	set(const InputIterator &first, const InputIterator &last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(first, last, value_compare(comp), alloc), _comp(comp)
	{
	}

	set(const set &x) : _tree(x._tree), _comp(x._comp)
	{
	}

	~set()
	{
	}

	set &operator=(const set &other)
	{
		_tree = other._tree;
		return *this;
	}

	iterator begin()
	{
		return _tree.begin();
	}

	const_iterator begin() const
	{
		return _tree.begin();
	}

	iterator end()
	{
		return _tree.end();
	}

	const_iterator end() const
	{
		return _tree.end();
	}

	reverse_iterator rbegin()
	{
		return _tree.rbegin();
	}

	const_reverse_iterator rbegin() const
	{
		return _tree.rbegin();
	}

	reverse_iterator rend()
	{
		return _tree.rend();
	}

	const_reverse_iterator rend() const
	{
		return _tree.rend();
	}

	bool empty() const
	{
		return _tree.empty();
	}

	size_type size() const
	{
		return _tree.size();
	}

	size_type max_size() const
	{
		return _tree.max_size();
	}

	pair<iterator, bool> insert(const_reference val)
	{
		return _tree.insert(val);
	}

	iterator insert(iterator position, const_reference val)
	{
		return _tree.insert(position, val);
	}

	template <class InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		_tree.insert(first, last);
	}

	void erase(iterator position)
	{
		_tree.erase(position);
	}

	size_type erase(const value_type &k)
	{
		return _tree.erase(k);
	}

	void erase(iterator first, iterator last)
	{
		_tree.erase(first, last);
	}

	void swap(set &x)
	{
		_tree.swap(x._tree);
	}

	void clear()
	{
		_tree.clear();
	}

	key_compare key_comp() const
	{
		return _comp;
	}

	value_compare value_comp() const
	{
		return _comp;
	}

	iterator find(const key_type &key)
	{
		return _tree.find(key);
	}

	const_iterator find(const key_type &key) const
	{
		return _tree.find(key);
	}

	size_type count(const key_type &key) const
	{
		return _tree.count(key);
	}

	iterator lower_bound(const key_type &key)
	{
		return _tree.lower_bound(key);
	}

	const_iterator lower_bound(const key_type &key) const
	{
		return _tree.lower_bound(key);
	}

	iterator upper_bound(const key_type &key)
	{
		return _tree.upper_bound(key);
	}

	const_iterator upper_bound(const key_type &key) const
	{
		return _tree.upper_bound(key);
	}

	pair<iterator, iterator> equal_range(const key_type &key)
	{
		return _tree.equal_range(key);
	}

	pair<const_iterator, const_iterator> equal_range(const key_type &key) const
	{
		return _tree.equal_range(key);
	}

	allocator_type get_allocator() const
	{
		return _tree.get_allocator();
	}

	friend bool operator<(const set &x, const set &y)
	{
		return x._tree < y._tree;
	}

private:
	tree_type _tree;
	key_compare _comp;
};

#endif
