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
	struct is_integral
	{
		enum
		{
			_value = 0
		};
		typedef _false_type __type;
	};

	template <>
	struct is_integral<int>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct is_integral<unsigned int>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct is_integral<char>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct is_integral<signed char>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct is_integral<unsigned char>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct is_integral<float>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct is_integral<double>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct is_integral<long>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct is_integral<unsigned long>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct is_integral<long long>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct is_integral<unsigned long long>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct is_integral<short>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct is_integral<unsigned short>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <>
	struct is_integral<bool>
	{
		enum
		{
			_value = 1
		};
		typedef _truth_type __type;
	};

	template <bool B, class T = void>
	struct enable_if
	{
	};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

} // namespace ft

#endif
