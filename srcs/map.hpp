/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 23:02:15 by gboucett          #+#    #+#             */
/*   Updated: 2021/07/07 01:58:13 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "RBTree.hpp"

namespace ft
{
	template <typename Key, typename T, typename Compare = less<Key>, typename Alloc = std::allocator<pair<Key, T> > >
	class map;

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y)
	{
		return y < x;
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y)
	{
		return !(x > y) && !(x < y);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y)
	{
		return !(x == y);
	}
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y)
	{
		return !(x > y);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y)
	{
		return !(x < y);
	}
}

template <typename Key, typename T, typename Compare, typename Alloc>
class ft::map
{
public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef pair<key_type, mapped_type> value_type;
	typedef Compare key_compare;
	typedef Alloc allocator_type;

private:
	class value_compare
	{
	private:
		key_compare comp;

	public:
		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;

		value_compare(key_compare c) : comp(c)
		{
		}

		bool operator()(const value_type &x, const value_type &y)
		{
			return comp(x.first, y.first);
		}
	};

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

	map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(value_compare(comp), alloc), _comp(comp)
	{
	}

	template <class InputIterator>
	map(InputIterator &first, InputIterator &last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(first, last, value_compare(comp), alloc), _comp(comp)
	{
	}

	map(const map &x) : _tree(x._tree), _comp(x._comp)
	{
	}

	~map()
	{
	}

	map &operator=(const map &other)
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

	mapped_type &operator[](const key_type &k)
	{
		return (insert(make_pair(k, mapped_type())).first)->second;
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

	size_type erase(const key_type &k)
	{
		return _tree.erase(make_pair(k, mapped_type()));
	}

	void erase(iterator first, iterator last)
	{
		_tree.erase(first, last);
	}

	void swap(map &x)
	{
		_tree.swap(x.swap);
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
		return value_compare(_comp);
	}

	iterator find(const key_type &key)
	{
		return _tree.find(make_pair(key, mapped_type()));
	}

	const_iterator find(const key_type &key) const
	{
		return _tree.find(make_pair(key, mapped_type()));
	}

	size_type count(const key_type &key) const
	{
		return _tree.count(make_pair(key, mapped_type()));
	}

	iterator lower_bound(const key_type &key)
	{
		return _tree.lower_bound(make_pair(key, mapped_type()));
	}

	const_iterator lower_bound(const key_type &key) const
	{
		return _tree.lower_bound(make_pair(key, mapped_type()));
	}

	iterator upper_bound(const key_type &key)
	{
		return _tree.upper_bound(make_pair(key, mapped_type()));
	}

	const_iterator upper_bound(const key_type &key) const
	{
		return _tree.upper_bound(make_pair(key, mapped_type()));
	}

	iterator equal_range(const key_type &key)
	{
		return _tree.equal_range(make_pair(key, mapped_type()));
	}

	const_iterator equal_range(const key_type &key) const
	{
		return _tree.count(make_pair(key, mapped_type()));
	}

	allocator_type get_allocator() const
	{
		return _tree.get_allocator();
	}

	friend bool operator<(map &x, map &y)
	{
		return x._tree < y._tree;
	}

private:
	tree_type _tree;
	key_compare _comp;
};

#endif
