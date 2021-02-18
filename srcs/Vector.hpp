/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
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

#include <numeric>
#include <cstring>
#include <string>
#include <sstream>
#include <stdexcept>
#include <exception>

#include <iostream>

namespace ft
{
	template <typename T>
	class Vector;

	template <typename T>
	class VectorIterator;

	template <typename T>
	class VectorReverseIterator;

	template <typename T>
	VectorIterator<T> operator+(typename VectorIterator<T>::difference_type n, const VectorIterator<T> a)
	{
		return a + n;
	}

	template <typename T>
	VectorReverseIterator<T> operator+(typename VectorReverseIterator<T>::difference_type n, const VectorReverseIterator<T> a)
	{
		return a + n;
	}

	template <typename T>
	void swap(Vector<T> &a, Vector<T> &b)
	{
		a.swap(b);
	}

	template <typename T>
	bool operator==(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		for (typename Vector<T>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return (true);
	}

	template <typename T>
	bool operator!=(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator<(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T>
	bool operator>(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T>
	bool operator<=(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T>
	bool operator>=(const Vector<T> &lhs, const Vector<T> &rhs)
	{
		return !(lhs < rhs);
	}
} // namespace ft

template <typename T>
class ft::VectorIterator
{
public:
	typedef std::random_access_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;

	typedef T value_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef T *pointer;

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

	VectorIterator &operator=(const VectorIterator &other)
	{
		_ptr = other._ptr;
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

private:
	pointer _ptr;
};

template <typename T>
class ft::VectorReverseIterator
{
public:
	typedef std::random_access_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;

	typedef T value_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef T *pointer;

	VectorReverseIterator() : _ptr(NULL)
	{
	}

	VectorReverseIterator(pointer ptr) : _ptr(ptr)
	{
	}

	VectorReverseIterator(const VectorReverseIterator &other)
	{
		*this = other;
	}

	VectorReverseIterator &operator=(const VectorReverseIterator &other)
	{
		_ptr = other._ptr;
		return *this;
	}

	bool operator==(const VectorReverseIterator &b) const
	{
		return _ptr == b._ptr;
	}

	bool operator!=(const VectorReverseIterator &b) const
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

	VectorReverseIterator &operator++()
	{
		_ptr--;
		return *this;
	}

	VectorReverseIterator operator++(int)
	{
		VectorReverseIterator it(*this);
		_ptr--;
		return it;
	}

	VectorReverseIterator &operator--()
	{
		_ptr++;
		return *this;
	}

	VectorReverseIterator operator--(int)
	{
		VectorReverseIterator it(*this);
		_ptr++;
		return it;
	}

	VectorReverseIterator operator+(difference_type n) const
	{
		VectorReverseIterator it(*this);

		it._ptr -= n;
		return it;
	}

	VectorReverseIterator operator-(difference_type n) const
	{
		VectorReverseIterator it(*this);

		it._ptr += n;
		return it;
	}

	difference_type operator-(const VectorReverseIterator &b) const
	{
		return _ptr - b._ptr;
	}

	bool operator<(const VectorReverseIterator &b) const
	{
		return _ptr > b._ptr;
	}

	bool operator>(const VectorReverseIterator &b) const
	{
		return _ptr < b._ptr;
	}

	bool operator<=(const VectorReverseIterator &b) const
	{
		return !(*this > b);
	}

	bool operator>=(const VectorReverseIterator &b) const
	{
		return !(*this < b);
	}

	VectorReverseIterator &operator+=(difference_type n)
	{
		*this = *this + n;
		return *this;
	}

	VectorReverseIterator &operator-=(difference_type n)
	{
		*this = *this - n;
		return *this;
	}

	reference operator[](difference_type n)
	{
		return *(_ptr - n);
	}

	const_reference operator[](difference_type n) const
	{
		return *(_ptr - n);
	}

private:
	pointer _ptr;
};

template <typename T>
class ft::Vector
{
public:
	typedef T value_type;
	typedef T &reference;
	typedef T *pointer;
	typedef const value_type &const_reference;
	typedef const value_type *const_pointer;
	typedef VectorIterator<value_type> iterator;
	typedef VectorIterator<const value_type> const_iterator;
	typedef VectorReverseIterator<value_type> reverse_iterator;
	typedef VectorReverseIterator<const value_type> const_reverse_iterator;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

	explicit Vector() : _data(NULL), _capacity(0), _size(0)
	{
	}

	explicit Vector(size_type n, const value_type &val = value_type()) : _data(NULL), _capacity(0), _size(0)
	{
		assign(n, val);
	}

	template <class InputIterator>
	Vector(InputIterator first, InputIterator last) : _data(NULL), _capacity(0), _size(0)
	{
		typedef typename __is_integer<InputIterator>::__type Integral;
		_init_vec(first, last, Integral());
	}

	Vector(const Vector &x) : _data(NULL), _capacity(0), _size(0)
	{
		*this = x;
	}

	~Vector()
	{
		clear();
		operator delete(_data);
	}

	Vector &operator=(const Vector<value_type> &x)
	{
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
		return reverse_iterator(_data + _size - 1);
	}

	reverse_iterator rend()
	{
		return reverse_iterator(_data - 1);
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(_data + _size - 1);
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(_data - 1);
	}

	size_type size() const
	{
		return _size;
	}

	size_type max_size() const
	{
		return std::numeric_limits<difference_type>().max() / sizeof(value_type);
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
			pointer data = static_cast<pointer>(operator new(sizeof(value_type) * n));

			if (_data)
			{
				memcpy(data, _data, sizeof(value_type) * _size);
				operator delete(_data);
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
		new (_data + _size++) value_type(val);
	}

	void pop_back()
	{
		_data[--_size].~value_type();
	}

	iterator insert(iterator position, const value_type &val)
	{
		return insert(position, 1, val);
	}

	iterator insert(iterator position, size_type n, const value_type &val)
	{
		return _fill_insert(position, n, val);
	}

	template <typename InputIterator>
	iterator insert(iterator position, InputIterator first, InputIterator last)
	{
		typedef typename __is_integer<InputIterator>::__type _Integral;
		return _dispatch_insert(position, first, last, _Integral());
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

	void swap(Vector &x)
	{
		Vector tmp = *this;

		*this = x;
		x = tmp;
	}

	void clear()
	{
		if (!_data)
			return;
		for (size_type i = 0; i < _size; i++)
			_data[i].~value_type();
		_size = 0;
	}

private:
	void range_check(size_type n) const
	{
		if (n < _size)
			return;
		std::ostringstream oss;

		oss << "Vector::range_check: n (which is " << n << ") >= this->size() (which is " << _size << ")";
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
			new (_data + fs + i) value_type(*it);
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
			new (_data + fs + i) value_type(val);
		_size += n;
		return iterator(_data + fs);
	}

	pointer _data;
	size_type _capacity;
	size_type _size;
};

#endif
