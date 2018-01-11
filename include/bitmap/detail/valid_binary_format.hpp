//-----------------------------------------------------------------------------
// Copyright (c) 2017-2018 Benjamin Buch
//
// https://github.com/bebuch/bitmap
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
//-----------------------------------------------------------------------------
#ifndef _bitmap__detail__valid_binary_format__hpp_INCLUDED_
#define _bitmap__detail__valid_binary_format__hpp_INCLUDED_

#include "../pixel.hpp"

#include <type_traits>


namespace bmp::detail{


	template < typename T, bool = ::bmp::pixel::is_pixel_type_v< T > >
	struct is_valid_binary_format
		: std::bool_constant< std::is_arithmetic_v< T >
			&& !std::is_same_v< T, long double > >{};

	template < typename T >
	struct is_valid_binary_format< T, true >
		: std::bool_constant< std::is_arithmetic_v< typename T::value_type >
			&& !std::is_same_v< typename T::value_type, long double >
			&& !std::is_same_v< typename T::value_type, bool > >{};


	template < typename T >
	constexpr bool is_valid_binary_format_v =
		is_valid_binary_format< T >::value;


}


#endif
