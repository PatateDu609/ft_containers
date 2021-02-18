/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 03:35:37 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/18 04:21:19 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
{
	struct _truth_type
	{
	};
	struct _false_type
	{
	};

	template <class T>
	struct __is_integer
	{
		enum
		{
			_value = 0
		};
		typedef _false_type __type;
	};

	template <>
	struct __is_integer<int>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct __is_integer<unsigned int>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct __is_integer<char>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct __is_integer<signed char>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct __is_integer<unsigned char>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct __is_integer<float>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct __is_integer<double>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct __is_integer<long>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct __is_integer<unsigned long>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct __is_integer<long long>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct __is_integer<unsigned long long>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct __is_integer<short>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct __is_integer<unsigned short>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct __is_integer<bool>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

} // namespace ft

#endif
