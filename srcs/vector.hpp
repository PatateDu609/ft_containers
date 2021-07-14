/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:06:58 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/18 16:12:00 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "algorithm.hpp"
#include "Type_traits.hpp"
#include "Iterator.hpp"

#include <numeric>
#include <cstring>
#include <string>
#include <sstream>
#include <stdexcept>
#include <exception>
#include <memory>

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector;

	template <typename T, typename T1>
	class VectorIterator;

	template <typename T, typename T1>
	VectorIterator<T, T1> operator+(typename VectorIterator<T, T1>::difference_type n, const VectorIterator<T, T1> a)
	{
		return a + n;
	}

	template <typename T>
	void swap(vector<T> &a, vector<T> &b)
	{
		a.swap(b);
	}

	template <typename T>
	bool operator==(const vector<T> &lhs, const vector<T> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		for (typename vector<T>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return (true);
	}

	template <typename T>
	bool operator!=(const vector<T> &lhs, const vector<T> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator<(const vector<T> &lhs, const vector<T> &rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T>
	bool operator>(const vector<T> &lhs, const vector<T> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T>
	bool operator<=(const vector<T> &lhs, const vector<T> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T>
	bool operator>=(const vector<T> &lhs, const vector<T> &rhs)
	{
		return !(lhs < rhs);
	}
} // namespace ft

template <typename T, typename T1>
class ft::VectorIterator
{
private:
	typedef IteratorTraits<T> traits;

public:
	typedef typename traits::iterator_category iterator_category;
	typedef typename traits::value_type value_type;
	typedef typename traits::difference_type difference_type;
	typedef typename traits::pointer pointer;
	typedef typename traits::reference reference;

private:
	typedef const reference const_reference;
	typedef const pointer const_pointer;

public:
	VectorIterator() : _ptr(NULL)
	{
	}

	VectorIterator(pointer ptr) : _ptr(ptr)
	{
	}

	VectorIterator(const VectorIterator &other)
	{
		*this = other;
	}

	VectorIterator(const VectorIterator<T1, T> &other)
	{
		*this = other;
	}

	VectorIterator &operator=(const VectorIterator &other)
	{
		_ptr = other._ptr;
		return *this;
	}

	VectorIterator &operator=(const VectorIterator<T1, T> &other)
	{
		_ptr = other.ptr();
		return *this;
	}

	bool operator==(const VectorIterator &b) const
	{
		return _ptr == b._ptr;
	}

	bool operator!=(const VectorIterator &b) const
	{
		return !(*this == b);
	}

	const_reference operator*() const
	{
		return *_ptr;
	}

	const_reference operator->() const
	{
		return *_ptr;
	}

	reference operator*()
	{
		return *_ptr;
	}

	reference operator->()
	{
		return *_ptr;
	}

	VectorIterator &operator++()
	{
		_ptr++;
		return *this;
	}

	VectorIterator operator++(int)
	{
		VectorIterator it(*this);
		_ptr++;
		return it;
	}

	VectorIterator &operator--()
	{
		_ptr--;
		return *this;
	}

	VectorIterator operator--(int)
	{
		VectorIterator it(*this);
		_ptr++;
		return it;
	}

	VectorIterator operator+(difference_type n) const
	{
		VectorIterator it(*this);

		it._ptr += n;
		return it;
	}

	VectorIterator operator-(difference_type n) const
	{
		VectorIterator it(*this);

		it._ptr -= n;
		return it;
	}

	difference_type operator-(const VectorIterator &b) const
	{
		return _ptr - b._ptr;
	}

	bool operator<(const VectorIterator &b) const
	{
		return _ptr < b._ptr;
	}

	bool operator>(const VectorIterator &b) const
	{
		return _ptr > b._ptr;
	}

	bool operator<=(const VectorIterator &b) const
	{
		return !(*this > b);
	}

	bool operator>=(const VectorIterator &b) const
	{
		return !(*this < b);
	}

	VectorIterator &operator+=(difference_type n)
	{
		*this = *this + n;
		return *this;
	}

	VectorIterator &operator-=(difference_type n)
	{
		*this = *this - n;
		return *this;
	}

	reference operator[](difference_type n)
	{
		return *(_ptr + n);
	}

	const_reference operator[](difference_type n) const
	{
		return *(_ptr + n);
	}

	pointer ptr() const
	{
		return _ptr;
	}

private:
	pointer _ptr;
};

template <typename T, typename Alloc>
class ft::vector
{
public:
	typedef T value_type;
	typedef Alloc allocator_type;

	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;

	typedef VectorIterator<pointer, const_pointer> iterator;
	typedef VectorIterator<const_pointer, pointer> const_iterator;
	typedef ReverseIterator<iterator> reverse_iterator;
	typedef ReverseIterator<const_iterator> const_reverse_iterator;

	typedef typename allocator_type::size_type size_type;
	typedef typename allocator_type::difference_type difference_type;

	explicit vector(const allocator_type &alloc = allocator_type()) : _data(NULL), _capacity(0), _size(0), allocator(alloc)
	{
	}

	explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _data(NULL), _capacity(0), _size(0), allocator(alloc)
	{
		assign(n, val);
	}

	template <class InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) : _data(NULL), _capacity(0), _size(0), allocator(alloc)
	{
		typedef typename __is_integer<InputIterator>::__type Integral;
		_init_vec(first, last, Integral());
	}

	vector(const vector &x, const allocator_type &alloc = allocator_type()) : _data(NULL), _capacity(0), _size(0), allocator(alloc)
	{
		*this = x;
	}

	~vector()
	{
		clear();
		allocator.deallocate(_data, _capacity);
	}

	vector &operator=(const vector<value_type> &x)
	{
		allocator = x.allocator;
		assign(x.begin(), x.end());
		return (*this);
	}

	iterator begin()
	{
		return iterator(_data);
	}

	iterator end()
	{
		return iterator(_data + _size);
	}

	const_iterator begin() const
	{
		return const_iterator(_data);
	}

	const_iterator end() const
	{
		return const_iterator(_data + _size);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

	size_type size() const
	{
		return _size;
	}

	size_type max_size() const
	{
		return allocator.max_size();
	}

	void resize(size_type n, value_type val = value_type())
	{
		if (n < _size)
			erase(begin() + n, end());
		else if (n > _size)
		{
			difference_type diff = n - _size;
			insert(end(), diff, val);
		}
	}

	size_type capacity() const
	{
		return _capacity;
	}

	bool empty() const
	{
		return !_size;
	}

	void reserve(size_type n)
	{
		if (_capacity == 0)
			n = n ? n : 1;
		if (_capacity < n)
		{
			pointer data = allocator.allocate(n);

			if (_data)
			{
				memcpy(data, _data, sizeof(value_type) * _size);
				allocator.deallocate(_data, _capacity);
			}

			_capacity = n;
			_data = data;
		}
	}

	reference operator[](size_type n)
	{
		return _data[n];
	}

	const_reference operator[](size_type n) const
	{
		return _data[n];
	}

	reference at(size_type n)
	{
		range_check(n);
		return _data[n];
	}

	const_reference at(size_type n) const
	{
		range_check(n);
		return _data[n];
	}

	reference front()
	{
		return _data[0];
	}

	const_reference front() const
	{
		return _data[0];
	}

	reference back()
	{
		return _data[_size - 1];
	}

	const_reference back() const
	{
		return _data[_size - 1];
	}

	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		typedef typename __is_integer<InputIterator>::__type _Integral;
		clear();
		_dispatch_assignation(first, last, _Integral());
	}

	void assign(size_type n, const value_type &val)
	{
		clear();
		insert(begin(), n, val);
	}

	void push_back(const value_type &val)
	{
		if (_size == _capacity || _capacity == 0)
			reserve(_capacity * 2);
		allocator.construct(_data + _size++, val);
	}

	void pop_back()
	{
		_data[--_size].~value_type();
	}

	iterator insert(iterator position, const value_type &val)
	{
		return _fill_insert(position, 1, val);
	}

	void insert(iterator position, size_type n, const value_type &val)
	{
		_fill_insert(position, n, val);
	}

	template <typename InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last)
	{
		typedef typename __is_integer<InputIterator>::__type _Integral;
		_dispatch_insert(position, first, last, _Integral());
	}

	iterator erase(iterator position)
	{
		return erase(position, position + 1);
	}

	iterator erase(iterator first, iterator last)
	{
		difference_type start = first - begin();
		difference_type end = last - begin();

		for (difference_type i = start; i < end; i++)
			_data[i].~value_type();

		memmove(_data + start, _data + end, sizeof(value_type) * (_size - end));

		_size -= end - start;
		return iterator(_data + start);
	}

	void swap(vector &x)
	{
		vector tmp = *this;

		*this = x;
		x = tmp;
	}

	void clear()
	{
		if (!_data)
			return;
		for (size_type i = 0; i < _size; i++)
			allocator.destroy(_data + i);
		_size = 0;
	}

	allocator_type get_allocator() const
	{
		return allocator;
	}

private:
	void range_check(size_type n) const
	{
		if (n < _size)
			return;
		std::ostringstream oss;

		oss << "vector::range_check: n (which is " << n << ") >= this->size() (which is " << _size << ")";
		throw std::out_of_range(oss.str());
	}

	size_type next_capacity(size_type n)
	{
		size_type i;
		for (i = _capacity; i < n; i *= 2)
			;
		return i * 2;
	}

	template <typename Integral>
	void _init_vec(Integral n, Integral val, _truth_type)
	{
		assign(n, val);
	}

	template <typename InputIterator>
	void _init_vec(InputIterator first, InputIterator last, _false_type)
	{
		assign(first, last);
	}

	template <typename Integral>
	void _dispatch_assignation(Integral n, Integral val, _truth_type)
	{
		insert(begin(), n, val);
	}

	template <typename InputIterator>
	void _dispatch_assignation(InputIterator first, InputIterator last, _false_type)
	{
		insert(begin(), first, last);
	}

	template <typename Integral>
	iterator _dispatch_insert(iterator position, Integral n, Integral val, _truth_type)
	{
		return _fill_insert(position, n, val);
	}

	template <typename InputIterator>
	iterator _dispatch_insert(iterator position, InputIterator first, InputIterator last, _false_type)
	{
		return _range_insert(position, first, last);
	}

	template <typename InputIterator>
	iterator _range_insert(iterator position, InputIterator first, InputIterator last)
	{
		difference_type fs = position - begin();
		typename InputIterator::difference_type n = 0;

		for (InputIterator it = first; it != last; it++)
			n++;

		if (!_capacity)
			reserve(n);
		else if (_size + n > _capacity)
			reserve(next_capacity(n));

		memmove(_data + fs + n, _data + fs, sizeof(value_type) * (_size - fs));
		size_type i = 0;
		for (InputIterator it = first; it != last; it++, i++)
			allocator.construct(_data + fs + i, *it);
		_size += n;

		return iterator(_data + fs);
	}

	iterator _fill_insert(iterator position, size_type n, const value_type &val)
	{
		difference_type fs = position - begin();

		if (!_capacity)
			reserve(n);
		else if (_size + n > _capacity)
			reserve(next_capacity(n));

		memmove(_data + fs + n, _data + fs, sizeof(value_type) * (_size - fs));

		for (size_type i = 0; i < n; i++)
			allocator.construct(_data + fs + i, val);
		_size += n;
		return iterator(_data + fs);
	}

	pointer _data;
	size_type _capacity;
	size_type _size;
	allocator_type allocator;
};

#endif
