/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:29:29 by gboucett          #+#    #+#             */
/*   Updated: 2021/03/14 11:48:54 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "RBTree.hpp"
#include "MapUtils.hpp"

namespace ft
{
	template <typename Key, typename T, typename Compare = less<Key>,
		typename Alloc = std::allocator<pair<Key, T> > >
	class Map;
}

template <typename Key, typename T, typename Compare, typename Alloc>
class ft::Map
{
public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef ft::pair<key_type, mapped_type> value_type;
	typedef Alloc allocator_type;

	typedef Compare key_compare;

	class value_compare
	{
	public:
		value_compare(const key_compare& compare) : _comp(compare)
		{}

		bool operator() (const value_type& a, const value_type& b) const
		{
			return _comp(a.first, b.first);
		}
	private:
		key_compare _comp;
	};

private:
	typedef RBTree<value_type, value_compare, allocator_type, false> Tree_type;

public:
	typedef typename Tree_type::reference reference;
	typedef typename Tree_type::const_reference const_reference;
	typedef typename Tree_type::pointer pointer;
	typedef typename Tree_type::const_pointer const_pointer;

	typedef typename Tree_type::iterator iterator;
	typedef typename Tree_type::const_iterator const_iterator;
	typedef typename Tree_type::reverse_iterator reverse_iterator;
	typedef typename Tree_type::const_reverse_iterator const_reverse_iterator;

	typedef typename Tree_type::difference_type difference_type;
	typedef typename Tree_type::size_type size_type;

	explicit Map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(value_compare(comp), alloc), _comp(comp)
	{}

	template <typename InputIterator>
	Map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(first, last, value_compare(comp), alloc), _comp(comp)
	{}

	Map(const Map& other) : _tree(other._tree), _comp(other._comp)
	{}

	~Map()
	{}

	Map& operator=(const Map& other)
	{
		_tree = other._tree;
		_comp = other._comp;
	}

	iterator begin()
	{
		return _tree.begin();
	}

	iterator end()
	{
		return _tree.end();
	}

	const_iterator begin() const
	{
		return _tree.begin();
	}

	const_iterator end() const
	{
		return _tree.end();
	}

	reverse_iterator rbegin()
	{
		return _tree.rbegin();
	}

	reverse_iterator rend()
	{
		return _tree.rend();
	}

	const_reverse_iterator rbegin() const
	{
		return _tree.rbegin();
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

	mapped_type& operator[](const key_type& k)
	{
		return ((insert(std::make_pair(k, mapped_type()))).first)->second;
	}

	ft::pair<iterator, bool> insert(const_reference val)
	{
		iterator it = _tree.find(val);
		return std::make_pair(it != end() ? it : _tree.insert(val), it == end());
	}

	iterator insert(iterator hint, const_reference val)
	{
		return _tree.insert(hint, val);
	}

	template <typename InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		_tree.insert(first, last);
	}

	void erase(iterator position)
	{
		_tree.erase(position);
	}

	size_type erase(const key_type& t)
	{
		return _tree.erase(find(t));
	}

	void erase(iterator first, iterator last)
	{
		return _tree.erase(first, last);
	}

	void swap(Map& other)
	{
		_tree.swap(other.swap());
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

	iterator find(const key_type& t)
	{
		return _tree.find(std::make_pair(t, mapped_type()));
	}

	const_iterator find(const key_type& t) const
	{
		return _tree.find(std::make_pair(t, mapped_type()));
	}

	size_type count(const key_type& t) const
	{
		return _tree.count(std::make_pair(t, mapped_type()));
	}

	iterator lower_bound(const key_type& t)
	{
		return _tree.lower_bound(std::make_pair(t, mapped_type()));
	}

	const_iterator lower_bound(const key_type& t) const
	{
		return _tree.lower_bound(std::make_pair(t, mapped_type()));
	}

	iterator upper_bound(const key_type& t)
	{
		return _tree.upper_bound(std::make_pair(t, mapped_type()));
	}

	const_iterator upper_bound(const key_type& t) const
	{
		return _tree.upper_bound(std::make_pair(t, mapped_type()));
	}

	iterator equal_range(const key_type& t)
	{
		return _tree.equal_range(std::make_pair(t, mapped_type()));
	}

	const_iterator equal_range(const key_type& t) const
	{
		return _tree.equal_range(std::make_pair(t, mapped_type()));
	}

	allocator_type get_allocator() const
	{
		return _tree.get_allocator();
	}

private:
	Tree_type _tree;
	key_compare _comp;
};

#endif
